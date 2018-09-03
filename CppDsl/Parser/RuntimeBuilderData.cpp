#include "RuntimeBuilderData.h"
#include "Dsl.h"

#define BYTECODE_PRINTF	nullprintf

//--------------------------------------------------------------------------------------
Dsl::Value RuntimeBuilderData::TokenInfo::ToValue(void)const
{
	switch (mType) {
	case ID_TOKEN:
	{
		char* pStr = mString;
		if (0 != pStr) {
			Value val(pStr, Value::TYPE_IDENTIFIER);
			return val;
		}
	}
	break;
	case NUM_TOKEN:
	{
		char* pStr = mString;
		if (0 != pStr) {
			Value val(pStr, Value::TYPE_NUM);
			return val;
		}
	}
	break;
	case STRING_TOKEN:
	{
		char* pStr = mString;
		if (0 != pStr) {
			Value val(pStr, Value::TYPE_STRING);
			return val;
		}
	}
	break;
	case BOOL_TOKEN:
	{
		char* pStr = mString;
		if (0 != pStr) {
			Value val(pStr, Value::TYPE_BOOL);
			return val;
		}
	}
	break;
	}
	return Value();
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
void RuntimeBuilderData::pushStatement(Dsl::Statement* p)
{
	mSemanticStack.PushBack(p);
}
Dsl::Statement* RuntimeBuilderData::popStatement(void)
{
	if (mSemanticStack.Empty()) {
		return 0;
	}
	Statement* cdata = mSemanticStack.Back();
	mSemanticStack.PopBack();
	return cdata;
}
Dsl::Statement* RuntimeBuilderData::getCurStatement(void)const
{
	if (mSemanticStack.Empty())
		return 0;
	Statement* topData = mSemanticStack.Back();
	return topData;
}
Dsl::Function*& RuntimeBuilderData::getLastFunctionRef(void)const
{
	Statement* statement = getCurStatement();
	if (0 != statement)
		return statement->GetLastFunctionRef();
	else
		return Function::GetNullFunctionPtrRef();
}
//--------------------------------------------------------------------------------------
RuntimeBuilderData::RuntimeBuilderData(void)
{
}