#ifndef __ByteCode_H__
#define __ByteCode_H__

#include "DslParser.h"
#include "RuntimeBuilderData.h"
#include "tsnprintf.h"

namespace DslParser
{
    template<typename RealTypeT>
    class RuntimeBuilderT
    {
    public:
        RuntimeBuilderT(DslFile& dataFile) :mThis(nullptr), mDataFile(&dataFile), mApi()
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
        inline void    markSeparator(void);
        inline void    endStatement(void);
        inline void    buildOperator(void);
        inline void    buildFirstTernaryOperator(void);
        inline void    buildSecondTernaryOperator(void);
        inline void    beginStatement(void);
        inline void    addFunction(void);
        inline void    setFunctionId(void);
        inline void    buildNullableOperator(void);
        inline void    markParenthesisParam(void);
        inline void    markParenthesisParamEnd(void);
        inline void    buildHighOrderFunction(void);
        inline void    markBracketParam(void);
        inline void    markBracketParamEnd(void);
        inline void    markStatement(void);
        inline void    markStatementEnd(void);
        inline void    markExternScript(void);
        inline void    setExternScript(void);
        inline void    markBracketColonParam(void);
        inline void    markBracketColonParamEnd(void);
        inline void    markParenthesisColonParam(void);
        inline void    markParenthesisColonParamEnd(void);
        inline void    markAngleBracketColonParam(void);
        inline void    markAngleBracketColonParamEnd(void);
        inline void    markBracePercentParam(void);
        inline void    markBracePercentParamEnd(void);
        inline void    markBracketPercentParam(void);
        inline void    markBracketPercentParamEnd(void);
        inline void    markParenthesisPercentParam(void);
        inline void    markParenthesisPercentParamEnd(void);
        inline void    markAngleBracketPercentParam(void);
        inline void    markAngleBracketPercentParamEnd(void);
        inline void    markColonColonParam(void);
        inline void    markPeriodParam(void);
        inline void    markPointerParam(void);
        inline void    markPeriodStarParam(void);
        inline void    markPointerStarParam(void);
    public:
        inline int     peekPairTypeStack()const { uint32_t tag = 0; return peekPairTypeStack(tag); }
        inline int     peekPairTypeStack(uint32_t& tag)const;
        inline int     getPairTypeStackSize()const;
        inline int     peekPairTypeStack(int ix)const { uint32_t tag = 0; return peekPairTypeStack(ix, tag); }
        inline int     peekPairTypeStack(int ix, uint32_t& tag)const;
    private:
        inline void    pushPairType(int type) { pushPairType(type, 0); };
        inline void    pushPairType(int type, uint32_t tag);
        inline void    popPairType();
    public:
        RuntimeBuilderData& getRuntimeBuilderData() { return mData; }
        const RuntimeBuilderData& getRuntimeBuilderData()const { return mData; }
    private:
        inline ISyntaxComponent& simplifyStatement(StatementData& data)const;
        inline ValueOrFunctionData& simplifyStatement(FunctionData& data)const;
        inline void simplifyFunction(FunctionData& data)const;
        inline bool	preconditionCheck()const
        {
            return nullptr != mThis && nullptr != mDataFile;
        }
    protected:
        RuntimeBuilderData mData;
        DslActionApi mApi;
        DslFile* mDataFile;
        RealTypeT* mThis;
    };
}

#include "ByteCode.inl"

#endif //__ByteCode_H__