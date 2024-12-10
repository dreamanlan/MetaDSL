#include "RuntimeBuilderData.h"

#define BYTECODE_PRINTF	nullprintf

//--------------------------------------------------------------------------------------
DslParser::ValueData RuntimeBuilderData::TokenInfo::ToValue()const
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
    case DOLLAR_STRING_TOKEN:
    {
        char* pStr = mString;
        if (0 != pStr) {
            DslParser::ValueData val(pStr, DslParser::ValueData::VALUE_TYPE_DOLLAR_STRING);
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
RuntimeBuilderData::TokenInfo RuntimeBuilderData::pop()
{
    if (mTokenStack.Empty())
        return TokenInfo();
    TokenInfo info = mTokenStack.Back();
    mTokenStack.PopBack();
    return info;
}
int RuntimeBuilderData::isSemanticStackEmpty()const
{
    return mSemanticStack.Empty();
}
void RuntimeBuilderData::pushStatement(DslParser::StatementData* p)
{
    mSemanticStack.PushBack(p);
}
DslParser::StatementData* RuntimeBuilderData::popStatement()
{
    if (mSemanticStack.Empty()) {
        return 0;
    }
    DslParser::StatementData* cdata = mSemanticStack.Back();
    mSemanticStack.PopBack();
    return cdata;
}
DslParser::StatementData* RuntimeBuilderData::getCurStatement()const
{
    if (mSemanticStack.Empty())
        return 0;
    DslParser::StatementData* topData = mSemanticStack.Back();
    return topData;
}
DslParser::FunctionData* RuntimeBuilderData::getLastFunction()const
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
uint32_t RuntimeBuilderData::peekPairType()const
{
    if (mPairTypeStack.Empty())
        return IDslSyntaxCommon::PAIR_TYPE_NONE;
    return mPairTypeStack.Back();
}
void RuntimeBuilderData::pushPairType(uint32_t pairType)
{
    mPairTypeStack.PushBack(pairType);
}
uint32_t RuntimeBuilderData::popPairType()
{
    if (mPairTypeStack.Empty())
        return IDslSyntaxCommon::PAIR_TYPE_NONE;
    return mPairTypeStack.PopBack();
}
const RuntimeBuilderData::PairTypeStack& RuntimeBuilderData::getPairTypeStack()const
{
    return mPairTypeStack;
}
RuntimeBuilderData::PairTypeStack& RuntimeBuilderData::getPairTypeStack()
{
    return mPairTypeStack;
}
//--------------------------------------------------------------------------------------
RuntimeBuilderData::RuntimeBuilderData()
{
}