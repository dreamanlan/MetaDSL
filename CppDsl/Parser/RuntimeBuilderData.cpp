#include "RuntimeBuilderData.h"

#define BYTECODE_PRINTF	nullprintf

//--------------------------------------------------------------------------------------
Dsl::ValueData RuntimeBuilderData::TokenInfo::ToValue(void)const
{
	switch (mType) {
	case ID_TOKEN:
	{
		char* pStr = mString;
		if (0 != pStr) {
			ValueData val(pStr, ValueData::TYPE_IDENTIFIER);
			return val;
		}
	}
	break;
	case NUM_TOKEN:
	{
		char* pStr = mString;
		if (0 != pStr) {
			ValueData val(pStr, ValueData::TYPE_NUM);
			return val;
		}
	}
	break;
	case STRING_TOKEN:
	{
		char* pStr = mString;
		if (0 != pStr) {
			ValueData val(pStr, ValueData::TYPE_STRING);
			return val;
		}
	}
	break;
	case BOOL_TOKEN:
	{
		char* pStr = mString;
		if (0 != pStr) {
			ValueData val(pStr, ValueData::TYPE_BOOL);
			return val;
		}
	}
	break;
	}
	return ValueData();
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
void RuntimeBuilderData::pushStatement(Dsl::StatementData* p)
{
	mSemanticStack.PushBack(p);
}
Dsl::StatementData* RuntimeBuilderData::popStatement(void)
{
	if (mSemanticStack.Empty()) {
		return 0;
	}
	StatementData* cdata = mSemanticStack.Back();
	mSemanticStack.PopBack();
	return cdata;
}
Dsl::StatementData* RuntimeBuilderData::getCurStatement(void)const
{
	if (mSemanticStack.Empty())
		return 0;
	StatementData* topData = mSemanticStack.Back();
	return topData;
}
Dsl::FunctionData*& RuntimeBuilderData::getLastFunctionRef(void)const
{
	StatementData* statement = getCurStatement();
	if (0 != statement)
		return statement->GetLastFunctionRef();
	else
		return GetNullFunctionPtrRef();
}
//--------------------------------------------------------------------------------------
RuntimeBuilderData::RuntimeBuilderData(void)
{
}