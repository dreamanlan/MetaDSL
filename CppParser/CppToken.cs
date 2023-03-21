using System;
using System.Collections.Generic;
using System.Text;
using Dsl.Parser;

namespace Dsl.Common
{
    public struct CppToken
    {
        internal CppToken(DslAction action, DslLog log, string input)
        {
            mAction = action;
            mLog = log;
            mInput = input;
            mIterator = 0;

            mLineNumber = 1;
            mLastLineNumber = 1;

            mCurToken = string.Empty;
            mLastToken = string.Empty;

            mTokenBuilder = new StringBuilder();
            mTokenQueue = new Queue<TokenInfo>();
            mMatchStack = new Stack<string>();
            mOnGetToken = null;
            mOnTokenCanEatQuestion = null;
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
            //跳过注释与白空格
            for (; isSkip && CurChar != 0;) {
                bool s1 = SkipWhiteSpaces();
                bool s2 = SkipComments();
                isSkip = s1 || s2;
                //预处理先忽略掉
                if (CurChar == '#') {
                    //预处理（define, undef, include, if, ifdef, ifndef, else, elif, elifdef, elifndef (since C++23), endif, line, error, pragma）
                    ++mIterator;
                    mTokenBuilder.Length = 0;
                    bool isSkip2 = true;
                    for (; isSkip2 && CurChar!=0;) {
                        bool ps1 = SkipWhiteSpaces();
                        bool ps2 = SkipComments();
                        isSkip2 = ps1 || ps2;
                    }
                    for (; char.IsLetter(CurChar); ++mIterator) {
                        mTokenBuilder.Append(CurChar);
                    }
                    mTokenBuilder.Length = 0;
                    for (; CurChar != '\n' && isWhiteSpace(CurChar); ++mIterator) ;
                    string arg = string.Empty;
                    if (CurChar != 0 && CurChar != '\n') {
                        char lc = '\0';
                        for (; CurChar != 0; ++mIterator) {
                            SkipComments();
                            if (CurChar == 0)
                                break;
                            char cc = CurChar;
                            if (cc == '\r' && lc != '\\' || cc == '\n' && lc != '\r' && lc != '\\') {
                                arg = mTokenBuilder.ToString().Trim();
                                break;
                            }
                            if (cc == '"' || cc == '\'') {
                                //字符串
                                mTokenBuilder.Append(cc);
                                ++mIterator;
                                while (CurChar != 0 && CurChar != cc) {
                                    char c = CurChar;
                                    mTokenBuilder.Append(c);
                                    ++mIterator;
                                    if (c == '\\' && CurChar != 0) {
                                        mTokenBuilder.Append(CurChar);
                                        ++mIterator;
                                    }
                                }
                                mTokenBuilder.Append(CurChar);
                            }
                            else if (cc == '\\' && (NextChar == '\r' || NextChar == '\n')) {
                                //续行符不输出
                            }
                            else {
                                if (cc == '\n')
                                    ++mLineNumber;
                                mTokenBuilder.Append(cc);
                            }
                            lc = CurChar;
                        }
                    }
                    isSkip = true;
                }
            }
            mTokenBuilder.Length = 0;
            if (CurChar == 0) {//输入结束
                mCurToken = "<<eof>>";
                return CppConstants.END_OF_SLK_INPUT_;
            }
            else if (CurChar == '<' && NextChar == ':') {
                ++mIterator;
                ++mIterator;
                if (CurChar == ':') {
                    if (NextChar == '>') {
                        mCurToken = "[";
                        mMatchStack.Push(mCurToken);
                        return CppConstants.LBRACK_;
                    }
                    else {
                        ++mIterator;
                        mTokenQueue.Enqueue(new TokenInfo { Token = "::", TokenValue = CppConstants.IDENTIFIER_, LineNumber = mLineNumber });
                        mCurToken = "<";
                        return CppConstants.IDENTIFIER_;
                    }
                }
                else {
                    mCurToken = "[";
                    mMatchStack.Push(mCurToken);
                    return CppConstants.LBRACK_;
                }
            }
            else if (CurChar == ':' && NextChar == '>') {
                ++mIterator;
                ++mIterator;
                if (mMatchStack.Count == 0) {
                    mCurToken = "[";
                    EnqueueMatchedToken(mCurToken);
                    return CppConstants.LBRACK_;
                }
                else {
                    if(mMatchStack.Peek() == "[")
                        mMatchStack.Pop();
                    mCurToken = "]";
                    return CppConstants.RBRACK_;
                }
            }
            else if (CurChar == '<' && NextChar == '%') {
                ++mIterator;
                ++mIterator;
                mCurToken = "{";
                mMatchStack.Push(mCurToken);
                return CppConstants.LBRACE_;
            }
            else if (CurChar == '%' && NextChar == '>') {
                ++mIterator;
                ++mIterator;
                if (mMatchStack.Count == 0) {
                    mCurToken = "{";
                    EnqueueMatchedToken(mCurToken);
                    return CppConstants.LBRACE_;
                }
                else {
                    if (mMatchStack.Peek() == "{")
                        mMatchStack.Pop();
                    mCurToken = "}";
                    return CppConstants.RBRACE_;
                }
            }
            else if (CurChar == ':' && NextChar == ':') {
                ++mIterator;
                ++mIterator;
                mCurToken = "::";
                return CppConstants.IDENTIFIER_;
            }
            else if (CurChar == '-') {
                if (NextChar == '>') {
                    char nextChar = '\0';
                    for (int start = mIterator + 2; start < mInput.Length; ++start) {
                        if (mWhiteSpaces.IndexOf(mInput[start]) >= 0) {
                            continue;
                        }
                        else {
                            nextChar = mInput[start];
                            break;
                        }
                    }
                    if (nextChar == '*') {
                        ++mIterator;
                        ++mIterator;
                        ++mIterator;
                        mCurToken = "->*";
                        return CppConstants.IDENTIFIER_;
                    }
                    else if (!char.IsLetter(nextChar) && nextChar != '_') {
                        getOperatorToken();
                        return CppConstants.IDENTIFIER_;
                    }
                    else {
                        ++mIterator;
                        ++mIterator;
                        mCurToken = "->";
                        return CppConstants.IDENTIFIER_;
                    }
                }
                else {
                    getOperatorToken();
                    return CppConstants.IDENTIFIER_;
                }
            }
            else if (CurChar == '.' && NextChar == '*') {
                ++mIterator;
                ++mIterator;
                mCurToken = ".*";
                return CppConstants.IDENTIFIER_;
            }
            else if (CurChar == '.' && NextChar == '.') {
                ++mIterator;
                ++mIterator;
                if (CurChar == '.') {
                    ++mIterator;
                    mCurToken = "...";
                    return CppConstants.IDENTIFIER_;
                }
                else {
                    mCurToken = "..";
                    return CppConstants.IDENTIFIER_;
                }
            }
            else if (mOperators.IndexOf(CurChar) >= 0) {
                getOperatorToken();
                return CppConstants.IDENTIFIER_;
            }
            else if (CurChar == '.' && !myisdigit(NextChar, false)) {
                while (CurChar == '.' && !myisdigit(NextChar, false)) {
                    mTokenBuilder.Append(CurChar);
                    ++mIterator;
                }
                mCurToken = mTokenBuilder.ToString();
                return CppConstants.IDENTIFIER_;
            }
            else if (CurChar == '{') {
                ++mIterator;
                mCurToken = "{";
                mMatchStack.Push(mCurToken);
                return CppConstants.LBRACE_;
            }
            else if (CurChar == '}') {
                ++mIterator;
                if (mMatchStack.Count == 0) {
                    mCurToken = "{";
                    EnqueueMatchedToken(mCurToken);
                    return CppConstants.LBRACE_;
                }
                else {
                    if (mMatchStack.Peek() == "{")
                        mMatchStack.Pop();
                    mCurToken = "}";
                    return CppConstants.RBRACE_;
                }
            }
            else if (CurChar == '[') {
                ++mIterator;
                mCurToken = "[";
                mMatchStack.Push(mCurToken);
                return CppConstants.LBRACK_;
            }
            else if (CurChar == ']') {
                ++mIterator;
                if (mMatchStack.Count == 0) {
                    mCurToken = "[";
                    EnqueueMatchedToken(mCurToken);
                    return CppConstants.LBRACK_;
                }
                else {
                    if (mMatchStack.Peek() == "[")
                        mMatchStack.Pop();
                    mCurToken = "]";
                    return CppConstants.RBRACK_;
                }
            }
            else if (CurChar == '(') {
                ++mIterator;
                mCurToken = "(";
                mMatchStack.Push(mCurToken);
                return CppConstants.LPAREN_;
            }
            else if (CurChar == ')') {
                ++mIterator;
                if (mMatchStack.Count == 0) {
                    mCurToken = "(";
                    EnqueueMatchedToken(mCurToken);
                    return CppConstants.LPAREN_;
                }
                else {
                    if (mMatchStack.Peek() == "(")
                        mMatchStack.Pop();
                    mCurToken = ")";
                    return CppConstants.RPAREN_;
                }
            }
            else if (CurChar == ',') {
                ++mIterator;
                mCurToken = ",";
                return CppConstants.COMMA_;
            }
            else if (CurChar == ';') {
                ++mIterator;
                mCurToken = ";";
                return CppConstants.SEMI_;
            }
            else {//关键字、标识符或常数
                if (CurChar == '"' || CurChar == '\'') {//引号括起来的名称或关键字
                    int line = mLineNumber;
                    char c = CurChar;
                    for (++mIterator; CurChar != 0 && CurChar != c; ++mIterator) {
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
                                //4位16进制数
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
                                //8位16进制数
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
                                //1~2位16进制数
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
                                //1~3位8进制数
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
                        else {
                            mTokenBuilder.Append(CurChar);
                        }
                    }
                    if (CurChar != 0) {
                        ++mIterator;
                    }
                    else {
                        mLog.Log("[error][行 {0} ]：字符串无法结束！\n", line);
                    }
                    mCurToken = mTokenBuilder.ToString();
                    return CppConstants.STRING_;
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
                            //类型名后接问号的情形（nullable type），只允许后接一个问号
                            if (null != mOnTokenCanEatQuestion) {
                                if (mOnTokenCanEatQuestion(mTokenBuilder)) {
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
                        return CppConstants.NUMBER_;
                    }
                    else {
                        return CppConstants.IDENTIFIER_;
                    }
                }
            }
        }

        internal short peek(int level) // scan next token without consuming it
        {
            if (mTokenQueue.Count >= level) {
                int i = 0;
                foreach (var tk in mTokenQueue) {
                    ++i;
                    if (i == level) {
                        return tk.TokenValue;
                    }
                }
            }
            string curToken = getCurToken();
            string lastToken = getLastToken();
            int lineNumber = getLineNumber();
            int lastLineNumber = getLastLineNumber();
            short token = 0;
            for (int i = mTokenQueue.Count; i < level; ++i) {
                token = get();
                mTokenQueue.Enqueue(new TokenInfo { Token = getCurToken(), TokenValue = token, LineNumber = getLineNumber() });
            }
            mCurToken = curToken;
            mLastToken = lastToken;
            mLineNumber = lineNumber;
            mLastLineNumber = lastLineNumber;
            return token;
        }

        internal void fake(short token)
        {
            switch (token) {
                case CppConstants.IDENTIFIER_:
                case CppConstants.STRING_:
                    mLastToken = "cpp_dsl_add";
                    break;
                case CppConstants.NUMBER_:
                    mLastToken = "0xBadCafe";
                    break;
                case CppConstants.LPAREN_:
                    mLastToken = "(";
                    break;
                case CppConstants.LBRACK_:
                    mLastToken = "[";
                    break;
                case CppConstants.LBRACE_:
                    mLastToken = "{";
                    break;
                case CppConstants.RPAREN_:
                    mMatchStack.Pop();
                    mLastToken = ")";
                    break;
                case CppConstants.RBRACK_:
                    mMatchStack.Pop();
                    mLastToken = "]";
                    break;
                case CppConstants.RBRACE_:
                    mMatchStack.Pop();
                    mLastToken = "}";
                    break;
            }
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
        internal GetCppTokenDelegation OnGetToken
        {
            get { return mOnGetToken; }
            set { mOnGetToken = value; }
        }
        internal TokenCanEatQuestionDelegation OnTokenCanEatQuestion
        {
            get { return mOnTokenCanEatQuestion; }
            set { mOnTokenCanEatQuestion = value; }
        }

        private bool SkipWhiteSpaces()
        {
            bool isSkip = false;
            for (; mWhiteSpaces.IndexOf(CurChar) >= 0; ++mIterator) {
                if (CurChar == '\n') {
                    ++mLineNumber;
                }
                isSkip = true;
            }
            return isSkip;
        }
        private bool SkipComments()
        {
            bool isSkip = false;
            //单行注释
            if (CurChar == '/' && NextChar == '/') {
                for (; CurChar != 0 && CurChar != '\n'; ++mIterator) ;
                //++mLineNumber;
                isSkip = true;
            }
            //多行注释
            if (CurChar == '/' && NextChar == '*') {
                ++mIterator;
                ++mIterator;
                for (; CurChar != 0; ++mIterator) {
                    if (CurChar == '\n') {
                        ++mLineNumber;
                    }
                    else if (CurChar == '*' && NextChar == '/') {
                        ++mIterator;
                        ++mIterator;
                        break;
                    }
                }
                isSkip = true;
            }
            return isSkip;
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
        public bool isNotIdentifierAndEndParenthesis(char c)
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

        public void EnqueueMatchedToken(string otherPair)
        {
            if (otherPair == "(")
                mTokenQueue.Enqueue(new TokenInfo { Token = ")", TokenValue = CppConstants.RPAREN_, LineNumber = mLineNumber });
            else if (otherPair == "[")
                mTokenQueue.Enqueue(new TokenInfo { Token = "]", TokenValue = CppConstants.RBRACK_, LineNumber = mLineNumber });
            else if (otherPair == "{")
                mTokenQueue.Enqueue(new TokenInfo { Token = "}", TokenValue = CppConstants.RBRACE_, LineNumber = mLineNumber });
            else if (otherPair == ")")
                mTokenQueue.Enqueue(new TokenInfo { Token = "(", TokenValue = CppConstants.LPAREN_, LineNumber = mLineNumber });
            else if (otherPair == "]")
                mTokenQueue.Enqueue(new TokenInfo { Token = "[", TokenValue = CppConstants.LBRACK_, LineNumber = mLineNumber });
            else if (otherPair == "}")
                mTokenQueue.Enqueue(new TokenInfo { Token = "{", TokenValue = CppConstants.LBRACE_, LineNumber = mLineNumber });
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
        public static string myUnQuoteString(string str)
        {
            if (str.Length >= 2 && str[0] == '"' && str[str.Length - 1] == '"') {
                return str.Substring(1, str.Length - 2);
            }
            else {
                return str;
            }
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

        private const string mWhiteSpaces = " \t\r\n";
        private const string mDelimiters = ",;";
        private const string mBeginParentheses = "{([";
        private const string mEndParentheses = "})]";
        private const string mOperators = "~`!%^&*-+=|:<>?/";
        private const string mQuotes = "'\"";
        private const string mSpecialChars = mWhiteSpaces + mDelimiters + mBeginParentheses + mEndParentheses + mOperators + mQuotes;

        private StringBuilder mTokenBuilder;
        private Queue<TokenInfo> mTokenQueue;
        private Stack<string> mMatchStack;
        private GetCppTokenDelegation mOnGetToken;
        private TokenCanEatQuestionDelegation mOnTokenCanEatQuestion;
    }
}
