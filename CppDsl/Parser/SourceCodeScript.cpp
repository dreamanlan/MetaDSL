#include <sstream>
#include "SourceCodeScript.h"
#include "SlkInc.h"
#include "SlkParse.h"
#include "ByteCode.h"

#define MAX_ACTION_NUM	41

//--------------------------------------------------------------------------------------
class ActionForSourceCodeScript : public SlkAction, public RuntimeBuilderT < ActionForSourceCodeScript >
{
    typedef RuntimeBuilderT<ActionForSourceCodeScript> BaseType;
public:
    inline char* getLastToken(void) const;
    inline int getLastLineNumber(void) const;
    inline int getCommentNum(int& commentOnNewLine) const;
    inline char* getComment(int index) const;
    inline void resetComments(void);
    inline void setCanFinish(int val);
    inline void setStringDelimiter(const char* begin, const char* end);
    inline void setScriptDelimiter(const char* begin, const char* end);
public:
    ActionForSourceCodeScript(SlkToken& scanner, Dsl::DslFile& dataFile);
public:
    inline void    pushId(void);
    inline void    pushStr(void);
    inline void    pushNum(void);
    void    (ActionForSourceCodeScript::* Action[MAX_ACTION_NUM]) (void);
    inline void    initialize_table(void);
    inline void 	 execute(int  number) { (this->*Action[number]) (); }
private:
    SlkToken* mScanner;
};
//--------------------------------------------------------------------------------------
inline char* ActionForSourceCodeScript::getLastToken(void) const
{
    if (NULL != mScanner) {
        return mScanner->getLastToken();
    }
    else {
        return NULL;
    }
}
inline int ActionForSourceCodeScript::getLastLineNumber(void) const
{
    if (NULL != mScanner) {
        return mScanner->getLastLineNumber();
    }
    else {
        return -1;
    }
}
inline int ActionForSourceCodeScript::getCommentNum(int& commentOnNewLine) const
{
    if (NULL != mScanner) {
        return mScanner->getCommentNum(commentOnNewLine);
    }
    else {
        commentOnNewLine = FALSE;
        return 0;
    }
}
inline char* ActionForSourceCodeScript::getComment(int index) const
{
    if (NULL != mScanner) {
        return mScanner->getComment(index);
    }
    else {
        return NULL;
    }
}
inline void ActionForSourceCodeScript::resetComments(void)
{
    if (NULL != mScanner) {
        mScanner->resetComments();
    }
}
inline void ActionForSourceCodeScript::setCanFinish(int val)
{
    if (NULL != mScanner) {
        mScanner->setCanFinish(val);
    }
}
inline void ActionForSourceCodeScript::setStringDelimiter(const char* begin, const char* end)
{
    if (NULL != mScanner) {
        mScanner->setStringDelimiter(begin, end);
    }
}
inline void ActionForSourceCodeScript::setScriptDelimiter(const char* begin, const char* end)
{
    if (NULL != mScanner) {
        mScanner->setScriptDelimiter(begin, end);
    }
}
//--------------------------------------------------------------------------------------
//标识符
inline void ActionForSourceCodeScript::pushId(void)
{
    char* lastToken = getLastToken();
    if (NULL != lastToken) {
        mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::ID_TOKEN));
    }
}
inline void ActionForSourceCodeScript::pushNum(void)
{
    char* lastToken = getLastToken();
    if (NULL != lastToken) {
        mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::NUM_TOKEN));
    }
}
inline void ActionForSourceCodeScript::pushStr(void)
{
    char* lastToken = getLastToken();
    if (NULL != lastToken) {
        mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::STRING_TOKEN));
    }
}
//--------------------------------------------------------------------------------------
inline ActionForSourceCodeScript::ActionForSourceCodeScript(SlkToken& scanner, Dsl::DslFile& dataFile) :mScanner(&scanner), BaseType(dataFile)
{
    mApi.SetImpl(this);
    initialize_table();
    setEnvironmentObjRef(*this);
}
//--------------------------------------------------------------------------------------
inline void ActionForSourceCodeScript::initialize_table(void)
{
    Action[0] = 0;
    Action[1] = &ActionForSourceCodeScript::endStatement;
    Action[2] = &ActionForSourceCodeScript::pushId;
    Action[3] = &ActionForSourceCodeScript::buildOperator;
    Action[4] = &ActionForSourceCodeScript::buildFirstTernaryOperator;
    Action[5] = &ActionForSourceCodeScript::buildSecondTernaryOperator;
    Action[6] = &ActionForSourceCodeScript::beginStatement;
    Action[7] = &ActionForSourceCodeScript::addFunction;
    Action[8] = &ActionForSourceCodeScript::setFunctionId;
    Action[9] = &ActionForSourceCodeScript::markParenthesisParam;
    Action[10] = &ActionForSourceCodeScript::buildHighOrderFunction;
    Action[11] = &ActionForSourceCodeScript::markBracketParam;
    Action[12] = &ActionForSourceCodeScript::markQuestionParenthesisParam;
    Action[13] = &ActionForSourceCodeScript::markQuestionBracketParam;
    Action[14] = &ActionForSourceCodeScript::markQuestionBraceParam;
    Action[15] = &ActionForSourceCodeScript::markStatement;
    Action[16] = &ActionForSourceCodeScript::markExternScript;
    Action[17] = &ActionForSourceCodeScript::setExternScript;
    Action[18] = &ActionForSourceCodeScript::markBracketColonParam;
    Action[19] = &ActionForSourceCodeScript::markParenthesisColonParam;
    Action[20] = &ActionForSourceCodeScript::markAngleBracketColonParam;
    Action[21] = &ActionForSourceCodeScript::markBracePercentParam;
    Action[22] = &ActionForSourceCodeScript::markBracketPercentParam;
    Action[23] = &ActionForSourceCodeScript::markParenthesisPercentParam;
    Action[24] = &ActionForSourceCodeScript::markAngleBracketPercentParam;
    Action[25] = &ActionForSourceCodeScript::markColonColonParam;
    Action[26] = &ActionForSourceCodeScript::setMemberId;
    Action[27] = &ActionForSourceCodeScript::markColonColonParenthesisParam;
    Action[28] = &ActionForSourceCodeScript::markColonColonBracketParam;
    Action[29] = &ActionForSourceCodeScript::markColonColonBraceParam;
    Action[30] = &ActionForSourceCodeScript::markPeriodParam;
    Action[31] = &ActionForSourceCodeScript::markPeriodParenthesisParam;
    Action[32] = &ActionForSourceCodeScript::markPeriodBracketParam;
    Action[33] = &ActionForSourceCodeScript::markPeriodBraceParam;
    Action[34] = &ActionForSourceCodeScript::markQuestionPeriodParam;
    Action[35] = &ActionForSourceCodeScript::markPointerParam;
    Action[36] = &ActionForSourceCodeScript::markPeriodStarParam;
    Action[37] = &ActionForSourceCodeScript::markQuestionPeriodStarParam;
    Action[38] = &ActionForSourceCodeScript::markPointerStarParam;
    Action[39] = &ActionForSourceCodeScript::pushStr;
    Action[40] = &ActionForSourceCodeScript::pushNum;
}
//--------------------------------------------------------------------------------------

namespace Dsl
{
    class CachedScriptSource : public IScriptSource
    {
    public:
        explicit CachedScriptSource(const char* p) :m_Source(p)
        {}
    protected:
        virtual int Load(void)
        {
            return FALSE;
        }
        virtual const char* GetBuffer(void)const
        {
            return m_Source;
        }
    private:
        const char* m_Source;
    };
    //------------------------------------------------------------------------------------------------------
    void DslActionApi::endStatement(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->endStatement();
    }
    void DslActionApi::buildOperator(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->buildOperator();
    }
    void DslActionApi::buildFirstTernaryOperator(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->buildFirstTernaryOperator();
    }
    void DslActionApi::buildSecondTernaryOperator(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->buildSecondTernaryOperator();
    }
    void DslActionApi::beginStatement(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->beginStatement();
    }
    void DslActionApi::addFunction(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->addFunction();
    }
    void DslActionApi::setFunctionId(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->setFunctionId();
    }
    void DslActionApi::markParenthesisParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markParenthesisParam();
    }
    void DslActionApi::buildHighOrderFunction(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->buildHighOrderFunction();
    }
    void DslActionApi::markBracketParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markBracketParam();
    }
    void DslActionApi::markQuestionParenthesisParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markQuestionParenthesisParam();
    }
    void DslActionApi::markQuestionBracketParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markQuestionBracketParam();
    }
    void DslActionApi::markQuestionBraceParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markQuestionBraceParam();
    }
    void DslActionApi::markStatement(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markStatement();
    }
    void DslActionApi::markExternScript(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markExternScript();
    }
    void DslActionApi::markBracketColonParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markBracketColonParam();
    }
    void DslActionApi::markParenthesisColonParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markParenthesisColonParam();
    }
    void DslActionApi::markAngleBracketColonParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markAngleBracketColonParam();
    }
    void DslActionApi::markBracePercentParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markBracePercentParam();
    }
    void DslActionApi::markBracketPercentParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markBracketPercentParam();
    }
    void DslActionApi::markParenthesisPercentParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markParenthesisPercentParam();
    }
    void DslActionApi::markAngleBracketPercentParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markAngleBracketPercentParam();
    }
    void DslActionApi::markColonColonParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markColonColonParam();
    }
    void DslActionApi::markColonColonParenthesisParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markColonColonParenthesisParam();
    }
    void DslActionApi::markColonColonBracketParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markColonColonBracketParam();
    }
    void DslActionApi::markColonColonBraceParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markColonColonBraceParam();
    }
    void DslActionApi::setExternScript(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->setExternScript();
    }
    void DslActionApi::markPeriodParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markPeriodParam();
    }
    void DslActionApi::setMemberId(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->setMemberId();
    }
    void DslActionApi::markPeriodParenthesisParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markPeriodParenthesisParam();
    }
    void DslActionApi::markPeriodBracketParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markPeriodBracketParam();
    }
    void DslActionApi::markPeriodBraceParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markPeriodBraceParam();
    }
    void DslActionApi::markQuestionPeriodParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markQuestionPeriodParam();
    }
    void DslActionApi::markPointerParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markPointerParam();
    }
    void DslActionApi::markPeriodStarParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markPeriodStarParam();
    }
    void DslActionApi::markQuestionPeriodStarParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markQuestionPeriodStarParam();
    }
    void DslActionApi::markPointerStarParam(void)const
    {
        if (!m_Impl)
            return;
        m_Impl->markPointerStarParam();
    }
    void DslActionApi::push(char* token, int type)const
    {
        if (!m_Impl)
            return;
        m_Impl->getRuntimeBuilderData().push(RuntimeBuilderData::TokenInfo(token, type));
    }
    StatementData* DslActionApi::getCurStatement(void)const
    {
        if (!m_Impl)
            return 0;
        m_Impl->getRuntimeBuilderData().getCurStatement();
    }
    FunctionData* DslActionApi::getLastFunction(void)const
    {
        if (!m_Impl)
            return 0;
        m_Impl->getRuntimeBuilderData().getLastFunction();
    }
    void DslActionApi::setLastFunction(FunctionData* p)const
    {
        if (!m_Impl)
            return;
        m_Impl->getRuntimeBuilderData().setLastFunction(p);
    }
    //------------------------------------------------------------------------------------------------------
    bool Mac2Unix(char* buf, int len)
    {
        bool r = false;
        char* p = strchr(buf, '\r');
        if (p && *(p + 1) != '\n') {
            for (int ix = 0; ix < len; ++ix) {
                if (buf[ix] == '\r')
                    buf[ix] = '\n';
            }
            r = true;
        }
        return r;
    }
    void Parse(const char* buf, DslFile& file)
    {
        if (0 == buf)
            return;
        CachedScriptSource source(buf);
        Parse(source, file);
    }
    void Parse(IScriptSource& source, DslFile& file)
    {
        file.ClearErrorInfo();
        SlkToken tokens(source, file);
        SlkError error(file);
        ActionForSourceCodeScript action(tokens, file);
        SlkParse(action, tokens, error, 0);
        if (tokens.getStringBeginDelimiter()[0] && tokens.getStringEndDelimiter()[0]) {
            file.SetStringDelimiter(tokens.getStringBeginDelimiter(), tokens.getStringEndDelimiter());
        }
        if (tokens.getScriptBeginDelimiter()[0] && tokens.getScriptEndDelimiter()[0]) {
            file.SetScriptDelimiter(tokens.getScriptBeginDelimiter(), tokens.getScriptEndDelimiter());
        }
    }
    std::string TransformPreprocess(const char* input, int len, const char* beginDelim, const char* endDelim);
    void ParseGpp(const char* buf, DslFile& file, const char* beginDelim, const char* endDelim, char* gppBuf, int& len)
    {
        std::string str = TransformPreprocess(buf, static_cast<int>(strlen(buf)), beginDelim, endDelim);
        Parse(str.c_str(), file);
        if (gppBuf && len > 0) {
            tsnprintf(gppBuf, len, "%s", str.c_str());
            len = static_cast<int>(str.length());
        }
    }
    static inline void ltrim(std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
            }));
    }
    static inline void rtrim(std::string& s) {
        s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
            }).base(), s.end());
    }
    static inline void trim(std::string& s) {
        ltrim(s);
        rtrim(s);
    }
    static inline std::size_t replace_all(std::string& inout, const std::string& what, const std::string& with)
    {
        std::size_t count = 0;
        for (std::string::size_type pos = 0; inout.npos != (pos = inout.find(what.data(), pos, what.length())); pos += with.length(), ++count) {
            inout.replace(pos, what.length(), with.data(), with.length());
        }
        return count;
    }
    static inline bool isWhiteSpace(char c)
    {
        if (c == 0)
            return false;
        else
            return 0 != strchr(" \t\r\n", c);
    }
    static inline std::string quoteString(const std::string& str, const char* beginDelim, const char* endDelim)
    {
        std::stringstream ss;
        ss << beginDelim;
        for (int i = 0; i < str.length(); ++i) {
            char c = str[i];
            switch (c) {
            case '\\':
                ss << "\\\\";
                break;
            case '"':
                ss << "\\\"";
                break;
            case '\'':
                ss << "\\'";
                break;
            case '\0':
                ss << "\\\0";
                break;
            default:
                ss << c;
                break;
            }
        }
        ss << endDelim;
        return ss.str();
    }
    static inline void TryEmitStartCodeBlock(std::stringstream& ss, const char* delim, bool& codeBlockNeedClose)
    {
        if (!codeBlockNeedClose) {
            ss << "@@code";
            ss << std::endl;
            ss << delim;
            ss << std::endl;
            codeBlockNeedClose = true;
        }
    }
    static inline void TryEmitCloseCodeBlock(std::stringstream& ss, const char* delim, bool& codeBlockNeedClose)
    {
        if (codeBlockNeedClose) {
            ss << delim;
            ss << ';';
            ss << std::endl;
            codeBlockNeedClose = false;
        }
    }
    static inline bool SkipWhiteSpaces(const char* input, int len, int& ix)
    {
        bool isSkip = false;
        for (; ix < len && input[ix] != '\n' && isWhiteSpace(input[ix]); ++ix) {
            isSkip = true;
        }
        return isSkip;
    }
    static inline bool SkipComments(const char* input, int len, int& ix)
    {
        bool isSkip = false;
        //单行注释
        if (ix + 1 < len && input[ix] == '/' && input[ix + 1] == '/') {
            for (; ix < len && input[ix] != '\n'; ++ix);
            isSkip = true;
        }
        //多行注释
        if (ix + 1 < len && input[ix] == '/' && input[ix + 1] == '*') {
            ++ix;
            ++ix;
            for (; ix + 1 < len; ++ix) {
                if (input[ix] == '*' && input[ix + 1] == '/') {
                    ++ix;
                    ++ix;
                    break;
                }
            }
            isSkip = true;
        }
        return isSkip;
    }
    static bool IsSimpleDefine(const std::string& str)
    {
        for (int i = 0; i < str.length(); ++i) {
            char c = str[i];
            if (!::isalnum(c) && c != '_' && c != ' ' && c != '\t')
                return false;
        }
        return true;
    }
    static std::string TransformPreprocess(const char* input, int len, const char* beginDelim, const char* endDelim)
    {
        std::stringstream ss;
        std::stringstream tokenBuilder;
        bool codeBlockNeedClose = false;
        if (beginDelim && endDelim) {
            ss << "@@delimiter(script, \"" << beginDelim << "\", \"" << endDelim << "\");" << std::endl;
        }
        else {
            beginDelim = "{:";
            endDelim = ":}";
        }
        for (int i = 0; i < len; ++i) {
            char ch = input[i];
            switch (ch) {
            case '/': {
                TryEmitStartCodeBlock(ss, beginDelim, codeBlockNeedClose);
                ss << ch;
                if (i + 1 < len) {
                    char c = input[i + 1];
                    if (c == '/') {
                        ss << c;
                        for (int j = i + 2; j < len; ++j) {
                            c = input[j];
                            ss << c;
                            if (c == '\n') {
                                i = j;
                                break;
                            }
                            else if (j == len - 1) {
                                i = j;
                            }
                        }
                    }
                    else if (c == '*') {
                        ss << c;
                        char lc = '\0';
                        for (int j = i + 2; j < len; ++j) {
                            c = input[j];
                            ss << c;
                            if (lc == '*' && c == '/') {
                                i = j;
                                break;
                            }
                            lc = c;
                        }
                    }
                }
            }
                    break;
            case '\'':
            case '"': {
                TryEmitStartCodeBlock(ss, beginDelim, codeBlockNeedClose);
                ss << ch;
                for (int j = i + 1; j < len; ++j) {
                    char c = input[j];
                    ss << c;
                    if (c == '\\') {
                        ++j;
                        if (j < len) {
                            c = input[j];
                            ss << c;
                        }
                        else {
                            i = j - 1;
                            break;
                        }
                    }
                    else if (c == ch) {
                        i = j;
                        break;
                    }
                }
            }
                    break;
            case '#': {
                //预处理（define, undef, include, if, ifdef, ifndef, else, elif, elifdef, elifndef (since C++23), endif, line, error, pragma）
                int j = i + 1;
                tokenBuilder.str(std::string());
                bool isSkip = true;
                for (; isSkip && j < len;) {
                    bool s1 = SkipWhiteSpaces(input, len, j);
                    bool s2 = SkipComments(input, len, j);
                    isSkip = s1 || s2;
                }
                for (; j < len && ::isalpha(input[j]); ++j) {
                    tokenBuilder << input[j];
                }
                std::string key = tokenBuilder.str();
                tokenBuilder.str(std::string());
                std::string arg;
                for (; j < len && input[j] != '\n' && isWhiteSpace(input[j]); ++j);
                if (j < len && input[j] != '\n') {
                    bool isExpression = key == "define" || key.length() >= 2 && (key[0] == 'i' && key[1] == 'f' || key[0] == 'e' && key[1] == 'l' || key[0] == 'e' && key[1] == 'n');
                    char lc = '\0';
                    for (; j < len; ++j) {
                        SkipComments(input, len, j);
                        if (j >= len)
                            break;
                        char cc = input[j];
                        if (cc == '\r' && lc != '\\' || cc == '\n' && lc != '\r' && lc != '\\') {
                            arg = tokenBuilder.str();
                            trim(arg);
                            break;
                        }
                        if (isExpression && (cc == '"' || cc == '\'')) {
                            //字符串
                            tokenBuilder << cc;
                            ++j;
                            while (j + 1 < len && input[j] != cc) {
                                char c = input[j];
                                tokenBuilder << c;
                                ++j;
                                if (c == '\\') {
                                    tokenBuilder << input[j];
                                    ++j;
                                }
                            }
                            tokenBuilder << input[j];
                        }
                        else if (cc == '\\' && (input[j + 1] == '\r' || input[j + 1] == '\n')) {
                            //续行符不输出
                        }
                        else {
                            tokenBuilder << cc;
                        }
                        lc = input[j];
                    }
                }
                TryEmitCloseCodeBlock(ss, endDelim, codeBlockNeedClose);
                if (key.length() >= 2 && (key[0] == 'i' && key[1] == 'f' || key[0] == 'e' && key[1] == 'l' || key[0] == 'e' && key[1] == 'n')) {
                    //语句块
                    if (key[0] == 'i' && key[1] == 'f') {
                        ss << "@@";
                        ss << key;
                        ss << '(';
                        ss << arg;
                        ss << ')';
                        ss << std::endl;
                        ss << "{";
                        ss << std::endl;
                    }
                    else if (key[0] == 'e' && key[1] == 'l') {
                        ss << "}";
                        ss << std::endl;
                        ss << "@@";
                        ss << key;
                        ss << '(';
                        ss << arg;
                        ss << ')';
                        ss << std::endl;
                        ss << "{";
                        ss << std::endl;
                    }
                    else {
                        ss << "}";
                        ss << ';';
                        ss << std::endl;
                    }
                }
                else {
                    //函数
                    ss << "@@"; 
                    if (key.empty())
                        ss << "ignore";
                    else
                        ss << key;
                    ss << '(';
                    if (key == "define" && IsSimpleDefine(arg) || key == "undef") {
                        ss << key;
                    }
                    else {
                        std::string quoteArg = quoteString(arg, "\"", "\"");
                        ss << arg;
                    }
                    ss << arg;
                    ss << ')';
                    ss << ';';
                    ss << std::endl;
                }
                i = j;
            }
                    break;
            case ' ':
            case '\t':
            case '\r':
            case '\n':
                TryEmitStartCodeBlock(ss, beginDelim, codeBlockNeedClose);
                ss << ch;
                break;
            default:
                TryEmitStartCodeBlock(ss, beginDelim, codeBlockNeedClose);
                ss << ch;
                break;
            }
        }
        ss.seekg(-1, std::ios::end);
        if (!isWhiteSpace(ss.get())) {
            ss << std::endl;
        }
        TryEmitCloseCodeBlock(ss, endDelim, codeBlockNeedClose);
        return ss.str();
    }
}