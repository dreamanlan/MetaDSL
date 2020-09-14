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
    delegate string GetLastTokenDelegation();
    delegate int GetLastLineNumberDelegation();
    delegate IList<string> GetCommentsDelegation(out bool commentOnNewLine);
    delegate void SetDelimiterDelegation(string begin, string end);
    internal enum DslActionType
    {
        Dsl = 0,
        Lua,
        Cpp,
    }
    internal struct DslAction
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

        internal void predict(short production_number)
        {
            /*
            switch (mActionType) {
                case DslActionType.Dsl:
                    mLog.Log("{0}", Dsl.Parser.DslString.GetProductionName(production_number));
                    break;
                case DslActionType.Lua:
                    mLog.Log("{0}", Lua.Parser.LuaString.GetProductionName(production_number));
                    break;
                case DslActionType.Cpp:
                    mLog.Log("{0}", Cpp.Parser.CppString.GetProductionName(production_number));
                    break;
            }
            */
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
                case 1: endStatement(); break;
                case 2: pushId(); break;
                case 3: buildOperator(); break;
                case 4: buildFirstTernaryOperator(); break;
                case 5: buildSecondTernaryOperator(); break;
                case 6: beginStatement(); break;
                case 7: addFunction(); break;
                case 8: setFunctionId(); break;
                case 9: markParenthesisParam(); break;
                case 10: buildHighOrderFunction(); break;
                case 11: markBracketParam(); break;
                case 12: markQuestionParenthesisParam(); break;
                case 13: markQuestionBracketParam(); break;
                case 14: markQuestionBraceParam(); break;
                case 15: markStatement(); break;
                case 16: markExternScript(); break;
                case 17: setExternScript(); break;
                case 18: markBracketAttrParam(); break;
                case 19: markParenthesisAttrParam(); break;
                case 20: markPeriodParam(); break;
                case 21: setMemberId(); break;
                case 22: markPeriodParenthesisParam(); break;
                case 23: markPeriodBracketParam(); break;
                case 24: markPeriodBraceParam(); break;
                case 25: markQuestionPeriodParam(); break;
                case 26: markPointerParam(); break;
                case 27: markPeriodStarParam(); break;
                case 28: markQuestionPeriodStarParam(); break;
                case 29: markPointerStarParam(); break;
                case 30: pushStr(); break;
                case 31: pushNum(); break;
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
                case 7: endStatement(); break;
                case 8: pushLuaList(); break;
                case 9: checkLuaList(); break;
                case 10: pushAssignWith(); break;
                case 11: removeLuaList(); break;
                case 12: pushLuaLabel(); break;
                case 13: buildHighOrderFunction(); break;
                case 14: pushLuaRange(); break;
                case 15: pushLuaVarAttr(); break;
                case 16: markBracketAttrParam(); break;
                case 17: removeLuaVarAttr(); break;
                case 18: markParenthesisAttrParam(); break;
                case 19: pushDot(); break;
                case 20: pushColon(); break;
                case 21: pushLuaArgs(); break;
                case 22: buildOperator(); break;
                case 23: markBracketParam(); break;
                case 24: markPeriodParam(); break;
                case 25: setMemberId(); break;
                case 26: markPointerParam(); break;
                case 27: pushStr(); break;
                case 28: pushNum(); break;
            }
        }
        private void executeCpp(int number)
        {
            switch (number) {
                case 1: endStatement(); break;
                case 2: beginStatement(); break;
                case 3: addFunction(); break;
                case 4: setFunctionId(); break;
                case 5: markParenthesisParam(); break;
                case 6: buildHighOrderFunction(); break;
                case 7: markBracketParam(); break;
                case 8: markStatement(); break;
                case 9: pushId(); break;
                case 10: pushStr(); break;
                case 11: pushNum(); break;
            }
        }

        private void buildOperator()
        {
            int type;
            string name = pop(out type);

            StatementData arg = popStatement();
            ISyntaxComponent argComp = simplifyStatement(arg);

            StatementData _statement = newStatementWithOneFunction();
            FunctionData first = _statement.First;
            first.Name.SetLine(getLastLineNumber());

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
        private void buildFirstTernaryOperator()
        {
            int type;
            string name = pop(out type);

            StatementData arg = popStatement();
            ISyntaxComponent argComp = simplifyStatement(arg);

            StatementData _statement = newStatementWithOneFunction();
            FunctionData first = _statement.First;

            //三元运算符表示成op1(cond)(true_val)op2(false_val)
            first.LowerOrderFunction = new FunctionData();
            first.LowerOrderFunction.Name = new ValueData();
            first.LowerOrderFunction.Name.SetLine(getLastLineNumber());

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
        private void buildSecondTernaryOperator()
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
        private void beginStatement()
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
        private void endStatement()
        {
            StatementData statement = popStatement();
            if ((null != mSetStringDelimiter || null != mSetScriptDelimiter) && statement.GetId() == "@@delimiter" && statement.Functions.Count == 1 && (statement.First.GetParamNum() == 1 || statement.First.GetParamNum() == 3) && !statement.First.IsHighOrder) {
                FunctionData call = statement.First;
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
                func.AddParam(statementSyntax);
            }
        }
        private void addFunction()
        {
            StatementData statement = getCurStatement();
            FunctionData func = newFunctionOfStatement(statement);
        }
        private void setFunctionId()
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
        private void setMemberId()
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
        private void buildHighOrderFunction()
        {
            //高阶函数构造（当前函数返回一个函数）
            FunctionData func = getLastFunction();
            FunctionData temp = new FunctionData();
            temp.CopyFrom(func);
            func.Clear();
            func.LowerOrderFunction = temp;
        }
        private void markParenthesisParam()
        {
            FunctionData func = getLastFunction();

            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS);
        }
        private void markBracketParam()
        {
            FunctionData func = getLastFunction();

            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET);
        }
        private void markPeriodParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD);
        }
        private void markPeriodParenthesisParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_PARENTHESIS);
        }
        private void markPeriodBracketParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACKET);
        }
        private void markPeriodBraceParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACE);
        }
        private void markQuestionPeriodParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD);
        }
        private void markQuestionParenthesisParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PARENTHESIS);
        }
        private void markQuestionBracketParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACKET);
        }
        private void markQuestionBraceParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACE);
        }
        private void markStatement()
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
        private void markExternScript()
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
        private void markBracketAttrParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET_ATTR);
        }
        private void markParenthesisAttrParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS_ATTR);
        }
        private void setExternScript()
        {
            FunctionData func = getLastFunction();
            func.AddParam(getLastToken());
        }
        private void markPointerParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER);
        }
        private void markPeriodStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_STAR);
        }
        private void markQuestionPeriodStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD_STAR);
        }
        private void markPointerStarParam()
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
        //a,b,c = d,e,f => lualist(a,b,c)assignwith(d,e,f)
        private void pushLuaList()
        {
            push("lualist", FunctionData.ID_TOKEN);
        }
        private void removeLuaList()
        {
            var statement = getCurStatement();
            var func = statement.First;
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
            endStatement();
        }
        private void checkLuaList()
        {
            var statement = getCurStatement();
            var func = statement.First;
            for(int i = 0; i < func.GetParamNum(); ++i) {
                var p = func.GetParam(i);
                var f = p as Dsl.FunctionData;
                if (null != f &&
                    f.GetParamClass() != (int)Dsl.FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD &&
                    f.GetParamClass() != (int)Dsl.FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET) {
                    mLog.Error("[error] Can only assignment to left value. {0}:{1} last token:{2} line {3}", f.GetLine(), f.ToScriptString(false), getLastToken(), getLastLineNumber());
                }
            }
        }
        //for i = i1,i2,i3 do => for(i)luarange(i1,i2,i3){}
        private void pushLuaRange()
        {
            push("luarange", FunctionData.ID_TOKEN);
        }
        //name <attr> => luavarattr(name, attr)
        private void pushLuaVarAttr()
        {
            push("luavarattr", FunctionData.ID_TOKEN);
        }
        private void removeLuaVarAttr()
        {
            var statement = getCurStatement();
            var func = statement.First;
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
            endStatement();
        }
        //function name(arg) => function(name)args(arg)
        private void pushLuaArgs()
        {
            push("luaargs", FunctionData.ID_TOKEN);
        }
        //::label:: => lualabel(label)
        private void pushLuaLabel()
        {
            push("lualabel", FunctionData.ID_TOKEN);
        }

        private void push(string s, int val)
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
        private StatementData getCurStatement()
        {
            if (mStatementSemanticStack.Count == 0)
                return null;
            StatementData topData = mStatementSemanticStack.Peek();
            return topData;
        }
        private FunctionData getFirstFunction()
        {
            StatementData statement = getCurStatement();
            return statement.First;
        }
        private FunctionData getSecondFunction()
        {
            StatementData statement = getCurStatement();
            return statement.Second;
        }
        private FunctionData getLastFunction()
        {
            StatementData statement = getCurStatement();
            return statement.Last;
        }
        private StatementData newStatementWithOneFunction()
        {
            StatementData data = new StatementData();
            FunctionData func = new FunctionData();
            ValueData name = new ValueData();
            func.Name = name;
            data.Functions.Add(func);
            return data;
        }
        private StatementData newStatementWithoutFunction()
        {
            StatementData data = new StatementData();
            return data;
        }
        private FunctionData newFunctionOfStatement(StatementData data)
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
                FunctionData func = data.Functions[0];
                func.CopyComments(data);
                return simplifyStatement(func);
            }
            return data;
        }
        private AbstractSyntaxComponent simplifyStatement(FunctionData data)
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
        private List<ISyntaxComponent> mScriptDatas;
        private Stack<SemanticInfo> mSemanticStack;
        private Stack<StatementData> mStatementSemanticStack;

        private static List<string> s_EmptyList = new List<string>();
    }
}
