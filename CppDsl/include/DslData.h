/*****************************************************************************

DslData.h

******************************************************************************/

#ifndef _DSL_DATA_H
#define _DSL_DATA_H

#include "BaseType.h"
#include "Delegation.h"
#include "DslCommon.h"
#include <new>
#include <string>
#include <vector>

namespace DslData
{
    // The main design of DslParser considers the use of fixed-size memory to parse dsl files, using continuous memory to avoid memory fragmentation, and memory can be fully reused.
    // Here is the result data parsed for external use. Considering the practical convenience, dynamic memory management and more stl objects are used here
    // The classes presented here are essentially parallel to the classes in DslParser
    struct DelimiterInfo final
    {
        const std::string ScriptBeginDelimiter;
        const std::string ScriptEndDelimiter;
        const std::string StringBeginDelimiter;
        const std::string StringEndDelimiter;

        DelimiterInfo()
            :ScriptBeginDelimiter("{:"), ScriptEndDelimiter(":}"), StringBeginDelimiter("\""), StringEndDelimiter("\"")
        {}
        DelimiterInfo(const std::string& strBeginDelim, const std::string& strEndDelim, const std::string& scpBeginDelim, const std::string& scpEndDelim)
            :ScriptBeginDelimiter(scpBeginDelim), ScriptEndDelimiter(scpEndDelim), StringBeginDelimiter(strBeginDelim), StringEndDelimiter(strEndDelim)
        {}
    };

    //These two structures are used for pure data and do not need virtual destruction
    struct SyntaxComponentCommentsInfo
    {
        bool m_FirstCommentOnNewLine;
        bool m_LastCommentOnNewLine;
        std::vector<std::string> m_FirstComments;
        std::vector<std::string> m_LastComments;

        SyntaxComponentCommentsInfo() :m_FirstCommentOnNewLine(false), m_LastCommentOnNewLine(false), m_FirstComments(0), m_LastComments(0)
        {}
    };
    struct FunctionCommentsInfo : public SyntaxComponentCommentsInfo
    {
        std::vector<std::string> m_Comments;

        FunctionCommentsInfo() :SyntaxComponentCommentsInfo(), m_Comments(0)
        {}
    };

    class ISyntaxComponent : public IDslSyntaxCommon
    {
    public:
        ISyntaxComponent(int syntaxType);
        virtual ~ISyntaxComponent()override;
    public:
        virtual bool IsValid() const = 0;
        virtual const std::string& GetId() const = 0;
        virtual int GetIdType() const = 0;
        virtual int GetLine() const = 0;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const = 0;
        virtual bool HaveId() const = 0;
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
        void AddFirstComment(const std::string& cmt)
        {
            std::string str = cmt;
            AddFirstComment(std::move(str));
        }
        void AddFirstComment(std::string&& cmt)
        {
            if (nullptr == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_FirstComments.push_back(std::move(cmt));
        }
        void RemoveFirstComment(int index)
        {
            if (nullptr == GetCommentsInfo())
                return;
            if (index >= 0 && index < static_cast<int>(GetCommentsInfo()->m_FirstComments.size())) {
                auto it = GetCommentsInfo()->m_FirstComments.begin();
                std::advance(it, index);
                GetCommentsInfo()->m_FirstComments.erase(it);
            }
        }
        void ClearFirstComments()
        {
            if (nullptr == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_FirstComments.clear();
        }
        int GetFirstCommentNum() const
        {
            if (nullptr == GetCommentsInfo())
                return 0;
            return static_cast<int>(GetCommentsInfo()->m_FirstComments.size());
        }
        const std::string& GetFirstComment(int index) const
        {
            if (0 != GetCommentsInfo() && index >= 0 && index < static_cast<int>(GetCommentsInfo()->m_FirstComments.size())) {
                return GetCommentsInfo()->m_FirstComments[index];
            }
            else {
                return EmptyString();
            }
        }
        bool IsFirstCommentOnNewLine() const
        {
            if (nullptr == GetCommentsInfo())
                return false;
            return GetCommentsInfo()->m_FirstCommentOnNewLine;
        }
        void SetFirstCommentOnNewLine(bool v)
        {
            if (nullptr == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_FirstCommentOnNewLine = v;
        }
        void AddLastComment(const std::string& cmt)
        {
            std::string str = cmt;
            AddLastComment(std::move(str));
        }
        void AddLastComment(std::string&& cmt)
        {
            if (nullptr == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_LastComments.push_back(std::move(cmt));
        }
        void RemoveLastComment(int index)
        {
            if (0 != GetCommentsInfo() && index >= 0 && index < static_cast<int>(GetCommentsInfo()->m_LastComments.size())) {
                auto it = GetCommentsInfo()->m_LastComments.begin();
                std::advance(it, index);
                GetCommentsInfo()->m_LastComments.erase(it);
            }
        }
        void ClearLastComments()
        {
            if (nullptr == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_LastComments.clear();
        }
        int GetLastCommentNum() const
        {
            if (nullptr == GetCommentsInfo())
                return 0;
            return static_cast<int>(GetCommentsInfo()->m_LastComments.size());
        }
        const std::string& GetLastComment(int index) const
        {
            if (0 != GetCommentsInfo() && index >= 0 && index < static_cast<int>(GetCommentsInfo()->m_LastComments.size())) {
                return GetCommentsInfo()->m_LastComments[index];
            }
            else {
                return EmptyString();
            }
        }
        bool IsLastCommentOnNewLine() const
        {
            if (nullptr == GetCommentsInfo())
                return false;
            return GetCommentsInfo()->m_LastCommentOnNewLine;
        }
        void SetLastCommentOnNewLine(bool v)
        {
            if (nullptr == GetCommentsInfo())
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
            if (nullptr == GetCommentsInfo() || nullptr == other.GetCommentsInfo())
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
            if (nullptr == GetCommentsInfo() || nullptr == other.GetCommentsInfo())
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
        void ReleaseFirstComments(SyntaxComponentCommentsInfo* pCommentsInfo);
        void ReleaseLastComments(SyntaxComponentCommentsInfo* pCommentsInfo);
    protected:
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo() const { return nullptr; }
    private:
        int m_SyntaxType;
        int m_Separator;
    public:
        static const std::string& EmptyString()
        {
            static std::string s_Str;
            return s_Str;
        }
    };

    class FunctionData;
    class ValueData;
    class ValueOrFunctionData : public ISyntaxComponent
    {
    public:
        ValueOrFunctionData(int syntaxType) :ISyntaxComponent(syntaxType)
        {}
    public:
        bool IsValue()const
        {
            return GetSyntaxType() == ISyntaxComponent::TYPE_VALUE;
        }
        bool IsFunction()const
        {
            return GetSyntaxType() == ISyntaxComponent::TYPE_FUNCTION;
        }
        inline const ValueData* AsValue()const;
        inline ValueData* AsValue();
        inline const FunctionData* AsFunction()const;
        inline FunctionData* AsFunction();
    };

    class ValueData final : public ValueOrFunctionData
    {
    public:
        ValueData() :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_IDENTIFIER), m_StringVal(), m_FunctionVal(nullptr), m_Line(0) {}
        explicit ValueData(const std::string& val) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_STRING), m_StringVal(val), m_FunctionVal(nullptr), m_Line(0) {}
        explicit ValueData(const std::string& val, int type) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_StringVal(val), m_FunctionVal(nullptr), m_Line(0) {}
        explicit ValueData(std::string&& val) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_STRING), m_StringVal(std::move(val)), m_FunctionVal(nullptr), m_Line(0) {}
        explicit ValueData(std::string&& val, int type) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_StringVal(std::move(val)), m_FunctionVal(nullptr), m_Line(0) {}
        ValueData(const ValueData& other) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_IDENTIFIER), m_StringVal(), m_FunctionVal(nullptr), m_Line(0)
        {
            ISyntaxComponent::CopyFrom(other);
            CopyFrom(other);
        }
        ValueData(ValueData&& other) noexcept :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_IDENTIFIER), m_StringVal(), m_FunctionVal(nullptr), m_Line(0)
        {
            std::swap(*this, other);
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
            std::swap(*this, other);
            return *this;
        }
        virtual ~ValueData() override;

        virtual bool IsValid()const override;
        virtual int GetIdType()const override;
        virtual const std::string& GetId()const override;
        virtual int GetLine()const override;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual bool HaveId()const override;

        FunctionData* GetFunction()const { return m_FunctionVal; }

        bool IsNum()const { return (m_Type == VALUE_TYPE_NUM); }
        bool IsString()const { return (m_Type == VALUE_TYPE_STRING); }
        bool IsDollarString()const { return (m_Type == VALUE_TYPE_DOLLAR_STRING); }
        bool IsIdentifier()const { return (m_Type == VALUE_TYPE_IDENTIFIER && !m_StringVal.empty()); }
        bool IsFunction()const { return (m_Type == VALUE_TYPE_FUNCTION); }

        void SetInvalid()
        {
            Release();
            m_Type = VALUE_TYPE_IDENTIFIER;
            m_StringVal.clear();
        }
        void SetNumber(const std::string& str)
        {
            std::string tstr = str;
            SetNumber(std::move(tstr));
        }
        void SetString(const std::string& str)
        {
            std::string tstr = str;
            SetString(std::move(tstr));
        }
        void SetDollarString(const std::string& str)
        {
            std::string tstr = str;
            SetDollarString(std::move(tstr));
        }
        void SetIdentifier(const std::string& name)
        {
            std::string tstr = name;
            SetIdentifier(std::move(tstr));
        }
        void SetTypeAndId(int type, const std::string& id)
        {
            std::string tstr = id;
            SetTypeAndId(type, std::move(tstr));
        }
        void SetNumber(std::string&& str)
        {
            Release();
            m_Type = VALUE_TYPE_NUM;
            m_StringVal = std::move(str);
        }
        void SetString(std::string&& str)
        {
            Release();
            m_Type = VALUE_TYPE_STRING;
            m_StringVal = std::move(str);
        }
        void SetDollarString(std::string&& str)
        {
            Release();
            m_Type = VALUE_TYPE_DOLLAR_STRING;
            m_StringVal = std::move(str);
        }
        void SetIdentifier(std::string&& name)
        {
            Release();
            m_Type = VALUE_TYPE_IDENTIFIER;
            m_StringVal = std::move(name);
        }
        void SetTypeAndId(int type, std::string&& id)
        {
            Release();
            m_Type = type;
            m_StringVal = std::move(id);
        }
        void SetType(int type)
        {
            m_Type = type;
        }
        void SetLine(int line)
        {
            m_Line = line;
        }
        FunctionData* SetFunction();
        FunctionData* SetFunctionCopyFrom(const FunctionData& other);
    private:
        void CopyFrom(const ValueData& other);
        void Release();
    private:
        int m_Type;
        std::string m_StringVal;
        FunctionData* m_FunctionVal;
        int m_Line;
    };

    class StatementData;
    class FunctionData final : public ValueOrFunctionData
    {
        using SyntaxComponentPtr = ISyntaxComponent*;
    public:
        virtual bool IsValid()const override
        {
            if (m_Name.IsValid())
                return true;
            else if (HaveParamOrStatement())
                return true;
            else
                return false;
        }
        virtual int GetIdType()const override { return m_Name.GetIdType(); }
        virtual const std::string& GetId()const override { return m_Name.GetId(); }
        virtual int GetLine()const override;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual bool HaveId()const override { return m_Name.HaveId(); }
    public:
        void SetName(const ValueData& val) { m_Name = val; }
        ValueData& GetName() { return m_Name; }
        void ClearParams();
        ValueData* AddValueParam();
        FunctionData* AddFunctionParam();
        StatementData* AddStatementParam();
        ISyntaxComponent* AddParamCopyFrom(const ISyntaxComponent& other);
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
        bool HaveParamClassInfixFlag()const
        {
            int infix = (m_ParamClass & (int)PARAM_CLASS_WRAP_INFIX_CALL_MASK);
            return infix == (int)PARAM_CLASS_WRAP_INFIX_CALL_MASK;
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
        bool IsOperatorParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_OPERATOR;
        }
        bool IsQuestionNullableOperatorParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_QUESTION_NULLABLE_OPERATOR;
        }
        bool IsExclamationNullableOperatorParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR;
        }
        bool IsTernaryOperatorParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_TERNARY_OPERATOR;
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
        bool IsMemberParamClass()const
        {
            int paramClass = GetParamClassUnmasked();
            return (paramClass == (int)PARAM_CLASS_COLON_COLON ||
                paramClass == (int)PARAM_CLASS_PERIOD ||
                paramClass == (int)PARAM_CLASS_PERIOD_STAR ||
                paramClass == (int)PARAM_CLASS_POINTER ||
                paramClass == (int)PARAM_CLASS_POINTER_STAR);
        }
        bool HaveParamOrStatement()const { return m_ParamClass != PARAM_CLASS_NOTHING; }
        bool HaveParam()const { return HaveParamOrStatement() && !HaveStatement() && !HaveExternScript(); }
        bool HaveStatement()const { return m_ParamClass == PARAM_CLASS_STATEMENT; }
        bool HaveExternScript()const { return m_ParamClass == PARAM_CLASS_EXTERN_SCRIPT; }
        bool IsHighOrder()const { return m_Name.IsFunction(); }
        FunctionData& GetLowerOrderFunction()const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr) {
                return *fptr;
            }
            else {
                return GetNullFunction();
            }
        }
        const FunctionData& GetThisOrLowerOrderCall()const
        {
            if (HaveParam()) {
                return *this;
            }
            else if (HaveLowerOrderParam()) {
                return *m_Name.GetFunction();
            }
            else {
                return GetNullFunction();
            }
        }
        FunctionData& GetThisOrLowerOrderCall()
        {
            if (HaveParam()) {
                return *this;
            }
            else if (HaveLowerOrderParam()) {
                return *m_Name.GetFunction();
            }
            else {
                return GetNullFunction();
            }
        }
        const FunctionData& GetThisOrLowerOrderBody()const
        {
            if (HaveStatement()) {
                return *this;
            }
            else if (HaveLowerOrderStatement()) {
                return *m_Name.GetFunction();
            }
            else {
                return GetNullFunction();
            }
        }
        FunctionData& GetThisOrLowerOrderBody()
        {
            if (HaveStatement()) {
                return *this;
            }
            else if (HaveLowerOrderStatement()) {
                return *m_Name.GetFunction();
            }
            else {
                return GetNullFunction();
            }
        }
        const FunctionData& GetThisOrLowerOrderScript()const
        {
            if (HaveExternScript()) {
                return *this;
            }
            else if (HaveLowerOrderExternScript()) {
                return *m_Name.GetFunction();
            }
            else {
                return GetNullFunction();
            }
        }
        FunctionData& GetThisOrLowerOrderScript()
        {
            if (HaveExternScript()) {
                return *this;
            }
            else if (HaveLowerOrderExternScript()) {
                return *m_Name.GetFunction();
            }
            else {
                return GetNullFunction();
            }
        }
        bool HaveLowerOrderParam()const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveParam())
                return true;
            else
                return false;
        }
        bool HaveLowerOrderStatement()const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveStatement())
                return true;
            else
                return false;
        }
        int HaveLowerOrderExternScript()const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveExternScript())
                return true;
            else
                return false;
        }
    public:
        const ValueData& GetName()const { return m_Name; }
        int GetParamNum()const { return static_cast<int>(m_Params.size()); }
        ISyntaxComponent* GetParam(int index)const
        {
            if (index < 0 || index >= static_cast<int>(m_Params.size()))
                return &GetNullSyntax();
            return m_Params[index];
        }
        const std::string& GetParamId(int index)const
        {
            if (index < 0 || index >= static_cast<int>(m_Params.size()) || nullptr == m_Params[index])
                return ISyntaxComponent::EmptyString();
            return m_Params[index]->GetId();
        }
    public:
        void AddComment(const std::string& cmt)
        {
            std::string str = cmt;
            AddComment(std::move(str));
        }
        void AddComment(std::string&& cmt)
        {
            auto p = m_pCommentsInfo;
            if (nullptr == p)
                return;
            p->m_Comments.push_back(std::move(cmt));
        }
        void RemoveComment(int index)
        {
            auto p = m_pCommentsInfo;
            if (nullptr == p)
                return;
            if (index >= 0 && index < static_cast<int>(p->m_Comments.size())) {
                auto it = p->m_Comments.begin();
                std::advance(it, index);
                p->m_Comments.erase(it);
            }
        }
        void ClearComments()
        {
            auto p = m_pCommentsInfo;
            if (nullptr == p)
                return;
            p->m_Comments.clear();
        }
        int GetCommentNum() const
        {
            auto p = m_pCommentsInfo;
            if (nullptr == p)
                return 0;
            return static_cast<int>(p->m_Comments.size());
        }
        const std::string& GetComment(int index) const
        {
            auto p = m_pCommentsInfo;
            if (nullptr == p)
                return ISyntaxComponent::EmptyString();
            if (index >= 0 && index < static_cast<int>(p->m_Comments.size())) {
                return p->m_Comments[index];
            }
            else {
                return ISyntaxComponent::EmptyString();
            }
        }
    public:
        FunctionData();
        virtual ~FunctionData()override;
        void CopyFrom(const FunctionData& other);
        void InitParamsCapacity(int v);
    protected:
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo() const override
        {
            return m_pCommentsInfo;
        }
    private:
        FunctionData(const FunctionData&) = delete;
        FunctionData(FunctionData&&) noexcept = delete;
        FunctionData operator=(const FunctionData&) = delete;
        FunctionData operator=(FunctionData&&) noexcept = delete;
    private:
        void ReleaseParams();
        void ReleaseComments();
    private:
        ISyntaxComponent& GetNullSyntax()const;
        FunctionData& GetNullFunction()const;
    private:
        ValueData m_Name;
        std::vector<SyntaxComponentPtr> m_Params;
        int m_ParamClass;
    private:
        FunctionCommentsInfo* m_pCommentsInfo;
    };

    inline const ValueData* ValueOrFunctionData::AsValue()const
    {
        if (IsValue())
            return static_cast<const ValueData*>(this);
        else
            return nullptr;
    }
    inline ValueData* ValueOrFunctionData::AsValue()
    {
        if (IsValue())
            return static_cast<ValueData*>(this);
        else
            return nullptr;
    }
    inline const FunctionData* ValueOrFunctionData::AsFunction()const
    {
        if (IsFunction())
            return static_cast<const FunctionData*>(this);
        else
            return nullptr;
    }
    inline FunctionData* ValueOrFunctionData::AsFunction()
    {
        if (IsFunction())
            return static_cast<FunctionData*>(this);
        else
            return nullptr;
    }

    /* Note: Why StatementData members do not use ISyntaxComponent[] instead of FunctionData[]
     * 1. While syntactically FunctionData here can degenerate to ValueData, it cannot be StatementData and is thus not conceptually equivalent to ISyntaxComponent
     * 2. FunctionData should be designed with degradation in mind and take up as little extra space as possible in degenerate cases
     */
    class StatementData final : public ISyntaxComponent
    {
    public:
        virtual bool IsValid()const override
        {
            if (m_ValueOrFunctions.size() > 0 && m_ValueOrFunctions[0]->IsValid())
                return true;
            else
                return false;
        }
        virtual int GetIdType()const override
        {
            int type = ValueData::VALUE_TYPE_IDENTIFIER;
            if (IsValid()) {
                type = m_ValueOrFunctions[0]->GetIdType();
            }
            return type;
        }
        virtual const std::string& GetId()const override
        {
            if (IsValid()) {
                return m_ValueOrFunctions[0]->GetId();
            }
            return ISyntaxComponent::EmptyString();
        }
        virtual int GetLine()const override;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual bool HaveId() const override
        {
            if (0 == static_cast<int>(m_ValueOrFunctions.size()))
                return false;
            else
                return m_ValueOrFunctions[static_cast<int>(m_ValueOrFunctions.size()) - 1]->HaveId();
        }
    public:
        void ClearFunctions();
        ValueData* AddValue();
        FunctionData* AddFunction();
        ValueOrFunctionData* AddValueOrFunctionCopyFrom(const ValueOrFunctionData& other);
    public:
        int GetFunctionNum()const { return static_cast<int>(m_ValueOrFunctions.size()); }
        ValueOrFunctionData* GetFunction(int index)const
        {
            if (index < 0 || index >= static_cast<int>(m_ValueOrFunctions.size()))
                return &GetNullValueOrFunction();
            return m_ValueOrFunctions[index];
        }
        const std::string& GetFunctionId(int index)const
        {
            if (index < 0 || index >= static_cast<int>(m_ValueOrFunctions.size()) || nullptr == m_ValueOrFunctions[index])
                return ISyntaxComponent::EmptyString();
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
                return &GetNullValueOrFunction();
            return GetFunction(num - 1);
        }
    public:
        StatementData();
        virtual ~StatementData() override;
        void CopyFrom(const StatementData& other);
        void InitFunctionsCapacity(int v);
    protected:
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo() const override
        {
            return m_pCommentsInfo;
        }
    private:
        StatementData(const StatementData&) = delete;
        StatementData(StatementData&&) noexcept = delete;
        StatementData& operator=(const StatementData&) = delete;
        StatementData& operator=(StatementData&&) noexcept = delete;
    private:
        void ReleaseFunctions();
    private:
        ValueOrFunctionData& GetNullValueOrFunction()const;
    private:
        std::vector<ValueOrFunctionData*> m_ValueOrFunctions;
    private:
        SyntaxComponentCommentsInfo* m_pCommentsInfo;
    };

    class DslFile final
    {
        using SyntaxComponentPtr = ISyntaxComponent*;
    public:
        int GetDslInfoNum()const { return static_cast<int>(m_DslInfos.size()); }
        ISyntaxComponent* GetDslInfo(int index)const
        {
            if (index < 0 || index >= static_cast<int>(m_DslInfos.size()))
                return nullptr;
            return m_DslInfos[index];
        }
        void WriteToFile(FILE* fp, int indent) const;
    public:
        ValueData* AddValue();
        FunctionData* AddFunction();
        StatementData* AddStatement();
        ISyntaxComponent* AddDslCopyFrom(const DslData::ISyntaxComponent& other);
    public:
        DslFile();
        ~DslFile();
        void Reset();
    public:
        void LoadBinaryCode(const char* buffer, int bufferSize, std::vector<std::string>& reuseKeyBuffer, std::vector<std::string>& reuseIdBuffer);
        void SaveBinaryFile(FILE* fp) const;
    public:
        void SetFileName(const std::string& name)
        {
            std::string str = name;
            SetFileName(std::move(str));
        }
        void SetFileName(std::string&& name)
        {
            m_FileName = std::move(name);
        }
        const std::string& GetFileName()const { return m_FileName; }
        void SetNullableSyntax(bool enabled);
        void SetStringDelimiter(const char* begin, const char* end);
        void SetScriptDelimiter(const char* begin, const char* end);
    public:
        bool IsNullableSyntaxEnabled()const { return m_NullableSyntaxEnabled; }
        const std::string& GetStringBeginDelimiter()const { return m_StringBeginDelimiter; }
        const std::string& GetStringEndDelimiter()const { return m_StringEndDelimiter; }
        const std::string& GetScriptBeginDelimiter()const { return m_ScriptBeginDelimiter; }
        const std::string& GetScriptEndDelimiter()const { return m_ScriptEndDelimiter; }
    public:
        void ClearErrorInfo()
        {
            m_HasError = false;
            m_ErrorInfo.clear();
        }
        void AddError(const std::string& err)
        {
            std::string str = err;
            AddError(std::move(str));
        }
        void AddError(std::string&& err)
        {
            m_HasError = true;
            m_ErrorInfo.push_back(std::move(err));
        }
        int HasError()const { return m_HasError; }
        int GetErrorNum()const { return static_cast<int>(m_ErrorInfo.size()); }
        const std::string& GetErrorInfo(int index) const
        {
            if (index < 0 || index >= GetErrorNum())
                return ISyntaxComponent::EmptyString();
            return m_ErrorInfo[index];
        }
    private:
        DslFile(const DslFile&) = delete;
        DslFile(DslFile&&) noexcept = delete;
        DslFile& operator=(const DslFile&) = delete;
        DslFile& operator=(DslFile&&) noexcept = delete;
    private:
        void Init();
        void Release();
    private:
        std::string m_FileName;
        std::vector<SyntaxComponentPtr> m_DslInfos;
    private:
        bool m_NullableSyntaxEnabled;
        std::string m_ScriptBeginDelimiter;
        std::string m_ScriptEndDelimiter;
        std::string m_StringBeginDelimiter;
        std::string m_StringEndDelimiter;
    private:
        bool m_HasError;
        std::vector<std::string> m_ErrorInfo;
    public:
        static bool Mac2Unix(char* buf, int len);
    public:
        static ISyntaxComponent& GetNullSyntax();
        static FunctionData& GetNullFunction();
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

}

#endif
