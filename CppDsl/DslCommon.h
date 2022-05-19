#ifndef _DSL_COMMON_H
#define _DSL_COMMON_H

class IDslSyntaxCommon
{
public:
    enum
    {
        TYPE_NULL,
        TYPE_VALUE,
        TYPE_FUNCTION,
        TYPE_STATEMENT,
    };
    enum
    {
        VALUE_TYPE_IDENTIFIER = 0,
        VALUE_TYPE_NUM,
        VALUE_TYPE_STRING,
        VALUE_TYPE_FUNCTION,
        VALUE_TYPE_MAX = VALUE_TYPE_STRING
    };
    enum
    {
        PARAM_CLASS_NOTHING = 0,
        PARAM_CLASS_PARENTHESIS,
        PARAM_CLASS_BRACKET,
        PARAM_CLASS_PERIOD,
        PARAM_CLASS_PERIOD_PARENTHESIS,
        PARAM_CLASS_PERIOD_BRACKET,
        PARAM_CLASS_PERIOD_BRACE,
        PARAM_CLASS_QUESTION_PERIOD,
        PARAM_CLASS_QUESTION_PARENTHESIS,
        PARAM_CLASS_QUESTION_BRACKET,
        PARAM_CLASS_QUESTION_BRACE,
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
        PARAM_CLASS_COLON_COLON_PARENTHESIS,
        PARAM_CLASS_COLON_COLON_BRACKET,
        PARAM_CLASS_COLON_COLON_BRACE,
        PARAM_CLASS_PERIOD_STAR,
        PARAM_CLASS_QUESTION_PERIOD_STAR,
        PARAM_CLASS_POINTER_STAR,
        PARAM_CLASS_OPERATOR,
        PARAM_CLASS_TERNARY_OPERATOR,
        PARAM_CLASS_MAX,
        PARAM_CLASS_WRAP_INFIX_CALL_MASK = 0x20,
        PARAM_CLASS_UNMASK = 0x1F,
    };
public:
    virtual ~IDslSyntaxCommon(void) {}
};

enum DslBinaryCode
{
    BinCode_BeginStatement = 1,
    BinCode_EndStatement,
    BinCode_BeginFunction,
    BinCode_EndFunction,
    BinCode_BeginValue,
    BinCode_EndValue,
    BinCode_ValueTypeBegin,
    BinCode_ValueTypeEnd = BinCode_ValueTypeBegin + IDslSyntaxCommon::VALUE_TYPE_MAX,
    BinCode_ParamOrExternClassBegin
};

#endif