#ifndef _DSL_COMMON_H
#define _DSL_COMMON_H

class IDslSyntaxCommon
{
public:
    enum
    {
        SEPARATOR_NOTHING = 0,
        SEPARATOR_COMMA,
        SEPARATOR_SEMICOLON,
    };
    enum
    {
        TYPE_UNKNOWN_SYNTAX = 0,
        TYPE_VALUE,
        TYPE_FUNCTION,
        TYPE_STATEMENT,
    };
    enum
    {
        VALUE_TYPE_IDENTIFIER = 0,
        VALUE_TYPE_NUM,
        VALUE_TYPE_STRING,
        VALUE_TYPE_DOLLAR_STRING,
        VALUE_TYPE_FUNCTION,
        VALUE_TYPE_MAX = VALUE_TYPE_DOLLAR_STRING
    };
    enum
    {
        PARAM_CLASS_MIN = 0,
        PARAM_CLASS_NOTHING = PARAM_CLASS_MIN,
        PARAM_CLASS_PARENTHESIS,
        PARAM_CLASS_BRACKET,
        PARAM_CLASS_PERIOD,
        PARAM_CLASS_POINTER,
        PARAM_CLASS_STATEMENT,
        PARAM_CLASS_EXTERN_SCRIPT,
        PARAM_CLASS_PARENTHESIS_COLON,
        PARAM_CLASS_BRACKET_COLON,
        PARAM_CLASS_ANGLE_BRACKET_COLON,
        PARAM_CLASS_PARENTHESIS_PERCENT,
        PARAM_CLASS_BRACKET_PERCENT,
        PARAM_CLASS_BRACE_PERCENT,
        PARAM_CLASS_ANGLE_BRACKET_PERCENT,
        PARAM_CLASS_COLON_COLON,
        PARAM_CLASS_PERIOD_STAR,
        PARAM_CLASS_POINTER_STAR,
        PARAM_CLASS_OPERATOR,
        PARAM_CLASS_TERNARY_OPERATOR,
        PARAM_CLASS_QUESTION_NULLABLE_OPERATOR,
        PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR,
        PARAM_CLASS_MAX,
        PARAM_CLASS_WRAP_INFIX_CALL_MASK = 0x20,
        PARAM_CLASS_UNMASK = 0x1F,
    };
    enum
    {
        OPERATOR_CATEGORY_NORMAL = 0,
        OPERATOR_CATEGORY_TERNARY,
        OPERATOR_CATEGORY_MAXNUM
    };
    enum
    {
        PAIR_TYPE_NONE = 0,
        PAIR_TYPE_QUESTION_COLON,
        PAIR_TYPE_PARENTHESIS,
        PAIR_TYPE_BRACKET,
        PAIR_TYPE_BRACE,
        PAIR_TYPE_BRACKET_COLON,
        PAIR_TYPE_PARENTHESIS_COLON,
        PAIR_TYPE_ANGLE_BRACKET_COLON,
        PAIR_TYPE_BRACE_PERCENT,
        PAIR_TYPE_BRACKET_PERCENT,
        PAIR_TYPE_PARENTHESIS_PERCENT,
        PAIR_TYPE_ANGLE_BRACKET_PERCENT,
        PAIR_TYPE_MAXNUM
    };
public:
    virtual ~IDslSyntaxCommon() {}
};

enum DslBinaryCode
{
    BinCode_BeginStatement = 1,
    BinCode_EndStatement,
    BinCode_EndStatementWithComma,
    BinCode_EndStatementWithSemiColon,
    BinCode_BeginFunction,
    BinCode_EndFunction,
    BinCode_EndFunctionWithComma,
    BinCode_EndFunctionWithSemiColon,
    BinCode_BeginValue,
    BinCode_EndValue,
    BinCode_EndValueWithComma,
    BinCode_EndValueWithSemiColon,
    BinCode_ValueTypeBegin,
    BinCode_ValueTypeEnd = BinCode_ValueTypeBegin + IDslSyntaxCommon::VALUE_TYPE_MAX,
    BinCode_ParamOrExternClassBegin
};

#endif