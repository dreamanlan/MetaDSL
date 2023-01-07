using System;
using System.Collections.Generic;
using System.Text;

namespace Dsl.Common
{
    /*
     * 备忘：为什么采用约简的方式而不是延迟一次性构造
     * 1、已尝试过采用一个临时的结构比如SyntaxMaterial来收集语法解析过程中的数据，到语句完成时再构造语句
     * 2、临时的结构与最终语义数据结构上相似度很高，也需要表示递归结构并且要与现有语义数据关联，代码重复并且逻辑不够清晰。
     * 3、约简方式已经尽量重用语法解析中构造的实例，基本不会产生额外内存占用
     * 4、约简方式下最终内存占用与脚本复杂度线性相关，不用担心占用过多内存
     * 5、语义数据在定义上考虑了退化情形，除必须数据外已尽量不占用额外空间
     */
    public delegate bool GetTokenDelegation(ref DslToken dslToken, ref string tok, ref short val, ref int line);
    public delegate bool BeforeAddFunctionDelegation(ref DslAction dslAction, StatementData statement);
    public delegate bool AddFunctionDelegation(ref DslAction dslAction, StatementData statement, FunctionData function);
    public delegate bool BeforeEndStatementDelegation(ref DslAction dslAction);
    public delegate bool EndStatementDelegation(ref DslAction dslAction, ref StatementData statement);

    internal delegate string GetLastTokenDelegation();
    internal delegate int GetLastLineNumberDelegation();
    internal delegate IList<string> GetCommentsDelegation(out bool commentOnNewLine);
    internal delegate void SetDelimiterDelegation(string begin, string end);
    internal enum DslActionType
    {
        Dsl = 0,
        Lua,
        Cpp,
    }
    public struct DslAction
    {
        class SemanticInfo
        {
            internal string token;
            internal int value;

            internal SemanticInfo()
            { }
            internal SemanticInfo(string _token, int _value)
            {
                token = _token;
                value = _value;
            }
        };

        internal DslAction(DslLog log, List<ISyntaxComponent> datas)
        {
            mActionType = DslActionType.Dsl;
            mLog = log;
            mScriptDatas = datas;

            mSemanticStack = new Stack<SemanticInfo>();
            mStatementSemanticStack = new Stack<StatementData>();

            mGetLastToken = null;
            mGetLastLineNumber = null;
            mGetComments = null;
            mSetStringDelimiter = null;
            mSetScriptDelimiter = null;
            mOnBeforeAddFunction = null;
            mOnAddFunction = null;
            mOnBeforeEndStatement = null;
            mOnEndStatement = null;
        }

        internal DslActionType Type
        {
            get { return mActionType; }
            set { mActionType = value; }
        }
        internal GetLastTokenDelegation onGetLastToken
        {
            get { return mGetLastToken; }
            set { mGetLastToken = value; }
        }
        internal GetLastLineNumberDelegation onGetLastLineNumber
        {
            get { return mGetLastLineNumber; }
            set { mGetLastLineNumber = value; }
        }
        internal GetCommentsDelegation onGetComment
        {
            get { return mGetComments; }
            set { mGetComments = value; }
        }
        internal SetDelimiterDelegation onSetStringDelimiter
        {
            get { return mSetStringDelimiter; }
            set { mSetStringDelimiter = value; }
        }
        internal SetDelimiterDelegation onSetScriptDelimiter
        {
            get { return mSetScriptDelimiter; }
            set { mSetScriptDelimiter = value; }
        }
        internal BeforeAddFunctionDelegation onBeforeAddFunction
        {
            get { return mOnBeforeAddFunction; }
            set { mOnBeforeAddFunction = value; }
        }
        internal AddFunctionDelegation onAddFunction
        {
            get { return mOnAddFunction; }
            set { mOnAddFunction = value; }
        }
        internal BeforeEndStatementDelegation onBeforeEndStatement
        {
            get { return mOnBeforeEndStatement; }
            set { mOnBeforeEndStatement = value; }
        }
        internal EndStatementDelegation onEndStatement
        {
            get { return mOnEndStatement; }
            set { mOnEndStatement = value; }
        }

        internal void predict(short productionNumber, short nonterminal, short token, int level, string lastTok, int lastLineNo, string curTok, int lineNo)
        {
            switch (mActionType) {
                case DslActionType.Dsl:
                    //mLog.Log("{0} [production: {1} nonterminal: {2} token symbol: {3} last token: {4} line: {5} cur token: {6} line: {7} ]", Dsl.Parser.DslString.GetProductionName(productionNumber), productionNumber, nonterminal, Dsl.Parser.DslString.GetSymbolName(token), lastTok, lastLineNo, curTok, lineNo);
                    break;
                case DslActionType.Lua:
                    //mLog.Log("{0} [production: {1} nonterminal: {2} token symbol: {3} last token: {4} line: {5} cur token: {6} line: {7} ]", Dsl.Parser.LuaString.GetProductionName(productionNumber), productionNumber, nonterminal, Dsl.Parser.LuaString.GetSymbolName(token), lastTok, lastLineNo, curTok, lineNo);
                    break;
                case DslActionType.Cpp:
                    //mLog.Log("{0} [production: {1} nonterminal: {2} token symbol: {3} last token: {4} line: {5} cur token: {6} line: {7} ]", Dsl.Parser.CppString.GetProductionName(productionNumber), productionNumber, nonterminal, Dsl.Parser.CppString.GetSymbolName(token), lastTok, lastLineNo, curTok, lineNo);
                    
                    //var list = Dsl.Parser.CppParser.GetProductionArray(productionNumber);
                    //mLog.Log("\tproduction length:{0}|{1}=>", list[0], list[1]);
                    //for (int i = 2; i <= list[0] && i < list.Length; ++i) {
                    //    mLog.Log("\t\t{0}", list[i]);
                    //}
                    break;
            }
        }
        internal void execute(int number)
        {
            switch (mActionType) {
                case DslActionType.Dsl:
                    executeDsl(number);
                    break;
                case DslActionType.Lua:
                    executeLua(number);
                    break;
                case DslActionType.Cpp:
                    executeCpp(number);
                    break;
            }
        }

        private void executeDsl(int number)
        {
            switch (number) {
                case 1: markSeparator(); break;
                case 2: endStatement(); break;
                case 3: pushId(); break;
                case 4: buildOperator(); break;
                case 5: buildFirstTernaryOperator(); break;
                case 6: buildSecondTernaryOperator(); break;
                case 7: beginStatement(); break;
                case 8: addFunction(); break;
                case 9: setFunctionId(); break;
                case 10: markParenthesisParam(); break;
                case 11: buildHighOrderFunction(); break;
                case 12: markBracketParam(); break;
                case 13: markQuestionParenthesisParam(); break;
                case 14: markQuestionBracketParam(); break;
                case 15: markQuestionBraceParam(); break;
                case 16: markStatement(); break;
                case 17: markExternScript(); break;
                case 18: setExternScript(); break;
                case 19: markBracketColonParam(); break;
                case 20: markParenthesisColonParam(); break;
                case 21: markAngleBracketColonParam(); break;
                case 22: markBracePercentParam(); break;
                case 23: markBracketPercentParam(); break;
                case 24: markParenthesisPercentParam(); break;
                case 25: markAngleBracketPercentParam(); break;
                case 26: markColonColonParam(); break;
                case 27: setMemberId(); break;
                case 28: markColonColonParenthesisParam(); break;
                case 29: markColonColonBracketParam(); break;
                case 30: markColonColonBraceParam(); break;
                case 31: markPeriodParam(); break;
                case 32: markPeriodParenthesisParam(); break;
                case 33: markPeriodBracketParam(); break;
                case 34: markPeriodBraceParam(); break;
                case 35: markQuestionPeriodParam(); break;
                case 36: markPointerParam(); break;
                case 37: markPeriodStarParam(); break;
                case 38: markQuestionPeriodStarParam(); break;
                case 39: markPointerStarParam(); break;
                case 40: pushStr(); break;
                case 41: pushNum(); break;
                case 42: pushComma(); break;
                case 43: pushSemiColon(); break;
            }
        }
        private void executeLua(int number)
        {
            switch (number) {
                case 1: beginStatement(); break;
                case 2: addFunction(); break;
                case 3: pushId(); break;
                case 4: setFunctionId(); break;
                case 5: markStatement(); break;
                case 6: markParenthesisParam(); break;
                case 7: endStatementLua(); break;
                case 8: pushLuaList(); break;
                case 9: checkLuaList(); break;
                case 10: pushAssignWith(); break;
                case 11: removeLuaList(); break;
                case 12: pushLuaLabel(); break;
                case 13: buildHighOrderFunction(); break;
                case 14: pushLuaRange(); break;
                case 15: pushLuaVarAttr(); break;
                case 16: markBracketColonParam(); break;
                case 17: removeLuaVarAttr(); break;
                case 18: markAngleBracketColonParam(); break;
                case 19: pushDot(); break;
                case 20: pushColon(); break;
                case 21: pushLuaArgs(); break;
                case 22: buildOperator(); break;
                case 23: markBracketParam(); break;
                case 24: markParenthesisColonParam(); break;
                case 25: markPeriodParam(); break;
                case 26: setMemberId(); break;
                case 27: markPointerParam(); break;
                case 28: pushStr(); break;
                case 29: pushNum(); break;
            }
        }
        private void executeCpp(int number)
        {
            switch (number) {
                case 1: markSeparator(); break;
                case 2: endStatement(); break;
                case 3: beginStatement(); break;
                case 4: cppOnFunctionBegin(); break;
                case 5: addFunction(); break;
                case 6: cppOnFunctionEnd(); break;
                case 7: setFunctionId(); break;
                case 8: markParenthesisParam(); break;
                case 9: buildHighOrderFunction(); break;
                case 10: markBracketParam(); break;
                case 11: markStatement(); break;
                case 12: pushId(); break;
                case 13: pushStr(); break;
                case 14: pushNum(); break;
                case 15: pushComma(); break;
                case 16: pushSemiColon(); break;
            }
        }

        private void endStatementImpl(bool addSep)
        {
            if (null != mOnBeforeEndStatement) {
                mOnBeforeEndStatement(ref this);
            }
            StatementData statement = popStatement();
            if (null != mOnEndStatement) {
                mOnEndStatement(ref this, ref statement);
            }
            FunctionData call = statement.First.AsFunction;
            if ((null != mSetStringDelimiter || null != mSetScriptDelimiter) && statement.Functions.Count == 1 && null != call && call.GetId() == "@@delimiter" && (call.GetParamNum() == 1 || call.GetParamNum() == 3) && !call.IsHighOrder) {
                string type = call.GetParamId(0);
                if (call.GetParamNum() == 3) {
                    string begin = call.GetParamId(1);
                    string end = call.GetParamId(2);
                    if (type == "string") {
                        setStringDelimiter(begin, end);
                    }
                    else if (type == "script") {
                        setScriptDelimiter(begin, end);
                    }
                    else {
                        //invalid
                    }
                }
                else {
                    if (type == "string") {
                        setStringDelimiter(string.Empty, string.Empty);
                    }
                    else if (type == "script") {
                        setScriptDelimiter(string.Empty, string.Empty);
                    }
                    else {
                        //invalid
                    }
                }
                return;
            }

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                if (statement.LastComments.Count <= 0) {
                    statement.LastCommentOnNewLine = commentOnNewLine;
                }
                statement.LastComments.AddRange(cmts);
            }

            if (mStatementSemanticStack.Count == 0) {
                //化简只需要处理一级，参数与语句部分应该在添加到语句时已经处理了
                AbstractSyntaxComponent statementSyntax = simplifyStatement(statement);
                ValueData vdSyntax = statementSyntax as ValueData;
                if (!statementSyntax.IsValid()) {
                    //_epsilon_表达式无语句语义
                    if (mScriptDatas.Count > 0) {
                        ISyntaxComponent last = mScriptDatas[mScriptDatas.Count - 1];
                        if (last.LastComments.Count <= 0) {
                            last.LastCommentOnNewLine = statementSyntax.FirstCommentOnNewLine;
                        }
                        last.LastComments.AddRange(statementSyntax.FirstComments);
                        last.LastComments.AddRange(statementSyntax.LastComments);
                    }
                    return;
                }
                else if (null != vdSyntax) {
                    //如果语句是普通值，注释挪到上一语句
                    if (mScriptDatas.Count > 0) {
                        ISyntaxComponent last = mScriptDatas[mScriptDatas.Count - 1];
                        if (last.LastComments.Count <= 0) {
                            last.LastCommentOnNewLine = statement.FirstCommentOnNewLine;
                        }
                        last.LastComments.AddRange(statement.FirstComments);
                        last.LastComments.AddRange(statement.LastComments);
                    }
                }
                else {
                    //上一行语句的注释挪到上一行语句
                    if (mScriptDatas.Count > 0 && !statementSyntax.FirstCommentOnNewLine && statementSyntax.FirstComments.Count > 0) {
                        string cmt = statementSyntax.FirstComments[0];
                        statementSyntax.FirstComments.RemoveAt(0);
                        statementSyntax.FirstCommentOnNewLine = true;
                        ISyntaxComponent last = mScriptDatas[mScriptDatas.Count - 1];
                        if (last.LastComments.Count <= 0) {
                            last.LastCommentOnNewLine = false;
                        }
                        last.LastComments.Add(cmt);
                    }
                }
                //顶层元素结束
                if (addSep && mScriptDatas.Count > 0) {
                    var lastStm = mScriptDatas[mScriptDatas.Count - 1];
                    lastStm.SetSeparator(AbstractSyntaxComponent.SEPARATOR_SEMICOLON);
                }
                mScriptDatas.Add(statementSyntax);
            }
            else {
                //化简只需要处理一级，参数与语句部分应该在添加到语句时已经处理了
                AbstractSyntaxComponent statementSyntax = simplifyStatement(statement);
                ValueData vdSyntax = statementSyntax as ValueData;
                FunctionData func = getLastFunction();
                if (func.HaveParam()) {
                    //如果是参数里的注释，保持原样。普通值上的注释会丢弃，嵌入的注释如果挪到行尾会比较莫名其妙。
                    if (!statementSyntax.IsValid())
                        return;
                }
                else if (!statement.IsValid()) {
                    //_epsilon_表达式无语句语义
                    if (func.Params.Count > 0 && statementSyntax.FirstComments.Count > 0) {
                        AbstractSyntaxComponent last = func.Params[func.Params.Count - 1] as AbstractSyntaxComponent;
                        if (last.LastComments.Count <= 0) {
                            last.LastCommentOnNewLine = statementSyntax.FirstCommentOnNewLine;
                        }
                        last.LastComments.AddRange(statementSyntax.FirstComments);
                        last.LastComments.AddRange(statementSyntax.LastComments);
                    }
                    return;
                }
                else if (null != vdSyntax) {
                    //如果语句是普通值，注释挪到上一语句
                    if (func.Params.Count > 0) {
                        AbstractSyntaxComponent last = func.Params[func.Params.Count - 1] as AbstractSyntaxComponent;
                        if (last.LastComments.Count <= 0) {
                            last.LastCommentOnNewLine = statement.FirstCommentOnNewLine;
                        }
                        last.LastComments.AddRange(statement.FirstComments);
                        last.LastComments.AddRange(statement.LastComments);
                    }
                    else {
                        func.Comments.AddRange(statement.FirstComments);
                        func.Comments.AddRange(statement.LastComments);
                    }
                }
                else {
                    //上一行语句的注释挪到上一行语句或外层函数头或外层函数
                    if (!statementSyntax.FirstCommentOnNewLine && statementSyntax.FirstComments.Count > 0) {
                        string cmt = statementSyntax.FirstComments[0];
                        statementSyntax.FirstComments.RemoveAt(0);
                        statementSyntax.FirstCommentOnNewLine = true;
                        if (func.Params.Count > 0) {
                            AbstractSyntaxComponent last = func.Params[func.Params.Count - 1] as AbstractSyntaxComponent;
                            if (last.LastComments.Count <= 0) {
                                last.LastCommentOnNewLine = false;
                            }
                            last.LastComments.Add(cmt);
                        }
                        else if (func.IsHighOrder) {
                            func.LowerOrderFunction.Comments.Add(cmt);
                        }
                        else {
                            func.Comments.Add(cmt);
                        }
                    }
                }

                if (addSep && func.GetParamNum() > 0) {
                    var lastParam = func.GetParam(func.GetParamNum()-1);
                    lastParam.SetSeparator(func.GetParamClassUnmasked() == (int)FunctionData.ParamClassEnum.PARAM_CLASS_STATEMENT ? AbstractSyntaxComponent.SEPARATOR_SEMICOLON : AbstractSyntaxComponent.SEPARATOR_COMMA);
                }
                func.AddParam(statementSyntax);
            }
        }
        private void endStatementLua()
        {
            endStatementImpl(true);
        }

        public void markSeparator()
        {
            int type;
            string name = pop(out type);

            if (mStatementSemanticStack.Count == 0) {
                if (mScriptDatas.Count > 0) {
                    var dslInfo = mScriptDatas[mScriptDatas.Count - 1];
                    dslInfo.SetSeparator(CalcSeparator(name));
                }
            }
            else {
                var lastFunc = getLastFunction();
                if (lastFunc.GetParamNum() > 0) {
                    var lastParam = lastFunc.GetParam(lastFunc.GetParamNum() - 1);
                    lastParam.SetSeparator(CalcSeparator(name));
                }
            }
        }
        public void buildOperator()
        {
            int type;
            string name = pop(out type);

            StatementData arg = popStatement();
            ISyntaxComponent argComp = simplifyStatement(arg);

            StatementData _statement = newStatementWithOneFunction();
            var first = _statement.First;
            if (first.IsValue)
                first.AsValue.SetLine(getLastLineNumber());
            else
                first.AsFunction.Name.SetLine(getLastLineNumber());

            _statement.CopyFirstComments(argComp);
            argComp.FirstComments.Clear();

            mStatementSemanticStack.Push(_statement);

            StatementData statement = getCurStatement();
            FunctionData func = getLastFunction();
            if (!func.IsValid()) {
                if (name.Length > 0 && name[0] == '`') {
                    func.SetParamClass((int)(FunctionData.ParamClassEnum.PARAM_CLASS_WRAP_INFIX_CALL_MASK | FunctionData.ParamClassEnum.PARAM_CLASS_OPERATOR));

                    func.Name.SetId(name.Substring(1));
                    func.Name.SetType(type);
                }
                else {
                    func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_OPERATOR);

                    func.Name.SetId(name);
                    func.Name.SetType(type);
                }
                if (argComp.IsValid()) {
                    func.AddParam(argComp);
                }
            }
        }
        public void buildFirstTernaryOperator()
        {
            int type;
            string name = pop(out type);

            StatementData arg = popStatement();
            ISyntaxComponent argComp = simplifyStatement(arg);

            StatementData _statement = newStatementWithOneFunction();
            FunctionData first = _statement.First.AsFunction;
            if (null != first) {
                //三元运算符表示成op1(cond)(true_val)op2(false_val)
                first.LowerOrderFunction = new FunctionData();
                first.LowerOrderFunction.Name = new ValueData();
                first.LowerOrderFunction.Name.SetLine(getLastLineNumber());
            }
            _statement.CopyFirstComments(argComp);
            argComp.FirstComments.Clear();

            mStatementSemanticStack.Push(_statement);

            StatementData statement = getCurStatement();
            FunctionData func = getLastFunction();
            if (!func.IsValid()) {
                func.LowerOrderFunction.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS);
                func.LowerOrderFunction.Name.SetId(name);
                func.LowerOrderFunction.Name.SetType(type);
                if (argComp.IsValid()) {
                    func.LowerOrderFunction.AddParam(argComp);
                }

                func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR);                      
            }
        }
        public void buildSecondTernaryOperator()
        {
            int type;
            string name = pop(out type);

            StatementData statement = getCurStatement();
            FunctionData newFunc = new FunctionData();
            ValueData nname = new ValueData();
            newFunc.Name = nname;
            statement.Functions.Add(newFunc);

            FunctionData func = getLastFunction();
            if (!func.IsValid()) {
                func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR);
                func.Name.SetId(name);
                func.Name.SetType(type);
                func.Name.SetLine(getLastLineNumber());
            }
        }
        public void beginStatement()
        {
            StatementData statement = newStatementWithoutFunction();

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                if (statement.FirstComments.Count <= 0) {
                    statement.FirstCommentOnNewLine = commentOnNewLine;
                }
                statement.FirstComments.AddRange(cmts);
            }

            mStatementSemanticStack.Push(statement);
        }
        public void endStatement()
        {
            endStatementImpl(false);
        }
        public void addFunction()
        {
            StatementData statement = getCurStatement();
            if (null != mOnBeforeAddFunction) {
                mOnBeforeAddFunction(ref this, statement);
            }
            statement = getCurStatement();
            FunctionData func = newFunctionOfStatement(statement);
            if (null != mOnAddFunction) {
                mOnAddFunction(ref this, statement, func);
            }
        }
        public void setFunctionId()
        {
            int type;
            string name = pop(out type);
            FunctionData func = getLastFunction();
            if (!func.IsValid()) {
                func.Name.SetId(name);
                func.Name.SetType(type);
                func.Name.SetLine(getLastLineNumber());
            }
        }
        public void setMemberId()
        {
            int type;
            string name = pop(out type);
            FunctionData func = getLastFunction();
            if (!func.IsValid()) {
                func.Name.SetId(name);
                func.Name.SetType(type);
                func.Name.SetLine(getLastLineNumber());
            }
        }
        public void buildHighOrderFunction()
        {
            //高阶函数构造（当前函数返回一个函数）
            FunctionData func = getLastFunction();
            FunctionData temp = new FunctionData();
            temp.CopyFrom(func);
            func.Clear();
            func.LowerOrderFunction = temp;
        }
        public void markParenthesisParam()
        {
            FunctionData func = getLastFunction();

            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS);
        }
        public void markBracketParam()
        {
            FunctionData func = getLastFunction();

            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET);
        }
        public void markPeriodParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD);
        }
        public void markPeriodParenthesisParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_PARENTHESIS);
        }
        public void markPeriodBracketParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACKET);
        }
        public void markPeriodBraceParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACE);
        }
        public void markQuestionPeriodParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD);
        }
        public void markQuestionParenthesisParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PARENTHESIS);
        }
        public void markQuestionBracketParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACKET);
        }
        public void markQuestionBraceParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACE);
        }
        public void markStatement()
        {
            FunctionData func = getLastFunction();

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                if (func.IsHighOrder)
                    func.LowerOrderFunction.Comments.AddRange(cmts);
                else
                    func.Comments.AddRange(cmts);
            }

            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_STATEMENT);
        }
        public void markExternScript()
        {
            FunctionData func = getLastFunction();

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                if (func.IsHighOrder)
                    func.LowerOrderFunction.Comments.AddRange(cmts);
                else
                    func.Comments.AddRange(cmts);
            }

            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT);
        }
        public void markBracketColonParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET_COLON);
        }
        public void markParenthesisColonParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS_COLON);
        }        
        public void markAngleBracketColonParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_COLON);
        }
        public void markBracePercentParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACE_PERCENT);
        }
        public void markBracketPercentParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET_PERCENT);
        }
        public void markParenthesisPercentParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS_PERCENT);
        }
        public void markAngleBracketPercentParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT);
        }
        public void markColonColonParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON);
        }
        public void markColonColonParenthesisParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON_PARENTHESIS);
        }
        public void markColonColonBracketParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON_BRACKET);
        }
        public void markColonColonBraceParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_COLON_COLON_BRACE);
        }
        public void setExternScript()
        {
            FunctionData func = getLastFunction();
            func.AddParam(getLastToken(), ValueData.STRING_TOKEN);
        }
        public void markPointerParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER);
        }
        public void markPeriodStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_STAR);
        }
        public void markQuestionPeriodStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD_STAR);
        }
        public void markPointerStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER_STAR);
        }
        private void pushId()
        {
            push(getLastToken(), FunctionData.ID_TOKEN);
        }
        private void pushNum()
        {
            push(getLastToken(), FunctionData.NUM_TOKEN);
        }
        private void pushStr()
        {
            push(getLastToken(), FunctionData.STRING_TOKEN);
        }
        private void pushComma()
        {
            push(",", FunctionData.STRING_TOKEN);
        }
        private void pushSemiColon()
        {
            push(";", FunctionData.STRING_TOKEN);
        }
        /// ---------------------------------------------------------------
        /// 用于特定语法的语义行为，dsl目前提供lua精确语法与cpp类语言模糊语法的解析
        /// cpp类语言的解析主要识别括弧结构与分隔符分隔开的语句，可用于提取类接口等
        /// 简单应用
        /// ---------------------------------------------------------------
        private void pushDot()
        {
            push(".", FunctionData.STRING_TOKEN);
        }
        private void pushColon()
        {
            push(":", FunctionData.STRING_TOKEN);
        }
        private void pushAssignWith()
        {
            push("assignwith", FunctionData.ID_TOKEN);
        }
        ///a,b,c = d,e,f => lualist(a,b,c)assignwith(d,e,f)
        private void pushLuaList()
        {
            push("lualist", FunctionData.ID_TOKEN);
        }
        private void removeLuaList()
        {
            var statement = getCurStatement();
            var func = statement.First.AsFunction;
            if (null != func) {
                var p = func.GetParam(0);
                var st = p as Dsl.StatementData;
                if (null != st) {
                    popStatement();
                    mStatementSemanticStack.Push(st);
                }
                else {
                    var f = p as Dsl.FunctionData;
                    if (null != f) {
                        statement.Functions.Clear();
                        statement.AddFunction(f);
                    }
                    else {
                        var v = p as Dsl.ValueData;
                        if (null != v) {
                            func.Clear();
                            func.Name = v;
                        }
                        else {
                            mLog.Log("[error] unknown function call/variable syntax ! last token:{0} line {1}", getLastToken(), getLastLineNumber());
                        }
                    }
                }
            }
            endStatement();
        }
        private void checkLuaList()
        {
            var statement = getCurStatement();
            var func = statement.First.AsFunction;
            if (null != func) {
                for (int i = 0; i < func.GetParamNum(); ++i) {
                    var p = func.GetParam(i);
                    var f = p as Dsl.FunctionData;
                    if (null != f &&
                        f.GetParamClass() != (int)Dsl.FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD &&
                        f.GetParamClass() != (int)Dsl.FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET) {
                        mLog.Error("[error] Can only assignment to left value. {0}:{1} last token:{2} line {3}", f.GetLine(), f.ToScriptString(false), getLastToken(), getLastLineNumber());
                    }
                }
            }
        }
        ///for i = i1,i2,i3 do => for(i)luarange(i1,i2,i3){}
        private void pushLuaRange()
        {
            push("luarange", FunctionData.ID_TOKEN);
        }
        ///name <attr> => luavarattr(name, attr)
        private void pushLuaVarAttr()
        {
            push("luavarattr", FunctionData.ID_TOKEN);
        }
        private void removeLuaVarAttr()
        {
            var statement = getCurStatement();
            var func = statement.First.AsFunction;
            if (null != func) {
                var p = func.GetParam(0);
                var st = p as Dsl.StatementData;
                if (null != st) {
                    popStatement();
                    mStatementSemanticStack.Push(st);
                }
                else {
                    var f = p as Dsl.FunctionData;
                    if (null != f) {
                        statement.Functions.Clear();
                        statement.AddFunction(f);
                    }
                    else {
                        var v = p as Dsl.ValueData;
                        if (null != v) {
                            func.Clear();
                            func.Name = v;
                        }
                        else {
                            mLog.Log("[error] unknown function call/variable syntax ! last token:{0} line {1}", getLastToken(), getLastLineNumber());
                        }
                    }
                }
            }
            endStatement();
        }
        ///function name(arg) => function(name)args(arg)
        private void pushLuaArgs()
        {
            push("luaargs", FunctionData.ID_TOKEN);
        }
        ///::label:: => lualabel(label)
        private void pushLuaLabel()
        {
            push("lualabel", FunctionData.ID_TOKEN);
        }
        ///在每个函数结束时（可能是单个标识符样式、函数调用样式、高阶函数调用样式）对c++语句进行断句，
        ///这比在语法上精确定义处理起来更简单
        private void cppOnFunctionBegin()
        {
            var first = getFirstFunction();
            var last = getLastFunction();
            var firstId = first.GetId();
            var lastId = last.GetId();
            if (last.HaveStatement() && !firstId.StartsWith("@@") && firstId != "if" && firstId != "do" && firstId != "try" ||
                (firstId == "public" || firstId == "protected" || firstId == "private") && lastId == ":") {
                endStatement();
                beginStatement();
                return;
            }
        }
        private void cppOnFunctionEnd()
        {
            var statement = getCurStatement();
            var first = getFirstFunction();
            var firstFunc = first.AsFunction;
            var second = getSecondFunction();
            var last = getLastFunction();
            var firstId = first.GetId();
            var secondId = second.GetId();
            var lastId = last.GetId();
            if (firstId == "if" && null != firstFunc && firstFunc.HaveStatement() && lastId != "if" && lastId != "else" ||
                firstId == "do" && lastId != "while" ||
                firstId == "try" && lastId != "catch" && lastId != "finally") {
                statement.Functions.Remove(last);
                endStatement();
                beginStatement();
                var newStatement = getCurStatement();
                newStatement.Functions.Add(last);
                return;
            }
            //构造函数初始化列表转换为:的参数列表
            if (IsCppConstructor(statement, true)) {
                markParenthesisParam();
                beginStatement();
                return;
            }
            //构造函数初始化列表结束需要将函数体与最后一个初始化变量拆分
            if (last.HaveStatement() && mStatementSemanticStack.Count > 1) {
                StatementData parentSt = getCurParentStatement();
                if (IsCppConstructor(parentSt, false)) {
                    var ps = new List<ISyntaxComponent>(last.Params);
                    if (last.IsHighOrder) {
                        var curStatement = getCurStatement();
                        curStatement.Functions[curStatement.Functions.Count - 1] = last.LowerOrderFunction;
                    }
                    else {
                        last.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_NOTHING);
                        last.Params.Clear();
                    }
                    endStatement();
                    buildHighOrderFunction();
                    markStatement();
                    last = getLastFunction();
                    last.Params.AddRange(ps);
                }
            }
        }
        /// ---------------------------------------------------------------
        /// 特定语言工具函数
        /// ---------------------------------------------------------------
        private bool IsCppConstructor(StatementData statement, bool curIsColon)
        {
            bool ret = false;
            var first = statement.First;
            var firstFunc = first.AsFunction;
            var second = statement.Second;
            var secondFunc = second.AsFunction;
            var third = statement.Third;
            var last = statement.Last;
            var firstId = first.GetId();
            var secondId = second.GetId();
            var thirdId = third.GetId();
            if (firstId == "explicit" && null != secondFunc && secondFunc.HaveId() && secondFunc.HaveParam() && thirdId == ":" && (!curIsColon || third == last) ||
                null != firstFunc && firstFunc.HaveId() && firstFunc.HaveParam() && secondId == ":" && firstId != "case" && (!curIsColon || second == last)) {
                ret = true;
            }
            return ret;
        }

        /// ---------------------------------------------------------------
        /// 工具函数部分
        /// ---------------------------------------------------------------
        public void push(string s, int val)
        {
            mSemanticStack.Push(new SemanticInfo(s, val));
        }
        private string pop(out int val)
        {
            val = 0;
            if (mSemanticStack.Count == 0)
                return "null_stack_!!!";
            SemanticInfo info = mSemanticStack.Pop();
            val = info.value;
            return info.token;
        }
        private StatementData popStatement()
        {
            if (mStatementSemanticStack.Count == 0) {
                return newStatementWithoutFunction();
            }
            StatementData cdata = mStatementSemanticStack.Pop();
            return cdata;
        }
        public StatementData getCurStatement()
        {
            if (mStatementSemanticStack.Count == 0)
                return null;
            StatementData topData = mStatementSemanticStack.Peek();
            return topData;
        }
        public StatementData getCurParentStatement()
        {
            if (mStatementSemanticStack.Count <= 1)
                return null;
            var topData = mStatementSemanticStack.Pop();
            var parentData = mStatementSemanticStack.Peek();
            mStatementSemanticStack.Push(topData);
            return parentData;
        }
        public ValueOrFunctionData getFirstFunction()
        {
            StatementData statement = getCurStatement();
            return statement.First;
        }
        public ValueOrFunctionData getSecondFunction()
        {
            StatementData statement = getCurStatement();
            return statement.Second;
        }
        public ValueOrFunctionData getThirdFunction()
        {
            StatementData statement = getCurStatement();
            return statement.Third;
        }
        public FunctionData getLastFunction()
        {
            StatementData statement = getCurStatement();
            return statement.Last.AsFunction;
        }
        public StatementData newStatementWithOneFunction()
        {
            StatementData data = new StatementData();
            FunctionData func = new FunctionData();
            ValueData name = new ValueData();
            func.Name = name;
            data.Functions.Add(func);
            return data;
        }
        public StatementData newStatementWithoutFunction()
        {
            StatementData data = new StatementData();
            return data;
        }
        public FunctionData newFunctionOfStatement(StatementData data)
        {
            FunctionData func = new FunctionData();
            ValueData name = new ValueData();
            func.Name = name;
            data.Functions.Add(func);
            return func;
        }
        private AbstractSyntaxComponent simplifyStatement(StatementData data)
        {
            //对语句进行化简（语法分析过程中为了方便，全部按完整StatementData来构造，这里化简为原来的类型：ValueData/CallData/FunctionData等，主要涉及参数与语句部分）
            if (data.Functions.Count == 1) {
                //只有一个函数的语句退化为函数（再按函数进一步退化）。
                var f = data.Functions[0];
                f.CopyComments(data);
                if (f.IsValue)
                    return f;
                else
                    return simplifyStatement(f.AsFunction);
            }
            else {
                for(int i = 0; i < data.Functions.Count; ++i) {
                    var f = data.Functions[i];
                    var func = f.AsFunction;
                    if (null != func) {
                        data.Functions[i] = simplifyStatement(func);
                    }
                }
            }
            return data;
        }
        private ValueOrFunctionData simplifyStatement(FunctionData data)
        {
            //注意，为了省内存ValueData上不附带注释了，相关接口无实际效果！！！
            if (!data.HaveParamOrStatement()) {
                //没有参数的调用退化为基本值数据
                if (data.IsHighOrder) {
                    //这种情况应该不会出现
                    return data;
                }
                else {
                    return data.Name;
                }
            }
            else if (data.GetId() == "-" && data.GetParamNum() == 1) {
                ISyntaxComponent val = data.GetParam(0);
                ValueData temp = val as ValueData;
                if (null != temp && temp.IsNumber()) {
                    ValueData ret = new ValueData("-" + temp.GetId(), ValueData.NUM_TOKEN);
                    return ret;
                }
                else {
                    return data;
                }
            }
            else if (data.GetId() == "+" && data.GetParamNum() == 1) {
                ISyntaxComponent val = data.GetParam(0);
                ValueData temp = val as ValueData;
                if (null != temp && temp.IsNumber()) {
                    ValueData ret = new ValueData(temp.GetId(), ValueData.NUM_TOKEN);
                    return ret;
                }
                else {
                    return data;
                }
            }
            else {
                return data;
            }
        }

        private string getLastToken()
        {
            if (null != mGetLastToken)
                return mGetLastToken();
            else
                return string.Empty;
        }
        private int getLastLineNumber()
        {
            if (null != mGetLastLineNumber)
                return mGetLastLineNumber();
            else
                return -1;
        }
        private IList<string> GetComments(out bool commentOnNewLine)
        {
            if (null != mGetComments) {
                return mGetComments(out commentOnNewLine);
            }
            else {
                commentOnNewLine = false;
                return s_EmptyList;
            }

        }
        private void setStringDelimiter(string begin, string end)
        {
            if (null != mSetStringDelimiter) {
                mSetStringDelimiter(begin, end);
            }
        }
        private void setScriptDelimiter(string begin, string end)
        {
            if (null != mSetScriptDelimiter) {
                mSetScriptDelimiter(begin, end);
            }
        }

        private DslActionType mActionType;
        private DslLog mLog;
        private GetLastTokenDelegation mGetLastToken;
        private GetLastLineNumberDelegation mGetLastLineNumber;
        private GetCommentsDelegation mGetComments;
        private SetDelimiterDelegation mSetStringDelimiter;
        private SetDelimiterDelegation mSetScriptDelimiter;
        private BeforeAddFunctionDelegation mOnBeforeAddFunction;
        private AddFunctionDelegation mOnAddFunction;
        private BeforeEndStatementDelegation mOnBeforeEndStatement;
        private EndStatementDelegation mOnEndStatement;
        private List<ISyntaxComponent> mScriptDatas;
        private Stack<SemanticInfo> mSemanticStack;
        private Stack<StatementData> mStatementSemanticStack;

        private static List<string> s_EmptyList = new List<string>();

        private int CalcSeparator(string tok)
        {
            if (tok == ",")
                return AbstractSyntaxComponent.SEPARATOR_COMMA;
            else if (tok == ";")
                return AbstractSyntaxComponent.SEPARATOR_SEMICOLON;
            else
                return AbstractSyntaxComponent.SEPARATOR_NOTHING;
        }
    }
    internal interface IVisitor
    {
        void Visit(short[] production, int[] production_row, short[] parse, int[] parse_row, short start_symbol, short start_action);
    }
}
