#ifndef __RuntimeBuilderData_H__
#define __RuntimeBuilderData_H__

#include "Queue.h"

#define STACKSIZE			255

namespace Dsl
{
	class Function;
	class Statement;
	class DslFile;
	class Value;
}
class RuntimeBuilderData
{
public:
	enum
	{
		UNKNOWN_TOKEN = -1,
		ID_TOKEN = 0,
		NUM_TOKEN,
		STRING_TOKEN,
		BOOL_TOKEN,
	};
	struct TokenInfo
	{
		char*	mString;
		int mType;

		TokenInfo(void) :mString(0), mType(UNKNOWN_TOKEN)
		{}
		TokenInfo(char* pstr, int type) :mString(pstr), mType(type)
		{}
		int IsValid(void)const
		{
			if (UNKNOWN_TOKEN != mType)
				return TRUE;
			else
				return FALSE;
		}
		Dsl::Value ToValue(void)const;
	};
private:
	typedef DequeT<TokenInfo, STACKSIZE> TokenStack;
	typedef DequeT<Dsl::Statement*, STACKSIZE> SemanticStack;
public:
	RuntimeBuilderData(void);
public:
	void push(const TokenInfo& info);
	TokenInfo pop(void);
	int isSemanticStackEmpty(void)const;
	void pushStatement(Dsl::Statement* p);
	Dsl::Statement* popStatement(void);
	Dsl::Statement* getCurStatement(void)const;
	Dsl::Function*& getLastFunctionRef(void)const;
private:
	TokenStack		mTokenStack;
	SemanticStack	mSemanticStack;
};

#endif //__RuntimeBuilderData_H__