using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Runtime.InteropServices;
using System.Text;

namespace Dsl.Common
{
    /*
    * Memo: Why use reduction instead of delayed one-time construction
    * 1. We have tried to use a temporary structure such as SyntaxMaterial to collect data during the syntax parsing process, and then construct the statement when the statement is completed.
    * 2. The temporary structure is very similar to the final semantic data structure. It also needs to represent the recursive structure and be associated with the existing semantic data. The code is repeated and the logic is not clear enough.
    * 3. The reduction method has tried its best to reuse the instances constructed in the grammar parsing, and basically does not cause additional memory usage.
    * 4. In the reduction mode, the final memory usage is linearly related to the script complexity, so there is no need to worry about taking up too much memory.
    * 5. The definition of semantic data takes degradation situations into consideration and tries not to occupy additional space except for necessary data.
    */
    public enum OperatorCategoryEnum
    {
        OPERATOR_CATEGORY_NORMAL = 0,
        OPERATOR_CATEGORY_TERNARY,
        OPERATOR_CATEGORY_MAXNUM
    }
    public enum PairTypeEnum
    {
        PAIR_TYPE_NONE = 0,
        PAIR_TYPE_QUESTION_COLON,
        PAIR_TYPE_PARENTHESES,
        PAIR_TYPE_BRACKET,
        PAIR_TYPE_BRACE,
        PAIR_TYPE_BRACKET_COLON,
        PAIR_TYPE_PARENTHESES_COLON,
        PAIR_TYPE_ANGLE_BRACKET_COLON,
        PAIR_TYPE_BRACE_PERCENT,
        PAIR_TYPE_BRACKET_PERCENT,
        PAIR_TYPE_PARENTHESES_PERCENT,
        PAIR_TYPE_ANGLE_BRACKET_PERCENT,
        PAIR_TYPE_MAXNUM
    }
    public delegate bool TokenCanEatCharDelegation(StringBuilder tokenBuilder, char c);
    public delegate bool GetCppTokenDelegation(ref DslAction dslAction, ref CppToken dslToken, ref string tok, ref short val, ref int line);
    public delegate bool GetTokenDelegation(ref DslAction dslAction, ref DslToken dslToken, ref string tok, ref short val, ref int line);
    public delegate bool BeforeAddFunctionDelegation(ref DslAction dslAction, StatementData statement);
    public delegate bool AddFunctionDelegation(ref DslAction dslAction, StatementData statement, FunctionData function);
    public delegate bool BeforeEndStatementDelegation(ref DslAction dslAction, StatementData statement);
    public delegate bool EndStatementDelegation(ref DslAction dslAction, ref StatementData statement);
    public delegate bool BeforeBuildOperatorDelegation(ref DslAction dslAction, OperatorCategoryEnum category, string op, StatementData statement);
    public delegate bool BuildOperatorDelegation(ref DslAction dslAction, OperatorCategoryEnum category, string op, ref StatementData statement);
    public delegate bool SetFunctionIdDelegation(ref DslAction dslAction, string name, StatementData statement, FunctionData function);
    public delegate bool BeforeBuildHighOrderDelegation(ref DslAction dslAction, StatementData statement, FunctionData function);
    public delegate bool BuildHighOrderDelegation(ref DslAction dslAction, StatementData statement, FunctionData function);

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
            mPairTypeStack = new Stack<uint>();
            mNameTags = null;

            mGetLastToken = null;
            mGetLastLineNumber = null;
            mGetComments = null;
            mSetStringDelimiter = null;
            mSetScriptDelimiter = null;
            mOnBeforeAddFunction = null;
            mOnAddFunction = null;
            mOnBeforeEndStatement = null;
            mOnEndStatement = null;
            mOnBeforeBuildOperator = null;
            mOnBuildOperator = null;
            mOnSetFunctionId = null;
            mOnBeforeBuildHighOrder = null;
            mOnBuildHighOrder = null;
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
        internal GetCommentsDelegation onGetComments
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
        internal BeforeBuildOperatorDelegation onBeforeBuildOperator
        {
            get { return mOnBeforeBuildOperator; }
            set { mOnBeforeBuildOperator = value; }
        }
        internal BuildOperatorDelegation onBuildOperator
        {
            get { return mOnBuildOperator; }
            set { mOnBuildOperator = value; }
        }
        internal SetFunctionIdDelegation onSetFunctionId
        {
            get { return mOnSetFunctionId; }
            set { mOnSetFunctionId = value; }
        }
        internal BeforeBuildHighOrderDelegation onBeforeBuildHighOrder
        {
            get { return mOnBeforeBuildHighOrder; }
            set { mOnBeforeBuildHighOrder = value; }
        }
        internal BuildHighOrderDelegation onBuildHighOrder
        {
            get { return mOnBuildHighOrder; }
            set { mOnBuildHighOrder = value; }
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
                case 10: buildNullableOperator(); break;
                case 11: markParenthesesParam(); break;
                case 12: markParenthesesParamEnd(); break;
                case 13: buildHighOrderFunction(); break;
                case 14: markBracketParam(); break;
                case 15: markBracketParamEnd(); break;
                case 16: markStatement(); break;
                case 17: markStatementEnd(); break;
                case 18: markExternScript(); break;
                case 19: setExternScript(); break;
                case 20: markBracketColonParam(); break;
                case 21: markBracketColonParamEnd(); break;
                case 22: markParenthesesColonParam(); break;
                case 23: markParenthesesColonParamEnd(); break;
                case 24: markAngleBracketColonParam(); break;
                case 25: markAngleBracketColonParamEnd(); break;
                case 26: markBracePercentParam(); break;
                case 27: markBracePercentParamEnd(); break;
                case 28: markBracketPercentParam(); break;
                case 29: markBracketPercentParamEnd(); break;
                case 30: markParenthesesPercentParam(); break;
                case 31: markParenthesesPercentParamEnd(); break;
                case 32: markAngleBracketPercentParam(); break;
                case 33: markAngleBracketPercentParamEnd(); break;
                case 34: markColonColonParam(); break;
                case 35: markPeriodParam(); break;
                case 36: markPointerParam(); break;
                case 37: markPeriodStarParam(); break;
                case 38: markPointerStarParam(); break;
                case 39: pushStr(); break;
                case 40: pushNum(); break;
                case 41: pushDollarStr(); break;
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
                case 6: markParenthesesParam(); break;
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
                case 24: markParenthesesColonParam(); break;
                case 25: markPeriodParam(); break;
                case 26: markPointerParam(); break;
                case 27: pushStr(); break;
                case 28: pushNum(); break;
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
                case 8: markParenthesesParam(); break;
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
                var stm = getCurStatement();
                Debug.Assert(null != stm);
                mOnBeforeEndStatement(ref this, stm);
            }
            StatementData statement = popStatement();
            if (null != mOnEndStatement) {
                mOnEndStatement(ref this, ref statement);
                Debug.Assert(null != statement);
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
                //Simplification only needs to handle the first level, and the parameters and statement parts
                //should have already been processed when added to the statement.
                AbstractSyntaxComponent statementSyntax = simplifyStatement(statement);
                ValueData vdSyntax = statementSyntax as ValueData;
                if (!statementSyntax.IsValid()) {
                    //The "epsilon" expression has no statement semantics.
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
                    //If the statement is a regular value, move the comment to the previous statement.
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
                    //Move the comment from the previous line of code to the line above.
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
                //Top-level element ends.
                if (addSep && mScriptDatas.Count > 0) {
                    var lastStm = mScriptDatas[mScriptDatas.Count - 1];
                    lastStm.SetSeparator(AbstractSyntaxComponent.SEPARATOR_SEMICOLON);
                }
                mScriptDatas.Add(statementSyntax);
            }
            else {
                //Simplification only needs to handle the first level. The parameters and statement parts
                //should have already been processed when added to the statement.
                AbstractSyntaxComponent statementSyntax = simplifyStatement(statement);
                ValueData vdSyntax = statementSyntax as ValueData;
                FunctionData func = getLastFunction();
                if (func.HaveParam()) {
                    //If it is a comment within the parameters, keep it as it is. Comments on regular values
                    //will be discarded, and if embedded comments are moved to the end of the line, it may
                    //appear inexplicable.
                    //if (!statementSyntax.IsValid())
                    //    return;
                }
                else if (!statement.IsValid()) {
                    //The "epsilon" expression has no statement semantics.
                    if (func.Params.Count > 0 && statementSyntax.FirstComments.Count > 0) {
                        AbstractSyntaxComponent last = func.Params[func.Params.Count - 1] as AbstractSyntaxComponent;
                        if (last.LastComments.Count <= 0) {
                            last.LastCommentOnNewLine = statementSyntax.FirstCommentOnNewLine;
                        }
                        last.LastComments.AddRange(statementSyntax.FirstComments);
                        last.LastComments.AddRange(statementSyntax.LastComments);
                    }
                    //return;
                }
                else if (null != vdSyntax) {
                    //If the statement is a regular value, move the comment to the previous statement.
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
                    //Move the comment from the previous line of code to the line above.
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
                    lastParam.SetSeparator(func.GetParamClassUnmasked() == (int)ParamClassEnum.PARAM_CLASS_STATEMENT ? AbstractSyntaxComponent.SEPARATOR_SEMICOLON : AbstractSyntaxComponent.SEPARATOR_COMMA);
                }
                func.AddParam(statementSyntax);
            }
        }
        private void endStatementLua()
        {
            endStatementImpl(true);
        }

        public void SetNameTags(Dictionary<string, uint> tags)
        {
            mNameTags = tags;
        }
        public PairTypeEnum PeekPairTypeStack()
        {
            return PeekPairTypeStack(out var tag);
        }
        public PairTypeEnum PeekPairTypeStack(out uint tag)
        {
            var ret = PairTypeEnum.PAIR_TYPE_NONE;
            tag = 0;
            if (mPairTypeStack.Count > 0) {
                uint v = mPairTypeStack.Peek();
                tag = (v >> 8);
                ret = (PairTypeEnum)(v & 0x0ff);
            }
            return ret;
        }
        public int GetPairTypeStackSize()
        {
            return mPairTypeStack.Count;
        }
        public PairTypeEnum PeekPairTypeStack(int ix)
        {
            return PeekPairTypeStack(ix, out var tag);
        }
        public PairTypeEnum PeekPairTypeStack(int ix, out uint tag)
        {
            var ret = PairTypeEnum.PAIR_TYPE_NONE;
            tag = 0;
            if (ix >= 0 && ix < mPairTypeStack.Count) {
                int i = 0;
                foreach(var v in mPairTypeStack) {
                    if (i == ix) {
                        tag = (v >> 8);
                        ret = (PairTypeEnum)(v & 0x0ff);
                        break;
                    }
                    ++i;
                }
            }
            return ret;
        }
        private void PushPairType(PairTypeEnum pairType)
        {
            PushPairType(pairType, 0);
        }
        private void PushPairType(PairTypeEnum pairType, uint tag)
        {
            uint v = (tag << 8) + (uint)pairType;
            mPairTypeStack.Push(v);
        }
        private void PopPairType()
        {
            if (mPairTypeStack.Count > 0) {
                mPairTypeStack.Pop();
            }
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

            StatementData arg = getCurStatement();
            Debug.Assert(null != arg);
            if (null != mOnBeforeBuildOperator) {
                mOnBeforeBuildOperator(ref this, OperatorCategoryEnum.OPERATOR_CATEGORY_NORMAL, name, arg);
            }
            arg = popStatement();
            if (null != mOnBuildOperator) {
                mOnBuildOperator(ref this, OperatorCategoryEnum.OPERATOR_CATEGORY_NORMAL, name, ref arg);
                Debug.Assert(null != arg);
            }

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

            FunctionData func = getLastFunction();
            if (!func.IsValid()) {
                if (name.Length > 0 && name[0] == '`') {
                    func.SetParamClass((int)(ParamClassEnum.PARAM_CLASS_WRAP_INFIX_CALL_MASK | ParamClassEnum.PARAM_CLASS_OPERATOR));

                    func.Name.SetId(name.Substring(1));
                    func.Name.SetType(type);
                }
                else {
                    func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_OPERATOR);

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

            StatementData arg = getCurStatement();
            Debug.Assert(null != arg);
            if (null != mOnBeforeBuildOperator) {
                mOnBeforeBuildOperator(ref this, OperatorCategoryEnum.OPERATOR_CATEGORY_TERNARY, name, arg);
            }
            arg = popStatement();
            if (null != mOnBuildOperator) {
                mOnBuildOperator(ref this, OperatorCategoryEnum.OPERATOR_CATEGORY_TERNARY, name, ref arg);
                Debug.Assert(null != arg);
            }

            ISyntaxComponent argComp = simplifyStatement(arg);

            StatementData _statement = newStatementWithOneFunction();
            FunctionData first = _statement.First.AsFunction;
            if (null != first) {
                //The ternary operator is represented as op1(cond)(true_val)op2(false_val)
                first.LowerOrderFunction = new FunctionData();
                first.LowerOrderFunction.Name = new ValueData();
                first.LowerOrderFunction.Name.SetLine(getLastLineNumber());
            }
            _statement.CopyFirstComments(argComp);
            argComp.FirstComments.Clear();

            mStatementSemanticStack.Push(_statement);
            PushPairType(PairTypeEnum.PAIR_TYPE_QUESTION_COLON);

            FunctionData func = getLastFunction();
            if (!func.IsValid()) {
                func.LowerOrderFunction.SetParamClass((int)ParamClassEnum.PARAM_CLASS_PARENTHESES);
                func.LowerOrderFunction.Name.SetId(name);
                func.LowerOrderFunction.Name.SetType(type);
                if (argComp.IsValid()) {
                    func.LowerOrderFunction.AddParam(argComp);
                }

                func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR);
            }
        }
        public void buildSecondTernaryOperator()
        {
            int type;
            string name = pop(out type);

            StatementData statement = getCurStatement();
            Debug.Assert(null != statement);
            if (null != mOnBeforeBuildOperator) {
                mOnBeforeBuildOperator(ref this, OperatorCategoryEnum.OPERATOR_CATEGORY_TERNARY, name, statement);
                statement = getCurStatement();
                Debug.Assert(null != statement);
            }

            PopPairType();

            FunctionData newFunc = new FunctionData();
            ValueData nname = new ValueData();
            newFunc.Name = nname;
            statement.Functions.Add(newFunc);

            FunctionData func = getLastFunction();
            if (!func.IsValid()) {
                func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR);
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
            Debug.Assert(null != statement);
            if (null != mOnBeforeAddFunction) {
                mOnBeforeAddFunction(ref this, statement);
                statement = getCurStatement();
                Debug.Assert(null != statement);
            }
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
            if (null != mOnSetFunctionId) {
                StatementData stm = getCurStatement();
                Debug.Assert(null != stm);
                mOnSetFunctionId(ref this, name, stm, func);
            }
        }
        public void buildNullableOperator()
        {
            int type;
            string name = pop(out type);

            FunctionData func = getLastFunction();
            if (name == "?")
                func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_QUESTION_NULLABLE_OPERATOR);
            else
                func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR);

            if (null != mOnBeforeBuildHighOrder) {
                StatementData stm = getCurStatement();
                Debug.Assert(null != stm);
                mOnBeforeBuildHighOrder(ref this, stm, func);
                func = getLastFunction();
            }
            FunctionData temp = new FunctionData();
            temp.CopyFrom(func);
            func.Clear();
            func.LowerOrderFunction = temp;
            if (null != mOnBuildHighOrder) {
                StatementData stm = getCurStatement();
                Debug.Assert(null != stm);
                mOnBuildHighOrder(ref this, stm, func);
            }
        }
        public void buildHighOrderFunction()
        {
            //Higher-order function construction (the current function returns another function).
            FunctionData func = getLastFunction();
            if (null != mOnBeforeBuildHighOrder) {
                StatementData stm = getCurStatement();
                Debug.Assert(null != stm);
                mOnBeforeBuildHighOrder(ref this, stm, func);
                func = getLastFunction();
            }
            FunctionData temp = new FunctionData();
            temp.CopyFrom(func);
            func.Clear();
            func.LowerOrderFunction = temp;
            if (null != mOnBuildHighOrder) {
                StatementData stm = getCurStatement();
                Debug.Assert(null != stm);
                mOnBuildHighOrder(ref this, stm, func);
            }
        }
        public void markParenthesesParam()
        {
            FunctionData func = getLastFunction();

            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_PARENTHESES);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_PARENTHESES, tag);
        }
        public void markParenthesesParamEnd()
        {
            PopPairType();
        }
        public void markBracketParam()
        {
            FunctionData func = getLastFunction();

            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_BRACKET);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_BRACKET, tag);
        }
        public void markBracketParamEnd()
        {
            PopPairType();
        }
        public void markPeriodParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_PERIOD);
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

            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_STATEMENT);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_BRACE, tag);
        }
        public void markStatementEnd()
        {
            PopPairType();
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

            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT);
        }
        public void markBracketColonParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_BRACKET_COLON);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_BRACKET_COLON, tag);
        }
        public void markBracketColonParamEnd()
        {
            PopPairType();
        }
        public void markParenthesesColonParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_PARENTHESES_COLON);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_PARENTHESES_COLON, tag);
        }
        public void markParenthesesColonParamEnd()
        {
            PopPairType();
        }
        public void markAngleBracketColonParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_COLON);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_ANGLE_BRACKET_COLON, tag);
        }
        public void markAngleBracketColonParamEnd()
        {
            PopPairType();
        }
        public void markBracePercentParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_BRACE_PERCENT);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_BRACE_PERCENT, tag);
        }
        public void markBracePercentParamEnd()
        {
            PopPairType();
        }
        public void markBracketPercentParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_BRACKET_PERCENT);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_BRACKET_PERCENT, tag);
        }
        public void markBracketPercentParamEnd()
        {
            PopPairType();
        }
        public void markParenthesesPercentParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_PARENTHESES_PERCENT);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_PARENTHESES_PERCENT, tag);
        }
        public void markParenthesesPercentParamEnd()
        {
            PopPairType();
        }
        public void markAngleBracketPercentParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT);
            uint tag = 0;
            if (null != mNameTags) {
                mNameTags.TryGetValue(func.GetId(), out tag);
            }
            PushPairType(PairTypeEnum.PAIR_TYPE_ANGLE_BRACKET_PERCENT, tag);
        }
        public void markAngleBracketPercentParamEnd()
        {
            PopPairType();
        }
        public void markColonColonParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_COLON_COLON);
        }
        public void setExternScript()
        {
            FunctionData func = getLastFunction();
            func.AddParam(getLastToken(), ValueData.STRING_TOKEN);
        }
        public void markPointerParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_POINTER);
        }
        public void markPeriodStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_PERIOD_STAR);
        }
        public void markPointerStarParam()
        {
            FunctionData func = getLastFunction();
            func.SetParamClass((int)ParamClassEnum.PARAM_CLASS_POINTER_STAR);
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
        private void pushDollarStr()
        {
            push(getLastToken(), FunctionData.DOLLAR_STRING_TOKEN);
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
        /// Used for semantic behavior specific to a certain syntax. The DSL currently provides parsing for both precise Lua syntax and fuzzy syntax similar to C++-like languages.
        /// Parsing for C++-like languages mainly recognizes bracket structures and statements separated by delimiters, which can be used to extract class interfaces, etc.
        /// Simple application.
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
            Debug.Assert(null != statement);
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
            Debug.Assert(null != statement);
            var func = statement.First.AsFunction;
            if (null != func) {
                for (int i = 0; i < func.GetParamNum(); ++i) {
                    var p = func.GetParam(i);
                    var f = p as Dsl.FunctionData;
                    if (null != f &&
                        f.GetParamClass() != (int)Dsl.ParamClassEnum.PARAM_CLASS_PERIOD &&
                        f.GetParamClass() != (int)Dsl.ParamClassEnum.PARAM_CLASS_BRACKET) {
                        mLog.Error("[error] Can only assignment to left value. {0}:{1} last token:{2} line {3}", f.GetLine(), f.ToScriptString(false, DelimiterInfo.Default), getLastToken(), getLastLineNumber());
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
            Debug.Assert(null != statement);
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
        /// At the end of each function (which may be in the form of a single identifier, function call, or higher-order function call), the C++ statements are segmented.
        /// This is simpler to handle than defining it precisely in terms of syntax.
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
            Debug.Assert(null != statement);
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
            //Convert constructor initialization lists to a parameter list of ":".
            if (IsCppConstructor(statement, true)) {
                markParenthesesParam();
                beginStatement();
                return;
            }
            //The constructor initialization list should be separated from the function body and
            //the last initialized variable when it ends.
            if (last.HaveStatement() && mStatementSemanticStack.Count > 1) {
                StatementData parentSt = getCurParentStatement();
                Debug.Assert(null != parentSt);
                if (IsCppConstructor(parentSt, false)) {
                    var ps = new List<ISyntaxComponent>(last.Params);
                    if (last.IsHighOrder) {
                        var curStatement = getCurStatement();
                        Debug.Assert(null != curStatement);
                        curStatement.Functions[curStatement.Functions.Count - 1] = last.LowerOrderFunction;
                    }
                    else {
                        last.SetParamClass((int)ParamClassEnum.PARAM_CLASS_NOTHING);
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
        /// Specific language utility functions.
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
        /// Utility function section.
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
            Debug.Assert(null != statement);
            return statement.First;
        }
        public ValueOrFunctionData getSecondFunction()
        {
            StatementData statement = getCurStatement();
            Debug.Assert(null != statement);
            return statement.Second;
        }
        public ValueOrFunctionData getThirdFunction()
        {
            StatementData statement = getCurStatement();
            Debug.Assert(null != statement);
            return statement.Third;
        }
        public FunctionData getLastFunction()
        {
            StatementData statement = getCurStatement();
            Debug.Assert(null != statement);
            return statement.Last.AsFunction;
        }
        public static StatementData newStatementWithOneFunction()
        {
            StatementData data = new StatementData();
            FunctionData func = new FunctionData();
            ValueData name = new ValueData();
            func.Name = name;
            data.Functions.Add(func);
            return data;
        }
        public static StatementData newStatementWithoutFunction()
        {
            StatementData data = new StatementData();
            return data;
        }
        public static FunctionData newFunctionOfStatement(StatementData data)
        {
            FunctionData func = new FunctionData();
            ValueData name = new ValueData();
            func.Name = name;
            data.Functions.Add(func);
            return func;
        }
        private static AbstractSyntaxComponent simplifyStatement(StatementData data)
        {
            //Simplify statements (during the process of syntax analysis, they are constructed
            //using complete StatementData for convenience, but here they are simplified to their original
            //types: ValueData/CallData/FunctionData, etc.,
            //mainly involving parameters and statement parts).
            if (data.Functions.Count == 1) {
                //Statements with only one function are reduced to the function itself
                //(and further reduced according to the function).
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
        private static ValueOrFunctionData simplifyStatement(FunctionData data)
        {
            //Note that in order to save memory, comments are not included in ValueData.
            //The related interfaces have no actual effect!!!
            if (!data.HaveParamOrStatement()) {
                //Calls without parameters are reduced to basic value data.
                if (data.IsHighOrder) {
                    //This situation should not occur.
                    return data;
                }
                else {
                    return data.Name;
                }
            }
            else {
                //Handling epsilon statements and parameters.
                simplifyFunction(data);
            }
            if (data.GetId() == "-" && data.GetParamNum() == 1) {
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
        private static void simplifyFunction(FunctionData data)
        {
            // When the last statement is epsilon and the only parameter is epsilon, delete this statement and parameter.
            // This ensures correct parsing of for(;;){}.
            // Currently, {} is used for non-block statement cases, so there should be no need for the last parameter to be empty
            // (allowing preceding parameters to be empty is already allowed). The side effect is that the statement list
            // also allows other statements to be empty except for the last one that is not terminated by a semicolon.
            // The higher-level application needs to handle this case when further parsing.
            if (data.IsHighOrder) {
                simplifyFunction(data.LowerOrderFunction);
            }
            int num = data.GetParamNum();
            if (data.HaveStatement() && num > 0 || num == 1) {
                if (!data.GetParam(num - 1).IsValid()) {
                    data.Params.RemoveAt(num - 1);
                }
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
        private BeforeBuildOperatorDelegation mOnBeforeBuildOperator;
        private BuildOperatorDelegation mOnBuildOperator;
        private SetFunctionIdDelegation mOnSetFunctionId;
        private BeforeBuildHighOrderDelegation mOnBeforeBuildHighOrder;
        private BuildHighOrderDelegation mOnBuildHighOrder;

        private List<ISyntaxComponent> mScriptDatas;
        private Stack<SemanticInfo> mSemanticStack;
        private Stack<StatementData> mStatementSemanticStack;
        private Stack<uint> mPairTypeStack;
        private Dictionary<string, uint> mNameTags;

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
