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
    DslStringAndObjectBuffer<> buffer;
	DslFile dataFile(buffer);
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
	builder.markStatement();
	builder.markExternScript();
	builder.setExternScript();
	builder.markParenthesisParam();
	builder.markPeriodBraceParam();
	builder.markPeriodBracketParam();
	builder.markPeriodParam();
	builder.markPeriodParenthesisParam();
	builder.setMemberId();
	builder.setCanFinish(false);
	builder.setFunctionId();
	builder.setMemberId();
    builder.markQuestionPeriodParam();
    builder.markQuestionParenthesisParam();
    builder.markQuestionBracketParam();
    builder.markQuestionBraceParam();
    builder.markPointerParam();
    builder.markPeriodStarParam();
    builder.markQuestionPeriodStarParam();
    builder.markPointerStarParam();
}