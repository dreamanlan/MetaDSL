// DslToken.js - JavaScript port of MetaDSL DslParser/DslToken.cs (DSL lexer).

'use strict';

const { StrBuf } = require('./Dsl.js');
const { DslConstants } = require('./DslParserWrap.js');

const PAIR_TYPE_QUESTION_COLON = 1;

const mWhiteSpaces = ' \t\r\n';
const mDelimiters = ',;';
const mBeginParentheses = '{([';
const mEndParentheses = '})]';
const mOperators = '~`!%^&*-+=|:<>?/';
const mQuotes = '\'"';
const mSpecialChars = mWhiteSpaces + mDelimiters + mBeginParentheses + mEndParentheses + mOperators + mQuotes;

function isLetter(c) { return c !== '\0' && /\p{L}/u.test(c); }
function isDigit(c) { return c !== '\0' && /\p{Nd}/u.test(c); }
function isLetterOrDigit(c) { return isLetter(c) || isDigit(c); }
function isCsWhiteSpace(c) { return c !== '\0' && /\s/u.test(c); }

function myisdigit(c, isHex, includeEPart, includeAddSub) {
    let ret = false;
    if (isHex) {
        if (includeEPart && (c === 'P' || c === 'p')) ret = true;
        else if (includeAddSub && (c === '+' || c === '-')) ret = true;
        else if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')) ret = true;
    }
    else {
        if (includeEPart && (c === 'E' || c === 'e')) ret = true;
        else if (includeAddSub && (c === '+' || c === '-')) ret = true;
        else if (c >= '0' && c <= '9') ret = true;
    }
    return ret;
}

function mychar2int(c) {
    if (c >= '0' && c <= '9') return c.charCodeAt(0) - 48;
    if (c >= 'a' && c <= 'f') return 10 + c.charCodeAt(0) - 97;
    if (c >= 'A' && c <= 'F') return 10 + c.charCodeAt(0) - 65;
    return 0;
}

class DslToken {
    constructor(action, log, input, nullableSyntaxEnabled) {
        this.mAction = action;
        this.mLog = log;
        this.mInput = input;
        this.mIterator = 0;
        this.mLineNumber = 1;
        this.mLastLineNumber = 1;
        this.mCurToken = '';
        this.mLastToken = '';
        this.mCommentBuilder = new StrBuf();
        this.mComments = [];
        this.mCommentOnNewLine = false;
        this.mTokenBuilder = new StrBuf();
        this.mTokenQueue = [];
        this.mNullableSyntaxEnabled = nullableSyntaxEnabled;
        this.mStringBeginDelimiter = '';
        this.mStringEndDelimiter = '';
        this.mScriptBeginDelimiter = '';
        this.mScriptEndDelimiter = '';
        this.mOnGetToken = null;
        this.mOnTokenCanEatChar = null;
    }

    get() {
        let tok = this.getImpl();
        if (this.mOnGetToken !== null) {
            // Mutable stand-in for C# ref parameters.
            const info = { tok: this.mCurToken, val: tok, line: this.mLineNumber };
            this.mOnGetToken(this.mAction, this, info);
            this.mCurToken = info.tok;
            tok = info.val;
            this.mLineNumber = info.line;
        }
        return tok;
    }

    getImpl() {
        this.mLastToken = this.mCurToken;
        this.mLastLineNumber = this.mLineNumber;
        if (this.mTokenQueue.length > 0) {
            const token = this.mTokenQueue.shift();
            this.mCurToken = token.Token;
            this.mLineNumber = token.LineNumber;
            return token.TokenValue;
        }
        let isSkip = true;
        // skip comments and white spaces
        for (; isSkip && this.CurChar !== '\0';) {
            isSkip = false;
            for (; mWhiteSpaces.indexOf(this.CurChar) >= 0; ++this.mIterator) {
                if (this.CurChar === '\n') {
                    ++this.mLineNumber;
                    if (this.mComments.length <= 0) {
                        this.mCommentOnNewLine = true;
                    }
                }
                isSkip = true;
            }
            // #Leading single-line or block comment
            if (this.CurChar === '#' || (this.CurChar === '/' && this.NextChar === '/')) {
                this.mCommentBuilder.Clear();
                for (; this.CurChar !== '\0' && this.CurChar !== '\n'; ++this.mIterator) {
                    if (this.CurChar !== '\r') this.mCommentBuilder.Append(this.CurChar);
                }
                isSkip = true;
                this.mComments.push(this.mCommentBuilder.ToString());
            }
            // C++ style multi-line comments
            if (this.CurChar === '/' && this.NextChar === '*') {
                this.mCommentBuilder.Clear();
                this.mCommentBuilder.Append(this.CurChar);
                this.mCommentBuilder.Append(this.NextChar);
                ++this.mIterator;
                ++this.mIterator;
                for (; this.CurChar !== '\0'; ++this.mIterator) {
                    if (this.CurChar === '\n') {
                        this.mCommentBuilder.AppendLine();
                        ++this.mLineNumber;
                    }
                    else if (this.CurChar === '*' && this.NextChar === '/') {
                        this.mCommentBuilder.Append(this.CurChar);
                        this.mCommentBuilder.Append(this.NextChar);
                        ++this.mIterator;
                        ++this.mIterator;
                        break;
                    }
                    else if (this.CurChar !== '\r') {
                        this.mCommentBuilder.Append(this.CurChar);
                    }
                }
                isSkip = true;
                this.mComments.push(this.mCommentBuilder.ToString());
            }
        }
        this.mTokenBuilder.Clear();
        if (this.CurChar === '\0') { // end of input
            this.mCurToken = '<<eof>>';
            return DslConstants.END_OF_SLK_INPUT_;
        }
        else if (this.StringBeginDelimiter.length > 0 && this.StringEndDelimiter.length > 0 && this.IsBegin(this.StringBeginDelimiter)) {
            this.mIterator += this.StringBeginDelimiter.length;
            this.mCurToken = this.getBlockString(this.StringEndDelimiter);
            return DslConstants.STRING_;
        }
        else if (this.ScriptBeginDelimiter.length > 0 && this.ScriptEndDelimiter.length > 0 && this.IsBegin(this.ScriptBeginDelimiter)) {
            this.mIterator += this.ScriptBeginDelimiter.length;
            this.mCurToken = this.getBlockString(this.ScriptEndDelimiter);
            return DslConstants.SCRIPT_CONTENT_;
        }
        else if (this.CurChar === '{' && this.NextChar === ':') {
            ++this.mIterator;
            ++this.mIterator;
            const line = this.mLineNumber;
            // find the end of script ':}'
            for (; this.CurChar !== '\0';) {
                while (this.CurChar !== '\0' && this.CurChar !== ':') {
                    if (this.CurChar === '\n') ++this.mLineNumber;
                    this.mTokenBuilder.Append(this.CurChar);
                    ++this.mIterator;
                }
                if (this.CurChar === '\0') break;
                if (this.NextChar === '}') {
                    ++this.mIterator;
                    ++this.mIterator;
                    break;
                }
                else {
                    this.mTokenBuilder.Append(this.CurChar);
                    ++this.mIterator;
                }
            }
            if (this.CurChar === '\0') {
                this.mLog.Log('[error][line {0}]: ExternScript can\'t finish! \n', line);
            }
            this.mCurToken = this.mTokenBuilder.ToString();
            this.mCurToken = this.removeFirstAndLastEmptyLine(this.mCurToken);
            return DslConstants.SCRIPT_CONTENT_;
        }
        else if (this.CurChar === '[' && this.NextChar === ':') {
            this.mIterator += 2;
            this.mCurToken = '[:';
            return DslConstants.BRACKET_COLON_BEGIN_;
        }
        else if (this.CurChar === ':' && this.NextChar === ']') {
            this.mIterator += 2;
            this.mCurToken = ':]';
            return DslConstants.BRACKET_COLON_END_;
        }
        else if (this.CurChar === '(' && this.NextChar === ':') {
            this.mIterator += 2;
            this.mCurToken = '(:';
            return DslConstants.PARENTHESES_COLON_BEGIN_;
        }
        else if (this.CurChar === ':' && this.NextChar === ')') {
            this.mIterator += 2;
            this.mCurToken = ':)';
            return DslConstants.PARENTHESES_COLON_END_;
        }
        else if (this.CurChar === '<' && this.NextChar === ':') {
            this.mIterator += 2;
            if (this.CurChar === ':') {
                if (this.NextChar === '>') {
                    this.mCurToken = '<:';
                    return DslConstants.ANGLE_BRACKET_COLON_BEGIN_;
                }
                else {
                    ++this.mIterator;
                    this.mTokenQueue.push({ Token: '::', TokenValue: DslConstants.COLON_COLON_, LineNumber: this.mLineNumber });
                    this.mCurToken = '<';
                    return this.getOperatorTokenValue();
                }
            }
            else {
                this.mCurToken = '<:';
                return DslConstants.ANGLE_BRACKET_COLON_BEGIN_;
            }
        }
        else if (this.CurChar === ':' && this.NextChar === '>') {
            this.mIterator += 2;
            this.mCurToken = ':>';
            return DslConstants.ANGLE_BRACKET_COLON_END_;
        }
        else if (this.CurChar === '{' && this.NextChar === '%') {
            this.mIterator += 2;
            this.mCurToken = '{%';
            return DslConstants.BRACE_PERCENT_BEGIN_;
        }
        else if (this.CurChar === '%' && this.NextChar === '}') {
            this.mIterator += 2;
            this.mCurToken = '%}';
            return DslConstants.BRACE_PERCENT_END_;
        }
        else if (this.CurChar === '[' && this.NextChar === '%') {
            this.mIterator += 2;
            this.mCurToken = '[%';
            return DslConstants.BRACKET_PERCENT_BEGIN_;
        }
        else if (this.CurChar === '%' && this.NextChar === ']') {
            this.mIterator += 2;
            this.mCurToken = '%]';
            return DslConstants.BRACKET_PERCENT_END_;
        }
        else if (this.CurChar === '(' && this.NextChar === '%') {
            this.mIterator += 2;
            this.mCurToken = '(%';
            return DslConstants.PARENTHESES_PERCENT_BEGIN_;
        }
        else if (this.CurChar === '%' && this.NextChar === ')') {
            this.mIterator += 2;
            this.mCurToken = '%)';
            return DslConstants.PARENTHESES_PERCENT_END_;
        }
        else if (this.CurChar === '<' && this.NextChar === '%') {
            this.mIterator += 2;
            this.mCurToken = '<%';
            return DslConstants.ANGLE_BRACKET_PERCENT_BEGIN_;
        }
        else if (this.CurChar === '%' && this.NextChar === '>') {
            this.mIterator += 2;
            this.mCurToken = '%>';
            return DslConstants.ANGLE_BRACKET_PERCENT_END_;
        }
        else if (this.CurChar === ':' && this.NextChar === ':') {
            this.mIterator += 2;
            this.mCurToken = '::';

            if (this.lastTokenEndsWithOperator()) return this.getOperatorTokenValue();
            const nextChar = this.PeekNextValidChar(0);
            const nextChar2 = this.PeekNextValidChar(1);
            const nextChar3 = this.PeekNextValidChar(2);
            if (this.isNotIdentifierAndBeginParentheses(nextChar) &&
                !(nextChar === '<' && nextChar2 === ':' && isCsWhiteSpace(nextChar3)) &&
                !(nextChar === '<' && nextChar2 === '%' && isCsWhiteSpace(nextChar3))) {
                return this.getOperatorTokenValue();
            }
            return DslConstants.COLON_COLON_;
        }
        else if (this.CurChar === '?' || this.CurChar === '!') {
            if (this.lastTokenEndsWithOperator()) {
                this.getOperatorToken();
                return this.getOperatorTokenValue();
            }
            else if (this.mNullableSyntaxEnabled) {
                const tok = this.CurChar === '?' ? '?' : '!';
                if (this.NextChar === '.') {
                    ++this.mIterator;
                    this.mCurToken = tok;
                    return DslConstants.OP_TOKEN_NULLABLE_;
                }
                else if (this.NextChar === '-' && this.PeekChar(2) === '>') {
                    ++this.mIterator;
                    this.mCurToken = tok;
                    return DslConstants.OP_TOKEN_NULLABLE_;
                }
                else if (this.NextChar === '(' || this.NextChar === '[' || this.NextChar === '{') {
                    ++this.mIterator;
                    this.mCurToken = tok;
                    return DslConstants.OP_TOKEN_NULLABLE_;
                }
                else if (this.NextChar === '<' && (this.PeekChar(2) === ':' || this.PeekChar(2) === '%')) {
                    ++this.mIterator;
                    this.mCurToken = tok;
                    return DslConstants.OP_TOKEN_NULLABLE_;
                }
                else {
                    this.getOperatorToken();
                    return this.getOperatorTokenValue();
                }
            }
            else {
                this.getOperatorToken();
                return this.getOperatorTokenValue();
            }
        }
        else if (this.CurChar === '-') {
            if (this.NextChar === '>') {
                this.mIterator += 2;
                if (this.CurChar === '*') {
                    ++this.mIterator;
                    this.mCurToken = '->*';
                    if (this.lastTokenEndsWithOperator()) return this.getOperatorTokenValue();
                    if (this.memberAccessFollowedByOperator()) return this.getOperatorTokenValue();
                    return DslConstants.POINTER_STAR_;
                }
                else {
                    this.mCurToken = '->';
                    if (this.lastTokenEndsWithOperator()) return this.getOperatorTokenValue();
                    if (this.memberAccessFollowedByOperator()) return this.getOperatorTokenValue();
                    return DslConstants.POINTER_;
                }
            }
            else {
                this.getOperatorToken();
                return this.getOperatorTokenValue();
            }
        }
        else if (this.CurChar === '.' && this.NextChar === '*') {
            this.mIterator += 2;
            this.mCurToken = '.*';
            if (this.lastTokenEndsWithOperator()) return this.getOperatorTokenValue();
            if (this.memberAccessFollowedByOperator()) return this.getOperatorTokenValue();
            return DslConstants.PERIOD_STAR_;
        }
        else if (this.CurChar === '.' && this.NextChar === '.') {
            this.mIterator += 2;
            if (this.CurChar === '.') {
                ++this.mIterator;
                this.mCurToken = '...';
                return DslConstants.IDENTIFIER_;
            }
            else {
                this.mCurToken = '..';
                return this.getOperatorTokenValue();
            }
        }
        else if (mOperators.indexOf(this.CurChar) >= 0) {
            this.getOperatorToken();
            return this.getOperatorTokenValue();
        }
        else if (this.CurChar === '.' && !myisdigit(this.NextChar, false)) {
            const c = this.CurChar;
            ++this.mIterator;
            this.mTokenBuilder.Append(c);
            this.mCurToken = this.mTokenBuilder.ToString();
            if (this.lastTokenEndsWithOperator()) return this.getOperatorTokenValue();
            if (this.memberAccessFollowedByOperator()) return this.getOperatorTokenValue();
            return DslConstants.DOT_;
        }
        else if (this.CurChar === '{') {
            ++this.mIterator;
            this.mCurToken = '{';
            return DslConstants.LBRACE_;
        }
        else if (this.CurChar === '}') {
            ++this.mIterator;
            this.mCurToken = '}';
            return DslConstants.RBRACE_;
        }
        else if (this.CurChar === '[') {
            ++this.mIterator;
            this.mCurToken = '[';
            return DslConstants.LBRACK_;
        }
        else if (this.CurChar === ']') {
            ++this.mIterator;
            this.mCurToken = ']';
            return DslConstants.RBRACK_;
        }
        else if (this.CurChar === '(') {
            ++this.mIterator;
            this.mCurToken = '(';
            return DslConstants.LPAREN_;
        }
        else if (this.CurChar === ')') {
            ++this.mIterator;
            this.mCurToken = ')';
            return DslConstants.RPAREN_;
        }
        else if (this.CurChar === ',') {
            ++this.mIterator;
            this.mCurToken = ',';
            return DslConstants.COMMA_;
        }
        else if (this.CurChar === ';') {
            ++this.mIterator;
            this.mCurToken = ';';
            return DslConstants.SEMI_;
        }
        else if ((this.CurChar === '@' && (this.NextChar === '"' || this.NextChar === '\'')) ||
            (this.CurChar === '@' && this.NextChar === '$' && (this.PeekChar(2) === '"' || this.PeekChar(2) === '\'')) ||
            (this.CurChar === '$' && this.NextChar === '@' && (this.PeekChar(2) === '"' || this.PeekChar(2) === '\''))) {
            let isDollar = false;
            if ((this.CurChar === '@' && this.NextChar === '$') || (this.CurChar === '$' && this.NextChar === '@')) {
                this.mIterator += 2;
                isDollar = true;
            }
            else {
                ++this.mIterator;
            }
            const line = this.mLineNumber;
            const c = this.CurChar;
            for (++this.mIterator; this.CurChar !== '\0'; ++this.mIterator) {
                if (this.CurChar === '\n') ++this.mLineNumber;
                if (this.CurChar === c) {
                    if (this.NextChar === c) {
                        this.mTokenBuilder.Append(this.CurChar);
                        ++this.mIterator;
                    }
                    else {
                        break;
                    }
                }
                else {
                    this.mTokenBuilder.Append(this.CurChar);
                }
            }
            if (this.CurChar !== '\0') {
                ++this.mIterator;
            }
            else {
                this.mLog.Log('[error][line {0}]: String cannot be ended !\n', line);
            }
            this.mCurToken = this.mTokenBuilder.ToString();
            // Ordinary strings keep the appearance of the source code (no trimming of blank lines).
            if (isDollar) return DslConstants.DOLLAR_STRING_;
            return DslConstants.STRING_;
        }
        else { // keyword, identifier or constant
            if (this.CurChar === '"' || this.CurChar === '\'' || (this.CurChar === '$' && (this.NextChar === '"' || this.NextChar === '\''))) {
                let isDollar = false;
                if (this.CurChar === '$') {
                    ++this.mIterator;
                    isDollar = true;
                }
                const line = this.mLineNumber;
                const c = this.CurChar;
                for (++this.mIterator; this.CurChar !== '\0'; ++this.mIterator) {
                    if (this.CurChar === '\n') ++this.mLineNumber;
                    if (this.CurChar === '\\') {
                        ++this.mIterator;
                        if (this.CurChar === 'n') {
                            this.mTokenBuilder.Append('\n');
                        }
                        else if (this.CurChar === 'r') {
                            this.mTokenBuilder.Append('\r');
                        }
                        else if (this.CurChar === 't') {
                            this.mTokenBuilder.Append('\t');
                        }
                        else if (this.CurChar === 'v') {
                            this.mTokenBuilder.Append('\v');
                        }
                        else if (this.CurChar === 'a') {
                            this.mTokenBuilder.Append('\x07');
                        }
                        else if (this.CurChar === 'b') {
                            this.mTokenBuilder.Append('\b');
                        }
                        else if (this.CurChar === 'f') {
                            this.mTokenBuilder.Append('\f');
                        }
                        else if (this.CurChar === 'u' && myisdigit(this.NextChar, true) && myisdigit(this.PeekChar(2), true) && myisdigit(this.PeekChar(3), true)) {
                            ++this.mIterator;
                            // 4 digits HEX
                            const h1 = this.CurChar;
                            ++this.mIterator;
                            const h2 = this.CurChar;
                            ++this.mIterator;
                            const h3 = this.CurChar;
                            ++this.mIterator;
                            const h4 = this.CurChar;
                            this.mTokenBuilder.Append(String.fromCharCode((mychar2int(h1) << 12) + (mychar2int(h2) << 8) + (mychar2int(h3) << 4) + mychar2int(h4)));
                        }
                        else if (this.CurChar === 'U' && myisdigit(this.NextChar, true) && myisdigit(this.PeekChar(2), true) && myisdigit(this.PeekChar(3), true) &&
                            myisdigit(this.PeekChar(4), true) && myisdigit(this.PeekChar(5), true) && myisdigit(this.PeekChar(6), true) && myisdigit(this.PeekChar(7), true)) {
                            ++this.mIterator;
                            // 8 digits HEX
                            const h1 = this.CurChar;
                            ++this.mIterator;
                            const h2 = this.CurChar;
                            ++this.mIterator;
                            const h3 = this.CurChar;
                            ++this.mIterator;
                            const h4 = this.CurChar;
                            ++this.mIterator;
                            const h5 = this.CurChar;
                            ++this.mIterator;
                            const h6 = this.CurChar;
                            ++this.mIterator;
                            const h7 = this.CurChar;
                            ++this.mIterator;
                            const h8 = this.CurChar;
                            this.mTokenBuilder.Append(String.fromCharCode((mychar2int(h5) << 12) + (mychar2int(h6) << 8) + (mychar2int(h7) << 4) + mychar2int(h8)));
                            this.mTokenBuilder.Append(String.fromCharCode((mychar2int(h1) << 12) + (mychar2int(h2) << 8) + (mychar2int(h3) << 4) + mychar2int(h4)));
                        }
                        else if (this.CurChar === 'x' && myisdigit(this.NextChar, true)) {
                            ++this.mIterator;
                            // 1~2 digits HEX
                            const h1 = this.CurChar;
                            if (myisdigit(this.NextChar, true)) {
                                ++this.mIterator;
                                const h2 = this.CurChar;
                                this.mTokenBuilder.Append(String.fromCharCode((mychar2int(h1) << 4) + mychar2int(h2)));
                            }
                            else {
                                this.mTokenBuilder.Append(String.fromCharCode(mychar2int(h1)));
                            }
                        }
                        else if (myisdigit(this.CurChar, false)) {
                            // 1~3 digits OCT (kept identical to the C# implementation)
                            const o1 = this.CurChar;
                            if (myisdigit(this.NextChar, false)) {
                                ++this.mIterator;
                                const o2 = this.CurChar;
                                if (myisdigit(this.NextChar, false)) {
                                    ++this.mIterator;
                                    const o3 = this.CurChar;
                                    this.mTokenBuilder.Append(String.fromCharCode((mychar2int(o1) << 6) + (mychar2int(o2) * 3) + mychar2int(o3)));
                                }
                                else {
                                    this.mTokenBuilder.Append(String.fromCharCode((mychar2int(o1) << 3) + mychar2int(o2)));
                                }
                            }
                            else {
                                this.mTokenBuilder.Append(String.fromCharCode(mychar2int(o1)));
                            }
                        }
                        else {
                            this.mTokenBuilder.Append(this.CurChar);
                        }
                    }
                    else if (this.CurChar === c) {
                        if (this.NextChar === c) {
                            this.mTokenBuilder.Append(this.CurChar);
                            ++this.mIterator;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        this.mTokenBuilder.Append(this.CurChar);
                    }
                }
                if (this.CurChar !== '\0') {
                    ++this.mIterator;
                }
                else {
                    this.mLog.Log('[error][line {0}]: string can\'t end !\n', line);
                }
                this.mCurToken = this.mTokenBuilder.ToString();
                if (isDollar) return DslConstants.DOLLAR_STRING_;
                return DslConstants.STRING_;
            }
            else {
                let isNum = true;
                let isHex = false;
                let includeEPart = false;
                let includeAddSub = false;
                let waitFinish = false;
                let dotCt = 0;
                if (this.CurChar === '0' && this.NextChar === 'x') {
                    isHex = true;
                    this.mTokenBuilder.Append(this.CurChar);
                    ++this.mIterator;
                    this.mTokenBuilder.Append(this.CurChar);
                    ++this.mIterator;
                }
                for (let charCt = 0; this.CurChar === '?' || this.CurChar === '\'' ||
                    (isNum && myisdigit(this.CurChar, isHex, includeEPart, includeAddSub)) ||
                    !this.isSpecialChar(this.CurChar); ++this.mIterator, ++charCt) {
                    if (this.CurChar === '#') {
                        break;
                    }
                    else if (this.CurChar === '?') {
                        // In the case of a nullable type, only one question mark is allowed.
                        if (this.mOnTokenCanEatChar !== null) {
                            if (this.mOnTokenCanEatChar(this.mTokenBuilder, this.CurChar)) {
                                this.mTokenBuilder.Append(this.CurChar);
                                ++this.mIterator;
                                ++charCt;
                            }
                        }
                        break;
                    }
                    else if (this.CurChar === '\'') {
                        if (!isNum) {
                            break;
                        }
                        else {
                            if (this.NextChar !== '\0' && !myisdigit(this.NextChar, isHex, includeEPart, includeAddSub)) {
                                break;
                            }
                            ++this.mIterator;
                            ++charCt;
                        }
                    }
                    else if (this.CurChar === '.') {
                        if (!isNum || isHex) {
                            break;
                        }
                        else {
                            if (this.NextChar === 'b' || this.NextChar === 'B' || this.NextChar === 'f' || this.NextChar === 'F' || this.NextChar === 'l' || this.NextChar === 'L') {
                            }
                            else if (this.NextChar !== '\0' && !myisdigit(this.NextChar, isHex, includeEPart, includeAddSub)) {
                                const c = this.PeekNextValidChar(1);
                                if (!this.isSpecialChar(c)) break;
                            }
                        }
                        ++dotCt;
                        if (dotCt > 1) break;
                    }
                    else if (isNum) {
                        if (dotCt > 0 && (this.CurChar === 'b' || this.CurChar === 'B' || this.CurChar === 'f' || this.CurChar === 'F' || this.CurChar === 'l' || this.CurChar === 'L')) {
                        }
                        else if (dotCt === 0 && charCt > 0 && (this.CurChar === 'l' || this.CurChar === 'L' || this.CurChar === 'u' || this.CurChar === 'U' || this.CurChar === 'z' || this.CurChar === 'Z')) {
                        }
                        else if (!myisdigit(this.CurChar, isHex, includeEPart, includeAddSub)) {
                            isNum = false;
                        }
                    }
                    if (isNum && !waitFinish) {
                        if (includeEPart && ((!isHex && (this.CurChar === 'e' || this.CurChar === 'E')) || (isHex && (this.CurChar === 'p' || this.CurChar === 'P')))) {
                            includeEPart = false;
                            includeAddSub = true;
                        }
                        else if (includeAddSub) {
                            includeAddSub = false;
                            waitFinish = true;
                        }
                        else {
                            includeEPart = true;
                        }
                    }
                    this.mTokenBuilder.Append(this.CurChar);
                }
                this.mCurToken = this.mTokenBuilder.ToString();
                if (isNum) return DslConstants.NUMBER_;
                return DslConstants.IDENTIFIER_;
            }
        }
    }

    // mLastToken ends with an operator (member access tokens are then treated as operators).
    lastTokenEndsWithOperator() {
        const last = this.mLastToken;
        return last.length > 0 && this.isNotIdentifierAndNumberAndEndParentheses(last[last.length - 1]) &&
            last[last.length - 1] !== '?' && last[last.length - 1] !== '!' &&
            (last.length !== 2 || (!((last[0] === ':' && last[1] === '>') || (last[0] === '%' && last[1] === '>'))));
    }

    memberAccessFollowedByOperator() {
        const nextChar = this.PeekNextValidChar(0);
        const nextChar2 = this.PeekNextValidChar(1);
        const nextChar3 = this.PeekNextValidChar(2);
        return this.isNotIdentifierAndBeginParentheses(nextChar) &&
            !(nextChar === '<' && nextChar2 === ':' && isCsWhiteSpace(nextChar3)) &&
            !(nextChar === '<' && nextChar2 === '%' && isCsWhiteSpace(nextChar3));
    }

    peek(level) { // scan next token without consuming it
        this.mLog.Log('[info] peek_token is not called in an LL(1) grammar\n');
        return 0;
    }

    setCurToken(tok) { this.mCurToken = tok; }
    setLastToken(tok) { this.mLastToken = tok; }
    enqueueToken(tok, val, line) {
        this.mTokenQueue.push({ Token: tok, TokenValue: val, LineNumber: line });
        return true;
    }
    getCurToken() { return this.mCurToken; }
    getLastToken() { return this.mLastToken; }
    getLineNumber() { return this.mLineNumber; }
    getLastLineNumber() { return this.mLastLineNumber; }
    IsCommentOnNewLine() { return this.mCommentOnNewLine; }
    GetComments() { return this.mComments; }
    ResetComments() {
        this.mCommentOnNewLine = false;
        this.mComments.length = 0;
    }
    setStringDelimiter(begin, end) {
        this.mStringBeginDelimiter = begin;
        this.mStringEndDelimiter = end;
    }
    setScriptDelimiter(begin, end) {
        this.mScriptBeginDelimiter = begin;
        this.mScriptEndDelimiter = end;
    }
    get StringBeginDelimiter() { return this.mStringBeginDelimiter; }
    get StringEndDelimiter() { return this.mStringEndDelimiter; }
    get ScriptBeginDelimiter() { return this.mScriptBeginDelimiter; }
    get ScriptEndDelimiter() { return this.mScriptEndDelimiter; }
    get OnGetToken() { return this.mOnGetToken; }
    set OnGetToken(value) { this.mOnGetToken = value; }
    get OnTokenCanEatChar() { return this.mOnTokenCanEatChar; }
    set OnTokenCanEatChar(value) { this.mOnTokenCanEatChar = value; }

    IsBegin(delimiter) {
        if (delimiter.length === 0) return false;
        const start = this.mIterator;
        return start + delimiter.length <= this.mInput.length && this.mInput.startsWith(delimiter, start);
    }

    getBlockString(delimiter) {
        const start = this.mIterator;
        const end = this.mInput.indexOf(delimiter, start);
        if (end < 0) {
            this.mLog.Log('[error][line {0}]: block can\'t finish, delimiter: {1}！\n', this.mLineNumber, delimiter);
            return '';
        }
        this.mIterator = end + delimiter.length;
        let lineStart = this.mInput.indexOf('\n', start);
        while (lineStart >= 0 && lineStart < end) {
            ++this.mLineNumber;
            lineStart = this.mInput.indexOf('\n', lineStart + 1);
        }
        return this.removeFirstAndLastEmptyLine(this.mInput.substring(start, end));
    }

    removeFirstAndLastEmptyLine(str) {
        let start = 0;
        while (start < str.length && this.isWhiteSpace(str[start]) && str[start] !== '\n') ++start;
        if (start < str.length && str[start] === '\n') {
            ++start;
        }
        else {
            // If there is no newline at the beginning of the line, preserve the white space.
            start = 0;
        }
        let end = str.length - 1;
        while (end > 0 && this.isWhiteSpace(str[end]) && str[end] !== '\n') --end;
        if (end > 0 && str[end] !== '\n') {
            // If there is no newline at the end of the line, preserve the white space.
            end = str.length - 1;
        }
        if (start > 0 || end < str.length - 1) {
            return str.substring(start, end + 1);
        }
        return str;
    }

    getOperatorToken() {
        const st = this.mIterator;
        switch (this.CurChar) {
            case '+': {
                ++this.mIterator;
                if (this.CurChar === '+' || this.CurChar === '=') ++this.mIterator;
                break;
            }
            case '-': {
                ++this.mIterator;
                if (this.CurChar === '-' || this.CurChar === '=' || this.CurChar === '>') ++this.mIterator;
                break;
            }
            case '>': {
                ++this.mIterator;
                if (this.CurChar === '=') {
                    ++this.mIterator;
                }
                else if (this.CurChar === '>') {
                    ++this.mIterator;
                    if (this.CurChar === '>') ++this.mIterator;
                    if (this.CurChar === '=') ++this.mIterator;
                }
                break;
            }
            case '<': {
                ++this.mIterator;
                if (this.CurChar === '=') {
                    ++this.mIterator;
                    if (this.CurChar === '>') ++this.mIterator;
                }
                else if (this.CurChar === '-') {
                    ++this.mIterator;
                }
                else if (this.CurChar === '<') {
                    ++this.mIterator;
                    if (this.CurChar === '=') ++this.mIterator;
                }
                break;
            }
            case '&': {
                ++this.mIterator;
                if (this.CurChar === '=') {
                    ++this.mIterator;
                }
                else if (this.CurChar === '&') {
                    ++this.mIterator;
                    if (this.CurChar === '=') ++this.mIterator;
                }
                break;
            }
            case '|': {
                ++this.mIterator;
                if (this.CurChar === '=') {
                    ++this.mIterator;
                }
                else if (this.CurChar === '|') {
                    ++this.mIterator;
                    if (this.CurChar === '=') ++this.mIterator;
                }
                break;
            }
            case '=': {
                ++this.mIterator;
                if (this.CurChar === '=' || this.CurChar === '>') ++this.mIterator;
                break;
            }
            case '!':
            case '^':
            case '*':
            case '/':
            case '%': {
                ++this.mIterator;
                if (this.CurChar === '=') ++this.mIterator;
                break;
            }
            case '?': {
                ++this.mIterator;
                if (this.CurChar === '?') {
                    ++this.mIterator;
                    if (this.CurChar === '=') ++this.mIterator;
                }
                break;
            }
            case '`': {
                ++this.mIterator;
                let isOp = false;
                while (this.isOperator(this.CurChar)) {
                    ++this.mIterator;
                    isOp = true;
                }
                if (!isOp) {
                    while (this.CurChar !== '\0' && !this.isSpecialChar(this.CurChar)) {
                        if (this.CurChar === '#' || this.CurChar === '.') break;
                        ++this.mIterator;
                    }
                }
                break;
            }
            default: {
                ++this.mIterator;
                break;
            }
        }
        const ed = this.mIterator;
        this.mCurToken = this.mInput.substring(st, ed);
    }

    getOperatorTokenValue() {
        const curOperator = this.mCurToken;
        const lastToken = this.mLastToken;
        let lastIsOperator = true;
        if (lastToken !== null && lastToken.length > 0) {
            if (this.isDelimiter(lastToken[0])) {
                lastIsOperator = true;
            }
            else if (this.isBeginParentheses(lastToken[0])) {
                lastIsOperator = true;
            }
            else {
                lastIsOperator = this.isOperator(lastToken[0]);
            }
        }
        let val = DslConstants.OP_TOKEN_2_;
        if (curOperator.length > 0) {
            const c0 = curOperator[0];
            const c1 = curOperator.length > 1 ? curOperator[1] : '\0';
            const c2 = curOperator.length > 2 ? curOperator[2] : '\0';
            const c3 = curOperator.length > 3 ? curOperator[3] : '\0';
            const c4 = curOperator.length > 4 ? curOperator[4] : '\0';
            if ((c0 === '=' && c1 === '\0') || (c0 === '<' && c1 === '-' && c2 === '\0')) {
                val = DslConstants.OP_TOKEN_1_;
            }
            else if (c0 !== '=' && c0 !== '!' && c0 !== '>' && c0 !== '<' && c1 === '=' && c2 === '\0') {
                val = DslConstants.OP_TOKEN_1_;
            }
            else if (c2 === '=' && c3 === '\0') {
                val = DslConstants.OP_TOKEN_1_;
            }
            else if (c3 === '=' && c4 === '\0') {
                val = DslConstants.OP_TOKEN_1_;
            }
            else if (c0 === '=' && c1 === '>' && c2 === '\0') {
                val = DslConstants.OP_TOKEN_2_;
            }
            else if (c0 === ':' && c1 === '\0') {
                if (this.mAction.PeekPairTypeStack() === PAIR_TYPE_QUESTION_COLON) val = DslConstants.OP_TOKEN_QUESTION_COLON_;
                else val = DslConstants.OP_TOKEN_COLON_;
            }
            else if (c0 === '?' && c1 === '\0') {
                val = DslConstants.OP_TOKEN_QUESTION_;
            }
            else if ((c0 === '|' && c1 === '|' && c2 === '\0') || (c0 === '?' && c1 === '?' && c2 === '\0')) {
                val = DslConstants.OP_TOKEN_4_;
            }
            else if (c0 === '&' && c1 === '&' && c2 === '\0') {
                val = DslConstants.OP_TOKEN_5_;
            }
            else if (c0 === '|' && c1 === '\0') {
                val = DslConstants.OP_TOKEN_6_;
            }
            else if (c0 === '^' && c1 === '\0') {
                val = DslConstants.OP_TOKEN_7_;
            }
            else if (c0 === '&' && c1 === '\0') {
                val = lastIsOperator ? DslConstants.OP_TOKEN_14_ : DslConstants.OP_TOKEN_8_;
            }
            else if (((c0 === '=' || c0 === '!') && c1 === '=' && c2 === '\0') || (c0 === '<' && c1 === '=' && c2 === '>' && c3 === '\0')) {
                val = DslConstants.OP_TOKEN_9_;
            }
            else if ((c0 === '<' || c0 === '>') && ((c1 === '=' && c2 === '\0') || c1 === '\0')) {
                val = DslConstants.OP_TOKEN_10_;
            }
            else if ((c0 === '<' && c1 === '<' && c2 === '\0') || (c0 === '>' && c1 === '>' && c2 === '\0') || (c0 === '>' && c1 === '>' && c2 === '>' && c3 === '\0')) {
                val = DslConstants.OP_TOKEN_11_;
            }
            else if ((c0 === '+' || c0 === '-') && c1 === '\0') {
                val = lastIsOperator ? DslConstants.OP_TOKEN_14_ : DslConstants.OP_TOKEN_12_;
            }
            else if (((c0 === '*' || c0 === '/' || c0 === '%') && c1 === '\0') || (c0 === '.' && c1 === '.' && c2 === '\0')) {
                if (c0 === '*' && lastIsOperator) val = DslConstants.OP_TOKEN_14_;
                else val = DslConstants.OP_TOKEN_13_;
            }
            else if ((c0 === '+' && c1 === '+' && c2 === '\0') || (c0 === '-' && c1 === '-' && c2 === '\0') || (c0 === '~' && c1 === '\0') || (c0 === '!' && c1 === '\0')) {
                val = DslConstants.OP_TOKEN_14_;
            }
            else if (c0 === '`' && c1 === '\0') {
                val = DslConstants.OP_TOKEN_0_;
            }
            else if (c0 === '`' && c1 !== '\0') {
                val = DslConstants.OP_TOKEN_3_;
            }
            else if ((c0 === '-' && c1 === '>' && (c2 === '\0' || (c2 === '*' && c3 === '\0'))) ||
                (c0 === '.' && (c1 === '\0' || (c1 === '*' && c2 === '\0'))) ||
                (c0 === ':' && c1 === ':' && c2 === '\0')) {
                this.mLog.Log('[warning][line {0}]: Member access operation \'{1}\' should not appear in operators', this.mLineNumber, this.mCurToken);
                val = DslConstants.OP_TOKEN_15_;
            }
            else {
                val = DslConstants.OP_TOKEN_3_;
            }
        }
        return val;
    }

    isNotIdentifier(c) {
        if (c === '\0') return false;
        return !isLetter(c) && c !== '_' && c !== '@' && c !== '$';
    }
    isNotIdentifierAndBeginParentheses(c) {
        if (c === '\0') return false;
        return mBeginParentheses.indexOf(c) < 0 && !isLetter(c) && c !== '_' && c !== '@' && c !== '$';
    }
    isNotIdentifierAndNumberAndEndParentheses(c) {
        if (c === '\0') return false;
        return mEndParentheses.indexOf(c) < 0 && !isLetterOrDigit(c) && c !== '_' && c !== '@' && c !== '$';
    }
    isWhiteSpace(c) {
        if (c === '\0') return false;
        return mWhiteSpaces.indexOf(c) >= 0;
    }
    isDelimiter(c) {
        if (c === '\0') return false;
        return mDelimiters.indexOf(c) >= 0;
    }
    isBeginParentheses(c) {
        if (c === '\0') return false;
        return mBeginParentheses.indexOf(c) >= 0;
    }
    isEndParentheses(c) {
        if (c === '\0') return false;
        return mEndParentheses.indexOf(c) >= 0;
    }
    isOperator(c) {
        if (c === '\0') return false;
        return mOperators.indexOf(c) >= 0;
    }
    isQuote(c) {
        if (c === '\0') return false;
        return mQuotes.indexOf(c) >= 0;
    }
    isSpecialChar(c) {
        if (c === '\0') return true;
        return mSpecialChars.indexOf(c) >= 0;
    }

    get CurChar() { return this.PeekChar(0); }
    get NextChar() { return this.PeekChar(1); }
    PeekChar(ix) {
        if (ix >= 0 && this.mIterator + ix < this.mInput.length) return this.mInput[this.mIterator + ix];
        return '\0';
    }
    PeekNextValidChar(beginIndex) {
        for (let start = this.mIterator + beginIndex; start < this.mInput.length; ++start) {
            if (mWhiteSpaces.indexOf(this.mInput[start]) >= 0) continue;
            return this.mInput[start];
        }
        return '\0';
    }
}

DslToken.myisdigit = myisdigit;
DslToken.mychar2int = mychar2int;

if (typeof module !== 'undefined' && module.exports) {
    module.exports = { DslToken, myisdigit, mychar2int };
}
if (typeof globalThis !== 'undefined') {
    globalThis.DslToken = DslToken;
}
