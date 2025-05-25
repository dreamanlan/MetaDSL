using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using Dsl.Parser;

namespace Dsl.Common
{
    public struct DslToken
    {
        internal DslToken(DslAction action, DslLog log, string input, bool nullableSyntaxEnabled)
        {
            mAction = action;
            mLog = log;
            mInput = input;
            mIterator = 0;

            mLineNumber = 1;
            mLastLineNumber = 1;

            mCurToken = string.Empty;
            mLastToken = string.Empty;

            mCommentBuilder = new StringBuilder();
            mComments = new List<string>();
            mCommentOnNewLine = false;

            mTokenBuilder = new StringBuilder();
            mTokenQueue = new Queue<TokenInfo>();

            mNullableSyntaxEnabled = nullableSyntaxEnabled;
            mStringBeginDelimiter = string.Empty;
            mStringEndDelimiter = string.Empty;
            mScriptBeginDelimiter = string.Empty;
            mScriptEndDelimiter = string.Empty;
            mOnGetToken = null;
            mOnTokenCanEatChar = null;
        }

        internal short get()
        {
            short tok = getImpl();
            if (null != mOnGetToken) {
                mOnGetToken(ref mAction, ref this, ref mCurToken, ref tok, ref mLineNumber);
            }
            return tok;
        }
        private short getImpl()
        {
            mLastToken = mCurToken;
            mLastLineNumber = mLineNumber;
            if (mTokenQueue.Count > 0) {
                var token = mTokenQueue.Dequeue();
                mCurToken = token.Token;
                mLineNumber = token.LineNumber;
                return token.TokenValue;
            }
            bool isSkip = true;
            //skip comments and white spaces
            for (; isSkip && CurChar != 0;) {
                isSkip = false;
                for (; mWhiteSpaces.IndexOf(CurChar) >= 0; ++mIterator) {
                    if (CurChar == '\n') {
                        ++mLineNumber;
                        if (mComments.Count <= 0) {
                            mCommentOnNewLine = true;
                        }
                    }
                    isSkip = true;
                }
                //#Leading single-line or block comment
                if (CurChar == '#' || CurChar == '/' && NextChar == '/') {
                    mCommentBuilder.Length = 0;
                    for (; CurChar != 0 && CurChar != '\n'; ++mIterator) {
                        if (CurChar != '\r')
                            mCommentBuilder.Append(CurChar);
                    }
                    //++mLineNumber;
                    isSkip = true;
                    mComments.Add(mCommentBuilder.ToString());
                }
                //C++ style multi-line comments
                if (CurChar == '/' && NextChar == '*') {
                    mCommentBuilder.Length = 0;
                    mCommentBuilder.Append(CurChar);
                    mCommentBuilder.Append(NextChar);
                    ++mIterator;
                    ++mIterator;
                    for (; CurChar != 0; ++mIterator) {
                        if (CurChar == '\n') {
                            mCommentBuilder.AppendLine();
                            ++mLineNumber;
                        }
                        else if (CurChar == '*' && NextChar == '/') {
                            mCommentBuilder.Append(CurChar);
                            mCommentBuilder.Append(NextChar);
                            ++mIterator;
                            ++mIterator;
                            break;
                        }
                        else if (CurChar != '\r') {
                            mCommentBuilder.Append(CurChar);
                        }
                    }
                    isSkip = true;
                    mComments.Add(mCommentBuilder.ToString());
                }
            }
            mTokenBuilder.Length = 0;
            if (CurChar == 0) {//end of input
                mCurToken = "<<eof>>";
                return DslConstants.END_OF_SLK_INPUT_;
            }
            else if (!string.IsNullOrEmpty(StringBeginDelimiter) && !string.IsNullOrEmpty(StringEndDelimiter) && IsBegin(StringBeginDelimiter)) {
                mIterator += StringBeginDelimiter.Length;
                mCurToken = getBlockString(StringEndDelimiter);
                return DslConstants.STRING_;
            }
            else if (!string.IsNullOrEmpty(ScriptBeginDelimiter) && !string.IsNullOrEmpty(ScriptEndDelimiter) && IsBegin(ScriptBeginDelimiter)) {
                mIterator += ScriptBeginDelimiter.Length;
                mCurToken = getBlockString(ScriptEndDelimiter);
                return DslConstants.SCRIPT_CONTENT_;
            }
            else if (CurChar == '{' && NextChar == ':') {
                ++mIterator;
                ++mIterator;
                int line = mLineNumber;
                //find the end of script ':}'
                for (; CurChar != 0;) {
                    while (CurChar != 0 && CurChar != ':') {
                        if (CurChar == '\n')
                            ++mLineNumber;

                        mTokenBuilder.Append(CurChar);
                        ++mIterator;
                    }
                    if (CurChar == 0)
                        break;
                    if (NextChar == '}') {
                        ++mIterator;
                        ++mIterator;
                        break;
                    }
                    else {
                        mTokenBuilder.Append(CurChar);
                        ++mIterator;
                    }
                }
                if (CurChar == 0) {
                    mLog.Log("[error][line {0}]: ExternScript can't finish! \n", line);
                }
                mCurToken = mTokenBuilder.ToString();
                mCurToken = removeFirstAndLastEmptyLine(mCurToken);
                return DslConstants.SCRIPT_CONTENT_;
            }
            else if (CurChar == '[' && NextChar == ':') {
                ++mIterator;
                ++mIterator;
                mCurToken = "[:";
                return DslConstants.BRACKET_COLON_BEGIN_;
            }
            else if (CurChar == ':' && NextChar == ']') {
                ++mIterator;
                ++mIterator;
                mCurToken = ":]";
                return DslConstants.BRACKET_COLON_END_;
            }
            else if (CurChar == '(' && NextChar == ':') {
                ++mIterator;
                ++mIterator;
                mCurToken = "(:";
                return DslConstants.PARENTHESES_COLON_BEGIN_;
            }
            else if (CurChar == ':' && NextChar == ')') {
                ++mIterator;
                ++mIterator;
                mCurToken = ":)";
                return DslConstants.PARENTHESES_COLON_END_;
            }
            else if (CurChar == '<' && NextChar == ':') {
                ++mIterator;
                ++mIterator;
                if (CurChar == ':') {
                    if (NextChar == '>') {
                        mCurToken = "<:";
                        return DslConstants.ANGLE_BRACKET_COLON_BEGIN_;
                    }
                    else {
                        ++mIterator;
                        mTokenQueue.Enqueue(new TokenInfo { Token = "::", TokenValue = DslConstants.COLON_COLON_, LineNumber = mLineNumber });
                        mCurToken = "<";
                        return getOperatorTokenValue();
                    }
                }
                else {
                    mCurToken = "<:";
                    return DslConstants.ANGLE_BRACKET_COLON_BEGIN_;
                }
            }
            else if (CurChar == ':' && NextChar == '>') {
                ++mIterator;
                ++mIterator;
                mCurToken = ":>";
                return DslConstants.ANGLE_BRACKET_COLON_END_;
            }
            else if (CurChar == '{' && NextChar == '%') {
                ++mIterator;
                ++mIterator;
                mCurToken = "{%";
                return DslConstants.BRACE_PERCENT_BEGIN_;
            }
            else if (CurChar == '%' && NextChar == '}') {
                ++mIterator;
                ++mIterator;
                mCurToken = "%}";
                return DslConstants.BRACE_PERCENT_END_;
            }
            else if (CurChar == '[' && NextChar == '%') {
                ++mIterator;
                ++mIterator;
                mCurToken = "[%";
                return DslConstants.BRACKET_PERCENT_BEGIN_;
            }
            else if (CurChar == '%' && NextChar == ']') {
                ++mIterator;
                ++mIterator;
                mCurToken = "%]";
                return DslConstants.BRACKET_PERCENT_END_;
            }
            else if (CurChar == '(' && NextChar == '%') {
                ++mIterator;
                ++mIterator;
                mCurToken = "(%";
                return DslConstants.PARENTHESES_PERCENT_BEGIN_;
            }
            else if (CurChar == '%' && NextChar == ')') {
                ++mIterator;
                ++mIterator;
                mCurToken = "%)";
                return DslConstants.PARENTHESES_PERCENT_END_;
            }
            else if (CurChar == '<' && NextChar == '%') {
                ++mIterator;
                ++mIterator;
                mCurToken = "<%";
                return DslConstants.ANGLE_BRACKET_PERCENT_BEGIN_;
            }
            else if (CurChar == '%' && NextChar == '>') {
                ++mIterator;
                ++mIterator;
                mCurToken = "%>";
                return DslConstants.ANGLE_BRACKET_PERCENT_END_;
            }
            else if (CurChar == ':' && NextChar == ':') {
                ++mIterator;
                ++mIterator;
                mCurToken = "::";

                if (mLastToken.Length > 0 && isNotIdentifierAndNumberAndEndParentheses(mLastToken[mLastToken.Length - 1]) && mLastToken[mLastToken.Length - 1] != '?' && mLastToken[mLastToken.Length - 1] != '!' &&
                    (mLastToken.Length != 2 || (!(mLastToken[mLastToken.Length - 2] == ':' && mLastToken[mLastToken.Length - 1] == '>') && !(mLastToken[mLastToken.Length - 2] == '%' && mLastToken[mLastToken.Length - 1] == '>'))))
                    return getOperatorTokenValue();
                char nextChar = PeekNextValidChar(0);
                char nextChar2 = PeekNextValidChar(1);
                char nextChar3 = PeekNextValidChar(2);
                if (isNotIdentifierAndBeginParentheses(nextChar) && !(nextChar == '<' && nextChar2 == ':' && char.IsWhiteSpace(nextChar3)) && !(nextChar == '<' && nextChar2 == '%' && char.IsWhiteSpace(nextChar3))) {
                    return getOperatorTokenValue();
                }
                return DslConstants.COLON_COLON_;
            }
            else if (CurChar == '?' || CurChar == '!') {
                if (mLastToken.Length > 0 && isNotIdentifierAndNumberAndEndParentheses(mLastToken[mLastToken.Length - 1]) && mLastToken[mLastToken.Length - 1] != '?' && mLastToken[mLastToken.Length - 1] != '!' &&
                    (mLastToken.Length != 2 || (!(mLastToken[mLastToken.Length - 2] == ':' && mLastToken[mLastToken.Length - 1] == '>') && !(mLastToken[mLastToken.Length - 2] == '%' && mLastToken[mLastToken.Length - 1] == '>')))) {
                    getOperatorToken();
                    return getOperatorTokenValue();
                }
                else if (mNullableSyntaxEnabled) {
                    string tok = (CurChar == '?' ? "?" : "!");
                    if (NextChar == '.') {
                        ++mIterator;
                        mCurToken = tok;
                        return DslConstants.OP_TOKEN_NULLABLE_;
                    }
                    else if (NextChar == '-' && PeekChar(2) == '>') {
                        ++mIterator;
                        mCurToken = tok;
                        return DslConstants.OP_TOKEN_NULLABLE_;
                    }
                    else if (NextChar == '(') {
                        ++mIterator;
                        mCurToken = tok;
                        return DslConstants.OP_TOKEN_NULLABLE_;
                    }
                    else if (NextChar == '[') {
                        ++mIterator;
                        mCurToken = tok;
                        return DslConstants.OP_TOKEN_NULLABLE_;
                    }
                    else if (NextChar == '{') {
                        ++mIterator;
                        mCurToken = tok;
                        return DslConstants.OP_TOKEN_NULLABLE_;
                    }
                    else if (NextChar == '<' && (PeekChar(2) == ':' || PeekChar(2) == '%')) {
                        ++mIterator;
                        mCurToken = tok;
                        return DslConstants.OP_TOKEN_NULLABLE_;
                    }
                    else {
                        getOperatorToken();
                        return getOperatorTokenValue();
                    }
                }
                else {
                    getOperatorToken();
                    return getOperatorTokenValue();
                }
            }
            else if (CurChar == '-') {
                if (NextChar == '>') {
                    ++mIterator;
                    ++mIterator;
                    if (CurChar == '*') {
                        ++mIterator;
                        mCurToken = "->*";

                        if (mLastToken.Length > 0 && isNotIdentifierAndNumberAndEndParentheses(mLastToken[mLastToken.Length - 1]) && mLastToken[mLastToken.Length - 1] != '?' && mLastToken[mLastToken.Length - 1] != '!' &&
                            (mLastToken.Length != 2 || (!(mLastToken[mLastToken.Length - 2] == ':' && mLastToken[mLastToken.Length - 1] == '>') && !(mLastToken[mLastToken.Length - 2] == '%' && mLastToken[mLastToken.Length - 1] == '>'))))
                            return getOperatorTokenValue();
                        char nextChar = PeekNextValidChar(0);
                        char nextChar2 = PeekNextValidChar(1);
                        char nextChar3 = PeekNextValidChar(2);
                        if (isNotIdentifierAndBeginParentheses(nextChar) && !(nextChar == '<' && nextChar2 == ':' && char.IsWhiteSpace(nextChar3)) && !(nextChar == '<' && nextChar2 == '%' && char.IsWhiteSpace(nextChar3))) {
                            return getOperatorTokenValue();
                        }
                        return DslConstants.POINTER_STAR_;
                    }
                    else {
                        mCurToken = "->";

                        if (mLastToken.Length > 0 && isNotIdentifierAndNumberAndEndParentheses(mLastToken[mLastToken.Length - 1]) && mLastToken[mLastToken.Length - 1] != '?' && mLastToken[mLastToken.Length - 1] != '!' &&
                            (mLastToken.Length != 2 || (!(mLastToken[mLastToken.Length - 2] == ':' && mLastToken[mLastToken.Length - 1] == '>') && !(mLastToken[mLastToken.Length - 2] == '%' && mLastToken[mLastToken.Length - 1] == '>'))))
                            return getOperatorTokenValue();
                        char nextChar = PeekNextValidChar(0);
                        char nextChar2 = PeekNextValidChar(1);
                        char nextChar3 = PeekNextValidChar(2);
                        if (isNotIdentifierAndBeginParentheses(nextChar) && !(nextChar == '<' && nextChar2 == ':' && char.IsWhiteSpace(nextChar3)) && !(nextChar == '<' && nextChar2 == '%' && char.IsWhiteSpace(nextChar3))) {
                            return getOperatorTokenValue();
                        }
                        return DslConstants.POINTER_;
                    }
                }
                else {
                    getOperatorToken();
                    return getOperatorTokenValue();
                }
            }
            else if (CurChar == '.' && NextChar == '*') {
                ++mIterator;
                ++mIterator;
                mCurToken = ".*";

                if (mLastToken.Length > 0 && isNotIdentifierAndNumberAndEndParentheses(mLastToken[mLastToken.Length - 1]) && mLastToken[mLastToken.Length - 1] != '?' && mLastToken[mLastToken.Length - 1] != '!' &&
                    (mLastToken.Length != 2 || (!(mLastToken[mLastToken.Length - 2] == ':' && mLastToken[mLastToken.Length - 1] == '>') && !(mLastToken[mLastToken.Length - 2] == '%' && mLastToken[mLastToken.Length - 1] == '>'))))
                    return getOperatorTokenValue();
                char nextChar = PeekNextValidChar(0);
                char nextChar2 = PeekNextValidChar(1);
                char nextChar3 = PeekNextValidChar(2);
                if (isNotIdentifierAndBeginParentheses(nextChar) && !(nextChar == '<' && nextChar2 == ':' && char.IsWhiteSpace(nextChar3)) && !(nextChar == '<' && nextChar2 == '%' && char.IsWhiteSpace(nextChar3))) {
                    return getOperatorTokenValue();
                }
                return DslConstants.PERIOD_STAR_;
            }
            else if (CurChar == '.' && NextChar == '.') {
                ++mIterator;
                ++mIterator;
                if (CurChar == '.') {
                    ++mIterator;
                    mCurToken = "...";
                    return DslConstants.IDENTIFIER_;
                }
                else {
                    mCurToken = "..";
                    return getOperatorTokenValue();
                }
            }
            else if (mOperators.IndexOf(CurChar) >= 0) {
                getOperatorToken();
                return getOperatorTokenValue();
            }
            else if (CurChar == '.' && !myisdigit(NextChar, false)) {
                char c = CurChar;
                ++mIterator;

                mTokenBuilder.Append(c);
                mCurToken = mTokenBuilder.ToString();

                if (mLastToken.Length > 0 && isNotIdentifierAndNumberAndEndParentheses(mLastToken[mLastToken.Length - 1]) && mLastToken[mLastToken.Length - 1] != '?' && mLastToken[mLastToken.Length - 1] != '!' &&
                    (mLastToken.Length != 2 || (!(mLastToken[mLastToken.Length - 2] == ':' && mLastToken[mLastToken.Length - 1] == '>') && !(mLastToken[mLastToken.Length - 2] == '%' && mLastToken[mLastToken.Length - 1] == '>'))))
                    return getOperatorTokenValue();
                char nextChar = PeekNextValidChar(0);
                char nextChar2 = PeekNextValidChar(1);
                char nextChar3 = PeekNextValidChar(2);
                if (isNotIdentifierAndBeginParentheses(nextChar) && !(nextChar == '<' && nextChar2 == ':' && char.IsWhiteSpace(nextChar3)) && !(nextChar == '<' && nextChar2 == '%' && char.IsWhiteSpace(nextChar3))) {
                    return getOperatorTokenValue();
                }
                return DslConstants.DOT_;
            }
            else if (CurChar == '{') {
                ++mIterator;
                mCurToken = "{";
                return DslConstants.LBRACE_;
            }
            else if (CurChar == '}') {
                ++mIterator;
                mCurToken = "}";
                return DslConstants.RBRACE_;
            }
            else if (CurChar == '[') {
                ++mIterator;
                mCurToken = "[";
                return DslConstants.LBRACK_;
            }
            else if (CurChar == ']') {
                ++mIterator;
                mCurToken = "]";
                return DslConstants.RBRACK_;
            }
            else if (CurChar == '(') {
                ++mIterator;
                mCurToken = "(";
                return DslConstants.LPAREN_;
            }
            else if (CurChar == ')') {
                ++mIterator;
                mCurToken = ")";
                return DslConstants.RPAREN_;
            }
            else if (CurChar == ',') {
                ++mIterator;
                mCurToken = ",";
                return DslConstants.COMMA_;
            }
            else if (CurChar == ';') {
                ++mIterator;
                mCurToken = ";";
                return DslConstants.SEMI_;
            }
            else if ((CurChar == '@' && (NextChar == '"' || NextChar == '\'')) ||
                (CurChar == '@' && NextChar == '$' && (PeekChar(2) == '"' || PeekChar(2) == '\'')) ||
                (CurChar == '$' && NextChar == '@' && (PeekChar(2) == '"' || PeekChar(2) == '\''))) {
                bool isDollar = false;
                if ((CurChar == '@' && NextChar == '$') || (CurChar == '$' && NextChar == '@')) {
                    ++mIterator;
                    ++mIterator;
                    isDollar = true;
                }
                else {
                    ++mIterator;
                }
                int line = mLineNumber;
                char c = CurChar;
                for (++mIterator; CurChar != 0; ++mIterator) {
                    if (CurChar == '\n') ++mLineNumber;
                    if (CurChar == c) {
                        if (NextChar == c) {
                            mTokenBuilder.Append(CurChar);
                            ++mIterator;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        mTokenBuilder.Append(CurChar);
                    }
                }
                if (CurChar != 0) {
                    ++mIterator;
                }
                else {
                    mLog.Log("[error][line {0}]: String cannot be ended !\n", line);
                }
                mCurToken = mTokenBuilder.ToString();
                /*Ordinary strings keep the appearance of the source code without removing the leading and trailing blank lines.
                if (mCurToken.IndexOf('\n') >= 0) {
                    mCurToken = removeFirstAndLastEmptyLine(mCurToken);
                }
                */
                if (isDollar)
                    return DslConstants.DOLLAR_STRING_;
                else
                    return DslConstants.STRING_;
            }
            else {//keyword,identifier or constant
                if (CurChar == '"' || CurChar == '\'' || CurChar=='$' && (NextChar == '"' || NextChar == '\'')) {//Quoted name or keyword
                    bool isDollar = false;
                    if (CurChar == '$') {
                        ++mIterator;
                        isDollar = true;
                    }
                    int line = mLineNumber;
                    char c = CurChar;
                    for (++mIterator; CurChar != 0; ++mIterator) {
                        if (CurChar == '\n') ++mLineNumber;
                        if (CurChar == '\\') {
                            ++mIterator;
                            if (CurChar == 'n') {
                                mTokenBuilder.Append('\n');
                            }
                            else if (CurChar == 'r') {
                                mTokenBuilder.Append('\r');
                            }
                            else if (CurChar == 't') {
                                mTokenBuilder.Append('\t');
                            }
                            else if (CurChar == 'v') {
                                mTokenBuilder.Append('\v');
                            }
                            else if (CurChar == 'a') {
                                mTokenBuilder.Append('\a');
                            }
                            else if (CurChar == 'b') {
                                mTokenBuilder.Append('\b');
                            }
                            else if (CurChar == 'f') {
                                mTokenBuilder.Append('\f');
                            }
                            else if (CurChar == 'u' && myisdigit(NextChar, true) && myisdigit(PeekChar(2), true) && myisdigit(PeekChar(3), true)) {
                                ++mIterator;
                                //4 digits HEX
                                char h1 = CurChar;
                                ++mIterator;
                                char h2 = CurChar;
                                ++mIterator;
                                char h3 = CurChar;
                                ++mIterator;
                                char h4 = CurChar;
                                mTokenBuilder.Append((char)((mychar2int(h1) << 12) + (mychar2int(h2) << 8) + (mychar2int(h3) << 4) + mychar2int(h4)));
                            }
                            else if (CurChar == 'U' && myisdigit(NextChar, true) && myisdigit(PeekChar(2), true) && myisdigit(PeekChar(3), true)
                                && myisdigit(PeekChar(4), true) && myisdigit(PeekChar(5), true) && myisdigit(PeekChar(6), true) && myisdigit(PeekChar(7), true)) {
                                ++mIterator;
                                //8 digits HEX
                                char h1 = CurChar;
                                ++mIterator;
                                char h2 = CurChar;
                                ++mIterator;
                                char h3 = CurChar;
                                ++mIterator;
                                char h4 = CurChar;
                                ++mIterator;
                                char h5 = CurChar;
                                ++mIterator;
                                char h6 = CurChar;
                                ++mIterator;
                                char h7 = CurChar;
                                ++mIterator;
                                char h8 = CurChar;
                                mTokenBuilder.Append((char)((mychar2int(h5) << 12) + (mychar2int(h6) << 8) + (mychar2int(h7) << 4) + mychar2int(h8)));
                                mTokenBuilder.Append((char)((mychar2int(h1) << 12) + (mychar2int(h2) << 8) + (mychar2int(h3) << 4) + mychar2int(h4)));
                            }
                            else if (CurChar == 'x' && myisdigit(NextChar, true)) {
                                ++mIterator;
                                //1~2 digits HEX
                                char h1 = CurChar;
                                if (myisdigit(NextChar, true)) {
                                    ++mIterator;
                                    char h2 = CurChar;
                                    char nc = (char)((mychar2int(h1) << 4) + mychar2int(h2));
                                    mTokenBuilder.Append(nc);
                                }
                                else {
                                    char nc = (char)mychar2int(h1);
                                    mTokenBuilder.Append(nc);
                                }
                            }
                            else if (myisdigit(CurChar, false)) {
                                //1~3 digits OCT
                                char o1 = CurChar;
                                if (myisdigit(NextChar, false)) {
                                    ++mIterator;
                                    char o2 = CurChar;
                                    if (myisdigit(NextChar, false)) {
                                        ++mIterator;
                                        char o3 = CurChar;
                                        char nc = (char)((mychar2int(o1) << 6) + (mychar2int(o2) * 3) + mychar2int(o3));
                                        mTokenBuilder.Append(nc);
                                    }
                                    else {
                                        char nc = (char)((mychar2int(o1) << 3) + mychar2int(o2));
                                        mTokenBuilder.Append(nc);
                                    }
                                }
                                else {
                                    char nc = (char)mychar2int(o1);
                                    mTokenBuilder.Append(nc);
                                }
                            }
                            else {
                                mTokenBuilder.Append(CurChar);
                            }
                        }
                        else if (CurChar == c) {
                            if (NextChar == c) {
                                mTokenBuilder.Append(CurChar);
                                ++mIterator;
                            }
                            else {
                                break;
                            }
                        }
                        else {
                            mTokenBuilder.Append(CurChar);
                        }
                    }
                    if (CurChar != 0) {
                        ++mIterator;
                    }
                    else {
                        mLog.Log("[error][line {0}]: string can't end !\n", line);
                    }
                    mCurToken = mTokenBuilder.ToString();
                    /*Ordinary strings should maintain their appearance in the source code, without removing leading or trailing blank lines.
                    if (mCurToken.IndexOf('\n') >= 0) {
                        mCurToken = removeFirstAndLastEmptyLine(mCurToken);
                    }
                    */
                    if (isDollar)
                        return DslConstants.DOLLAR_STRING_;
                    else
                        return DslConstants.STRING_;
                }
                else {
                    bool isNum = true;
                    bool isHex = false;
                    bool includeEPart = false;
                    bool includeAddSub = false;
                    bool waitFinish = false;
                    int dotCt = 0;
                    if (CurChar == '0' && NextChar == 'x') {
                        isHex = true;
                        mTokenBuilder.Append(CurChar);
                        ++mIterator;
                        mTokenBuilder.Append(CurChar);
                        ++mIterator;
                    }
                    for (int charCt = 0; CurChar == '?' || CurChar == '\'' || isNum && myisdigit(CurChar, isHex, includeEPart, includeAddSub) || !isSpecialChar(CurChar); ++mIterator, ++charCt) {
                        if (CurChar == '#')
                            break;
                        else if (CurChar == '?') {
                            //In the case of a nullable type (with a question mark following the type name), only one question mark is allowed.
                            if (null != mOnTokenCanEatChar) {
                                if (mOnTokenCanEatChar(mTokenBuilder, CurChar)) {
                                    mTokenBuilder.Append(CurChar);
                                    ++mIterator;
                                    ++charCt;
                                }
                            }
                            break;
                        }
                        else if (CurChar == '\'') {
                            if (!isNum) {
                                break;
                            }
                            else {
                                if (NextChar != 0 && !myisdigit(NextChar, isHex, includeEPart, includeAddSub)) {
                                    break;
                                }
                                ++mIterator;
                                ++charCt;
                            }
                        }
                        else if (CurChar == '.') {
                            if (!isNum || isHex) {
                                break;
                            }
                            else {
                                if (NextChar == 'b' || NextChar == 'B' || NextChar == 'f' || NextChar == 'F' || NextChar == 'l' || NextChar == 'L') {
                                }
                                else if (NextChar != 0 && !myisdigit(NextChar, isHex, includeEPart, includeAddSub)) {
                                    char c = PeekNextValidChar(1);
                                    if (!isSpecialChar(c))
                                        break;
                                }
                            }
                            ++dotCt;
                            if (dotCt > 1)
                                break;
                        }
                        else if (isNum) {
                            if (dotCt > 0 && (CurChar == 'b' || CurChar == 'B' || CurChar == 'f' || CurChar == 'F' || CurChar == 'l' || CurChar == 'L')) {
                            }
                            else if (dotCt == 0 && charCt > 0 && (CurChar == 'l' || CurChar == 'L' || CurChar == 'u' || CurChar == 'U' || CurChar == 'z' || CurChar == 'Z')) {
                            }
                            else if (!myisdigit(CurChar, isHex, includeEPart, includeAddSub)) {
                                isNum = false;
                            }
                        }
                        if (isNum && !waitFinish) {
                            if (includeEPart && (!isHex && (CurChar == 'e' || CurChar == 'E')) || (isHex && (CurChar == 'p' || CurChar == 'P'))) {
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
                        mTokenBuilder.Append(CurChar);
                    }
                    mCurToken = mTokenBuilder.ToString();
                    if (isNum) {
                        return DslConstants.NUMBER_;
                    }
                    else {
                        return DslConstants.IDENTIFIER_;
                    }
                }
            }
        }
        internal short peek(int level) // scan next token without consuming it
        {
            short token = 0;
            mLog.Log("[info] peek_token is not called in an LL(1) grammar\n");
            return token;
        }

        public void setCurToken(string tok)
        {
            mCurToken = tok;
        }
        public void setLastToken(string tok)
        {
            mLastToken = tok;
        }
        public bool enqueueToken(string tok, short val, int line)
        {
            mTokenQueue.Enqueue(new TokenInfo { Token = tok, TokenValue = val, LineNumber = line });
            return true;
        }

        public string getCurToken()
        {
            return mCurToken;
        }
        public string getLastToken()
        {
            return mLastToken;
        }
        public int getLineNumber()
        {
            return mLineNumber;
        }
        public int getLastLineNumber()
        {
            return mLastLineNumber;
        }
        internal bool IsCommentOnNewLine()
        {
            return mCommentOnNewLine;
        }
        internal IList<string> GetComments()
        {
            return mComments;
        }
        internal void ResetComments()
        {
            mCommentOnNewLine = false;
            mComments.Clear();
        }
        internal void setStringDelimiter(string begin, string end)
        {
            mStringBeginDelimiter = begin;
            mStringEndDelimiter = end;
        }
        internal void setScriptDelimiter(string begin, string end)
        {
            mScriptBeginDelimiter = begin;
            mScriptEndDelimiter = end;
        }
        internal string StringBeginDelimiter
        {
            get { return mStringBeginDelimiter; }
        }
        internal string StringEndDelimiter
        {
            get { return mStringEndDelimiter; }
        }
        internal string ScriptBeginDelimiter
        {
            get { return mScriptBeginDelimiter; }
        }
        internal string ScriptEndDelimiter
        {
            get { return mScriptEndDelimiter; }
        }
        internal GetTokenDelegation OnGetToken
        {
            get { return mOnGetToken; }
            set { mOnGetToken = value; }
        }
        internal TokenCanEatCharDelegation OnTokenCanEatChar
        {
            get { return mOnTokenCanEatChar; }
            set { mOnTokenCanEatChar = value; }
        }

        private bool IsBegin(string delimiter)
        {
            bool ret = false;
            if (!string.IsNullOrEmpty(delimiter)) {
                int start = mIterator;
                if (start + delimiter.Length <= mInput.Length && start == mInput.IndexOf(delimiter, start, delimiter.Length))
                    ret = true;
            }
            return ret;
        }
        private string getBlockString(string delimiter)
        {
            int start = mIterator;
            int end = mInput.IndexOf(delimiter, start);
            if (end < 0) {
                mLog.Log("[error][line {0}]: block can't finish, delimiter: {1}！\n", mLineNumber, delimiter);
                return string.Empty;
            }
            mIterator = end + delimiter.Length;
            int lineStart = mInput.IndexOf('\n', start, end - start);
            while (lineStart >= 0) {
                ++mLineNumber;
                lineStart = mInput.IndexOf('\n', lineStart + 1, end - lineStart - 1);
            }
            return removeFirstAndLastEmptyLine(mInput.Substring(start, end - start));
        }
        private string removeFirstAndLastEmptyLine(string str)
        {
            int start = 0;
            while (start < str.Length && isWhiteSpace(str[start]) && str[start] != '\n')
                ++start;
            if (start < str.Length && str[start] == '\n') {
                ++start;
            }
            else {
                //If there is no newline at the beginning of the line, preserve the white space.
                start = 0;
            }
            int end = str.Length - 1;
            while (end > 0 && isWhiteSpace(str[end]) && str[end] != '\n')
                --end;
            if (end > 0 && str[end] != '\n') {
                //If there is no newline at the end of the line, preserve the white space; otherwise, remove the white space but keep the newline.
                end = str.Length - 1;
            }
            if (start > 0 || end < str.Length - 1) {
                return str.Substring(start, end - start + 1);
            }
            else {
                return str;
            }
        }

        public void getOperatorToken()
        {
            int st = mIterator;
            switch (CurChar) {
                case '+': {
                        ++mIterator;
                        if (CurChar == '+' || CurChar == '=') {
                            ++mIterator;
                        }
                    }
                    break;
                case '-': {
                        ++mIterator;
                        if (CurChar == '-' || CurChar == '=' || CurChar == '>') {
                            ++mIterator;
                        }
                    }
                    break;
                case '>': {
                        ++mIterator;
                        if (CurChar == '=') {
                            ++mIterator;
                        }
                        else if (CurChar == '>') {
                            ++mIterator;
                            if (CurChar == '>') {
                                ++mIterator;
                            }
                            if (CurChar == '=') {
                                ++mIterator;
                            }
                        }
                    }
                    break;
                case '<': {
                        ++mIterator;
                        if (CurChar == '=') {
                            ++mIterator;
                            if (CurChar == '>') {
                                ++mIterator;
                            }
                        }
                        else if (CurChar == '-') {
                            ++mIterator;
                        }
                        else if (CurChar == '<') {
                            ++mIterator;
                            if (CurChar == '=') {
                                ++mIterator;
                            }
                        }
                    }
                    break;
                case '&': {
                        ++mIterator;
                        if (CurChar == '=') {
                            ++mIterator;
                        }
                        else if (CurChar == '&') {
                            ++mIterator;
                            if (CurChar == '=') {
                                ++mIterator;
                            }
                        }
                    }
                    break;
                case '|': {
                        ++mIterator;
                        if (CurChar == '=') {
                            ++mIterator;
                        }
                        else if (CurChar == '|') {
                            ++mIterator;
                            if (CurChar == '=') {
                                ++mIterator;
                            }
                        }
                    }
                    break;
                case '=': {
                        ++mIterator;
                        if (CurChar == '=' || CurChar == '>') {
                            ++mIterator;
                        }
                    }
                    break;
                case '!':
                case '^':
                case '*':
                case '/':
                case '%': {
                        ++mIterator;
                        if (CurChar == '=') {
                            ++mIterator;
                        }
                    }
                    break;
                case '?': {
                        ++mIterator;
                        if (CurChar == '?') {
                            ++mIterator;
                            if (CurChar == '=') {
                                ++mIterator;
                            }
                        }
                    }
                    break;
                case '`': {
                        ++mIterator;
                        bool isOp = false;
                        while (isOperator(CurChar)) {
                            ++mIterator;
                            isOp = true;
                        }
                        if (!isOp) {
                            while (CurChar != '\0' && !isSpecialChar(CurChar)) {
                                if (CurChar == '#')
                                    break;
                                else if (CurChar == '.') {
                                    break;
                                }
                                ++mIterator;
                            }
                        }
                    }
                    break;
                default: {
                        ++mIterator;
                    }
                    break;
            }
            int ed = mIterator;
            mCurToken = mInput.Substring(st, ed - st);
        }
        public short getOperatorTokenValue()
        {
            string curOperator = mCurToken;
            string lastToken = mLastToken;
            bool lastIsOperator = true;
            if (null != lastToken && lastToken.Length > 0) {
                if (isDelimiter(lastToken[0])) {
                    lastIsOperator = true;
                }
                else if (isBeginParentheses(lastToken[0])) {
                    lastIsOperator = true;
                }
                else {
                    lastIsOperator = isOperator(lastToken[0]);
                }
            }
            short val = DslConstants.OP_TOKEN_2_;
            if (curOperator.Length > 0) {
                char c0 = curOperator[0];
                char c1 = (char)0;
                char c2 = (char)0;
                char c3 = (char)0;
                char c4 = (char)0;
                if (curOperator.Length > 1)
                    c1 = curOperator[1];
                if (curOperator.Length > 2)
                    c2 = curOperator[2];
                if (curOperator.Length > 3)
                    c3 = curOperator[3];
                if (curOperator.Length > 4)
                    c4 = curOperator[4];
                if (c0 == '=' && c1 == '\0' || c0 == '<' && c1 == '-' && c2 == '\0') {
                    val = DslConstants.OP_TOKEN_1_;
                }
                else if (c0 != '=' && c0 != '!' && c0 != '>' && c0 != '<' && c1 == '=' && c2 == '\0') {
                    val = DslConstants.OP_TOKEN_1_;
                }
                else if (c2 == '=' && c3 == '\0') {
                    val = DslConstants.OP_TOKEN_1_;
                }
                else if (c3 == '=' && c4 == '\0') {
                    val = DslConstants.OP_TOKEN_1_;
                }
                else if (c0 == '=' && c1 == '>' && c2 == '\0') {
                    val = DslConstants.OP_TOKEN_2_;
                }
                else if (c0 == ':' && c1 == '\0') {
                    if (mAction.PeekPairTypeStack() == PairTypeEnum.PAIR_TYPE_QUESTION_COLON)
                        val = DslConstants.OP_TOKEN_QUESTION_COLON_;
                    else
                        val = DslConstants.OP_TOKEN_COLON_;
                }
                else if (c0 == '?' && c1 == '\0') {
                    val = DslConstants.OP_TOKEN_QUESTION_;
                }
                else if (c0 == '|' && c1 == '|' && c2 == '\0' || c0 == '?' && c1 == '?' && c2 == '\0') {
                    val = DslConstants.OP_TOKEN_4_;
                }
                else if (c0 == '&' && c1 == '&' && c2 == '\0') {
                    val = DslConstants.OP_TOKEN_5_;
                }
                else if (c0 == '|' && c1 == '\0') {
                    val = DslConstants.OP_TOKEN_6_;
                }
                else if (c0 == '^' && c1 == '\0') {
                    val = DslConstants.OP_TOKEN_7_;
                }
                else if (c0 == '&' && c1 == '\0') {
                    if (lastIsOperator)
                        val = DslConstants.OP_TOKEN_14_;
                    else
                        val = DslConstants.OP_TOKEN_8_;
                }
                else if ((c0 == '=' || c0 == '!') && c1 == '=' && c2 == '\0' || c0 == '<' && c1 == '=' && c2 == '>' && c3 == '\0') {
                    val = DslConstants.OP_TOKEN_9_;
                }
                else if ((c0 == '<' || c0 == '>') && (c1 == '=' && c2 == '\0' || c1 == 0)) {
                    val = DslConstants.OP_TOKEN_10_;
                }
                else if ((c0 == '<' && c1 == '<' && c2 == '\0') || (c0 == '>' && c1 == '>' && c2 == '\0') || (c0 == '>' && c1 == '>' && c2 == '>' && c3 == '\0')) {
                    val = DslConstants.OP_TOKEN_11_;
                }
                else if ((c0 == '+' || c0 == '-') && c1 == '\0') {
                    if (lastIsOperator)
                        val = DslConstants.OP_TOKEN_14_;
                    else
                        val = DslConstants.OP_TOKEN_12_;
                }
                else if ((c0 == '*' || c0 == '/' || c0 == '%') && c1 == '\0' || c0 == '.' && c1 == '.' && c2 == '\0') {
                    if (c0 == '*' && lastIsOperator)
                        val = DslConstants.OP_TOKEN_14_;
                    else
                        val = DslConstants.OP_TOKEN_13_;
                }
                else if ((c0 == '+' && c1 == '+' && c2 == '\0') || (c0 == '-' && c1 == '-' && c2 == '\0') || (c0 == '~' && c1 == '\0') || (c0 == '!' && c1 == '\0')) {
                    val = DslConstants.OP_TOKEN_14_;
                }
                else if (c0 == '`' && c1 == '\0') {
                    val = DslConstants.OP_TOKEN_0_;
                }
                else if (c0 == '`' && c1 != '\0') {
                    val = DslConstants.OP_TOKEN_3_;
                }
                else if (c0 == '-' && c1 == '>' && (c2 == '\0' || c2 == '*' && c3 == '\0') ||
                    c0 == '.' && (c1 == '\0' || c1 == '*' && c2 == '\0') ||
                    (c0 == ':' && c1 == ':' && c2 == '\0')
                    ) {
                    mLog.Log("[warning][line {0}]: Member access operation '{1}' should not appear in operators", mLineNumber, mCurToken);
                    val = DslConstants.OP_TOKEN_15_;
                }
                else {
                    val = DslConstants.OP_TOKEN_3_;
                }
            }
            return val;
        }
        public bool isNotIdentifier(char c)
        {
            if (0 == c)
                return false;
            else
                return !char.IsLetter(c) && c != '_' && c != '@' && c != '$';
        }
        public bool isNotIdentifierAndBeginParentheses(char c)
        {
            if (0 == c)
                return false;
            else
                return mBeginParentheses.IndexOf(c) < 0 && !char.IsLetter(c) && c != '_' && c != '@' && c != '$';
        }
        public bool isNotIdentifierAndNumberAndEndParentheses(char c)
        {
            if (0 == c)
                return false;
            else
                return mEndParentheses.IndexOf(c) < 0 && !char.IsLetterOrDigit(c) && c != '_' && c != '@' && c != '$';
        }
        public bool isWhiteSpace(char c)
        {
            if (0 == c)
                return false;
            else
                return mWhiteSpaces.IndexOf(c) >= 0;
        }
        public bool isDelimiter(char c)
        {
            if (0 == c)
                return false;
            else
                return mDelimiters.IndexOf(c) >= 0;
        }
        public bool isBeginParentheses(char c)
        {
            if (0 == c)
                return false;
            else
                return mBeginParentheses.IndexOf(c) >= 0;
        }
        public bool isEndParentheses(char c)
        {
            if (0 == c)
                return false;
            else
                return mEndParentheses.IndexOf(c) >= 0;
        }
        public bool isOperator(char c)
        {
            if (0 == c)
                return false;
            else
                return mOperators.IndexOf(c) >= 0;
        }
        public bool isQuote(char c)
        {
            if (0 == c)
                return false;
            else
                return mQuotes.IndexOf(c) >= 0;
        }
        public bool isSpecialChar(char c)
        {
            if (0 == c)
                return true;
            else
                return mSpecialChars.IndexOf(c) >= 0;
        }

        public char CurChar
        {
            get {
                return PeekChar(0);
            }
        }
        public char NextChar
        {
            get {
                return PeekChar(1);
            }
        }
        public char PeekChar(int ix)
        {
            char c = (char)0;
            if (ix >= 0 && mIterator + ix < mInput.Length)
                c = mInput[mIterator + ix];
            return c;
        }
        public char PeekNextValidChar(int beginIndex)
        {
            int _;
            return PeekNextValidChar(beginIndex, out _);
        }
        public char PeekNextValidChar(int beginIndex, out int index)
        {
            char nextChar = '\0';
            index = -1;
            for (int start = mIterator + beginIndex; start < mInput.Length; ++start) {
                if (mWhiteSpaces.IndexOf(mInput[start]) >= 0) {
                    continue;
                }
                else {
                    nextChar = mInput[start];
                    index = start - mIterator;
                    break;
                }
            }
            return nextChar;
        }

        public static bool myisdigit(char c, bool isHex)
        {
            return myisdigit(c, isHex, false, false);
        }
        public static bool myisdigit(char c, bool isHex, bool includeEPart, bool includeAddSub)
        {
            bool ret = false;
            if (isHex) {
                if (includeEPart && (c == 'P' || c == 'p'))
                    ret = true;
                else if (includeAddSub && (c == '+' || c == '-'))
                    ret = true;
                else if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
                    ret = true;
                else
                    ret = false;
            }
            else {
                if (includeEPart && (c == 'E' || c == 'e'))
                    ret = true;
                else if (includeAddSub && (c == '+' || c == '-'))
                    ret = true;
                else if ((c >= '0' && c <= '9'))
                    ret = true;
                else
                    ret = false;
            }
            return ret;
        }
        public static int mychar2int(char c)
        {
            if (c >= '0' && c <= '9')
                return c - '0';
            else if (c >= 'a' && c <= 'f')
                return 10 + c - 'a';
            else if (c >= 'A' && c <= 'F')
                return 10 + c - 'A';
            else
                return 0;
        }

        private struct TokenInfo
        {
            internal string Token;
            internal short TokenValue;
            internal int LineNumber;
        }

        private DslAction mAction;
        private DslLog mLog;
        private string mInput;
        private int mIterator;
        private string mCurToken;
        private string mLastToken;

        private int mLineNumber;
        private int mLastLineNumber;

        private StringBuilder mCommentBuilder;
        private List<string> mComments;
        private bool mCommentOnNewLine;

        private const string mWhiteSpaces = " \t\r\n";
        private const string mDelimiters = ",;";
        private const string mBeginParentheses = "{([";
        private const string mEndParentheses = "})]";
        private const string mOperators = "~`!%^&*-+=|:<>?/";
        private const string mQuotes = "'\"";
        private const string mSpecialChars = mWhiteSpaces + mDelimiters + mBeginParentheses + mEndParentheses + mOperators + mQuotes;

        private StringBuilder mTokenBuilder;
        private Queue<TokenInfo> mTokenQueue;

        private bool mNullableSyntaxEnabled;
        private string mStringBeginDelimiter;
        private string mStringEndDelimiter;
        private string mScriptBeginDelimiter;
        private string mScriptEndDelimiter;
        private GetTokenDelegation mOnGetToken;
        private TokenCanEatCharDelegation mOnTokenCanEatChar;
    }
}
