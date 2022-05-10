/*****************************************************************************

calc.h

******************************************************************************/

#ifndef _CALC_H
#define _CALC_H

#include "BaseType.h"
#include <new>

namespace Dsl
{
    template<typename DestT>
    struct ReinterpretCast
    {
        template<typename SrcT>
        static DestT From(const SrcT& v)
        {
            union
            {
                SrcT m_Src;
                DestT m_Dest;
            } tmp;
            tmp.m_Src = v;
            return tmp.m_Dest;
        }
    };

    enum
    {
        MAX_ERROR_INFO_CAPACITY = 1024,
        MAX_RECORD_ERROR_NUM = 256,

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
        //这三个数不能大于PTR_POOL_FREELINK_HEADER_SIZE
        MAX_FUNCTION_DIMENSION_NUM = 16,
        MAX_FUNCTION_PARAM_NUM = 16 * 1024,
        MAX_DSL_INFO_NUM = 16 * 1024,

        STRING_BUFFER_SIZE = 4 * 1024 * 1024,
        OBJECT_BUFFER_SIZE = 4 * 1024 * 1024,
        SYNTAXCOMPONENT_POOL_SIZE = 512 * 1024,
        PTR_POOL_SIZE = 512 * 1024,
        PTR_POOL_FREELINK_SIZE = 128 * 1024,
        PTR_POOL_FREELINK_HEADER_SIZE = 16 * 1024,
    };

    class DslOptions
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
    struct DelimiterInfo
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
    class ISyntaxComponent
    {
    public:
        enum
        {
            TYPE_NULL,
            TYPE_VALUE,
            TYPE_FUNCTION,
            TYPE_STATEMENT,
        };
    public:
        ISyntaxComponent(int syntaxType);
        virtual ~ISyntaxComponent(void);
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
            if (DslOptions::DontLoadComments())
                return;
            if (0 == GetCommentsInfo())
                return;
            PrepareFirstComments();
            if (GetCommentsInfo()->m_FirstCommentNum < GetCommentsInfo()->m_FirstCommentSpace) {
                GetCommentsInfo()->m_FirstComments[GetCommentsInfo()->m_FirstCommentNum++] = cmt;
            }
        }
        void RemoveFirstComment(int index)
        {
            if (DslOptions::DontLoadComments())
                return;
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
            if (DslOptions::DontLoadComments())
                return;
            if (0 == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_FirstCommentNum = 0;
        }
        int GetFirstCommentNum(void) const
        {
            if (DslOptions::DontLoadComments())
                return 0;
            if (0 == GetCommentsInfo())
                return 0;
            return GetCommentsInfo()->m_FirstCommentNum;
        }
        const char* GetFirstComment(int index) const
        {
            if (DslOptions::DontLoadComments())
                return 0;
            if (0 != GetCommentsInfo() && index >= 0 && index < GetCommentsInfo()->m_FirstCommentNum) {
                return GetCommentsInfo()->m_FirstComments[index];
            }
            else {
                return 0;
            }
        }
        int IsFirstCommentOnNewLine(void) const
        {
            if (DslOptions::DontLoadComments())
                return 0;
            if (0 == GetCommentsInfo())
                return 0;
            return GetCommentsInfo()->m_FirstCommentOnNewLine;
        }
        void SetFirstCommentOnNewLine(int v)
        {
            if (DslOptions::DontLoadComments())
                return;
            if (0 == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_FirstCommentOnNewLine = v;
        }
        void AddLastComment(const char* cmt)
        {
            if (DslOptions::DontLoadComments())
                return;
            if (0 == GetCommentsInfo())
                return;
            PrepareLastComments();
            if (GetCommentsInfo()->m_LastCommentNum < GetCommentsInfo()->m_LastCommentSpace) {
                GetCommentsInfo()->m_LastComments[GetCommentsInfo()->m_LastCommentNum++] = cmt;
            }
        }
        void RemoveLastComment(int index)
        {
            if (DslOptions::DontLoadComments())
                return;
            if (0 != GetCommentsInfo() && index >= 0 && index < GetCommentsInfo()->m_LastCommentNum) {
                for (int ix = index; ix < GetCommentsInfo()->m_LastCommentNum - 1; ++ix) {
                    GetCommentsInfo()->m_LastComments[ix] = GetCommentsInfo()->m_LastComments[ix + 1];
                }
                --GetCommentsInfo()->m_LastCommentNum;
            }
        }
        void ClearLastComments()
        {
            if (DslOptions::DontLoadComments())
                return;
            if (0 == GetCommentsInfo())
                return;
            GetCommentsInfo()->m_LastCommentNum = 0;
        }
        int GetLastCommentNum(void) const
        {
            if (DslOptions::DontLoadComments())
                return 0;
            if (0 == GetCommentsInfo())
                return 0;
            return GetCommentsInfo()->m_LastCommentNum;
        }
        const char* GetLastComment(int index) const
        {
            if (DslOptions::DontLoadComments())
                return 0;
            if (0 != GetCommentsInfo() && index >= 0 && index < GetCommentsInfo()->m_LastCommentNum) {
                return GetCommentsInfo()->m_LastComments[index];
            }
            else {
                return 0;
            }
        }
        int IsLastCommentOnNewLine(void) const
        {
            if (DslOptions::DontLoadComments())
                return 0;
            if (0 == GetCommentsInfo())
                return 0;
            return GetCommentsInfo()->m_LastCommentOnNewLine;
        }
        void SetLastCommentOnNewLine(int v)
        {
            if (DslOptions::DontLoadComments())
                return;
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
            if (DslOptions::DontLoadComments())
                return;
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
            if (DslOptions::DontLoadComments())
                return;
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
    };

    class ValueData : public ValueOrFunctionData
    {
    public:
        enum
        {
            TYPE_IDENTIFIER = 0,
            TYPE_NUM,
            TYPE_STRING,
            TYPE_FUNCTION,
            TYPE_MAX = TYPE_STRING
        };

        ValueData(void) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_IDENTIFIER), m_StringVal(0), m_Line(0) {}
        explicit ValueData(char* val) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_STRING), m_StringVal(val), m_Line(0) {}
        explicit ValueData(const char* val) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_STRING), m_ConstStringVal(val), m_Line(0) {}
        explicit ValueData(FunctionData* val) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_FUNCTION), m_FunctionVal(val), m_Line(0) {}
        explicit ValueData(char* val, int type) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_StringVal(val), m_Line(0) {}
        explicit ValueData(const char* val, int type) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(type), m_ConstStringVal(val), m_Line(0) {}
        ValueData(const ValueData& other) :ValueOrFunctionData(ISyntaxComponent::TYPE_VALUE), m_Type(TYPE_IDENTIFIER), m_StringVal(0), m_Line(0)
        {
            ISyntaxComponent::CopyFrom(other);
            CopyFrom(other);
        }
        ValueData& operator=(const ValueData& other)
        {
            if (this == &other)
                return *this;
            ISyntaxComponent::CopyFrom(other);
            CopyFrom(other);
            return *this;
        }

        virtual int IsValid(void)const;
        virtual int GetIdType(void)const;
        virtual const char* GetId(void)const;
        virtual int GetLine(void)const;
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const;
        virtual int HaveId()const;

        FunctionData* GetFunction(void)const { return m_FunctionVal; }

        int IsNum(void)const { return (m_Type == TYPE_NUM ? TRUE : FALSE); }
        int IsString(void)const { return (m_Type == TYPE_STRING ? TRUE : FALSE); }
        int IsIdentifier(void)const { return (m_Type == TYPE_IDENTIFIER ? TRUE : FALSE); }
        int IsFunction(void)const { return (m_Type == TYPE_FUNCTION ? TRUE : FALSE); }

        void SetInvalid(void)
        {
            m_Type = TYPE_IDENTIFIER;
            m_StringVal = 0;
        }
        void SetNumber(char* str)
        {
            m_Type = TYPE_NUM;
            m_StringVal = str;
        }
        void SetNumber(const char* str)
        {
            m_Type = TYPE_NUM;
            m_ConstStringVal = str;
        }
        void SetString(char* str)
        {
            m_Type = TYPE_STRING;
            m_StringVal = str;
        }
        void SetString(const char* str)
        {
            m_Type = TYPE_STRING;
            m_ConstStringVal = str;
        }
        void SetFunction(FunctionData* func)
        {
            m_Type = TYPE_FUNCTION;
            m_FunctionVal = func;
        }
        void SetIdentifier(char* name)
        {
            m_Type = TYPE_IDENTIFIER;
            m_StringVal = name;
        }
        void SetLine(int line)
        {
            m_Line = line;
        }
        void SetTypeAndId(int type, const char* id)
        {
            m_Type = type;
            m_ConstStringVal = id;
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

    class NullSyntax : public ISyntaxComponent
    {
    public:
        NullSyntax(void) : ISyntaxComponent(ISyntaxComponent::TYPE_NULL) {}
    public:
        virtual int IsValid(void) const { return FALSE; }
        virtual const char* GetId(void) const { return ""; }
        virtual int GetIdType(void) const { return ValueData::TYPE_IDENTIFIER; }
        virtual int GetLine(void) const { return 0; }
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const {}
        virtual int HaveId()const { return FALSE; }
    private:
        NullSyntax(const NullSyntax&) = delete;
        NullSyntax& operator=(const NullSyntax&) = delete;
    };

    class IDslStringAndObjectBuffer;
    class FunctionData : public ValueOrFunctionData
    {
    public:
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
        typedef ISyntaxComponent* SyntaxComponentPtr;
    public:
        virtual int IsValid(void)const
        {
            if (m_Name.IsValid())
                return TRUE;
            else if (HaveParamOrStatement())
                return TRUE;
            else
                return FALSE;
        }
        virtual int GetIdType(void)const { return m_Name.GetIdType(); }
        virtual const char* GetId(void)const { return m_Name.GetId(); }
        virtual int GetLine(void)const { return m_Name.GetLine(); }
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const;
        virtual int HaveId(void)const { return m_Name.HaveId(); }
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
            if (NULL == pVal || index < 0 || index >= m_MaxParamNum)
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
        FunctionData* GetLowerOrderFunction(void)const
        {
            auto fptr = m_Name.GetFunction();
            if (IsHighOrder() && fptr) {
                return fptr;
            }
            else {
                return GetNullFunctionPtr();
            }
        }
        const FunctionData* GetThisOrLowerOrderCall(void)const
        {
            if (HaveParam()) {
                return this;
            }
            else if (HaveLowerOrderParam()) {
                return m_Name.GetFunction();
            }
            else {
                return GetNullFunctionPtr();
            }
        }
        FunctionData* GetThisOrLowerOrderCall(void)
        {
            if (HaveParam()) {
                return this;
            }
            else if (HaveLowerOrderParam()) {
                return m_Name.GetFunction();
            }
            else {
                return GetNullFunctionPtr();
            }
        }
        const FunctionData* GetThisOrLowerOrderBody(void)const
        {
            if (HaveStatement()) {
                return this;
            }
            else if (HaveLowerOrderStatement()) {
                return m_Name.GetFunction();
            }
            else {
                return GetNullFunctionPtr();
            }
        }
        FunctionData* GetThisOrLowerOrderBody(void)
        {
            if (HaveStatement()) {
                return this;
            }
            else if (HaveLowerOrderStatement()) {
                return m_Name.GetFunction();
            }
            else {
                return GetNullFunctionPtr();
            }
        }
        const FunctionData* GetThisOrLowerOrderScript(void)const
        {
            if (HaveExternScript()) {
                return this;
            }
            else if (HaveLowerOrderExternScript()) {
                return m_Name.GetFunction();
            }
            else {
                return GetNullFunctionPtr();
            }
        }
        FunctionData* GetThisOrLowerOrderScript(void)
        {
            if (HaveExternScript()) {
                return this;
            }
            else if (HaveLowerOrderExternScript()) {
                return m_Name.GetFunction();
            }
            else {
                return GetNullFunctionPtr();
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
            if (DslOptions::DontLoadComments())
                return;
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
            if (DslOptions::DontLoadComments())
                return;
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
            if (DslOptions::DontLoadComments())
                return;
            auto p = m_pCommentsInfo;
            if (0 == p)
                return;
            p->m_CommentNum = 0;
        }
        int GetCommentNum(void) const
        {
            if (DslOptions::DontLoadComments())
                return 0;
            auto p = m_pCommentsInfo;
            if (0 == p)
                return 0;
            return p->m_CommentNum;
        }
        const char* GetComment(int index) const
        {
            if (DslOptions::DontLoadComments())
                return 0;
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
        virtual ~FunctionData(void);
        void InitParamsCapacity(int c);
    protected:
        virtual IDslStringAndObjectBuffer* GetBuffer(void) const
        {
            return &m_Buffer;
        }
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo(void) const
        {
            return m_pCommentsInfo;
        }
    private:
        FunctionData(const FunctionData& other) = delete;
        FunctionData operator=(const FunctionData& other) = delete;
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
    class StatementData : public ISyntaxComponent
    {
    public:
        virtual int IsValid(void)const
        {
            if (NULL != m_ValueOrFunctions && m_ValueOrFunctionNum > 0 && m_ValueOrFunctions[0]->IsValid())
                return TRUE;
            else
                return FALSE;
        }
        virtual int GetIdType(void)const
        {
            int type = ValueData::TYPE_IDENTIFIER;
            if (IsValid()) {
                type = m_ValueOrFunctions[0]->GetIdType();
            }
            return type;
        }
        virtual const char* GetId(void)const
        {
            const char* str = "";
            if (IsValid()) {
                str = m_ValueOrFunctions[0]->GetId();
            }
            return str;
        }
        virtual int GetLine(void)const
        {
            int line = 0;
            if (IsValid()) {
                line = m_ValueOrFunctions[0]->GetLine();
            }
            return line;
        }
        virtual void WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim) const;
        virtual int HaveId(void) const
        {
            if (NULL == m_ValueOrFunctions || 0 == m_ValueOrFunctionNum)
                return FALSE;
            else
                return m_ValueOrFunctions[m_ValueOrFunctionNum - 1]->HaveId();
        }
    public:
        void ClearFunctions(void) { m_ValueOrFunctionNum = 0; }
        void AddFunction(ValueOrFunctionData* pVal)
        {
            if (NULL == pVal || m_ValueOrFunctionNum < 0 || m_ValueOrFunctionNum >= m_MaxValueOrFunctionNum)
                return;
            PrepareFunctions();
            if (NULL == m_ValueOrFunctions || m_ValueOrFunctionNum >= m_ValueOrFunctionSpace)
                return;
            m_ValueOrFunctions[m_ValueOrFunctionNum] = pVal;
            ++m_ValueOrFunctionNum;
        }
        ValueOrFunctionData*& GetLastFunctionRef(void)const
        {
            if (NULL == m_ValueOrFunctions || 0 == m_ValueOrFunctionNum)
                return GetNullValueOrFunctionPtrRef();
            else
                return m_ValueOrFunctions[m_ValueOrFunctionNum - 1];
        }
        ValueOrFunctionData*& GetFunctionRef(int index)const
        {
            if (NULL == m_ValueOrFunctions || index < 0 || index >= m_ValueOrFunctionNum || index >= m_MaxValueOrFunctionNum)
                return GetNullValueOrFunctionPtrRef();
            return m_ValueOrFunctions[index];
        }
    public:
        int GetFunctionNum(void)const { return m_ValueOrFunctionNum; }
        ValueOrFunctionData* GetFunction(int index)const
        {
            if (NULL == m_ValueOrFunctions || index < 0 || index >= m_ValueOrFunctionNum || index >= m_MaxValueOrFunctionNum)
                return 0;
            return m_ValueOrFunctions[index];
        }
        const char* GetFunctionId(int index)const
        {
            if (0 == m_ValueOrFunctions || index < 0 || index >= m_ValueOrFunctionNum || index >= m_MaxValueOrFunctionNum)
                return 0;
            return m_ValueOrFunctions[index]->GetId();
        }
    public:
        StatementData(IDslStringAndObjectBuffer& buffer);
        virtual ~StatementData(void)
        {
            ReleaseFunctions();
            ReleaseFirstComments(&m_Buffer, m_pCommentsInfo);
            ReleaseLastComments(&m_Buffer, m_pCommentsInfo);
        }
        void InitFunctionsCapacity(int c);
    protected:
        virtual IDslStringAndObjectBuffer* GetBuffer(void) const
        {
            return &m_Buffer;
        }
        virtual SyntaxComponentCommentsInfo* GetCommentsInfo(void) const
        {
            return m_pCommentsInfo;
        }
    private:
        StatementData(const StatementData&) = delete;
        StatementData& operator=(const StatementData&) = delete;
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
        virtual NullSyntax* GetNullSyntaxPtr(void) = 0;
        virtual FunctionData* GetNullFunctionPtr(void) = 0;
        virtual FunctionData*& GetNullFunctionPtrRef(void) = 0;
        virtual ValueOrFunctionData*& GetNullValueOrFunctionPtrRef(void) = 0;
    public:
        virtual ~IDslStringAndObjectBuffer(void) {}
    };

    /*
     * 实际的DSL预先分配缓冲区，这个类需要在堆上实例化（在栈上可能导致栈溢出），类本身使
     * 用数组来分配缓冲区。
     * 理想情况是所有相关类使用的内存都是预先分配的。
     */
    template<int MaxStringBufferSize = STRING_BUFFER_SIZE,
        int MaxObjectBufferSize = OBJECT_BUFFER_SIZE,
        int SyntaxComponentPoolSize = SYNTAXCOMPONENT_POOL_SIZE,
        int PtrPoolSize = PTR_POOL_SIZE,
        int PtrPoolFreeLinkSize = PTR_POOL_FREELINK_SIZE,
        int PtrPoolFreeLinkHeaderSize = PTR_POOL_FREELINK_HEADER_SIZE>
        class DslStringAndObjectBufferT : public IDslStringAndObjectBuffer
    {
        struct alignas(4) FreeLinkInfo
        {
            int m_PtrPoolIndex;
            int m_NextFreeLink;
        };
        typedef ISyntaxComponent* SyntaxComponentPtr;
    public:
        virtual DslOptions& GetOptions(void) { return m_Options; }
        virtual const DslOptions& GetOptions(void)const { return m_Options; }
    public:
        virtual char* AllocString(int len)
        {
            if (m_pUnusedStringPtr + len - m_pStringBuffer >= MaxStringBufferSize) {
                return 0;
            }
            char* p = m_pUnusedStringPtr;
            if (0 != p) {
                m_pUnusedStringPtr[len] = 0;
                m_pUnusedStringPtr += len + 1;
            }
            return p;
        }
        virtual char* AllocString(const char* src)
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
        virtual char* GetStringBuffer(void)const { return m_pStringBuffer; }
        virtual char*& GetUnusedStringPtrRef(void) { return m_pUnusedStringPtr; }
        virtual int GetUnusedStringLength(void)const
        {
            MyAssert(m_pStringBuffer);
            MyAssert(m_pUnusedStringRef);
            return MaxStringBufferSize - int(m_pUnusedStringPtr - m_pStringBuffer);
        }
    public:
        virtual SyntaxComponentCommentsInfo* NewSyntaxComponentCommentsInfo(void)
        {
            size_t size = sizeof(SyntaxComponentCommentsInfo);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            void* pMemory = m_pUnusedObjectPtr;
            m_pUnusedObjectPtr += size;
            SyntaxComponentCommentsInfo* p = new(pMemory) SyntaxComponentCommentsInfo();
            ++m_SyntaxComponentCommentsInfoNum;
            return p;
        }
        virtual FunctionCommentsInfo* NewFunctionCommentsInfo(void)
        {
            size_t size = sizeof(FunctionCommentsInfo);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            void* pMemory = m_pUnusedObjectPtr;
            m_pUnusedObjectPtr += size;
            FunctionCommentsInfo* p = new(pMemory) FunctionCommentsInfo();
            ++m_FunctionCommentsInfoNum;
            return p;
        }
    public:
        virtual ValueData* AddNewValueComponent(void)
        {
            size_t size = sizeof(ValueData);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            void* pMemory = m_pUnusedObjectPtr;
            m_pUnusedObjectPtr += size;
            ValueData* p = new(pMemory) ValueData();
            AddSyntaxComponent(p);
            return p;
        }
        virtual FunctionData* AddNewFunctionComponent(void)
        {
            size_t size = sizeof(FunctionData);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            void* pMemory = m_pUnusedObjectPtr;
            m_pUnusedObjectPtr += size;
            FunctionData* p = new(pMemory) FunctionData(*this);
            AddSyntaxComponent(p);
            return p;
        }
        virtual StatementData* AddNewStatementComponent(void)
        {
            size_t size = sizeof(StatementData);
            if (GetUnusedObjectLength() < static_cast<int>(size))
                return 0;
            void* pMemory = m_pUnusedObjectPtr;
            m_pUnusedObjectPtr += size;
            StatementData* p = new(pMemory) StatementData(*this);
            AddSyntaxComponent(p);
            return p;
        }
        virtual int GetUnusedObjectLength(void)const
        {
            MyAssert(m_pObjectBuffer);
            MyAssert(m_pUnusedObjectRef);
            return MaxObjectBufferSize - int(m_pUnusedObjectPtr - m_pObjectBuffer);
        }
    public:
        virtual void** NewPtrArray(int size)
        {
            if (size<0 || size>PTR_POOL_FREELINK_HEADER_SIZE)
                return 0;
            int ix = m_PtrFreeLinkHeader[size];
            if (ix >= 0) {
                //空闲链表上有的话就用空闲链表的数据，空闲链表头指向链表后一个元素，原链表头从链表拆除后放到空闲链表块的空闲链表中
                auto link = m_PtrFreeLink[ix];
                m_PtrFreeLinkHeader[size] = link.m_NextFreeLink;
                if (m_FreedFreeLinkHeader >= 0) {
                    m_PtrFreeLink[ix].m_NextFreeLink = m_FreedFreeLinkHeader;
                }
                else {
                    m_PtrFreeLink[ix].m_NextFreeLink = -1;
                }
                m_FreedFreeLinkHeader = ix;
            }
            if (m_PtrNum + size > PtrPoolSize)
                return 0;
            int start = m_PtrNum;
            m_PtrNum += size;
            return &(m_PtrPool[start]);
        }
        virtual void DeletePtrArray(void** ptr, int size)
        {
            if (size<0 || size>PTR_POOL_FREELINK_HEADER_SIZE)
                return;
            //分配一个新的空闲链表块来描述回收的数组，并加到空闲链表上
            int newFreeHeader = -1;
            FreeLinkInfo* p = 0;
            if (m_FreedFreeLinkHeader >= 0) {
                newFreeHeader = m_FreedFreeLinkHeader;
                p = &(m_PtrFreeLink[m_FreedFreeLinkHeader]);
                m_FreedFreeLinkHeader = p->m_NextFreeLink;
            }
            else if (m_FreeLinkNum < PtrPoolFreeLinkSize) {
                newFreeHeader = m_FreeLinkNum;
                p = &(m_PtrFreeLink[m_FreeLinkNum]);
                ++m_FreeLinkNum;
            }
            else {
                //这个块浪费掉了，需要调整空闲链表参数的大小
            }
            if (p) {
                p->m_PtrPoolIndex = (ptr - m_PtrPool);
                int ix = m_PtrFreeLinkHeader[size];
                if (ix >= 0) {
                    p->m_NextFreeLink = ix;
                }
                else {
                    p->m_NextFreeLink = -1;
                }
                m_PtrFreeLinkHeader[size] = newFreeHeader;
            }
        }
    public:
        virtual NullSyntax* GetNullSyntaxPtr(void)
        {
            return &m_NullSyntax;
        }
        virtual FunctionData* GetNullFunctionPtr(void)
        {
            m_NullFunction.GetName().SetInvalid();
            m_NullFunction.SetParamClass(FunctionData::PARAM_CLASS_NOTHING);
            m_NullFunction.ClearParams();
            return &m_NullFunction;
        }
        virtual FunctionData*& GetNullFunctionPtrRef(void)
        {
            auto fptr = m_pNullFunction;
            fptr->GetName().SetInvalid();
            fptr->SetParamClass(FunctionData::PARAM_CLASS_NOTHING);
            fptr->ClearParams();
            return m_pNullFunction;
        }
        virtual ValueOrFunctionData*& GetNullValueOrFunctionPtrRef(void)
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
            m_pObjectBuffer(m_ObjectBuffer),
            m_pUnusedObjectPtr(m_ObjectBuffer),
            m_NullSyntax(),
            m_NullFunction(*this),
            m_pNullFunction(&m_NullFunction),
            m_pNullValueOrFunction(&m_NullFunction)
        {
            memset(m_PtrPool, 0, sizeof(void*) * PtrPoolSize);
            m_PtrNum = 0;
            memset(m_PtrFreeLink, 0xff, sizeof(FreeLinkInfo) * PtrPoolFreeLinkSize);
            m_FreeLinkNum = 0;
            memset(m_PtrFreeLinkHeader, 0xff, sizeof(unsigned int) * PtrPoolFreeLinkHeaderSize);
            m_FreedFreeLinkHeader = -1;
        }
        void Reset(void)
        {
            m_SyntaxComponentNum = 0;
            m_SyntaxComponentCommentsInfoNum = 0;
            m_FunctionCommentsInfoNum = 0;
            m_pStringBuffer = m_StringBuffer;
            m_pUnusedStringPtr = m_StringBuffer;
            m_pObjectBuffer = m_ObjectBuffer;
            m_pUnusedObjectPtr = m_ObjectBuffer;
            m_pNullFunction = &m_NullFunction;

            memset(m_PtrPool, 0, sizeof(void*) * PtrPoolSize);
            m_PtrNum = 0;
            memset(m_PtrFreeLink, 0xff, sizeof(FreeLinkInfo) * PtrPoolFreeLinkSize);
            m_FreeLinkNum = 0;
            memset(m_PtrFreeLinkHeader, 0xff, sizeof(unsigned int) * PtrPoolFreeLinkHeaderSize);
            m_FreedFreeLinkHeader = -1;
        }
    private:
        void AddSyntaxComponent(ISyntaxComponent* p)
        {
            if (m_SyntaxComponentNum >= SyntaxComponentPoolSize || 0 == m_SyntaxComponentPool)
                return;
            m_SyntaxComponentPool[m_SyntaxComponentNum] = p;
            ++m_SyntaxComponentNum;
        }
    private:
        DslStringAndObjectBufferT(const DslStringAndObjectBufferT&) = delete;
        DslStringAndObjectBufferT& operator=(const DslStringAndObjectBufferT&) = delete;
    private:
        DslOptions m_Options;
    private:
        char m_StringBuffer[MaxStringBufferSize];
        char* m_pStringBuffer;
        char* m_pUnusedStringPtr;
    private:
        char m_ObjectBuffer[MaxObjectBufferSize];
        char* m_pObjectBuffer;
        char* m_pUnusedObjectPtr;
    private:
        SyntaxComponentPtr m_SyntaxComponentPool[SyntaxComponentPoolSize];
        int m_SyntaxComponentNum;
        int m_SyntaxComponentCommentsInfoNum;
        int m_FunctionCommentsInfoNum;
    private:
        void* m_PtrPool[PtrPoolSize];
        int m_PtrNum;
        FreeLinkInfo m_PtrFreeLink[PtrPoolFreeLinkSize];//低32位对应m_PtrPool的索引，高32位是下一个空闲块的索引
        int m_FreeLinkNum;
        int m_PtrFreeLinkHeader[PtrPoolFreeLinkHeaderSize];//以数组大小为索引的各size空闲链表头的位置
        int m_FreedFreeLinkHeader;//空闲的空闲块链表的头
    private:
        NullSyntax m_NullSyntax;
        FunctionData m_NullFunction;
        FunctionData* m_pNullFunction;
        ValueOrFunctionData* m_pNullValueOrFunction;
    };

    class IScriptSource;
    class DslFile
    {
        typedef ISyntaxComponent* SyntaxComponentPtr;
    public:
        int GetDslInfoNum(void)const { return m_DslInfoNum; }
        ISyntaxComponent* GetDslInfo(int index)const
        {
            if (index < 0 || index >= m_DslInfoNum)
                return NULL;
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
        void LoadBinaryFile(const char* file);
        void LoadBinaryCode(const char* buffer, int bufferSize);
        void SaveBinaryFile(const char* file) const;
    public:
        void SetStringDelimiter(const char* begin, const char* end);
        void SetScriptDelimiter(const char* begin, const char* end);
    private:
        DslFile(const DslFile&) = delete;
        DslFile& operator=(const DslFile&) = delete;
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
            if (index < 0 || index >= m_ErrorNum || index >= MAX_RECORD_ERROR_NUM)
                return "";
            return m_ErrorInfo[index];
        }
        char* NewErrorInfo(void)
        {
            m_HasError = TRUE;
            if (m_ErrorNum < MAX_RECORD_ERROR_NUM) {
                ++m_ErrorNum;
                return m_ErrorInfo[m_ErrorNum - 1];
            }
            else {
                return 0;
            }
        }
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
        NullSyntax* GetNullSyntaxPtr(void) const { return m_Buffer.GetNullSyntaxPtr(); }
        FunctionData* GetNullFunctionPtr(void) { return m_Buffer.GetNullFunctionPtr(); }
        FunctionData*& GetNullFunctionPtrRef(void) { return m_Buffer.GetNullFunctionPtrRef(); }
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
        char m_ErrorInfo[MAX_RECORD_ERROR_NUM][MAX_ERROR_INFO_CAPACITY];
        int m_ErrorNum;
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
                if (NULL != m_pSource) {
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
            int operator ==(const Iterator& other) const
            {
                return m_pSource == other.m_pSource && m_Iterator == other.m_Iterator && m_EndIterator == other.m_EndIterator;
            }
            int operator !=(const Iterator& other) const
            {
                return !(operator ==(other));
            }
        public:
            Iterator(void) :m_pSource(NULL), m_Iterator(""), m_EndIterator(m_Iterator)
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
using namespace Dsl;

#endif
