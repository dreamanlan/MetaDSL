#ifndef __ByteCode_H__
#define __ByteCode_H__

#include "Dsl.h"
#include "RuntimeBuilderData.h"
#include "tsnprintf.h"

namespace Dsl
{
	template<typename RealTypeT>
	class RuntimeBuilderT
	{
	public:
		RuntimeBuilderT(DslFile& dataFile) :mThis(NULL), mDataFile(&dataFile)
		{
			MyAssert(mDataFile);
		}
		inline void    setEnvironmentObjRef(RealTypeT& thisObj)
		{
			mThis = &thisObj;
			MyAssert(mThis);
		}
	public:
		inline void    beginStatement(void);
		inline void    endStatement(void);
		inline void    markOperator(void);
		inline void    buildOperator(void);
		inline void    buildFirstTernaryOperator(void);
		inline void    buildSecondTernaryOperator(void);
		inline void    beginFunction(void);
		inline void    endFunction(void);
		inline void    setFunctionId(void);
		inline void    markHaveStatement(void);
		inline void    markHaveExternScript(void);
		inline void    setExternScript(void);
		inline void    buildHighOrderFunction(void);
		inline void    markParenthesisParam(void);
		inline void    markBracketParam(void);
		inline void    markPeriod(void);
		inline void    markPeriodParam(void);
		inline void    setMemberId(void);
		inline void    markPeriodParenthesisParam(void);
		inline void    markPeriodBracketParam(void);
		inline void    markPeriodBraceParam(void);
		inline void    markQuestion(void);
		inline void    markQuestionPeriodParam(void);
		inline void    markQuestionParenthesisParam(void);
		inline void    markQuestionBracketParam(void);
		inline void    markQuestionBraceParam(void);
		inline void    markPointer(void);
		inline void    markPointerParam(void);
		inline void    markPeriodStarParam(void);
		inline void    markQuestionPeriodStarParam(void);
		inline void    markPointerStarParam(void);
	private:
		inline ISyntaxComponent& simplifyStatement(Statement& data)const;
		inline ISyntaxComponent& simplifyStatement(Function& data)const;
		inline ISyntaxComponent& simplifyStatement(Call& data)const;
		inline void simplifyStatementData(Statement& data)const;
		inline void simplifyFunctionData(Function& data)const;
		inline void simplifyCallData(Call& data)const;
		inline bool	preconditionCheck(void)const
		{
			return NULL != mThis && NULL != mDataFile;
		}
	protected:
		RuntimeBuilderData		        mData;
		DslFile*		                mDataFile;
		RealTypeT*						mThis;
	};
}

#include "ByteCode.inl"

#endif //__ByteCode_H__