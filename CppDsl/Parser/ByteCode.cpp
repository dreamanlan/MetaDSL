#include "ByteCode.h"
#include "DslParser.h"

using namespace DslParser;

class TestRuntimeBuilder : public RuntimeBuilderT < TestRuntimeBuilder >
{
    using BaseType = RuntimeBuilderT<TestRuntimeBuilder>;
public:
    char* getLastToken() const { return const_cast<char*>(""); }
    int getLastLineNumber() const { return 0; }
    int getCommentNum([[maybe_unused]] int& commentOnNewLine) const { return 0; }
    char* getComment([[maybe_unused]] int index) const { return const_cast<char*>(""); }
    void resetComments() {}
    void setCanFinish([[maybe_unused]] int val) {}
    void setStringDelimiter([[maybe_unused]] const char* begin, [[maybe_unused]] const char* end) {}
    void setScriptDelimiter([[maybe_unused]] const char* begin, [[maybe_unused]] const char* end) {}
public:
    TestRuntimeBuilder(DslFile& dataFile) :BaseType(dataFile)
    {}
};

void CompileTest_ByteCode()
{
    DslStringAndObjectBufferT<> buffer;
    DslFile dataFile(buffer);
    TestRuntimeBuilder builder(dataFile);
    builder.addFunction();
    builder.beginStatement();
    builder.buildFirstTernaryOperator();
    builder.buildHighOrderFunction();
    builder.buildOperator();
    builder.buildSecondTernaryOperator();
    builder.endStatement();
    builder.markBracketParam();
    builder.markStatement();
    builder.markExternScript();
    builder.markBracketColonParam();
    builder.markParenthesisColonParam();
    builder.markAngleBracketColonParam();
    builder.markBracePercentParam();
    builder.markBracketPercentParam();
    builder.markParenthesisPercentParam();
    builder.markAngleBracketPercentParam();
    builder.setExternScript();
    builder.markParenthesisParam();
    builder.markPeriodParam();
    builder.setCanFinish(false);
    builder.setFunctionId();
    builder.markPointerParam();
    builder.markPeriodStarParam();
    builder.markPointerStarParam();
}