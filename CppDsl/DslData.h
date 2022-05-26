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
    //DslParser部分主要设计考虑使用固定大小的内存来解析dsl文件，使用连续内存，避免内存碎片，同时内存可完全重用。
    //这里则是解析后供外部使用的结果数据，考虑到实际使用方便，这里会使用动态内存管理与比较多的stl对象
    //这里出现的类与DslParser里面的类基本上是平行的一对一关系

    struct DelimiterInfo final
    {
        const std::string ScriptBeginDelimiter;
        const std::string ScriptEndDelimiter;
        const std::string StringBeginDelimiter;
        const std::string StringEndDelimiter;

        DelimiterInfo(void)
            :StringBeginDelimiter("\""), StringEndDelimiter("\""), ScriptBeginDelimiter("{:"), ScriptEndDelimiter(":}")
        {}
        DelimiterInfo(const std::string& strBeginDelim, const std::string& strEndDelim, const std::string& scpBeginDelim, const std::string& scpEndDelim)
            :StringBeginDelimiter(strBeginDelim), StringEndDelimiter(strEndDelim), ScriptBeginDelimiter(scpBeginDelim), ScriptEndDelimiter(scpEndDelim)
        {}
    };

    //这2个结构作纯数据使用，不需要虚析构了
    struct SyntaxComponentCommentsInfo
    {
        bool m_FirstCommentOnNewLine;
        bool m_LastCommentOnNewLine;
        std::vector<std::string> m_FirstComments;
        std::vector<std::string> m_LastComments;

        SyntaxComponentCommentsInfo(void) :m_FirstComments(0), m_LastComments(0), m_FirstCommentOnNewLine(false), m_LastCommentOnNewLine(false)
        {}
    };
    struct FunctionCommentsInfo : public SyntaxComponentCommentsInfo
    {
        std::vector<std::string> m_Comments;

        FunctionCommentsInfo(void) :SyntaxComponentCommentsInfo(), m_Comments(0)
        {}
    };

    class ISyntaxComponent : public IDslSyntaxCommon
    {
    public:
        ISyntaxComponent(int syntaxType);
        virtual ~ISyntaxComponent(void)override;
    public:
        virtual bool IsValid(void) const = 0;
        virtual const std::string& GetId(void) const = 0;
        virtual int GetIdType(void) const = 0;
        virtual int GetLine(void) const = 0;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const = 0;
        virtual bool HaveId(void) const = 0;
    public:
        int GetSyntaxType(void) const { return m_SyntaxType; }
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
        int GetFirstCommentNum(void) const
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
        bool IsFirstCommentOnNewLine(void) const
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
        int GetLastCommentNum(void) const
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
        bool IsLastCommentOnNewLine(void) const
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
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo(void) const { return nullptr; }
    private:
        int m_SyntaxType;
    public:
        static const std::string& EmptyString(void)
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
        bool IsValue(void)const
        {
            return GetSyntaxType() == ISyntaxComponent::TYPE_VALUE;
        }
        bool IsFunction(void)const
        {
            return GetSyntaxType() == ISyntaxComponent::TYPE_FUNCTION;
        }
        const ValueData* AsValue(void)const
        {
            if (IsValue())
                return reinterpret_cast<const ValueData*>(this);
            else
                return nullptr;
        }
        ValueData* AsValue(void)
        {
            if (IsValue())
                return reinterpret_cast<ValueData*>(this);
            else
                return nullptr;
        }
        const FunctionData* AsFunction(void)const
        {
            if (IsFunction())
                return reinterpret_cast<const FunctionData*>(this);
            else
                return nullptr;
        }
        FunctionData* AsFunction(void)
        {
            if (IsFunction())
                return reinterpret_cast<FunctionData*>(this);
            else
                return nullptr;
        }
    };

    class ValueData final : public ValueOrFunctionData
    {
    public:
        ValueData(void) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_IDENTIFIER), m_StringVal(), m_FunctionVal(nullptr), m_Line(0) {}
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

        virtual bool IsValid(void)const override;
        virtual int GetIdType(void)const override;
        virtual const std::string& GetId(void)const override;
        virtual int GetLine(void)const override;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual bool HaveId()const override;

        FunctionData* GetFunction(void)const { return m_FunctionVal; }

        bool IsNum(void)const { return (m_Type == VALUE_TYPE_NUM); }
        bool IsString(void)const { return (m_Type == VALUE_TYPE_STRING); }
        bool IsIdentifier(void)const { return (m_Type == VALUE_TYPE_IDENTIFIER && !m_StringVal.empty()); }
        bool IsFunction(void)const { return (m_Type == VALUE_TYPE_FUNCTION); }

        void SetInvalid(void)
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
        FunctionData* SetFunction(void);
        FunctionData* SetFunctionCopyFrom(const FunctionData& other);
    private:
        void CopyFrom(const ValueData& other);
        void Release(void);
    private:
        int m_Type;
        std::string m_StringVal;
        FunctionData* m_FunctionVal;
        int m_Line;
    };

    class NullSyntax final : public ISyntaxComponent
    {
    public:
        NullSyntax(void) : ISyntaxComponent(ISyntaxComponent::TYPE_NULL) {}
    public:
        virtual bool IsValid(void) const override { return false; }
        virtual const std::string& GetId(void) const override { return ISyntaxComponent::EmptyString(); }
        virtual int GetIdType(void) const override { return ValueData::VALUE_TYPE_IDENTIFIER; }
        virtual int GetLine(void) const override { return 0; }
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override {}
        virtual bool HaveId() const override { return false; }
    private:
        NullSyntax(const NullSyntax&) = delete;
        NullSyntax(NullSyntax&&) = delete;
        NullSyntax& operator=(const NullSyntax&) = delete;
        NullSyntax& operator=(NullSyntax&&) = delete;
    };

    class StatementData;
    class FunctionData final : public ValueOrFunctionData
    {
        typedef ISyntaxComponent* SyntaxComponentPtr;
    public:
        virtual bool IsValid(void)const override
        {
            if (m_Name.IsValid())
                return true;
            else if (HaveParamOrStatement())
                return true;
            else
                return false;
        }
        virtual int GetIdType(void)const override { return m_Name.GetIdType(); }
        virtual const std::string& GetId(void)const override { return m_Name.GetId(); }
        virtual int GetLine(void)const override { return m_Name.GetLine(); }
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual bool HaveId(void)const override { return m_Name.HaveId(); }
    public:
        void SetName(const ValueData& val) { m_Name = val; }
        ValueData& GetName(void) { return m_Name; }
        void ClearParams(void);
        ValueData* AddValueParam(void);
        FunctionData* AddFunctionParam(void);
        StatementData* AddStatementParam(void);
        ISyntaxComponent* AddParamCopyFrom(const ISyntaxComponent& other);
        void SetParamClass(int v) { m_ParamClass = v; }
        int GetParamClass(void)const { return m_ParamClass; }
        int GetParamClassUnmasked(void)const
        {
            int paramClass = (m_ParamClass & (int)PARAM_CLASS_UNMASK);
            return paramClass;
        }
        bool HaveParamClassInfixFlag(void)const
        {
            int infix = (m_ParamClass & (int)PARAM_CLASS_WRAP_INFIX_CALL_MASK);
            return infix == (int)PARAM_CLASS_WRAP_INFIX_CALL_MASK;
        }
        bool IsOperatorParamClass(void)const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_OPERATOR;
        }
        bool IsTernaryOperatorParamClass(void)const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_TERNARY_OPERATOR;
        }
        bool IsMemberParamClass(void)const
        {
            int paramClass = GetParamClassUnmasked();
            return (paramClass == (int)PARAM_CLASS_COLON_COLON ||
                paramClass == (int)PARAM_CLASS_PERIOD ||
                paramClass == (int)PARAM_CLASS_PERIOD_STAR ||
                paramClass == (int)PARAM_CLASS_POINTER ||
                paramClass == (int)PARAM_CLASS_POINTER_STAR ||
                paramClass == (int)PARAM_CLASS_QUESTION_PERIOD ||
                paramClass == (int)PARAM_CLASS_QUESTION_PERIOD_STAR);
        }
        bool HaveParamOrStatement(void)const { return m_ParamClass != PARAM_CLASS_NOTHING; }
        bool HaveParam(void)const { return HaveParamOrStatement() && !HaveStatement() && !HaveExternScript(); }
        bool HaveStatement(void)const { return m_ParamClass == PARAM_CLASS_STATEMENT; }
        bool HaveExternScript(void)const { return m_ParamClass == PARAM_CLASS_EXTERN_SCRIPT; }
        bool IsHighOrder(void)const { return m_Name.IsFunction(); }
        FunctionData& GetLowerOrderFunction(void)const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr) {
                return *fptr;
            }
            else {
                return GetNullFunction();
            }
        }
        const FunctionData& GetThisOrLowerOrderCall(void)const
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
        FunctionData& GetThisOrLowerOrderCall(void)
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
        const FunctionData& GetThisOrLowerOrderBody(void)const
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
        FunctionData& GetThisOrLowerOrderBody(void)
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
        const FunctionData& GetThisOrLowerOrderScript(void)const
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
        FunctionData& GetThisOrLowerOrderScript(void)
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
        bool HaveLowerOrderParam(void)const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveParam())
                return true;
            else
                return false;
        }
        bool HaveLowerOrderStatement(void)const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveStatement())
                return true;
            else
                return false;
        }
        int HaveLowerOrderExternScript(void)const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveExternScript())
                return true;
            else
                return false;
        }
    public:
        const ValueData& GetName(void)const { return m_Name; }
        int GetParamNum(void)const { return static_cast<int>(m_Params.size()); }
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
        int GetCommentNum(void) const
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
        FunctionData(void);
        virtual ~FunctionData(void)override;
        void CopyFrom(const FunctionData& other);
        void InitParamsCapacity(int v);
    protected:
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo(void) const override
        {
            return m_pCommentsInfo;
        }
    private:
        FunctionData(const FunctionData& other) = delete;
        FunctionData(FunctionData&& other) = delete;
        FunctionData operator=(const FunctionData& other) = delete;
        FunctionData operator=(FunctionData&& other) = delete;
    private:
        void ReleaseParams(void);
        void ReleaseComments(void);
    private:
        NullSyntax& GetNullSyntax(void)const;
        FunctionData& GetNullFunction(void)const;
    private:
        ValueData m_Name;
        std::vector<SyntaxComponentPtr> m_Params;
        int m_ParamClass;
    private:
        FunctionCommentsInfo* m_pCommentsInfo;
    };

    /* 备忘：为什么StatementData的成员不使用ISyntaxComponent[]而是FunctionData[]
     * 1、虽然语法上这里的FunctionData可以退化为ValueData，但不可以是StatementData，这样在概念上不能与ISyntaxComponent等同
     * 2、在设计上，FunctionData应该考虑到退化情形，尽量在退化情形不占用额外空间
     */
    class StatementData final : public ISyntaxComponent
    {
    public:
        virtual bool IsValid(void)const override
        {
            if (m_ValueOrFunctions.size() > 0 && m_ValueOrFunctions[0]->IsValid())
                return true;
            else
                return false;
        }
        virtual int GetIdType(void)const override
        {
            int type = ValueData::VALUE_TYPE_IDENTIFIER;
            if (IsValid()) {
                type = m_ValueOrFunctions[0]->GetIdType();
            }
            return type;
        }
        virtual const std::string& GetId(void)const override
        {
            if (IsValid()) {
                return m_ValueOrFunctions[0]->GetId();
            }
            return ISyntaxComponent::EmptyString();
        }
        virtual int GetLine(void)const override
        {
            int line = 0;
            if (IsValid()) {
                line = m_ValueOrFunctions[0]->GetLine();
            }
            return line;
        }
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual bool HaveId(void) const override
        {
            if (0 == static_cast<int>(m_ValueOrFunctions.size()))
                return false;
            else
                return m_ValueOrFunctions[static_cast<int>(m_ValueOrFunctions.size()) - 1]->HaveId();
        }
    public:
        void ClearFunctions(void);
        ValueData* AddValue(void);
        FunctionData* AddFunction(void);
        ValueOrFunctionData* AddValueOrFunctionCopyFrom(const ValueOrFunctionData& other);
    public:
        int GetFunctionNum(void)const { return static_cast<int>(m_ValueOrFunctions.size()); }
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
        ValueOrFunctionData* GetFirst(void)const
        {
            return GetFunction(0);
        }
        ValueOrFunctionData* GetSecond(void)const
        {
            return GetFunction(1);
        }
        ValueOrFunctionData* GetThird(void)const
        {
            return GetFunction(2);
        }
        ValueOrFunctionData* GetLast(void)const
        {
            int num = GetFunctionNum();
            if (num <= 0)
                return &GetNullValueOrFunction();
            return GetFunction(num - 1);
        }
    public:
        StatementData(void);
        virtual ~StatementData(void) override;
        void CopyFrom(const StatementData& other);
        void InitFunctionsCapacity(int v);
    protected:
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo(void) const override
        {
            return m_pCommentsInfo;
        }
    private:
        StatementData(const StatementData&) = delete;
        StatementData(StatementData&&) = delete;
        StatementData& operator=(const StatementData&) = delete;
        StatementData& operator=(StatementData&&) = delete;
    private:
        void ReleaseFunctions(void);
    private:
        ValueOrFunctionData& GetNullValueOrFunction(void)const;
    private:
        std::vector<ValueOrFunctionData*> m_ValueOrFunctions;
    private:
        SyntaxComponentCommentsInfo* m_pCommentsInfo;
    };

    class DslFile final
    {
        typedef ISyntaxComponent* SyntaxComponentPtr;
    public:
        int GetDslInfoNum(void)const { return static_cast<int>(m_DslInfos.size()); }
        ISyntaxComponent* GetDslInfo(int index)const
        {
            if (index < 0 || index >= static_cast<int>(m_DslInfos.size()))
                return nullptr;
            return m_DslInfos[index];
        }
        void WriteToFile(FILE* fp, int indent) const;
    public:
        ValueData* AddValue(void);
        FunctionData* AddFunction(void);
        StatementData* AddStatement(void);
        ISyntaxComponent* AddDslCopyFrom(const DslData::ISyntaxComponent& other);
    public:
        DslFile(void);
        ~DslFile(void);
        void Reset(void);
    public:
        void LoadBinaryFile(const char* file);
        void LoadBinaryCode(const char* buffer, int bufferSize);
        void SaveBinaryFile(const char* file) const;
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
        const std::string& GetFileName(void)const { return m_FileName; }
        void SetStringDelimiter(const char* begin, const char* end);
        void SetScriptDelimiter(const char* begin, const char* end);
    public:
        const std::string& GetStringBeginDelimiter(void)const { return m_StringBeginDelimiter; }
        const std::string& GetStringEndDelimiter(void)const { return m_StringEndDelimiter; }
        const std::string& GetScriptBeginDelimiter(void)const { return m_ScriptBeginDelimiter; }
        const std::string& GetScriptEndDelimiter(void)const { return m_ScriptEndDelimiter; }
    public:
        void ClearErrorInfo(void)
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
        int HasError(void)const { return m_HasError; }
        int GetErrorNum(void)const { return static_cast<int>(m_ErrorInfo.size()); }
        const std::string& GetErrorInfo(int index) const
        {
            if (index < 0 || index >= GetErrorNum())
                return ISyntaxComponent::EmptyString();
            return m_ErrorInfo[index];
        }
    private:
        DslFile(const DslFile&) = delete;
        DslFile(DslFile&&) = delete;
        DslFile& operator=(const DslFile&) = delete;
        DslFile& operator=(DslFile&&) = delete;
    private:
        void Init(void);
        void Release(void);
    private:
        std::string m_FileName;
        std::vector<SyntaxComponentPtr> m_DslInfos;
    private:
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
        static NullSyntax& GetNullSyntax(void);
        static FunctionData& GetNullFunction(void);
    public:
        static bool DontLoadComments(void)
        {
            return DontLoadCommentsRef();
        }
        static void DontLoadComments(bool val)
        {
            DontLoadCommentsRef() = val;
        }
    private:
        static bool& DontLoadCommentsRef(void)
        {
            static bool s_DontLoadComments = false;
            return s_DontLoadComments;
        }
    };

}

#endif
