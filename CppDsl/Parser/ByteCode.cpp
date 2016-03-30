#include "ByteCode.h"
#include "Dsl.h"

class TestRuntimeBuilder : public RuntimeBuilderT < TestRuntimeBuilder >
{
  typedef RuntimeBuilderT<TestRuntimeBuilder> BaseType;
public:
  char* getLastToken(void) const{ return ""; }
  int getLastLineNumber(void) const{ return 0; }
  void setCanFinish(int val){}
  void setStringDelimiter(const char* delimiter){}
  void setScriptDelimiter(const char* delimiter){}
public:
  TestRuntimeBuilder(DslFile& dataFile) :BaseType(dataFile)
  {}
};

void CompileTest_ByteCode(void)
{
  DslFile dataFile;
  TestRuntimeBuilder builder(dataFile);
  builder.beginFunction();
  builder.beginStatement();
  builder.buildFirstTernaryOperator();
  builder.buildHighOrderFunction();
  builder.buildOperator();
  builder.buildSecondTernaryOperator();
  builder.endFunction();
  builder.endStatement();
  builder.markBracketParam();
  builder.markHaveExternScript();
  builder.markHaveStatement();
  builder.markParenthesisParam();
  builder.markPeriodBraceParam();
  builder.markPeriodBracketParam();
  builder.markPeriodParam();
  builder.markPeriodParenthesisParam();
  builder.setMemberId();
  builder.setCanFinish(false);
  builder.setExternScript();
  builder.setFunctionId();
  builder.setMemberId();
}