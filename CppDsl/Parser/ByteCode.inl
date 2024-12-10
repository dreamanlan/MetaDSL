//--------------------------------------------------------------------------------------
//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
//--------------------------------------------------------------------------------------

#define PRINT_FUNCTION_SCRIPT_DEBUG_INFO printf

namespace DslParser
{
    /*
    * Memo: Why use reduction instead of delayed one-time construction
    * 1. We have tried to use a temporary structure such as SyntaxMaterial to collect data during the syntax parsing process, and then construct the statement when the statement is completed.
    * 2. The temporary structure is very similar to the final semantic data structure. It also needs to represent the recursive structure and be associated with the existing semantic data. The code is repeated and the logic is not clear enough.
    * 3. The reduction method has tried its best to reuse the instances constructed in the grammar parsing, and basically does not cause additional memory usage.
    * 4. In the reduction mode, the final memory usage is linearly related to the script complexity, so there is no need to worry about taking up too much memory.
    * 5. The definition of semantic data takes degradation situations into consideration and tries not to occupy additional space except for necessary data.
    */
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::setExternScript()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 != p) {
            char* pStr = mThis->getLastToken();
            if (0 != pStr) {
                if (mDataFile->IsDebugInfoEnable()) {
                    PRINT_FUNCTION_SCRIPT_DEBUG_INFO("script:%s\n", pStr);
                }

                ValueData* pVal = mDataFile->AddNewValueComponent();
                pVal->SetString(pStr);
                p->AddParam(pVal);
            }
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::buildOperator()
    {
        if (!preconditionCheck())return;
        RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
        if (TRUE != tokenInfo.IsValid())return;

        if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("op:%s\n", tokenInfo.mString);
        }

        StatementData* pArg = mData.getCurStatement();
        if (0 == pArg)
            return;
        if (!mDataFile->OnBeforeBuildOperator.isNull()) {
            mDataFile->OnBeforeBuildOperator(mApi, IDslSyntaxCommon::OPERATOR_CATEGORY_NORMAL, tokenInfo.mString, pArg);
        }
        pArg = mData.popStatement();
        if (0 == pArg)
            return;
        if (!mDataFile->OnBuildOperator.isNull()) {
            mDataFile->OnBuildOperator(mApi, IDslSyntaxCommon::OPERATOR_CATEGORY_NORMAL, tokenInfo.mString, pArg);
            if (0 == pArg)
                return;
        }

        ISyntaxComponent& argComp = simplifyStatement(*pArg);

        StatementData* pStatement = mDataFile->AddNewStatementComponent();
        if (0 == pStatement)
            return;

        pStatement->CopyFirstComments(argComp);
        argComp.ClearFirstComments();

        mData.pushStatement(pStatement);

        FunctionData* p = mDataFile->AddNewFunctionComponent();
        if (0 != p) {
            FunctionData& call = *p;
            if (0 != tokenInfo.mString && tokenInfo.mString[0] == '`') {
                call.SetParamClass(FunctionData::PARAM_CLASS_WRAP_INFIX_CALL_MASK | FunctionData::PARAM_CLASS_OPERATOR);

                ValueData v = call.GetName();
                ValueData op(tokenInfo.mString + 1, ValueData::VALUE_TYPE_IDENTIFIER);
                op.SetLine(mThis->getLastLineNumber());
                call.SetName(op);
            }
            else {
                call.SetParamClass(FunctionData::PARAM_CLASS_OPERATOR);

                ValueData v = call.GetName();
                ValueData op(tokenInfo.mString, ValueData::VALUE_TYPE_IDENTIFIER);
                op.SetLine(mThis->getLastLineNumber());
                call.SetName(op);
            }
            if (argComp.IsValid()) {
                call.AddParam(&argComp);
            }

            pStatement->AddFunction(p);
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::buildFirstTernaryOperator()
    {
        if (!preconditionCheck())return;
        RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
        if (TRUE != tokenInfo.IsValid())return;

        if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("op1/2:%s\n", tokenInfo.mString);
        }

        StatementData* pArg = mData.getCurStatement();
        if (0 == pArg)
            return;
        if (!mDataFile->OnBeforeBuildOperator.isNull()) {
            mDataFile->OnBeforeBuildOperator(mApi, IDslSyntaxCommon::OPERATOR_CATEGORY_TERNARY, tokenInfo.mString, pArg);
        }
        pArg = mData.popStatement();
        if (0 == pArg)
            return;
        if (!mDataFile->OnBuildOperator.isNull()) {
            mDataFile->OnBuildOperator(mApi, IDslSyntaxCommon::OPERATOR_CATEGORY_TERNARY, tokenInfo.mString, pArg);
            if (0 == pArg)
                return;
        }

        ISyntaxComponent& argComp = simplifyStatement(*pArg);
        StatementData* pStatement = mDataFile->AddNewStatementComponent();
        if (0 == pStatement)
            return;

        pStatement->CopyFirstComments(argComp);
        argComp.ClearFirstComments();

        mData.pushStatement(pStatement);
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_QUESTION_COLON);

        FunctionData* p = mDataFile->AddNewFunctionComponent();
        if (0 != p) {
            //The ternary operator is expressed as op1(cond)(true_val)op2(false_val)
            FunctionData* lowerOrderFunction = mDataFile->AddNewFunctionComponent();
            p->GetName().SetFunction(lowerOrderFunction);
            p->SetParamClass(FunctionData::PARAM_CLASS_TERNARY_OPERATOR);
            lowerOrderFunction->SetParamClass(FunctionData::PARAM_CLASS_PARENTHESIS);

            ValueData op(tokenInfo.mString, ValueData::VALUE_TYPE_IDENTIFIER);
            op.SetLine(mThis->getLastLineNumber());
            lowerOrderFunction->SetName(op);
            if (argComp.IsValid()) {
                lowerOrderFunction->AddParam(&argComp);
            }

            pStatement->AddFunction(p);
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::buildSecondTernaryOperator()
    {
        if (!preconditionCheck())return;
        RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
        if (TRUE != tokenInfo.IsValid())return;

        if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("op2/2:%s\n", tokenInfo.mString);
        }

        StatementData* statement = mData.getCurStatement();
        if (0 != statement) {
            if (!mDataFile->OnBeforeBuildOperator.isNull()) {
                mDataFile->OnBeforeBuildOperator(mApi, IDslSyntaxCommon::OPERATOR_CATEGORY_TERNARY, tokenInfo.mString, statement);
                statement = mData.getCurStatement();
            }

            popPairType();

            if (0 != statement) {
                FunctionData* p = mDataFile->AddNewFunctionComponent();
                if (0 != p) {
                    FunctionData& call = *p;
                    call.SetParamClass(FunctionData::PARAM_CLASS_TERNARY_OPERATOR);

                    ValueData op(tokenInfo.mString, ValueData::VALUE_TYPE_IDENTIFIER);
                    op.SetLine(mThis->getLastLineNumber());
                    call.SetName(op);

                    statement->AddFunction(p);
                }
            }
        }
    }
    //--------------------------------------------------------------------------------------
    static inline int calcSeparator(const char* tok)
    {
        if(nullptr==tok)
            return IDslSyntaxCommon::SEPARATOR_NOTHING;
        else if (tok[0] == ',' && tok[1] == '\0')
            return IDslSyntaxCommon::SEPARATOR_COMMA;
        else if (tok[0] == ';' && tok[1] == '\0')
            return IDslSyntaxCommon::SEPARATOR_SEMICOLON;
        else
            return IDslSyntaxCommon::SEPARATOR_NOTHING;
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markSeparator()
    {
        if (!preconditionCheck())return;

        RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
        if (TRUE != tokenInfo.IsValid())return;

        if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("sep:%s\n", tokenInfo.mString);
        }

        if (mData.isSemanticStackEmpty()) {
            int dslNum = mDataFile->GetDslInfoNum();
            if (dslNum > 0) {
                auto* pDslInfo = mDataFile->GetDslInfo(dslNum - 1);
                if (nullptr != pDslInfo) {
                    pDslInfo->SetSeparator(calcSeparator(tokenInfo.mString));
                }
            }
        }
        else {
            auto* pFunc = mData.getLastFunction();
            if (nullptr != pFunc) {
                int paramNum = pFunc->GetParamNum();
                if (paramNum > 0) {
                    auto* pParam = pFunc->GetParam(paramNum - 1);
                    if (nullptr != pParam) {
                        pParam->SetSeparator(calcSeparator(tokenInfo.mString));
                    }
                }
            }
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::beginStatement()
    {
        if (!preconditionCheck())return;
        StatementData* p = mDataFile->AddNewStatementComponent();
        if (0 == p)
            return;

        int commentOnNewLine;
        int num = mThis->getCommentNum(commentOnNewLine);
        if (num > 0 && p->GetFirstCommentNum() <= 0) {
            p->SetFirstCommentOnNewLine(commentOnNewLine);
        }
        for (int ix = 0; ix < num; ++ix) {
            char* cmt = mThis->getComment(ix);
            p->AddFirstComment(cmt);
        }
        mThis->resetComments();

        mData.pushStatement(p);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::endStatement()
    {
        if (!preconditionCheck())return;
        if (!mDataFile->OnBeforeEndStatement.isNull()) {
            StatementData* pStm = mData.getCurStatement();
            if (0 == pStm)
                return;
            mDataFile->OnBeforeEndStatement(mApi, pStm);
        }
        StatementData* statement = mData.popStatement();
        if (0 == statement)
            return;

        auto&& lastFunc = statement->GetLast()->AsFunction();
        if (nullptr != lastFunc) {
            switch (lastFunc->GetParamClassUnmasked()) {
            case IDslSyntaxCommon::PARAM_CLASS_PARENTHESIS:
            case IDslSyntaxCommon::PARAM_CLASS_BRACKET:
            case IDslSyntaxCommon::PARAM_CLASS_STATEMENT:
            case IDslSyntaxCommon::PARAM_CLASS_PARENTHESIS_COLON:
            case IDslSyntaxCommon::PARAM_CLASS_BRACKET_COLON:
            case IDslSyntaxCommon::PARAM_CLASS_ANGLE_BRACKET_COLON:
            case IDslSyntaxCommon::PARAM_CLASS_PARENTHESIS_PERCENT:
            case IDslSyntaxCommon::PARAM_CLASS_BRACKET_PERCENT:
            case IDslSyntaxCommon::PARAM_CLASS_BRACE_PERCENT:
            case IDslSyntaxCommon::PARAM_CLASS_ANGLE_BRACKET_PERCENT:
                popPairType();
                break;
            }
        }

        if (!mDataFile->OnEndStatement.isNull()) {
            mDataFile->OnEndStatement(mApi, statement);
            if (0 == statement)
                return;
        }
        auto* f = statement->GetLastFunctionRef();
        const char* id = f->GetId();
        auto* func = f->AsFunction();
        if (0 != id && strcmp(id, "@@delimiter") == 0 && statement->GetFunctionNum() == 1 && nullptr != func && (func->GetParamNum() == 1 || func->GetParamNum() == 3) && !func->IsHighOrder()) {
            const FunctionData& call = *func;
            const char* type = call.GetParamId(0);
            if (call.GetParamNum() == 3) {
                const char* begin = call.GetParamId(1);
                const char* end = call.GetParamId(2);
                if (strcmp(type, "string") == 0) {
                    mThis->setStringDelimiter(begin, end);
                }
                else if (strcmp(type, "script") == 0) {
                    mThis->setScriptDelimiter(begin, end);
                }
                else {
                    //invalid
                }
            }
            else {
                if (strcmp(type, "string") == 0) {
                    mThis->setStringDelimiter("", "");
                }
                else if (strcmp(type, "script") == 0) {
                    mThis->setScriptDelimiter("", "");
                }
                else {
                    //invalid
                }
            }
            return;
        }

        int commentOnNewLine;
        int num = mThis->getCommentNum(commentOnNewLine);
        if (num > 0 && statement->GetLastCommentNum() <= 0) {
            statement->SetLastCommentOnNewLine(commentOnNewLine);
        }
        for (int ix = 0; ix < num; ++ix) {
            char* cmt = mThis->getComment(ix);
            statement->AddLastComment(cmt);
        }
        mThis->resetComments();

        if (mData.isSemanticStackEmpty()) {
            //Simplification only needs to be processed at one level, and the parameters and statement parts should have been processed when they are added to the statement.
            ISyntaxComponent& statementSyntax = simplifyStatement(*statement);
            if (!statementSyntax.IsValid()) {
                //_epsilon_ Expression has no statement semantics
                if (mDataFile->GetDslInfoNum() > 0) {
                    ISyntaxComponent* last = mDataFile->GetDslInfo(mDataFile->GetDslInfoNum() - 1);
                    if (last->GetLastCommentNum() <= 0) {
                        last->SetLastCommentOnNewLine(statementSyntax.IsFirstCommentOnNewLine());
                    }
                    int fnum = statementSyntax.GetFirstCommentNum();
                    for (int ix = 0; ix < fnum; ++ix) {
                        last->AddLastComment(statementSyntax.GetFirstComment(ix));
                    }
                    int lnum = statementSyntax.GetLastCommentNum();
                    for (int ix = 0; ix < lnum; ++ix) {
                        last->AddLastComment(statementSyntax.GetLastComment(ix));
                    }
                }
                return;
            }
            else if (statementSyntax.GetSyntaxType() == ISyntaxComponent::TYPE_VALUE) {
                //Comments for ordinary value statements are moved to the previous statement
                if (mDataFile->GetDslInfoNum() > 0) {
                    ISyntaxComponent* last = mDataFile->GetDslInfo(mDataFile->GetDslInfoNum() - 1);
                    if (last->GetLastCommentNum() <= 0) {
                        last->SetLastCommentOnNewLine(statement->IsFirstCommentOnNewLine());
                    }
                    int fnum = statement->GetFirstCommentNum();
                    for (int ix = 0; ix < fnum; ++ix) {
                        last->AddLastComment(statement->GetFirstComment(ix));
                    }
                    int lnum = statement->GetLastCommentNum();
                    for (int ix = 0; ix < lnum; ++ix) {
                        last->AddLastComment(statement->GetLastComment(ix));
                    }
                }
            }
            else {
                //The comment on the previous line of statement is moved to the previous line of statement
                if (mDataFile->GetDslInfoNum() > 0 && !statementSyntax.IsFirstCommentOnNewLine() && statementSyntax.GetFirstCommentNum() > 0) {
                    const char* cmt = statementSyntax.GetFirstComment(0);
                    statementSyntax.RemoveFirstComment(0);
                    statementSyntax.SetFirstCommentOnNewLine(TRUE);
                    ISyntaxComponent* last = mDataFile->GetDslInfo(mDataFile->GetDslInfoNum() - 1);
                    if (last->GetLastCommentNum() <= 0) {
                        last->SetLastCommentOnNewLine(FALSE);
                    }
                    last->AddLastComment(cmt);
                }
            }
            //End of top-level element
            mDataFile->AddDslInfo(&statementSyntax);
            mThis->setCanFinish(TRUE);
        }
        else {
            //Simplification only needs to be processed at one level, and the parameters and statement parts
            //should have been processed when they are added to the statement.
            ISyntaxComponent& statementSyntax = simplifyStatement(*statement);

            FunctionData* p = mData.getLastFunction();
            if (0 != p) {
                if (p->HaveParam()) {
                    //If it is a comment in a parameter, leave it as is. Comments on ordinary values will be discarded,
                    //and embedded comments will be confusing if they are moved to the end of the line.
                    //if (!statementSyntax.IsValid())
                    //    return;
                }
                else if (!statementSyntax.IsValid()) {
                    //_epsilon_ Expression has no statement semantics
                    if (p->GetParamNum() > 0 && statementSyntax.GetFirstCommentNum() > 0) {
                        ISyntaxComponent* last = p->GetParam(p->GetParamNum() - 1);
                        if (last->GetLastCommentNum() <= 0) {
                            last->SetLastCommentOnNewLine(statementSyntax.IsFirstCommentOnNewLine());
                        }
                        int fnum = statementSyntax.GetFirstCommentNum();
                        for (int ix = 0; ix < fnum; ++ix) {
                            last->AddLastComment(statementSyntax.GetFirstComment(ix));
                        }
                        int lnum = statementSyntax.GetLastCommentNum();
                        for (int ix = 0; ix < lnum; ++ix) {
                            last->AddLastComment(statementSyntax.GetLastComment(ix));
                        }
                    }
                    //return;
                }
                else if (statementSyntax.GetSyntaxType() == ISyntaxComponent::TYPE_VALUE) {
                    //If the statement is a normal value, the comment is moved to the previous statement
                    if (p->GetParamNum() > 0) {
                        ISyntaxComponent* last = p->GetParam(p->GetParamNum() - 1);
                        if (last->GetLastCommentNum() <= 0) {
                            last->SetLastCommentOnNewLine(statement->IsFirstCommentOnNewLine());
                        }
                        int fnum = statement->GetFirstCommentNum();
                        for (int ix = 0; ix < fnum; ++ix) {
                            last->AddLastComment(statement->GetFirstComment(ix));
                        }
                        int lnum = statement->GetLastCommentNum();
                        for (int ix = 0; ix < lnum; ++ix) {
                            last->AddLastComment(statement->GetLastComment(ix));
                        }
                    }
                    else {
                        int fnum = statement->GetFirstCommentNum();
                        for (int ix = 0; ix < fnum; ++ix) {
                            p->AddComment(statement->GetFirstComment(ix));
                        }
                        int lnum = statement->GetLastCommentNum();
                        for (int ix = 0; ix < lnum; ++ix) {
                            p->AddComment(statement->GetLastComment(ix));
                        }
                    }
                }
                else {
                    //The comment of the previous line of statement is moved to the previous line of statement or outer function header or outer function.
                    if (!statementSyntax.IsFirstCommentOnNewLine() && statementSyntax.GetFirstCommentNum() > 0) {
                        const char* cmt = statementSyntax.GetFirstComment(0);
                        statementSyntax.RemoveFirstComment(0);
                        statementSyntax.SetFirstCommentOnNewLine(TRUE);
                        if (p->GetParamNum() > 0) {
                            ISyntaxComponent* last = p->GetParam(p->GetParamNum() - 1);
                            if (last->GetLastCommentNum() <= 0) {
                                last->SetLastCommentOnNewLine(FALSE);
                            }
                            last->AddLastComment(cmt);
                        }
                        else if (p->IsHighOrder()) {
                            p->GetLowerOrderFunction().AddComment(cmt);
                        }
                        else {
                            p->AddComment(cmt);
                        }
                    }
                }
                //Function expansion statement part
                p->AddParam(&statementSyntax);
            }
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::addFunction()
    {
        if (!preconditionCheck())return;
        StatementData* statement = mData.getCurStatement();
        if (0 != statement) {
            if (!mDataFile->OnBeforeAddFunction.isNull()) {
                mDataFile->OnBeforeAddFunction(mApi, statement);
                statement = mData.getCurStatement();
            }
            if (0 != statement) {
                FunctionData* newFunc = mDataFile->AddNewFunctionComponent();
                if (0 != newFunc) {
                    statement->AddFunction(newFunc);
                    if (!mDataFile->OnAddFunction.isNull()) {
                        mDataFile->OnAddFunction(mApi, statement, newFunc);
                    }
                }
            }
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::setFunctionId()
    {
        if (!preconditionCheck())return;
        RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
        if (TRUE != tokenInfo.IsValid())return;

        if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("id:%s\n", tokenInfo.mString);
        }

        FunctionData* p = mData.getLastFunction();
        if (0 != p && !p->IsValid()) {
            ValueData val = tokenInfo.ToValue();
            if (TRUE == val.IsValid()) {
                val.SetLine(mThis->getLastLineNumber());
                p->SetName(val);
            }
        }
        if (!mDataFile->OnSetFunctionId.isNull()) {
            StatementData* pStm = mData.getCurStatement();
            if (0 == pStm || 0 == p)
                return;
            mDataFile->OnSetFunctionId(mApi, tokenInfo.mString, pStm, p);
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::buildNullableOperator()
    {
        if (!preconditionCheck())return;
        RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
        if (TRUE != tokenInfo.IsValid())return;

        if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("op:%s\n", tokenInfo.mString);
        }

        if (!preconditionCheck())return;
        //Higher-order function construction (the current function returns a function)
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        if (tokenInfo.mString[0] == '?')
            p->SetParamClass(IDslSyntaxCommon::PARAM_CLASS_QUESTION_NULLABLE_OPERATOR);
        else
            p->SetParamClass(IDslSyntaxCommon::PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR);

        if (!mDataFile->OnBeforeBuildHighOrder.isNull()) {
            StatementData* pStm = mData.getCurStatement();
            if (0 == pStm)
                return;
            mDataFile->OnBeforeBuildHighOrder(mApi, pStm, p);
            p = mData.getLastFunction();
            if (0 == p)
                return;
        }
        FunctionData* newP = mDataFile->AddNewFunctionComponent();
        if (0 != newP) {
            ValueData val(p);
            val.SetLine(p->GetLine());
            newP->SetName(val);
            mData.setLastFunction(newP);
        }
        if (!mDataFile->OnBuildHighOrder.isNull()) {
            StatementData* pStm = mData.getCurStatement();
            if (0 == pStm || 0 == newP)
                return;
            mDataFile->OnBuildHighOrder(mApi, pStm, newP);
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::buildHighOrderFunction()
    {
        if (!preconditionCheck())return;
        //Higher-order function construction (the current function returns a function)
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        if (!mDataFile->OnBeforeBuildHighOrder.isNull()) {
            StatementData* pStm = mData.getCurStatement();
            if (0 == pStm)
                return;
            mDataFile->OnBeforeBuildHighOrder(mApi, pStm, p);
            p = mData.getLastFunction();
            if (0 == p)
                return;
        }
        FunctionData* newP = mDataFile->AddNewFunctionComponent();
        if (0 != newP) {
            ValueData val(p);
            val.SetLine(p->GetLine());
            newP->SetName(val);
            mData.setLastFunction(newP);
        }
        if (!mDataFile->OnBuildHighOrder.isNull()) {
            StatementData* pStm = mData.getCurStatement();
            if (0 == pStm || 0 == newP)
                return;
            mDataFile->OnBuildHighOrder(mApi, pStm, newP);
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markParenthesisParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;

        call.SetParamClass(FunctionData::PARAM_CLASS_PARENTHESIS);
        auto&& pID = call.GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_PARENTHESIS, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markBracketParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;

        call.SetParamClass(FunctionData::PARAM_CLASS_BRACKET);
        auto&& pID = call.GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_BRACKET, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPeriodParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PERIOD);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markStatement()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData* lowerOrderFunc = 0;
        if (p->IsHighOrder()) {
            lowerOrderFunc = p->GetName().GetFunction();
        }
        int commentOnNewLine;
        int num = mThis->getCommentNum(commentOnNewLine);
        for (int ix = 0; ix < num; ++ix) {
            char* cmt = mThis->getComment(ix);
            if (0 != lowerOrderFunc) {
                lowerOrderFunc->AddComment(cmt);
            }
            else {
                p->AddComment(cmt);
            }
        }
        mThis->resetComments();

        p->SetParamClass(FunctionData::PARAM_CLASS_STATEMENT);
        auto&& pID = p->GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_BRACE, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markExternScript()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData* lowerOrderFunc = 0;
        if (p->IsHighOrder()) {
            lowerOrderFunc = p->GetName().GetFunction();
        }
        int commentOnNewLine;
        int num = mThis->getCommentNum(commentOnNewLine);
        for (int ix = 0; ix < num; ++ix) {
            char* cmt = mThis->getComment(ix);
            if (0 != lowerOrderFunc) {
                lowerOrderFunc->AddComment(cmt);
            }
            else {
                p->AddComment(cmt);
            }
        }
        mThis->resetComments();

        p->SetParamClass(FunctionData::PARAM_CLASS_EXTERN_SCRIPT);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markBracketColonParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_BRACKET_COLON);
        auto&& pID = call.GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_BRACKET_COLON, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markParenthesisColonParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PARENTHESIS_COLON);
        auto&& pID = call.GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_PARENTHESIS_COLON, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markAngleBracketColonParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_ANGLE_BRACKET_COLON);
        auto&& pID = call.GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_ANGLE_BRACKET_COLON, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markBracePercentParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_BRACE_PERCENT);
        auto&& pID = call.GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_BRACE_PERCENT, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markBracketPercentParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_BRACKET_PERCENT);
        auto&& pID = call.GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_BRACKET_PERCENT, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markParenthesisPercentParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PARENTHESIS_PERCENT);
        auto&& pID = call.GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_PARENTHESIS_PERCENT, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markAngleBracketPercentParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_ANGLE_BRACKET_PERCENT);
        auto&& pID = call.GetId();
        uint32_t tag = 0;
        if (pID) {
            auto&& tags = mDataFile->NameTagsRef();
            auto&& tagIt = tags.find(pID);
            if (tagIt != tags.end()) {
                tag = tagIt->second;
            }
        }
        pushPairType(IDslSyntaxCommon::PAIR_TYPE_ANGLE_BRACKET_PERCENT, tag);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markColonColonParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_COLON_COLON);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPointerParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_POINTER);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPeriodStarParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PERIOD_STAR);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPointerStarParam()
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_POINTER_STAR);
    }
    template<class RealTypeT> inline
        ISyntaxComponent& RuntimeBuilderT<RealTypeT>::simplifyStatement(StatementData& data)const
    {
        int num = data.GetFunctionNum();
        //Simplify the statements (for convenience during the syntax analysis process, all are constructed according to the complete StatementData.
        //Here they are simplified to the original types: ValueData/FunctionData/FunctionData, etc.,
        //mainly involving parameters and statement parts)
        if (num == 1) {
            //A statement with only one function degenerates into a function (and then further degenerates by function).
            auto* f = data.GetFunction(0);
            f->CopyComments(data);
            if (f->IsFunction()) {
                FunctionData& func = *f->AsFunction();
                return simplifyStatement(func);
            }
            else {
                return *f->AsValue();
            }
        }
        else {
            for (int i = 0; i < num; ++i) {
                auto* f = data.GetFunction(i);
                if (f->IsFunction()) {
                    FunctionData& func = *f->AsFunction();
                    data.GetFunctionRef(i) = &simplifyStatement(func);
                }
            }
        }
        return data;
    }
    template<class RealTypeT> inline
        ValueOrFunctionData& RuntimeBuilderT<RealTypeT>::simplifyStatement(FunctionData& data)const
    {
        //Note that in order to save memory, there are no comments on ValueData,
        //and the related interfaces have no actual effect! ! !
        if (!data.HaveParamOrStatement()) {
            //Calls without parameters degenerate to basic value data
            if (data.IsHighOrder()) {
                //This should not happen
                return data;
            }
            else {
                ValueData& name = data.GetName();
                return name;
            }
        }
        else {
            //Processing epsilon statements and parameters
            simplifyFunction(data);
        }
        if (nullptr != data.GetId() && data.GetId()[0] == '-' && data.GetId()[1] == '\0' && data.GetParamNum() == 1) {
            ISyntaxComponent& temp = *data.GetParam(0);
            if (temp.GetSyntaxType() == ISyntaxComponent::TYPE_VALUE) {
                ValueData& val = static_cast<ValueData&>(temp);
                if (val.IsNum()) {
                    int size = (int)strlen(val.GetId()) + 1;
                    char* pBuf = mDataFile->AllocString(size);
                    tsnprintf(pBuf, size + 1, "-%s", val.GetId());
                    val.SetNumber(pBuf);
                    return val;
                }
                else {
                    return data;
                }
            }
            else {
                return data;
            }
        }
        else if (nullptr != data.GetId() && data.GetId()[0] == '+' && data.GetId()[1] == '\0' && data.GetParamNum() == 1) {
            ISyntaxComponent& temp = *data.GetParam(0);
            if (temp.GetSyntaxType() == ISyntaxComponent::TYPE_VALUE) {
                ValueData& val = static_cast<ValueData&>(temp);
                if (val.IsNum()) {
                    int size = (int)strlen(val.GetId()) + 1;
                    char* pBuf = mDataFile->AllocString(size);
                    tsnprintf(pBuf, size + 1, "+%s", val.GetId());
                    val.SetNumber(pBuf);
                    return val;
                }
                else {
                    return data;
                }
            }
            else {
                return data;
            }
        }
        else {
            //There are parameters that will not degrade
            return data;
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::simplifyFunction(FunctionData& data)const
    {
        //When the last statement is epsilon and the only parameter is epsilon, delete this statement and parameters so that for(;;){} can be parsed correctly
        //Currently {} is used in non-statement blocks. There should be no situation where the last parameter needs to be empty (the previous parameters are
        //currently allowed to be empty).
        //The function is that the statement list also allows other statements to be empty except the last statement that does not end with a semicolon.
        //The upper-layer application needs to handle it during further parsing
        if (data.IsHighOrder()) {
            simplifyFunction(data.GetLowerOrderFunction());
        }
        int num = data.GetParamNum();
        if ((data.HaveStatement() && num > 0) || num == 1) {
            if (!data.GetParam(num - 1)->IsValid()) {
                data.RemoveLastParam();
            }
        }
    }
    template<class RealTypeT> inline
        int RuntimeBuilderT<RealTypeT>::peekPairTypeStack(uint32_t& tag)const
    {
        uint32_t v =  mData.peekPairType();
        tag = (v >> 8);
        return static_cast<int>(v & 0xff);
    }
    template<class RealTypeT> inline
        int RuntimeBuilderT<RealTypeT>::getPairTypeStackSize()const
    {
        return mData.getPairTypeStack().Size();
    }
    template<class RealTypeT> inline
        int RuntimeBuilderT<RealTypeT>::peekPairTypeStack(int ix, uint32_t& tag)const
    {
        if (ix >= 0 && ix < getPairTypeStackSize()) {
            auto&& stack = mData.getPairTypeStack();
            int id = stack.BackID();
            for (int i = 0; i < ix; ++i) {
                id = stack.PrevID(id);
            }
            uint32_t v = stack[id];
            tag = (v >> 8);
            return static_cast<int>(v & 0xff);
        }
        else {
            tag = 0;
            return IDslSyntaxCommon::PAIR_TYPE_NONE;
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::pushPairType(int type, uint32_t tag)
    {
        uint32_t v = (tag << 8) + static_cast<uint32_t>(type & 0xff);
        mData.pushPairType(v);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::popPairType()
    {
        mData.popPairType();
    }
}
//--------------------------------------------------------------------------------------
//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
//--------------------------------------------------------------------------------------