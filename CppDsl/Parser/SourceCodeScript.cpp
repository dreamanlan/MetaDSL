#include "SourceCodeScript.h"
#include "SlkInc.h"
#include "SlkParse.h"
#include "ByteCode.h"

#define MAX_ACTION_NUM	23

//--------------------------------------------------------------------------------------
class ActionForSourceCodeScript : public SlkAction, public RuntimeBuilderT < ActionForSourceCodeScript >
{
  typedef RuntimeBuilderT<ActionForSourceCodeScript> BaseType;
public:
  inline CHAR* getLastToken(void) const;
  inline INT getLastLineNumber(void) const;
  inline void setCanFinish(BOOL val);
public:
  ActionForSourceCodeScript(SlkToken &scanner, Dsl::DslFile& dataFile);
public:
  inline void    pushId(void);
  inline void    pushStr(void);
  inline void    pushNum(void);
  void    (ActionForSourceCodeScript::*Action[MAX_ACTION_NUM]) (void);
  inline void    initialize_table(void);
  inline void	execute(INT  number)   { (this->*Action[number]) (); }
private:
  SlkToken   *mScanner;
};
//--------------------------------------------------------------------------------------
inline CHAR* ActionForSourceCodeScript::getLastToken(void) const
{
  if (NULL != mScanner) {
    return mScanner->getLastToken();
  } else {
    return NULL;
  }
}
inline INT ActionForSourceCodeScript::getLastLineNumber(void) const
{
  if (NULL != mScanner) {
    return mScanner->getLastLineNumber();
  } else {
    return -1;
  }
}
inline void ActionForSourceCodeScript::setCanFinish(BOOL val)
{
  if (NULL != mScanner) {
    mScanner->setCanFinish(val);
  }
}
//--------------------------------------------------------------------------------------
//±êÊ¶·û
inline void ActionForSourceCodeScript::pushId(void)
{
  CHAR* lastToken = getLastToken();
  if (NULL != lastToken) {
    mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::VARIABLE_TOKEN));
  }
}
inline void ActionForSourceCodeScript::pushNum(void)
{
  CHAR* lastToken = getLastToken();
  if (NULL != lastToken) {
    mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::INT_TOKEN));
  }
}
inline void ActionForSourceCodeScript::pushStr(void)
{
  CHAR* lastToken = getLastToken();
  if (NULL != lastToken) {
    mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::STRING_TOKEN));
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
  Action[2] = &ActionForSourceCodeScript::pushId;
  Action[3] = &ActionForSourceCodeScript::buildOperator;
  Action[4] = &ActionForSourceCodeScript::buildFirstTernaryOperator;
  Action[5] = &ActionForSourceCodeScript::buildSecondTernaryOperator;
  Action[6] = &ActionForSourceCodeScript::beginStatement;
  Action[7] = &ActionForSourceCodeScript::beginFunction;
  Action[8] = &ActionForSourceCodeScript::endFunction;
  Action[9] = &ActionForSourceCodeScript::setFunctionId;
  Action[10] = &ActionForSourceCodeScript::markHaveStatement;
  Action[11] = &ActionForSourceCodeScript::markHaveExternScript;
  Action[12] = &ActionForSourceCodeScript::setExternScript;
  Action[13] = &ActionForSourceCodeScript::markParenthesisParam;
  Action[14] = &ActionForSourceCodeScript::buildHighOrderFunction;
  Action[15] = &ActionForSourceCodeScript::markBracketParam;
  Action[16] = &ActionForSourceCodeScript::markPeriodParam;
  Action[17] = &ActionForSourceCodeScript::setMemberId;
  Action[18] = &ActionForSourceCodeScript::markPeriodParenthesisParam;
  Action[19] = &ActionForSourceCodeScript::markPeriodBracketParam;
  Action[20] = &ActionForSourceCodeScript::markPeriodBraceParam;
  Action[21] = &ActionForSourceCodeScript::pushStr;
  Action[22] = &ActionForSourceCodeScript::pushNum;
}
//--------------------------------------------------------------------------------------

namespace Dsl
{
  class CachedScriptSource : public IScriptSource
  {
  public:
    explicit CachedScriptSource(const CHAR* p) :m_Source(p)
    {}
  protected:
    virtual BOOL Load(void)
    {
      return FALSE;
    }
    virtual const CHAR* GetBuffer(void)const
    {
      return m_Source;
    }
  private:
    const CHAR* m_Source;
  };
  //------------------------------------------------------------------------------------------------------
  void SourceCodeScript::Parse(const CHAR* buf)
  {
    if (0 == buf)
      return;
    CachedScriptSource source(buf);
    Parse(source);
  }

  void SourceCodeScript::Parse(IScriptSource& source)
  {
    mDataFile.ClearErrorInfo();
    SlkToken tokens(source, mDataFile.GetErrorAndStringBuffer());
    SlkError error(tokens, mDataFile.GetErrorAndStringBuffer());
    ActionForSourceCodeScript action(tokens, mDataFile);
    SlkParse(action, tokens, error, 0);
  }
}