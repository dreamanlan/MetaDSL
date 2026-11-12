// Dsl.js - JavaScript port of MetaDSL Dsl.cs (text DSL data model and serialization).
// Scope: ValueData/FunctionData/StatementData/DelimiterInfo/Utility (text output + binary BDSL).
// Lua/Cpp frontends and Gpp preprocessing are intentionally not ported.

'use strict';

const ParamClassEnum = Object.freeze({
    PARAM_CLASS_MIN: 0,
    PARAM_CLASS_NOTHING: 0,
    PARAM_CLASS_PARENTHESES: 1,
    PARAM_CLASS_BRACKET: 2,
    PARAM_CLASS_PERIOD: 3,
    PARAM_CLASS_POINTER: 4,
    PARAM_CLASS_STATEMENT: 5,
    PARAM_CLASS_EXTERN_SCRIPT: 6,
    PARAM_CLASS_PARENTHESES_COLON: 7,
    PARAM_CLASS_BRACKET_COLON: 8,
    PARAM_CLASS_ANGLE_BRACKET_COLON: 9,
    PARAM_CLASS_PARENTHESES_PERCENT: 10,
    PARAM_CLASS_BRACKET_PERCENT: 11,
    PARAM_CLASS_BRACE_PERCENT: 12,
    PARAM_CLASS_ANGLE_BRACKET_PERCENT: 13,
    PARAM_CLASS_COLON_COLON: 14,
    PARAM_CLASS_PERIOD_STAR: 15,
    PARAM_CLASS_POINTER_STAR: 16,
    PARAM_CLASS_OPERATOR: 17,
    PARAM_CLASS_TERNARY_OPERATOR: 18,
    PARAM_CLASS_QUESTION_NULLABLE_OPERATOR: 19,
    PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR: 20,
    PARAM_CLASS_MAX: 21,
    PARAM_CLASS_WRAP_INFIX_CALL_MASK: 0x20,
    PARAM_CLASS_UNMASK: 0x1F,
});

class StrBuf {
    constructor() { this.parts = []; this.length = 0; }
    Append(s) {
        if (s === null || s === undefined) return;
        s = String(s);
        this.parts.push(s);
        this.length += s.length;
    }
    AppendLine(s) {
        if (s !== undefined && s !== null) this.Append(s);
        this.Append('\r\n');
    }
    Clear() { this.parts.length = 0; this.length = 0; }
    ToString() { return this.parts.join(''); }
    toString() { return this.ToString(); }
}

class DelimiterInfo {
    constructor(strBeginDelim, strEndDelim, scpBeginDelim, scpEndDelim) {
        this.StringBeginDelimiter = strBeginDelim !== undefined ? strBeginDelim : '"';
        this.StringEndDelimiter = strEndDelim !== undefined ? strEndDelim : '"';
        this.ScriptBeginDelimiter = scpBeginDelim !== undefined ? scpBeginDelim : '{:';
        this.ScriptEndDelimiter = scpEndDelim !== undefined ? scpEndDelim : ':}';
    }
    static get Default() { return DelimiterInfo.s_Default; }
}
DelimiterInfo.s_Default = new DelimiterInfo();

class SyntaxComponentCommentsInfo {
    constructor() {
        this.mFirstComments = null;
        this.mFirstCommentOnNewLine = false;
        this.mLastComments = null;
        this.mLastCommentOnNewLine = false;
    }
}
class FunctionCommentsInfo extends SyntaxComponentCommentsInfo {
    constructor() {
        super();
        this.m_Comments = null;
    }
}

// DslFile static flags live here to avoid a circular dependency with DslFile.js.
const DslGlobals = {
    DontLoadComments: false,
};

class AbstractSyntaxComponent {
    constructor() {
        this.m_Separator = AbstractSyntaxComponent.SEPARATOR_NOTHING;
    }
    IsValid() { throw new Error('abstract'); }
    GetId() { throw new Error('abstract'); }
    GetIdType() { throw new Error('abstract'); }
    GetLine() { throw new Error('abstract'); }
    ToScriptString(includeComment, delim) { throw new Error('abstract'); }
    HaveId() { throw new Error('abstract'); }

    SetSeparator(sep) { this.m_Separator = sep; }
    GetSeparator() { return this.m_Separator; }
    GetSepChar() {
        switch (this.m_Separator) {
            case AbstractSyntaxComponent.SEPARATOR_COMMA: return ',';
            case AbstractSyntaxComponent.SEPARATOR_SEMICOLON: return ';';
            default: return ' ';
        }
    }
    SetEmptySeparator() { this.m_Separator = AbstractSyntaxComponent.SEPARATOR_NOTHING; }
    SetCommaSeparator() { this.m_Separator = AbstractSyntaxComponent.SEPARATOR_COMMA; }
    SetSemiColonSeparator() { this.m_Separator = AbstractSyntaxComponent.SEPARATOR_SEMICOLON; }
    IsEmptySeparator() { return this.m_Separator === AbstractSyntaxComponent.SEPARATOR_NOTHING; }
    IsCommaSeparator() { return this.m_Separator === AbstractSyntaxComponent.SEPARATOR_COMMA; }
    IsSemiColonSeparator() { return this.m_Separator === AbstractSyntaxComponent.SEPARATOR_SEMICOLON; }

    CalcFirstComment() {
        if (DslGlobals.DontLoadComments) return '';
        const cmtsInfo = this.GetCommentsInfo();
        if (cmtsInfo === null || cmtsInfo.mFirstComments === null) return '';
        return cmtsInfo.mFirstComments.join('');
    }
    CalcLastComment() {
        if (DslGlobals.DontLoadComments) return '';
        const cmtsInfo = this.GetCommentsInfo();
        if (cmtsInfo === null || cmtsInfo.mLastComments === null) return '';
        return cmtsInfo.mLastComments.join('');
    }
    CopyComments(other) {
        this.CopyFirstComments(other);
        this.CopyLastComments(other);
    }
    CopyFirstComments(other) {
        if (DslGlobals.DontLoadComments) return;
        if (other.FirstComments.length > 0) {
            this.FirstComments.push(...other.FirstComments);
            this.FirstCommentOnNewLine = other.FirstCommentOnNewLine;
        }
    }
    CopyLastComments(other) {
        if (DslGlobals.DontLoadComments) return;
        if (other.LastComments.length > 0) {
            this.LastComments.push(...other.LastComments);
            this.LastCommentOnNewLine = other.LastCommentOnNewLine;
        }
    }
    get FirstComments() {
        if (DslGlobals.DontLoadComments) return [];
        const cmtsInfo = this.GetCommentsInfo();
        if (cmtsInfo === null) return [];
        if (cmtsInfo.mFirstComments === null) cmtsInfo.mFirstComments = [];
        return cmtsInfo.mFirstComments;
    }
    get FirstCommentOnNewLine() {
        if (DslGlobals.DontLoadComments) return false;
        const cmtsInfo = this.GetCommentsInfo();
        if (cmtsInfo === null) return false;
        return cmtsInfo.mFirstCommentOnNewLine;
    }
    set FirstCommentOnNewLine(value) {
        if (DslGlobals.DontLoadComments) return;
        const cmtsInfo = this.GetCommentsInfo();
        if (cmtsInfo === null) return;
        cmtsInfo.mFirstCommentOnNewLine = value;
    }
    get LastComments() {
        if (DslGlobals.DontLoadComments) return [];
        const cmtsInfo = this.GetCommentsInfo();
        if (cmtsInfo === null) return [];
        if (cmtsInfo.mLastComments === null) cmtsInfo.mLastComments = [];
        return cmtsInfo.mLastComments;
    }
    get LastCommentOnNewLine() {
        if (DslGlobals.DontLoadComments) return false;
        const cmtsInfo = this.GetCommentsInfo();
        if (cmtsInfo === null) return false;
        return cmtsInfo.mLastCommentOnNewLine;
    }
    set LastCommentOnNewLine(value) {
        if (DslGlobals.DontLoadComments) return;
        const cmtsInfo = this.GetCommentsInfo();
        if (cmtsInfo === null) return;
        cmtsInfo.mLastCommentOnNewLine = value;
    }
    GetCommentsInfo() { return null; }

    static get NullSyntax() {
        AbstractSyntaxComponent.s_NullSyntax.Clear();
        return AbstractSyntaxComponent.s_NullSyntax;
    }
}
AbstractSyntaxComponent.ID_TOKEN = 0;
AbstractSyntaxComponent.NUM_TOKEN = 1;
AbstractSyntaxComponent.STRING_TOKEN = 2;
AbstractSyntaxComponent.DOLLAR_STRING_TOKEN = 3;
AbstractSyntaxComponent.MAX_TYPE = 3;
AbstractSyntaxComponent.SEPARATOR_NOTHING = 0;
AbstractSyntaxComponent.SEPARATOR_COMMA = 1;
AbstractSyntaxComponent.SEPARATOR_SEMICOLON = 2;

class ValueOrFunctionData extends AbstractSyntaxComponent {
    get IsValue() { return this instanceof ValueData; }
    get IsFunction() { return this instanceof FunctionData; }
    get AsValue() { return this instanceof ValueData ? this : null; }
    get AsFunction() { return this instanceof FunctionData ? this : null; }
}

class ValueData extends ValueOrFunctionData {
    constructor(val, _type) {
        super();
        this.m_Type = ValueData.ID_TOKEN;
        this.m_Id = '';
        this.m_Line = -1;
        if (val !== undefined && val !== null) {
            if (_type !== undefined) {
                this.m_Type = _type;
            }
            else if (/^0x[0-9a-fA-F]+$/.test(val)) {
                this.m_Type = ValueData.NUM_TOKEN;
            }
            else if (Utility.isCsNumeric(val)) {
                this.m_Type = ValueData.NUM_TOKEN;
            }
            else if (Utility.needQuote(val)) {
                this.m_Type = ValueData.STRING_TOKEN;
            }
            this.m_Id = val;
        }
    }
    IsValid() { return this.HaveId(); }
    GetId() { return this.m_Id; }
    GetIdType() { return this.m_Type; }
    GetLine() { return this.m_Line; }
    ToScriptString(includeComment, delim) {
        if (includeComment) {
            return this.CalcFirstComment() + Utility.quoteString(this.m_Id, this.m_Type, delim) + this.CalcLastComment();
        }
        return Utility.quoteString(this.m_Id, this.m_Type, delim);
    }
    HaveId() { return this.m_Id.length > 0 || this.m_Type !== ValueData.ID_TOKEN; }
    SetId(id) { this.m_Id = id; }
    SetType(_type) { this.m_Type = _type; }
    SetLine(line) { this.m_Line = line; }
    IsId() { return this.m_Type === ValueData.ID_TOKEN; }
    IsNumber() { return this.m_Type === ValueData.NUM_TOKEN; }
    IsString() { return this.m_Type === ValueData.STRING_TOKEN; }
    IsDollarString() { return this.m_Type === ValueData.DOLLAR_STRING_TOKEN; }
    Clear() {
        this.m_Type = ValueData.ID_TOKEN;
        this.m_Id = '';
        this.m_Line = -1;
    }
    CopyFrom(other) {
        this.m_Type = other.m_Type;
        this.m_Id = other.m_Id;
        this.m_Line = other.m_Line;
        this.SetSeparator(other.GetSeparator());
        if (!DslGlobals.DontLoadComments) {
            this.CopyComments(other);
        }
    }
    static get NullValue() {
        ValueData.s_Instance.Clear();
        return ValueData.s_Instance;
    }
}
ValueData.s_Instance = new ValueData();

class FunctionData extends ValueOrFunctionData {
    constructor() {
        super();
        this.m_IsHighOrder = false;
        this.m_Name = null;
        this.m_LowerOrderFunction = null;
        this.m_Params = null;
        this.m_ParamClass = ParamClassEnum.PARAM_CLASS_NOTHING;
        this.m_CommentsInfo = null;
    }
    IsValid() { return this.HaveId() || this.HaveParamOrStatement(); }
    GetId() {
        if (this.m_Name !== null) return this.m_Name.GetId();
        if (this.m_LowerOrderFunction !== null) return this.m_LowerOrderFunction.GetId();
        return '';
    }
    GetIdType() {
        if (this.m_Name !== null) return this.m_Name.GetIdType();
        if (this.m_LowerOrderFunction !== null) return this.m_LowerOrderFunction.GetIdType();
        return FunctionData.ID_TOKEN;
    }
    GetLine() {
        if (this.m_Name !== null) return this.m_Name.GetLine();
        if (this.m_LowerOrderFunction !== null) return this.m_LowerOrderFunction.GetLine();
        if (this.m_Params !== null && this.m_Params.length > 0) {
            for (const p of this.m_Params) {
                const line = p.GetLine();
                if (line >= 0) return line;
            }
        }
        return -1;
    }
    ToScriptString(includeComment, delim) {
        if (includeComment) {
            return this.CalcFirstComment() + Utility.getFunctionString(this, true, delim) + this.CalcComment() + this.CalcLastComment();
        }
        return Utility.getFunctionString(this, true, delim);
    }
    HaveId() {
        if (this.m_Name !== null) return this.m_Name.HaveId();
        if (this.m_LowerOrderFunction !== null) return this.m_LowerOrderFunction.HaveId();
        return false;
    }
    CalcComment() {
        if (DslGlobals.DontLoadComments) return '';
        const cmtsInfo = this.GetFunctionCommentsInfo();
        if (cmtsInfo === null || cmtsInfo.m_Comments === null) return '';
        let cmt = cmtsInfo.m_Comments.join('');
        if (this.m_LowerOrderFunction !== null && !this.HaveStatement() && !this.HaveExternScript()) {
            cmt = this.m_LowerOrderFunction.CalcComment() + cmt;
        }
        return cmt;
    }
    get Comments() {
        if (DslGlobals.DontLoadComments) return [];
        const cmtsInfo = this.GetFunctionCommentsInfo();
        if (cmtsInfo.m_Comments === null) cmtsInfo.m_Comments = [];
        return cmtsInfo.m_Comments;
    }
    get Params() {
        this.PrepareParams();
        return this.m_Params;
    }
    set Params(value) {
        this.m_Params = value;
        if (this.m_Params === null) {
            this.m_ParamClass = ParamClassEnum.PARAM_CLASS_NOTHING;
        }
        else if (this.m_Params.length > 0) {
            if (this.m_ParamClass === ParamClassEnum.PARAM_CLASS_NOTHING) {
                this.m_ParamClass = ParamClassEnum.PARAM_CLASS_PARENTHESES;
            }
        }
    }
    get IsHighOrder() { return this.m_IsHighOrder; }
    get Name() {
        if (this.m_Name !== null) return this.m_Name;
        return ValueData.NullValue;
    }
    set Name(value) {
        this.m_Name = value;
        this.m_LowerOrderFunction = null;
        this.m_IsHighOrder = false;
    }
    get LowerOrderFunction() {
        if (this.m_LowerOrderFunction !== null) return this.m_LowerOrderFunction;
        return FunctionData.NullFunction;
    }
    set LowerOrderFunction(value) {
        this.m_Name = null;
        this.m_LowerOrderFunction = value;
        this.m_IsHighOrder = true;
    }
    get ThisOrLowerOrderCall() {
        if (this.HaveParam()) return this;
        if (this.HaveLowerOrderParam()) return this.m_LowerOrderFunction;
        return FunctionData.NullFunction;
    }
    get ThisOrLowerOrderBody() {
        if (this.HaveStatement()) return this;
        if (this.HaveLowerOrderStatement()) return this.m_LowerOrderFunction;
        return FunctionData.NullFunction;
    }
    get ThisOrLowerOrderScript() {
        if (this.HaveExternScript()) return this;
        if (this.HaveLowerOrderExternScript()) return this.m_LowerOrderFunction;
        return FunctionData.NullFunction;
    }
    HaveLowerOrderParam() {
        return this.m_LowerOrderFunction !== null && this.m_LowerOrderFunction.HaveParam();
    }
    HaveLowerOrderStatement() {
        return this.m_LowerOrderFunction !== null && this.m_LowerOrderFunction.HaveStatement();
    }
    HaveLowerOrderExternScript() {
        return this.m_LowerOrderFunction !== null && this.m_LowerOrderFunction.HaveExternScript();
    }
    SetParamClass(type) {
        const innerType = type & ParamClassEnum.PARAM_CLASS_UNMASK;
        if (innerType >= ParamClassEnum.PARAM_CLASS_MIN && innerType < ParamClassEnum.PARAM_CLASS_MAX) {
            this.m_ParamClass = type;
        }
    }
    GetParamClass() { return this.m_ParamClass; }
    GetParamClassUnmasked() { return this.m_ParamClass & ParamClassEnum.PARAM_CLASS_UNMASK; }
    HaveParamClassInfixFlag() {
        return (this.m_ParamClass & ParamClassEnum.PARAM_CLASS_WRAP_INFIX_CALL_MASK) === ParamClassEnum.PARAM_CLASS_WRAP_INFIX_CALL_MASK;
    }
    SetInfixOperatorParamClass() {
        this.m_ParamClass = ParamClassEnum.PARAM_CLASS_WRAP_INFIX_CALL_MASK | ParamClassEnum.PARAM_CLASS_OPERATOR;
    }
    SetOperatorParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_OPERATOR; }
    SetQuestionNullableOperatorParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_QUESTION_NULLABLE_OPERATOR; }
    SetExclamationNullableOperatorParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR; }
    SetTernaryOperatorParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR; }
    SetParenthesesParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_PARENTHESES; }
    SetBracketParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_BRACKET; }
    SetColonColonParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_COLON_COLON; }
    SetPeriodParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_PERIOD; }
    SetPeriodStarParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_PERIOD_STAR; }
    SetPointerParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_POINTER; }
    SetPointerStarParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_POINTER_STAR; }
    SetParenthesesColonParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_PARENTHESES_COLON; }
    SetBracketColonParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_BRACKET_COLON; }
    SetAngleBracketColonParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_COLON; }
    SetParenthesesPercentParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_PARENTHESES_PERCENT; }
    SetBracketPercentParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_BRACKET_PERCENT; }
    SetBracePercentParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_BRACE_PERCENT; }
    SetAngleBracketPercentParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT; }
    IsOperatorParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_OPERATOR; }
    IsQuestionNullableOperatorParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_QUESTION_NULLABLE_OPERATOR; }
    IsExclamationNullableOperatorParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR; }
    IsTernaryOperatorParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_TERNARY_OPERATOR; }
    IsParenthesesParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_PARENTHESES; }
    IsBracketParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_BRACKET; }
    IsColonColonParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_COLON_COLON; }
    IsPeriodParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_PERIOD; }
    IsPeriodStarParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_PERIOD_STAR; }
    IsPointerParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_POINTER; }
    IsPointerStarParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_POINTER_STAR; }
    IsParenthesesColonParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_PARENTHESES_COLON; }
    IsBracketColonParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_BRACKET_COLON; }
    IsAngleBracketColonParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_COLON; }
    IsParenthesesPercentParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_PARENTHESES_PERCENT; }
    IsBracketPercentParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_BRACKET_PERCENT; }
    IsBracePercentParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_BRACE_PERCENT; }
    IsAngleBracketPercentParamClass() { return this.GetParamClassUnmasked() === ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT; }
    IsMemberParamClass() {
        const paramClass = this.GetParamClassUnmasked();
        return paramClass === ParamClassEnum.PARAM_CLASS_COLON_COLON ||
            paramClass === ParamClassEnum.PARAM_CLASS_PERIOD ||
            paramClass === ParamClassEnum.PARAM_CLASS_PERIOD_STAR ||
            paramClass === ParamClassEnum.PARAM_CLASS_POINTER ||
            paramClass === ParamClassEnum.PARAM_CLASS_POINTER_STAR;
    }
    SetStatementParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_STATEMENT; }
    SetExternScriptParamClass() { this.m_ParamClass = ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT; }
    HaveParamOrStatement() { return this.m_ParamClass !== ParamClassEnum.PARAM_CLASS_NOTHING; }
    HaveParam() { return this.HaveParamOrStatement() && !this.HaveStatement() && !this.HaveExternScript(); }
    HaveStatement() { return this.m_ParamClass === ParamClassEnum.PARAM_CLASS_STATEMENT; }
    HaveExternScript() { return this.m_ParamClass === ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT; }
    GetParamNum() {
        if (this.m_Params === null) return 0;
        return this.m_Params.length;
    }
    SetParam(index, data) {
        if (this.m_Params === null) return;
        if (index < 0 || index >= this.m_Params.length) return;
        this.m_Params[index] = data;
    }
    GetParam(index) {
        if (this.m_Params === null) return AbstractSyntaxComponent.NullSyntax;
        if (index < 0 || index >= this.m_Params.length) return AbstractSyntaxComponent.NullSyntax;
        return this.m_Params[index];
    }
    GetParamId(index) {
        if (this.m_Params === null) return '';
        if (index < 0 || index >= this.m_Params.length) return '';
        return this.m_Params[index].GetId();
    }
    ClearParams() {
        this.PrepareParams();
        this.m_Params.length = 0;
    }
    AddParam(param, type) {
        this.PrepareParams();
        if (typeof param === 'string') {
            if (type !== undefined) this.m_Params.push(new ValueData(param, type));
            else this.m_Params.push(new ValueData(param));
        }
        else {
            this.m_Params.push(param);
        }
        if (this.m_ParamClass === ParamClassEnum.PARAM_CLASS_NOTHING) {
            this.m_ParamClass = ParamClassEnum.PARAM_CLASS_PARENTHESES;
        }
    }
    Clear() {
        this.m_Name = null;
        this.m_LowerOrderFunction = null;
        this.m_IsHighOrder = false;
        this.m_Params = null;
        this.m_ParamClass = ParamClassEnum.PARAM_CLASS_NOTHING;
        this.m_CommentsInfo = null;
    }
    CopyFrom(other) {
        this.m_IsHighOrder = other.m_IsHighOrder;
        if (other.m_Name !== null) {
            this.m_Name = Utility.CloneDsl(other.m_Name);
        }
        else {
            this.m_Name = null;
        }
        if (other.m_LowerOrderFunction !== null) {
            this.m_LowerOrderFunction = Utility.CloneDsl(other.m_LowerOrderFunction);
        }
        else {
            this.m_LowerOrderFunction = null;
        }
        this.m_ParamClass = other.m_ParamClass;
        if (other.m_Params !== null) {
            this.ClearParams();
            for (const p of other.m_Params) {
                this.m_Params.push(Utility.CloneDsl(p));
            }
        }
        else {
            this.m_Params = null;
        }
        this.SetSeparator(other.GetSeparator());
        if (!DslGlobals.DontLoadComments) {
            if (other.m_CommentsInfo !== null && other.m_CommentsInfo.m_Comments !== null) {
                this.Comments.push(...other.m_CommentsInfo.m_Comments);
            }
            this.CopyComments(other);
        }
    }
    PrepareParams() {
        if (this.m_Params === null) this.m_Params = [];
    }
    GetCommentsInfo() { return this.GetFunctionCommentsInfo(); }
    GetFunctionCommentsInfo() {
        if (DslGlobals.DontLoadComments) return null;
        if (this.m_CommentsInfo === null) this.m_CommentsInfo = new FunctionCommentsInfo();
        return this.m_CommentsInfo;
    }
    static get NullFunction() {
        FunctionData.s_Instance.Clear();
        return FunctionData.s_Instance;
    }
}
FunctionData.s_Instance = new FunctionData();

class StatementData extends AbstractSyntaxComponent {
    constructor() {
        super();
        this.m_ValueOrFunctions = null;
        this.m_CommentsInfo = null;
    }
    IsValid() {
        let ret = true;
        if (this.m_ValueOrFunctions === null || this.m_ValueOrFunctions.length <= 0) {
            ret = false;
        }
        else {
            for (let i = 0; i < this.m_ValueOrFunctions.length; ++i) {
                ret = ret && this.m_ValueOrFunctions[i].IsValid();
            }
        }
        return ret;
    }
    GetId() {
        if (this.m_ValueOrFunctions === null || this.m_ValueOrFunctions.length <= 0) return '';
        return this.m_ValueOrFunctions[0].GetId();
    }
    GetIdType() {
        if (this.m_ValueOrFunctions === null || this.m_ValueOrFunctions.length <= 0) return StatementData.ID_TOKEN;
        return this.m_ValueOrFunctions[0].GetIdType();
    }
    GetLine() {
        if (this.m_ValueOrFunctions === null || this.m_ValueOrFunctions.length <= 0) return -1;
        for (const item of this.m_ValueOrFunctions) {
            const line = item.GetLine();
            if (line >= 0) return line;
        }
        return -1;
    }
    ToScriptString(includeComment, delim) {
        if (this.m_ValueOrFunctions === null) return '';
        // In contrast to the write method, here the output is a single line with no indentation.
        const tempData = this.First.AsFunction;
        let callData = null;
        if (tempData !== null) {
            callData = tempData.m_LowerOrderFunction;
        }
        if (callData !== null && tempData.IsTernaryOperatorParamClass()) {
            // The ternary operator is represented as op1(cond)(true_val)op2(false_val)
            if (callData.HaveId() && callData.HaveParamOrStatement()) {
                let line = '/*[?:]*/';
                if (this.Functions.length === 2) {
                    const funcData = this.Functions[1].AsFunction;
                    if (funcData !== null && funcData.HaveId() && funcData.HaveParamOrStatement()) {
                        line = callData.GetParam(0).ToScriptString(includeComment, delim) + ' ' + callData.GetId() + ' ' + tempData.GetParam(0).ToScriptString(includeComment, delim);
                        line = line + ' ' + funcData.GetId() + ' ' + funcData.GetParam(0).ToScriptString(includeComment, delim);
                    }
                }
                if (includeComment) {
                    return this.CalcFirstComment() + line + this.CalcLastComment();
                }
                return line;
            }
            if (includeComment) {
                return this.CalcFirstComment() + this.CalcLastComment();
            }
            return '';
        }
        const stream = new StrBuf();
        if (includeComment) {
            stream.Append(this.CalcFirstComment());
        }
        const ct = this.Functions.length;
        for (let i = 0; i < ct; ++i) {
            const funcData = this.Functions[i];
            stream.Append(funcData.ToScriptString(includeComment, delim));
        }
        if (includeComment) {
            stream.Append(this.CalcLastComment());
        }
        return stream.ToString();
    }
    HaveId() {
        if (this.m_ValueOrFunctions !== null && this.m_ValueOrFunctions.length > 0) {
            return this.m_ValueOrFunctions[0].HaveId();
        }
        return false;
    }
    GetFunctionNum() {
        if (this.m_ValueOrFunctions === null) return 0;
        return this.m_ValueOrFunctions.length;
    }
    SetFunction(index, funcData) {
        if (this.m_ValueOrFunctions === null || index < 0 || index >= this.m_ValueOrFunctions.length) return;
        this.m_ValueOrFunctions[index] = funcData;
    }
    GetFunction(index) {
        if (this.m_ValueOrFunctions === null || index < 0 || index >= this.m_ValueOrFunctions.length) return FunctionData.NullFunction;
        return this.m_ValueOrFunctions[index];
    }
    GetFunctionId(index) {
        if (this.m_ValueOrFunctions === null || index < 0 || index >= this.m_ValueOrFunctions.length) return '';
        return this.m_ValueOrFunctions[index].GetId();
    }
    AddFunction(funcData) {
        this.PrepareValueOrFunctions();
        this.m_ValueOrFunctions.push(funcData);
    }
    get Functions() {
        this.PrepareValueOrFunctions();
        return this.m_ValueOrFunctions;
    }
    get First() {
        if (this.m_ValueOrFunctions !== null && this.m_ValueOrFunctions.length > 0) return this.m_ValueOrFunctions[0];
        return ValueData.NullValue;
    }
    get Second() {
        if (this.m_ValueOrFunctions !== null && this.m_ValueOrFunctions.length > 1) return this.m_ValueOrFunctions[1];
        return FunctionData.NullFunction;
    }
    get Third() {
        if (this.m_ValueOrFunctions !== null && this.m_ValueOrFunctions.length > 2) return this.m_ValueOrFunctions[2];
        return FunctionData.NullFunction;
    }
    get Last() {
        if (this.m_ValueOrFunctions !== null && this.m_ValueOrFunctions.length > 0) return this.m_ValueOrFunctions[this.m_ValueOrFunctions.length - 1];
        return FunctionData.NullFunction;
    }
    Clear() {
        this.m_ValueOrFunctions = null;
        this.m_CommentsInfo = null;
    }
    CopyFrom(other) {
        if (other.m_ValueOrFunctions !== null) {
            this.PrepareValueOrFunctions();
            this.m_ValueOrFunctions.length = 0;
            for (const f of other.m_ValueOrFunctions) {
                this.m_ValueOrFunctions.push(Utility.CloneDsl(f));
            }
        }
        else {
            this.m_ValueOrFunctions = null;
        }
        this.SetSeparator(other.GetSeparator());
        if (!DslGlobals.DontLoadComments) {
            this.CopyComments(other);
        }
    }
    PrepareValueOrFunctions() {
        if (this.m_ValueOrFunctions === null) this.m_ValueOrFunctions = [];
    }
    GetCommentsInfo() {
        if (DslGlobals.DontLoadComments) return null;
        if (this.m_CommentsInfo === null) this.m_CommentsInfo = new SyntaxComponentCommentsInfo();
        return this.m_CommentsInfo;
    }
    static get NullStatement() {
        StatementData.s_NullStatement.Clear();
        return StatementData.s_NullStatement;
    }
}
StatementData.s_NullStatement = new StatementData();
AbstractSyntaxComponent.s_NullSyntax = new StatementData();

class Utility {
    static CloneDsl(syntax) {
        if (syntax instanceof ValueData) {
            const nvd = new ValueData();
            nvd.CopyFrom(syntax);
            return nvd;
        }
        if (syntax instanceof FunctionData) {
            const nfd = new FunctionData();
            nfd.CopyFrom(syntax);
            return nfd;
        }
        if (syntax instanceof StatementData) {
            const nsd = new StatementData();
            nsd.CopyFrom(syntax);
            return nsd;
        }
        return AbstractSyntaxComponent.NullSyntax;
    }

    static writeSyntaxComponent(stream, data, indent, firstLineNoIndent, isLastOfStatement, delim) {
        if (data instanceof ValueData) {
            Utility.writeValueData(stream, data, indent, firstLineNoIndent, isLastOfStatement, delim);
        }
        else if (data instanceof FunctionData) {
            Utility.writeFunctionData(stream, data, indent, firstLineNoIndent, isLastOfStatement, delim);
        }
        else {
            Utility.writeStatementData(stream, data, indent, firstLineNoIndent, isLastOfStatement, delim);
        }
    }

    static writeValueData(stream, data, indent, firstLineNoIndent, isLastOfStatement, delim) {
        Utility.writeFirstComments(stream, data, indent, firstLineNoIndent);
        Utility.writeText(stream, data.ToScriptString(false, delim), firstLineNoIndent ? 0 : indent);
        if (isLastOfStatement && !data.IsEmptySeparator()) stream.Append(data.GetSepChar());
        Utility.writeLastComments(stream, data, indent, isLastOfStatement);
    }

    static writeFunctionData(stream, data, indent, firstLineNoIndent, isLastOfStatement, delim) {
        Utility.writeFirstComments(stream, data, indent, firstLineNoIndent);
        if (data.HaveParamOrStatement()) {
            if (data.IsOperatorParamClass()) {
                const paramNum = data.GetParamNum();
                if (paramNum === 1) {
                    Utility.writeText(stream, '', firstLineNoIndent ? 0 : indent);
                    if (data.IsHighOrder) {
                        Utility.writeFunctionData(stream, data.LowerOrderFunction, indent, paramNum > 0 ? true : firstLineNoIndent, false, delim);
                    }
                    else if (data.HaveId()) {
                        let op = data.GetId();
                        if (data.HaveParamClassInfixFlag()) op = '`' + op;
                        const line = Utility.quoteString(op, data.GetIdType(), delim.StringBeginDelimiter, delim.StringEndDelimiter);
                        Utility.writeText(stream, line, paramNum > 0 ? 0 : (firstLineNoIndent ? 0 : indent));
                    }
                    Utility.writeText(stream, ' ', 0);
                    Utility.writeSyntaxComponent(stream, data.GetParam(0), indent, true, false, delim);
                }
                else {
                    if (paramNum > 0) {
                        Utility.writeSyntaxComponent(stream, data.GetParam(0), indent, firstLineNoIndent, false, delim);
                        Utility.writeText(stream, ' ', 0);
                    }
                    if (data.IsHighOrder) {
                        Utility.writeFunctionData(stream, data.LowerOrderFunction, indent, paramNum > 0 ? true : firstLineNoIndent, false, delim);
                    }
                    else if (data.HaveId()) {
                        let op = data.GetId();
                        if (data.HaveParamClassInfixFlag()) op = '`' + op;
                        const line = Utility.quoteString(op, data.GetIdType(), delim.StringBeginDelimiter, delim.StringEndDelimiter);
                        Utility.writeText(stream, line, paramNum > 0 ? 0 : (firstLineNoIndent ? 0 : indent));
                    }
                    if (paramNum > 1) {
                        Utility.writeText(stream, ' ', 0);
                        Utility.writeSyntaxComponent(stream, data.GetParam(1), indent, true, false, delim);
                    }
                }
            }
            else {
                if (data.IsHighOrder) {
                    Utility.writeFunctionData(stream, data.LowerOrderFunction, indent, firstLineNoIndent, false, delim);
                }
                else if (data.HaveId()) {
                    const line = Utility.quoteString(data.GetId(), data.GetIdType(), delim.StringBeginDelimiter, delim.StringEndDelimiter);
                    Utility.writeText(stream, line, firstLineNoIndent ? 0 : indent);
                }
                else {
                    Utility.writeText(stream, '', firstLineNoIndent ? 0 : indent);
                }
                if (data.IsQuestionNullableOperatorParamClass()) {
                    Utility.writeText(stream, '?', 0);
                }
                else if (data.IsExclamationNullableOperatorParamClass()) {
                    Utility.writeText(stream, '!', 0);
                }
                else if (data.HaveStatement() || data.HaveExternScript()) {
                    if (data.IsHighOrder) {
                        Utility.writeLastComments(stream, data.LowerOrderFunction, indent, false);
                    }
                    else if (data.HaveId()) {
                        Utility.writeLastComments(stream, data.Name, indent, false);
                    }
                    Utility.writeStatementsOrExternScript(stream, data, indent, delim);
                }
                else {
                    let lbracket = '';
                    let rbracket = '';
                    const paramClass = data.GetParamClassUnmasked();
                    switch (paramClass) {
                        case ParamClassEnum.PARAM_CLASS_PARENTHESES: lbracket = '('; rbracket = ')'; break;
                        case ParamClassEnum.PARAM_CLASS_BRACKET: lbracket = '['; rbracket = ']'; break;
                        case ParamClassEnum.PARAM_CLASS_PERIOD: lbracket = '.'; rbracket = ''; break;
                        case ParamClassEnum.PARAM_CLASS_COLON_COLON: lbracket = '::'; rbracket = ''; break;
                        case ParamClassEnum.PARAM_CLASS_POINTER: lbracket = '->'; rbracket = ''; break;
                        case ParamClassEnum.PARAM_CLASS_BRACKET_COLON: lbracket = '[:'; rbracket = ':]'; break;
                        case ParamClassEnum.PARAM_CLASS_PARENTHESES_COLON: lbracket = '(:'; rbracket = ':)'; break;
                        case ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_COLON: lbracket = '<:'; rbracket = ':>'; break;
                        case ParamClassEnum.PARAM_CLASS_BRACE_PERCENT: lbracket = '{%'; rbracket = '%}'; break;
                        case ParamClassEnum.PARAM_CLASS_BRACKET_PERCENT: lbracket = '[%'; rbracket = '%]'; break;
                        case ParamClassEnum.PARAM_CLASS_PARENTHESES_PERCENT: lbracket = '(%'; rbracket = '%)'; break;
                        case ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT: lbracket = '<%'; rbracket = '%>'; break;
                        case ParamClassEnum.PARAM_CLASS_PERIOD_STAR: lbracket = '.*'; rbracket = ''; break;
                        case ParamClassEnum.PARAM_CLASS_POINTER_STAR: lbracket = '->*'; rbracket = ''; break;
                    }
                    stream.Append(lbracket);
                    const ct = data.GetParamNum();
                    for (let i = 0; i < ct; ++i) {
                        if (i > 0) stream.Append(' ');
                        const param = data.GetParam(i);
                        const isEmptySep = param.IsEmptySeparator();
                        const sep = param.GetSepChar();
                        if (paramClass === ParamClassEnum.PARAM_CLASS_PERIOD ||
                            paramClass === ParamClassEnum.PARAM_CLASS_POINTER ||
                            paramClass === ParamClassEnum.PARAM_CLASS_PERIOD_STAR ||
                            paramClass === ParamClassEnum.PARAM_CLASS_POINTER_STAR) {
                            stream.Append(param.ToScriptString(true, delim));
                        }
                        else {
                            Utility.writeSyntaxComponent(stream, param, indent, true, false, delim);
                        }
                        if (!isEmptySep) stream.Append(sep);
                    }
                    stream.Append(rbracket);
                }
            }
        }
        else {
            if (data.IsHighOrder) {
                Utility.writeFunctionData(stream, data.LowerOrderFunction, indent, firstLineNoIndent, false, delim);
            }
            else if (data.HaveId()) {
                const line = Utility.quoteString(data.GetId(), data.GetIdType(), delim.StringBeginDelimiter, delim.StringEndDelimiter);
                Utility.writeText(stream, line, firstLineNoIndent ? 0 : indent);
            }
        }
        if (isLastOfStatement && !data.IsEmptySeparator()) stream.Append(data.GetSepChar());
        for (const cmt of data.Comments) {
            Utility.writeText(stream, cmt, 1);
        }
        Utility.writeLastComments(stream, data, indent, isLastOfStatement);
    }

    static writeStatementData(stream, data, indent, firstLineNoIndent, isLastOfStatement, delim) {
        Utility.writeFirstComments(stream, data, indent, firstLineNoIndent);
        const tempData = data.First.AsFunction;
        let callData = null;
        if (tempData !== null) {
            callData = tempData.m_LowerOrderFunction;
        }
        if (callData !== null && tempData.IsTernaryOperatorParamClass()) {
            // The ternary operator is represented as op1(cond)(true_val)op2(false_val)
            if (callData.HaveId() && callData.HaveParamOrStatement()) {
                let line = '/*[?:]*/';
                if (data.Functions.length === 2) {
                    const funcData = data.Functions[1].AsFunction;
                    if (funcData !== null && funcData.HaveId() && funcData.HaveParamOrStatement()) {
                        line = callData.GetParam(0).ToScriptString(true, delim) + ' ' + callData.GetId() + ' ' + tempData.GetParam(0).ToScriptString(true, delim);
                        line = line + ' ' + funcData.GetId() + ' ' + funcData.GetParam(0).ToScriptString(true, delim);
                    }
                }
                Utility.writeText(stream, line, firstLineNoIndent ? 0 : indent);
            }
        }
        else {
            const ct = data.Functions.length;
            let lastFuncNoParam = false;
            let lastFuncNoStatement = false;
            for (let i = 0; i < ct; ++i) {
                const dof = data.Functions[i];
                const val = dof.AsValue;
                if (val !== null) {
                    let noIndent = false;
                    if (i > 0) {
                        if (lastFuncNoParam && lastFuncNoStatement) {
                            Utility.writeText(stream, ' ', 0);
                            noIndent = true;
                        }
                        else if (lastFuncNoStatement) {
                            noIndent = true;
                        }
                        else {
                            Utility.writeLine(stream, '', 0);
                            noIndent = false;
                        }
                    }
                    Utility.writeValueData(stream, val, indent, (firstLineNoIndent && i === 0) || noIndent, false, delim);
                    lastFuncNoParam = true;
                    lastFuncNoStatement = true;
                }
                else {
                    const func = dof.AsFunction;
                    const funcNoParam = !func.IsHighOrder && (!func.HaveParam() || func.IsMemberParamClass());
                    const funcNoStatement = !func.HaveStatement() && !func.HaveExternScript();
                    let noIndent = false;
                    if (i > 0) {
                        if (lastFuncNoParam && lastFuncNoStatement) {
                            Utility.writeText(stream, ' ', 0);
                            noIndent = true;
                        }
                        else if (lastFuncNoStatement && funcNoStatement) {
                            noIndent = true;
                        }
                        else {
                            Utility.writeLine(stream, '', 0);
                            noIndent = false;
                        }
                    }
                    Utility.writeFunctionData(stream, func, indent, (firstLineNoIndent && i === 0) || noIndent, false, delim);
                    lastFuncNoParam = funcNoParam;
                    lastFuncNoStatement = funcNoStatement;
                }
            }
        }
        if (isLastOfStatement && !data.IsEmptySeparator()) stream.Append(data.GetSepChar());
        Utility.writeLastComments(stream, data, indent, isLastOfStatement);
    }

    static needQuote(str) {
        const escapeChars = " \t\r\n{}()[],;~`!%^&*-+=|:<>?/#\\'\"";
        if (str.length === 0) return true;
        let haveDot = false;
        let notNum = false;
        for (let i = 0; i < str.length; ++i) {
            const c = str[i];
            if (escapeChars.indexOf(c) >= 0) return true;
            if (c === '.') {
                haveDot = true;
            }
            else if (!notNum && !/[0-9]/.test(c)) {
                notNum = true;
            }
            if (haveDot && notNum) return true;
        }
        return false;
    }

    // Approximation of float/int.TryParse with NumberStyles.Any used by ValueData(string).
    static isCsNumeric(val) {
        const s = val.trim();
        if (s.length === 0) return false;
        return /^[+-]?(?:\d{1,3}(?:,\d{3})+|\d+)?(?:\.\d+)?(?:[eE][+-]?\d+)?$/.test(s) && /[0-9]/.test(s);
    }

    static quoteString(str, _type, delimOrBegin, strEndDelim) {
        let strBeginDelim;
        if (typeof delimOrBegin === 'string') {
            strBeginDelim = delimOrBegin;
        }
        else {
            const delim = delimOrBegin || DelimiterInfo.Default;
            strBeginDelim = delim.StringBeginDelimiter;
            strEndDelim = delim.StringEndDelimiter;
        }
        switch (_type) {
            case AbstractSyntaxComponent.DOLLAR_STRING_TOKEN:
                return '$' + Utility.quoteStringRaw(str, strBeginDelim, strEndDelim);
            case AbstractSyntaxComponent.STRING_TOKEN:
                return Utility.quoteStringRaw(str, strBeginDelim, strEndDelim);
            default:
                return str;
        }
    }
    static quoteStringRaw(str, strBeginDelim, strEndDelim) {
        const sb = new StrBuf();
        sb.Append(strBeginDelim);
        for (let i = 0; i < str.length; i++) {
            const c = str[i];
            switch (c) {
                case '\\': sb.Append('\\\\'); break;
                case '"': sb.Append('\\"'); break;
                case "'": sb.Append("\\'"); break;
                case '\0': sb.Append('\\\0'); break;
                default: sb.Append(c); break;
            }
        }
        sb.Append(strEndDelim);
        return sb.ToString();
    }

    static getFunctionString(data, includeComment, delim) {
        const lineNo = '';
        let line = '';
        if (data.IsHighOrder) {
            line = Utility.getFunctionString(data.LowerOrderFunction, includeComment, delim);
        }
        else if (data.HaveId()) {
            let op = data.GetId();
            if (data.HaveParamClassInfixFlag()) op = '`' + op;
            line = Utility.quoteString(op, data.GetIdType(), delim);
        }
        if (data.HaveParamOrStatement()) {
            if (data.IsOperatorParamClass()) {
                switch (data.GetParamNum()) {
                    case 1:
                        return line + ' ' + data.GetParam(0).ToScriptString(includeComment, delim);
                    case 2:
                        return data.GetParam(0).ToScriptString(includeComment, delim) + ' ' + line + ' ' + data.GetParam(1).ToScriptString(includeComment, delim);
                    default:
                        return line;
                }
            }
            else if (data.IsQuestionNullableOperatorParamClass()) {
                return data.GetParam(0).ToScriptString(includeComment, delim) + line + '?';
            }
            else if (data.IsExclamationNullableOperatorParamClass()) {
                return data.GetParam(0).ToScriptString(includeComment, delim) + line + '!';
            }
            else {
                let lbracket = '';
                let rbracket = '';
                const paramClass = data.GetParamClassUnmasked();
                switch (paramClass) {
                    case ParamClassEnum.PARAM_CLASS_PARENTHESES: lbracket = '('; rbracket = ')'; break;
                    case ParamClassEnum.PARAM_CLASS_BRACKET: lbracket = '['; rbracket = ']'; break;
                    case ParamClassEnum.PARAM_CLASS_PERIOD: lbracket = '.'; rbracket = ''; break;
                    case ParamClassEnum.PARAM_CLASS_COLON_COLON: lbracket = '::'; rbracket = ''; break;
                    case ParamClassEnum.PARAM_CLASS_POINTER: lbracket = '->'; rbracket = ''; break;
                    case ParamClassEnum.PARAM_CLASS_STATEMENT: lbracket = '{'; rbracket = '}'; break;
                    case ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT: lbracket = '{:'; rbracket = ':}'; break;
                    case ParamClassEnum.PARAM_CLASS_BRACKET_COLON: lbracket = '[:'; rbracket = ':]'; break;
                    case ParamClassEnum.PARAM_CLASS_PARENTHESES_COLON: lbracket = '(:'; rbracket = ':)'; break;
                    case ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_COLON: lbracket = '<:'; rbracket = ':>'; break;
                    case ParamClassEnum.PARAM_CLASS_BRACE_PERCENT: lbracket = '{%'; rbracket = '%}'; break;
                    case ParamClassEnum.PARAM_CLASS_BRACKET_PERCENT: lbracket = '[%'; rbracket = '%]'; break;
                    case ParamClassEnum.PARAM_CLASS_PARENTHESES_PERCENT: lbracket = '(%'; rbracket = '%)'; break;
                    case ParamClassEnum.PARAM_CLASS_ANGLE_BRACKET_PERCENT: lbracket = '<%'; rbracket = '%>'; break;
                    case ParamClassEnum.PARAM_CLASS_PERIOD_STAR: lbracket = '.*'; rbracket = ''; break;
                    case ParamClassEnum.PARAM_CLASS_POINTER_STAR: lbracket = '->*'; rbracket = ''; break;
                }
                const stream = new StrBuf();
                stream.Append(lbracket);
                if (paramClass === ParamClassEnum.PARAM_CLASS_EXTERN_SCRIPT) {
                    stream.Append(data.GetParamId(0));
                }
                else {
                    const ct = data.GetParamNum();
                    for (let i = 0; i < ct; ++i) {
                        if (data.HaveParam() && i > 0) stream.Append(',');
                        const param = data.GetParam(i);
                        stream.Append(param.ToScriptString(includeComment, delim));
                        if (data.HaveStatement()) stream.Append(';');
                    }
                }
                stream.Append(rbracket);
                return lineNo + line + stream.ToString();
            }
        }
        return lineNo + line;
    }

    static writeStatementsOrExternScript(stream, data, indent, delim) {
        if (data.HaveStatement()) {
            Utility.writeLine(stream, '', 0);
            Utility.writeLine(stream, '{', indent);
            ++indent;
            const ct = data.GetParamNum();
            for (let i = 0; i < ct; ++i) {
                const tempData = data.GetParam(i);
                Utility.writeSyntaxComponent(stream, tempData, indent, false, true, delim);
            }
            --indent;
            Utility.writeText(stream, '}', indent);
        }
        else if (data.HaveExternScript()) {
            Utility.writeLine(stream, '', 0);
            const script = data.GetParamId(0);
            if (script.indexOf('\n') >= 0) {
                Utility.writeLine(stream, delim.ScriptBeginDelimiter, indent);
            }
            else {
                Utility.writeText(stream, delim.ScriptBeginDelimiter, indent);
            }
            stream.Append(script);
            if (script.length > 0 && script[script.length - 1] === '\n') {
                Utility.writeText(stream, delim.ScriptEndDelimiter, indent);
            }
            else {
                stream.Append(delim.ScriptEndDelimiter);
            }
        }
    }

    static writeFirstComments(stream, data, indent, firstLineNoIndent) {
        let isFirst = true;
        let haveComments = false;
        let newLine = false;
        for (const cmt of data.FirstComments) {
            if (isFirst && !data.FirstCommentOnNewLine) {
                Utility.writeText(stream, cmt, firstLineNoIndent ? 0 : indent);
            }
            else {
                Utility.writeLine(stream, cmt, isFirst && firstLineNoIndent ? 0 : indent);
                newLine = true;
            }
            isFirst = false;
            haveComments = true;
        }
        if (haveComments && !newLine) {
            // Line-leading comments must be followed by a newline, otherwise they may comment out the code.
            Utility.writeLine(stream, '', 0);
        }
    }

    static writeLastComments(stream, data, indent, isLastOfStatement) {
        let isFirst = true;
        if (data.LastComments.length > 0) {
            if (data.LastCommentOnNewLine) {
                Utility.writeLine(stream, '', 0);
            }
            isFirst = true;
            for (const cmt of data.LastComments) {
                if (isFirst && !data.LastCommentOnNewLine) {
                    Utility.writeText(stream, cmt, 1);
                }
                else {
                    Utility.writeText(stream, cmt, indent);
                }
                if (isLastOfStatement) {
                    Utility.writeLine(stream, '', 0);
                }
                isFirst = false;
            }
        }
        else if (isLastOfStatement) {
            Utility.writeLine(stream, '', 0);
        }
    }

    static writeText(stream, line, indent) {
        for (let i = 0; i < indent; ++i) stream.Append('\t');
        stream.Append(line);
    }

    static writeLine(stream, line, indent) {
        Utility.writeText(stream, line, indent);
        stream.Append('\r\n');
    }
}

const DslBinaryCode = Object.freeze({
    BeginStatement: 1,
    EndStatement: 2,
    EndStatementWithComma: 3,
    EndStatementWithSemiColon: 4,
    BeginFunction: 5,
    EndFunction: 6,
    EndFunctionWithComma: 7,
    EndFunctionWithSemiColon: 8,
    BeginValue: 9,
    EndValue: 10,
    EndValueWithComma: 11,
    EndValueWithSemiColon: 12,
    ValueTypeBegin: 13,
    ValueTypeEnd: 13 + AbstractSyntaxComponent.MAX_TYPE,
    ParamOrExternClassBegin: 17,
});

// Byte output stream, stand-in for System.IO.MemoryStream.
class ByteStream {
    constructor() { this.bytes = []; }
    WriteByte(b) { this.bytes.push(b & 0xff); }
    ToBytes() { return Uint8Array.from(this.bytes); }
    get Length() { return this.bytes.length; }
}

function utf8Encode(str) {
    return new TextEncoder().encode(str);
}
function utf8Decode(bytes, start, count) {
    return new TextDecoder('utf-8').decode(bytes.subarray(start, start + count));
}

Object.assign(Utility, {
    readInt(bytes, pos) {
        if (bytes && pos >= 0 && pos + 3 < bytes.length) {
            return bytes[pos] | (bytes[pos + 1] << 8) | (bytes[pos + 2] << 16) | (bytes[pos + 3] << 24);
        }
        return -1;
    },
    // Returns { value, byteCount } (C# out parameter).
    read7BitEncodedInt(bytes, pos) {
        let num = -1;
        let byteCount = 0;
        if (bytes && pos < bytes.length) {
            let bitCount = 0;
            let b;
            num = 0;
            do {
                if (bitCount === 35) {
                    num = -1;
                    break;
                }
                b = bytes[pos++];
                num |= (b & 0x7F) << bitCount;
                bitCount += 7;
            } while (pos < bytes.length && (b & 0x80) !== 0);
            byteCount = Math.floor(bitCount / 7);
        }
        return { value: num, byteCount };
    },
    writeInt(stream, val) {
        stream.WriteByte(val);
        stream.WriteByte(val >> 8);
        stream.WriteByte(val >> 16);
        stream.WriteByte(val >> 24);
    },
    write7BitEncodedInt(stream, val) {
        let num;
        for (num = val >>> 0; num >= 128; num >>>= 7) {
            stream.WriteByte(num | 0x80);
        }
        stream.WriteByte(num);
    },

    readByte(bytes, curCodeIndex) {
        if (curCodeIndex < bytes.length) return bytes[curCodeIndex];
        return 0;
    },
    readIdentifier(identifiers, curIdIndex) {
        if (curIdIndex < identifiers.length) return identifiers[curIdIndex];
        return '';
    },
    // Returns { isEnd, sep } (C# out parameter).
    isBinaryEndCode(endCodeStart, code) {
        if (code >= endCodeStart && code <= endCodeStart + AbstractSyntaxComponent.SEPARATOR_SEMICOLON - AbstractSyntaxComponent.SEPARATOR_NOTHING) {
            return { isEnd: true, sep: code - endCodeStart + AbstractSyntaxComponent.SEPARATOR_NOTHING };
        }
        return { isEnd: false, sep: 0 };
    },
    getBinaryEndCode(endCode, sep) {
        if (sep >= AbstractSyntaxComponent.SEPARATOR_NOTHING && sep <= AbstractSyntaxComponent.SEPARATOR_SEMICOLON) {
            return endCode + sep - AbstractSyntaxComponent.SEPARATOR_NOTHING;
        }
        return endCode;
    },

    readBinary(bytes, start, count, identifiers) {
        const infos = [];
        const cur = { codeIndex: 0, idIndex: 0 };
        while (cur.codeIndex < count) {
            while (cur.codeIndex < count) {
                const b = bytes[start + cur.codeIndex];
                if (b === DslBinaryCode.BeginStatement || b === DslBinaryCode.BeginFunction || b === DslBinaryCode.BeginValue) break;
                ++cur.codeIndex;
            }
            if (cur.codeIndex < count) {
                const info = Utility.readBinaryData(bytes, start, cur, identifiers);
                if (info !== null && info.IsValid()) infos.push(info);
            }
        }
        return infos;
    },
    readBinaryData(bytes, start, cur, identifiers) {
        const code = Utility.readByte(bytes, start + cur.codeIndex);
        if (code === DslBinaryCode.BeginValue) {
            const data = new ValueData();
            Utility.readBinaryValue(bytes, start, cur, identifiers, data);
            return data;
        }
        if (code === DslBinaryCode.BeginFunction) {
            const data = new FunctionData();
            Utility.readBinaryFunction(bytes, start, cur, identifiers, data);
            return data;
        }
        if (code === DslBinaryCode.BeginStatement) {
            const data = new StatementData();
            Utility.readBinaryStatement(bytes, start, cur, identifiers, data);
            return data;
        }
        return null;
    },
    readBinaryValue(bytes, start, cur, identifiers, data) {
        let code = Utility.readByte(bytes, start + cur.codeIndex++);
        if (code === DslBinaryCode.BeginValue) {
            code = Utility.readByte(bytes, start + cur.codeIndex);
            if (code >= DslBinaryCode.ValueTypeBegin) {
                ++cur.codeIndex;
                data.SetType(code - DslBinaryCode.ValueTypeBegin);
                data.SetId(Utility.readIdentifier(identifiers, cur.idIndex++));
                const r = Utility.read7BitEncodedInt(bytes, start + cur.codeIndex);
                data.SetLine(r.value);
                cur.codeIndex += r.byteCount;
            }
            code = Utility.readByte(bytes, start + cur.codeIndex);
            const e = Utility.isBinaryEndCode(DslBinaryCode.EndValue, code);
            if (e.isEnd) {
                data.SetSeparator(e.sep);
                ++cur.codeIndex;
            }
        }
    },
    readBinaryFunction(bytes, start, cur, identifiers, data) {
        let code = Utility.readByte(bytes, start + cur.codeIndex++);
        if (code === DslBinaryCode.BeginFunction) {
            code = Utility.readByte(bytes, start + cur.codeIndex);
            if (code >= DslBinaryCode.ParamOrExternClassBegin) {
                ++cur.codeIndex;
                data.SetParamClass(code - DslBinaryCode.ParamOrExternClassBegin);
                if (data.HaveParamOrStatement()) {
                    const r = Utility.read7BitEncodedInt(bytes, start + cur.codeIndex);
                    cur.codeIndex += r.byteCount;
                }
            }
            code = Utility.readByte(bytes, start + cur.codeIndex);
            if (code === DslBinaryCode.BeginValue) {
                const valueData = new ValueData();
                Utility.readBinaryValue(bytes, start, cur, identifiers, valueData);
                data.Name = valueData;
            }
            else if (code === DslBinaryCode.BeginFunction) {
                const callData = new FunctionData();
                Utility.readBinaryFunction(bytes, start, cur, identifiers, callData);
                data.LowerOrderFunction = callData;
            }
            for (; ;) {
                code = Utility.readByte(bytes, start + cur.codeIndex);
                const e = Utility.isBinaryEndCode(DslBinaryCode.EndFunction, code);
                if (e.isEnd) {
                    data.SetSeparator(e.sep);
                    ++cur.codeIndex;
                    break;
                }
                const syntaxData = Utility.readBinaryData(bytes, start, cur, identifiers);
                if (syntaxData !== null) {
                    data.Params.push(syntaxData);
                }
                else {
                    break;
                }
            }
        }
    },
    readBinaryStatement(bytes, start, cur, identifiers, data) {
        let code = Utility.readByte(bytes, start + cur.codeIndex++);
        if (code === DslBinaryCode.BeginStatement) {
            const r = Utility.read7BitEncodedInt(bytes, start + cur.codeIndex);
            cur.codeIndex += r.byteCount;
            for (; ;) {
                code = Utility.readByte(bytes, start + cur.codeIndex);
                if (code === DslBinaryCode.BeginValue) {
                    const valData = new ValueData();
                    Utility.readBinaryValue(bytes, start, cur, identifiers, valData);
                    data.Functions.push(valData);
                }
                else if (code === DslBinaryCode.BeginFunction) {
                    const funcData = new FunctionData();
                    Utility.readBinaryFunction(bytes, start, cur, identifiers, funcData);
                    data.Functions.push(funcData);
                }
                else {
                    const e = Utility.isBinaryEndCode(DslBinaryCode.EndStatement, code);
                    if (e.isEnd) {
                        data.SetSeparator(e.sep);
                        ++cur.codeIndex;
                    }
                    break;
                }
            }
        }
    },

    writeBinary(stream, identifiers, data) {
        if (data instanceof ValueData) {
            Utility.writeBinaryValue(stream, identifiers, data);
        }
        else if (data instanceof FunctionData) {
            Utility.writeBinaryFunction(stream, identifiers, data);
        }
        else {
            Utility.writeBinaryStatement(stream, identifiers, data);
        }
    },
    writeBinaryValue(stream, identifiers, data) {
        stream.WriteByte(DslBinaryCode.BeginValue);
        if (data !== null) {
            stream.WriteByte(DslBinaryCode.ValueTypeBegin + data.GetIdType());
            identifiers.push(data.GetId());
            Utility.write7BitEncodedInt(stream, data.GetLine());
            stream.WriteByte(Utility.getBinaryEndCode(DslBinaryCode.EndValue, data.GetSeparator()));
        }
    },
    writeBinaryFunction(stream, identifiers, data) {
        stream.WriteByte(DslBinaryCode.BeginFunction);
        if (data !== null) {
            stream.WriteByte(DslBinaryCode.ParamOrExternClassBegin + data.GetParamClass());
            if (data.HaveParamOrStatement()) {
                Utility.write7BitEncodedInt(stream, data.GetParamNum());
            }
            if (data.IsHighOrder) {
                Utility.writeBinaryFunction(stream, identifiers, data.LowerOrderFunction);
            }
            else {
                Utility.writeBinaryValue(stream, identifiers, data.Name);
            }
            for (const syntaxData of data.Params) {
                Utility.writeBinary(stream, identifiers, syntaxData);
            }
            stream.WriteByte(Utility.getBinaryEndCode(DslBinaryCode.EndFunction, data.GetSeparator()));
        }
    },
    writeBinaryStatement(stream, identifiers, data) {
        stream.WriteByte(DslBinaryCode.BeginStatement);
        Utility.write7BitEncodedInt(stream, data.GetFunctionNum());
        for (const f of data.Functions) {
            Utility.writeBinary(stream, identifiers, f);
        }
        stream.WriteByte(Utility.getBinaryEndCode(DslBinaryCode.EndStatement, data.GetSeparator()));
    },
});

const Dsl = {
    ParamClassEnum,
    DslBinaryCode,
    ByteStream,
    utf8Encode,
    utf8Decode,
    StrBuf,
    DelimiterInfo,
    SyntaxComponentCommentsInfo,
    FunctionCommentsInfo,
    DslGlobals,
    AbstractSyntaxComponent,
    ValueOrFunctionData,
    ValueData,
    FunctionData,
    StatementData,
    Utility,
};

if (typeof module !== 'undefined' && module.exports) {
    module.exports = Dsl;
}
if (typeof globalThis !== 'undefined') {
    globalThis.Dsl = Object.assign(globalThis.Dsl || {}, Dsl);
}
