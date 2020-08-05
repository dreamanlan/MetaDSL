/*****************************************************************************

Dsl.cpp

******************************************************************************/
#include "Dsl.h"
#include "SourceCodeScript.h"
#include "tsnprintf.h"

#if defined(__LINUX__)
#include <ctype.h>
#endif

#define GET_PRODUCTION_NAME    SlkGetProductionName
#define GET_SYMBOL_NAME        SlkGetSymbolName

namespace Dsl
{
    enum DslBinaryCode
    {
        BinCode_BeginStatement = 1,
        BinCode_EndStatement,
        BinCode_BeginFunction,
        BinCode_EndFunction,
        BinCode_BeginValue,
        BinCode_EndValue,
        BinCode_ValueTypeBegin,
        BinCode_ValueTypeEnd = BinCode_ValueTypeBegin + ValueData::TYPE_MAX,
        BinCode_ParamOrExternClassBegin
    };
    ISyntaxComponent::ISyntaxComponent(int syntaxType) :m_SyntaxType(syntaxType),
        m_FirstComments(0), m_FirstCommentNum(0), m_FirstCommentSpace(0), m_FirstCommentOnNewLine(0),
        m_LastComments(0), m_LastCommentNum(0), m_LastCommentSpace(0), m_LastCommentOnNewLine(0)
    {
    }
    ISyntaxComponent::~ISyntaxComponent(void)
    {
        ReleaseFirstComments();
        ReleaseLastComments();
    }
    void ISyntaxComponent::CopyFrom(const ISyntaxComponent& other)
    {
        m_FirstCommentNum = other.m_FirstCommentNum;
        m_FirstCommentSpace = other.m_FirstCommentSpace;
        m_FirstComments = new const char*[m_FirstCommentSpace];
        memcpy(m_FirstComments, other.m_FirstComments, m_FirstCommentNum * sizeof(const char*));
        m_LastCommentNum = other.m_LastCommentNum;
        m_LastCommentSpace = other.m_LastCommentSpace;
        m_LastComments = new const char*[m_LastCommentSpace];
        memcpy(m_LastComments, other.m_LastComments, m_LastCommentNum * sizeof(const char*));
    }
    void ISyntaxComponent::PrepareFirstComments(void)
    {
        if (m_FirstCommentNum >= m_FirstCommentSpace) {
            int newSpace = m_FirstCommentSpace + DELTA_COMMENT;
            const char** pNew = new const char*[newSpace];
            if (pNew) {
                if (NULL != m_FirstComments) {
                    memcpy(pNew, m_FirstComments, m_FirstCommentNum * sizeof(const char*));
                    memset(pNew + m_FirstCommentNum, 0, DELTA_COMMENT * sizeof(const char*));
                    delete[] m_FirstComments;
                }
                m_FirstComments = pNew;
                m_FirstCommentSpace = newSpace;
            }
        }
    }
    void ISyntaxComponent::ReleaseFirstComments(void)
    {
        if (NULL != m_FirstComments) {
            delete[] m_FirstComments;
            m_FirstComments = NULL;
        }
    }
    void ISyntaxComponent::PrepareLastComments(void)
    {
        if (m_LastCommentNum >= m_LastCommentSpace) {
            int newSpace = m_LastCommentSpace + DELTA_COMMENT;
            const char** pNew = new const char*[newSpace];
            if (pNew) {
                if (NULL != m_LastComments) {
                    memcpy(pNew, m_LastComments, m_LastCommentNum * sizeof(const char*));
                    memset(pNew + m_LastCommentNum, 0, DELTA_COMMENT * sizeof(const char*));
                    delete[] m_LastComments;
                }
                m_LastComments = pNew;
                m_LastCommentSpace = newSpace;
            }
        }
    }
    void ISyntaxComponent::ReleaseLastComments(void)
    {
        if (NULL != m_LastComments) {
            delete[] m_LastComments;
            m_LastComments = NULL;
        }
    }
    //------------------------------------------------------------------------------------------------------
    int ValueData::IsValid(void)const
    {
        if (m_Type == TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->IsValid();
            else
                return FALSE;
        }
        return HaveId();
    }
    int ValueData::GetIdType(void)const
    {
        if (m_Type == TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->GetIdType();
            else
                return TYPE_IDENTIFIER;
        }
        return m_Type;
    }
    const char* ValueData::GetId(void)const
    {
        if (m_Type == TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->GetId();
            else
                return "";
        }
        return m_StringVal;
    }
    int ValueData::GetLine(void)const
    {
        if (m_Type == TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->GetLine();
            else
                return m_Line;
        }
        return m_Line;
    }
    int ValueData::HaveId(void)const
    {
        if (m_Type == TYPE_FUNCTION) {
            if (0 != m_FunctionVal)
                return m_FunctionVal->HaveId();
            else
                return FALSE;
        }
        return 0 != m_StringVal ? TRUE : FALSE;
    }
    //------------------------------------------------------------------------------------------------------
    FunctionData::FunctionData(IDslStringAndObjectBuffer& buffer) :ISyntaxComponent(ISyntaxComponent::TYPE_FUNCTION),
        m_Buffer(buffer),
        m_Params(0),
        m_ParamNum(0),
        m_ParamSpace(0),
        m_ParamClass(PARAM_CLASS_NOTHING),
        m_Comments(0),
        m_CommentNum(0),
        m_CommentSpace(0)
    {
        const DslOptions& options = buffer.GetOptions();
        m_MaxParamNum = options.GetMaxParamNum();
    }

    FunctionData::~FunctionData(void)
    {
        ReleaseParams();
        ReleaseComments();
    }

    NullSyntax* FunctionData::GetNullSyntaxPtr(void)const
    {
        return m_Buffer.GetNullSyntaxPtr();
    }

    FunctionData* FunctionData::GetNullFunctionPtr(void)const
    {
        return m_Buffer.GetNullFunctionPtr();
    }

    void FunctionData::PrepareParams(void)
    {
        if (NULL == m_Params && TRUE == HaveParamOrStatement()) {
            m_Params = new SyntaxComponentPtr[INIT_FUNCTION_PARAM];
            if (m_Params) {
                m_ParamSpace = INIT_FUNCTION_PARAM;
            }
        }
        else if (HaveParamOrStatement() && m_ParamNum >= m_ParamSpace) {
            int delta = HaveStatement() ? DELTA_FUNCTION_STATEMENT : DELTA_FUNCTION_PARAM;
            int newSpace = m_ParamSpace + delta;
            if (newSpace <= m_MaxParamNum) {
                SyntaxComponentPtr* pNew = new SyntaxComponentPtr[newSpace];
                if (pNew) {
                    memcpy(pNew, m_Params, m_ParamNum * sizeof(SyntaxComponentPtr));
                    memset(pNew + m_ParamNum, 0, delta * sizeof(SyntaxComponentPtr));
                    delete[] m_Params;
                    m_Params = pNew;
                    m_ParamSpace = newSpace;
                }
            }
        }
    }

    void FunctionData::ReleaseParams(void)
    {
        if (NULL != m_Params) {
            delete[] m_Params;
            m_Params = NULL;
        }
    }

    void FunctionData::PrepareComments(void)
    {
        if (m_CommentNum >= m_CommentSpace) {
            int newSpace = m_CommentSpace + DELTA_COMMENT;
            const char** pNew = new const char*[newSpace];
            if (pNew) {
                memcpy(pNew, m_Comments, m_CommentNum * sizeof(const char*));
                memset(pNew + m_CommentNum, 0, DELTA_COMMENT * sizeof(const char*));
                delete[] m_Comments;
                m_Comments = pNew;
                m_CommentSpace = newSpace;
            }
        }
    }

    void FunctionData::ReleaseComments(void)
    {
        if (NULL != m_Comments) {
            delete[] m_Comments;
            m_Comments = NULL;
        }
    }
    
    StatementData::StatementData(IDslStringAndObjectBuffer& buffer) :ISyntaxComponent(ISyntaxComponent::TYPE_STATEMENT),
        m_Buffer(buffer),
        m_Functions(0),
        m_FunctionNum(0),
        m_FunctionSpace(0)
    {
        const DslOptions& options = buffer.GetOptions();
        m_MaxFunctionNum = options.GetMaxFunctionDimensionNum();
    }

    FunctionData*& StatementData::GetNullFunctionPtrRef(void)const
    {
        return m_Buffer.GetNullFunctionPtrRef();
    }

    void StatementData::PrepareFunctions(void)
    {
        if (NULL == m_Functions) {
            m_Functions = new FunctionData*[INIT_STATEMENT_FUNCTION];
            if (m_Functions) {
                m_FunctionSpace = INIT_STATEMENT_FUNCTION;
            }
        }
        else if (m_FunctionNum >= m_FunctionSpace) {
            int newSpace = m_FunctionSpace + DELTA_STATEMENT_FUNCTION;
            if (newSpace <= m_MaxFunctionNum) {
                FunctionData** pNew = new FunctionData*[newSpace];
                if (pNew) {
                    memcpy(pNew, m_Functions, m_FunctionNum * sizeof(FunctionData*));
                    memset(pNew + m_FunctionNum, 0, DELTA_STATEMENT_FUNCTION * sizeof(FunctionData*));
                    delete[] m_Functions;
                    m_Functions = pNew;
                    m_FunctionSpace = newSpace;
                }
            }
        }
    }

    void StatementData::ReleaseFunctions(void)
    {
        if (NULL != m_Functions) {
            delete[] m_Functions;
            m_Functions = NULL;
        }
    }

    DslFile::DslFile(IDslStringAndObjectBuffer& buffer) :m_Buffer(buffer), m_IsDebugInfoEnable(FALSE),
        m_DslInfos(NULL)
    {
        Init();
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

    void DslFile::Parse(const char* buf)
    {
        Dsl::Parse(buf, *this);
    }

    void DslFile::Parse(IScriptSource& source)
    {
        Dsl::Parse(source, *this);
    }

    void DslFile::AddDslInfo(ISyntaxComponent* p)
    {
        if (0 == p || 0 == m_DslInfos)
            return;
        if (m_DslInfoNum < 0 || m_DslInfoNum >= m_Buffer.GetOptions().GetMaxProgramSize())
            return;
        m_DslInfos[m_DslInfoNum] = p;
        ++m_DslInfoNum;
    }

    static const char* c_BinaryIdentity = "BDSL";
    static int StringCompare(const void* a, const void* b)
    {
        const char* stra = *static_cast<const char*const*>(a);
        const char* strb = *static_cast<const char*const*>(b);
        if (0 == stra && 0 == strb)
            return 0;
        else if (0 == stra)
            return -1;
        else if (0 == strb)
            return 1;

        size_t lena = strlen(stra);
        size_t lenb = strlen(strb);
        if (lena < lenb)
            return -1;
        else if (lena > lenb)
            return 1;
        else
            return strcmp(stra, strb);
    }
    static void WriteInt(char* s, int& pos, int val)
    {
        unsigned int v = val;
        s[pos++] = (char)(v & 0xff);
        s[pos++] = (char)((v & 0xff00) >> 8);
        s[pos++] = (char)((v & 0xff0000) >> 16);
        s[pos++] = (char)((v & 0xff000000) >> 24);
    }
    static void Write7BitEncodedInt(char* s, int& pos, int val)
    {
        unsigned int num;
        for (num = (unsigned int)val; num >= 128; num >>= 7) {
            s[pos++] = (char)(num | 0x80);
        }
        s[pos++] = (char)num;
    }
    static int ReadInt(const char* bytes, int size, int pos)
    {
        if (0 != bytes && pos >= 0 && pos + 3 < size) {
            unsigned char b1 = bytes[pos];
            unsigned char b2 = bytes[pos + 1];
            unsigned char b3 = bytes[pos + 2];
            unsigned char b4 = bytes[pos + 3];
            return b1 | (b2 << 8) | (b3 << 16) | (b4 << 24);
        }
        else {
            return -1;
        }
    }
    static int Read7BitEncodedInt(const char* bytes, int size, int pos, int& byteCount)
    {
        int num = -1;
        byteCount = 0;
        if (0 != bytes && pos < size) {
            int bitCount = 0;
            unsigned char b;
            num = 0;
            do {
                if (bitCount == 35) {
                    num = -1;
                    break;
                }
                b = bytes[pos++];
                num |= (b & 0x7F) << bitCount;
                bitCount += 7;
            } while (pos < size && (b & 0x80) != 0);
            byteCount = bitCount / 7;
        }
        return num;
    }

    static ISyntaxComponent* readBinary(DslFile& file, const char* bytes, int size, int start, int& curCodeIndex, const char** identifiers, int idCount, int& curIdIndex);
    void DslFile::LoadBinaryFile(const char* file)
    {
        char buffer[0x80000];
        int bufferSize = 0;

        FILE* fp = fopen(file, "rb");
        if (0 != fp) {
            bufferSize = fread(buffer, 1, 0x80000, fp);
            fclose(fp);
        }
        LoadBinaryCode(buffer, bufferSize);
    }

    void DslFile::LoadBinaryCode(const char* buffer, int bufferSize)
    {
        if (bufferSize > 0) {
            int pos = strlen(c_BinaryIdentity);
            int bytesLen = ReadInt(buffer, bufferSize, pos);
            pos += 4;
            int bytes2Len = ReadInt(buffer, bufferSize, pos);
            pos += 4;
            int keyCount = ReadInt(buffer, bufferSize, pos);
            pos += 4;
            int bytesStart = pos;
            int bytes2Start = bytesStart + bytesLen;
            int keyStart = bytes2Start + bytes2Len;

            const char* keys[0x10000];
            int ct = 0;

            pos = keyStart;
            for (int i = 0; i < keyCount; ++i) {
                int byteCount;
                int len = Read7BitEncodedInt(buffer, bufferSize, pos, byteCount);
                if (len >= 0) {
                    pos += byteCount;
                    if (len > 0) {
                        char* id = AllocString(len);
                        memcpy(id, buffer + pos, len);
                        pos += len;
                        id[len] = 0;
                        keys[ct++] = id;
                    }
                    else {
                        keys[ct++] = "";
                    }
                }
                else {
                    break;
                }
            }
            const char* identifiers[0x10000];
            int idCount = 0;
            for (int i = bytes2Start; i < bytes2Start + bytes2Len && i < bufferSize; ++i) {
                int ix;
                unsigned char first = (unsigned char)buffer[i];
                if ((first & 0x80) == 0x80) {
                    ++i;
                    unsigned char second = (unsigned char)buffer[i];
                    ix = (int)(((int)first & 0x0000007f) | ((int)second << 7));
                }
                else {
                    ix = first;
                }
                if (ix >= 0 && ix < ct) {
                    identifiers[idCount++] = keys[ix];
                }
                else {
                    identifiers[idCount++] = "";
                }
            }

            int curCodeIndex = 0;
            int curIdIndex = 0;
            while (curCodeIndex < bytesLen) {
                while (curCodeIndex < bufferSize) {
                    char b = buffer[bytesStart + curCodeIndex];
                    if (b == (char)BinCode_BeginStatement || b == (char)BinCode_BeginFunction || b == (char)BinCode_BeginValue)
                        break;
                    ++curCodeIndex;
                }
                if (curCodeIndex < bytesLen) {
                    ISyntaxComponent* p = readBinary(*this, buffer, bufferSize, bytesStart, curCodeIndex, identifiers, idCount, curIdIndex);
                    if (0 != p && p->IsValid()) {
                        AddDslInfo(p);
                    }
                }
            }
        }
    }
    static void writeBinary(char* s, int capacity, int& pos, const char** identifiers, int idCapacity, int& idCount, const ISyntaxComponent& data);
    void DslFile::SaveBinaryFile(const char* file) const
    {
#if FULL_VERSION
        char bytes1[0x40000];
        char bytes2[0x40000];
        int pos1 = 0;
        int pos2 = 0;
        const char* identifiers[0x10000];
        int idCount = 0;
        for (int i = 0; i < GetDslInfoNum(); ++i) {
            ISyntaxComponent* info = GetDslInfo(i);
            writeBinary(bytes1, 0x10000, pos1, identifiers, 0x10000, idCount, *info);
        }

        const char* keys[0x10000];
        for (int i = 0; i < idCount; ++i) {
            if (0 == identifiers[i])
                identifiers[i] = "";
        }
        memcpy(keys, identifiers, 0x10000 * sizeof(const char*));
        qsort(keys, idCount, sizeof(const char*), StringCompare);
        int k = 0;
        for (int i = 1; i < idCount; ++i) {
            const char* lastId = keys[k];
            const char* curId = keys[i];
            if (strcmp(lastId, curId) != 0) {
                if (k + 1 < i) {
                    keys[k + 1] = curId;
                }
                ++k;
            }
        }
        int ct = k + 1;
        if (ct > 0x00004000) {
            assert(0);
            return;
        }
        for (int i = 0; i < idCount; ++i) {
            const char* key = identifiers[i];
            const char** pp = (const char**)bsearch(&key, keys, ct, sizeof(const char*), StringCompare);
            int ix = pp - keys;
            if (ix < 0x80) {
                bytes2[pos2++] = (char)ix;
            }
            else {
                bytes2[pos2++] = (char)((ix & 0x0000007f) | 0x00000080);
                bytes2[pos2++] = (char)(ix >> 7);
            }
        }
        FILE* fp = fopen(file, "wb");
        if (0 != fp) {
            fwrite(c_BinaryIdentity, 1, strlen(c_BinaryIdentity), fp);

            char intbuf[sizeof(int)];
            int pos = 0;
            WriteInt(intbuf, pos, pos1);
            fwrite(intbuf, 1, pos, fp);

            pos = 0;
            WriteInt(intbuf, pos, pos2);
            fwrite(intbuf, 1, pos, fp);

            pos = 0;
            WriteInt(intbuf, pos, ct);
            fwrite(intbuf, 1, pos, fp);

            fwrite(bytes1, 1, pos1, fp);
            fwrite(bytes2, 1, pos2, fp);
            for (int i = 0; i < ct; ++i) {
                const char* id = keys[i];
                size_t len = 0;
                if (0 != id)
                    len = strlen(id);
                pos = 0;
                Write7BitEncodedInt(intbuf, pos, len);
                fwrite(intbuf, 1, pos, fp);
                if (len > 0)
                    fwrite((void*)id, 1, len, fp);
            }
            fclose(fp);
        }
#endif
    }

    void DslFile::Init(void)
    {
        m_DslInfos = new SyntaxComponentPtr[m_Buffer.GetOptions().GetMaxProgramSize()];
        m_DslInfoNum = 0;
    }

    void DslFile::Release(void)
    {
        if (0 != m_DslInfos) {
            delete[] m_DslInfos;
            m_DslInfoNum = 0;
        }
    }

    void DslFile::ClearErrorInfo(void)
    {
        m_HasError = FALSE;
        m_ErrorNum = 0;
        memset(m_ErrorInfo, 0, sizeof(m_ErrorInfo));
    }

    void DslFile::AddError(const char* error)
    {
        char* p = NewErrorInfo();
        if (p)
            tsnprintf(p, MAX_ERROR_INFO_CAPACITY, "%s", error);
    }

    //------------------------------------------------------------------------------------------------------------------------------------
    static void WriteIndent(FILE* fp, int indent)
    {
        for (int i = 0; i < indent; ++i) {
            fwrite("\t", 1, 1, fp);
        }
    }
    static void WriteId(FILE* fp, const char* str, int indent)
    {
        WriteIndent(fp, indent);
        fprintf(fp, "%s", str);
    }
    static void WriteString(FILE* fp, const char* str, int indent)
    {
        const char* escapeChars = "\\\"";
        WriteIndent(fp, indent);
        fwrite("\"", 1, 1, fp);
        const char* p = str;
        int len = strlen(p);
        while (*p) {
            int n = strcspn(p, escapeChars);
            if (n < len) {
                fwrite(p, 1, n, fp);
                fwrite("\\", 1, 1, fp);
                fwrite(p + n, 1, 1, fp);
                p += n + 1;
                len = strlen(p);
            }
            else {
                fwrite(p, 1, len, fp);
                break;
            }
        }
        fwrite("\"", 1, 1, fp);
    }
    static void WriteComponent(FILE* fp, const ISyntaxComponent& component, int indent, int firstLineNoIndent, int isLastOfStatement)
    {
        switch (component.GetSyntaxType()) {
        case ISyntaxComponent::TYPE_VALUE:
            dynamic_cast<const ValueData&>(component).WriteToFile(fp, indent, firstLineNoIndent, isLastOfStatement);
            break;
        case ISyntaxComponent::TYPE_FUNCTION:
            dynamic_cast<const FunctionData&>(component).WriteToFile(fp, indent, firstLineNoIndent, isLastOfStatement);
            break;
        case ISyntaxComponent::TYPE_STATEMENT:
            dynamic_cast<const StatementData&>(component).WriteToFile(fp, indent, firstLineNoIndent, isLastOfStatement);
            break;
        }
    }
    static void WriteStatementsOrExternScript(FILE* fp, const FunctionData& thisData, int indent)
    {
#if FULL_VERSION
        if (thisData.HaveStatement()) {
            fwrite("\n", 1, 1, fp);
            WriteIndent(fp, indent);
            fwrite("{\n", 2, 1, fp);
            for (int ix = 0; ix < thisData.GetParamNum(); ++ix) {
                ISyntaxComponent& component = *thisData.GetParam(ix);
                WriteComponent(fp, component, indent + 1, FALSE, TRUE);
            }
            WriteIndent(fp, indent);
            fwrite("}", 1, 1, fp);
        }
        if (thisData.HaveExternScript()) {
            fwrite("\n", 1, 1, fp);
            WriteIndent(fp, indent);
            const char* externScript = thisData.GetParamId(0);
            size_t len = strlen(externScript);
            if (strchr(externScript, '\n')) {
                fwrite("{:\n", 3, 1, fp);
            }
            else {
                fwrite("{:", 2, 1, fp);
            }
            fwrite(externScript, len, 1, fp);
            if (len > 0 && externScript[len - 1] == '\n') {
                WriteIndent(fp, indent);
                fwrite(":}", 2, 1, fp);
            }
            else {
                fwrite(":}", 2, 1, fp);
            }
        }
#endif
    }
    //------------------------------------------------------------------------------------------------------------------------------------
    void ISyntaxComponent::WriteFirstCommentsToFile(FILE* fp, int indent, int firstLineNoIndent) const
    {
#if FULL_VERSION
        int haveComments = FALSE;
        int newLine = FALSE;
        int fnum = GetFirstCommentNum();
        for (int i = 0; i < fnum; ++i) {
            if (i == 0 && !IsFirstCommentOnNewLine()) {
                WriteId(fp, GetFirstComment(i), firstLineNoIndent ? 0 : indent);
            }
            else {
                WriteId(fp, GetFirstComment(i), i == 0 && firstLineNoIndent ? 0 : indent);
                fwrite("\n", 1, 1, fp);
                newLine = true;
            }
            haveComments = TRUE;
        }
        if (haveComments && !newLine) {
            //行首注释必须要换行，否则可能会把代码注释掉
            fwrite("\n", 1, 1, fp);
        }
#endif
    }
    void ISyntaxComponent::WriteLastCommentsToFile(FILE* fp, int indent, int isLastOfStatement) const
    {
#if FULL_VERSION
        int lnum = GetLastCommentNum();
        if (lnum > 0) {
            if (IsLastCommentOnNewLine()) {
                fwrite("\n", 1, 1, fp);
            }
            for (int i = 0; i < lnum; ++i) {
                if (i == 0 && !IsLastCommentOnNewLine()) {
                    WriteId(fp, GetLastComment(i), 1);
                }
                else {
                    WriteId(fp, GetLastComment(i), indent);
                }
                if (isLastOfStatement) {
                    fwrite("\n", 1, 1, fp);
                }
            }
        }
        else if (isLastOfStatement) {
            fwrite("\n", 1, 1, fp);
        }
#endif
    }
    void ValueData::WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement)const
    {
#if FULL_VERSION
        WriteFirstCommentsToFile(fp, indent, firstLineNoIndent);
        if (IsString()) {
            WriteString(fp, m_ConstStringVal, firstLineNoIndent ? 0 : indent);
        }
        else if (IsValid()) {
            WriteId(fp, m_ConstStringVal, firstLineNoIndent ? 0 : indent);
        }
        if (isLastOfStatement) {
            fwrite(";", 1, 1, fp);
        }
        WriteLastCommentsToFile(fp, indent, isLastOfStatement);
#endif
    }
    void FunctionData::WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement)const
    {
#if FULL_VERSION
        WriteFirstCommentsToFile(fp, indent, firstLineNoIndent);
        int paramClass = GetParamClass() & FunctionData::PARAM_CLASS_UNMASK;
        if (paramClass == FunctionData::PARAM_CLASS_OPERATOR) {
            int infix = GetParamClass() & FunctionData::PARAM_CLASS_WRAP_INFIX_CALL_MASK;
            if (GetParamNum() == 2) {
                ISyntaxComponent& component0 = *GetParam(0);
                WriteComponent(fp, component0, indent, firstLineNoIndent, FALSE);
                fwrite(" ", 1, 1, fp);
                if (IsHighOrder() && NULL != m_Name.GetFunction()) {
                    FunctionData& call = *m_Name.GetFunction();
                    call.WriteToFile(fp, indent, TRUE, FALSE);
                }
                else {
                    if (infix == FunctionData::PARAM_CLASS_WRAP_INFIX_CALL_MASK) {
                        fwrite("`", 1, 1, fp);
                    }
                    m_Name.WriteToFile(fp, indent, TRUE, FALSE);
                }
                fwrite(" ", 1, 1, fp);
                ISyntaxComponent& component1 = *GetParam(1);
                WriteComponent(fp, component1, indent, TRUE, FALSE);
            }
            else {
                fwrite(" ", 1, 1, fp);
                if (IsHighOrder() && NULL != m_Name.GetFunction()) {
                    FunctionData& call = *m_Name.GetFunction();
                    call.WriteToFile(fp, indent, TRUE, FALSE);
                }
                else {
                    if (infix == FunctionData::PARAM_CLASS_WRAP_INFIX_CALL_MASK) {
                        fwrite("`", 1, 1, fp);
                    }
                    m_Name.WriteToFile(fp, indent, TRUE, FALSE);
                }
                fwrite(" ", 1, 1, fp);
                ISyntaxComponent& component0 = *GetParam(0);
                WriteComponent(fp, component0, indent, firstLineNoIndent, FALSE);
            }
        }
        else {
            if (IsHighOrder() && NULL != m_Name.GetFunction()) {
                const FunctionData& lowerOrderFunction = *m_Name.GetFunction();
                lowerOrderFunction.WriteToFile(fp, indent, firstLineNoIndent, FALSE);
            }
            else {
                m_Name.WriteToFile(fp, indent, firstLineNoIndent, FALSE);
            }
            if (HaveStatement() || HaveExternScript()) {
                if (IsHighOrder()) {
                    const FunctionData& lowerOrderFunction = *m_Name.GetFunction();
                    lowerOrderFunction.WriteLastCommentsToFile(fp, indent, isLastOfStatement);
                }
                else if (HaveId()) {
                    GetName().WriteLastCommentsToFile(fp, indent, isLastOfStatement);
                }
                WriteStatementsOrExternScript(fp, *this, indent);
            }
            else if (HaveParam()) {
                switch (paramClass) {
                case FunctionData::PARAM_CLASS_PARENTHESIS:
                    fwrite("(", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_BRACKET:
                    fwrite("[", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_PERIOD:
                    fwrite(".", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_PERIOD_PARENTHESIS:
                    fwrite(".(", 2, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_PERIOD_BRACKET:
                    fwrite(".[", 2, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_PERIOD_BRACE:
                    fwrite(".{", 2, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_PERIOD:
                    fwrite("?.", 2, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_PARENTHESIS:
                    fwrite("?(", 2, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_BRACKET:
                    fwrite("?[", 2, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_BRACE:
                    fwrite("?{", 2, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_POINTER:
                    fwrite("->", 2, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_PERIOD_STAR:
                    fwrite(".*", 2, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_PERIOD_STAR:
                    fwrite("?.*", 3, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_POINTER_STAR:
                    fwrite("->*", 3, 1, fp);
                    break;
                }
                for (int ix = 0; ix < GetParamNum(); ++ix) {
                    if (ix > 0) {
                        fwrite(",", 1, 1, fp);
                    }
                    ISyntaxComponent& component = *GetParam(ix);
                    WriteComponent(fp, component, indent, TRUE, FALSE);
                }
                switch (paramClass) {
                case FunctionData::PARAM_CLASS_PARENTHESIS:
                    fwrite(")", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_BRACKET:
                    fwrite("]", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_PERIOD:
                    break;
                case FunctionData::PARAM_CLASS_PERIOD_PARENTHESIS:
                    fwrite(")", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_PERIOD_BRACKET:
                    fwrite("]", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_PERIOD_BRACE:
                    fwrite("}", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_PERIOD:
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_PARENTHESIS:
                    fwrite(")", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_BRACKET:
                    fwrite("]", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_BRACE:
                    fwrite("}", 1, 1, fp);
                    break;
                case FunctionData::PARAM_CLASS_POINTER:
                    break;
                case FunctionData::PARAM_CLASS_PERIOD_STAR:
                    break;
                case FunctionData::PARAM_CLASS_QUESTION_PERIOD_STAR:
                    break;
                case FunctionData::PARAM_CLASS_POINTER_STAR:
                    break;
                }
            }
        }
        if (isLastOfStatement) {
            fwrite(";", 1, 1, fp);
        }
        int cnum = GetCommentNum();
        for (int i = 0; i < cnum; ++i) {
            WriteId(fp, GetComment(i), 1);
        }
        WriteLastCommentsToFile(fp, indent, isLastOfStatement);
#endif
    }
    void StatementData::WriteToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement)const
    {
#if FULL_VERSION
        WriteFirstCommentsToFile(fp, indent, firstLineNoIndent);
        int num = GetFunctionNum();
        FunctionData* func1 = GetFunction(0);
        FunctionData* func2 = GetFunction(1);
        if (num == 2 && NULL != func1 && NULL != func2 && func1->GetParamClass() == FunctionData::PARAM_CLASS_TERNARY_OPERATOR && func2->GetParamClass() == FunctionData::PARAM_CLASS_TERNARY_OPERATOR) {
            FunctionData* lowerOrderFunc = func1->GetName().GetFunction();
            ISyntaxComponent* pcomp0 = 0;
            if (0 != lowerOrderFunc)
                pcomp0 = lowerOrderFunc->GetParam(0);
            ISyntaxComponent* pcomp1 = func1->GetParam(0);
            ISyntaxComponent* pcomp2 = func2->GetParam(0);
            if (NULL != pcomp0 && NULL != pcomp1 && NULL != pcomp2) {
                WriteComponent(fp, *pcomp0, indent, firstLineNoIndent, FALSE);
                fwrite(" ? ", 3, 1, fp);
                WriteComponent(fp, *pcomp1, indent, TRUE, FALSE);
                fwrite(" : ", 3, 1, fp);
                WriteComponent(fp, *pcomp2, indent, TRUE, FALSE);
            }
        }
        else {
            int lastFuncNoParam = FALSE;
            int lastFuncNoStatement = FALSE;
            for (int ix = 0; ix < num; ++ix) {
                FunctionData& func = *GetFunction(ix);
                int noIndent = FALSE;
                int funcNoParam = !func.IsHighOrder() && !func.HaveParam();
                int funcNoStatement = !func.HaveStatement() && !func.HaveExternScript();
                if (ix > 0) {
                    if (lastFuncNoParam && lastFuncNoStatement) {
                        fwrite(" ", 1, 1, fp);
                        noIndent = TRUE;
                    }
                    else if (lastFuncNoStatement && funcNoStatement) {
                        noIndent = TRUE;
                    }
                    else {
                        fwrite("\n", 1, 1, fp);
                        noIndent = FALSE;
                    }
                }
                WriteComponent(fp, func, indent, firstLineNoIndent && ix == 0 || noIndent, FALSE);
                lastFuncNoParam = funcNoParam;
                lastFuncNoStatement = funcNoStatement;
            }
        }
        if (isLastOfStatement) {
            fwrite(";", 1, 1, fp);
        }
        WriteLastCommentsToFile(fp, indent, isLastOfStatement);
#endif
    }
    void DslFile::WriteToFile(FILE* fp, int indent)const
    {
#if FULL_VERSION
        for (int ix = 0; ix < GetDslInfoNum(); ++ix) {
            ISyntaxComponent* p = GetDslInfo(ix);
            if (p) {
                p->WriteToFile(fp, indent, TRUE, TRUE);
            }
        }
#endif
    }
    //------------------------------------------------------------------------------------------------------------------------------------
    static char readByte(const char* bytes, int size, int curCodeIndex)
    {
        if (curCodeIndex < size)
            return bytes[curCodeIndex];
        else
            return 0;
    }
    static const char* readIdentifier(const char** identifiers, int idCount, int curIdIndex)
    {
        if (curIdIndex < idCount)
            return identifiers[curIdIndex];
        else
            return 0;
    }
    static ISyntaxComponent* readBinary(DslFile& file, const char* bytes, int size, int start, int& curCodeIndex, const char** identifiers, int idCount, int& curIdIndex);
    static void readBinary(DslFile& file, const char* bytes, int size, int start, int& curCodeIndex, const char** identifiers, int idCount, int& curIdIndex, ValueData& data)
    {
        char code = readByte(bytes, size, start + curCodeIndex++);
        if (code == (char)BinCode_BeginValue) {
            code = readByte(bytes, size, start + curCodeIndex);
            if (code >= (char)BinCode_ValueTypeBegin) {
                ++curCodeIndex;
                data.SetTypeAndId(code - (char)BinCode_ValueTypeBegin, readIdentifier(identifiers, idCount, curIdIndex++));
            }
            code = readByte(bytes, size, start + curCodeIndex);
            if (code == (char)BinCode_EndValue) {
                ++curCodeIndex;
            }
        }
    }
    static void readBinary(DslFile& file, const char* bytes, int size, int start, int& curCodeIndex, const char** identifiers, int idCount, int& curIdIndex, FunctionData& data)
    {
        char code = readByte(bytes, size, start + curCodeIndex++);
        if (code == (char)BinCode_BeginFunction) {
            code = readByte(bytes, size, start + curCodeIndex);
            if (code >= (char)BinCode_ParamOrExternClassBegin) {
                ++curCodeIndex;
                data.SetParamClass(code - (char)BinCode_ParamOrExternClassBegin);
            }
            code = readByte(bytes, size, start + curCodeIndex);
            if (code == (char)BinCode_BeginValue) {
                ValueData& name = data.GetName();
                readBinary(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, name);
            }
            else if (code == (char)BinCode_BeginFunction) {
                FunctionData* p = file.AddNewFunctionComponent();
                readBinary(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
                ValueData& name = data.GetName();
                name.SetFunction(p);
            }
            for (; ; ) {
                code = readByte(bytes, size, start + curCodeIndex);
                if (code == (char)BinCode_EndFunction) {
                    ++curCodeIndex;
                    break;
                }
                else {
                    ISyntaxComponent* syntaxData = readBinary(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex);
                    if (0 != syntaxData) {
                        data.AddParam(syntaxData);
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
    static void readBinary(DslFile& file, const char* bytes, int size, int start, int& curCodeIndex, const char** identifiers, int idCount, int& curIdIndex, StatementData& data)
    {
        char code = readByte(bytes, size, start + curCodeIndex++);
        if (code == (char)BinCode_BeginStatement) {
            for (; ; ) {
                code = readByte(bytes, size, start + curCodeIndex);
                if (code == (char)BinCode_BeginFunction) {
                    FunctionData* p = file.AddNewFunctionComponent();
                    readBinary(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
                    data.AddFunction(p);
                }
                else if (code == (char)BinCode_EndStatement) {
                    ++curCodeIndex;
                    break;
                }
                else {
                    break;
                }
            }
        }
    }
    static ISyntaxComponent* readBinary(DslFile& file, const char* bytes, int size, int start, int& curCodeIndex, const char** identifiers, int idCount, int& curIdIndex)
    {
        ISyntaxComponent* ret = 0;
        char code = readByte(bytes, size, start + curCodeIndex);
        if (code == (char)BinCode_BeginValue) {
            ValueData* p = file.AddNewValueComponent();
            readBinary(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
            ret = p;
        }
        else if (code == (char)BinCode_BeginFunction) {
            FunctionData* p = file.AddNewFunctionComponent();
            readBinary(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
            ret = p;
        }
        else if (code == (char)BinCode_BeginStatement) {
            StatementData* p = file.AddNewStatementComponent();
            readBinary(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
            ret = p;
        }
        return ret;
    }
    //---------------------------------------------------------------------------------------------
#if FULL_VERSION
    static void writeBinary(char* s, int capacity, int& pos, const char** identifiers, int idCapacity, int& idCount, const ISyntaxComponent& data);
    static void writeBinary(char* s, int capacity, int& pos, const char** identifiers, int idCapacity, int& idCount, const ValueData& data)
    {
        s[pos++] = (char)BinCode_BeginValue;
        s[pos++] = (char)((int)BinCode_ValueTypeBegin + data.GetIdType());
        identifiers[idCount++] = data.GetId();
        s[pos++] = (char)BinCode_EndValue;
    }
    static void writeBinary(char* s, int capacity, int& pos, const char** identifiers, int idCapacity, int& idCount, const FunctionData& data)
    {
        s[pos++] = (char)BinCode_BeginFunction;
        s[pos++] = (char)((int)BinCode_ParamOrExternClassBegin + data.GetParamClass());
        if (data.IsHighOrder()) {
            const ValueData& name = data.GetName();
            writeBinary(s, capacity, pos, identifiers, idCapacity, idCount, *name.GetFunction());
        }
        else {
            writeBinary(s, capacity, pos, identifiers, idCapacity, idCount, data.GetName());
        }

        for (int i = 0; i < data.GetParamNum(); ++i) {
            const ISyntaxComponent* syntaxData = data.GetParam(i);
            writeBinary(s, capacity, pos, identifiers, idCapacity, idCount, *syntaxData);
        }
        s[pos++] = (char)BinCode_EndFunction;
    }
    static void writeBinary(char* s, int capacity, int& pos, const char** identifiers, int idCapacity, int& idCount, const StatementData& data)
    {
        s[pos++] = (char)BinCode_BeginStatement;
        for (int i = 0; i < data.GetFunctionNum(); ++i) {
            const FunctionData* funcData = data.GetFunction(i);
            writeBinary(s, capacity, pos, identifiers, idCapacity, idCount, *funcData);
        }
        s[pos++] = (char)BinCode_EndStatement;
    }
    static void writeBinary(char* s, int capacity, int& pos, const char** identifiers, int idCapacity, int& idCount, const ISyntaxComponent& data)
    {
        int syntaxType = data.GetSyntaxType();
        switch (syntaxType) {
        case ISyntaxComponent::TYPE_VALUE: {
            const ValueData* val = dynamic_cast<const ValueData*>(&data);
            if (0 != val) {
                writeBinary(s, capacity, pos, identifiers, idCapacity, idCount, *val);
            }
            break;
        }
        case ISyntaxComponent::TYPE_FUNCTION: {
            const FunctionData* val = dynamic_cast<const FunctionData*>(&data);
            if (0 != val) {
                writeBinary(s, capacity, pos, identifiers, idCapacity, idCount, *val);
            }
            break;
        }
        case ISyntaxComponent::TYPE_STATEMENT: {
            const StatementData* val = dynamic_cast<const StatementData*>(&data);
            if (0 != val) {
                writeBinary(s, capacity, pos, identifiers, idCapacity, idCount, *val);
            }
            break;
        }
        }
    }
#endif
}