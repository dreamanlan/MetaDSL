#include "RuntimeBuilderData.h"

#define BYTECODE_PRINTF	nullprintf

//--------------------------------------------------------------------------------------
DslParser::ValueData RuntimeBuilderData::TokenInfo::ToValue(void)const
{
    switch (mType) {
    case ID_TOKEN:
    {
        char* pStr = mString;
        if (0 != pStr) {
            DslParser::ValueData val(pStr, DslParser::ValueData::VALUE_TYPE_IDENTIFIER);
            return val;
        }
    }
    break;
    case NUM_TOKEN:
    {
        char* pStr = mString;
        if (0 != pStr) {
            DslParser::ValueData val(pStr, DslParser::ValueData::VALUE_TYPE_NUM);
            return val;
        }
    }
    break;
    case STRING_TOKEN:
    {
        char* pStr = mString;
        if (0 != pStr) {
            DslParser::ValueData val(pStr, DslParser::ValueData::VALUE_TYPE_STRING);
            return val;
        }
    }
    break;
    }
    return DslParser::ValueData();
}
//--------------------------------------------------------------------------------------
void RuntimeBuilderData::push(const TokenInfo& info)
{
    mTokenStack.PushBack(info);
}
RuntimeBuilderData::TokenInfo RuntimeBuilderData::pop(void)
{
    if (mTokenStack.Empty())
        return TokenInfo();
    TokenInfo info = mTokenStack.Back();
    mTokenStack.PopBack();
    return info;
}
int RuntimeBuilderData::isSemanticStackEmpty(void)const
{
    return mSemanticStack.Empty();
}
void RuntimeBuilderData::pushStatement(DslParser::StatementData* p)
{
    mSemanticStack.PushBack(p);
}
DslParser::StatementData* RuntimeBuilderData::popStatement(void)
{
    if (mSemanticStack.Empty()) {
        return 0;
    }
    DslParser::StatementData* cdata = mSemanticStack.Back();
    mSemanticStack.PopBack();
    return cdata;
}
DslParser::StatementData* RuntimeBuilderData::getCurStatement(void)const
{
    if (mSemanticStack.Empty())
        return 0;
    DslParser::StatementData* topData = mSemanticStack.Back();
    return topData;
}
DslParser::FunctionData* RuntimeBuilderData::getLastFunction(void)const
{
    DslParser::StatementData* statement = getCurStatement();
    if (0 != statement) {
        auto* f = statement->GetLastFunctionRef();
        if (f->IsFunction())
            return reinterpret_cast<DslParser::FunctionData*>(f);
        else
            return GetNullFunctionPtrRef();
    }
    else {
        return GetNullFunctionPtrRef();
    }
}
void RuntimeBuilderData::setLastFunction(DslParser::FunctionData* p)const
{
    DslParser::StatementData* statement = getCurStatement();
    if (0 != statement) {     
        auto*& f = statement->GetLastFunctionRef();
        f = p;
    }
}
//--------------------------------------------------------------------------------------
RuntimeBuilderData::RuntimeBuilderData(void)
{
}