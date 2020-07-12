using System;
using System.Collections.Generic;
using System.Text;

namespace Dsl.Parser
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
    struct DslAction
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
            //mLog.Log("{0}", DslString.GetProductionName(production_number));
        }
        internal void execute(int number)
        {
            switch (number) {
                case 1: endStatement(); break;
                case 2: markOperator(); break;
                case 3: pushId(); break;
                case 4: buildOperator(); break;
                case 5: buildFirstTernaryOperator(); break;
                case 6: buildSecondTernaryOperator(); break;
                case 7: beginStatement(); break;
                case 8: beginFunction(); break;
                case 9: endFunction(); break;
                case 10: setFunctionId(); break;
                case 11: markParenthesisParam(); break;
                case 12: buildHighOrderFunction(); break;
                case 13: markBracketParam(); break;
                case 14: markPeriod(); break;
                case 15: markQuestion(); break;
                case 16: markQuestionParenthesisParam(); break;
                case 17: markQuestionBracketParam(); break;
                case 18: markQuestionBraceParam(); break;
                case 19: markPointer(); break;
                case 20: markStatement(); break;
                case 21: markExternScript(); break;
                case 22: setExternScript(); break;
                case 23: markPeriodParam(); break;
                case 24: setMemberId(); break;
                case 25: markPeriodParenthesisParam(); break;
                case 26: markPeriodBracketParam(); break;
                case 27: markPeriodBraceParam(); break;
                case 28: markQuestionPeriodParam(); break;
                case 29: markPointerParam(); break;
                case 30: markPeriodStarParam(); break;
                case 31: markQuestionPeriodStarParam(); break;
                case 32: markPointerStarParam(); break;
                case 33: pushStr(); break;
                case 34: pushNum(); break;
                case 35: pushTrue(); break;
                case 36: pushFalse(); break;
            }
        }

        internal void markOperator()
        {
            StatementData statement = getCurStatement();

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                if (statement.LastComments.Count <= 0) {
                    statement.LastCommentOnNewLine = commentOnNewLine;
                }
                statement.LastComments.AddRange(cmts);
            }
        }
        internal void buildOperator()
        {
            int type;
            string name = pop(out type);

            StatementData arg = popStatement();
            ISyntaxComponent argComp = simplifyStatement(arg);

            StatementData _statement = newStatement();
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
        internal void buildFirstTernaryOperator()
        {
            int type;
            string name = pop(out type);

            StatementData arg = popStatement();
            ISyntaxComponent argComp = simplifyStatement(arg);

            StatementData _statement = newStatement();
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
        internal void buildSecondTernaryOperator()
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
        internal void beginStatement()
        {
            StatementData statement = newStatement();

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
        internal void endStatement()
        {
            StatementData statement = popStatement();
            if (statement.GetId() == "@@delimiter" && statement.Functions.Count == 1 && (statement.First.LowerOrderFunction.GetParamNum() == 1 || statement.First.LowerOrderFunction.GetParamNum() == 3) && !statement.First.LowerOrderFunction.IsHighOrder) {
                FunctionData call = statement.First.LowerOrderFunction;
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
                if (!statementSyntax.IsValid()) {
                    //_epsilon_表达式无语句语义
                    if (mScriptDatas.Count > 0 && statementSyntax.FirstComments.Count > 0) {
                        ISyntaxComponent last = mScriptDatas[mScriptDatas.Count - 1];
                        if (last.LastComments.Count <= 0) {
                            last.LastCommentOnNewLine = statementSyntax.FirstCommentOnNewLine;
                        }
                        last.LastComments.AddRange(statementSyntax.FirstComments);
                    }
                    return;
                }
                else {
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

                FunctionData func = getLastFunction();
                if (!statementSyntax.IsValid()) {
                    //_epsilon_表达式无语句语义
                    if (func.Params.Count > 0 && statementSyntax.FirstComments.Count > 0) {
                        AbstractSyntaxComponent last = func.Params[func.Params.Count - 1] as AbstractSyntaxComponent;
                        if (last.LastComments.Count <= 0) {
                            last.LastCommentOnNewLine = statementSyntax.FirstCommentOnNewLine;
                        }
                        last.LastComments.AddRange(statementSyntax.FirstComments);
                    }
                    return;
                }
                else {
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
                        else {
                            func.Comments.Add(cmt);
                        }
                    }
                }
                func.AddParam(statementSyntax);
            }
        }
        internal void beginFunction()
        {
            StatementData statement = getCurStatement();
            FunctionData func = getLastFunction();
            if (func.IsValid()) {
                //语句的多元函数的其它元函数名
                FunctionData newFunc = new FunctionData();
                ValueData name = new ValueData();
                newFunc.Name = name;

                statement.Functions.Add(newFunc);
            }
        }
        internal void setFunctionId()
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
        internal void setMemberId()
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
        internal void endFunction()
        {
        }
        internal void buildHighOrderFunction()
        {
            //高阶函数构造（当前函数返回一个函数）
            FunctionData func = getLastFunction();
            FunctionData temp = new FunctionData();
            temp.CopyFrom(func);
            func.Clear();
            func.LowerOrderFunction = temp;
        }
        internal void markParenthesisParam()
        {
            FunctionData func = getLastFunction();

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                func.Comments.AddRange(cmts);
            }

            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PARENTHESIS);
        }
        internal void markBracketParam()
        {
            FunctionData func = getLastFunction();

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                func.Comments.AddRange(cmts);
            }

            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_BRACKET);
        }
        internal void markPeriod()
        {
            FunctionData func = getLastFunction();

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                func.Comments.AddRange(cmts);
            }
        }
        internal void markPeriodParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD);
        }
        internal void markPeriodParenthesisParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_PARENTHESIS);
        }
        internal void markPeriodBracketParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACKET);
        }
        internal void markPeriodBraceParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_BRACE);
        }
        internal void markQuestion()
        {
            FunctionData func = getLastFunction();

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                func.Comments.AddRange(cmts);
            }
        }
        internal void markQuestionPeriodParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD);
        }
        internal void markQuestionParenthesisParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PARENTHESIS);
        }
        internal void markQuestionBracketParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACKET);
        }
        internal void markQuestionBraceParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_BRACE);
        }
        internal void markPointer()
        {
            FunctionData func = getLastFunction();

            bool commentOnNewLine;
            IList<string> cmts = GetComments(out commentOnNewLine);
            if (cmts.Count > 0) {
                func.Comments.AddRange(cmts);
            }
        }
        internal void markStatement()
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
        internal void markExternScript()
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
        internal void setExternScript()
        {
            FunctionData func = getLastFunction();
            func.AddParam(getLastToken());
        }
        internal void markPointerParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER);
        }
        internal void markPeriodStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_PERIOD_STAR);
        }
        internal void markQuestionPeriodStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_QUESTION_PERIOD_STAR);
        }
        internal void markPointerStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)FunctionData.ParamClassEnum.PARAM_CLASS_POINTER_STAR);
        }
        internal void pushId()
        {
            push(getLastToken(), FunctionData.ID_TOKEN);
        }
        internal void pushNum()
        {
            push(getLastToken(), FunctionData.NUM_TOKEN);
        }
        internal void pushStr()
        {
            push(getLastToken(), FunctionData.STRING_TOKEN);
        }
        internal void pushTrue()
        {
            push("true", FunctionData.BOOL_TOKEN);
        }
        internal void pushFalse()
        {
            push("false", FunctionData.BOOL_TOKEN);
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
                return newStatement();
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
        private StatementData newStatement()
        {
            StatementData data = new StatementData();
            FunctionData func = new FunctionData();
            ValueData name = new ValueData();
            func.Name = name;
            data.Functions.Add(func);
            return data;
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
            if (!data.HaveParamOrStatement()) {
                //没有参数的调用退化为基本值数据
                if (data.IsHighOrder) {
                    //这种情况应该不会出现
                    return data;
                }
                else {
                    data.Name.CopyComments(data);
                    return data.Name;
                }
            }
            else if (data.GetId() == "-" && data.GetParamNum() == 1) {
                ISyntaxComponent val = data.GetParam(0);
                ValueData temp = val as ValueData;
                if (null != temp && temp.IsNumber()) {
                    ValueData ret = new ValueData("-" + temp.GetId(), ValueData.NUM_TOKEN);
                    ret.CopyComments(temp);
                    ret.CopyComments(data);
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
                    ret.CopyComments(temp);
                    ret.CopyComments(data);
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
