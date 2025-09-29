/*****************************************************************************

calc.h

******************************************************************************/

#ifndef _DSL_PARSER_H
#define _DSL_PARSER_H

#include "BaseType.h"
#include "Delegation.h"
#include "DslCommon.h"
#include <cstdint>
#include <new>
#include <string>
#include <vector>
#include <unordered_map>

class SlkToken;
class ActionForSourceCodeScript;
namespace DslParser
{
    template<typename DestT>
    struct ReinterpretCast final
    {
        template<typename SrcT>
        static DestT From(const SrcT& v)
        {
            union
            {
                SrcT m_Src;
                DestT m_Dest;
            } tmp{.m_Src = v};
            return tmp.m_Dest;
        }
    };

    enum
    {
        SINGLE_ERROR_INFO_CAPACITY = 1024,
        MAX_ERROR_INFO_NUM = 128,

        INIT_FUNCTION_PARAM = 1,
        MAX_DELTA_FUNCTION_PARAM = 8,
        MAX_DELTA_FUNCTION_STATEMENT = 32,
        INIT_STATEMENT_FUNCTION = 1,
        MAX_DELTA_STATEMENT_FUNCTION = 1,
        INIT_DSL_INFO = 1,
        MAX_DELTA_DSL_INFO = 32,
        DELTA_COMMENT = 2,
    };

    enum
    {
        //These three numbers cannot be greater than PTR_ARRAY_POOL_FREELINK_HEADER_SIZE
        MAX_FUNCTION_DIMENSION_NUM = 256 * 1024,
        MAX_FUNCTION_PARAM_NUM = 256 * 1024,
        MAX_DSL_INFO_NUM = 256 * 1024,

        STRING_AND_OBJECT_BUFFER_SIZE = 8 * 1024 * 1024,
        SYNTAXCOMPONENT_AND_PTR_ARRAY_POOL_SIZE = 1024 * 1024,
        PTR_ARRAY_POOL_FREELINK_HEADER_SIZE = 256 * 1024,
    };

    class DslOptions final
    {
    public:
        DslOptions() :
            m_MaxFunctionDimensionNum(MAX_FUNCTION_DIMENSION_NUM),
            m_MaxParamNum(MAX_FUNCTION_PARAM_NUM),
            m_MaxDslInfoNum(MAX_DSL_INFO_NUM)
        {
        }
    public:
        int GetMaxFunctionDimensionNum() const { return m_MaxFunctionDimensionNum; }
        void SetMaxFunctionDimensionNum(int val) { m_MaxFunctionDimensionNum = val; }
        int GetMaxParamNum() const { return m_MaxParamNum; }
        void SetMaxParamNum(int val) { m_MaxParamNum = val; }
        int GetMaxDslInfoNum() const { return m_MaxDslInfoNum; }
        void SetMaxDslInfoNum(int val) { m_MaxDslInfoNum = val; }
    private:
        int	m_MaxFunctionDimensionNum;
        int	m_MaxParamNum;
        int	m_MaxDslInfoNum;
    public:
        static bool DontLoadComments()
        {
            return DontLoadCommentsRef();
        }
        static void DontLoadComments(bool val)
        {
            DontLoadCommentsRef() = val;
        }
    private:
        static bool& DontLoadCommentsRef()
        {
            static bool s_DontLoadComments = false;
            return s_DontLoadComments;
        }
    };
    struct DelimiterInfo final
    {
        const char* ScriptBeginDelimiter;
        const char* ScriptEndDelimiter;
        const char* StringBeginDelimiter;
        const char* StringEndDelimiter;

        DelimiterInfo()
            :ScriptBeginDelimiter("{:"), ScriptEndDelimiter(":}"), StringBeginDelimiter("\""), StringEndDelimiter("\"")
        {}
        DelimiterInfo(const char* strBeginDelim, const char* strEndDelim, const char* scpBeginDelim, const char* scpEndDelim)
            :ScriptBeginDelimiter(scpBeginDelim), ScriptEndDelimiter(scpEndDelim), StringBeginDelimiter(strBeginDelim), StringEndDelimiter(strEndDelim)
        {}
    };

    //These two structures are used for pure data and do not require virtual destruction.
    struct SyntaxComponentCommentsInfo
    {
        const char** m_FirstComments;
        int m_FirstCommentNum;
        int m_FirstCommentSpace;
        int m_FirstCommentOnNewLine;
        const char** m_LastComments;
        int m_LastCommentNum;
        int m_LastCommentSpace;
        int m_LastCommentOnNewLine;

        SyntaxComponentCommentsInfo() :m_FirstComments(0), m_FirstCommentNum(0), m_FirstCommentSpace(0), m_FirstCommentOnNewLine(0),
            m_LastComments(0), m_LastCommentNum(0), m_LastCommentSpace(0), m_LastCommentOnNewLine(0)
        {}
    };
    struct FunctionCommentsInfo : public SyntaxComponentCommentsInfo
    {
        const char** m_Comments;
        int m_CommentNum;
        int m_CommentSpace;

        FunctionCommentsInfo() :SyntaxComponentCommentsInfo(), m_Comments(0), m_CommentNum(0), m_CommentSpace(0)
        {}
    };

    class IDslStringAndObjectBuffer;
    class ISyntaxComponent : public IDslSyntaxCommon
    {
    public:
        ISyntaxComponent(int syntaxType);
        virtual ~ISyntaxComponent() override;
    public:
        virtual int IsValid() const = 0;
        virtual const char* GetId() const = 0;
        virtual int GetIdType() const = 0;
        virtual int GetLine() const = 0;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const = 0;
        virtual int HaveId() const = 0;
    public:
        int GetSyntaxType() const { return m_SyntaxType; }
        void SetSeparator(int sep) { m_Separator = sep; }
        int GetSeparator() const { return m_Separator; }
        const char* GetSepChar() const
        {
            switch (m_Separator) {
            case SEPARATOR_COMMA:
                return ",";
            case SEPARATOR_SEMICOLON:
                return ";";
            default:
                return " ";
            }
        }
        void SetEmptySeparator()
        {
            m_Separator = (int)SEPARATOR_NOTHING;
        }
        void SetCommaSeparator()
        {
            m_Separator = (int)SEPARATOR_COMMA;
        }
        void SetSemiColonSeparator()
        {
            m_Separator = (int)SEPARATOR_SEMICOLON;
        }
        bool IsEmptySeparator()const
        {
            return m_Separator == (int)SEPARATOR_NOTHING;
        }
        bool IsCommaSeparator()const
        {
            return m_Separator == (int)SEPARATOR_COMMA;
        }
        bool IsSemiColonSeparator()const
        {
            return m_Separator == (int)SEPARATOR_SEMICOLON;
        }
        void AddFirstComment(const char* cmt)
        {
            if (0 == GetCommentsInfo())
                return;
            PrepareFirstComments();
            if (GetCommentsInfo()->m_FirstCommentNum < GetCommentsInfo()->m_FirstCommentSpace) {
                GetCommentsInfo()->m_FirstComments[GetCommentsInfo()->m_FirstCommentNum++] = cmt;
            }
        }
        void RemoveFirstComment(int index)
        {
            if (0 == GetCommentsInfo())
                return;
            if (index >= 0 && index < GetCommentsInfo()->m_FirstCommentNum) {
                for (int ix = index; ix < GetCommentsInfo()->m_FirstCommentNum - 1; ++ix) {
                    GetCommentsInfo()->m_FirstComments[ix] = GetCommentsInfo()->m_FirstComments[ix + 1];
                }
                --GetCommentsInfo()->m_FirstCommentNum;
            }
        }
        void ClearFirstComments()
        {
            if (0 == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_FirstCommentNum = 0;
        }
        int GetFirstCommentNum() const
        {
            if (0 == GetCommentsInfo())
                return 0;
            return GetCommentsInfo()->m_FirstCommentNum;
        }
        const char* GetFirstComment(int index) const
        {
            if (0 != GetCommentsInfo() && index >= 0 && index < GetCommentsInfo()->m_FirstCommentNum) {
                return GetCommentsInfo()->m_FirstComments[index];
            }
            else {
                return 0;
            }
        }
        int IsFirstCommentOnNewLine() const
        {
            if (0 == GetCommentsInfo())
                return 0;
            return GetCommentsInfo()->m_FirstCommentOnNewLine;
        }
        void SetFirstCommentOnNewLine(int v)
        {
            if (0 == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_FirstCommentOnNewLine = v;
        }
        void AddLastComment(const char* cmt)
        {
            if (0 == GetCommentsInfo())
                return;
            PrepareLastComments();
            if (GetCommentsInfo()->m_LastCommentNum < GetCommentsInfo()->m_LastCommentSpace) {
                GetCommentsInfo()->m_LastComments[GetCommentsInfo()->m_LastCommentNum++] = cmt;
            }
        }
        void RemoveLastComment(int index)
        {
            if (0 != GetCommentsInfo() && index >= 0 && index < GetCommentsInfo()->m_LastCommentNum) {
                for (int ix = index; ix < GetCommentsInfo()->m_LastCommentNum - 1; ++ix) {
                    GetCommentsInfo()->m_LastComments[ix] = GetCommentsInfo()->m_LastComments[ix + 1];
                }
                --GetCommentsInfo()->m_LastCommentNum;
            }
        }
        void ClearLastComments()
        {
            if (0 == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_LastCommentNum = 0;
        }
        int GetLastCommentNum() const
        {
            if (0 == GetCommentsInfo())
                return 0;
            return GetCommentsInfo()->m_LastCommentNum;
        }
        const char* GetLastComment(int index) const
        {
            if (0 != GetCommentsInfo() && index >= 0 && index < GetCommentsInfo()->m_LastCommentNum) {
                return GetCommentsInfo()->m_LastComments[index];
            }
            else {
                return 0;
            }
        }
        int IsLastCommentOnNewLine() const
        {
            if (0 == GetCommentsInfo())
                return 0;
            return GetCommentsInfo()->m_LastCommentOnNewLine;
        }
        void SetLastCommentOnNewLine(int v)
        {
            if (0 == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_LastCommentOnNewLine = v;
        }
        void CopyComments(const ISyntaxComponent& other)
        {
            CopyFirstComments(other);
            CopyLastComments(other);
        }
        void CopyFirstComments(const ISyntaxComponent& other)
        {
            if (0 == GetCommentsInfo() || 0 == other.GetCommentsInfo())
                return;
            int fnum = other.GetFirstCommentNum();
            if (fnum > 0) {
                GetCommentsInfo()->m_FirstCommentOnNewLine = other.GetCommentsInfo()->m_FirstCommentOnNewLine;
                for (int i = 0; i < fnum; ++i) {
                    AddFirstComment(other.GetFirstComment(i));
                }
            }
        }
        void CopyLastComments(const ISyntaxComponent& other)
        {
            if (0 == GetCommentsInfo() || 0 == other.GetCommentsInfo())
                return;
            int lnum = other.GetLastCommentNum();
            if (lnum > 0) {
                GetCommentsInfo()->m_LastCommentOnNewLine = other.GetCommentsInfo()->m_LastCommentOnNewLine;
                for (int i = 0; i < lnum; ++i) {
                    AddLastComment(other.GetLastComment(i));
                }
            }
        }
    public:
        void WriteFirstCommentsToFile(FILE* fp, int indent, int firstLineNoIndent) const;
        void WriteLastCommentsToFile(FILE* fp, int indent, int isLastOfStatement) const;
    protected:
        void CopyFrom(const ISyntaxComponent& other);
        void ReleaseFirstComments(IDslStringAndObjectBuffer* pBuffer, SyntaxComponentCommentsInfo* pCommentsInfo);
        void ReleaseLastComments(IDslStringAndObjectBuffer* pBuffer, SyntaxComponentCommentsInfo* pCommentsInfo);
    protected:
        virtual IDslStringAndObjectBuffer* GetBuffer() const { return 0; }
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo() const { return 0; }
    private:
        void PrepareFirstComments();
        void PrepareLastComments();
    private:
        int m_SyntaxType;
        int m_Separator;
    };

    class FunctionData;
    class ValueData;
    class ValueOrFunctionData : public ISyntaxComponent
    {
    public:
        ValueOrFunctionData(int syntaxType) :ISyntaxComponent(syntaxType)
        {}
    public:
        int IsValue()const
        {
            return GetSyntaxType() == ISyntaxComponent::TYPE_VALUE ? TRUE : FALSE;
        }
        int IsFunction()const
        {
            return GetSyntaxType() == ISyntaxComponent::TYPE_FUNCTION ? TRUE : FALSE;
        }
        const ValueData* AsValue()const
        {
            if (IsValue())
                return reinterpret_cast<const ValueData*>(this);
            else
                return nullptr;
        }
        ValueData* AsValue()
        {
            if (IsValue())
                return reinterpret_cast<ValueData*>(this);
            else
                return nullptr;
        }
        const FunctionData* AsFunction()const
        {
            if (IsFunction())
                return reinterpret_cast<const FunctionData*>(this);
            else
                return nullptr;
        }
        FunctionData* AsFunction()
        {
            if (IsFunction())
                return reinterpret_cast<FunctionData*>(this);
            else
                return nullptr;
        }
    private:
        ValueOrFunctionData(const ValueOrFunctionData& other) = delete;
        ValueOrFunctionData(ValueOrFunctionData&& other) noexcept = delete;
        ValueOrFunctionData& operator=(const ValueOrFunctionData& other) = delete;
        ValueOrFunctionData& operator=(ValueOrFunctionData&& other) noexcept = delete;
    };

    class ValueData final : public ValueOrFunctionData
    {
    public:
        ValueData() :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_IDENTIFIER), m_StringVal(0), m_Line(0) {}
        explicit ValueData(char* val) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_STRING), m_StringVal(val), m_Line(0) {}
        explicit ValueData(const char* val) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_STRING), m_ConstStringVal(val), m_Line(0) {}
        explicit ValueData(FunctionData* val) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_FUNCTION), m_FunctionVal(val), m_Line(0) {}
        explicit ValueData(char* val, int type) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_StringVal(val), m_Line(0) {}
        explicit ValueData(const char* val, int type) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_ConstStringVal(val), m_Line(0) {}
        ValueData(const ValueData& other) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_IDENTIFIER), m_StringVal(0), m_Line(0)
        {
            ISyntaxComponent::CopyFrom(other);
            CopyFrom(other);
        }
        ValueData(ValueData&& other) noexcept :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_IDENTIFIER), m_StringVal(0), m_Line(0)
        {
            ISyntaxComponent::CopyFrom(other);
            CopyFrom(other);
            other.~ValueData();
        }
        ValueData& operator=(const ValueData& other)
        {
            if (this == &other)
                return *this;
            ISyntaxComponent::CopyFrom(other);
            CopyFrom(other);
            return *this;
        }
        ValueData& operator=(ValueData&& other) noexcept
        {
            if (this == &other)
                return *this;
            ISyntaxComponent::CopyFrom(other);
            CopyFrom(other);
            other.~ValueData();
            return *this;
        }

        virtual int IsValid()const override;
        virtual int GetIdType()const override;
        virtual const char* GetId()const override;
        virtual int GetLine()const override;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual int HaveId()const override;

        FunctionData* GetFunction()const { return m_FunctionVal; }

        int IsNum()const { return (m_Type == VALUE_TYPE_NUM ? TRUE : FALSE); }
        int IsString()const { return (m_Type == VALUE_TYPE_STRING ? TRUE : FALSE); }
        int IsDollarString()const { return (m_Type == VALUE_TYPE_DOLLAR_STRING ? TRUE : FALSE); }
        int IsIdentifier()const { return (m_Type == VALUE_TYPE_IDENTIFIER && nullptr != m_ConstStringVal ? TRUE : FALSE); }
        int IsFunction()const { return (m_Type == VALUE_TYPE_FUNCTION ? TRUE : FALSE); }

        void SetInvalid()
        {
            m_Type = VALUE_TYPE_IDENTIFIER;
            m_StringVal = 0;
        }
        void SetNumber(char* str)
        {
            m_Type = VALUE_TYPE_NUM;
            m_StringVal = str;
        }
        void SetNumber(const char* str)
        {
            m_Type = VALUE_TYPE_NUM;
            m_ConstStringVal = str;
        }
        void SetString(char* str)
        {
            m_Type = VALUE_TYPE_STRING;
            m_StringVal = str;
        }
        void SetString(const char* str)
        {
            m_Type = VALUE_TYPE_STRING;
            m_ConstStringVal = str;
        }
        void SetDollarString(char* str)
        {
            m_Type = VALUE_TYPE_DOLLAR_STRING;
            m_StringVal = str;
        }
        void SetDollarString(const char* str)
        {
            m_Type = VALUE_TYPE_DOLLAR_STRING;
            m_ConstStringVal = str;
        }
        void SetFunction(FunctionData* func)
        {
            m_Type = VALUE_TYPE_FUNCTION;
            m_FunctionVal = func;
        }
        void SetIdentifier(char* name)
        {
            m_Type = VALUE_TYPE_IDENTIFIER;
            m_StringVal = name;
        }
        void SetTypeAndId(int type, const char* id)
        {
            m_Type = type;
            m_ConstStringVal = id;
        }
        void SetType(int type)
        {
            m_Type = type;
        }
        void SetLine(int line)
        {
            m_Line = line;
        }
    private:
        void CopyFrom(const ValueData& other)
        {
            m_Type = other.m_Type;
            m_StringVal = other.m_StringVal;
            m_Line = other.m_Line;
        }
    private:
        int m_Type;
        union
        {
            char* m_StringVal;
            const char* m_ConstStringVal;//The same type as m_StringVal in the script, used to implement automatic const_cast
            FunctionData* m_FunctionVal;
        };
        int m_Line;
    };

    class IDslStringAndObjectBuffer;
    class StatementData;
    class FunctionData final : public ValueOrFunctionData
    {
        using SyntaxComponentPtr = ISyntaxComponent*;
    public:
        virtual int IsValid()const override
        {
            if (m_Name.IsValid())
                return TRUE;
            else if (HaveParamOrStatement())
                return TRUE;
            else
                return FALSE;
        }
        virtual int GetIdType()const override { return m_Name.GetIdType(); }
        virtual const char* GetId()const override { return m_Name.GetId(); }
        virtual int GetLine()const override;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual int HaveId()const override { return m_Name.HaveId(); }
    public:
        void SetName(const ValueData& val) { m_Name = val; }
        ValueData& GetName() { return m_Name; }
        void ClearParams() { m_ParamNum = 0; }
        void RemoveLastParam()
        {
            if (0 == m_Params || m_ParamNum <= 0)
                return;
            --m_ParamNum;
            m_Params[m_ParamNum] = nullptr;
        }
        void AddParam(ISyntaxComponent* pVal)
        {
            if (0 == pVal || m_ParamNum < 0 || m_ParamNum >= m_MaxParamNum)
                return;
            PrepareParams();
            if (0 == m_Params || m_ParamNum >= m_ParamSpace)
                return;
            m_Params[m_ParamNum] = pVal;
            ++m_ParamNum;
        }
        void SetParam(int index, ISyntaxComponent* pVal)
        {
            if (nullptr == pVal || index < 0 || index >= m_MaxParamNum)
                return;
            m_Params[index] = pVal;
        }
        void SetParamClass(int v)
        {
            int innerType = v & (int)PARAM_CLASS_UNMASK;
            if (innerType >= (int)PARAM_CLASS_MIN && innerType < (int)PARAM_CLASS_MAX) {
                m_ParamClass = v;
            }
        }
        int GetParamClass()const { return m_ParamClass; }
        int GetParamClassUnmasked()const
        {
            int paramClass = (m_ParamClass & (int)PARAM_CLASS_UNMASK);
            return paramClass;
        }
        int HaveParamClassInfixFlag()const
        {
            int infix = (m_ParamClass & (int)PARAM_CLASS_WRAP_INFIX_CALL_MASK);
            return infix == (int)PARAM_CLASS_WRAP_INFIX_CALL_MASK ? TRUE : FALSE;
        }
        void SetInfixOperatorParamClass()
        {
            m_ParamClass = (int)(PARAM_CLASS_WRAP_INFIX_CALL_MASK | PARAM_CLASS_OPERATOR);
        }
        void SetOperatorParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_OPERATOR;
        }
        void SetQuestionNullableOperatorParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_QUESTION_NULLABLE_OPERATOR;
        }
        void SetExclamationNullableOperatorParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR;
        }
        void SetTernaryOperatorParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_TERNARY_OPERATOR;
        }
        void SetParenthesesParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_PARENTHESES;
        }
        void SetBracketParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_BRACKET;
        }
        void SetColonColonParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_COLON_COLON;
        }
        void SetPeriodParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_PERIOD;
        }
        void SetPeriodStarParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_PERIOD_STAR;
        }
        void SetPointerParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_POINTER;
        }
        void SetPointerStarParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_POINTER_STAR;
        }
        void SetParenthesesColonParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_PARENTHESES_COLON;
        }
        void SetBracketColonParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_BRACKET_COLON;
        }
        void SetAngleBracketColonParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_ANGLE_BRACKET_COLON;
        }
        void SetParenthesesPercentParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_PARENTHESES_PERCENT;
        }
        void SetBracketPercentParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_BRACKET_PERCENT;
        }
        void SetBracePercentParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_BRACE_PERCENT;
        }
        void SetAngleBracketPercentParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_ANGLE_BRACKET_PERCENT;
        }
        int IsOperatorParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_OPERATOR ? TRUE : FALSE;
        }
        int IsQuestionNullableOperatorParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_QUESTION_NULLABLE_OPERATOR ? TRUE : FALSE;
        }
        int IsExclamationNullableOperatorParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR ? TRUE : FALSE;
        }
        int IsTernaryOperatorParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_TERNARY_OPERATOR ? TRUE : FALSE;
        }
        bool IsParenthesesParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_PARENTHESES;
        }
        bool IsBracketParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_BRACKET;
        }
        bool IsColonColonParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_COLON_COLON;
        }
        bool IsPeriodParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_PERIOD;
        }
        bool IsPeriodStarParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_PERIOD_STAR;
        }
        bool IsPointerParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_POINTER;
        }
        bool IsPointerStarParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_POINTER_STAR;
        }
        bool IsParenthesesColonParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_PARENTHESES_COLON;
        }
        bool IsBracketColonParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_BRACKET_COLON;
        }
        bool IsAngleBracketColonParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_ANGLE_BRACKET_COLON;
        }
        bool IsParenthesesPercentParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_PARENTHESES_PERCENT;
        }
        bool IsBracketPercentParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_BRACKET_PERCENT;
        }
        bool IsBracePercentParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_BRACE_PERCENT;
        }
        bool IsAngleBracketPercentParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_ANGLE_BRACKET_PERCENT;
        }
        int IsMemberParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return (paramClass == (int)PARAM_CLASS_COLON_COLON ||
                paramClass == (int)PARAM_CLASS_PERIOD ||
                paramClass == (int)PARAM_CLASS_PERIOD_STAR ||
                paramClass == (int)PARAM_CLASS_POINTER ||
                paramClass == (int)PARAM_CLASS_POINTER_STAR) ? TRUE : FALSE;
        }
        void SetStatementParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_STATEMENT;
        }
        void SetExternScriptParamClass()
        {
            m_ParamClass = (int)PARAM_CLASS_EXTERN_SCRIPT;
        }
        int HaveParamOrStatement()const { return m_ParamClass != PARAM_CLASS_NOTHING ? TRUE : FALSE; }
        int HaveParam()const { return HaveParamOrStatement() && !HaveStatement() && !HaveExternScript(); }
        int HaveStatement()const { return m_ParamClass == PARAM_CLASS_STATEMENT ? TRUE : FALSE; }
        int HaveExternScript()const { return m_ParamClass == PARAM_CLASS_EXTERN_SCRIPT ? TRUE : FALSE; }
        int IsHighOrder()const { return m_Name.IsFunction(); }
        FunctionData& GetLowerOrderFunction()const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr) {
                return *fptr;
            }
            else {
                return *GetNullFunctionPtr();
            }
        }
        const FunctionData& GetThisOrLowerOrderCall()const
        {
            if (HaveParam()) {
                return *this;
            }
            else if (HaveLowerOrderParam() && m_Name.GetFunction()) {
                return *m_Name.GetFunction();
            }
            else {
                return *GetNullFunctionPtr();
            }
        }
        FunctionData& GetThisOrLowerOrderCall()
        {
            if (HaveParam()) {
                return *this;
            }
            else if (HaveLowerOrderParam() && m_Name.GetFunction()) {
                return *m_Name.GetFunction();
            }
            else {
                return *GetNullFunctionPtr();
            }
        }
        const FunctionData& GetThisOrLowerOrderBody()const
        {
            if (HaveStatement()) {
                return *this;
            }
            else if (HaveLowerOrderStatement() && m_Name.GetFunction()) {
                return *m_Name.GetFunction();
            }
            else {
                return *GetNullFunctionPtr();
            }
        }
        FunctionData& GetThisOrLowerOrderBody()
        {
            if (HaveStatement()) {
                return *this;
            }
            else if (HaveLowerOrderStatement() && m_Name.GetFunction()) {
                return *m_Name.GetFunction();
            }
            else {
                return *GetNullFunctionPtr();
            }
        }
        const FunctionData& GetThisOrLowerOrderScript()const
        {
            if (HaveExternScript()) {
                return *this;
            }
            else if (HaveLowerOrderExternScript() && m_Name.GetFunction()) {
                return *m_Name.GetFunction();
            }
            else {
                return *GetNullFunctionPtr();
            }
        }
        FunctionData& GetThisOrLowerOrderScript()
        {
            if (HaveExternScript()) {
                return *this;
            }
            else if (HaveLowerOrderExternScript() && m_Name.GetFunction()) {
                return *m_Name.GetFunction();
            }
            else {
                return *GetNullFunctionPtr();
            }
        }
        int HaveLowerOrderParam()const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveParam())
                return TRUE;
            else
                return FALSE;
        }
        int HaveLowerOrderStatement()const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveStatement())
                return TRUE;
            else
                return FALSE;
        }
        int HaveLowerOrderExternScript()const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveExternScript())
                return TRUE;
            else
                return FALSE;
        }
    public:
        const ValueData& GetName()const { return m_Name; }
        int GetParamNum()const { return m_ParamNum; }
        ISyntaxComponent* GetParam(int index)const
        {
            if (0 == m_Params || index < 0 || index >= m_ParamNum || index >= m_MaxParamNum)
                return GetNullSyntaxPtr();
            return m_Params[index];
        }
        const char* GetParamId(int index)const
        {
            if (0 == m_Params || index < 0 || index >= m_ParamNum || index >= m_MaxParamNum)
                return "";
            return m_Params[index]->GetId();
        }
    public:
        void AddComment(const char* cmt)
        {
            auto p = m_pCommentsInfo;
            if (0 == p)
                return;
            PrepareComments();
            if (p->m_CommentNum < p->m_CommentSpace) {
                p->m_Comments[p->m_CommentNum++] = cmt;
            }
        }
        void RemoveComment(int index)
        {
            auto p = m_pCommentsInfo;
            if (0 == p)
                return;
            if (index >= 0 && index < p->m_CommentNum) {
                for (int ix = index; ix < p->m_CommentNum - 1; ++ix) {
                    p->m_Comments[ix] = p->m_Comments[ix + 1];
                }
                --p->m_CommentNum;
            }
        }
        void ClearComments()
        {
            auto p = m_pCommentsInfo;
            if (0 == p)
                return;
            p->m_CommentNum = 0;
        }
        int GetCommentNum() const
        {
            auto p = m_pCommentsInfo;
            if (0 == p)
                return 0;
            return p->m_CommentNum;
        }
        const char* GetComment(int index) const
        {
            auto p = m_pCommentsInfo;
            if (0 == p)
                return 0;
            if (index >= 0 && index < p->m_CommentNum) {
                return p->m_Comments[index];
            }
            else {
                return 0;
            }
        }
    public:
        FunctionData(IDslStringAndObjectBuffer& buffer);
        virtual ~FunctionData() override;
        void InitParamsCapacity(int c);
    protected:
        virtual IDslStringAndObjectBuffer* GetBuffer() const override
        {
            return &m_Buffer;
        }
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo() const override
        {
            return m_pCommentsInfo;
        }
    private:
        FunctionData(const FunctionData& other) = delete;
        FunctionData(FunctionData&& other) noexcept = delete;
        FunctionData operator=(const FunctionData& other) = delete;
        FunctionData& operator=(FunctionData&& other) noexcept = delete;
    private:
        void PrepareParams();
        void ReleaseParams();
        void PrepareComments();
        void ReleaseComments();
    private:
        ISyntaxComponent* GetNullSyntaxPtr()const;
        FunctionData* GetNullFunctionPtr()const;
    private:
        ValueData m_Name;
        ISyntaxComponent** m_Params;
        int m_ParamNum;
        int m_ParamSpace;
        int m_MaxParamNum;
        int m_ParamClass;
    private:
        IDslStringAndObjectBuffer& m_Buffer;
        FunctionCommentsInfo* m_pCommentsInfo;
    };

    /* Memo: Why do members of StatementData not use ISyntaxComponent[] but FunctionData[]?
    * 1. Although FunctionData here can be degenerated into ValueData grammatically, it cannot be StatementData, so it cannot be conceptually equivalent to ISyntaxComponent.
    * 2. In terms of design, FunctionData should take the degradation situation into consideration and try not to occupy additional space in the degradation situation.
    */
    class StatementData final : public ISyntaxComponent
    {
    public:
        virtual int IsValid()const override
        {
            if (nullptr != m_ValueOrFunctions && m_ValueOrFunctionNum > 0 && m_ValueOrFunctions[0]->IsValid())
                return TRUE;
            else
                return FALSE;
        }
        virtual int GetIdType()const override
        {
            int type = ValueData::VALUE_TYPE_IDENTIFIER;
            if (IsValid()) {
                type = m_ValueOrFunctions[0]->GetIdType();
            }
            return type;
        }
        virtual const char* GetId()const override
        {
            const char* str = "";
            if (IsValid()) {
                str = m_ValueOrFunctions[0]->GetId();
            }
            return str;
        }
        virtual int GetLine()const override;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual int HaveId() const override
        {
            if (nullptr == m_ValueOrFunctions || 0 == m_ValueOrFunctionNum)
                return FALSE;
            else
                return m_ValueOrFunctions[m_ValueOrFunctionNum - 1]->HaveId();
        }
    public:
        void ClearFunctions() { m_ValueOrFunctionNum = 0; }
        void AddFunction(ValueOrFunctionData* pVal)
        {
            if (nullptr == pVal || m_ValueOrFunctionNum < 0 || m_ValueOrFunctionNum >= m_MaxValueOrFunctionNum)
                return;
            PrepareFunctions();
            if (nullptr == m_ValueOrFunctions || m_ValueOrFunctionNum >= m_ValueOrFunctionSpace)
                return;
            m_ValueOrFunctions[m_ValueOrFunctionNum] = pVal;
            ++m_ValueOrFunctionNum;
        }
        void RemoveLastFunction()
        {
            if (nullptr == m_ValueOrFunctions || 0 == m_ValueOrFunctionNum)
                return;
            --m_ValueOrFunctionNum;
            m_ValueOrFunctions[m_ValueOrFunctionNum] = nullptr;
        }
        ValueOrFunctionData*& GetLastFunctionRef()const
        {
            if (nullptr == m_ValueOrFunctions || 0 == m_ValueOrFunctionNum)
                return GetNullValueOrFunctionPtrRef();
            else
                return m_ValueOrFunctions[m_ValueOrFunctionNum - 1];
        }
        ValueOrFunctionData*& GetFunctionRef(int index)const
        {
            if (nullptr == m_ValueOrFunctions || index < 0 || index >= m_ValueOrFunctionNum || index >= m_MaxValueOrFunctionNum)
                return GetNullValueOrFunctionPtrRef();
            return m_ValueOrFunctions[index];
        }
    public:
        int GetFunctionNum()const { return m_ValueOrFunctionNum; }
        ValueOrFunctionData* GetFunction(int index)const
        {
            if (nullptr == m_ValueOrFunctions || index < 0 || index >= m_ValueOrFunctionNum || index >= m_MaxValueOrFunctionNum)
                return GetNullValueOrFunctionPtrRef();
            return m_ValueOrFunctions[index];
        }
        const char* GetFunctionId(int index)const
        {
            if (0 == m_ValueOrFunctions || index < 0 || index >= m_ValueOrFunctionNum || index >= m_MaxValueOrFunctionNum)
                return "";
            return m_ValueOrFunctions[index]->GetId();
        }
        ValueOrFunctionData* GetFirst()const
        {
            return GetFunction(0);
        }
        ValueOrFunctionData* GetSecond()const
        {
            return GetFunction(1);
        }
        ValueOrFunctionData* GetThird()const
        {
            return GetFunction(2);
        }
        ValueOrFunctionData* GetLast()const
        {
            int num = GetFunctionNum();
            if (num <= 0)
                return GetNullValueOrFunctionPtrRef();
            return GetFunction(num - 1);
        }
    public:
        StatementData(IDslStringAndObjectBuffer& buffer);
        virtual ~StatementData() override
        {
            ReleaseFunctions();
            ReleaseFirstComments(&m_Buffer, m_pCommentsInfo);
            ReleaseLastComments(&m_Buffer, m_pCommentsInfo);
        }
        void InitFunctionsCapacity(int c);
    protected:
        virtual IDslStringAndObjectBuffer* GetBuffer() const override
        {
            return &m_Buffer;
        }
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo() const override
        {
            return m_pCommentsInfo;
        }
    private:
        StatementData(const StatementData&) = delete;
        StatementData(StatementData&& other) noexcept = delete;
        StatementData& operator=(const StatementData&) = delete;
        StatementData& operator=(StatementData&& other) noexcept = delete;
    private:
        void PrepareFunctions();
        void ReleaseFunctions();
    private:
        ValueOrFunctionData*& GetNullValueOrFunctionPtrRef()const;
    private:
        ValueOrFunctionData** m_ValueOrFunctions;
        int m_ValueOrFunctionNum;
        int m_ValueOrFunctionSpace;
        int m_MaxValueOrFunctionNum;
    private:
        IDslStringAndObjectBuffer& m_Buffer;
        SyntaxComponentCommentsInfo* m_pCommentsInfo;
    };

    //In the C++ implementation, DSL memory is expected to be pre-allocated as much as possible.
    //This interface is used to implement pre-allocated memory.
    class IDslStringAndObjectBuffer
    {
    public:
        virtual DslOptions& GetOptions() = 0;
        virtual const DslOptions& GetOptions()const = 0;
    public:
        virtual char* AllocString(int len) = 0;
        virtual char* AllocString(const char* src) = 0;
        virtual char* GetStringBuffer()const = 0;
        virtual char*& GetUnusedStringPtrRef() = 0;
        virtual int GetUnusedStringLength()const = 0;
    public:
        virtual SyntaxComponentCommentsInfo* NewSyntaxComponentCommentsInfo() = 0;
        virtual FunctionCommentsInfo* NewFunctionCommentsInfo() = 0;
    public:
        virtual ValueData* AddNewValueComponent() = 0;
        virtual FunctionData* AddNewFunctionComponent() = 0;
        virtual StatementData* AddNewStatementComponent() = 0;
        virtual int GetUnusedObjectLength()const = 0;
    public:
        virtual void** NewPtrArray(int size) = 0;
        virtual void DeletePtrArray(void** ptr, int size) = 0;
    public:
        virtual void ZeroErrorInfoBuffer() = 0;
        virtual char* GetSingleErrorInfoBuffer(int index) = 0;
        virtual int GetSingleErrorInfoCapacity() = 0;
    public:
        virtual ISyntaxComponent* GetNullSyntaxPtr() = 0;
        virtual FunctionData* GetNullFunctionPtr() = 0;
        virtual FunctionData*& GetNullFunctionPtrRef() = 0;
        virtual ValueOrFunctionData*& GetNullValueOrFunctionPtrRef() = 0;
    public:
        virtual void Reset() = 0;
        virtual ~IDslStringAndObjectBuffer() {}
    };

    /*
    * The actual DSL pre-allocates the buffer. This class needs to be instantiated on the heap
    * (which may cause stack overflow on the stack). The class itself uses Use an array to allocate buffers.
    * The ideal situation is that the memory used by all related classes is pre-allocated.
    */
    template<int StringAndObjectBufferSize = STRING_AND_OBJECT_BUFFER_SIZE,
        int SyntaxComponentAndPtrArrayPoolSize = SYNTAXCOMPONENT_AND_PTR_ARRAY_POOL_SIZE,
        int PtrArrayPoolFreeLinkHeaderSize = PTR_ARRAY_POOL_FREELINK_HEADER_SIZE,
        int MaxErrorInfoNum = MAX_ERROR_INFO_NUM,
        int SingleErrorInfoCapacity = SINGLE_ERROR_INFO_CAPACITY
    >
    class DslStringAndObjectBufferT final : public IDslStringAndObjectBuffer
    {
        struct alignas(4) FreeLinkInfo
        {
            int m_PtrPoolIndex;
            int m_NextFreeLink;
        };
        using SyntaxComponentPtr = ISyntaxComponent*;
    public:
        virtual DslOptions& GetOptions() override { return m_Options; }
        virtual const DslOptions& GetOptions()const override { return m_Options; }
    public:
        virtual char* AllocString(int len) override
        {
            if (len + 1 >= GetUnusedStringLength()) {
                return 0;
            }
            char* p = m_pUnusedStringPtr;
            if (0 != p) {
                m_pUnusedStringPtr[len] = 0;
                m_pUnusedStringPtr += len + 1;
            }
            return p;
        }
        virtual char* AllocString(const char* src) override
        {
            if (0 == src)
                return 0;
            int len = (int)strlen(src);
            char* p = AllocString(len);
            if (0 != p) {
                strcpy_s(p, len + 1, src);
            }
            return p;
        }
        virtual char* GetStringBuffer()const override { return m_pStringBuffer; }
        virtual char*& GetUnusedStringPtrRef() override { return m_pUnusedStringPtr; }
        virtual int GetUnusedStringLength()const override
        {
            MyAssert(m_pUnusedStringRef);
            MyAssert(m_pUnusedObjectPtr);
            return static_cast<int>(m_pUnusedObjectPtr - m_pUnusedStringPtr);
        }
    public:
        virtual SyntaxComponentCommentsInfo* NewSyntaxComponentCommentsInfo() override
        {
            size_t size = sizeof(SyntaxComponentCommentsInfo);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            m_pUnusedObjectPtr -= size;
            void* pMemory = m_pUnusedObjectPtr;
            SyntaxComponentCommentsInfo* p = new(pMemory) SyntaxComponentCommentsInfo();
            ++m_SyntaxComponentCommentsInfoNum;
            return p;
        }
        virtual FunctionCommentsInfo* NewFunctionCommentsInfo() override
        {
            size_t size = sizeof(FunctionCommentsInfo);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            m_pUnusedObjectPtr -= size;
            void* pMemory = m_pUnusedObjectPtr;
            FunctionCommentsInfo* p = new(pMemory) FunctionCommentsInfo();
            ++m_FunctionCommentsInfoNum;
            return p;
        }
    public:
        virtual ValueData* AddNewValueComponent() override
        {
            size_t size = sizeof(ValueData);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            m_pUnusedObjectPtr -= size;
            void* pMemory = m_pUnusedObjectPtr;
            ValueData* p = new(pMemory) ValueData();
            AddSyntaxComponent(p);
            return p;
        }
        virtual FunctionData* AddNewFunctionComponent() override
        {
            size_t size = sizeof(FunctionData);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            m_pUnusedObjectPtr -= size;
            void* pMemory = m_pUnusedObjectPtr;
            FunctionData* p = new(pMemory) FunctionData(*this);
            AddSyntaxComponent(p);
            return p;
        }
        virtual StatementData* AddNewStatementComponent() override
        {
            size_t size = sizeof(StatementData);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            m_pUnusedObjectPtr -= size;
            void* pMemory = m_pUnusedObjectPtr;
            StatementData* p = new(pMemory) StatementData(*this);
            AddSyntaxComponent(p);
            return p;
        }
        virtual int GetUnusedObjectLength()const override
        {
            MyAssert(m_pUnusedStringPtr);
            MyAssert(m_pUnusedObjectRef);
            return static_cast<int>(m_pUnusedObjectPtr - m_pUnusedStringPtr);
        }
    public:
        virtual void** NewPtrArray(int size) override
        {
            if (size<0 || size>PtrArrayPoolFreeLinkHeaderSize)
                return 0;
            int ix = m_PtrFreeLinkHeader[size];
            if (ix > 0) {
                //If there is any in the free linked list, use the data of the free linked list.
                //The free linked list head points to the last element of the linked list. The
                //original linked list head is removed from the linked list and placed in the
                //free linked list of the free linked list block.
                auto& link = *(m_pPtrFreeLink - ix);
                m_PtrFreeLinkHeader[size] = link.m_NextFreeLink;
                if (m_FreedFreeLinkHeader > 0) {
                    link.m_NextFreeLink = m_FreedFreeLinkHeader;
                }
                else {
                    link.m_NextFreeLink = 0;
                }
                m_FreedFreeLinkHeader = ix;
            }
            if (m_SyntaxComponentNum + size > SyntaxComponentAndPtrArrayPoolSize)
                return 0;
            int start = m_SyntaxComponentNum;
            m_SyntaxComponentNum += size;
            return reinterpret_cast<void**>(&(m_SyntaxComponentPool[start]));
        }
        virtual void DeletePtrArray(void** ptr, int size) override
        {
            if (size<0 || size>PtrArrayPoolFreeLinkHeaderSize)
                return;
            //Allocate a new free list block to describe the recycled array and
            //add it to the free list
            int newFreeHeader = 0;
            FreeLinkInfo* p = 0;
            if (m_FreedFreeLinkHeader > 0) {
                newFreeHeader = m_FreedFreeLinkHeader;
                p = m_pPtrFreeLink - m_FreedFreeLinkHeader;
                m_FreedFreeLinkHeader = p->m_NextFreeLink;
            }
            else if (m_FreeLinkNum < static_cast<int>((SyntaxComponentAndPtrArrayPoolSize - m_SyntaxComponentNum)*sizeof(SyntaxComponentPtr)/sizeof(FreeLinkInfo))) {
                ++m_FreeLinkNum;
                newFreeHeader = m_FreeLinkNum;
                p = m_pPtrFreeLink - m_FreeLinkNum;
            }
            else {
                //This block is wasted, and the size of the free list parameters needs to be adjusted.
            }
            if (p) {
                p->m_PtrPoolIndex = static_cast<int>(ptr - reinterpret_cast<void**>(m_SyntaxComponentPool));
                int ix = m_PtrFreeLinkHeader[size];
                if (ix >= 0) {
                    p->m_NextFreeLink = ix;
                }
                else {
                    p->m_NextFreeLink = 0;
                }
                m_PtrFreeLinkHeader[size] = newFreeHeader;
            }
        }
    public:
        virtual void ZeroErrorInfoBuffer() override
        {
            memset(m_ErrorInfo, 0, sizeof(m_ErrorInfo));
        }
        virtual char* GetSingleErrorInfoBuffer(int index) override
        {
            if (index < 0 || index >= MaxErrorInfoNum)
                return nullptr;
            return m_ErrorInfo[index];
        }
        virtual int GetSingleErrorInfoCapacity() override
        {
            return SingleErrorInfoCapacity;
        }
    public:
        virtual StatementData* GetNullSyntaxPtr() override
        {
            return &m_NullSyntax;
        }
        virtual FunctionData* GetNullFunctionPtr() override
        {
            m_NullFunction.GetName().SetInvalid();
            m_NullFunction.SetParamClass(FunctionData::PARAM_CLASS_NOTHING);
            m_NullFunction.ClearParams();
            return &m_NullFunction;
        }
        virtual FunctionData*& GetNullFunctionPtrRef() override
        {
            auto fptr = m_pNullFunction;
            fptr->GetName().SetInvalid();
            fptr->SetParamClass(FunctionData::PARAM_CLASS_NOTHING);
            fptr->ClearParams();
            return m_pNullFunction;
        }
        virtual ValueOrFunctionData*& GetNullValueOrFunctionPtrRef() override
        {
            auto fptr = m_pNullFunction;
            fptr->GetName().SetInvalid();
            fptr->SetParamClass(FunctionData::PARAM_CLASS_NOTHING);
            fptr->ClearParams();
            return m_pNullValueOrFunction;
        }
    public:
        DslStringAndObjectBufferT() :
            m_pStringBuffer(m_StringBuffer),
            m_pUnusedStringPtr(m_StringBuffer),
            m_pUnusedObjectPtr(m_StringBuffer + StringAndObjectBufferSize),
            m_SyntaxComponentNum(0),
            m_SyntaxComponentCommentsInfoNum(0),
            m_FunctionCommentsInfoNum(0),
            m_NullSyntax(*this),
            m_NullFunction(*this),
            m_pNullFunction(&m_NullFunction),
            m_pNullValueOrFunction(&m_NullFunction)
        {
            memset(m_StringBuffer, 0, sizeof(m_StringBuffer));
            memset(m_SyntaxComponentPool, 0, sizeof(m_SyntaxComponentPool));
            m_pPtrFreeLink = reinterpret_cast<FreeLinkInfo*>(m_SyntaxComponentPool + SyntaxComponentAndPtrArrayPoolSize);
            m_FreeLinkNum = 0;
            memset(m_PtrFreeLinkHeader, 0, sizeof(m_PtrFreeLinkHeader));
            m_FreedFreeLinkHeader = 0;
            memset(m_ErrorInfo, 0, sizeof(m_ErrorInfo));
        }
        virtual void Reset() override
        {
            m_SyntaxComponentNum = 0;
            m_SyntaxComponentCommentsInfoNum = 0;
            m_FunctionCommentsInfoNum = 0;
            m_pStringBuffer = m_StringBuffer;
            m_pUnusedStringPtr = m_StringBuffer;
            m_pUnusedObjectPtr = m_StringBuffer + StringAndObjectBufferSize;
            m_pNullFunction = &m_NullFunction;

            memset(m_SyntaxComponentPool, 0, sizeof(SyntaxComponentPtr) * SyntaxComponentAndPtrArrayPoolSize);
            m_pPtrFreeLink = reinterpret_cast<FreeLinkInfo*>(m_SyntaxComponentPool + SyntaxComponentAndPtrArrayPoolSize);
            m_FreeLinkNum = 0;
            memset(m_PtrFreeLinkHeader, 0, sizeof(unsigned int) * PtrArrayPoolFreeLinkHeaderSize);
            m_FreedFreeLinkHeader = 0;
        }
    private:
        void AddSyntaxComponent(ISyntaxComponent* p)
        {
            if (m_SyntaxComponentNum >= SyntaxComponentAndPtrArrayPoolSize)
                return;
            m_SyntaxComponentPool[m_SyntaxComponentNum] = p;
            ++m_SyntaxComponentNum;
        }
    private:
        DslStringAndObjectBufferT(const DslStringAndObjectBufferT&) = delete;
        DslStringAndObjectBufferT(DslStringAndObjectBufferT&& other) noexcept = delete;
        DslStringAndObjectBufferT& operator=(const DslStringAndObjectBufferT&) = delete;
        DslStringAndObjectBufferT& operator=(DslStringAndObjectBufferT&& other) noexcept = delete;
    private:
        DslOptions m_Options;
    private:
        //Strings and objects share a buffer. Strings grow in the forward direction and objects
        //in the reverse direction.
        char m_StringBuffer[StringAndObjectBufferSize];
        char* m_pStringBuffer;
        char* m_pUnusedStringPtr;
        char* m_pUnusedObjectPtr;
        int m_SyntaxComponentNum;
        int m_SyntaxComponentCommentsInfoNum;
        int m_FunctionCommentsInfoNum;
    private:
        //The syntax component pointer, pointer array and free block share a buffer. The syntax
        //component pointer and pointer array grow in the forward direction, and the free block
        //grows in the opposite direction. The data here is usually word-aligned, so it is not
        //considered to be shared with string and object buffers.
        SyntaxComponentPtr m_SyntaxComponentPool[SyntaxComponentAndPtrArrayPoolSize];//Array of syntax component pointers,
            //the total number is equivalent to the number of all syntax components in a dsl file Pointer array buffer,
            //mainly used to allocate syntax component pointer array, PtrPoolSize is equivalent to the number of all
            //syntax components in a dsl file
        FreeLinkInfo* m_pPtrFreeLink;//The lower 32 bits correspond to the index of m_PtrPool, and the upper 32 bits are
            //the index of the next free block. The number of free blocks. For DSL file parsing, this value should
            //theoretically be very low, approximately equivalent to (the number of times the syntax array is expanded
            //- the number of times the new syntax reuses the array)
        int m_FreeLinkNum;
    private:
        int m_PtrFreeLinkHeader[PtrArrayPoolFreeLinkHeaderSize];//The position of the free linked list head of each size
            //indexed by the array size. The size of this array is the maximum value of each syntax component array allowed.
            //The number of statement functions, number of parameters, number of single file DSL, etc. are limited by this.
        int m_FreedFreeLinkHeader;//The head of the free free block list
    private:
        char m_ErrorInfo[MaxErrorInfoNum][SingleErrorInfoCapacity];
    private:
        StatementData m_NullSyntax;
        FunctionData m_NullFunction;
        FunctionData* m_pNullFunction;
        ValueOrFunctionData* m_pNullValueOrFunction;
    };

    class DslTokenApi final
    {
    public:
        char* getCurToken() const;
        char* getLastToken() const;
        int getLineNumber() const;
        int getLastLineNumber() const;
        void setCurToken(char* tok)const;
        void setLastToken(char* tok)const;
        bool enqueueToken(char* tok, short val, int line)const;
        char curChar()const;
        char nextChar()const;
        char peekChar(int ix)const;
        char peekNextValidChar(int beginIx)const;
        char peekNextValidChar(int beginIx, int& index)const;
        void getOperatorToken();
        short getOperatorTokenValue()const;
        int isNotIdentifier(char c)const;
        int isNotIdentifierAndBeginParentheses(char c)const;
        int isNotIdentifierAndNumberAndEndParentheses(char c)const;
        int isWhiteSpace(char c) const;
        int isDelimiter(char c) const;
        int isBeginParentheses(char c) const;
        int isEndParentheses(char c) const;
        int isOperator(char c) const;
        int isQuote(char c) const;
        int isSpecialChar(char c) const;
    public:
        inline DslTokenApi(SlkToken* p) :m_Impl(p) {}
    private:
        DslTokenApi(const DslTokenApi& other) = delete;
        DslTokenApi(DslTokenApi&& other) noexcept = delete;
        DslTokenApi& operator=(const DslTokenApi& other) = delete;
        DslTokenApi& operator=(DslTokenApi&& other) noexcept = delete;
    private:
        SlkToken* m_Impl;
    public:
        static int myisdigit(char c, int isHex, int includeEPart, int includeAddSub);
        static int myisdigit(char c, int isHex);
        static int mychar2int(char c);
    };
    class DslActionApi final
    {
    public:
        void markSeparator()const;
        void endStatement()const;
        void buildOperator()const;
        void buildNullableOperator()const;
        void buildFirstTernaryOperator()const;
        void buildSecondTernaryOperator()const;
        void beginStatement()const;
        void addFunction()const;
        void setFunctionId()const;
        void markParenthesesParam()const;
        void markParenthesesParamEnd()const;
        void buildHighOrderFunction()const;
        void markBracketParam()const;
        void markBracketParamEnd()const;
        void markStatement()const;
        void markStatementEnd()const;
        void markExternScript()const;
        void markBracketColonParam()const;
        void markBracketColonParamEnd()const;
        void markParenthesesColonParam()const;
        void markParenthesesColonParamEnd()const;
        void markAngleBracketColonParam()const;
        void markAngleBracketColonParamEnd()const;
        void markBracePercentParam()const;
        void markBracePercentParamEnd()const;
        void markBracketPercentParam()const;
        void markBracketPercentParamEnd()const;
        void markParenthesesPercentParam()const;
        void markParenthesesPercentParamEnd()const;
        void markAngleBracketPercentParam()const;
        void markAngleBracketPercentParamEnd()const;
        void markColonColonParam()const;
        void setExternScript()const;
        void markPeriodParam()const;
        void markPointerParam()const;
        void markPeriodStarParam()const;
        void markPointerStarParam()const;
    public:
        void push(char* token, int type)const;
        StatementData* getCurStatement()const;
        FunctionData* getLastFunction()const;
        void setLastFunction(FunctionData* p)const;
        int peekPairTypeStack()const;
        int peekPairTypeStack(uint32_t& tag)const;
        int getPairTypeStackSize()const;
        int peekPairTypeStack(int ix)const;
        int peekPairTypeStack(int ix, uint32_t& tag)const;
    public:
        inline DslActionApi() :m_Impl(0) {}
        inline void SetImpl(ActionForSourceCodeScript* p) { m_Impl = p; }
    private:
        DslActionApi(const DslActionApi& other) = delete;
        DslActionApi(DslActionApi&& other) noexcept = delete;
        DslActionApi& operator=(const DslActionApi& other) = delete;
        DslActionApi& operator=(DslActionApi&& other) noexcept = delete;
    private:
        ActionForSourceCodeScript* m_Impl;
    };
    class IScriptSource;
    class DslFile final
    {
        using SyntaxComponentPtr = ISyntaxComponent*;
        using NameTags = std::unordered_map<std::string, uint32_t>;
    public:
        using TokenCanEatCharDelegation = Delegation<bool(const char*, int, char)>;
        using GetTokenDelegation = Delegation<bool(const DslActionApi&, const DslTokenApi&, char*&, short&, int&)>;
        using BeforeAddFunctionDelegation = Delegation<bool(const DslActionApi&, StatementData*)>;
        using AddFunctionDelegation = Delegation<bool(const DslActionApi&, StatementData*, FunctionData*)>;
        using BeforeEndStatementDelegation = Delegation<bool(const DslActionApi&, StatementData*)>;
        using EndStatementDelegation = Delegation<bool(const DslActionApi&, StatementData*&)>;
        using BeforeBuildOperatorDelegation = Delegation<bool(const DslActionApi&, int, const char*, StatementData*)>;
        using BuildOperatorDelegation = Delegation<bool(const DslActionApi&, int, const char*, StatementData*&)>;
        using SetFunctionIdDelegation = Delegation<bool(const DslActionApi&, const char*, StatementData*, FunctionData*)>;
        using BeforeBuildHighOrderDelegation = Delegation<bool(const DslActionApi&, StatementData*, FunctionData*)>;
        using BuildHighOrderDelegation = Delegation<bool(const DslActionApi&, StatementData*, FunctionData*)>;
    public:
        int GetDslInfoNum()const { return m_DslInfoNum; }
        ISyntaxComponent* GetDslInfo(int index)const
        {
            if (index < 0 || index >= m_DslInfoNum)
                return nullptr;
            return m_DslInfos[index];
        }
        void WriteToFile(FILE* fp, int indent) const;
    public:
        void AddDslInfo(ISyntaxComponent* p);
    public:
        DslFile(IDslStringAndObjectBuffer& buffer);
        ~DslFile();
        void Reset();
        void Parse(const char* buf);
        void Parse(IScriptSource& source);
    public:
        void ParseGpp(const char* buf);
        void ParseGpp(const char* buf, const char* beginDelim, const char* endDelim);
        void ParseGpp(const char* buf, const char* beginDelim, const char* endDelim, char* gppBuf, int& len);
    public:
        void LoadBinaryCode(const char* buffer, int bufferSize, std::vector<const char*>& reuseKeyBuffer, std::vector<const char*>& reuseIdBuffer);
        void SaveBinaryFile(FILE* fp) const;
    public:
        NameTags& NameTagsRef() { return m_NameTags; }
        const NameTags& NameTagsRef()const { return m_NameTags; }
    public:
        void SetNullableSyntax(bool enabled);
        void SetStringDelimiter(const char* begin, const char* end);
        void SetScriptDelimiter(const char* begin, const char* end);
    public:
        bool IsNullableSyntaxEnabled()const { return m_NullableSyntaxEnabled; }
        const char* GetStringBeginDelimiter()const { return m_StringBeginDelimiter; }
        const char* GetStringEndDelimiter()const { return m_StringEndDelimiter; }
        const char* GetScriptBeginDelimiter()const { return m_ScriptBeginDelimiter; }
        const char* GetScriptEndDelimiter()const { return m_ScriptEndDelimiter; }
    public:
        TokenCanEatCharDelegation OnTokenCanEatChar;
        GetTokenDelegation OnGetToken;
        BeforeAddFunctionDelegation OnBeforeAddFunction;
        AddFunctionDelegation OnAddFunction;
        BeforeEndStatementDelegation OnBeforeEndStatement;
        EndStatementDelegation OnEndStatement;
        BeforeBuildOperatorDelegation OnBeforeBuildOperator;
        BuildOperatorDelegation OnBuildOperator;
        SetFunctionIdDelegation OnSetFunctionId;
        BeforeBuildHighOrderDelegation OnBeforeBuildHighOrder;
        BuildHighOrderDelegation OnBuildHighOrder;
    private:
        DslFile(const DslFile& other) = delete;
        DslFile(DslFile&& other) noexcept = delete;
        DslFile& operator=(const DslFile& other) = delete;
        DslFile& operator=(DslFile&& other) noexcept = delete;
    private:
        void Init();
        void Release();
    public:
        void EnableDebugInfo() { m_IsDebugInfoEnable = TRUE; }
        void DisableDebugInfo() { m_IsDebugInfoEnable = FALSE; }
        int IsDebugInfoEnable()const { return m_IsDebugInfoEnable; }
    public:
        void ClearErrorInfo();
        void AddError(const char* error);
        int HasError()const { return m_HasError; }
        int GetErrorNum()const { return m_ErrorNum; }
        const char* GetErrorInfo(int index) const
        {
            if (index < 0 || index >= m_ErrorNum)
                return "";
            auto* ptr = m_Buffer.GetSingleErrorInfoBuffer(index);
            if (!ptr)
                return "";
            return ptr;
        }
        char* NewErrorInfo()
        {
            m_HasError = TRUE;
            auto* ptr = m_Buffer.GetSingleErrorInfoBuffer(m_ErrorNum);
            if (ptr) {
                ++m_ErrorNum;
                return ptr;
            }
            else {
                return nullptr;
            }
        }
        int GetSingleErrorInfoCapacity()const { return m_Buffer.GetSingleErrorInfoCapacity(); }
    public:
        char* AllocString(int len) const { return m_Buffer.AllocString(len); }
        char* AllocString(const char* src) const { return m_Buffer.AllocString(src); }
        char* GetStringBuffer() const { return m_Buffer.GetStringBuffer(); }
        char*& GetUnusedStringPtrRef() const { return m_Buffer.GetUnusedStringPtrRef(); }
        int GetUnusedStringLength() const { return m_Buffer.GetUnusedStringLength(); }
    public:
        ValueData* AddNewValueComponent() const { return m_Buffer.AddNewValueComponent(); }
        FunctionData* AddNewFunctionComponent() const { return m_Buffer.AddNewFunctionComponent(); }
        StatementData* AddNewStatementComponent() const { return m_Buffer.AddNewStatementComponent(); }
    public:
        FunctionData* GetNullFunctionPtr() { return m_Buffer.GetNullFunctionPtr(); }
    private:
        void PrepareDslInfos();
        void ReleaseDslInfos();
    private:
        IDslStringAndObjectBuffer& m_Buffer;
    private:
        NameTags m_NameTags;
        SyntaxComponentPtr* m_DslInfos;
        int m_DslInfoNum;
        int m_DslInfoSpace;
        int m_MaxDslInfoNum;
    private:
        bool m_NullableSyntaxEnabled;
        const char* m_ScriptBeginDelimiter;
        const char* m_ScriptEndDelimiter;
        const char* m_StringBeginDelimiter;
        const char* m_StringEndDelimiter;
    private:
        int m_IsDebugInfoEnable;
    private:
        int	m_HasError;
        int m_ErrorNum;
    public:
        static bool Mac2Unix(char* buf, int len);
    };

    class IScriptSource
    {
    public:
        virtual ~IScriptSource() {}
    public:
        class Iterator
        {
        public:
            const char& operator * () const
            {
                return Peek(0);
            }
            Iterator& operator ++ ()
            {
                Advance();
                return *this;
            }
            const Iterator operator ++ (int)
            {
                Iterator it = *this;
                ++(*this);
                return it;
            }
            const Iterator operator + (int val) const
            {
                Iterator it = *this;
                for (int ix = 0; ix < val; ++ix)
                    it.Advance();
                return it;
            }
            int Load()
            {
                if (nullptr != m_pSource) {
                    int r = m_pSource->Load();
                    if (r) {
                        *this = m_pSource->GetIterator();
                    }
                    return r;
                }
                else {
                    return FALSE;
                }
            }
            const char* GetBuffer()const
            {
                return m_pSource->GetBuffer();
            }
            const char* GetLeft()const
            {
                return m_Iterator;
            }
        public:
            bool operator ==(const Iterator& other) const
            {
                return m_pSource == other.m_pSource && m_Iterator == other.m_Iterator && m_EndIterator == other.m_EndIterator;
            }
            bool operator !=(const Iterator& other) const
            {
                return !(operator ==(other));
            }
        public:
            Iterator() :m_pSource(nullptr), m_Iterator(""), m_EndIterator(m_Iterator)
            {
            }
            explicit Iterator(IScriptSource& source) :m_pSource(&source)
            {
                const char* p = m_pSource->GetBuffer();
                if (0 == p) {
                    m_Iterator = "";
                    m_EndIterator = m_Iterator;
                }
                else {
                    m_Iterator = p;
                    m_EndIterator = m_Iterator + strlen(p);
                }
            }
            Iterator(const Iterator& other)
            {
                CopyFrom(other);
            }
            Iterator& operator=(const Iterator& other)
            {
                if (this == &other)
                    return *this;
                CopyFrom(other);
                return *this;
            }
        private:
            const char& Peek(int index)const
            {
                if (m_Iterator + index < m_EndIterator)
                    return *(m_Iterator + index);
                else
                    return *m_EndIterator;
            }
            void Advance()
            {
                if (m_Iterator < m_EndIterator)
                    ++m_Iterator;
            }
            void CopyFrom(const Iterator& other)
            {
                m_pSource = other.m_pSource;
                m_Iterator = other.m_Iterator;
                m_EndIterator = other.m_EndIterator;
            }
        private:
            IScriptSource* m_pSource;
            const char* m_Iterator;
            const char* m_EndIterator;
        };
        friend class Iterator;
    public:
        Iterator GetIterator()
        {
            return Iterator(*this);
        }
    protected:
        virtual int Load() = 0;
        virtual const char* GetBuffer()const = 0;
    };
}

#endif
