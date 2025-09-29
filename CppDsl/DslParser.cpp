/*****************************************************************************

Dsl.cpp

******************************************************************************/
#include "DslParser.h"
#include "DslUtility.h"
#include "SourceCodeScript.h"
#include "tsnprintf.h"

#if defined(__LINUX__)
#include <ctype.h>
#endif

#define GET_PRODUCTION_NAME    SlkGetProductionName
#define GET_SYMBOL_NAME        SlkGetSymbolName

namespace DslParser
{
    ISyntaxComponent::ISyntaxComponent(int syntaxType) :m_SyntaxType(syntaxType), m_Separator(IDslSyntaxCommon::SEPARATOR_NOTHING)
    {
    }
    ISyntaxComponent::~ISyntaxComponent()
    {
    }
    void ISyntaxComponent::CopyFrom(const ISyntaxComponent& other)
    {
        m_Separator = other.m_Separator;
        auto pBuffer = GetBuffer();
        if (0 != pBuffer && 0 != GetCommentsInfo() && 0 != other.GetCommentsInfo()) {
            GetCommentsInfo()->m_FirstCommentNum = other.GetCommentsInfo()->m_FirstCommentNum;
            GetCommentsInfo()->m_FirstCommentSpace = other.GetCommentsInfo()->m_FirstCommentSpace;
            if (GetCommentsInfo()->m_FirstCommentSpace > 0) {
                GetCommentsInfo()->m_FirstComments = (const char**)(pBuffer->NewPtrArray(GetCommentsInfo()->m_FirstCommentSpace));
                memcpy(GetCommentsInfo()->m_FirstComments, other.GetCommentsInfo()->m_FirstComments, GetCommentsInfo()->m_FirstCommentNum * sizeof(const char*));
            }
            else {
                GetCommentsInfo()->m_FirstComments = 0;
            }
            GetCommentsInfo()->m_LastCommentNum = other.GetCommentsInfo()->m_LastCommentNum;
            GetCommentsInfo()->m_LastCommentSpace = other.GetCommentsInfo()->m_LastCommentSpace;
            if (GetCommentsInfo()->m_LastCommentSpace > 0) {
                GetCommentsInfo()->m_LastComments = (const char**)(pBuffer->NewPtrArray(GetCommentsInfo()->m_LastCommentSpace));
                memcpy(GetCommentsInfo()->m_LastComments, other.GetCommentsInfo()->m_LastComments, GetCommentsInfo()->m_LastCommentNum * sizeof(const char*));
            }
            else {
                GetCommentsInfo()->m_LastComments = 0;
            }
        }
    }
    void ISyntaxComponent::PrepareFirstComments()
    {
        auto pBuffer = GetBuffer();
        if (0 != pBuffer && 0 != GetCommentsInfo()) {
            if (GetCommentsInfo()->m_FirstCommentNum >= GetCommentsInfo()->m_FirstCommentSpace) {
                int newSpace = GetCommentsInfo()->m_FirstCommentSpace + DELTA_COMMENT;
                const char** pNew = (const char**)(pBuffer->NewPtrArray(newSpace));
                if (pNew) {
                    if (nullptr != GetCommentsInfo()->m_FirstComments) {
                        memcpy(pNew, GetCommentsInfo()->m_FirstComments, GetCommentsInfo()->m_FirstCommentNum * sizeof(const char*));
                        memset(pNew + GetCommentsInfo()->m_FirstCommentNum, 0, DELTA_COMMENT * sizeof(const char*));
                        pBuffer->DeletePtrArray((void**)GetCommentsInfo()->m_FirstComments, GetCommentsInfo()->m_FirstCommentSpace);
                    }
                    GetCommentsInfo()->m_FirstComments = pNew;
                    GetCommentsInfo()->m_FirstCommentSpace = newSpace;
                }
            }
        }
    }
    void ISyntaxComponent::ReleaseFirstComments(IDslStringAndObjectBuffer* pBuffer, SyntaxComponentCommentsInfo* pCommentsInfo)
    {
        if (0 != pBuffer && 0 != pCommentsInfo) {
            if (nullptr != pCommentsInfo->m_FirstComments) {
                pBuffer->DeletePtrArray((void**)pCommentsInfo->m_FirstComments, pCommentsInfo->m_FirstCommentSpace);
                pCommentsInfo->m_FirstComments = nullptr;
            }
        }
    }
    void ISyntaxComponent::PrepareLastComments()
    {
        auto pBuffer = GetBuffer();
        if (0 != pBuffer && 0 != GetCommentsInfo()) {
            if (GetCommentsInfo()->m_LastCommentNum >= GetCommentsInfo()->m_LastCommentSpace) {
                int newSpace = GetCommentsInfo()->m_LastCommentSpace + DELTA_COMMENT;
                const char** pNew = (const char**)(pBuffer->NewPtrArray(newSpace));
                if (pNew) {
                    if (nullptr != GetCommentsInfo()->m_LastComments) {
                        memcpy(pNew, GetCommentsInfo()->m_LastComments, GetCommentsInfo()->m_LastCommentNum * sizeof(const char*));
                        memset(pNew + GetCommentsInfo()->m_LastCommentNum, 0, DELTA_COMMENT * sizeof(const char*));
                        pBuffer->DeletePtrArray((void**)GetCommentsInfo()->m_LastComments, GetCommentsInfo()->m_LastCommentSpace);
                    }
                    GetCommentsInfo()->m_LastComments = pNew;
                    GetCommentsInfo()->m_LastCommentSpace = newSpace;
                }
            }
        }
    }
    void ISyntaxComponent::ReleaseLastComments(IDslStringAndObjectBuffer* pBuffer, SyntaxComponentCommentsInfo* pCommentsInfo)
    {
        if (0 != pBuffer && 0 != pCommentsInfo) {
            if (nullptr != pCommentsInfo->m_LastComments) {
                pBuffer->DeletePtrArray((void**)pCommentsInfo->m_LastComments, pCommentsInfo->m_LastCommentSpace);
                pCommentsInfo->m_LastComments = nullptr;
            }
        }
    }
    //------------------------------------------------------------------------------------------------------
    int ValueData::IsValid()const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->IsValid();
            else
                return FALSE;
        }
        return HaveId();
    }
    int ValueData::GetIdType()const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->GetIdType();
            else
                return VALUE_TYPE_IDENTIFIER;
        }
        return m_Type;
    }
    const char* ValueData::GetId()const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->GetId();
            else
                return "";
        }
        if (m_StringVal)
            return m_StringVal;
        return "";
    }
    int ValueData::GetLine()const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->GetLine();
            else
                return m_Line;
        }
        return m_Line;
    }
    int ValueData::HaveId()const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->HaveId();
            else
                return FALSE;
        }
        return 0 != m_StringVal ? TRUE : FALSE;
    }
    //------------------------------------------------------------------------------------------------------
    static inline int CalcCapacity(int need, [[maybe_unused]] int init, int max_delta)
    {
        if (need <= 0) {
            return 0;
        }
        else if (need < max_delta) {
            int v = max_delta;
            int v_div_2 = v / 2;
            while (need <= v_div_2) {
                v = v_div_2;
                v_div_2 /= 2;
            }
            need = v;
        }
        else {
            int mod = need % max_delta;
            if (mod != 0) {
                need += max_delta - mod;
            }
        }
        return need;
    }
    //------------------------------------------------------------------------------------------------------
    FunctionData::FunctionData(IDslStringAndObjectBuffer& buffer) :ValueOrFunctionData(ISyntaxComponent::TYPE_FUNCTION),
        m_Buffer(buffer),
        m_Params(0),
        m_ParamNum(0),
        m_ParamSpace(0),
        m_ParamClass(PARAM_CLASS_NOTHING)
    {
        if (DslOptions::DontLoadComments()) {
            m_pCommentsInfo = 0;
        }
        else {
            m_pCommentsInfo = buffer.NewFunctionCommentsInfo();
        }

        const DslOptions& options = buffer.GetOptions();
        m_MaxParamNum = options.GetMaxParamNum();
    }

    FunctionData::~FunctionData()
    {
        ReleaseParams();
        ReleaseComments();
        ReleaseFirstComments(&m_Buffer, m_pCommentsInfo);
        ReleaseLastComments(&m_Buffer, m_pCommentsInfo);
    }

    int FunctionData::GetLine()const
    {
        if(HaveId())
            return m_Name.GetLine();
        else {
            for (int ix = 0; ix < GetParamNum(); ++ix) {
                auto* p = GetParam(ix);
                if (nullptr != p) {
                    int line = p->GetLine();
                    if (line >= 0)
                        return line;
                }
            }
            return -1;
        }
    }

    ISyntaxComponent* FunctionData::GetNullSyntaxPtr()const
    {
        return m_Buffer.GetNullSyntaxPtr();
    }

    FunctionData* FunctionData::GetNullFunctionPtr()const
    {
        return m_Buffer.GetNullFunctionPtr();
    }

    void FunctionData::InitParamsCapacity(int c)
    {
        if (nullptr == m_Params && TRUE == HaveParamOrStatement()) {
            if (HaveStatement()) {
                c = CalcCapacity(c, INIT_FUNCTION_PARAM, MAX_DELTA_FUNCTION_STATEMENT);
            }
            else {
                c = CalcCapacity(c, INIT_FUNCTION_PARAM, MAX_DELTA_FUNCTION_PARAM);
            }
            if (c > 0) {
                m_Params = (SyntaxComponentPtr*)(m_Buffer.NewPtrArray(c));
                if (m_Params) {
                    m_ParamSpace = c;
                }
            }
        }
    }

    void FunctionData::PrepareParams()
    {
        if (nullptr == m_Params && TRUE == HaveParamOrStatement()) {
            m_Params = (SyntaxComponentPtr*)(m_Buffer.NewPtrArray(INIT_FUNCTION_PARAM));
            if (m_Params) {
                m_ParamSpace = INIT_FUNCTION_PARAM;
            }
        }
        else if (HaveParamOrStatement() && m_ParamNum >= m_ParamSpace) {
            int delta = m_ParamSpace;
            if (HaveStatement()) {
                if (delta > MAX_DELTA_FUNCTION_STATEMENT)
                    delta = MAX_DELTA_FUNCTION_STATEMENT;
            }
            else {
                if (delta > MAX_DELTA_FUNCTION_PARAM)
                    delta = MAX_DELTA_FUNCTION_PARAM;
            }
            int newSpace = m_ParamSpace + delta;
            if (newSpace <= m_MaxParamNum) {
                SyntaxComponentPtr* pNew = (SyntaxComponentPtr*)(m_Buffer.NewPtrArray(newSpace));
                if (pNew && m_Params) {
                    memcpy(pNew, m_Params, m_ParamNum * sizeof(SyntaxComponentPtr));
                    memset(pNew + m_ParamNum, 0, delta * sizeof(SyntaxComponentPtr));
                    m_Buffer.DeletePtrArray((void**)m_Params, m_ParamSpace);
                    m_Params = pNew;
                    m_ParamSpace = newSpace;
                }
            }
        }
    }

    void FunctionData::ReleaseParams()
    {
        if (nullptr != m_Params) {
            m_Buffer.DeletePtrArray((void**)m_Params, m_ParamSpace);
            m_Params = nullptr;
        }
    }

    void FunctionData::PrepareComments()
    {
        auto p = m_pCommentsInfo;
        if (0 == p)
            return;
        if (p->m_CommentNum >= p->m_CommentSpace) {
            int newSpace = p->m_CommentSpace + DELTA_COMMENT;
            const char** pNew = (const char**)(m_Buffer.NewPtrArray(newSpace));
            if (pNew) {
                memcpy(pNew, p->m_Comments, p->m_CommentNum * sizeof(const char*));
                memset(pNew + p->m_CommentNum, 0, DELTA_COMMENT * sizeof(const char*));
                m_Buffer.DeletePtrArray((void**)p->m_Comments, p->m_CommentSpace);
                p->m_Comments = pNew;
                p->m_CommentSpace = newSpace;
            }
        }
    }

    void FunctionData::ReleaseComments()
    {
        auto p = m_pCommentsInfo;
        if (0 == p)
            return;
        if (nullptr != p->m_Comments) {
            m_Buffer.DeletePtrArray((void**)p->m_Comments, p->m_CommentSpace);
            p->m_Comments = nullptr;
        }
    }

    StatementData::StatementData(IDslStringAndObjectBuffer& buffer) :ISyntaxComponent(ISyntaxComponent::TYPE_STATEMENT),
        m_Buffer(buffer),
        m_ValueOrFunctions(0),
        m_ValueOrFunctionNum(0),
        m_ValueOrFunctionSpace(0)
    {
        if (DslOptions::DontLoadComments()) {
            m_pCommentsInfo = 0;
        }
        else {
            m_pCommentsInfo = buffer.NewSyntaxComponentCommentsInfo();
        }

        const DslOptions& options = buffer.GetOptions();
        m_MaxValueOrFunctionNum = options.GetMaxFunctionDimensionNum();
    }

    ValueOrFunctionData*& StatementData::GetNullValueOrFunctionPtrRef()const
    {
        return m_Buffer.GetNullValueOrFunctionPtrRef();
    }

    int StatementData::GetLine()const
    {
        for (int ix = 0; ix < GetFunctionNum(); ++ix) {
            auto* p = GetFunction(ix);
            if (nullptr != p) {
                int line = p->GetLine();
                if (line >= 0)
                    return line;
            }
        }
        return -1;
    }

    void StatementData::InitFunctionsCapacity(int c)
    {
        if (nullptr == m_ValueOrFunctions) {
            c = CalcCapacity(c, INIT_STATEMENT_FUNCTION, MAX_DELTA_STATEMENT_FUNCTION);
            m_ValueOrFunctions = (ValueOrFunctionData**)(m_Buffer.NewPtrArray(c));
            if (m_ValueOrFunctions) {
                m_ValueOrFunctionSpace = c;
            }
        }
    }

    void StatementData::PrepareFunctions()
    {
        if (nullptr == m_ValueOrFunctions) {
            m_ValueOrFunctions = (ValueOrFunctionData**)(m_Buffer.NewPtrArray(INIT_STATEMENT_FUNCTION));
            if (m_ValueOrFunctions) {
                m_ValueOrFunctionSpace = INIT_STATEMENT_FUNCTION;
            }
        }
        else if (m_ValueOrFunctionNum >= m_ValueOrFunctionSpace) {
            int delta = m_ValueOrFunctionSpace;
            if (delta > MAX_DELTA_STATEMENT_FUNCTION)
                delta = MAX_DELTA_STATEMENT_FUNCTION;
            int newSpace = m_ValueOrFunctionSpace + delta;
            if (newSpace <= m_MaxValueOrFunctionNum) {
                ValueOrFunctionData** pNew = (ValueOrFunctionData**)(m_Buffer.NewPtrArray(newSpace));
                if (pNew) {
                    memcpy(pNew, m_ValueOrFunctions, m_ValueOrFunctionNum * sizeof(ValueOrFunctionData*));
                    memset(pNew + m_ValueOrFunctionNum, 0, delta * sizeof(ValueOrFunctionData*));
                    m_Buffer.DeletePtrArray((void**)m_ValueOrFunctions, m_ValueOrFunctionSpace);
                    m_ValueOrFunctions = pNew;
                    m_ValueOrFunctionSpace = newSpace;
                }
            }
        }
    }

    void StatementData::ReleaseFunctions()
    {
        if (nullptr != m_ValueOrFunctions) {
            m_Buffer.DeletePtrArray((void**)m_ValueOrFunctions, m_ValueOrFunctionSpace);
            m_ValueOrFunctions = nullptr;
        }
    }

    bool DslFile::Mac2Unix(char* buf, int len)
    {
        return DslParser::Mac2Unix(buf, len);
    }

    DslFile::DslFile(IDslStringAndObjectBuffer& buffer) :m_Buffer(buffer), m_IsDebugInfoEnable(FALSE),
        m_DslInfos(nullptr), 
        m_NullableSyntaxEnabled(true),
        m_StringBeginDelimiter("\""),
        m_StringEndDelimiter("\""),
        m_ScriptBeginDelimiter("{:"),
        m_ScriptEndDelimiter(":}")
    {
        Init();
        ClearErrorInfo();
    }

    DslFile::~DslFile()
    {
        Release();
    }

    void DslFile::Reset()
    {
        Release();
        Init();
    }

    void DslFile::Parse(const char* buf)
    {
        DslParser::Parse(buf, *this);
    }

    void DslFile::Parse(IScriptSource& source)
    {
        DslParser::Parse(source, *this);
    }

    void DslFile::ParseGpp(const char* buf)
    {
        int len = 0;
        DslParser::ParseGpp(buf, *this, 0, 0, 0, len);
    }

    void DslFile::ParseGpp(const char* buf, const char* beginDelim, const char* endDelim)
    {
        int len = 0;
        DslParser::ParseGpp(buf, *this, beginDelim, endDelim, 0, len);
    }

    void DslFile::ParseGpp(const char* buf, const char* beginDelim, const char* endDelim, char* gppBuf, int& len)
    {
        DslParser::ParseGpp(buf, *this, beginDelim, endDelim, gppBuf, len);
    }

    void DslFile::AddDslInfo(ISyntaxComponent* p)
    {
        if (nullptr == p || m_DslInfoNum < 0 || m_DslInfoNum >= m_MaxDslInfoNum)
            return;
        PrepareDslInfos();
        if (nullptr == m_DslInfos || m_DslInfoNum >= m_DslInfoSpace)
            return;
        m_DslInfos[m_DslInfoNum] = p;
        ++m_DslInfoNum;
    }

    void DslFile::PrepareDslInfos()
    {
        if (nullptr == m_DslInfos) {
            m_DslInfos = (ISyntaxComponent**)(m_Buffer.NewPtrArray(INIT_DSL_INFO));
            if (m_DslInfos) {
                m_DslInfoSpace = INIT_DSL_INFO;
            }
        }
        else if (m_DslInfoNum >= m_DslInfoSpace) {
            int delta = m_DslInfoSpace;
            if (delta > MAX_DELTA_DSL_INFO)
                delta = MAX_DELTA_DSL_INFO;
            int newSpace = m_DslInfoSpace + delta;
            if (newSpace <= m_MaxDslInfoNum) {
                ISyntaxComponent** pNew = (ISyntaxComponent**)(m_Buffer.NewPtrArray(newSpace));
                if (pNew) {
                    memcpy(pNew, m_DslInfos, m_DslInfoNum * sizeof(ISyntaxComponent*));
                    memset(pNew + m_DslInfoNum, 0, delta * sizeof(ISyntaxComponent*));
                    m_Buffer.DeletePtrArray((void**)m_DslInfos, m_DslInfoSpace);
                    m_DslInfos = pNew;
                    m_DslInfoSpace = newSpace;
                }
            }
        }
    }
    void DslFile::ReleaseDslInfos()
    {
        if (nullptr != m_DslInfos) {
            m_Buffer.DeletePtrArray((void**)m_DslInfos, m_DslInfoSpace);
            m_DslInfos = nullptr;
        }
    }

    void DslFile::LoadBinaryCode(const char* buffer, int bufferSize, std::vector<const char*>& reuseKeyBuffer, std::vector<const char*>& reuseIdBuffer)
    {
        DslFileReadWrite::readBinary(*this, buffer, bufferSize, reuseKeyBuffer, reuseIdBuffer);
    }
    void DslFile::SaveBinaryFile(FILE* fp) const
    {
#if FULL_VERSION
        DslFileReadWrite::writeBinary(fp, *this);
#endif
    }

    void DslFile::SetNullableSyntax(bool enabled)
    {
        m_NullableSyntaxEnabled = enabled;
    }
    void DslFile::SetStringDelimiter(const char* begin, const char* end)
    {
        m_StringBeginDelimiter = begin;
        m_StringEndDelimiter = end;
    }
    void DslFile::SetScriptDelimiter(const char* begin, const char* end)
    {
        m_ScriptBeginDelimiter = begin;
        m_ScriptEndDelimiter = end;
    }

    void DslFile::Init()
    {
        m_DslInfos = 0;
        m_DslInfoNum = 0;
        m_DslInfoSpace = 0;
        m_MaxDslInfoNum = m_Buffer.GetOptions().GetMaxDslInfoNum();
    }
    void DslFile::Release()
    {
        ReleaseDslInfos();
    }

    void DslFile::ClearErrorInfo()
    {
        m_HasError = FALSE;
        m_ErrorNum = 0;
        m_Buffer.ZeroErrorInfoBuffer();
    }
    void DslFile::AddError(const char* error)
    {
        char* p = NewErrorInfo();
        if (p)
            tsnprintf(p, m_Buffer.GetSingleErrorInfoCapacity(), "%s", error);
    }
    //------------------------------------------------------------------------------------------------------------------------------------
    void ISyntaxComponent::WriteFirstCommentsToFile(FILE* fp, int indent, int firstLineNoIndent) const
    {
#if FULL_VERSION
        DslFileReadWrite::WriteFirstCommentsToFile(fp, indent, firstLineNoIndent, *this);
#endif
    }
    void ISyntaxComponent::WriteLastCommentsToFile(FILE* fp, int indent, int isLastOfStatement) const
    {
#if FULL_VERSION
        DslFileReadWrite::WriteLastCommentsToFile(fp, indent, isLastOfStatement, *this);
#endif
    }
    void ValueData::WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim)const
    {
#if FULL_VERSION
        DslFileReadWrite::WriteValueToFile(fp, indent, firstLineNoIndent, isLastOfStatement, delim, *this);
#endif
    }
    void FunctionData::WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim)const
    {
#if FULL_VERSION
        DslFileReadWrite::WriteFunctionToFile(fp, indent, firstLineNoIndent, isLastOfStatement, delim, *this);
#endif
    }
    void StatementData::WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfo& delim)const
    {
#if FULL_VERSION
        DslFileReadWrite::WriteStatementToFile(fp, indent, firstLineNoIndent, isLastOfStatement, delim, *this);
#endif
    }
    void DslFile::WriteToFile(FILE* fp, int indent)const
    {
#if FULL_VERSION
        DslFileReadWrite::WriteDslToFile(fp, indent, *this);
#endif
    }
    //------------------------------------------------------------------------------------------------------------------------------------
    
}