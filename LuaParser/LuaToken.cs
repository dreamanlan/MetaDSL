using System;
using System.Collections.Generic;
using System.Text;
using Dsl.Common;

namespace Dsl.Parser
{
    struct LuaToken
    {
        internal LuaToken(DslLog log, string input)
        {
            mLog = log;
            mInput = input;
            mIterator = 0;

            mLineNumber = 1;
            mLastLineNumber = 1;

            mCurToken = string.Empty;
            mLastToken = string.Empty;
            mCachedToken = null;

            mCommentBuilder = new StringBuilder();
            mComments = new List<string>();
            mCommentOnNewLine = false;

            mTokenBuilder = new StringBuilder();
            mNames = new Dictionary<string, short> {
                { "or", LuaConstants.OP_1_ },
                { "and", LuaConstants.OP_2_ },
                { "not", LuaConstants.OP_11_ },
                { "break", LuaConstants.BREAK_ },
                { "do", LuaConstants.DO_ },
                { "else", LuaConstants.ELSE_ },
                { "elseif", LuaConstants.ELSEIF_ },
                { "end", LuaConstants.END_ },
                { "false", LuaConstants.FALSE_ },
                { "for", LuaConstants.FOR_ },
                { "function", LuaConstants.FUNCTION_ },
                { "goto", LuaConstants.GOTO_ },
                { "if", LuaConstants.IF_ },
                { "in", LuaConstants.IN_ },
                { "local", LuaConstants.LOCAL_ },
                { "nil", LuaConstants.NIL_ },
                { "repeat", LuaConstants.REPEAT_ },
                { "return", LuaConstants.RETURN_ },
                { "then", LuaConstants.THEN_ },
                { "true", LuaConstants.TRUE_ },
                { "until", LuaConstants.UNTIL_ },
                { "while", LuaConstants.WHILE_ },
            };
        }

        internal short get()
        {
            mLastToken = mCurToken;
            mLastLineNumber = mLineNumber;
            if (null != mCachedToken) {
                mCurToken = mCachedToken;
                mCachedToken = null;

                short v;
                if(mNames.TryGetValue(mCurToken, out v)) {
                    return v;
                }
                else if(mCurToken == "<<eof>>") {
                    return LuaConstants.END_OF_SLK_INPUT_;
                }
                else {
                    //走到这里应该不可能
                    throw new Exception("Fatal error !");
                }
            }
            bool isSkip = true;
            //跳过注释与白空格
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
                //--引导的单行或块注释
                if (CurChar == '-' && NextChar == '-') {
                    mCommentBuilder.Length = 0;
                    mCommentBuilder.Append(CurChar);
                    mCommentBuilder.Append(NextChar);
                    ++mIterator;
                    ++mIterator;
                    int ct = 0;
                    if (CurChar == '[') {
                        int oldIter = mIterator;
                        mCommentBuilder.Append(CurChar);
                        ++mIterator;
                        for (; CurChar != 0 && CurChar != '\n'; ++mIterator) {
                            if (CurChar != '\r')
                                mCommentBuilder.Append(CurChar);
                            if (CurChar == '=') {
                                continue;
                            }
                            else if (CurChar == '[') {
                                ct = mIterator - oldIter;
                                ++mIterator;
                                break;
                            }
                            else {
                                ++mIterator;
                                break;
                            }
                        }
                        if (ct > 0) {
                            for (; CurChar != 0; ++mIterator) {
                                if (CurChar == '\n') {
                                    mCommentBuilder.AppendLine();
                                    ++mLineNumber;
                                }
                                else if (CurChar != '\r') {
                                    mCommentBuilder.Append(CurChar);
                                }
                                if (CurChar == ']') {
                                    ++mIterator;
                                    bool end = true;
                                    for (int i = 0; i < ct - 1; ++i, ++mIterator) {
                                        if (CurChar == '\n') {
                                            mCommentBuilder.AppendLine();
                                        }
                                        else if (CurChar != '\r') {
                                            mCommentBuilder.Append(CurChar);
                                        }
                                        if (CurChar != '=') {
                                            end = false;
                                            break;
                                        }
                                    }
                                    if (end){
                                        if (CurChar == ']') {
                                            mCommentBuilder.Append(CurChar);
                                            ++mIterator;
                                            break;
                                        }
                                        else {
                                            --mIterator;
                                        }
                                    }
                                }
                            }
                        }
                    }
                    if (ct == 0) {
                        for (; CurChar != 0 && CurChar != '\n'; ++mIterator) {
                            if (CurChar != '\r')
                                mCommentBuilder.Append(CurChar);
                        }
                    }
                    isSkip = true;
                    //lua的注释在dsl里不是合法语法，另外，解析到dsl时添加的许多语法构造在输出时
                    //可能会与注释冲突，如果真的需要输出注释，可以考虑都转为块注释形式
                    //mComments.Add(mCommentBuilder.ToString());
                }
            }
            mTokenBuilder.Length = 0;
            if (CurChar == 0) {//输入结束
                mCurToken = "<<eof>>";
                if (mLastToken != ";") {
                    mCachedToken = mCurToken;
                    mCurToken = ";";
                    return LuaConstants.SEMI_;
                }
                return LuaConstants.END_OF_SLK_INPUT_;
            }
            else if (CurChar == '.' && NextChar == '.') {
                ++mIterator;
                ++mIterator;
                if (CurChar == '.') {
                    ++mIterator;
                    mCurToken = "...";
                    return LuaConstants.THREE_DOT_;
                }
                else {
                    mCurToken = "..";
                    return LuaConstants.OP_8_;
                }
            }
            else if (CurChar == ':') {
                ++mIterator;
                if (NextChar == ':') {
                    ++mIterator;
                    mCurToken = "::";
                    return LuaConstants.TWO_COLON_;
                }
                else {
                    mCurToken = ":";
                    return LuaConstants.COLON_;
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
                return LuaConstants.DOT_;
            }
            else if (CurChar == '{') {
                ++mIterator;
                mCurToken = "{";
                return LuaConstants.LBRACE_;
            }
            else if (CurChar == '}') {
                ++mIterator;
                mCurToken = "}";
                return LuaConstants.RBRACE_;
            }
            else if (CurChar == '[') {
                ++mIterator;
                mCurToken = "[";
                return LuaConstants.LBRACK_;
            }
            else if (CurChar == ']') {
                ++mIterator;
                mCurToken = "]";
                return LuaConstants.RBRACK_;
            }
            else if (CurChar == '(') {
                ++mIterator;
                mCurToken = "(";
                return LuaConstants.LPAREN_;
            }
            else if (CurChar == ')') {
                ++mIterator;
                mCurToken = ")";
                return LuaConstants.RPAREN_;
            }
            else if (CurChar == ',') {
                ++mIterator;
                mCurToken = ",";
                return LuaConstants.COMMA_;
            }
            else if (CurChar == ';') {
                ++mIterator;
                mCurToken = ";";
                return LuaConstants.SEMI_;
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
                    return LuaConstants.STRING_;
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
                    for (int charCt = 0; isNum && myisdigit(CurChar, isHex, includeEPart, includeAddSub) || !isSpecialChar(CurChar); ++mIterator, ++charCt) {
                        if (CurChar == '#')
                            break;
                        else if (CurChar == '.') {
                            if (!isNum || isHex) {
                                break;
                            }
                            else {
                                if (NextChar != 0 && NextChar != 'b' && NextChar != 'B' && NextChar != 'f' && NextChar != 'F' && NextChar != 'l' && NextChar != 'L' && !myisdigit(NextChar, isHex, includeEPart, includeAddSub)) {
                                    break;
                                }
                            }
                            ++dotCt;
                            if (dotCt > 1)
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
                            }
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
                        return LuaConstants.NUMBER_;
                    }
                    else {
                        short v;
                        if (mNames.TryGetValue(mCurToken, out v)) {
                            if (mLastToken != ";" && (v == LuaConstants.END_ || v == LuaConstants.ELSEIF_ || v == LuaConstants.ELSE_ || v == LuaConstants.UNTIL_ || v == LuaConstants.RETURN_)) {
                                mCachedToken = mCurToken;
                                mCurToken = ";";
                                return LuaConstants.SEMI_;
                            }
                            return v;
                        }
                        else {
                            return LuaConstants.NAME_;
                        }
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

        internal string getCurToken()
        {
            return mCurToken;
        }
        internal string getLastToken()
        {
            return mLastToken;
        }
        internal int getLineNumber()
        {
            return mLineNumber;
        }
        internal int getLastLineNumber()
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

        private void getOperatorToken()
        {
            int st = mIterator;
            switch (CurChar) {
                case '+':
                case '-':
                case '*':
                case '%':
                case '^':
                case '&':
                case '|':
                case '#': {
                        ++mIterator;
                    }
                    break;
                case '>': {
                        ++mIterator;
                        if (CurChar == '=') {
                            ++mIterator;
                        }
                        else if (CurChar == '>') {
                            ++mIterator;
                        }
                    }
                    break;
                case '<': {
                        ++mIterator;
                        if (CurChar == '=') {
                            ++mIterator;
                        }
                        else if (CurChar == '<') {
                            ++mIterator;
                        }
                    }
                    break;
                case '=': {
                        ++mIterator;
                        if (CurChar == '=') {
                            ++mIterator;
                        }
                    }
                    break;
                case '/': {
                        ++mIterator;
                        if (CurChar == '/') {
                            ++mIterator;
                        }
                    }
                    break;
                case '~': {
                        ++mIterator;
                        if (CurChar == '=') {
                            ++mIterator;
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
        private short getOperatorTokenValue()
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
                else if (mNames.ContainsKey(lastToken)) {
                    lastIsOperator = true;
                }
                else {
                    lastIsOperator = isOperator(lastToken[0]);
                }
            }
            short val = LuaConstants.OP_1_;
            if (curOperator.Length > 0) {
                char c0 = curOperator[0];
                char c1 = (char)0;
                char c2 = (char)0;
                if (curOperator.Length > 1)
                    c1 = curOperator[1];
                if (curOperator.Length > 2)
                    c2 = curOperator[2];
                if (c0 == '=' && c1 == '\0') {
                    val = LuaConstants.EQUAL_;
                }
                else if (c0 == '<' && c1 == '\0') {
                    val = LuaConstants.OP_3_;
                }
                else if (c0 == '>' && c1 == '\0') {
                    val = LuaConstants.OP_3_;
                }
                else if (c0 == '<' && c1 == '=' && c2 == '\0') {
                    val = LuaConstants.OP_3_;
                }
                else if (c0 == '>' && c1 == '=' && c2 == '\0') {
                    val = LuaConstants.OP_3_;
                }
                else if (c0 == '=' && c1 == '=' && c2 == '\0') {
                    val = LuaConstants.OP_3_;
                }
                else if (c0 == '~' && c1 == '=' && c2 == '\0') {
                    val = LuaConstants.OP_3_;
                }
                else if (c0 == '|' && c1 == '\0') {
                    val = LuaConstants.OP_4_;
                }
                else if (c0 == '~' && c1 == '\0') {
                    if(lastIsOperator)
                        val = LuaConstants.OP_11_;
                    else
                        val = LuaConstants.OP_5_;
                }
                else if (c0 == '&' && c1 == '\0') {
                    val = LuaConstants.OP_6_;
                }
                else if (c0 == '<' && c1 == '<' && c2 == '\0') {
                    val = LuaConstants.OP_7_;
                }
                else if (c0 == '>' && c1 == '>' && c2 == '\0') {
                    val = LuaConstants.OP_7_;
                }
                else if (c0 == '+' && c1 == '\0') {
                    val = LuaConstants.OP_9_;
                }
                else if (c0 == '-' && c1 == '\0') {
                    if(lastIsOperator)
                        val = LuaConstants.OP_11_;
                    else
                        val = LuaConstants.OP_9_;
                }
                else if (c0 == '*' && c1 == '\0') {
                    val = LuaConstants.OP_10_;
                }
                else if (c0 == '/' && c1 == '\0') {
                    val = LuaConstants.OP_10_;
                }
                else if (c0 == '%' && c1 == '\0') {
                    val = LuaConstants.OP_10_;
                }
                else if (c0 == '/' && c1 == '/' && c2 == '\0') {
                    val = LuaConstants.OP_10_;
                }
                else if (c0 == '#' && c1 == '\0') {
                    val = LuaConstants.OP_11_;
                }
                else if (c0 == '^' && c1 == '\0') {
                    val = LuaConstants.OP_12_;
                }
            }
            return val;
        }
        private bool isWhiteSpace(char c)
        {
            if (0 == c)
                return false;
            else
                return mWhiteSpaces.IndexOf(c) >= 0;
        }
        private bool isDelimiter(char c)
        {
            if (0 == c)
                return false;
            else
                return mDelimiters.IndexOf(c) >= 0;
        }
        private bool isBeginParentheses(char c)
        {
            if (0 == c)
                return false;
            else
                return mBeginParentheses.IndexOf(c) >= 0;
        }
        private bool isEndParentheses(char c)
        {
            if (0 == c)
                return false;
            else
                return mEndParentheses.IndexOf(c) >= 0;
        }
        private bool isOperator(char c)
        {
            if (0 == c)
                return false;
            else
                return mOperators.IndexOf(c) >= 0;
        }
        private bool isQuote(char c)
        {
            if (0 == c)
                return false;
            else
                return mQuotes.IndexOf(c) >= 0;
        }
        private bool isSpecialChar(char c)
        {
            if (0 == c)
                return true;
            else
                return mSpecialChars.IndexOf(c) >= 0;
        }

        private char CurChar
        {
            get {
                return PeekChar(0);
            }
        }
        private char NextChar
        {
            get {
                return PeekChar(1);
            }
        }
        private char PeekChar(int ix)
        {
            char c = (char)0;
            if (ix >= 0 && mIterator + ix < mInput.Length)
                c = mInput[mIterator + ix];
            return c;
        }

        private static bool myisdigit(char c, bool isHex)
        {
            return myisdigit(c, isHex, false, false);
        }
        private static bool myisdigit(char c, bool isHex, bool includeEPart, bool includeAddSub)
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
        private static int mychar2int(char c)
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

        private DslLog mLog;
        private string mInput;
        private int mIterator;
        private string mCurToken;
        private string mLastToken;
        private string mCachedToken;

        private int mLineNumber;
        private int mLastLineNumber;

        private StringBuilder mCommentBuilder;
        private List<string> mComments;
        private bool mCommentOnNewLine;

        private const string mWhiteSpaces = " \t\r\n";
        private const string mDelimiters = ",;";
        private const string mBeginParentheses = "{([";
        private const string mEndParentheses = "})]";
        private const string mOperators = "+-*/%^<=>~&|#:";
        private const string mQuotes = "'\"";
        private const string mSpecialChars = mWhiteSpaces + mDelimiters + mBeginParentheses + mEndParentheses + mOperators + mQuotes;

        private Dictionary<string, short> mNames;
        private StringBuilder mTokenBuilder;
    }
}
