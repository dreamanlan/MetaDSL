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
            mData.GetNullFunctionPtrRef() = mDataFile->GetNullFunctionPtr();
		}
		inline void    setEnvironmentObjRef(RealTypeT& thisObj)
		{
			mThis = &thisObj;
			MyAssert(mThis);
		}
	public:
        inline void    endStatement(void);
        inline void    buildOperator(void);
        inline void    buildFirstTernaryOperator(void);
        inline void    buildSecondTernaryOperator(void);
        inline void    beginStatement(void);
        inline void    addFunction(void);
        inline void    setFunctionId(void);
        inline void    markParenthesisParam(void);
        inline void    buildHighOrderFunction(void);
        inline void    markBracketParam(void);
        inline void    markQuestionParenthesisParam(void);
        inline void    markQuestionBracketParam(void);
        inline void    markQuestionBraceParam(void);
        inline void    markStatement(void);
        inline void    markExternScript(void);
        inline void    markBracketColonParam(void);
        inline void    markParenthesisColonParam(void);
        inline void    markAngleBracketColonParam(void);
        inline void    markBracePercentParam(void);
        inline void    markBracketPercentParam(void);
        inline void    markParenthesisPercentParam(void);
        inline void    markAngleBracketPercentParam(void);
        inline void    markColonColonParam(void);
        inline void    markColonColonParenthesisParam(void);
        inline void    markColonColonBracketParam(void);
        inline void    markColonColonBraceParam(void);
        inline void    setExternScript(void);
        inline void    markPeriodParam(void);
        inline void    setMemberId(void);
        inline void    markPeriodParenthesisParam(void);
        inline void    markPeriodBracketParam(void);
        inline void    markPeriodBraceParam(void);
        inline void    markQuestionPeriodParam(void);
        inline void    markPointerParam(void);
        inline void    markPeriodStarParam(void);
        inline void    markQuestionPeriodStarParam(void);
        inline void    markPointerStarParam(void);
	private:
		inline ISyntaxComponent& simplifyStatement(StatementData& data)const;
		inline ISyntaxComponent& simplifyStatement(FunctionData& data)const;
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