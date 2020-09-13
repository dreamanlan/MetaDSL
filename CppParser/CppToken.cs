using System;
using System.Collections.Generic;
using System.Text;
using Dsl.Common;

namespace Cpp.Parser
{
    struct CppToken
    {
        internal CppToken(DslLog log, string input)
        {
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

            mStringBeginDelimiter = string.Empty;
            mStringEndDelimiter = string.Empty;
            mScriptBeginDelimiter = string.Empty;
            mScriptEndDelimiter = string.Empty;
        }

        internal short get()
        {
            mLastToken = mCurToken;
            mLastLineNumber = mLineNumber;
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
                //#引导的单行注释或C++风格的单行注释
                if (CurChar == '#' || CurChar == '/' && NextChar == '/') {
                    mCommentBuilder.Length = 0;
                    for (; CurChar != 0 && CurChar != '\n'; ++mIterator) {
                        if (CurChar != '\r')
                            mCommentBuilder.Append(CurChar);
                    }
                    isSkip = true;
                    mComments.Add(mCommentBuilder.ToString());
                }
                //C++风格的多行注释
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
            if (CurChar == 0) {//输入结束
                mCurToken = "<<eof>>";
                return CppConstants.END_OF_SLK_INPUT_;
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
                return CppConstants.DOT_;
            }
            else if (CurChar == '{') {
                ++mIterator;
                mCurToken = "{";
                return CppConstants.LBRACE_;
            }
            else if (CurChar == '}') {
                ++mIterator;
                mCurToken = "}";
                return CppConstants.RBRACE_;
            }
            else if (CurChar == '[') {
                ++mIterator;
                mCurToken = "[";
                return CppConstants.LBRACK_;
            }
            else if (CurChar == ']') {
                ++mIterator;
                mCurToken = "]";
                return CppConstants.RBRACK_;
            }
            else if (CurChar == '(') {
                ++mIterator;
                mCurToken = "(";
                return CppConstants.LPAREN_;
            }
            else if (CurChar == ')') {
                ++mIterator;
                mCurToken = ")";
                return CppConstants.RPAREN_;
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
                            else if (CurChar == 'x' && myisdigit(NextChar, true)) {
                                ++mIterator;
                                //1~2位16进制数
                                char h1 = CurChar;
                                if (myisdigit(NextChar, true)) {
                                    ++mIterator;
                                    char h2 = CurChar;
                                    char nc = (char)(mychar2int(h1) * 16 + mychar2int(h2));
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
                                        char nc = (char)(mychar2int(o1) * 64 + mychar2int(o2) * 8 + mychar2int(o3));
                                        mTokenBuilder.Append(nc);
                                    }
                                    else {
                                        char nc = (char)(mychar2int(o1) * 8 + mychar2int(o2));
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
                    /*普通字符串保持源码的样子，不去掉首尾空行
                    if (mCurToken.IndexOf('\n') >= 0) {
                        mCurToken = removeFirstAndLastEmptyLine(mCurToken);
                    }
                    */
                    return CppConstants.STRING_;
                }
                else {
                    bool isNum = true;
                    bool isHex = false;
                    bool includeEPart = false;
                    bool includeAddSub = false;
                    int dotCt = 0;
                    if (CurChar == '0' && NextChar == 'x') {
                        isHex = true;
                        mTokenBuilder.Append(CurChar);
                        ++mIterator;
                        mTokenBuilder.Append(CurChar);
                        ++mIterator;
                    }
                    for (; isNum && myisdigit(CurChar, isHex, includeEPart, includeAddSub) || !isSpecialChar(CurChar); ++mIterator) {
                        if (CurChar == '#')
                            break;
                        else if (CurChar == '.') {
                            if (!isNum || isHex) {
                                break;
                            }
                            else {
                                if (NextChar != 0 && !myisdigit(NextChar, isHex, includeEPart, includeAddSub)) {
                                    break;
                                }
                            }
                            ++dotCt;
                            if (dotCt > 1)
                                break;
                        }
                        else if (!myisdigit(CurChar, isHex, includeEPart, includeAddSub)) {
                            isNum = false;
                        }
                        mTokenBuilder.Append(CurChar);
                        includeEPart = true;
                        if (includeEPart && (CurChar == 'e' || CurChar == 'E')) {
                            includeEPart = false;
                            includeAddSub = true;
                        }
                        else if (includeAddSub) {
                            includeAddSub = false;
                        }
                    }
                    mCurToken = mTokenBuilder.ToString();
                    if (isNum) {
                        if (mCurToken.IndexOf('.') >= 0)
                            return CppConstants.FLOAT_;
                        else
                            return CppConstants.INT_;
                    }
                    else {
                        return CppConstants.IDENTIFIER_;
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
                mLog.Log("[error][行 {0} ]：block can't finish, delimiter: {1}！\n", mLineNumber, delimiter);
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
            if (str[start] == '\n') {
                ++start;
            }
            else {
                //如果开始行没有换行，就保留白空格
                start = 0;
            }
            int end = str.Length - 1;
            while (end > 0 && isWhiteSpace(str[end]) && str[end] != '\n')
                --end;
            if (end > 0 && str[end] != '\n') {
                //如果结束行没有换行，就保留白空格；否则去掉白空格，但保留换行
                end = str.Length - 1;
            }
            if (start > 0 || end < str.Length - 1) {
                return str.Substring(start, end - start + 1);
            }
            else {
                return str;
            }
        }

        private void getOperatorToken()
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
                else {
                    lastIsOperator = isOperator(lastToken[0]);
                }
            }
            short val = CppConstants.EQUAL_;
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
                if (c0 == '=' && c1 == '\0') {
                    val = CppConstants.EQUAL_;
                }
                else {
                    val = CppConstants.EQUAL_;
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
                char c = (char)0;
                if (mIterator < mInput.Length)
                    c = mInput[mIterator];
                return c;
            }
        }
        private char NextChar
        {
            get {
                char c = (char)0;
                if (mIterator + 1 < mInput.Length)
                    c = mInput[mIterator + 1];
                return c;
            }
        }
        private string StringBeginDelimiter
        {
            get { return mStringBeginDelimiter; }
        }
        private string StringEndDelimiter
        {
            get { return mStringEndDelimiter; }
        }
        private string ScriptBeginDelimiter
        {
            get { return mScriptBeginDelimiter; }
        }
        private string ScriptEndDelimiter
        {
            get { return mScriptEndDelimiter; }
        }

        private static bool myisdigit(char c, bool isHex)
        {
            return myisdigit(c, isHex, false, false);
        }
        private static bool myisdigit(char c, bool isHex, bool includeEPart, bool includeAddSub)
        {
            bool ret = false;
            if (isHex) {
                if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
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

        private string mStringBeginDelimiter;
        private string mStringEndDelimiter;
        private string mScriptBeginDelimiter;
        private string mScriptEndDelimiter;
    }
}
