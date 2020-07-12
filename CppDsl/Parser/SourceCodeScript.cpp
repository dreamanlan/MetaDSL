#include "SourceCodeScript.h"
#include "SlkInc.h"
#include "SlkParse.h"
#include "ByteCode.h"

#define MAX_ACTION_NUM	37

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
	ActionForSourceCodeScript(SlkToken &scanner, Dsl::DslFile& dataFile);
public:
	inline void    pushId(void);
	inline void    pushStr(void);
	inline void    pushNum(void);
	inline void    pushTrue(void);
	inline void    pushFalse(void);
	void    (ActionForSourceCodeScript::*Action[MAX_ACTION_NUM]) (void);
	inline void    initialize_table(void);
	inline void 	 execute(int  number)   { (this->*Action[number]) (); }
private:
	SlkToken   *mScanner;
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
	if (NULL != mScanner){
		mScanner->setStringDelimiter(begin, end);
	}
}
inline void ActionForSourceCodeScript::setScriptDelimiter(const char* begin, const char* end)
{
	if (NULL != mScanner){
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
inline void ActionForSourceCodeScript::pushTrue(void)
{
	char* lastToken = getLastToken();
	if (NULL != lastToken) {
		mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::BOOL_TOKEN));
	}
}
inline void ActionForSourceCodeScript::pushFalse(void)
{
	char* lastToken = getLastToken();
	if (NULL != lastToken) {
		mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::BOOL_TOKEN));
	}
}
//--------------------------------------------------------------------------------------
inline ActionForSourceCodeScript::ActionForSourceCodeScript(SlkToken &scanner, Dsl::DslFile& dataFile) :mScanner(&scanner), BaseType(dataFile)
{
	initialize_table();
	setEnvironmentObjRef(*this);
}
//--------------------------------------------------------------------------------------
inline void ActionForSourceCodeScript::initialize_table(void)
{
	Action[0] = 0;
	Action[1] = &ActionForSourceCodeScript::endStatement;
	Action[2] = &ActionForSourceCodeScript::markOperator;
	Action[3] = &ActionForSourceCodeScript::pushId;
	Action[4] = &ActionForSourceCodeScript::buildOperator;
	Action[5] = &ActionForSourceCodeScript::buildFirstTernaryOperator;
	Action[6] = &ActionForSourceCodeScript::buildSecondTernaryOperator;
	Action[7] = &ActionForSourceCodeScript::beginStatement;
	Action[8] = &ActionForSourceCodeScript::beginFunction;
	Action[9] = &ActionForSourceCodeScript::endFunction;
	Action[10] = &ActionForSourceCodeScript::setFunctionId;
	Action[11] = &ActionForSourceCodeScript::markParenthesisParam;
	Action[12] = &ActionForSourceCodeScript::buildHighOrderFunction;
	Action[13] = &ActionForSourceCodeScript::markBracketParam;
	Action[14] = &ActionForSourceCodeScript::markPeriod;
	Action[15] = &ActionForSourceCodeScript::markQuestion;
	Action[16] = &ActionForSourceCodeScript::markQuestionParenthesisParam;
	Action[17] = &ActionForSourceCodeScript::markQuestionBracketParam;
	Action[18] = &ActionForSourceCodeScript::markQuestionBraceParam;
	Action[19] = &ActionForSourceCodeScript::markPointer;
    Action[20] = &ActionForSourceCodeScript::markStatement;
    Action[21] = &ActionForSourceCodeScript::markExternScript;
    Action[22] = &ActionForSourceCodeScript::setExternScript;
	Action[23] = &ActionForSourceCodeScript::markPeriodParam;
	Action[24] = &ActionForSourceCodeScript::setMemberId;
	Action[25] = &ActionForSourceCodeScript::markPeriodParenthesisParam;
	Action[26] = &ActionForSourceCodeScript::markPeriodBracketParam;
	Action[27] = &ActionForSourceCodeScript::markPeriodBraceParam;
	Action[28] = &ActionForSourceCodeScript::markQuestionPeriodParam;
	Action[29] = &ActionForSourceCodeScript::markPointerParam;
	Action[30] = &ActionForSourceCodeScript::markPeriodStarParam;
	Action[31] = &ActionForSourceCodeScript::markQuestionPeriodStarParam;
	Action[32] = &ActionForSourceCodeScript::markPointerStarParam;
	Action[33] = &ActionForSourceCodeScript::pushStr;
	Action[34] = &ActionForSourceCodeScript::pushNum;
	Action[35] = &ActionForSourceCodeScript::pushTrue;
	Action[36] = &ActionForSourceCodeScript::pushFalse;
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
		SlkToken tokens(source, file.GetErrorAndStringBuffer());
		SlkError error(tokens, file.GetErrorAndStringBuffer());
		ActionForSourceCodeScript action(tokens, file);
		SlkParse(action, tokens, error, 0);
	}
}