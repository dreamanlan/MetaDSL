﻿#ifndef __ByteCode_H__
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
        inline void    markSeparator();
        inline void    endStatement();
        inline void    buildOperator();
        inline void    buildFirstTernaryOperator();
        inline void    buildSecondTernaryOperator();
        inline void    beginStatement();
        inline void    addFunction();
        inline void    setFunctionId();
        inline void    buildNullableOperator();
        inline void    markParenthesesParam();
        inline void    markParenthesesParamEnd();
        inline void    buildHighOrderFunction();
        inline void    markBracketParam();
        inline void    markBracketParamEnd();
        inline void    markStatement();
        inline void    markStatementEnd();
        inline void    markExternScript();
        inline void    setExternScript();
        inline void    markBracketColonParam();
        inline void    markBracketColonParamEnd();
        inline void    markParenthesesColonParam();
        inline void    markParenthesesColonParamEnd();
        inline void    markAngleBracketColonParam();
        inline void    markAngleBracketColonParamEnd();
        inline void    markBracePercentParam();
        inline void    markBracePercentParamEnd();
        inline void    markBracketPercentParam();
        inline void    markBracketPercentParamEnd();
        inline void    markParenthesesPercentParam();
        inline void    markParenthesesPercentParamEnd();
        inline void    markAngleBracketPercentParam();
        inline void    markAngleBracketPercentParamEnd();
        inline void    markColonColonParam();
        inline void    markPeriodParam();
        inline void    markPointerParam();
        inline void    markPeriodStarParam();
        inline void    markPointerStarParam();
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