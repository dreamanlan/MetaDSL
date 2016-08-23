#include "ByteCode.h"
#include "Dsl.h"

class TestRuntimeBuilder : public RuntimeBuilderT < TestRuntimeBuilder >
{
  typedef RuntimeBuilderT<TestRuntimeBuilder> BaseType;
public:
  char* getLastToken(void) const{ return ""; }
  int getLastLineNumber(void) const{ return 0; }
  int getCommentNum(int& commentOnNewLine) const { return 0; }
  char* getComment(int index) const { return ""; }
  void resetComments(void) {}
  void setCanFinish(int val){}
  void setStringDelimiter(const char* begin, const char* end){}
  void setScriptDelimiter(const char* begin, const char* end){}
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