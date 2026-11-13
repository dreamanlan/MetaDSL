// DslAction.js - JavaScript port of MetaDSL Common/DslAction.cs (DSL grammar semantic actions only).

import {
    ParamClassEnum,
    AbstractSyntaxComponent,
    ValueData,
    FunctionData,
    StatementData,
} from './Dsl.js';

const OperatorCategoryEnum = Object.freeze({
    OPERATOR_CATEGORY_NORMAL: 0,
    OPERATOR_CATEGORY_TERNARY: 1,
    OPERATOR_CATEGORY_MAXNUM: 2,
});

const PairTypeEnum = Object.freeze({
    PAIR_TYPE_NONE: 0,
    PAIR_TYPE_QUESTION_COLON: 1,
    PAIR_TYPE_PARENTHESES: 2,
    PAIR_TYPE_BRACKET: 3,
    PAIR_TYPE_BRACE: 4,
    PAIR_TYPE_BRACKET_COLON: 5,
    PAIR_TYPE_PARENTHESES_COLON: 6,
    PAIR_TYPE_ANGLE_BRACKET_COLON: 7,
    PAIR_TYPE_BRACE_PERCENT: 8,
    PAIR_TYPE_BRACKET_PERCENT: 9,
    PAIR_TYPE_PARENTHESES_PERCENT: 10,
    PAIR_TYPE_ANGLE_BRACKET_PERCENT: 11,
    PAIR_TYPE_MAXNUM: 12,
});

class DslAction {
    constructor(log, datas) {
        this.mLog = log;
        this.mScriptDatas = datas;
        this.mSemanticStack = [];
        this.mStatementSemanticStack = [];
        this.mPairTypeStack = [];
        this.mNameTags = null;

        this.onGetLastToken = null;
        this.onGetLastLineNumber = null;
        this.onGetComments = null;
        this.onSetStringDelimiter = null;
        this.onSetScriptDelimiter = null;
        this.onBeforeAddFunction = null;
        this.onAddFunction = null;
        this.onBeforeEndStatement = null;
        this.onEndStatement = null;
        this.onBeforeBuildOperator = null;
        this.onBuildOperator = null;
        this.onSetFunctionId = null;
        this.onBeforeBuildHighOrder = null;
        this.onBuildHighOrder = null;
    }

    predict(productionNumber, nonterminal, token, level, lastTok, lastLineNo, curTok, lineNo) {
        // Debug logging hook, intentionally empty like the C# implementation.
    }

    execute(number) {
        switch (number) {
            case 1: this.markSeparator(); break;
            case 2: this.endStatement(); break;
            case 3: this.pushId(); break;
            case 4: this.buildOperator(); break;
            case 5: this.buildFirstTernaryOperator(); break;
            case 6: this.buildSecondTernaryOperator(); break;
            case 7: this.beginStatement(); break;
            case 8: this.addFunction(); break;
            case 9: this.setFunctionId(); break;
            case 10: this.buildNullableOperator(); break;
            case 11: this.markParenthesesParam(); break;
            case 12: this.markParenthesesParamEnd(); break;
            case 13: this.buildHighOrderFunction(); break;
            case 14: this.markBracketParam(); break;
            case 15: this.markBracketParamEnd(); break;
            case 16: this.markStatement(); break;
            case 17: this.markStatementEnd(); break;
            case 18: this.markExternScript(); break;
            case 19: this.setExternScript(); break;
            case 20: this.markBracketColonParam(); break;
            case 21: this.markBracketColonParamEnd(); break;
            case 22: this.markParenthesesColonParam(); break;
            case 23: this.markParenthesesColonParamEnd(); break;
            case 24: this.markAngleBracketColonParam(); break;
            case 25: this.markAngleBracketColonParamEnd(); break;
            case 26: this.markBracePercentParam(); break;
            case 27: this.markBracePercentParamEnd(); break;
            case 28: this.markBracketPercentParam(); break;
            case 29: this.markBracketPercentParamEnd(); break;
            case 30: this.markParenthesesPercentParam(); break;
            case 31: this.markParenthesesPercentParamEnd(); break;
            case 32: this.markAngleBracketPercentParam(); break;
            case 33: this.markAngleBracketPercentParamEnd(); break;
            case 34: this.markColonColonParam(); break;
            case 35: this.markPeriodParam(); break;
            case 36: this.markPointerParam(); break;
            case 37: this.markPeriodStarParam(); break;
            case 38: this.markPointerStarParam(); break;
            case 39: this.pushStr(); break;
            case 40: this.pushNum(); break;
            case 41: this.pushDollarStr(); break;
            case 42: this.pushComma(); break;
            case 43: this.pushSemiColon(); break;
        }
    }

    endStatementImpl(addSep) {
        if (this.onBeforeEndStatement !== null) {
            const stm = this.getCurStatement();
            this.onBeforeEndStatement(this, stm);
        }
        let statement = this.popStatement();
        if (this.onEndStatement !== null) {
            const ref = { statement };
            this.onEndStatement(this, ref);
            statement = ref.statement;
        }
        const call = statement.First.AsFunction;
        if ((this.onSetStringDelimiter !== null || this.onSetScriptDelimiter !== null) &&
            statement.Functions.length === 1 && call !== null && call.GetId() === '@@delimiter' &&
            (call.GetParamNum() === 1 || call.GetParamNum() === 3) && !call.IsHighOrder) {
            const type = call.GetParamId(0);
            if (call.GetParamNum() === 3) {
                const begin = call.GetParamId(1);
                const end = call.GetParamId(2);
                if (type === 'string') this.setStringDelimiter(begin, end);
                else if (type === 'script') this.setScriptDelimiter(begin, end);
            }
            else {
                if (type === 'string') this.setStringDelimiter('', '');
                else if (type === 'script') this.setScriptDelimiter('', '');
            }
            return;
        }

        const cmtsInfo = this.GetComments();
        const cmts = cmtsInfo.comments;
        if (cmts.length > 0) {
            if (statement.LastComments.length <= 0) {
                statement.LastCommentOnNewLine = cmtsInfo.commentOnNewLine;
            }
            statement.LastComments.push(...cmts);
        }

        if (this.mStatementSemanticStack.length === 0) {
            // Simplification only needs to handle the first level.
            const statementSyntax = DslAction.simplifyStatement(statement);
            const vdSyntax = statementSyntax instanceof ValueData ? statementSyntax : null;
            if (!statementSyntax.IsValid()) {
                // The "epsilon" expression has no statement semantics.
                if (this.mScriptDatas.length > 0) {
                    const last = this.mScriptDatas[this.mScriptDatas.length - 1];
                    if (last.LastComments.length <= 0) {
                        last.LastCommentOnNewLine = statementSyntax.FirstCommentOnNewLine;
                    }
                    last.LastComments.push(...statementSyntax.FirstComments);
                    last.LastComments.push(...statementSyntax.LastComments);
                }
                return;
            }
            else if (vdSyntax !== null) {
                // If the statement is a regular value, move the comment to the previous statement.
                if (this.mScriptDatas.length > 0) {
                    const last = this.mScriptDatas[this.mScriptDatas.length - 1];
                    if (last.LastComments.length <= 0) {
                        last.LastCommentOnNewLine = statement.FirstCommentOnNewLine;
                    }
                    last.LastComments.push(...statement.FirstComments);
                    last.LastComments.push(...statement.LastComments);
                }
            }
            else {
                // Move the comment from the previous line of code to the line above.
                if (this.mScriptDatas.length > 0 && !statementSyntax.FirstCommentOnNewLine && statementSyntax.FirstComments.length > 0) {
                    const cmt = statementSyntax.FirstComments[0];
                    statementSyntax.FirstComments.splice(0, 1);
                    statementSyntax.FirstCommentOnNewLine = true;
                    const last = this.mScriptDatas[this.mScriptDatas.length - 1];
                    if (last.LastComments.length <= 0) {
                        last.LastCommentOnNewLine = false;
                    }
                    last.LastComments.push(cmt);
                }
            }
            // Top-level element ends.
            if (addSep && this.mScriptDatas.length > 0) {
                const lastStm = this.mScriptDatas[this.mScriptDatas.length - 1];
                lastStm.SetSeparator(AbstractSyntaxComponent.SEPARATOR_SEMICOLON);
            }
            this.mScriptDatas.push(statementSyntax);
        }
        else {
            const statementSyntax = DslAction.simplifyStatement(statement);
            const vdSyntax = statementSyntax instanceof ValueData ? statementSyntax : null;
            const func = this.getLastFunction();
            if (func.HaveParam()) {
                // Comments inside parameters are kept as they are.
            }
            else if (!statement.IsValid()) {
                // The "epsilon" expression has no statement semantics.
                if (func.Params.length > 0 && statementSyntax.FirstComments.length > 0) {
                    const last = func.Params[func.Params.length - 1];
                    if (last.LastComments.length <= 0) {
                        last.LastCommentOnNewLine = statementSyntax.FirstCommentOnNewLine;
                    }
                    last.LastComments.push(...statementSyntax.FirstComments);
                    last.LastComments.push(...statementSyntax.LastComments);
                }
            }
            else if (vdSyntax !== null) {
                // If the statement is a regular value, move the comment to the previous statement.
                if (func.Params.length > 0) {
                    const last = func.Params[func.Params.length - 1];
                    if (last.LastComments.length <= 0) {
                        last.LastCommentOnNewLine = statement.FirstCommentOnNewLine;
                    }
                    last.LastComments.push(...statement.FirstComments);
                    last.LastComments.push(...statement.LastComments);
                }
                else {
                    func.Comments.push(...statement.FirstComments);
                    func.Comments.push(...statement.LastComments);
                }
            }
            else {
                // Move the comment from the previous line of code to the line above.
                if (!statementSyntax.FirstCommentOnNewLine && statementSyntax.FirstComments.length > 0) {
                    const cmt = statementSyntax.FirstComments[0];
                    statementSyntax.FirstComments.splice(0, 1);
                    statementSyntax.FirstCommentOnNewLine = true;
                    if (func.Params.length > 0) {
                        const last = func.Params[func.Params.length - 1];
                        if (last.LastComments.length <= 0) {
                            last.LastCommentOnNewLine = false;
                        }
                        last.LastComments.push(cmt);
                    }
                    else if (func.IsHighOrder) {
                        func.LowerOrderFunction.Comments.push(cmt);
                    }
                    else {
                        func.Comments.push(cmt);
                    }
                }
            }

            if (addSep && func.GetParamNum() > 0) {
                const lastParam = func.GetParam(func.GetParamNum() - 1);
                lastParam.SetSeparator(func.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_STATEMENT ?
                    AbstractSyntaxComponent.SEPARATOR_SEMICOLON : AbstractSyntaxComponent.SEPARATOR_COMMA);
            }
            func.AddParam(statementSyntax);
        }
    }

    SetNameTags(tags) { this.mNameTags = tags; }

    PeekPairTypeStack(ix) {
        const stack = this.mPairTypeStack;
        if (ix === undefined) {
            if (stack.length === 0) return PairTypeEnum.PAIR_TYPE_NONE;
            return stack[stack.length - 1] & 0x0ff;
        }
        if (ix >= 0 && ix < stack.length) {
            // C# enumerates a Stack from top to bottom.
            return stack[stack.length - 1 - ix] & 0x0ff;
        }
        return PairTypeEnum.PAIR_TYPE_NONE;
    }
    PeekPairTypeTag(ix) {
        const stack = this.mPairTypeStack;
        if (stack.length === 0) return 0;
        if (ix === undefined) return stack[stack.length - 1] >>> 8;
        if (ix >= 0 && ix < stack.length) return stack[stack.length - 1 - ix] >>> 8;
        return 0;
    }
    GetPairTypeStackSize() { return this.mPairTypeStack.length; }
    PushPairType(pairType, tag) {
        const v = (((tag || 0) << 8) >>> 0) + pairType;
        this.mPairTypeStack.push(v >>> 0);
    }
    PopPairType() {
        if (this.mPairTypeStack.length > 0) this.mPairTypeStack.pop();
    }

    markSeparator() {
        const info = this.pop();
        const name = info.token;
        if (this.mStatementSemanticStack.length === 0) {
            if (this.mScriptDatas.length > 0) {
                const dslInfo = this.mScriptDatas[this.mScriptDatas.length - 1];
                dslInfo.SetSeparator(this.CalcSeparator(name));
            }
        }
        else {
            const lastFunc = this.getLastFunction();
            if (lastFunc.GetParamNum() > 0) {
                const lastParam = lastFunc.GetParam(lastFunc.GetParamNum() - 1);
                lastParam.SetSeparator(this.CalcSeparator(name));
            }
        }
    }

    buildOperator() {
        const info = this.pop();
        const name = info.token;
        const type = info.value;

        let arg = this.getCurStatement();
        if (this.onBeforeBuildOperator !== null) {
            this.onBeforeBuildOperator(this, OperatorCategoryEnum.OPERATOR_CATEGORY_NORMAL, name, arg);
        }
        arg = this.popStatement();
        if (this.onBuildOperator !== null) {
            const ref = { statement: arg };
            this.onBuildOperator(this, OperatorCategoryEnum.OPERATOR_CATEGORY_NORMAL, name, ref);
            arg = ref.statement;
        }

        const argComp = DslAction.simplifyStatement(arg);

        const _statement = DslAction.newStatementWithOneFunction();
        const first = _statement.First;
        if (first.IsValue) first.AsValue.SetLine(this.getLastLineNumber());
        else first.AsFunction.Name.SetLine(this.getLastLineNumber());

        _statement.CopyFirstComments(argComp);
        argComp.FirstComments.length = 0;

        this.mStatementSemanticStack.push(_statement);

        const func = this.getLastFunction();
        if (!func.IsValid()) {
            if (name.length > 1 && name[0] === '`') {
                func.SetParamClass(ParamClassEnum.PARAM_CLASS_WRAP_INFIX_CALL_MASK | ParamClassEnum.PARAM_CLASS_OPERATOR);
                func.Name.SetId(name.substring(1));
                func.Name.SetType(type);
            }
            else {
                func.SetParamClass(ParamClassEnum.PARAM_CLASS_OPERATOR);
                func.Name.SetId(name);
                func.Name.SetType(type);
            }
            if (argComp.IsValid()) {
                func.AddParam(argComp);
            }
        }
    }

    buildFirstTernaryOperator() {
        const info = this.pop();
        const name = info.token;
        const type = info.value;

        let arg = this.getCurStatement();
        if (this.onBeforeBuildOperator !== null) {
            this.onBeforeBuildOperator(this, OperatorCategoryEnum.OPERATOR_CATEGORY_TERNARY, name, arg);
        }
        arg = this.popStatement();
        if (this.onBuildOperator !== null) {
            const ref = { statement: arg };
            this.onBuildOperator(this, OperatorCategoryEnum.OPERATOR_CATEGORY_TERNARY, name, ref);
            arg = ref.statement;
        }

        const argComp = DslAction.simplifyStatement(arg);

        const _statement = DslAction.newStatementWithOneFunction();
        const first = _statement.First.AsFunction;
        if (first !== null) {
            // The ternary operator is represented as op1(cond)(true_val)op2(false_val)
            first.LowerOrderFunction = new FunctionData();
            first.LowerOrderFunction.Name = new ValueData();
            first.LowerOrderFunction.Name.SetLine(this.getLastLineNumber());
        }
        _statement.CopyFirstComments(argComp);
        argComp.FirstComments.length = 0;

        this.mStatementSemanticStack.push(_statement);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_QUESTION_COLON, 0);

        const func = this.getLastFunction();
        if (!func.IsValid()) {
            func.LowerOrderFunction.SetParamClass(ParamClassEnum.PARAM_CLASS_PARENTHESES);
            func.LowerOrderFunction.Name.SetId(name);
            func.LowerOrderFunction.Name.SetType(type);
            if (argComp.IsValid()) {
                func.LowerOrderFunction.AddParam(argComp);
            }
            func.SetParamClass(ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR);
        }
    }

    buildSecondTernaryOperator() {
        const info = this.pop();
        const name = info.token;
        const type = info.value;

        const statement = this.getCurStatement();
        if (this.onBeforeBuildOperator !== null) {
            this.onBeforeBuildOperator(this, OperatorCategoryEnum.OPERATOR_CATEGORY_TERNARY, name, statement);
        }

        this.PopPairType();

        const newFunc = new FunctionData();
        const nname = new ValueData();
        newFunc.Name = nname;
        statement.Functions.push(newFunc);

        const func = this.getLastFunction();
        if (!func.IsValid()) {
            func.SetParamClass(ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR);
            func.Name.SetId(name);
            func.Name.SetType(type);
            func.Name.SetLine(this.getLastLineNumber());
        }
    }

    beginStatement() {
        const statement = DslAction.newStatementWithoutFunction();
        const cmtsInfo = this.GetComments();
        if (cmtsInfo.comments.length > 0) {
            if (statement.FirstComments.length <= 0) {
                statement.FirstCommentOnNewLine = cmtsInfo.commentOnNewLine;
            }
            statement.FirstComments.push(...cmtsInfo.comments);
        }
        this.mStatementSemanticStack.push(statement);
    }

    endStatement() { this.endStatementImpl(false); }

    addFunction() {
        let statement = this.getCurStatement();
        if (this.onBeforeAddFunction !== null) {
            this.onBeforeAddFunction(this, statement);
            statement = this.getCurStatement();
        }
        const func = DslAction.newFunctionOfStatement(statement);
        if (this.onAddFunction !== null) {
            this.onAddFunction(this, statement, func);
        }
    }

    setFunctionId() {
        const info = this.pop();
        const name = info.token;
        const type = info.value;
        const func = this.getLastFunction();
        if (!func.IsValid()) {
            func.Name.SetId(name);
            func.Name.SetType(type);
            func.Name.SetLine(this.getLastLineNumber());
        }
        if (this.onSetFunctionId !== null) {
            const stm = this.getCurStatement();
            this.onSetFunctionId(this, name, stm, func);
        }
    }

    buildNullableOperator() {
        const info = this.pop();
        const name = info.token;
        let func = this.getLastFunction();
        if (name === '?') func.SetParamClass(ParamClassEnum.PARAM_CLASS_QUESTION_NULLABLE_OPERATOR);
        else func.SetParamClass(ParamClassEnum.PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR);
        this.wrapHighOrder(func);
    }

    buildHighOrderFunction() {
        // Higher-order function construction (the current function returns another function).
        const func = this.getLastFunction();
        this.wrapHighOrder(func);
    }

    wrapHighOrder(func) {
        if (this.onBeforeBuildHighOrder !== null) {
            const stm = this.getCurStatement();
            this.onBeforeBuildHighOrder(this, stm, func);
            func = this.getLastFunction();
        }
        const temp = new FunctionData();
        temp.CopyFrom(func);
        func.Clear();
        func.LowerOrderFunction = temp;
        if (this.onBuildHighOrder !== null) {
            const stm = this.getCurStatement();
            this.onBuildHighOrder(this, stm, func);
        }
    }

    getNameTag(func) {
        if (this.mNameTags === null) return 0;
        if (this.mNameTags instanceof Map) {
            return this.mNameTags.get(func.GetId()) || 0;
        }
        return this.mNameTags[func.GetId()] || 0;
    }

    markParenthesesParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_PARENTHESES);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_PARENTHESES, this.getNameTag(func));
    }
    markParenthesesParamEnd() { this.PopPairType(); }
    markBracketParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_BRACKET);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_BRACKET, this.getNameTag(func));
    }
    markBracketParamEnd() { this.PopPairType(); }
    markPeriodParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_PERIOD);
    }
    markStatement() {
        const func = this.getLastFunction();
        const cmtsInfo = this.GetComments();
        if (cmtsInfo.comments.length > 0) {
            if (func.IsHighOrder) func.LowerOrderFunction.Comments.push(...cmtsInfo.comments);
            else func.Comments.push(...cmtsInfo.comments);
        }
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_STATEMENT);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_BRACE, this.getNameTag(func));
    }
    markStatementEnd() { this.PopPairType(); }
    markExternScript() {
        const func = this.getLastFunction();
        const cmtsInfo = this.GetComments();
        if (cmtsInfo.comments.length > 0) {
            if (func.IsHighOrder) func.LowerOrderFunction.Comments.push(...cmtsInfo.comments);
            else func.Comments.push(...cmtsInfo.comments);
        }
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT);
    }
    markBracketColonParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_BRACKET_COLON);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_BRACKET_COLON, this.getNameTag(func));
    }
    markBracketColonParamEnd() { this.PopPairType(); }
    markParenthesesColonParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_PARENTHESES_COLON);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_PARENTHESES_COLON, this.getNameTag(func));
    }
    markParenthesesColonParamEnd() { this.PopPairType(); }
    markAngleBracketColonParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_COLON);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_ANGLE_BRACKET_COLON, this.getNameTag(func));
    }
    markAngleBracketColonParamEnd() { this.PopPairType(); }
    markBracePercentParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_BRACE_PERCENT);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_BRACE_PERCENT, this.getNameTag(func));
    }
    markBracePercentParamEnd() { this.PopPairType(); }
    markBracketPercentParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_BRACKET_PERCENT);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_BRACKET_PERCENT, this.getNameTag(func));
    }
    markBracketPercentParamEnd() { this.PopPairType(); }
    markParenthesesPercentParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_PARENTHESES_PERCENT);
        this.PushPairType(PairTypeEnum.PAIR_TYPE_PARENTHESES_PERCENT, this.getNameTag(func));
    }
    markParenthesesPercentParamEnd() { this.PopPairType(); }
    markAngleBracketPercentParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT);
        this.PushPairType(PairTypeEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT, this.getNameTag(func));
    }
    markAngleBracketPercentParamEnd() { this.PopPairType(); }
    markColonColonParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_COLON_COLON);
    }
    setExternScript() {
        const func = this.getLastFunction();
        func.AddParam(this.getLastToken(), ValueData.STRING_TOKEN);
    }
    markPointerParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_POINTER);
    }
    markPeriodStarParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_PERIOD_STAR);
    }
    markPointerStarParam() {
        const func = this.getLastFunction();
        func.SetParamClass(ParamClassEnum.PARAM_CLASS_POINTER_STAR);
    }

    pushId() { this.push(this.getLastToken(), FunctionData.ID_TOKEN); }
    pushNum() { this.push(this.getLastToken(), FunctionData.NUM_TOKEN); }
    pushStr() { this.push(this.getLastToken(), FunctionData.STRING_TOKEN); }
    pushDollarStr() { this.push(this.getLastToken(), FunctionData.DOLLAR_STRING_TOKEN); }
    pushComma() { this.push(',', FunctionData.STRING_TOKEN); }
    pushSemiColon() { this.push(';', FunctionData.STRING_TOKEN); }

    push(s, val) {
        this.mSemanticStack.push({ token: s, value: val });
    }
    pop() {
        if (this.mSemanticStack.length === 0) return { token: 'null_stack_!!!', value: 0 };
        return this.mSemanticStack.pop();
    }
    popStatement() {
        if (this.mStatementSemanticStack.length === 0) return DslAction.newStatementWithoutFunction();
        return this.mStatementSemanticStack.pop();
    }
    getCurStatement() {
        if (this.mStatementSemanticStack.length === 0) return null;
        return this.mStatementSemanticStack[this.mStatementSemanticStack.length - 1];
    }
    getCurParentStatement() {
        if (this.mStatementSemanticStack.length <= 1) return null;
        return this.mStatementSemanticStack[this.mStatementSemanticStack.length - 2];
    }
    getFirstFunction() { return this.getCurStatement().First; }
    getSecondFunction() { return this.getCurStatement().Second; }
    getThirdFunction() { return this.getCurStatement().Third; }
    getLastFunction() { return this.getCurStatement().Last.AsFunction; }

    static newStatementWithOneFunction() {
        const data = new StatementData();
        const func = new FunctionData();
        func.Name = new ValueData();
        data.Functions.push(func);
        return data;
    }
    static newStatementWithoutFunction() {
        return new StatementData();
    }
    static newFunctionOfStatement(data) {
        const func = new FunctionData();
        func.Name = new ValueData();
        data.Functions.push(func);
        return func;
    }

    static simplifyStatement(data) {
        if (data instanceof StatementData) {
            // Simplify statements: single-function statements are reduced to the function itself.
            if (data.Functions.length === 1) {
                const f = data.Functions[0];
                f.CopyComments(data);
                if (f.IsValue) return f;
                return DslAction.simplifyStatement(f.AsFunction);
            }
            for (let i = 0; i < data.Functions.length; ++i) {
                const func = data.Functions[i].AsFunction;
                if (func !== null) {
                    data.Functions[i] = DslAction.simplifyStatement(func);
                }
            }
            return data;
        }
        // FunctionData overload.
        if (!data.HaveParamOrStatement()) {
            // Calls without parameters are reduced to basic value data.
            if (data.IsHighOrder) {
                // This situation should not occur.
                return data;
            }
            return data.Name;
        }
        // Handling epsilon statements and parameters.
        DslAction.simplifyFunction(data);
        if (data.GetId() === '-' && data.GetParamNum() === 1) {
            const temp = data.GetParam(0);
            if (temp instanceof ValueData && temp.IsNumber()) {
                return new ValueData('-' + temp.GetId(), ValueData.NUM_TOKEN);
            }
            return data;
        }
        if (data.GetId() === '+' && data.GetParamNum() === 1) {
            const temp = data.GetParam(0);
            if (temp instanceof ValueData && temp.IsNumber()) {
                return new ValueData(temp.GetId(), ValueData.NUM_TOKEN);
            }
            return data;
        }
        return data;
    }

    static simplifyFunction(data) {
        // When the last statement is epsilon and the only parameter is epsilon, delete it (for(;;){}).
        if (data.IsHighOrder) {
            DslAction.simplifyFunction(data.LowerOrderFunction);
        }
        const num = data.GetParamNum();
        if ((data.HaveStatement() && num > 0) || num === 1) {
            if (!data.GetParam(num - 1).IsValid()) {
                data.Params.splice(num - 1, 1);
            }
        }
    }

    getLastToken() {
        if (this.onGetLastToken !== null) return this.onGetLastToken();
        return '';
    }
    getLastLineNumber() {
        if (this.onGetLastLineNumber !== null) return this.onGetLastLineNumber();
        return -1;
    }
    GetComments() {
        if (this.onGetComments !== null) {
            return this.onGetComments();
        }
        return { commentOnNewLine: false, comments: [] };
    }
    setStringDelimiter(begin, end) {
        if (this.onSetStringDelimiter !== null) this.onSetStringDelimiter(begin, end);
    }
    setScriptDelimiter(begin, end) {
        if (this.onSetScriptDelimiter !== null) this.onSetScriptDelimiter(begin, end);
    }

    CalcSeparator(tok) {
        if (tok === ',') return AbstractSyntaxComponent.SEPARATOR_COMMA;
        if (tok === ';') return AbstractSyntaxComponent.SEPARATOR_SEMICOLON;
        return AbstractSyntaxComponent.SEPARATOR_NOTHING;
    }
}

export { DslAction, OperatorCategoryEnum, PairTypeEnum };
