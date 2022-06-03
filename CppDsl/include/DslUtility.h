#ifndef _DSL_UTILITY_H
#define _DSL_UTILITY_H

#include "DslParser.h"
#include "DslData.h"
#include "tsnprintf.h"

namespace DslFileReadWrite
{
    static const char* c_BinaryIdentity = "BDSL";
    //------------------------------------------------------------------------------------------------------------------------------------
    int stringCompare(const void* a, const void* b);
    void writeInt(std::vector<char>& s, int& pos, int val);
    void write7BitEncodedInt(std::vector<char>& s, int& pos, int val);
    void writeInt(char* s, int& pos, int val);
    void write7BitEncodedInt(char* s, int& pos, int val);
    int readInt(const char* bytes, int size, int pos);
    int read7BitEncodedInt(const char* bytes, int size, int pos, int& byteCount);
    char readByte(const char* bytes, int size, int curCodeIndex);
    const char* readIdentifier(const char** identifiers, int idCount, int curIdIndex);
    const std::string& readIdentifier(const std::string* identifiers, int idCount, int curIdIndex);
    void WriteIndent(FILE* fp, int indent);
    void WriteId(FILE* fp, const char* str, int indent);
    void WriteString(FILE* fp, const char* str, int indent, const char* beginDelim, const char* endDelim);
    //------------------------------------------------------------------------------------------------------------------------------------
    template<typename T>
    struct TypeAsArg
    {
        using ReadType = T;
    };
    template<typename T>
    struct DslTypeDeduce
    {
        using ISyntaxComponent = DslParser::ISyntaxComponent;
        using ValueData = DslParser::ValueData;
        using FunctionData =  DslParser::FunctionData;
        using StatementData = DslParser::StatementData;
        using DelimiterInfo = DslParser::DelimiterInfo;
        using StrType = const char*;
    };
    template<>
    struct DslTypeDeduce<DslData::ISyntaxComponent>
    {
        using ISyntaxComponent = DslData::ISyntaxComponent;
        using ValueData = DslData::ValueData;
        using FunctionData = DslData::FunctionData;
        using StatementData = DslData::StatementData;
        using DelimiterInfo = DslData::DelimiterInfo;
        using StrType = std::string;
    };
    template<>
    struct DslTypeDeduce<DslData::ValueData>
    {
        using ISyntaxComponent = DslData::ISyntaxComponent;
        using ValueData = DslData::ValueData;
        using FunctionData = DslData::FunctionData;
        using StatementData = DslData::StatementData;
        using DelimiterInfo = DslData::DelimiterInfo;
        using StrType = std::string;
    };
    template<>
    struct DslTypeDeduce<DslData::FunctionData>
    {
        using ISyntaxComponent = DslData::ISyntaxComponent;
        using ValueData = DslData::ValueData;
        using FunctionData = DslData::FunctionData;
        using StatementData = DslData::StatementData;
        using DelimiterInfo = DslData::DelimiterInfo;
        using StrType = std::string;
    };
    template<>
    struct DslTypeDeduce<DslData::StatementData>
    {
        using ISyntaxComponent = DslData::ISyntaxComponent;
        using ValueData = DslData::ValueData;
        using FunctionData = DslData::FunctionData;
        using StatementData = DslData::StatementData;
        using DelimiterInfo = DslData::DelimiterInfo;
        using StrType = std::string;
    };
    template<>
    struct DslTypeDeduce<DslData::DslFile>
    {
        using ISyntaxComponent = DslData::ISyntaxComponent;
        using ValueData = DslData::ValueData;
        using FunctionData = DslData::FunctionData;
        using StatementData = DslData::StatementData;
        using DelimiterInfo = DslData::DelimiterInfo;
        using StrType = std::string;
    };
    //------------------------------------------------------------------------------------------------------------------------------------
    struct StrPolicy
    {
        static inline const char* ToCStr(const std::string& str)
        {
            return str.c_str();
        }
        static inline const char* ToCStr(const char* str)
        {
            return str;
        }
        static inline void Null2Empty(std::string ids[], int len)
        {}
        static inline void Null2Empty(const char* ids[], int len)
        {
            for (int i = 0; i < len; ++i) {
                if (nullptr == ids[i])
                    ids[i] = "";
            }
        }
        static inline int Len(const std::string& str)
        {
            return static_cast<int>(str.length());
        }
        static inline int Len(const char* str)
        {
            return static_cast<int>(strlen(str));
        }
        static inline bool ExistsChar(const std::string& str, char ch)
        {
            return std::string::npos != str.find(ch);
        }
        static inline bool ExistsChar(const char* str, char ch)
        {
            return nullptr != strchr(str, ch);
        }
        static inline bool ExistsStr(const std::string& str, const char* s)
        {
            return std::string::npos != str.find(s);
        }
        static inline bool ExistsStr(const char* str, const char* s)
        {
            return nullptr != strstr(str, s);
        }
        static inline bool Equal(const std::string& str, const char* s)
        {
            return str == s;
        }
        static inline bool Equal(const char* str, const char* s)
        {
            return 0 == strcmp(str, s);
        }
        static inline void Push(std::vector<std::string>& ids, const std::string& id)
        {
            ids.push_back(id);
        }
        static inline void Push(std::vector<const char*>& ids, const char* id)
        {
            ids.push_back(id);
        }
        static inline void MemCpy(const char** keys, const std::string* ids, int count)
        {
            for (int i = 0; i < count; ++i) {
                keys[i] = ids[i].c_str();
            }
        }
        static inline void MemCpy(const char** keys, const char** ids, int count)
        {
            memcpy(keys, ids, count * sizeof(const char*));
        }
    };
    struct DslPolicy
    {
        static inline DslParser::FunctionData* SetFunction(DslParser::DslFile& file, DslParser::FunctionData& data)
        {
            return file.AddNewFunctionComponent();
        }
        static inline void CompleteSetFunction(DslParser::DslFile& file, DslParser::FunctionData& data, DslParser::FunctionData* p)
        {
            if (p)
                data.GetName().SetFunction(p);
        }
        static inline DslParser::ValueData* AddValueParam(DslParser::DslFile& file, DslParser::FunctionData& data)
        {
            return file.AddNewValueComponent();
        }
        static inline DslParser::FunctionData* AddFunctionParam(DslParser::DslFile& file, DslParser::FunctionData& data)
        {
            return file.AddNewFunctionComponent();
        }
        static inline DslParser::StatementData* AddStatementParam(DslParser::DslFile& file, DslParser::FunctionData& data)
        {
            return file.AddNewStatementComponent();
        }
        static inline void CompleteAddParam(DslParser::DslFile& file, DslParser::FunctionData& data, DslParser::ISyntaxComponent* p)
        {
            if (p)
                data.AddParam(p);
        }
        static inline DslParser::ValueData* AddValue(DslParser::DslFile& file, DslParser::StatementData& data)
        {
            return file.AddNewValueComponent();
        }
        static inline DslParser::FunctionData* AddFunction(DslParser::DslFile& file, DslParser::StatementData& data)
        {
            return file.AddNewFunctionComponent();
        }
        static inline void CompleteAddValurOrFunction(DslParser::DslFile& file, DslParser::StatementData& data, DslParser::ValueOrFunctionData* p)
        {
            if (p)
                data.AddFunction(p);
        }
        static inline DslParser::ValueData* AddValueDsl(DslParser::DslFile& file)
        {
            return file.AddNewValueComponent();
        }
        static inline DslParser::FunctionData* AddFunctionDsl(DslParser::DslFile& file)
        {
            return file.AddNewFunctionComponent();
        }
        static inline DslParser::StatementData* AddStatementDsl(DslParser::DslFile& file)
        {
            return file.AddNewStatementComponent();
        }
        static inline void CompleteAddDsl(DslParser::DslFile& file, DslParser::ISyntaxComponent* p)
        {
            if (p)
                file.AddDslInfo(p);
        }

        static inline DslData::FunctionData* SetFunction(DslData::DslFile& file, DslData::FunctionData& data)
        {
            return data.GetName().SetFunction();
        }
        static inline void CompleteSetFunction(DslData::DslFile& file, DslData::FunctionData& data, DslData::FunctionData* p)
        {
        }
        static inline DslData::ValueData* AddValueParam(DslData::DslFile& file, DslData::FunctionData& data)
        {
            return data.AddValueParam();
        }
        static inline DslData::FunctionData* AddFunctionParam(DslData::DslFile& file, DslData::FunctionData& data)
        {
            return data.AddFunctionParam();
        }
        static inline DslData::StatementData* AddStatementParam(DslData::DslFile& file, DslData::FunctionData& data)
        {
            return data.AddStatementParam();
        }
        static inline void CompleteAddParam(DslData::DslFile& file, DslData::FunctionData& data, DslData::ISyntaxComponent* p)
        {
        }
        static inline DslData::ValueData* AddValue(DslData::DslFile& file, DslData::StatementData& data)
        {
            return data.AddValue();
        }
        static inline DslData::FunctionData* AddFunction(DslData::DslFile& file, DslData::StatementData& data)
        {
            return data.AddFunction();
        }
        static inline void CompleteAddValurOrFunction(DslData::DslFile& file, DslData::StatementData& data, DslData::ValueOrFunctionData* p)
        {
        }
        static inline DslData::ValueData* AddValueDsl(DslData::DslFile& file)
        {
            return file.AddValue();
        }
        static inline DslData::FunctionData* AddFunctionDsl(DslData::DslFile& file)
        {
            return file.AddFunction();
        }
        static inline DslData::StatementData* AddStatementDsl(DslData::DslFile& file)
        {
            return file.AddStatement();
        }
        static inline void CompleteAddDsl(DslData::DslFile& file, DslData::ISyntaxComponent* p)
        {
        }

        static inline void CopyStr(DslParser::DslFile& file, std::vector<const char*>& keys, const char* p, int len)
        {
            char* id = file.AllocString(len);
            memcpy(id, p, len);
            id[len] = 0;
            keys.push_back(id);
        }
        static inline void CopyStr(DslData::DslFile& file, std::vector<std::string>& keys, const char* p, int len)
        {
            std::string str;
            str.append(p, len);
            keys.push_back(std::move(str));
        }
    };
    //------------------------------------------------------------------------------------------------------------------------------------
    template<typename DslTypeT, typename DelimiterInfoT>
    static inline void WriteComponent(FILE* fp, const DslTypeT& component, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfoT& delim)
    {
        component.WriteToFile(fp, indent, firstLineNoIndent, isLastOfStatement, delim);
    }
    template<typename DslTypeT, typename DelimiterInfoT>
    static inline void WriteStatementsOrExternScript(FILE* fp, const DslTypeT& thisData, int indent, const DelimiterInfoT& delim)
    {
#if FULL_VERSION
        if (thisData.HaveStatement()) {
            fwrite("\n", 1, 1, fp);
            WriteIndent(fp, indent);
            fwrite("{\n", 2, 1, fp);
            for (int ix = 0; ix < thisData.GetParamNum(); ++ix) {
                auto& component = *thisData.GetParam(ix);
                WriteComponent(fp, component, indent + 1, FALSE, TRUE, delim);
            }
            WriteIndent(fp, indent);
            fwrite("}", 1, 1, fp);
        }
        if (thisData.HaveExternScript()) {
            fwrite("\n", 1, 1, fp);
            WriteIndent(fp, indent);
            auto externScript = thisData.GetParamId(0);
            int len = StrPolicy::Len(externScript);
            if (StrPolicy::ExistsChar(externScript, '\n')) {
                fwrite(StrPolicy::ToCStr(delim.ScriptBeginDelimiter), StrPolicy::Len(delim.ScriptBeginDelimiter), 1, fp);
                fwrite("\n", 1, 1, fp);
            }
            else {
                fwrite(StrPolicy::ToCStr(delim.ScriptBeginDelimiter), StrPolicy::Len(delim.ScriptBeginDelimiter), 1, fp);
            }
            fwrite(StrPolicy::ToCStr(externScript), len, 1, fp);
            if (len > 0 && externScript[len - 1] == '\n') {
                WriteIndent(fp, indent);
                fwrite(StrPolicy::ToCStr(delim.ScriptEndDelimiter), StrPolicy::Len(delim.ScriptEndDelimiter), 1, fp);
            }
            else {
                fwrite(StrPolicy::ToCStr(delim.ScriptEndDelimiter), StrPolicy::Len(delim.ScriptEndDelimiter), 1, fp);
            }
        }
#endif
    }
    //------------------------------------------------------------------------------------------------------------------------------------
    template<typename DslTypeT>
    static inline void WriteFirstCommentsToFile(FILE* fp, int indent, int firstLineNoIndent, const DslTypeT& data)
    {
#if FULL_VERSION
        int haveComments = FALSE;
        int newLine = FALSE;
        int fnum = data.GetFirstCommentNum();
        for (int i = 0; i < fnum; ++i) {
            if (i == 0 && !data.IsFirstCommentOnNewLine()) {
                WriteId(fp, StrPolicy::ToCStr(data.GetFirstComment(i)), firstLineNoIndent ? 0 : indent);
            }
            else {
                WriteId(fp, StrPolicy::ToCStr(data.GetFirstComment(i)), i == 0 && firstLineNoIndent ? 0 : indent);
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
    template<typename DslTypeT>
    static inline void WriteLastCommentsToFile(FILE* fp, int indent, int isLastOfStatement, const DslTypeT& data)
    {
#if FULL_VERSION
        int lnum = data.GetLastCommentNum();
        if (lnum > 0) {
            if (data.IsLastCommentOnNewLine()) {
                fwrite("\n", 1, 1, fp);
            }
            for (int i = 0; i < lnum; ++i) {
                if (i == 0 && !data.IsLastCommentOnNewLine()) {
                    WriteId(fp, StrPolicy::ToCStr(data.GetLastComment(i)), 1);
                }
                else {
                    WriteId(fp, StrPolicy::ToCStr(data.GetLastComment(i)), indent);
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
    template<typename DslTypeT, typename DelimiterInfoT>
    static inline void WriteValueToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfoT& delim, const DslTypeT& data)
    {
#if FULL_VERSION
        WriteFirstCommentsToFile(fp, indent, firstLineNoIndent, data);
        if (data.IsString()) {
            WriteString(fp, StrPolicy::ToCStr(data.GetId()), firstLineNoIndent ? 0 : indent, StrPolicy::ToCStr(delim.StringBeginDelimiter), StrPolicy::ToCStr(delim.StringEndDelimiter));
        }
        else if (data.IsValid()) {
            WriteId(fp, StrPolicy::ToCStr(data.GetId()), firstLineNoIndent ? 0 : indent);
        }
        if (isLastOfStatement) {
            fwrite(";", 1, 1, fp);
        }
        WriteLastCommentsToFile(fp, indent, isLastOfStatement, data);
#endif
    }
    template<typename DslTypeT, typename DelimiterInfoT>
    static inline void WriteFunctionToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfoT& delim, const DslTypeT& data)
    {
#if FULL_VERSION
        WriteFirstCommentsToFile(fp, indent, firstLineNoIndent, data);
        auto& name = data.GetName();
        if (data.IsOperatorParamClass()) {
            if (data.GetParamNum() == 2) {
                auto& component0 = *data.GetParam(0);
                WriteComponent(fp, component0, indent, firstLineNoIndent, FALSE, delim);
                fwrite(" ", 1, 1, fp);
                if (data.IsHighOrder() && nullptr != name.GetFunction()) {
                    auto& call = *name.GetFunction();
                    call.WriteToFile(fp, indent, TRUE, FALSE, delim);
                }
                else {
                    if (data.HaveParamClassInfixFlag()) {
                        fwrite("`", 1, 1, fp);
                    }
                    name.WriteToFile(fp, indent, TRUE, FALSE, delim);
                }
                fwrite(" ", 1, 1, fp);
                auto& component1 = *data.GetParam(1);
                WriteComponent(fp, component1, indent, TRUE, FALSE, delim);
            }
            else {
                fwrite(" ", 1, 1, fp);
                if (data.IsHighOrder() && nullptr != name.GetFunction()) {
                    auto& call = *name.GetFunction();
                    call.WriteToFile(fp, indent, TRUE, FALSE, delim);
                }
                else {
                    if (data.HaveParamClassInfixFlag()) {
                        fwrite("`", 1, 1, fp);
                    }
                    name.WriteToFile(fp, indent, TRUE, FALSE, delim);
                }
                fwrite(" ", 1, 1, fp);
                auto& component0 = *data.GetParam(0);
                WriteComponent(fp, component0, indent, firstLineNoIndent, FALSE, delim);
            }
        }
        else {
            if (data.IsHighOrder() && nullptr != name.GetFunction()) {
                auto& lowerOrderFunction = *name.GetFunction();
                lowerOrderFunction.WriteToFile(fp, indent, firstLineNoIndent, FALSE, delim);
            }
            else if (name.HaveId()) {
                name.WriteToFile(fp, indent, firstLineNoIndent, FALSE, delim);
            }
            else {
                WriteIndent(fp, firstLineNoIndent ? 0 : indent);
            }
            if (data.HaveStatement() || data.HaveExternScript()) {
                if (data.IsHighOrder()) {
                    auto& lowerOrderFunction = *name.GetFunction();
                    lowerOrderFunction.WriteLastCommentsToFile(fp, indent, FALSE);
                }
                else if (data.HaveId()) {
                    name.WriteLastCommentsToFile(fp, indent, FALSE);
                }
                WriteStatementsOrExternScript(fp, data, indent, delim);
            }
            else if (data.HaveParam()) {
                int paramClass = data.GetParamClassUnmasked();
                switch (paramClass) {
                case IDslSyntaxCommon::PARAM_CLASS_PARENTHESIS:
                    fwrite("(", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_BRACKET:
                    fwrite("[", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD:
                    fwrite(".", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD_PARENTHESIS:
                    fwrite(".(", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD_BRACKET:
                    fwrite(".[", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD_BRACE:
                    fwrite(".{", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_COLON_COLON:
                    fwrite("::", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_COLON_COLON_PARENTHESIS:
                    fwrite("::(", 3, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_COLON_COLON_BRACKET:
                    fwrite("::[", 3, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_COLON_COLON_BRACE:
                    fwrite("::{", 3, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_PERIOD:
                    fwrite("?.", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_PARENTHESIS:
                    fwrite("?(", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_BRACKET:
                    fwrite("?[", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_BRACE:
                    fwrite("?{", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_POINTER:
                    fwrite("->", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_BRACKET_COLON:
                    fwrite("[:", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PARENTHESIS_COLON:
                    fwrite("(:", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_ANGLE_BRACKET_COLON:
                    fwrite("<:", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_BRACE_PERCENT:
                    fwrite("{%", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_BRACKET_PERCENT:
                    fwrite("[%", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PARENTHESIS_PERCENT:
                    fwrite("(%", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_ANGLE_BRACKET_PERCENT:
                    fwrite("<%", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD_STAR:
                    fwrite(".*", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_PERIOD_STAR:
                    fwrite("?.*", 3, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_POINTER_STAR:
                    fwrite("->*", 3, 1, fp);
                    break;
                }
                for (int ix = 0; ix < data.GetParamNum(); ++ix) {
                    if (ix > 0) {
                        fwrite(", ", 2, 1, fp);
                    }
                    auto& component = *data.GetParam(ix);
                    WriteComponent(fp, component, indent, TRUE, FALSE, delim);
                }
                switch (paramClass) {
                case IDslSyntaxCommon::PARAM_CLASS_PARENTHESIS:
                    fwrite(")", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_BRACKET:
                    fwrite("]", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD:
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD_PARENTHESIS:
                    fwrite(")", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD_BRACKET:
                    fwrite("]", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD_BRACE:
                    fwrite("}", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_COLON_COLON:
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_COLON_COLON_PARENTHESIS:
                    fwrite(")", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_COLON_COLON_BRACKET:
                    fwrite("]", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_COLON_COLON_BRACE:
                    fwrite("}", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_PERIOD:
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_PARENTHESIS:
                    fwrite(")", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_BRACKET:
                    fwrite("]", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_BRACE:
                    fwrite("}", 1, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_POINTER:
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_BRACKET_COLON:
                    fwrite(":]", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PARENTHESIS_COLON:
                    fwrite(":)", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_ANGLE_BRACKET_COLON:
                    fwrite(":>", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_BRACE_PERCENT:
                    fwrite("%}", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_BRACKET_PERCENT:
                    fwrite("%]", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PARENTHESIS_PERCENT:
                    fwrite("%)", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_ANGLE_BRACKET_PERCENT:
                    fwrite("%>", 2, 1, fp);
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_PERIOD_STAR:
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_QUESTION_PERIOD_STAR:
                    break;
                case IDslSyntaxCommon::PARAM_CLASS_POINTER_STAR:
                    break;
                }
            }
        }
        if (isLastOfStatement) {
            fwrite(";", 1, 1, fp);
        }
        int cnum = data.GetCommentNum();
        for (int i = 0; i < cnum; ++i) {
            WriteId(fp, StrPolicy::ToCStr(data.GetComment(i)), 1);
        }
        WriteLastCommentsToFile(fp, indent, isLastOfStatement, data);
#endif
    }
    template<typename DslTypeT, typename DelimiterInfoT>
    static inline void WriteStatementToFile(FILE* fp, int indent, int firstLineNoIndent, int isLastOfStatement, const DelimiterInfoT& delim, const DslTypeT& data)
    {
#if FULL_VERSION
        WriteFirstCommentsToFile(fp, indent, firstLineNoIndent, data);
        int num = data.GetFunctionNum();
        typename DslTypeDeduce<DslTypeT>::FunctionData* func1 = nullptr;
        auto* f0 = data.GetFunction(0);
        if (nullptr != f0 && f0->IsFunction())
            func1 = f0->AsFunction();
        typename DslTypeDeduce<DslTypeT>::FunctionData* func2 = nullptr;
        auto* f1 = data.GetFunction(1);
        if (nullptr != f1 && f1->IsFunction())
            func2 = f1->AsFunction();
        if (num == 2 && nullptr != func1 && nullptr != func2 && func1->IsTernaryOperatorParamClass() && func2->IsTernaryOperatorParamClass()) {
            auto* lowerOrderFunc = func1->GetName().GetFunction();
            typename DslTypeDeduce<DslTypeT>::ISyntaxComponent* pcomp0 = 0;
            if (0 != lowerOrderFunc)
                pcomp0 = lowerOrderFunc->GetParam(0);
            auto* pcomp1 = func1->GetParam(0);
            auto* pcomp2 = func2->GetParam(0);
            if (nullptr != pcomp0 && nullptr != pcomp1 && nullptr != pcomp2) {
                WriteComponent(fp, *pcomp0, indent, firstLineNoIndent, FALSE, delim);
                fwrite(" ? ", 3, 1, fp);
                WriteComponent(fp, *pcomp1, indent, TRUE, FALSE, delim);
                fwrite(" : ", 3, 1, fp);
                WriteComponent(fp, *pcomp2, indent, TRUE, FALSE, delim);
            }
        }
        else {
            int lastFuncNoParam = FALSE;
            int lastFuncNoStatement = FALSE;
            for (int ix = 0; ix < num; ++ix) {
                auto* f = data.GetFunction(ix);
                if (f->IsValue()) {
                    auto& val = *f->AsValue();
                    int noIndent = FALSE;
                    if (ix > 0) {
                        if (lastFuncNoParam && lastFuncNoStatement) {
                            fwrite(" ", 1, 1, fp);
                            noIndent = TRUE;
                        }
                        else if (lastFuncNoStatement) {
                            noIndent = TRUE;
                        }
                        else {
                            fwrite("\n", 1, 1, fp);
                            noIndent = FALSE;
                        }
                    }
                    WriteComponent(fp, val, indent, (firstLineNoIndent && ix == 0) || noIndent, FALSE, delim);
                    lastFuncNoParam = TRUE;
                    lastFuncNoStatement = TRUE;
                }
                else {
                    auto& func = *f->AsFunction();
                    int noIndent = FALSE;
                    int funcNoParam = !func.IsHighOrder() && (!func.HaveParam() || func.IsMemberParamClass());
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
                    WriteComponent(fp, func, indent, (firstLineNoIndent && ix == 0) || noIndent, FALSE, delim);
                    lastFuncNoParam = funcNoParam;
                    lastFuncNoStatement = funcNoStatement;
                }
            }
        }
        if (isLastOfStatement) {
            fwrite(";", 1, 1, fp);
        }
        WriteLastCommentsToFile(fp, indent, isLastOfStatement, data);
#endif
    }
    template<typename DslTypeT>
    static inline void WriteDslToFile(FILE* fp, int indent, const DslTypeT& dslFile)
    {
#if FULL_VERSION
        char buf[1025];
        if (!StrPolicy::Equal(dslFile.GetStringBeginDelimiter(), "\"") || !StrPolicy::Equal(dslFile.GetStringEndDelimiter(), "\"")) {
            tsnprintf(buf, 1024, "@@delimiter(string, \"%s\", \"%s\");\n", StrPolicy::ToCStr(dslFile.GetStringBeginDelimiter()), StrPolicy::ToCStr(dslFile.GetStringEndDelimiter()));
            fwrite(buf, 1, strlen(buf), fp);
        }
        if (!StrPolicy::Equal(dslFile.GetScriptBeginDelimiter(), "{:") || !StrPolicy::Equal(dslFile.GetScriptEndDelimiter(), ":}")) {
            tsnprintf(buf, 1024, "@@delimiter(script, \"%s\", \"%s\");\n", StrPolicy::ToCStr(dslFile.GetScriptBeginDelimiter()), StrPolicy::ToCStr(dslFile.GetScriptEndDelimiter()));
            fwrite(buf, 1, strlen(buf), fp);
        }
        for (int ix = 0; ix < dslFile.GetDslInfoNum(); ++ix) {
            auto* p = dslFile.GetDslInfo(ix);
            if (p) {
                p->WriteToFile(fp, indent, TRUE, TRUE, typename DslTypeDeduce<DslTypeT>::DelimiterInfo(dslFile.GetStringBeginDelimiter(), dslFile.GetStringEndDelimiter(), dslFile.GetScriptBeginDelimiter(), dslFile.GetScriptEndDelimiter()));
            }
        }
#endif
    }
    //---------------------------------------------------------------------------------------------
#if FULL_VERSION
    template<typename StrT, typename DslTypeT>
    static inline void writeBinarySyntax(std::vector<char>& s, int& pos, std::vector<StrT>& identifiers, int& idCount, const DslTypeT& data);
    template<typename StrT, typename DslTypeT>
    static inline void writeBinaryValue(std::vector<char>& s, int& pos, std::vector<StrT>& identifiers, int& idCount, const DslTypeT& data)
    {
        s.push_back(0); s[pos++] = (char)BinCode_BeginValue;
        s.push_back(0); s[pos++] = (char)((int)BinCode_ValueTypeBegin + data.GetIdType());
        StrPolicy::Push(identifiers, data.GetId()); 
        idCount++;
        write7BitEncodedInt(s, pos, data.GetLine());
        s.push_back(0); s[pos++] = (char)BinCode_EndValue;
    }
    template<typename StrT, typename DslTypeT>
    static inline void writeBinaryFunction(std::vector<char>& s, int& pos, std::vector<StrT>& identifiers, int& idCount, const DslTypeT& data)
    {
        s.push_back(0); s[pos++] = (char)BinCode_BeginFunction;
        s.push_back(0); s[pos++] = (char)((int)BinCode_ParamOrExternClassBegin + data.GetParamClass());
        if (data.HaveParamOrStatement()) {
            write7BitEncodedInt(s, pos, data.GetParamNum());
        }
        if (data.IsHighOrder()) {
            auto& name = data.GetName();
            writeBinaryFunction(s, pos, identifiers, idCount, *name.GetFunction());
        }
        else {
            writeBinaryValue(s, pos, identifiers, idCount, data.GetName());
        }

        for (int i = 0; i < data.GetParamNum(); ++i) {
            auto* syntaxData = data.GetParam(i);
            writeBinarySyntax(s, pos, identifiers, idCount, *syntaxData);
        }
        s.push_back(0); s[pos++] = (char)BinCode_EndFunction;
    }
    template<typename StrT, typename DslTypeT>
    static inline void writeBinaryStatement(std::vector<char>& s, int& pos, std::vector<StrT>& identifiers, int& idCount, const DslTypeT& data)
    {
        s.push_back(0); s[pos++] = (char)BinCode_BeginStatement;
        write7BitEncodedInt(s, pos, data.GetFunctionNum());
        for (int i = 0; i < data.GetFunctionNum(); ++i) {
            auto* f = data.GetFunction(i);
            if (f->IsValue()) {
                auto* valData = f->AsValue();
                writeBinaryValue(s, pos, identifiers, idCount, *valData);
            }
            else {
                auto* funcData = f->AsFunction();
                writeBinaryFunction(s, pos, identifiers, idCount, *funcData);
            }
        }
        s.push_back(0); s[pos++] = (char)BinCode_EndStatement;
    }
    template<typename StrT, typename DslTypeT>
    static inline void writeBinarySyntax(std::vector<char>& s, int& pos, std::vector<StrT>& identifiers, int& idCount, const DslTypeT& data)
    {
        int syntaxType = data.GetSyntaxType();
        switch (syntaxType) {
        case IDslSyntaxCommon::TYPE_VALUE: {
            auto* val = static_cast<const typename DslTypeDeduce<DslTypeT>::ValueData*>(&data);
            if (0 != val) {
                writeBinaryValue(s, pos, identifiers, idCount, *val);
            }
            break;
        }
        case IDslSyntaxCommon::TYPE_FUNCTION: {
            auto* val = static_cast<const typename DslTypeDeduce<DslTypeT>::FunctionData*>(&data);
            if (0 != val) {
                writeBinaryFunction(s, pos, identifiers, idCount, *val);
            }
            break;
        }
        case IDslSyntaxCommon::TYPE_STATEMENT: {
            auto* val = static_cast<const typename DslTypeDeduce<DslTypeT>::StatementData*>(&data);
            if (0 != val) {
                writeBinaryStatement(s, pos, identifiers, idCount, *val);
            }
            break;
        }
        }
    }
    template<typename DslFileT>
    static inline void writeBinary(FILE* fp, DslFileT& dslFile)
    {
#if FULL_VERSION
        std::vector<char> bytes1;
        std::vector<char> bytes2;
        int pos1 = 0;
        int pos2 = 0;
        std::vector<typename DslTypeDeduce<typename std::remove_const<DslFileT>::type>::StrType> identifiers;
        int idCount = 0;
        for (int i = 0; i < dslFile.GetDslInfoNum(); ++i) {
            auto* info = dslFile.GetDslInfo(i);
            writeBinarySyntax(bytes1, pos1, identifiers, idCount, *info);
        }
        StrPolicy::Null2Empty(identifiers.data(), idCount);

        std::vector<const char*> keys;
        keys.resize(idCount);
        StrPolicy::MemCpy(keys.data(), identifiers.data(), idCount);
        qsort(keys.data(), idCount, sizeof(const char*), stringCompare);
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
        for (int i = 0; i < idCount; ++i) {
            const char* key = StrPolicy::ToCStr(identifiers[i]);
            const char** pp = (const char**)bsearch(&key, keys.data(), ct, sizeof(const char*), stringCompare);
            int ix = static_cast<int>(pp - keys.data());
            write7BitEncodedInt(bytes2, pos2, ix);
        }
        if (0 != fp) {
            fwrite(c_BinaryIdentity, 1, strlen(c_BinaryIdentity), fp);

            char intbuf[sizeof(int)];
            int pos = 0;
            writeInt(intbuf, pos, pos1);
            fwrite(intbuf, 1, pos, fp);

            pos = 0;
            writeInt(intbuf, pos, pos2);
            fwrite(intbuf, 1, pos, fp);

            pos = 0;
            writeInt(intbuf, pos, ct);
            fwrite(intbuf, 1, pos, fp);

            fwrite(bytes1.data(), 1, pos1, fp);
            fwrite(bytes2.data(), 1, pos2, fp);
            for (int i = 0; i < ct; ++i) {
                const char* id = keys[i];
                size_t len = 0;
                if (0 != id)
                    len = strlen(id);
                pos = 0;
                write7BitEncodedInt(intbuf, pos, static_cast<int>(len));
                fwrite(intbuf, 1, pos, fp);
                if (len > 0)
                    fwrite((void*)id, 1, len, fp);
            }
        }
#endif
    }
#endif
    //------------------------------------------------------------------------------------------------------------------------------------
    template<typename DslFileT, typename StrT, typename DslTypeT>
    static inline IDslSyntaxCommon* readBinaryParam(DslFileT& file, const char* bytes, int size, int start, int& curCodeIndex, StrT* identifiers, int idCount, int& curIdIndex, DslTypeT& data);
    template<typename DslFileT, typename StrT, typename DslTypeT>
    static inline void readBinaryValue(DslFileT& file, const char* bytes, int size, int start, int& curCodeIndex, StrT* identifiers, int idCount, int& curIdIndex, DslTypeT& data)
    {
        char code = readByte(bytes, size, start + curCodeIndex++);
        if (code == (char)BinCode_BeginValue) {
            code = readByte(bytes, size, start + curCodeIndex);
            if (code >= (char)BinCode_ValueTypeBegin) {
                ++curCodeIndex;
                data.SetTypeAndId(code - (char)BinCode_ValueTypeBegin, readIdentifier(identifiers, idCount, curIdIndex++));
                int byteCount = 0;
                int v = read7BitEncodedInt(bytes, size, start + curCodeIndex, byteCount);
                data.SetLine(v);
                curCodeIndex += byteCount;
            }
            code = readByte(bytes, size, start + curCodeIndex);
            if (code == (char)BinCode_EndValue) {
                ++curCodeIndex;
            }
        }
    }
    template<typename DslFileT, typename StrT, typename DslTypeT>
    static inline void readBinaryFunction(DslFileT& file, const char* bytes, int size, int start, int& curCodeIndex, StrT* identifiers, int idCount, int& curIdIndex, DslTypeT& data)
    {
        char code = readByte(bytes, size, start + curCodeIndex++);
        if (code == (char)BinCode_BeginFunction) {
            code = readByte(bytes, size, start + curCodeIndex);
            if (code >= (char)BinCode_ParamOrExternClassBegin) {
                ++curCodeIndex;
                data.SetParamClass(code - (char)BinCode_ParamOrExternClassBegin);
                if (data.HaveParamOrStatement()) {
                    int byteCount = 0;
                    int v = read7BitEncodedInt(bytes, size, start + curCodeIndex, byteCount);
                    curCodeIndex += byteCount;
                    data.InitParamsCapacity(v);
                }
            }
            code = readByte(bytes, size, start + curCodeIndex);
            if (code == (char)BinCode_BeginValue) {
                auto& name = data.GetName();
                readBinaryValue(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, name);
            }
            else if (code == (char)BinCode_BeginFunction) {
                auto* p = DslPolicy::SetFunction(file, data);
                readBinaryFunction(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
                DslPolicy::CompleteSetFunction(file, data, p);
            }
            for (; ; ) {
                code = readByte(bytes, size, start + curCodeIndex);
                if (code == (char)BinCode_EndFunction) {
                    ++curCodeIndex;
                    break;
                }
                else {
                    auto* syntaxData = readBinaryParam(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, data);
                    if (nullptr == syntaxData) {
                        break;
                    }
                }
            }
        }
    }
    template<typename DslFileT, typename StrT, typename DslTypeT>
    static inline void readBinaryStatement(DslFileT& file, const char* bytes, int size, int start, int& curCodeIndex, StrT* identifiers, int idCount, int& curIdIndex, DslTypeT& data)
    {
        char code = readByte(bytes, size, start + curCodeIndex++);
        if (code == (char)BinCode_BeginStatement) {
            int byteCount = 0;
            int v = read7BitEncodedInt(bytes, size, start + curCodeIndex, byteCount);
            curCodeIndex += byteCount;
            data.InitFunctionsCapacity(v);
            for (; ; ) {
                code = readByte(bytes, size, start + curCodeIndex);
                if (code == (char)BinCode_BeginValue) {
                    auto* p = DslPolicy::AddValue(file, data);
                    readBinaryValue(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
                    DslPolicy::CompleteAddValurOrFunction(file, data, p);
                }
                else if (code == (char)BinCode_BeginFunction) {
                    auto* p = DslPolicy::AddFunction(file, data);
                    readBinaryFunction(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
                    DslPolicy::CompleteAddValurOrFunction(file, data, p);
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
    template<typename DslFileT, typename StrT, typename DslTypeT>
    static inline IDslSyntaxCommon* readBinaryParam(DslFileT& file, const char* bytes, int size, int start, int& curCodeIndex, StrT* identifiers, int idCount, int& curIdIndex, DslTypeT& data)
    {
        IDslSyntaxCommon* ret = 0;
        char code = readByte(bytes, size, start + curCodeIndex);
        if (code == (char)BinCode_BeginValue) {
            auto* p = DslPolicy::AddValueParam(file, data);
            readBinaryValue(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
            DslPolicy::CompleteAddParam(file, data, p);
            ret = p;
        }
        else if (code == (char)BinCode_BeginFunction) {
            auto* p = DslPolicy::AddFunctionParam(file, data);
            readBinaryFunction(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
            DslPolicy::CompleteAddParam(file, data, p);
            ret = p;
        }
        else if (code == (char)BinCode_BeginStatement) {
            auto* p = DslPolicy::AddStatementParam(file, data);
            readBinaryStatement(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
            DslPolicy::CompleteAddParam(file, data, p);
            ret = p;
        }
        return ret;
    }
    template<typename DslFileT, typename StrT>
    static inline IDslSyntaxCommon* readBinaryDsl(DslFileT& file, const char* bytes, int size, int start, int& curCodeIndex, StrT* identifiers, int idCount, int& curIdIndex)
    {
        IDslSyntaxCommon* ret = 0;
        char code = readByte(bytes, size, start + curCodeIndex);
        if (code == (char)BinCode_BeginValue) {
            auto* p = DslPolicy::AddValueDsl(file);
            readBinaryValue(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
            DslPolicy::CompleteAddDsl(file, p);
            ret = p;
        }
        else if (code == (char)BinCode_BeginFunction) {
            auto* p = DslPolicy::AddFunctionDsl(file);
            readBinaryFunction(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
            DslPolicy::CompleteAddDsl(file, p);
            ret = p;
        }
        else if (code == (char)BinCode_BeginStatement) {
            auto* p = DslPolicy::AddStatementDsl(file);
            readBinaryStatement(file, bytes, size, start, curCodeIndex, identifiers, idCount, curIdIndex, *p);
            DslPolicy::CompleteAddDsl(file, p);
            ret = p;
        }
        return ret;
    }
    template<typename DslFileT, typename StrType>
    static inline void readBinary(DslFileT& file, const char* buffer, int bufferSize, std::vector<StrType>& keys, std::vector<StrType>& identifiers )
    {
        if (bufferSize > 0) {
            int pos = static_cast<int>(strlen(c_BinaryIdentity));
            int bytesLen = readInt(buffer, bufferSize, pos);
            pos += 4;
            int bytes2Len = readInt(buffer, bufferSize, pos);
            pos += 4;
            int keyCount = readInt(buffer, bufferSize, pos);
            pos += 4;
            int bytesStart = pos;
            int bytes2Start = bytesStart + bytesLen;
            int keyStart = bytes2Start + bytes2Len;

            keys.reserve(keyCount);
            keys.clear();
            int ct = 0;
            pos = keyStart;
            for (int i = 0; i < keyCount; ++i) {
                int byteCount;
                int len = read7BitEncodedInt(buffer, bufferSize, pos, byteCount);
                if (len >= 0) {
                    pos += byteCount;
                    if (len > 0) {
                        DslPolicy::CopyStr(file, keys, buffer + pos, len);
                        pos += len;
                    }
                    else {
                        keys.push_back("");
                    }
                    ct++;
                }
                else {
                    break;
                }
            }

            identifiers.reserve(bytes2Len);
            identifiers.clear();
            int idCount = 0;
            for (int i = bytes2Start; i < bytes2Start + bytes2Len && i < bufferSize; ++i) {
                int byteCount = 0;
                int ix = read7BitEncodedInt(buffer, bufferSize, i, byteCount);
                if (ix >= 0) {
                    i += byteCount - 1;
                }
                if (ix >= 0 && ix < ct) {
                    identifiers.push_back(keys[ix]);
                }
                else {
                    identifiers.push_back("");
                }
                idCount++;
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
                    auto* p = readBinaryDsl(file, buffer, bufferSize, bytesStart, curCodeIndex, identifiers.data(), idCount, curIdIndex);
                    if (nullptr == p) {
                        break;
                    }
                }
            }
        }
    }
    //---------------------------------------------------------------------------------------------

}

#endif