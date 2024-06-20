/*****************************************************************************

SlkToken.cpp

******************************************************************************/
#include "SlkParse.h"
#include "tsnprintf.h"

using namespace DslParser;

//mIterator and mErrorInfo are passed in by the reference parameters of the constructor and will not be empty.
//So it no longer checks whether it is empty when using it.
static inline int myisdigit(char c, int isHex, int includeEPart, int includeAddSub)
{
    int ret = FALSE;
    if (TRUE == isHex) {
        if (TRUE == includeEPart && (c == 'P' || c == 'p'))
            ret = TRUE;
        else if (TRUE == includeAddSub && (c == '+' || c == '-'))
            ret = TRUE;
        else if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
            ret = TRUE;
        else
            ret = FALSE;
    }
    else {
        if (TRUE == includeEPart && (c == 'E' || c == 'e'))
            ret = TRUE;
        else if (TRUE == includeAddSub && (c == '+' || c == '-'))
            ret = TRUE;
        else if ((c >= '0' && c <= '9'))
            ret = TRUE;
        else
            ret = FALSE;
    }
    return ret;
}
static inline int myisdigit(char c, int isHex)
{
    return myisdigit(c, isHex, FALSE, FALSE);
}
static inline int mychar2int(char c)
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

int DslTokenApi::myisdigit(char c, int isHex, int includeEPart, int includeAddSub)
{
    return ::myisdigit(c, isHex, includeEPart, includeAddSub);
}
int DslTokenApi::myisdigit(char c, int isHex)
{
    return ::myisdigit(c, isHex);
}
int DslTokenApi::mychar2int(char c)
{
    return ::mychar2int(c);
}

char SlkToken::curChar()const
{
    return peekChar(0);
}

char SlkToken::nextChar()const
{
    return peekChar(1);
}

char SlkToken::peekChar(int ix)const
{
    char c = 0;
    if (ix >= 0)
        c = *(mIterator + ix);
    return c;
}

char SlkToken::peekNextValidChar(int beginIx)const
{
    int _;
    return peekNextValidChar(beginIx, _);
}
char SlkToken::peekNextValidChar(int beginIx, int& index)const
{
    char nc = '\0';
    index = -1;
    for (int start = beginIx; ; ++start) {
        char c = *(mIterator + start);
        if (c == '\0') {
            break;
        }
        else if (isWhiteSpace(c)) {
            continue;
        }
        else {
            nc = c;
            index = start;
            break;
        }
    }
    return nc;
}

void SlkToken::getOperatorToken()
{
    switch (curChar()) {
    case '+':
    {
        pushTokenChar(curChar());
        ++mIterator;
        if (curChar() == '+' || curChar() == '=') {
            pushTokenChar(curChar());
            ++mIterator;
        }
    }
    break;
    case '-':
    {
        pushTokenChar(curChar());
        ++mIterator;
        if (curChar() == '-' || curChar() == '=' || curChar() == '>') {
            pushTokenChar(curChar());
            ++mIterator;
        }
    }
    break;
    case '>':
    {
        pushTokenChar(curChar());
        ++mIterator;
        if (curChar() == '=') {
            pushTokenChar(curChar());
            ++mIterator;
        }
        else if (curChar() == '>') {
            pushTokenChar(curChar());
            ++mIterator;
            if (curChar() == '>') {
                pushTokenChar(curChar());
                ++mIterator;
            }
            if (curChar() == '=') {
                pushTokenChar(curChar());
                ++mIterator;
            }
        }
    }
    break;
    case '<':
    {
        pushTokenChar(curChar());
        ++mIterator;
        if (curChar() == '=') {
            pushTokenChar(curChar());
            ++mIterator;
            if (curChar() == '>') {
                pushTokenChar(curChar());
                ++mIterator;
            }
        }
        else if (curChar() == '-') {
            pushTokenChar(curChar());
            ++mIterator;
        }
        else if (curChar() == '<') {
            pushTokenChar(curChar());
            ++mIterator;
            if (curChar() == '=') {
                pushTokenChar(curChar());
                ++mIterator;
            }
        }
    }
    break;
    case '&':
    {
        pushTokenChar(curChar());
        ++mIterator;
        if (curChar() == '=') {
            pushTokenChar(curChar());
            ++mIterator;
        }
        else if (curChar() == '&') {
            pushTokenChar(curChar());
            ++mIterator;
            if (curChar() == '=') {
                pushTokenChar(curChar());
                ++mIterator;
            }
        }
    }
    break;
    case '|':
    {
        pushTokenChar(curChar());
        ++mIterator;
        if (curChar() == '=') {
            pushTokenChar(curChar());
            ++mIterator;
        }
        else if (curChar() == '|') {
            pushTokenChar(curChar());
            ++mIterator;
            if (curChar() == '=') {
                pushTokenChar(curChar());
                ++mIterator;
            }
        }
    }
    break;
    case '=':
    {
        pushTokenChar(curChar());
        ++mIterator;
        if (curChar() == '=' || curChar() == '>') {
            pushTokenChar(curChar());
            ++mIterator;
        }
    }
    break;
    case '!':
    case '^':
    case '*':
    case '/':
    case '%':
    {
        pushTokenChar(curChar());
        ++mIterator;
        if (curChar() == '=') {
            pushTokenChar(curChar());
            ++mIterator;
        }
    }
    break;
    case '?':
        pushTokenChar(curChar());
        ++mIterator;
        if (curChar() == '?') {
            pushTokenChar(curChar());
            ++mIterator;
            if (curChar() == '=') {
                pushTokenChar(curChar());
                ++mIterator;
            }
        }
        break;
    case '`': {
        pushTokenChar(curChar());
        ++mIterator;
        bool isOp = false;
        while (isOperator(curChar())) {
            pushTokenChar(curChar());
            ++mIterator;
            isOp = true;
        }
        if (!isOp) {
            while (curChar() != '\0' && !isSpecialChar(curChar())) {
                if (curChar() == '#')
                    break;
                else if (curChar() == '.') {
                    break;
                }
                pushTokenChar(curChar());
                ++mIterator;
            }
        }
    }break;
    default:
    {
        pushTokenChar(curChar());
        ++mIterator;
    }
    break;
    }
    endToken();
}

short SlkToken::getOperatorTokenValue()const
{
    const char* pOperator = mCurToken;
    const char* pLastToken = mLastToken;
    int lastIsOperator = TRUE;
    if (pLastToken && pLastToken[0]) {
        if (isDelimiter(pLastToken[0])) {
            lastIsOperator = TRUE;
        }
        else if (isBeginParentheses(pLastToken[0])) {
            lastIsOperator = TRUE;
        }
        else {
            lastIsOperator = isOperator(pLastToken[0]);
        }
    }
    short val = OP_TOKEN_2_;
    if (pOperator && pOperator[0]) {
        if (pOperator[0] == '=' && pOperator[1] == '\0') {
            val = OP_TOKEN_0_;
        }
        else if (pOperator[0] != '=' && pOperator[0] != '!' && pOperator[0] != '>' && pOperator[0] != '<' && pOperator[1] == '=' && pOperator[2] == '\0') {
            val = OP_TOKEN_0_;
        }
        else if (pOperator[1] && pOperator[2] == '=' && pOperator[3] == '\0') {
            val = OP_TOKEN_0_;
        }
        else if (pOperator[1] && pOperator[2] && pOperator[3] == '=' && pOperator[4] == '\0') {
            val = OP_TOKEN_0_;
        }
        else if ((pOperator[0] == '=' && pOperator[1] == '>' && pOperator[2] == '\0') || (pOperator[0] == '<' && pOperator[1] == '-' && pOperator[2] == '\0')) {
            val = OP_TOKEN_1_;
        }
        else if (pOperator[0] == ':' && pOperator[1] == '\0') {
            val = OP_TOKEN_COLON_;
        }
        else if (pOperator[0] == '?' && pOperator[1] == '\0') {
            val = OP_TOKEN_QUESTION_;
        }
        else if ((pOperator[0] == '|' && pOperator[1] == '|' && pOperator[2] == '\0') || (pOperator[0] == '?' && pOperator[1] == '?' && pOperator[2] == '\0')) {
            val = OP_TOKEN_3_;
        }
        else if (pOperator[0] == '&' && pOperator[1] == '&' && pOperator[2] == '\0') {
            val = OP_TOKEN_4_;
        }
        else if (pOperator[0] == '|' && pOperator[1] == '\0') {
            val = OP_TOKEN_5_;
        }
        else if (pOperator[0] == '^' && pOperator[1] == '\0') {
            val = OP_TOKEN_6_;
        }
        else if (pOperator[0] == '&' && pOperator[1] == '\0') {
            if (lastIsOperator)
                val = OP_TOKEN_14_;
            else
                val = OP_TOKEN_7_;
        }
        else if (((pOperator[0] == '=' || pOperator[0] == '!') && pOperator[1] == '=' && pOperator[2] == '\0') || (pOperator[0] == '<' && pOperator[1] == '=' && pOperator[2] == '>' && pOperator[3] == '\0')) {
            val = OP_TOKEN_8_;
        }
        else if ((pOperator[0] == '<' || pOperator[0] == '>') && ((pOperator[1] == '=' && pOperator[2] == '\0') || pOperator[1] == '\0')) {
            val = OP_TOKEN_9_;
        }
        else if ((pOperator[0] == '<' && pOperator[1] == '<' && pOperator[2] == '\0') || (pOperator[0] == '>' && pOperator[1] == '>' && pOperator[2] == '\0') || (pOperator[0] == '>' && pOperator[1] == '>' && pOperator[2] == '>' && pOperator[3] == '\0')) {
            val = OP_TOKEN_10_;
        }
        else if ((pOperator[0] == '+' || pOperator[0] == '-') && pOperator[1] == '\0') {
            if (lastIsOperator)
                val = OP_TOKEN_13_;
            else
                val = OP_TOKEN_11_;
        }
        else if ((pOperator[0] == '*' || pOperator[0] == '/' || pOperator[0] == '%') && pOperator[1] == '\0') {
            if (pOperator[0] == '*' && lastIsOperator)
                val = OP_TOKEN_14_;
            else
                val = OP_TOKEN_12_;
        }
        else if ((pOperator[0] == '+' && pOperator[1] == '+' && pOperator[2] == '\0') || (pOperator[0] == '-' && pOperator[1] == '-' && pOperator[2] == '\0') || (pOperator[0] == '~' && pOperator[1] == '\0') || (pOperator[0] == '!' && pOperator[1] == '\0')) {
            val = OP_TOKEN_13_;
        }
        else if (pOperator[0] == '`') {
            val = OP_TOKEN_1_;
        }
        else if ((pOperator[0] == '-' && pOperator[1] == '>' && (pOperator[2] == '\0' || (pOperator[2] == '*' && pOperator[3] == '\0')))
            || (pOperator[0] == '.' && (pOperator[1] == '\0' || (pOperator[1] == '*' && pOperator[2] == '\0')))
            || (pOperator[0] == ':' && pOperator[1] == ':' && pOperator[2] == '\0')) {
            val = OP_TOKEN_15_;
        }
        else {
            val = OP_TOKEN_2_;
        }
    }
    return val;
}

int SlkToken::isNotIdentifier(char c)const
{
    if (0 == c)
        return FALSE;
    else
        return (!::isalpha(c) && c != '_' && c != '@' && c != '$') ? TRUE : FALSE;
}

int SlkToken::isNotIdentifierAndBeginParenthesis(char c)const
{
    if (0 == c)
        return FALSE;
    else
        return (0 == strchr(mBeginParentheses, c) && !::isalpha(c) && c != '_' && c != '@' && c != '$') ? TRUE : FALSE;
}

int SlkToken::isNotIdentifierAndNumberAndEndParenthesis(char c)const
{
    if (0 == c)
        return FALSE;
    else
        return (0 == strchr(mEndParentheses, c) && !::isalnum(c) && c != '_' && c != '@' && c != '$') ? TRUE : FALSE;
}

int SlkToken::isWhiteSpace(char c) const
{
    if (0 == c)
        return FALSE;
    else
        return (0 != strchr(mWhiteSpaces, c) ? TRUE : FALSE);
}

int SlkToken::isOperator(char c) const
{
    if (0 == c)
        return FALSE;
    else
        return (0 != strchr(mOperators, c) ? TRUE : FALSE);
}

int SlkToken::isQuote(char c) const
{
    if (0 == c)
        return FALSE;
    else
        return (0 != strchr(mQuotes, c) ? TRUE : FALSE);
}

int SlkToken::isDelimiter(char c) const
{
    if (0 == c)
        return FALSE;
    else
        return (0 != strchr(mDelimiters, c) ? TRUE : FALSE);
}

int SlkToken::isBeginParentheses(char c) const
{
    if (0 == c)
        return FALSE;
    else
        return (0 != strchr(mBeginParentheses, c) ? TRUE : FALSE);
}

int SlkToken::isEndParentheses(char c) const
{
    if (0 == c)
        return FALSE;
    else
        return (0 != strchr(mEndParentheses, c) ? TRUE : FALSE);
}

int SlkToken::isSpecialChar(char c) const
{
    if (0 == c)
        return TRUE;
    else
        return (0 != strchr(mSpecialChars, c) ? TRUE : FALSE);
}

short SlkToken::get()
{
    short tok = getImpl();
    if (!mDslFile->OnGetToken.isNull()) {
        mDslFile->OnGetToken(*mDslActionApi, DslTokenApi(this), mCurToken, tok, mLineNumber);
    }
    return tok;
}

short SlkToken::getImpl()
{
    if (nullptr == mSource || nullptr == mDslFile) {
        return END_OF_SLK_INPUT_;
    }

    mLastToken = mCurToken;
    mLastLineNumber = mLineNumber;
    if (mTokenQueue.Size() > 0) {
        auto token = mTokenQueue.PopFront();
        mCurToken = token.Token;
        mLineNumber = token.LineNumber;
        return token.TokenValue;
    }

    for (;;) {
        if (curChar() == '\0') {
            if (isCanFinish()) {
                newToken();
                endTokenWithEof();
                return END_OF_SLK_INPUT_;
            }
            else {
                if (!mIterator.Load()) {
                    newToken();
                    endTokenWithEof();
                    return END_OF_SLK_INPUT_;
                }
            }
        }

        int isSkip = TRUE;
        //Skip comments and white spaces
        for (; isSkip && curChar() != '\0';) {
            isSkip = FALSE;
            for (; isWhiteSpace(curChar()); ++mIterator) {
                if (curChar() == '\n') {
                    ++mLineNumber;
                    if (mCommentNum <= 0) {
                        mCommentOnNewLine = TRUE;
                    }
                }
                isSkip = TRUE;
            }
            //# Guided single-line comments and C++-style single-line comments
            if (curChar() == '#' || (curChar() == '/' && nextChar() == '/')) {
                newComment();
                for (; curChar() != '\0' && curChar() != '\n'; ++mIterator) {
                    if (curChar() != '\r')
                        pushCommentChar(curChar());
                }
                endComment();
                isSkip = TRUE;
            }
            //C++ style single-line comments and multi-line comments
            if (curChar() == '/' && nextChar() == '*') {
                newComment();
                pushCommentChar(curChar());
                ++mIterator;
                pushCommentChar(curChar());
                ++mIterator;
                for (;;) {
                    if (curChar() != '\0') {
                        if (curChar() == '\n') {
                            pushCommentChar(curChar());
                            ++mLineNumber;
                        }
                        else if (curChar() == '*' && nextChar() == '/') {
                            pushCommentChar(curChar());
                            ++mIterator;
                            pushCommentChar(curChar());
                            ++mIterator;
                            break;
                        }
                        else if (curChar() != '\r') {
                            pushCommentChar(curChar());
                        }
                    }
                    else {
                        if (mIterator.Load()) {
                            continue;
                        }
                        else {
                            endComment();
                            newToken();
                            endTokenWithEof();
                            return END_OF_SLK_INPUT_;
                        }
                    }
                    ++mIterator;
                }
                isSkip = TRUE;
                endComment();
            }
        }
        if (curChar() != '\0')
            break;
    }

    newToken();
    if (isCanFinish())
        setCanFinish(FALSE);

    if (mStringBeginDelimiter[0] && mStringEndDelimiter[0] && isBegin(mStringBeginDelimiter, mStringBeginDelimiterLength)) {
        mIterator = mIterator + mStringBeginDelimiterLength;
        getBlockString(mStringEndDelimiter, mStringEndDelimiterLength);
        return STRING_;
    }
    else if (mScriptBeginDelimiter[0] && mScriptEndDelimiter[0] && isBegin(mScriptBeginDelimiter, mScriptBeginDelimiterLength)) {
        mIterator = mIterator + mScriptBeginDelimiterLength;
        getBlockString(mScriptEndDelimiter, mScriptEndDelimiterLength);
        return SCRIPT_CONTENT_;
    }
    else if (curChar() == '{' && nextChar() == ':') {
        ++mIterator;
        ++mIterator;
        int line = mLineNumber;
        //End of search script ':}'
        for (; curChar() != '\0';) {
            while (curChar() != '\0' && curChar() != ':') {
                if (curChar() == '\n')++mLineNumber;

                pushTokenChar(curChar());

                ++mIterator;
            }
            if (curChar() == '\0')
                break;
            IScriptSource::Iterator next = mIterator + 1;
            if (*next == '}') {
                ++mIterator;
                ++mIterator;
                break;
            }
            else {
                pushTokenChar(curChar());

                ++mIterator;
            }
        }
        if (curChar() == '\0') {
            char* pInfo = mDslFile->NewErrorInfo();
            if (pInfo)
                tsnprintf(pInfo, mDslFile->GetSingleErrorInfoCapacity(), "[line %d ]:ExternScript can't finish！", line);
        }
        endToken();
        removeFirstAndLastEmptyLine();
        return SCRIPT_CONTENT_;
    }
    else if (curChar() == '[' && nextChar() == ':') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('[');
        pushTokenChar(':');
        endToken();
        return BRACKET_COLON_BEGIN_;
    }
    else if (curChar() == ':' && nextChar() == ']') {
        ++mIterator;
        ++mIterator;
        pushTokenChar(':');
        pushTokenChar(']');
        endToken();
        return BRACKET_COLON_END_;
    }
    else if (curChar() == '(' && nextChar() == ':') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('(');
        pushTokenChar(':');
        endToken();
        return PARENTHESIS_COLON_BEGIN_;
    }
    else if (curChar() == ':' && nextChar() == ')') {
        ++mIterator;
        ++mIterator;
        pushTokenChar(':');
        pushTokenChar(')');
        endToken();
        return PARENTHESIS_COLON_END_;
    }
    else if (curChar() == '<' && nextChar() == ':') {
        ++mIterator;
        ++mIterator;
        if (curChar() == ':') {
            if (nextChar() == '>') {
                pushTokenChar('<');
                pushTokenChar(':');
                endToken();
                return ANGLE_BRACKET_COLON_BEGIN_;
            }
            else {
                ++mIterator;
                endToken();
                char* curToken = mCurToken;
                newToken();
                pushTokenChar(':');
                pushTokenChar(':');
                endToken();
                mTokenQueue.PushBack(TokenInfo(mCurToken, COLON_COLON_, mLineNumber));
                mCurToken = curToken;
                return getOperatorTokenValue();
            }
        }
        else {
            pushTokenChar('<');
            pushTokenChar(':');
            endToken();
            return ANGLE_BRACKET_COLON_BEGIN_;
        }
    }
    else if (curChar() == ':' && nextChar() == '>') {
        ++mIterator;
        ++mIterator;
        pushTokenChar(':');
        pushTokenChar('>');
        endToken();
        return ANGLE_BRACKET_COLON_END_;
    }
    else if (curChar() == '{' && nextChar() == '%') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('{');
        pushTokenChar('%');
        endToken();
        return BRACE_PERCENT_BEGIN_;
    }
    else if (curChar() == '%' && nextChar() == '}') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('%');
        pushTokenChar('}');
        endToken();
        return BRACE_PERCENT_END_;
    }
    else if (curChar() == '[' && nextChar() == '%') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('[');
        pushTokenChar('%');
        endToken();
        return BRACKET_PERCENT_BEGIN_;
    }
    else if (curChar() == '%' && nextChar() == ']') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('%');
        pushTokenChar(']');
        endToken();
        return BRACKET_PERCENT_END_;
    }
    else if (curChar() == '(' && nextChar() == '%') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('(');
        pushTokenChar('%');
        endToken();
        return PARENTHESIS_PERCENT_BEGIN_;
    }
    else if (curChar() == '%' && nextChar() == ')') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('%');
        pushTokenChar(')');
        endToken();
        return PARENTHESIS_PERCENT_END_;
    }
    else if (curChar() == '<' && nextChar() == '%') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('<');
        pushTokenChar('%');
        endToken();
        return ANGLE_BRACKET_PERCENT_BEGIN_;
    }
    else if (curChar() == '%' && nextChar() == '>') {
        ++mIterator;
        ++mIterator;
        pushTokenChar('%');
        pushTokenChar('>');
        endToken();
        return ANGLE_BRACKET_PERCENT_END_;
    }
    else if (curChar() == ':' && nextChar() == ':') {
        ++mIterator;
        ++mIterator;
        pushTokenChar(':');
        pushTokenChar(':');
        endToken();

        if (mLastToken && isNotIdentifierAndNumberAndEndParenthesis(mLastToken[0]))
            return getOperatorTokenValue();
        char nextChar = peekNextValidChar(0);
        if (isNotIdentifierAndBeginParenthesis(nextChar)) {
            return getOperatorTokenValue();
        }
        return COLON_COLON_;
    }
    else if (curChar() == '?' || curChar() == '!') {
        char nc = nextChar();
        if (mLastToken && isNotIdentifierAndNumberAndEndParenthesis(mLastToken[0])) {
            getOperatorToken();
            return getOperatorTokenValue();
        }
        else if (mNullableSyntaxEnabled) {
            if (nc == '.') {
                ++mIterator;
                pushTokenChar('?');
                endToken();
                return OP_TOKEN_NULLABLE_;
            }
            else if (nc == '-' && peekChar(2) == '>') {
                ++mIterator;
                pushTokenChar('?');
                endToken();
                return OP_TOKEN_NULLABLE_;
            }
            else if (nc == '(') {
                ++mIterator;
                pushTokenChar('?');
                endToken();
                return OP_TOKEN_NULLABLE_;
            }
            else if (nc == '[') {
                ++mIterator;
                pushTokenChar('?');
                endToken();
                return OP_TOKEN_NULLABLE_;
            }
            else if (nc == '{') {
                ++mIterator;
                pushTokenChar('?');
                endToken();
                return OP_TOKEN_NULLABLE_;
            }
            else if (nc == '<' && (peekChar(2) == ':' || peekChar(2) == '%')) {
                ++mIterator;
                pushTokenChar('?');
                endToken();
                return OP_TOKEN_NULLABLE_;
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
    else if (curChar() == '-') {
        char nc = nextChar();
        if (nc == '>') {
            ++mIterator;
            ++mIterator;
            if (curChar() == '*') {
                ++mIterator;
                pushTokenChar('-');
                pushTokenChar('>');
                pushTokenChar('*');
                endToken();

                if (mLastToken && isNotIdentifierAndNumberAndEndParenthesis(mLastToken[0]))
                    return getOperatorTokenValue();
                char nextChar = peekNextValidChar(0);
                if (isNotIdentifier(nextChar)) {
                    return getOperatorTokenValue();
                }
                return POINTER_STAR_;
            }
            else {
                pushTokenChar('-');
                pushTokenChar('>');
                endToken();

                if (mLastToken && isNotIdentifierAndNumberAndEndParenthesis(mLastToken[0]))
                    return getOperatorTokenValue();
                char nextChar = peekNextValidChar(0);
                if (isNotIdentifier(nextChar)) {
                    return getOperatorTokenValue();
                }
                return POINTER_;
            }
        }
        else {
            getOperatorToken();
            return getOperatorTokenValue();
        }
    }
    else if (curChar() == '.' && nextChar() == '.') {
        char c = curChar();
        ++mIterator;
        ++mIterator;
        pushTokenChar(c);
        pushTokenChar(c);
        if (curChar() == '.') {
            ++mIterator;
            pushTokenChar(c);
            endToken();
            return IDENTIFIER_;
        }
        else {
            endToken();
            return getOperatorTokenValue();
        }
    }
    else if (isOperator(curChar())) {//operator
        getOperatorToken();
        return getOperatorTokenValue();
    }
    else if (curChar() == '.' && 0 == myisdigit(nextChar(), FALSE)) {
        if (nextChar() == '*') {
            ++mIterator;
            ++mIterator;
            pushTokenChar('.');
            pushTokenChar('*');
            endToken();

            if (mLastToken && isNotIdentifierAndNumberAndEndParenthesis(mLastToken[0]))
                return getOperatorTokenValue();
            char nextChar = peekNextValidChar(0);
            if (isNotIdentifier(nextChar)) {
                return getOperatorTokenValue();
            }
            return PERIOD_STAR_;
        }
        else {
            char c = curChar();
            ++mIterator;

            pushTokenChar(c);
            endToken();

            if (mLastToken && isNotIdentifierAndNumberAndEndParenthesis(mLastToken[0]))
                return getOperatorTokenValue();
            char nextChar = peekNextValidChar(0);
            if (isNotIdentifierAndBeginParenthesis(nextChar)) {
                return getOperatorTokenValue();
            }
            return DOT_;
        }
    }
    else if (curChar() == '(') {
        ++mIterator;
        pushTokenChar('(');
        endToken();
        return LPAREN_;
    }
    else if (curChar() == ')') {
        ++mIterator;
        pushTokenChar(')');
        endToken();
        return RPAREN_;
    }
    else if (curChar() == '[') {
        ++mIterator;
        pushTokenChar('[');
        endToken();
        return LBRACK_;
    }
    else if (curChar() == ']') {
        ++mIterator;
        pushTokenChar(']');
        endToken();
        return RBRACK_;
    }
    else if (curChar() == '{') {
        ++mIterator;
        pushTokenChar('{');
        endToken();
        return LBRACE_;
    }
    else if (curChar() == '}') {
        ++mIterator;
        pushTokenChar('}');
        endToken();
        return RBRACE_;
    }
    else if (curChar() == ',') {
        ++mIterator;
        pushTokenChar(',');
        endToken();
        return COMMA_;
    }
    else if (curChar() == ';') {
        ++mIterator;
        pushTokenChar(';');
        endToken();
        return SEMI_;
    }
    else if ((curChar() == '@' && (nextChar() == '"' || nextChar() == '\'')) ||
        (curChar() == '@' && nextChar() == '$' && (peekChar(2) == '"' || peekChar(2) == '\'')) ||
        (curChar() == '$' && nextChar() == '@' && (peekChar(2) == '"' || peekChar(2) == '\''))) {
        bool isDollar = false;
        if ((curChar() == '@' && nextChar() == '$') || (curChar() == '$' && nextChar() == '@')) {
            ++mIterator;
            ++mIterator;
            isDollar = true;
        }
        else {
            ++mIterator;
        }
        int line = mLineNumber;
        char c = curChar();
        for (++mIterator; curChar() != '\0'; ++mIterator) {
            if (curChar() == '\n') ++mLineNumber;
            if (curChar() == c) {
                if (nextChar() == c) {
                    pushTokenChar(curChar());
                    ++mIterator;
                }
                else {
                    break;
                }
            }
            else {
                pushTokenChar(curChar());
            }
        }
        if (curChar() != 0) {
            ++mIterator;
        }
        else {
            char* pInfo = mDslFile->NewErrorInfo();
            if (pInfo)
                tsnprintf(pInfo, mDslFile->GetSingleErrorInfoCapacity(), "[line %d ]:String can't finish！", line);
        }
        endToken();
        /*Ordinary strings keep the appearance of the source code without removing the leading and trailing blank lines.
        if (myhavelinefeed(mCurToken)) {
            removeFirstAndLastEmptyLine();
        }
        */
        if (isDollar)
            return DOLLAR_STRING_;
        else
            return STRING_;
    }
    else {//keyword, identifier, or constant
        if (curChar() == '"' || curChar() == '\'' || (curChar() == '$' && (nextChar() == '"' || nextChar() == '\''))) {//Name or keyword enclosed in quotes
            bool isDollar = false;
            if (curChar() == '$') {
                ++mIterator;
                isDollar = true;
            }
            int line = mLineNumber;
            char c = curChar();
            for (++mIterator; curChar() != '\0';) {
                if (curChar() == '\n')++mLineNumber;
                if (curChar() == '\\') {
                    ++mIterator;
                    if (curChar() == 'n') {
                        pushTokenChar('\n');
                    }
                    else if (curChar() == 'r') {
                        pushTokenChar('\r');
                    }
                    else if (curChar() == 't') {
                        pushTokenChar('\t');
                    }
                    else if (curChar() == 'v') {
                        pushTokenChar('\v');
                    }
                    else if (curChar() == 'a') {
                        pushTokenChar('\a');
                    }
                    else if (curChar() == 'b') {
                        pushTokenChar('\b');
                    }
                    else if (curChar() == 'f') {
                        pushTokenChar('\f');
                    }
                    else if (curChar() == 'u' && myisdigit(nextChar(), true) && myisdigit(peekChar(2), true) && myisdigit(peekChar(3), true)) {
                        ++mIterator;
                        //4-digits hexadecimal number
                        char h1 = curChar();
                        ++mIterator;
                        char h2 = curChar();
                        ++mIterator;
                        char h3 = curChar();
                        ++mIterator;
                        char h4 = curChar();
                        pushTokenChar((char)((mychar2int(h3) << 4) + mychar2int(h4)));
                        pushTokenChar((char)((mychar2int(h1) << 4) + mychar2int(h2)));
                    }
                    else if (curChar() == 'U' && myisdigit(nextChar(), true) && myisdigit(peekChar(2), true) && myisdigit(peekChar(3), true)
                        && myisdigit(peekChar(4), true) && myisdigit(peekChar(5), true) && myisdigit(peekChar(6), true) && myisdigit(peekChar(7), true)) {
                        ++mIterator;
                        //8-digits hexadecimal number
                        char h1 = curChar();
                        ++mIterator;
                        char h2 = curChar();
                        ++mIterator;
                        char h3 = curChar();
                        ++mIterator;
                        char h4 = curChar();
                        ++mIterator;
                        char h5 = curChar();
                        ++mIterator;
                        char h6 = curChar();
                        ++mIterator;
                        char h7 = curChar();
                        ++mIterator;
                        char h8 = curChar();
                        pushTokenChar((char)((mychar2int(h7) << 4) + mychar2int(h8)));
                        pushTokenChar((char)((mychar2int(h5) << 4) + mychar2int(h6)));
                        pushTokenChar((char)((mychar2int(h3) << 4) + mychar2int(h4)));
                        pushTokenChar((char)((mychar2int(h1) << 4) + mychar2int(h2)));
                    }
                    else if (curChar() == 'x' && myisdigit(nextChar(), true)) {
                        ++mIterator;
                        //1~2 digits hexadecimal number
                        char h1 = curChar();
                        if (myisdigit(nextChar(), true)) {
                            ++mIterator;
                            char h2 = curChar();
                            char nc = (char)((mychar2int(h1) << 4) + mychar2int(h2));
                            pushTokenChar(nc);
                        }
                        else {
                            char nc = (char)mychar2int(h1);
                            pushTokenChar(nc);
                        }
                    }
                    else if (myisdigit(curChar(), false)) {
                        //1~3 digit octal number
                        char o1 = curChar();
                        if (myisdigit(nextChar(), false)) {
                            ++mIterator;
                            char o2 = curChar();
                            if (myisdigit(nextChar(), false)) {
                                ++mIterator;
                                char o3 = curChar();
                                char nc = (char)((mychar2int(o1) << 6) + (mychar2int(o2) << 3) + mychar2int(o3));
                                pushTokenChar(nc);
                            }
                            else {
                                char nc = (char)((mychar2int(o1) << 3) + mychar2int(o2));
                                pushTokenChar(nc);
                            }
                        }
                        else {
                            char nc = (char)mychar2int(o1);
                            pushTokenChar(nc);
                        }
                    }
                    else {
                        pushTokenChar(curChar());
                    }
                }
                else if (curChar() == c) {
                    if (nextChar() == c) {
                        pushTokenChar(curChar());
                        ++mIterator;
                    }
                    else {
                        break;
                    }
                }
                else {
                    pushTokenChar(curChar());
                }
                ++mIterator;

                if (curChar() == '\0') {
                    if (mIterator.Load()) {
                        continue;
                    }
                    else {
                        char* pInfo = mDslFile->NewErrorInfo();
                        if (pInfo)
                            tsnprintf(pInfo, mDslFile->GetSingleErrorInfoCapacity(), "[line %d ]:String can't finish！", line);
                        endTokenWithEof();
                        return END_OF_SLK_INPUT_;
                    }
                }
            }
            if (curChar() != '\0') {
                ++mIterator;
            }
            else {
                char* pInfo = mDslFile->NewErrorInfo();
                if (pInfo)
                    tsnprintf(pInfo, mDslFile->GetSingleErrorInfoCapacity(), "[line %d ]:String can't finish！", line);
            }
            endToken();
            /*Ordinary strings keep the appearance of the source code without removing the leading and trailing blank lines.
            if (myhavelinefeed(mCurToken)) {
                removeFirstAndLastEmptyLine();
            }
            */
            if (isDollar)
                return DOLLAR_STRING_;
            else
                return STRING_;
        }
        else {
            int isNum = TRUE;
            int isHex = FALSE;
            int includeEPart = FALSE;
            int includeAddSub = FALSE;
            int waitFinish = FALSE;
            int dotCt = 0;
            if (curChar() == '0' && nextChar() == 'x') {
                isHex = TRUE;
                pushTokenChar(curChar());
                ++mIterator;
                pushTokenChar(curChar());
                ++mIterator;
            }
            for (int charCt = 0; curChar() == '?' || curChar() == '\'' || (isNum && myisdigit(curChar(), isHex, includeEPart, includeAddSub)) || !isSpecialChar(curChar()); ++mIterator, ++charCt) {
                if (curChar() == '#')
                    break;
                else if (curChar() == '?') {
                    //When the type name is followed by a question mark (nullable type), only one question mark is allowed.
                    if (!mDslFile->OnTokenCanEatChar.isNull()) {
                        if (mDslFile->OnTokenCanEatChar(mCurToken, mTokenCharIndex, curChar())) {
                            pushTokenChar(curChar());
                            ++mIterator;
                            ++charCt;
                        }
                    }
                    break;
                }
                else if (curChar() == '\'') {
                    if (!isNum) {
                        break;
                    }
                    else {
                        if (nextChar() != 0 && !myisdigit(nextChar(), isHex, includeEPart, includeAddSub)) {
                            break;
                        }
                        ++mIterator;
                        ++charCt;
                    }
                }
                else if (curChar() == '.') {
                    if (!isNum || isHex) {
                        break;
                    }
                    else {
                        if (nextChar() == 'b' || nextChar() == 'B' || nextChar() == 'f' || nextChar() == 'F' || nextChar() == 'l' || nextChar() == 'L') {
                        }
                        else if (nextChar() != 0 && !myisdigit(nextChar(), isHex, includeEPart, includeAddSub)) {
                            char c = peekNextValidChar(1);
                            if (!isSpecialChar(c))
                                break;
                        }
                    }
                    ++dotCt;
                    if (dotCt > 1)
                        break;
                }
                else if (isNum) {
                    if (dotCt > 0 && (curChar() == 'b' || curChar() == 'B' || curChar() == 'f' || curChar() == 'F' || curChar() == 'l' || curChar() == 'L')) {
                    }
                    else if (dotCt == 0 && charCt > 0 && (curChar() == 'l' || curChar() == 'L' || curChar() == 'u' || curChar() == 'U' || curChar() == 'z' || curChar() == 'Z')) {
                    }
                    else if (FALSE == myisdigit(curChar(), isHex, includeEPart, includeAddSub)) {
                        isNum = FALSE;
                    }
                }
                if (isNum && !waitFinish) {
                    if (includeEPart && ((!isHex && (curChar() == 'e' || curChar() == 'E')) || (isHex && (curChar() == 'p' || curChar() == 'P')))) {
                        includeEPart = FALSE;
                        includeAddSub = TRUE;
                    }
                    else if (includeAddSub) {
                        includeAddSub = FALSE;
                        waitFinish = TRUE;
                    }
                    else {
                        includeEPart = TRUE;
                    }
                }
                pushTokenChar(curChar());
            }
            if (isNum) {
                endToken();
                return NUMBER_;
            }
            else {
                endToken();
                return IDENTIFIER_;
            }
        }
    }
}

bool SlkToken::enqueueToken(char* tok, short val, int line)
{
    mTokenQueue.PushBack(TokenInfo(tok, val, line));
    return true;
}

short SlkToken::peek([[maybe_unused]] int level)
{
    short token = 0;

    printf("peek_token is not called in an LL(1) grammar\n");

    return token;
}

void SlkToken::setStringDelimiter(const char* begin, const char* end)
{
    mStringBeginDelimiter = begin;
    mStringEndDelimiter = end;
    if (mStringBeginDelimiter)
        mStringBeginDelimiterLength = static_cast<int>(strlen(mStringBeginDelimiter));
    else
        mStringBeginDelimiterLength = 0;
    if (mStringEndDelimiter)
        mStringEndDelimiterLength = static_cast<int>(strlen(mStringEndDelimiter));
    else
        mStringEndDelimiterLength = 0;
}

void SlkToken::setScriptDelimiter(const char* begin, const char* end)
{
    mScriptBeginDelimiter = begin;
    mScriptEndDelimiter = end;
    if (mScriptBeginDelimiter)
        mScriptBeginDelimiterLength = static_cast<int>(strlen(mScriptBeginDelimiter));
    else
        mScriptBeginDelimiterLength = 0;
    if (mScriptEndDelimiter)
        mScriptEndDelimiterLength = static_cast<int>(strlen(mScriptEndDelimiter));
    else
        mScriptEndDelimiterLength = 0;
}

int SlkToken::isBegin(const char* delimiter, int len) const
{
    int ret = FALSE;
    if (delimiter && delimiter[0]) {
        const char* pLeft = mIterator.GetLeft();
        ret = TRUE;
        for (int i = 0; i < len; ++i) {
            if (pLeft[i] != delimiter[i]) {
                ret = FALSE;
                break;
            }
        }
    }
    return ret;
}

void SlkToken::getBlockString(const char* delimiter, int len)
{
    const char* pLeft = mIterator.GetLeft();
    const char* pFind = strstr(pLeft, delimiter);
    if (!pFind) {
        char* pInfo = mDslFile->NewErrorInfo();
        if (pInfo)
            tsnprintf(pInfo, mDslFile->GetSingleErrorInfoCapacity(), "[line %d ]:Block can't finish, delimiter: %s！", mLineNumber, delimiter);
        endToken();
        return;
    }
    const char* p = pLeft;
    while (p != pFind) {
        if (*p == '\n')
            ++mLineNumber;
        pushTokenChar(*p++);
        ++mIterator;
    }
    endToken();
    mIterator = mIterator + len;
    return removeFirstAndLastEmptyLine();
}

void SlkToken::removeFirstAndLastEmptyLine()
{
    int len = (int)strlen(mCurToken);
    int start = 0;
    while (start < len && isWhiteSpace(mCurToken[start]) && mCurToken[start] != '\n')
        ++start;
    if (start < len && mCurToken[start] == '\n') {
        ++start;
    }
    else {
        //If there is no line break at the beginning of the line, do not remove the white spaces.
        start = 0;
    }
    int end = len - 1;
    while (end > 0 && isWhiteSpace(mCurToken[end]) && mCurToken[end] != '\n') {
        --end;
    }
    if (end > 0 && mCurToken[end] == '\n') {
        //If there is a line break at the end of the line, remove the white spaces but retain the line break.
        mCurToken[end + 1] = 0;
    }
    mCurToken = &(mCurToken[start]);
}

void SlkToken::newComment()
{
    if (mDslFile) {
        mCurComment = mDslFile->GetUnusedStringPtrRef();

        mCommentCharIndex = 0;
        if (mCurComment) {
            mCurComment[mCommentCharIndex] = '\0';
        }
    }
}

void SlkToken::pushCommentChar(char c)
{
    if (nullptr == mDslFile || mDslFile->GetUnusedStringLength() <= 1 || nullptr == mCurComment)
        return;
    mCurComment[mCommentCharIndex] = c;
    ++mCommentCharIndex;
}

void SlkToken::endComment()
{
    if (nullptr == mDslFile || mDslFile->GetUnusedStringLength() <= 1 || nullptr == mCurComment || nullptr == mDslFile->GetUnusedStringPtrRef())
        return;
    mCurComment[mCommentCharIndex] = '\0';
    mDslFile->GetUnusedStringPtrRef() += mCommentCharIndex + 1;

    mComments[mCommentNum++] = mCurComment;
}

void SlkToken::newToken()
{
    if (mDslFile) {
        mCurToken = mDslFile->GetUnusedStringPtrRef();

        mTokenCharIndex = 0;
        if (mCurToken) {
            mCurToken[mTokenCharIndex] = '\0';
        }
    }
}

void SlkToken::pushTokenChar(char c)
{
    if (nullptr == mDslFile || mDslFile->GetUnusedStringLength() <= mTokenCharIndex + 1 || nullptr == mCurToken)
        return;
    mCurToken[mTokenCharIndex] = c;
    ++mTokenCharIndex;
}

void SlkToken::tempEndToken()
{
    if (nullptr == mDslFile || mDslFile->GetUnusedStringLength() <= mTokenCharIndex + 1 || nullptr == mCurToken || nullptr == mDslFile->GetUnusedStringPtrRef())
        return;
    mCurToken[mTokenCharIndex] = '\0';
}

void SlkToken::endToken()
{
    if (nullptr == mDslFile || mDslFile->GetUnusedStringLength() <= mTokenCharIndex + 1 || nullptr == mCurToken || nullptr == mDslFile->GetUnusedStringPtrRef())
        return;
    mCurToken[mTokenCharIndex] = '\0';
    mDslFile->GetUnusedStringPtrRef() += mTokenCharIndex + 1;
}

void SlkToken::endTokenWithEof()
{
    static const char* s_c_Eof = "<<eof>>";
    if (nullptr == mDslFile || mDslFile->GetUnusedStringLength() <= (int)strlen(s_c_Eof) + 1 || nullptr == mCurToken || nullptr == mDslFile->GetUnusedStringPtrRef())
        return;
    strcpy_s(mCurToken, mDslFile->GetUnusedStringLength() - 1, s_c_Eof);
    mDslFile->GetUnusedStringPtrRef() += strlen(s_c_Eof) + 1;
}

SlkToken::SlkToken(DslParser::IScriptSource& source, DslParser::DslFile& dslFile) :mSource(&source), mDslActionApi(nullptr), mDslFile(&dslFile), mTokenQueue()
{
    MyAssert(mSource);
    MyAssert(mDslFile);

    mNullableSyntaxEnabled = dslFile.IsNullableSyntaxEnabled();
    mIterator = mSource->GetIterator();

    mWhiteSpaces = " \t\r\n";
    mDelimiters = ",;";
    mBeginParentheses = "([{";
    mEndParentheses = ")]}";
    mOperators = "~`!%^&*-+=|<>/?:";
    mQuotes = "'\"";
    mSpecialChars = " \t\r\n,;([{)]}~`!%^&*-+=|<>/?:'\"";


    mLineNumber = 1;
    mLastLineNumber = 1;

    mCurToken = 0;
    mLastToken = 0;
    mTokenCharIndex = 0;

    mCurComment = 0;
    mCommentCharIndex = 0;
    mCommentNum = 0;
    mCommentOnNewLine = FALSE;

    setCanFinish(FALSE);
    setStringDelimiter("", "");
    setScriptDelimiter("", "");
}