/*****************************************************************************

calc.h

******************************************************************************/

#ifndef _DSL_PARSER_H
#define _DSL_PARSER_H

#include "BaseType.h"
#include "Delegation.h"
#include "DslCommon.h"
#include <new>
#include <vector>

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
        //这三个数不能大于PTR_ARRAY_POOL_FREELINK_HEADER_SIZE
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
        DslOptions(void) :
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
    struct DelimiterInfo final
    {
        const char* ScriptBeginDelimiter;
        const char* ScriptEndDelimiter;
        const char* StringBeginDelimiter;
        const char* StringEndDelimiter;

        DelimiterInfo(void)
            :StringBeginDelimiter("\""), StringEndDelimiter("\""), ScriptBeginDelimiter("{:"), ScriptEndDelimiter(":}")
        {}
        DelimiterInfo(const char* strBeginDelim, const char* strEndDelim, const char* scpBeginDelim, const char* scpEndDelim)
            :StringBeginDelimiter(strBeginDelim), StringEndDelimiter(strEndDelim), ScriptBeginDelimiter(scpBeginDelim), ScriptEndDelimiter(scpEndDelim)
        {}
    };

    //这2个结构作纯数据使用，不需要虚析构了
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

        SyntaxComponentCommentsInfo(void) :m_FirstComments(0), m_FirstCommentNum(0), m_FirstCommentSpace(0), m_FirstCommentOnNewLine(0),
            m_LastComments(0), m_LastCommentNum(0), m_LastCommentSpace(0), m_LastCommentOnNewLine(0)
        {}
    };
    struct FunctionCommentsInfo : public SyntaxComponentCommentsInfo
    {
        const char** m_Comments;
        int m_CommentNum;
        int m_CommentSpace;

        FunctionCommentsInfo(void) :SyntaxComponentCommentsInfo(), m_Comments(0), m_CommentNum(0), m_CommentSpace(0)
        {}
    };

    class IDslStringAndObjectBuffer;
    class ISyntaxComponent : public IDslSyntaxCommon
    {
    public:
        ISyntaxComponent(int syntaxType);
        virtual ~ISyntaxComponent(void) override;
    public:
        virtual int IsValid(void) const = 0;
        virtual const char* GetId(void) const = 0;
        virtual int GetIdType(void) const = 0;
        virtual int GetLine(void) const = 0;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const = 0;
        virtual int HaveId(void) const = 0;
    public:
        int GetSyntaxType(void) const { return m_SyntaxType; }
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
        int GetFirstCommentNum(void) const
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
        int IsFirstCommentOnNewLine(void) const
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
        int GetLastCommentNum(void) const
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
        int IsLastCommentOnNewLine(void) const
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
        virtual IDslStringAndObjectBuffer* GetBuffer(void) const { return 0; }
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo(void) const { return 0; }
    private:
        void PrepareFirstComments(void);
        void PrepareLastComments(void);
    private:
        int m_SyntaxType;
    };

    class FunctionData;
    class ValueData;
    class ValueOrFunctionData : public ISyntaxComponent
    {
    public:
        ValueOrFunctionData(int syntaxType) :ISyntaxComponent(syntaxType)
        {}
    public:
        int IsValue(void)const
        {
            return GetSyntaxType() == ISyntaxComponent::TYPE_VALUE ? TRUE : FALSE;
        }
        int IsFunction(void)const
        {
            return GetSyntaxType() == ISyntaxComponent::TYPE_FUNCTION ? TRUE : FALSE;
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
    private:
        ValueOrFunctionData(const ValueOrFunctionData& other) = delete;
        ValueOrFunctionData(ValueOrFunctionData&& other) noexcept = delete;
        ValueOrFunctionData& operator=(const ValueOrFunctionData& other) = delete;
        ValueOrFunctionData& operator=(ValueOrFunctionData&& other) noexcept = delete;
    };

    class ValueData final : public ValueOrFunctionData
    {
    public:
        ValueData(void) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(VALUE_TYPE_IDENTIFIER), m_StringVal(0), m_Line(0) {}
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

        virtual int IsValid(void)const override;
        virtual int GetIdType(void)const override;
        virtual const char* GetId(void)const override;
        virtual int GetLine(void)const override;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual int HaveId()const override;

        FunctionData* GetFunction(void)const { return m_FunctionVal; }

        int IsNum(void)const { return (m_Type == VALUE_TYPE_NUM ? TRUE : FALSE); }
        int IsString(void)const { return (m_Type == VALUE_TYPE_STRING ? TRUE : FALSE); }
        int IsIdentifier(void)const { return (m_Type == VALUE_TYPE_IDENTIFIER && nullptr != m_ConstStringVal ? TRUE : FALSE); }
        int IsFunction(void)const { return (m_Type == VALUE_TYPE_FUNCTION ? TRUE : FALSE); }

        void SetInvalid(void)
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
            const char* m_ConstStringVal;//在脚本里与m_StringVal类型相同,用于实现自动const_cast
            FunctionData* m_FunctionVal;
        };
        int m_Line;
    };

    class NullSyntax final : public ISyntaxComponent
    {
    public:
        NullSyntax(void) : ISyntaxComponent(ISyntaxComponent::TYPE_NULL) {}
    public:
        virtual int IsValid(void) const override { return FALSE; }
        virtual const char* GetId(void) const override { return ""; }
        virtual int GetIdType(void) const override { return ValueData::VALUE_TYPE_IDENTIFIER; }
        virtual int GetLine(void) const override { return 0; }
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override {}
        virtual int HaveId()const override { return FALSE; }
    private:
        NullSyntax(const NullSyntax&) = delete;
        NullSyntax(NullSyntax&& other) noexcept = delete;
        NullSyntax& operator=(const NullSyntax&) = delete;
        NullSyntax& operator=(NullSyntax&& other) noexcept = delete;
    };

    class IDslStringAndObjectBuffer;
    class FunctionData final : public ValueOrFunctionData
    {
        typedef ISyntaxComponent* SyntaxComponentPtr;
    public:
        virtual int IsValid(void)const override
        {
            if (m_Name.IsValid())
                return TRUE;
            else if (HaveParamOrStatement())
                return TRUE;
            else
                return FALSE;
        }
        virtual int GetIdType(void)const override { return m_Name.GetIdType(); }
        virtual const char* GetId(void)const override { return m_Name.GetId(); }
        virtual int GetLine(void)const override { return m_Name.GetLine(); }
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const override;
        virtual int HaveId(void)const override { return m_Name.HaveId(); }
    public:
        void SetName(const ValueData& val) { m_Name = val; }
        ValueData& GetName(void) { return m_Name; }
        void ClearParams(void) { m_ParamNum = 0; }
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
        void SetParamClass(int v) { m_ParamClass = v; }
        int GetParamClass(void)const { return m_ParamClass; }
        int GetParamClassUnmasked(void)const
        {
            int paramClass = (m_ParamClass & (int)PARAM_CLASS_UNMASK);
            return paramClass;
        }
        int HaveParamClassInfixFlag(void)const
        {
            int infix = (m_ParamClass & (int)PARAM_CLASS_WRAP_INFIX_CALL_MASK);
            return infix == (int)PARAM_CLASS_WRAP_INFIX_CALL_MASK ? TRUE : FALSE;
        }
        int IsOperatorParamClass(void)const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_OPERATOR ? TRUE : FALSE;
        }
        int IsTernaryOperatorParamClass(void)const
        {
            int paramClass = GetParamClassUnmasked();
            return paramClass == (int)PARAM_CLASS_TERNARY_OPERATOR ? TRUE : FALSE;
        }
        int IsMemberParamClass(void)const
        {
            int paramClass = GetParamClassUnmasked();
            return (paramClass == (int)PARAM_CLASS_COLON_COLON ||
                paramClass == (int)PARAM_CLASS_PERIOD ||
                paramClass == (int)PARAM_CLASS_PERIOD_STAR ||
                paramClass == (int)PARAM_CLASS_POINTER ||
                paramClass == (int)PARAM_CLASS_POINTER_STAR ||
                paramClass == (int)PARAM_CLASS_QUESTION_PERIOD ||
                paramClass == (int)PARAM_CLASS_QUESTION_PERIOD_STAR) ? TRUE : FALSE;
        }
        int HaveParamOrStatement(void)const { return m_ParamClass != PARAM_CLASS_NOTHING ? TRUE : FALSE; }
        int HaveParam(void)const { return HaveParamOrStatement() && !HaveStatement() && !HaveExternScript(); }
        int HaveStatement(void)const { return m_ParamClass == PARAM_CLASS_STATEMENT ? TRUE : FALSE; }
        int HaveExternScript(void)const { return m_ParamClass == PARAM_CLASS_EXTERN_SCRIPT ? TRUE : FALSE; }
        int IsHighOrder(void)const { return m_Name.IsFunction(); }
        FunctionData& GetLowerOrderFunction(void)const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr) {
                return *fptr;
            }
            else {
                return *GetNullFunctionPtr();
            }
        }
        const FunctionData& GetThisOrLowerOrderCall(void)const
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
        FunctionData& GetThisOrLowerOrderCall(void)
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
        const FunctionData& GetThisOrLowerOrderBody(void)const
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
        FunctionData& GetThisOrLowerOrderBody(void)
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
        const FunctionData& GetThisOrLowerOrderScript(void)const
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
        FunctionData& GetThisOrLowerOrderScript(void)
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
        int HaveLowerOrderParam(void)const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveParam())
                return TRUE;
            else
                return FALSE;
        }
        int HaveLowerOrderStatement(void)const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveStatement())
                return TRUE;
            else
                return FALSE;
        }
        int HaveLowerOrderExternScript(void)const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr && fptr->HaveExternScript())
                return TRUE;
            else
                return FALSE;
        }
    public:
        const ValueData& GetName(void)const { return m_Name; }
        int GetParamNum(void)const { return m_ParamNum; }
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
        int GetCommentNum(void) const
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
        virtual ~FunctionData(void) override;
        void InitParamsCapacity(int c);
    protected:
        virtual IDslStringAndObjectBuffer* GetBuffer(void) const override
        {
            return &m_Buffer;
        }
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo(void) const override
        {
            return m_pCommentsInfo;
        }
    private:
        FunctionData(const FunctionData& other) = delete;
        FunctionData(FunctionData&& other) noexcept = delete;
        FunctionData operator=(const FunctionData& other) = delete;
        FunctionData& operator=(FunctionData&& other) noexcept = delete;
    private:
        void PrepareParams(void);
        void ReleaseParams(void);
        void PrepareComments(void);
        void ReleaseComments(void);
    private:
        NullSyntax* GetNullSyntaxPtr(void)const;
        FunctionData* GetNullFunctionPtr(void)const;
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

    /* 备忘：为什么StatementData的成员不使用ISyntaxComponent[]而是FunctionData[]
     * 1、虽然语法上这里的FunctionData可以退化为ValueData，但不可以是StatementData，这样在概念上不能与ISyntaxComponent等同
     * 2、在设计上，FunctionData应该考虑到退化情形，尽量在退化情形不占用额外空间
     */
    class StatementData final : public ISyntaxComponent
    {
    public:
        virtual int IsValid(void)const override
        {
            if (nullptr != m_ValueOrFunctions && m_ValueOrFunctionNum > 0 && m_ValueOrFunctions[0]->IsValid())
                return TRUE;
            else
                return FALSE;
        }
        virtual int GetIdType(void)const override
        {
            int type = ValueData::VALUE_TYPE_IDENTIFIER;
            if (IsValid()) {
                type = m_ValueOrFunctions[0]->GetIdType();
            }
            return type;
        }
        virtual const char* GetId(void)const override
        {
            const char* str = "";
            if (IsValid()) {
                str = m_ValueOrFunctions[0]->GetId();
            }
            return str;
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
        virtual int HaveId(void) const override
        {
            if (nullptr == m_ValueOrFunctions || 0 == m_ValueOrFunctionNum)
                return FALSE;
            else
                return m_ValueOrFunctions[m_ValueOrFunctionNum - 1]->HaveId();
        }
    public:
        void ClearFunctions(void) { m_ValueOrFunctionNum = 0; }
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
        ValueOrFunctionData*& GetLastFunctionRef(void)const
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
        int GetFunctionNum(void)const { return m_ValueOrFunctionNum; }
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
                return GetNullValueOrFunctionPtrRef();
            return GetFunction(num - 1);
        }
    public:
        StatementData(IDslStringAndObjectBuffer& buffer);
        virtual ~StatementData(void) override
        {
            ReleaseFunctions();
            ReleaseFirstComments(&m_Buffer, m_pCommentsInfo);
            ReleaseLastComments(&m_Buffer, m_pCommentsInfo);
        }
        void InitFunctionsCapacity(int c);
    protected:
        virtual IDslStringAndObjectBuffer* GetBuffer(void) const override
        {
            return &m_Buffer;
        }
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo(void) const override
        {
            return m_pCommentsInfo;
        }
    private:
        StatementData(const StatementData&) = delete;
        StatementData(StatementData&& other) noexcept = delete;
        StatementData& operator=(const StatementData&) = delete;
        StatementData& operator=(StatementData&& other) noexcept = delete;
    private:
        void PrepareFunctions(void);
        void ReleaseFunctions(void);
    private:
        ValueOrFunctionData*& GetNullValueOrFunctionPtrRef(void)const;
    private:
        ValueOrFunctionData** m_ValueOrFunctions;
        int m_ValueOrFunctionNum;
        int m_ValueOrFunctionSpace;
        int m_MaxValueOrFunctionNum;
    private:
        IDslStringAndObjectBuffer& m_Buffer;
        SyntaxComponentCommentsInfo* m_pCommentsInfo;
    };

    //在c++实现里，DSL的内存希望尽量是预先分配的，这个接口用来实现预先分配的内存
    class IDslStringAndObjectBuffer
    {
    public:
        virtual DslOptions& GetOptions(void) = 0;
        virtual const DslOptions& GetOptions(void)const = 0;
    public:
        virtual char* AllocString(int len) = 0;
        virtual char* AllocString(const char* src) = 0;
        virtual char* GetStringBuffer(void)const = 0;
        virtual char*& GetUnusedStringPtrRef(void) = 0;
        virtual int GetUnusedStringLength(void)const = 0;
    public:
        virtual SyntaxComponentCommentsInfo* NewSyntaxComponentCommentsInfo(void) = 0;
        virtual FunctionCommentsInfo* NewFunctionCommentsInfo(void) = 0;
    public:
        virtual ValueData* AddNewValueComponent(void) = 0;
        virtual FunctionData* AddNewFunctionComponent(void) = 0;
        virtual StatementData* AddNewStatementComponent(void) = 0;
        virtual int GetUnusedObjectLength(void)const = 0;
    public:
        virtual void** NewPtrArray(int size) = 0;
        virtual void DeletePtrArray(void** ptr, int size) = 0;
    public:
        virtual void ZeroErrorInfoBuffer(void) = 0;
        virtual char* GetSingleErrorInfoBuffer(int index) = 0;
        virtual int GetSingleErrorInfoCapacity(void) = 0;
    public:
        virtual NullSyntax* GetNullSyntaxPtr(void) = 0;
        virtual FunctionData* GetNullFunctionPtr(void) = 0;
        virtual FunctionData*& GetNullFunctionPtrRef(void) = 0;
        virtual ValueOrFunctionData*& GetNullValueOrFunctionPtrRef(void) = 0;
    public:
        virtual void Reset(void) = 0;
        virtual ~IDslStringAndObjectBuffer(void) {}
    };

    /*
     * 实际的DSL预先分配缓冲区，这个类需要在堆上实例化（在栈上可能导致栈溢出），类本身使
     * 用数组来分配缓冲区。
     * 理想情况是所有相关类使用的内存都是预先分配的。
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
        typedef ISyntaxComponent* SyntaxComponentPtr;
    public:
        virtual DslOptions& GetOptions(void) override { return m_Options; }
        virtual const DslOptions& GetOptions(void)const override { return m_Options; }
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
                strcpy(p, src);
            }
            return p;
        }
        virtual char* GetStringBuffer(void)const override { return m_pStringBuffer; }
        virtual char*& GetUnusedStringPtrRef(void) override { return m_pUnusedStringPtr; }
        virtual int GetUnusedStringLength(void)const override
        {
            MyAssert(m_pUnusedStringRef);
            MyAssert(m_pUnusedObjectPtr);
            return static_cast<int>(m_pUnusedObjectPtr - m_pUnusedStringPtr);
        }
    public:
        virtual SyntaxComponentCommentsInfo* NewSyntaxComponentCommentsInfo(void) override
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
        virtual FunctionCommentsInfo* NewFunctionCommentsInfo(void) override
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
        virtual ValueData* AddNewValueComponent(void) override
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
        virtual FunctionData* AddNewFunctionComponent(void) override
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
        virtual StatementData* AddNewStatementComponent(void) override
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
        virtual int GetUnusedObjectLength(void)const override
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
                //空闲链表上有的话就用空闲链表的数据，空闲链表头指向链表后一个元素，原链表头从链表拆除后放到空闲链表块的空闲链表中
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
            //分配一个新的空闲链表块来描述回收的数组，并加到空闲链表上
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
                //这个块浪费掉了，需要调整空闲链表参数的大小
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
        virtual void ZeroErrorInfoBuffer(void) override
        {
            memset(m_ErrorInfo, 0, sizeof(m_ErrorInfo));
        }
        virtual char* GetSingleErrorInfoBuffer(int index) override
        {
            if (index < 0 || index >= MaxErrorInfoNum)
                return nullptr;
            return m_ErrorInfo[index];
        }
        virtual int GetSingleErrorInfoCapacity(void) override
        {
            return SingleErrorInfoCapacity;
        }
    public:
        virtual NullSyntax* GetNullSyntaxPtr(void) override
        {
            return &m_NullSyntax;
        }
        virtual FunctionData* GetNullFunctionPtr(void) override
        {
            m_NullFunction.GetName().SetInvalid();
            m_NullFunction.SetParamClass(FunctionData::PARAM_CLASS_NOTHING);
            m_NullFunction.ClearParams();
            return &m_NullFunction;
        }
        virtual FunctionData*& GetNullFunctionPtrRef(void) override
        {
            auto fptr = m_pNullFunction;
            fptr->GetName().SetInvalid();
            fptr->SetParamClass(FunctionData::PARAM_CLASS_NOTHING);
            fptr->ClearParams();
            return m_pNullFunction;
        }
        virtual ValueOrFunctionData*& GetNullValueOrFunctionPtrRef(void) override
        {
            auto fptr = m_pNullFunction;
            fptr->GetName().SetInvalid();
            fptr->SetParamClass(FunctionData::PARAM_CLASS_NOTHING);
            fptr->ClearParams();
            return m_pNullValueOrFunction;
        }
    public:
        DslStringAndObjectBufferT(void) :m_SyntaxComponentNum(0), m_SyntaxComponentCommentsInfoNum(0), m_FunctionCommentsInfoNum(0),
            m_pStringBuffer(m_StringBuffer),
            m_pUnusedStringPtr(m_StringBuffer),
            m_pUnusedObjectPtr(m_StringBuffer + StringAndObjectBufferSize),
            m_NullSyntax(),
            m_NullFunction(*this),
            m_pNullFunction(&m_NullFunction),
            m_pNullValueOrFunction(&m_NullFunction)
        {
            memset(m_SyntaxComponentPool, 0, sizeof(SyntaxComponentPtr) * (SyntaxComponentAndPtrArrayPoolSize));
            m_pPtrFreeLink = reinterpret_cast<FreeLinkInfo*>(m_SyntaxComponentPool + SyntaxComponentAndPtrArrayPoolSize);
            m_FreeLinkNum = 0;
            memset(m_PtrFreeLinkHeader, 0, sizeof(unsigned int) * PtrArrayPoolFreeLinkHeaderSize);
            m_FreedFreeLinkHeader = 0;
        }
        virtual void Reset(void) override
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
        //字符串与对象共用一个buffer，字符串正向增长，对象反向增长
        char m_StringBuffer[StringAndObjectBufferSize];
        char* m_pStringBuffer;
        char* m_pUnusedStringPtr;
        char* m_pUnusedObjectPtr;
    private:
        //语法组件指针、指针数组与空闲块共用一个buffer，语法组件指针与指针数组正向增长，空闲块反向增长，这里的数据通常是字对齐的，所以不考虑与字符串和对象buffer共用
        SyntaxComponentPtr m_SyntaxComponentPool[SyntaxComponentAndPtrArrayPoolSize];//语法组件指针数组，总数与一个dsl文件里的所有语法组件数量相当
            //指针数组缓冲区，主要用来分配语法组件指针数组，PtrPoolSize与一个dsl文件里的所有语法组件数量相当
        FreeLinkInfo* m_pPtrFreeLink;//低32位对应m_PtrPool的索引，高32位是下一个空闲块的索引。空闲块的数量，对dsl文件解析来说，这个值理论上应该很低，大约与（语法数组扩容的次数-新语法重用数组的次数）相当
        int m_FreeLinkNum;
        int m_SyntaxComponentNum;
        int m_SyntaxComponentCommentsInfoNum;
        int m_FunctionCommentsInfoNum;
    private:
        int m_PtrFreeLinkHeader[PtrArrayPoolFreeLinkHeaderSize];//以数组大小为索引的各size空闲链表头的位置，这个数组的大小就是允许的各个语法组件数组的最大值，语句函数数量、参数数量、单文件DSL数量等受此限制
        int m_FreedFreeLinkHeader;//空闲的空闲块链表的头
    private:
        char m_ErrorInfo[MaxErrorInfoNum][SingleErrorInfoCapacity];
    private:
        NullSyntax m_NullSyntax;
        FunctionData m_NullFunction;
        FunctionData* m_pNullFunction;
        ValueOrFunctionData* m_pNullValueOrFunction;
    };

    class DslTokenApi
    {
    public:
        char* getCurToken(void) const;
        char* getLastToken(void) const;
        int getLineNumber(void) const;
        int getLastLineNumber(void) const;
        void setCurToken(char* tok)const;
        void setLastToken(char* tok)const;
        bool enqueueToken(char* tok, short val, int line)const;
        char curChar(void)const;
        char nextChar(void)const;
        char peekChar(int ix)const;
        char peekNextValidChar(int beginIx)const;
        char peekNextValidChar(int beginIx, int& index)const;
        void getOperatorToken(void);
        short getOperatorTokenValue(void)const;
        int isNotIdentifierAndEndParenthesis(char c)const;
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
    class DslActionApi
    {
    public:
        void endStatement(void)const;
        void buildOperator(void)const;
        void buildFirstTernaryOperator(void)const;
        void buildSecondTernaryOperator(void)const;
        void beginStatement(void)const;
        void addFunction(void)const;
        void setFunctionId(void)const;
        void markParenthesisParam(void)const;
        void buildHighOrderFunction(void)const;
        void markBracketParam(void)const;
        void markQuestionParenthesisParam(void)const;
        void markQuestionBracketParam(void)const;
        void markQuestionBraceParam(void)const;
        void markStatement(void)const;
        void markExternScript(void)const;
        void markBracketColonParam(void)const;
        void markParenthesisColonParam(void)const;
        void markAngleBracketColonParam(void)const;
        void markBracePercentParam(void)const;
        void markBracketPercentParam(void)const;
        void markParenthesisPercentParam(void)const;
        void markAngleBracketPercentParam(void)const;
        void markColonColonParam(void)const;
        void markColonColonParenthesisParam(void)const;
        void markColonColonBracketParam(void)const;
        void markColonColonBraceParam(void)const;
        void setExternScript(void)const;
        void markPeriodParam(void)const;
        void setMemberId(void)const;
        void markPeriodParenthesisParam(void)const;
        void markPeriodBracketParam(void)const;
        void markPeriodBraceParam(void)const;
        void markQuestionPeriodParam(void)const;
        void markPointerParam(void)const;
        void markPeriodStarParam(void)const;
        void markQuestionPeriodStarParam(void)const;
        void markPointerStarParam(void)const;
    public:
        void push(char* token, int type)const;
        StatementData* getCurStatement(void)const;
        FunctionData* getLastFunction(void)const;
        void setLastFunction(FunctionData* p)const;
    public:
        inline DslActionApi(void) :m_Impl(0) {}
        inline void SetImpl(ActionForSourceCodeScript* p) { m_Impl = p; }
    private:
        DslActionApi(const DslActionApi& other) = delete;
        DslActionApi(DslActionApi&& other) noexcept = delete;
        DslActionApi& operator=(const DslActionApi& other) = delete;
        DslActionApi& operator=(DslActionApi&& other) noexcept = delete;
    private:
        ActionForSourceCodeScript* m_Impl;
    };
    typedef Delegation3<bool, char*, short, int> EnqueueTokenDelegation;
    class IScriptSource;
    class DslFile final
    {
        typedef ISyntaxComponent* SyntaxComponentPtr;
    public:
        typedef Delegation4<bool, const DslTokenApi&, char*&, short&, int&> GetTokenDelegation;
        typedef Delegation2<bool, const DslActionApi&, StatementData*> BeforeAddFunctionDelegation;
        typedef Delegation3<bool, const DslActionApi&, StatementData*, FunctionData*> AddFunctionDelegation;
        typedef Delegation1<bool, const DslActionApi&> BeforeEndStatementDelegation;
        typedef Delegation2<bool, const DslActionApi&, StatementData*&> EndStatementDelegation;
    public:
        int GetDslInfoNum(void)const { return m_DslInfoNum; }
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
        ~DslFile(void);
        void Reset(void);
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
        void SetStringDelimiter(const char* begin, const char* end);
        void SetScriptDelimiter(const char* begin, const char* end);
    public:
        const char* GetStringBeginDelimiter(void)const { return m_StringBeginDelimiter; }
        const char* GetStringEndDelimiter(void)const { return m_StringEndDelimiter; }
        const char* GetScriptBeginDelimiter(void)const { return m_ScriptBeginDelimiter; }
        const char* GetScriptEndDelimiter(void)const { return m_ScriptEndDelimiter; }
    public:
        GetTokenDelegation OnGetToken;
        BeforeAddFunctionDelegation OnBeforeAddFunction;
        AddFunctionDelegation OnAddFunction;
        BeforeEndStatementDelegation OnBeforeEndStatement;
        EndStatementDelegation OnEndStatement;
    private:
        DslFile(const DslFile& other) = delete;
        DslFile(DslFile&& other) noexcept = delete;
        DslFile& operator=(const DslFile& other) = delete;
        DslFile& operator=(DslFile&& other) noexcept = delete;
    private:
        void Init(void);
        void Release(void);
    public:
        void EnableDebugInfo(void) { m_IsDebugInfoEnable = TRUE; }
        void DisableDebugInfo(void) { m_IsDebugInfoEnable = FALSE; }
        int IsDebugInfoEnable(void)const { return m_IsDebugInfoEnable; }
    public:
        void ClearErrorInfo(void);
        void AddError(const char* error);
        int HasError(void)const { return m_HasError; }
        int GetErrorNum(void)const { return m_ErrorNum; }
        const char* GetErrorInfo(int index) const
        {
            if (index < 0 || index >= m_ErrorNum)
                return "";
            auto* ptr = m_Buffer.GetSingleErrorInfoBuffer(index);
            if (!ptr)
                return "";
            return ptr;
        }
        char* NewErrorInfo(void)
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
        int GetSingleErrorInfoCapacity(void)const { return m_Buffer.GetSingleErrorInfoCapacity(); }
    public:
        char* AllocString(int len) const { return m_Buffer.AllocString(len); }
        char* AllocString(const char* src) const { return m_Buffer.AllocString(src); }
        char* GetStringBuffer(void) const { return m_Buffer.GetStringBuffer(); }
        char*& GetUnusedStringPtrRef(void) const { return m_Buffer.GetUnusedStringPtrRef(); }
        int GetUnusedStringLength(void) const { return m_Buffer.GetUnusedStringLength(); }
    public:
        ValueData* AddNewValueComponent(void) const { return m_Buffer.AddNewValueComponent(); }
        FunctionData* AddNewFunctionComponent(void) const { return m_Buffer.AddNewFunctionComponent(); }
        StatementData* AddNewStatementComponent(void) const { return m_Buffer.AddNewStatementComponent(); }
    public:
        FunctionData* GetNullFunctionPtr(void) { return m_Buffer.GetNullFunctionPtr(); }
    private:
        void PrepareDslInfos(void);
        void ReleaseDslInfos(void);
    private:
        IDslStringAndObjectBuffer& m_Buffer;
    private:
        SyntaxComponentPtr* m_DslInfos;
        int m_DslInfoNum;
        int m_DslInfoSpace;
        int m_MaxDslInfoNum;
    private:
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
        virtual ~IScriptSource(void) {}
    public:
        class Iterator
        {
        public:
            const char& operator * (void) const
            {
                return Peek(0);
            }
            Iterator& operator ++ (void)
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
            int Load(void)
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
            const char* GetBuffer(void)const
            {
                return m_pSource->GetBuffer();
            }
            const char* GetLeft(void)const
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
            Iterator(void) :m_pSource(nullptr), m_Iterator(""), m_EndIterator(m_Iterator)
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
            void Advance(void)
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
        Iterator GetIterator(void)
        {
            return Iterator(*this);
        }
    protected:
        virtual int Load(void) = 0;
        virtual const char* GetBuffer(void)const = 0;
    };
}

#endif
