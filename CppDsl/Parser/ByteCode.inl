//--------------------------------------------------------------------------------------
//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
//--------------------------------------------------------------------------------------

#define PRINT_FUNCTION_SCRIPT_DEBUG_INFO printf

namespace Dsl
{
    /*
     * 备忘：为什么采用约简的方式而不是延迟一次性构造
     * 1、已尝试过采用一个临时的结构比如SyntaxMaterial来收集语法解析过程中的数据，到语句完成时再构造语句
     * 2、临时的结构与最终语义数据结构上相似度很高，也需要表示递归结构并且要与现有语义数据关联，代码重复并且逻辑不够清晰。
     * 3、约简方式已经尽量重用语法解析中构造的实例，基本不会产生额外内存占用
     * 4、约简方式下最终内存占用与脚本复杂度线性相关，不用担心占用过多内存
     * 5、语义数据在定义上考虑了退化情形，除必须数据外已尽量不占用额外空间
     */
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::setExternScript(void)
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
        void RuntimeBuilderT<RealTypeT>::buildOperator(void)
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
        mData.popStatement();
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
                ValueData op(tokenInfo.mString + 1, ValueData::TYPE_IDENTIFIER);
                op.SetLine(mThis->getLastLineNumber());
                call.SetName(op);
            }
            else {
                call.SetParamClass(FunctionData::PARAM_CLASS_OPERATOR);

                ValueData v = call.GetName();
                ValueData op(tokenInfo.mString, ValueData::TYPE_IDENTIFIER);
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
        void RuntimeBuilderT<RealTypeT>::buildFirstTernaryOperator(void)
    {
        if (!preconditionCheck())return;
        RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
        if (TRUE != tokenInfo.IsValid())return;

        if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("op1/2:%s\n", tokenInfo.mString);
        }

        StatementData* pArg = mData.popStatement();
        if (0 == pArg)
            return;
        ISyntaxComponent& argComp = simplifyStatement(*pArg);
        StatementData* pStatement = mDataFile->AddNewStatementComponent();
        if (0 == pStatement)
            return;

        pStatement->CopyFirstComments(argComp);
        argComp.ClearFirstComments();

        mData.pushStatement(pStatement);

        FunctionData* p = mDataFile->AddNewFunctionComponent();
        if (0 != p) {
            //三元运算符表示成op1(cond)(true_val)op2(false_val)
            FunctionData* lowerOrderFunction = mDataFile->AddNewFunctionComponent();
            p->GetName().SetFunction(lowerOrderFunction);
            p->SetParamClass(FunctionData::PARAM_CLASS_TERNARY_OPERATOR);
            lowerOrderFunction->SetParamClass(FunctionData::PARAM_CLASS_PARENTHESIS);

            ValueData op(tokenInfo.mString, ValueData::TYPE_IDENTIFIER);
            op.SetLine(mThis->getLastLineNumber());
            lowerOrderFunction->SetName(op);
            if (argComp.IsValid()) {
                lowerOrderFunction->AddParam(&argComp);
            }

            pStatement->AddFunction(p);
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::buildSecondTernaryOperator(void)
    {
        if (!preconditionCheck())return;
        RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
        if (TRUE != tokenInfo.IsValid())return;

        if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("op2/2:%s\n", tokenInfo.mString);
        }

        StatementData* statement = mData.getCurStatement();
        if (0 != statement) {
            FunctionData* p = mDataFile->AddNewFunctionComponent();
            if (0 != p) {
                FunctionData& call = *p;
                call.SetParamClass(FunctionData::PARAM_CLASS_TERNARY_OPERATOR);

                ValueData op(tokenInfo.mString, ValueData::TYPE_IDENTIFIER);
                op.SetLine(mThis->getLastLineNumber());
                call.SetName(op);

                statement->AddFunction(p);
            }
        }
    }
    //--------------------------------------------------------------------------------------	
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::beginStatement(void)
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
        void RuntimeBuilderT<RealTypeT>::endStatement(void)
    {
        if (!preconditionCheck())return;
        StatementData* statement = mData.popStatement();
        if (0 == statement)
            return;
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
            //化简只需要处理一级，参数与语句部分应该在添加到语句时已经处理了
            ISyntaxComponent& statementSyntax = simplifyStatement(*statement);
            if (!statementSyntax.IsValid()) {
                //_epsilon_表达式无语句语义
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
                //普通值语句的注释挪到上一语句
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
                //上一行语句的注释挪到上一行语句
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
            //顶层元素结束
            mDataFile->AddDslInfo(&statementSyntax);
            mThis->setCanFinish(TRUE);
        }
        else {
            //化简只需要处理一级，参数与语句部分应该在添加到语句时已经处理了
            ISyntaxComponent& statementSyntax = simplifyStatement(*statement);

            FunctionData* p = mData.getLastFunction();
            if (0 != p) {
                if (p->HaveParam()) {
                    //如果是参数里的注释，保持原样。普通值上的注释会丢弃，嵌入的注释如果挪到行尾会比较莫名其妙。
                    if (!statementSyntax.IsValid())
                        return;
                }
                else if (!statementSyntax.IsValid()) {
                    //_epsilon_表达式无语句语义
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
                    return;
                }
                else if (statementSyntax.GetSyntaxType() == ISyntaxComponent::TYPE_VALUE) {
                    //如果语句是普通值，注释挪到上一语句
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
                    //上一行语句的注释挪到上一行语句或外层函数头或外层函数
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
                            p->GetLowerOrderFunction()->AddComment(cmt);
                        }
                        else {
                            p->AddComment(cmt);
                        }
                    }
                }
                //函数扩展语句部分
                p->AddParam(&statementSyntax);
            }
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::addFunction(void)
    {
        if (!preconditionCheck())return;
        StatementData* statement = mData.getCurStatement();
        if (0 != statement) {
            FunctionData* newFunc = mDataFile->AddNewFunctionComponent();
            if (0 != newFunc) {
                statement->AddFunction(newFunc);
            }
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::setFunctionId(void)
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
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::setMemberId(void)
    {
        if (!preconditionCheck())return;
        RuntimeBuilderData::TokenInfo tokenInfo = mData.pop();
        if (TRUE != tokenInfo.IsValid())return;

        if (mDataFile->IsDebugInfoEnable()) {
            PRINT_FUNCTION_SCRIPT_DEBUG_INFO("member:%s\n", tokenInfo.mString);
        }

        FunctionData* p = mData.getLastFunction();
        if (0 != p && !p->IsValid()) {
            ValueData val = tokenInfo.ToValue();
            if (TRUE == val.IsValid()) {
                val.SetLine(mThis->getLastLineNumber());
                p->SetName(val);
            }
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::buildHighOrderFunction(void)
    {
        if (!preconditionCheck())return;
        //高阶函数构造（当前函数返回一个函数）
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData* newP = mDataFile->AddNewFunctionComponent();
        if (0 != newP) {
            ValueData val(p);
            val.SetLine(p->GetLine());
            newP->SetName(val);
            mData.setLastFunction(newP);
        }
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markParenthesisParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;

        call.SetParamClass(FunctionData::PARAM_CLASS_PARENTHESIS);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markBracketParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;

        call.SetParamClass(FunctionData::PARAM_CLASS_BRACKET);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPeriodParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PERIOD);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPeriodParenthesisParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PERIOD_PARENTHESIS);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPeriodBracketParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PERIOD_BRACKET);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPeriodBraceParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PERIOD_BRACE);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markQuestionPeriodParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_QUESTION_PERIOD);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markQuestionParenthesisParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_QUESTION_PARENTHESIS);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markQuestionBracketParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_QUESTION_BRACKET);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markQuestionBraceParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_QUESTION_BRACE);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markStatement(void)
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
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markExternScript(void)
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
        void RuntimeBuilderT<RealTypeT>::markBracketColonParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_BRACKET_COLON);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markParenthesisColonParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PARENTHESIS_COLON);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markAngleBracketColonParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_ANGLE_BRACKET_COLON);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markBracePercentParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_BRACE_PERCENT);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markBracketPercentParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_BRACKET_PERCENT);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markParenthesisPercentParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PARENTHESIS_PERCENT);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markAngleBracketPercentParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_ANGLE_BRACKET_PERCENT);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markColonColonParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_COLON_COLON);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markColonColonParenthesisParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_COLON_COLON_PARENTHESIS);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markColonColonBracketParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_COLON_COLON_BRACKET);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markColonColonBraceParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_COLON_COLON_BRACE);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPointerParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_POINTER);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPeriodStarParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_PERIOD_STAR);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markQuestionPeriodStarParam(void)
    {
        if (!preconditionCheck())return;
        FunctionData* p = mData.getLastFunction();
        if (0 == p)
            return;
        FunctionData& call = *p;
        call.SetParamClass(FunctionData::PARAM_CLASS_QUESTION_PERIOD_STAR);
    }
    template<class RealTypeT> inline
        void RuntimeBuilderT<RealTypeT>::markPointerStarParam(void)
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
        //对语句进行化简（语法分析过程中为了方便，全部按完整StatementData来构造，这里化简为原来的类型：ValueData/FunctionData/FunctionData等，主要涉及参数与语句部分）
        if (num == 1) {
            //只有一个函数的语句退化为函数（再按函数进一步退化）。
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
        //注意，为了省内存ValueData上不附带注释了，相关接口无实际效果！！！
        if (!data.HaveParamOrStatement()) {
            //没有参数的调用退化为基本值数据
            if (data.IsHighOrder()) {
                //这种情况应该不会出现
                return data;
            }
            else {
                ValueData& name = data.GetName();
                return name;
            }
        }
        else if (NULL != data.GetId() && data.GetId()[0] == '-' && data.GetParamNum() == 1) {
            ISyntaxComponent& temp = *data.GetParam(0);
            if (temp.GetSyntaxType() == ISyntaxComponent::TYPE_VALUE) {
                ValueData& val = dynamic_cast<ValueData&>(temp);
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
        else if (NULL != data.GetId() && data.GetId()[0] == '+' && data.GetParamNum() == 1) {
            ISyntaxComponent& temp = *data.GetParam(0);
            if (temp.GetSyntaxType() == ISyntaxComponent::TYPE_VALUE) {
                ValueData& val = dynamic_cast<ValueData&>(temp);
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
            //有参数不会退化
            return data;
        }
    }
}
//--------------------------------------------------------------------------------------
//**************************************************************************************
//**************************************************************************************
//**************************************************************************************
//--------------------------------------------------------------------------------------