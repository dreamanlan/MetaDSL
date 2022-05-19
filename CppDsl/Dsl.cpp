#include "Dsl.h"

namespace Dsl
{
    static void CopyFirstLastComments(const DslParser::ISyntaxComponent& src, DslData::ISyntaxComponent& dest)
    {
        if (src.GetFirstCommentNum() > 0) {
            dest.SetFirstCommentOnNewLine(src.IsFirstCommentOnNewLine());
            for (int i = 0; i < src.GetFirstCommentNum(); ++i) {
                auto* p = src.GetFirstComment(i);
                if (p)
                    dest.AddFirstComment(p);
            }
        }
        if (src.GetLastCommentNum() > 0) {
            dest.SetLastCommentOnNewLine(src.IsLastCommentOnNewLine());
            for (int i = 0; i < src.GetLastCommentNum(); ++i) {
                auto* p = src.GetLastComment(i);
                if(p)
                    dest.AddLastComment(p);
            }
        }
    }
    static void CopyFunctionComments(const DslParser::FunctionData& src, DslData::FunctionData& dest)
    {
        if (src.GetCommentNum() > 0) {
            for (int i = 0; i < src.GetCommentNum(); ++i) {
                auto* p = src.GetComment(i);
                if (p)
                    dest.AddComment(p);
            }
        }
    }
    static void TransformFunction(const DslParser::FunctionData& src, DslData::FunctionData& dest);
    static void TransformStatement(const DslParser::StatementData& src, DslData::StatementData& dest);
    static void TransformValue(const DslParser::ValueData& src, DslData::ValueData& dest)
    {
        CopyFirstLastComments(src, dest);
        dest.SetLine(src.GetLine());
        if (!src.IsValid()) {
            dest.SetInvalid();
        }
        else if (src.IsFunction()) {
            auto* pFunc = dest.SetFunction();
            TransformFunction(*src.GetFunction(), *pFunc);
        }
        else if(src.IsNum()){
            dest.SetNumber(src.GetId());
        }
        else if (src.IsString()) {
            dest.SetString(src.GetId());
        }
        else if (src.IsIdentifier()) {
            dest.SetIdentifier(src.GetId());
        }
        else {
            dest.SetInvalid();
        }
    }
    static void TransformFunction(const DslParser::FunctionData& src, DslData::FunctionData& dest)
    {
        CopyFirstLastComments(src, dest);
        CopyFunctionComments(src, dest);
        TransformValue(src.GetName(), dest.GetName());
        dest.SetParamClass(src.GetParamClass());
        for (int ix = 0; ix < src.GetParamNum(); ++ix) {
            auto& param = *src.GetParam(ix);
            switch (param.GetSyntaxType()) {
            case DslParser::ISyntaxComponent::TYPE_VALUE: {
                auto& vd = static_cast<const DslParser::ValueData&>(param);
                auto* p = dest.AddValueParam();
                TransformValue(vd, *p);
            }break;
            case DslParser::ISyntaxComponent::TYPE_FUNCTION: {
                auto& fd = static_cast<const DslParser::FunctionData&>(param);
                auto* p = dest.AddFunctionParam();
                TransformFunction(fd, *p);
            }break;
            case DslParser::ISyntaxComponent::TYPE_STATEMENT: {
                auto& sd = static_cast<const DslParser::StatementData&>(param);
                auto* p = dest.AddStatementParam();
                TransformStatement(sd, *p);
            }break;
            }
        }
    }
    static void TransformStatement(const DslParser::StatementData& src, DslData::StatementData& dest)
    {
        CopyFirstLastComments(src, dest);
        for (int ix = 0; ix < src.GetFunctionNum(); ++ix) {
            auto& func = *src.GetFunction(ix);
            if (func.IsValue()) {
                auto& vd = static_cast<const DslParser::ValueData&>(func);
                auto* p = dest.AddValue();
                TransformValue(vd, *p);
            }
            else if (func.IsFunction()) {
                auto& fd = static_cast<const DslParser::FunctionData&>(func);
                auto* p = dest.AddFunction();
                TransformFunction(fd, *p);
            }
        }
    }
    void Transform(const DslParser::DslFile& src, DslData::DslFile& dest)
    {
        DslData::DslFile::DontLoadComments(DslParser::DslOptions::DontLoadComments());
        dest.Reset();
        dest.SetStringDelimiter(src.GetStringBeginDelimiter(), src.GetStringEndDelimiter());
        dest.SetScriptDelimiter(src.GetScriptBeginDelimiter(), src.GetScriptEndDelimiter());
        for (int ix = 0; ix < src.GetErrorNum(); ++ix) {
            dest.AddError(src.GetErrorInfo(ix));
        }
        for (int ix = 0; ix < src.GetDslInfoNum(); ++ix) {
            auto& info = *src.GetDslInfo(ix);
            switch (info.GetSyntaxType()) {
            case DslParser::ISyntaxComponent::TYPE_VALUE: {
                auto& vd = static_cast<const DslParser::ValueData&>(info);
                auto* p = dest.AddValue();
                TransformValue(vd, *p);
            }break;
            case DslParser::ISyntaxComponent::TYPE_FUNCTION: {
                auto& fd = static_cast<const DslParser::FunctionData&>(info);
                auto* p = dest.AddFunction();
                TransformFunction(fd, *p);
            }break;
            case DslParser::ISyntaxComponent::TYPE_STATEMENT: {
                auto& sd = static_cast<const DslParser::StatementData&>(info);
                auto* p = dest.AddStatement();
                TransformStatement(sd, *p);
            }break;
            }
        }
    }
}