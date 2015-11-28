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
  inline char* getLastToken(void) const;
  inline int getLastLineNumber(void) const;
  inline void setCanFinish(int val);
public:
  ActionForSourceCodeScript(SlkToken &scanner, Dsl::DslFile& dataFile);
public:
  inline void    pushId(void);
  inline void    pushStr(void);
  inline void    pushNum(void);
  void    (ActionForSourceCodeScript::*Action[MAX_ACTION_NUM]) (void);
  inline void    initialize_table(void);
  inline void	execute(int  number)   { (this->*Action[number]) (); }
private:
  SlkToken   *mScanner;
};
//--------------------------------------------------------------------------------------
inline char* ActionForSourceCodeScript::getLastToken(void) const
{
  if (NULL != mScanner) {
    return mScanner->getLastToken();
  } else {
    return NULL;
  }
}
inline int ActionForSourceCodeScript::getLastLineNumber(void) const
{
  if (NULL != mScanner) {
    return mScanner->getLastLineNumber();
  } else {
    return -1;
  }
}
inline void ActionForSourceCodeScript::setCanFinish(int val)
{
  if (NULL != mScanner) {
    mScanner->setCanFinish(val);
  }
}
//--------------------------------------------------------------------------------------
//±êÊ¶·û
inline void ActionForSourceCodeScript::pushId(void)
{
  char* lastToken = getLastToken();
  if (NULL != lastToken) {
    mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::VARIABLE_TOKEN));
  }
}
inline void ActionForSourceCodeScript::pushNum(void)
{
  char* lastToken = getLastToken();
  if (NULL != lastToken) {
    mData.push(RuntimeBuilderData::TokenInfo(lastToken, RuntimeBuilderData::INT_TOKEN));
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