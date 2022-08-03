/*****************************************************************************

DslData.cpp

******************************************************************************/
#include "DslData.h"
#include "DslUtility.h"
#include "SourceCodeScript.h"
#include "tsnprintf.h"

#if defined(__LINUX__)
#include <ctype.h>
#endif

namespace DslData
{
    ISyntaxComponent::ISyntaxComponent(int syntaxType) :m_SyntaxType(syntaxType)
    {
    }
    ISyntaxComponent::~ISyntaxComponent(void)
    {
    }
    void ISyntaxComponent::CopyFrom(const ISyntaxComponent& other)
    {
        CopyFirstComments(other);
        CopyLastComments(other);
    }
    void ISyntaxComponent::ReleaseFirstComments(SyntaxComponentCommentsInfo* pCommentsInfo)
    {
        if (0 != pCommentsInfo) {
            pCommentsInfo->m_FirstComments.clear();
        }
    }
    void ISyntaxComponent::ReleaseLastComments(SyntaxComponentCommentsInfo* pCommentsInfo)
    {
        if (0 != pCommentsInfo) {
            pCommentsInfo->m_LastComments.clear();
        }
    }
    //------------------------------------------------------------------------------------------------------
    ValueData::~ValueData()
    {
        SetInvalid();
    }
    void ValueData::Release(void)
    {
        if (nullptr != m_FunctionVal) {
            delete m_FunctionVal;
            m_FunctionVal = nullptr;
        }
    }
    void ValueData::CopyFrom(const ValueData& other)
    {
        if (other.m_Type == VALUE_TYPE_FUNCTION) {
            if (nullptr != other.m_FunctionVal) {
                SetFunctionCopyFrom(*other.m_FunctionVal);
            }
            else {
                SetFunction();
            }
        }
        else {
            m_Type = other.m_Type;
            m_StringVal = other.m_StringVal;
        }
        m_Line = other.m_Line;
    }
    FunctionData* ValueData::SetFunction(void)
    {
        m_Type = VALUE_TYPE_FUNCTION;
        if (nullptr == m_FunctionVal)
            m_FunctionVal = new FunctionData();
        m_StringVal.clear();
        return m_FunctionVal;
    }
    FunctionData* ValueData::SetFunctionCopyFrom(const FunctionData& other)
    {
        auto* p = SetFunction();
        p->CopyFrom(other);
        return p;
    }
    bool ValueData::IsValid(void)const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (nullptr != m_FunctionVal)
                return m_FunctionVal->IsValid();
            else
                return false;
        }
        return HaveId();
    }
    int ValueData::GetIdType(void)const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (nullptr != m_FunctionVal)
                return m_FunctionVal->GetIdType();
            else
                return VALUE_TYPE_IDENTIFIER;
        }
        return m_Type;
    }
    const std::string& ValueData::GetId(void)const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (nullptr != m_FunctionVal)
                return m_FunctionVal->GetId();
            else
                return ISyntaxComponent::EmptyString();
        }
        return m_StringVal;
    }
    int ValueData::GetLine(void)const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (nullptr != m_FunctionVal)
                return m_FunctionVal->GetLine();
            else
                return m_Line;
        }
        return m_Line;
    }
    bool ValueData::HaveId(void)const
    {
        if (m_Type == VALUE_TYPE_FUNCTION) {
            if (nullptr != m_FunctionVal)
                return m_FunctionVal->HaveId();
            else
                return false;
        }
        return !m_StringVal.empty();
    }
    //------------------------------------------------------------------------------------------------------
    static inline int CalcCapacity(int need, int init, int max_delta)
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
    FunctionData::FunctionData(void) :ValueOrFunctionData(ISyntaxComponent::TYPE_FUNCTION),
        m_Params(0),
        m_ParamClass(PARAM_CLASS_NOTHING)
    {
        if (DslFile::DontLoadComments()) {
            m_pCommentsInfo = nullptr;
        }
        else {
            m_pCommentsInfo = new FunctionCommentsInfo();
        }
    }

    FunctionData::~FunctionData(void)
    {
        ReleaseParams();
        ReleaseComments();
        ReleaseFirstComments(m_pCommentsInfo);
        ReleaseLastComments(m_pCommentsInfo);
        if (nullptr != m_pCommentsInfo) {
            delete m_pCommentsInfo;
            m_pCommentsInfo = nullptr;
        }
    }

    void FunctionData::CopyFrom(const FunctionData& other)
    {
        ISyntaxComponent::CopyFrom(other);
        m_Name = other.m_Name;
        m_ParamClass = other.m_ParamClass;
        ClearParams();
        for (auto* p : other.m_Params) {
            switch (p->GetSyntaxType()) {
            case ISyntaxComponent::TYPE_VALUE: {
                auto* pp = AddValueParam();
                *pp = *static_cast<ValueData*>(p);
            }break;
            case ISyntaxComponent::TYPE_FUNCTION: {
                auto* pp = AddFunctionParam();
                pp->CopyFrom(*static_cast<FunctionData*>(p));
            }break;
            case ISyntaxComponent::TYPE_STATEMENT: {
                auto* pp = AddStatementParam();
                pp->CopyFrom(*static_cast<StatementData*>(p));
            }break;
            }
        }
        if (m_pCommentsInfo && other.m_pCommentsInfo) {
            ClearFirstComments();
            ClearLastComments();
            ClearComments();
            CopyComments(other);
            for (auto& str : other.m_pCommentsInfo->m_Comments) {
                m_pCommentsInfo->m_Comments.push_back(str);
            }
        }
    }

    void FunctionData::InitParamsCapacity(int v)
    {
        if (v >= 0)
            m_Params.reserve(static_cast<size_t>(v));
    }

    NullSyntax& FunctionData::GetNullSyntax(void)const
    {
        return DslFile::GetNullSyntax();
    }

    FunctionData& FunctionData::GetNullFunction(void)const
    {
        return DslFile::GetNullFunction();
    }

    void FunctionData::ReleaseParams(void)
    {
        for (auto* ptr : m_Params) {
            delete ptr;
        }
        m_Params.clear();
    }

    void FunctionData::ReleaseComments(void)
    {
        if (nullptr == m_pCommentsInfo)
            return;
        m_pCommentsInfo->m_Comments.clear();
    }

    void FunctionData::ClearParams(void)
    {
        ReleaseParams();
    }

    ValueData* FunctionData::AddValueParam(void)
    {
        auto* p = new ValueData();
        m_Params.push_back(p);
        return p;
    }

    FunctionData* FunctionData::AddFunctionParam(void)
    {
        auto* p = new FunctionData();
        m_Params.push_back(p);
        return p;
    }

    StatementData* FunctionData::AddStatementParam(void)
    {
        auto* p = new StatementData();
        m_Params.push_back(p);
        return p;
    }

    ISyntaxComponent* FunctionData::AddParamCopyFrom(const ISyntaxComponent& other)
    {
        switch (other.GetSyntaxType()) {
        case ISyntaxComponent::TYPE_VALUE: {
            auto* p = AddValueParam();
            *p = static_cast<const ValueData&>(other);
            return p;
        }
        case ISyntaxComponent::TYPE_FUNCTION: {
            auto* p = AddFunctionParam();
            p->CopyFrom(static_cast<const FunctionData&>(other));
            return p;
        }
        case ISyntaxComponent::TYPE_STATEMENT: {
            auto* p = AddStatementParam();
            p->CopyFrom(static_cast<const StatementData&>(other));
            return p;
        }
        }
        return nullptr;
    }

    StatementData::StatementData(void) :ISyntaxComponent(ISyntaxComponent::TYPE_STATEMENT),
        m_ValueOrFunctions(0)
    {
        if (DslFile::DontLoadComments()) {
            m_pCommentsInfo = nullptr;
        }
        else {
            m_pCommentsInfo = new SyntaxComponentCommentsInfo();
        }
    }

    StatementData::~StatementData(void)
    {
        ReleaseFunctions();
        ReleaseFirstComments(m_pCommentsInfo);
        ReleaseLastComments(m_pCommentsInfo);
        if (nullptr != m_pCommentsInfo) {
            delete m_pCommentsInfo;
            m_pCommentsInfo = nullptr;
        }
    }

    void StatementData::CopyFrom(const StatementData& other)
    {
        ISyntaxComponent::CopyFrom(other);
        ClearFunctions();
        for (auto* p : other.m_ValueOrFunctions) {
            switch (p->GetSyntaxType()) {
            case ISyntaxComponent::TYPE_VALUE: {
                auto* pp = AddValue();
                *pp = *static_cast<ValueData*>(p);
            }break;
            case ISyntaxComponent::TYPE_FUNCTION: {
                auto* pp = AddFunction();
                pp->CopyFrom(*static_cast<FunctionData*>(p));
            }break;
            }
        }
        if (m_pCommentsInfo && other.m_pCommentsInfo) {
            ClearFirstComments();
            ClearLastComments();
            CopyComments(other);
        }
    }

    void StatementData::InitFunctionsCapacity(int v)
    {
        if (v >= 0)
            m_ValueOrFunctions.reserve(static_cast<size_t>(v));
    }

    void StatementData::ReleaseFunctions(void)
    {
        for (auto* ptr : m_ValueOrFunctions) {
            delete ptr;
        }
        m_ValueOrFunctions.clear();
    }
    ValueOrFunctionData& StatementData::GetNullValueOrFunction(void)const
    {
        return DslFile::GetNullFunction();
    }

    void StatementData::ClearFunctions(void)
    {
        ReleaseFunctions();
    }
    ValueData* StatementData::AddValue(void)
    {
        auto* p = new ValueData();
        m_ValueOrFunctions.push_back(p);
        return p;
    }
    FunctionData* StatementData::AddFunction(void)
    {
        auto* p = new FunctionData();
        m_ValueOrFunctions.push_back(p);
        return p;
    }
    ValueOrFunctionData* StatementData::AddValueOrFunctionCopyFrom(const ValueOrFunctionData& other)
    {
        switch (other.GetSyntaxType()) {
        case ISyntaxComponent::TYPE_VALUE: {
            auto* p = AddValue();
            *p = static_cast<const ValueData&>(other);
            return p;
        }
        case ISyntaxComponent::TYPE_FUNCTION: {
            auto* p = AddFunction();
            p->CopyFrom(static_cast<const FunctionData&>(other));
            return p;
        }
        }
        return nullptr;
    }

    bool DslFile::Mac2Unix(char* buf, int len)
    {
        return DslParser::Mac2Unix(buf, len);
    }
    NullSyntax& DslFile::GetNullSyntax(void)
    {
        static NullSyntax s_Null;
        return s_Null;
    }
    FunctionData& DslFile::GetNullFunction(void)
    {
        static FunctionData s_Null;
        return s_Null;
    }

    DslFile::DslFile(void) :m_DslInfos(0), m_HasError(false), 
        m_StringBeginDelimiter("\""), m_StringEndDelimiter("\""), m_ScriptBeginDelimiter("{:"), m_ScriptEndDelimiter(":}")
    {
    }

    DslFile::~DslFile(void)
    {
        Release();
    }

    void DslFile::Reset(void)
    {
        Release();
        Init();
    }

    void DslFile::Init(void)
    {
        m_HasError = false;
        SetStringDelimiter("\"", "\"");
        SetScriptDelimiter("{:", ":}");
    }

    void DslFile::Release(void)
    {
        ClearErrorInfo();
        for (auto* ptr : m_DslInfos) {
            delete ptr;
        }
        m_DslInfos.clear();
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

    ValueData* DslFile::AddValue(void)
    {
        auto* p = new ValueData();
        m_DslInfos.push_back(p);
        return p;
    }

    FunctionData* DslFile::AddFunction(void)
    {
        auto* p = new FunctionData();
        m_DslInfos.push_back(p);
        return p;
    }

    StatementData* DslFile::AddStatement(void)
    {
        auto* p = new StatementData();
        m_DslInfos.push_back(p);
        return p;
    }

    ISyntaxComponent* DslFile::AddDslCopyFrom(const ISyntaxComponent& other)
    {
        switch (other.GetSyntaxType()) {
        case ISyntaxComponent::TYPE_VALUE: {
            auto* p = AddValue();
            *p = static_cast<const ValueData&>(other);
            return p;
        }
        case ISyntaxComponent::TYPE_FUNCTION: {
            auto* p = AddFunction();
            p->CopyFrom(static_cast<const FunctionData&>(other));
            return p;
        }
        case ISyntaxComponent::TYPE_STATEMENT: {
            auto* p = AddStatement();
            p->CopyFrom(static_cast<const StatementData&>(other));
            return p;
        }
        }
        return nullptr;
    }

    void DslFile::LoadBinaryCode(const char* buffer, int bufferSize, std::vector<std::string>& reuseKeyBuffer, std::vector<std::string>& reuseIdBuffer)
    {
        DslFileReadWrite::readBinary(*this, buffer, bufferSize, reuseKeyBuffer, reuseIdBuffer);
    }
    void DslFile::SaveBinaryFile(FILE* fp) const
    {
#if FULL_VERSION
        DslFileReadWrite::writeBinary(fp, *this);
#endif
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