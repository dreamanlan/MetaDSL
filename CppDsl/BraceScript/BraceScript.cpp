
#include "BraceScript.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <limits>

namespace Brace
{
#include "BraceScript_Assignment.inl"

    FuncInfo* AbstractBraceApi::CurFuncInfo(void)const
    {
        return GetInterpreter().CurFuncInfo();
    }
    AbstractBraceApi* AbstractBraceApi::GetFailbackApi(void)const
    {
        return GetInterpreter().GetFailbackApi();
    }
    bool AbstractBraceApi::Load(const DslData::ISyntaxComponent& syntax, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
    {
        bool ret = false;
        auto* curFunc = CurFuncInfo();
        auto* failbackApi = GetFailbackApi();
        switch (syntax.GetSyntaxType()) {
        case DslData::ISyntaxComponent::TYPE_VALUE: {
            auto& valueData = static_cast<const DslData::ValueData&>(syntax);
            ret = LoadValue(*curFunc, valueData, resultInfo, executor);
            if (!ret && failbackApi) {
                ret = failbackApi->LoadValue(*curFunc, valueData, resultInfo, executor);
            }
            break;
        }
        case DslData::ISyntaxComponent::TYPE_FUNCTION: {
            auto& funcData = static_cast<const DslData::FunctionData&>(syntax);
            ret = LoadFunction(*curFunc, funcData, resultInfo, executor);
            if (!ret && failbackApi) {
                ret = failbackApi->LoadFunction(*curFunc, funcData, resultInfo, executor);
            }
            if (!ret && funcData.HaveParam()) {
                //Provide a Load specifically for function calls
                BraceApiExecutor lowerFunc;
                BraceApiLoadInfo lowerFuncInfo;
                if (funcData.IsHighOrder()) {
                    auto& lowerFuncData = funcData.GetLowerOrderFunction();
                    lowerFunc = LoadHelper(lowerFuncData, lowerFuncInfo);
                    ret = LoadHighOrderCall(*curFunc, lowerFuncData, lowerFunc, lowerFuncInfo);
                    if (!ret && failbackApi) {
                        ret = failbackApi->LoadHighOrderCall(*curFunc, lowerFuncData, lowerFunc, lowerFuncInfo);
                    }
                }
                std::vector<BraceApiExecutor> args;
                std::vector<BraceApiLoadInfo> argLoadInfos;
                int num = funcData.GetParamNum();
                for (int ix = 0; ix < num; ++ix) {
                    auto* param = funcData.GetParam(ix);
                    BraceApiLoadInfo argLoadInfo;
                    auto p = LoadHelper(*param, argLoadInfo);
                    args.push_back(std::move(p));
                    argLoadInfos.push_back(std::move(argLoadInfo));
                }
                ret = LoadCall(*curFunc, funcData, args, argLoadInfos, resultInfo, executor);
                if (!ret && failbackApi) {
                    ret = failbackApi->LoadCall(*curFunc, funcData, args, argLoadInfos, resultInfo, executor);
                }
            }
            break;
        }
        case DslData::ISyntaxComponent::TYPE_STATEMENT: {
            auto& statementData = static_cast<const DslData::StatementData&>(syntax);
            ret = LoadStatement(*curFunc, statementData, resultInfo, executor);
            if (!ret && failbackApi) {
                ret = failbackApi->LoadStatement(*curFunc, statementData, resultInfo, executor);
            }
            break;
        }
        }
        return ret;
    }
    void AbstractBraceApi::FreeObjVars(VariableInfo& vars, const std::vector<int>& objVars)
    {
        for (auto ix : objVars) {
            VarSetObject(vars, ix, nullptr);
        }
    }

    std::string AbstractBraceApi::GenTempVarName(void)const
    {
        return std::string("_t_") + std::to_string(GenNextUniqueId());
    }
    FuncApiTypeInfo* AbstractBraceApi::GetFuncApiTypeInfo(const std::string& name)const
    {
        return GetInterpreter().GetFuncApiTypeInfo(name);
    }
    FuncInfo* AbstractBraceApi::GetFuncInfo(const std::string& name)const
    {
        return GetInterpreter().GetFuncInfo(name);
    }
    VarInfo* AbstractBraceApi::GetGlobalVarInfo(const std::string& name)const
    {
        auto* info = GetInterpreter().GlobalFuncInfo();
        if (nullptr == info)
            return nullptr;
        auto& varInfos = info->VarTypeInfos;
        auto it = varInfos.find(name);
        if (it != varInfos.end()) {
            return &(it->second);
        }
        return nullptr;
    }
    VarInfo* AbstractBraceApi::GetVarInfo(const std::string& name)const
    {
        auto& interpreter = GetInterpreter();
        auto* info = interpreter.CurFuncInfo();
        if (nullptr == info)
            return nullptr;
        std::string key;
        int level;
        auto it = interpreter.FindVariable(info, name, key, level);
        if (it != info->VarTypeInfos.end()) {
            return &(it->second);
        }
        return nullptr;
    }
    VarInfo* AbstractBraceApi::GetConstInfo(int tok_type, const std::string& name)const
    {
        auto& interpreter = GetInterpreter();
        auto* info = interpreter.GlobalFuncInfo();
        if (nullptr == info)
            return nullptr;
        auto& varInfos = info->VarTypeInfos;
        std::string key = interpreter.CalcConstKey(tok_type, name);
        auto it = varInfos.find(key);
        if (it != varInfos.end()) {
            return &(it->second);
        }
        return nullptr;
    }
    int AbstractBraceApi::GetObjectTypeId(const DslData::ISyntaxComponent& typeSyntax)const
    {
        return GetInterpreter().GetObjectTypeId(typeSyntax);
    }
    const char* AbstractBraceApi::GetObjectTypeName(int objTypeId)const
    {
        return GetInterpreter().GetObjectTypeName(objTypeId);
    }
    ParamTypeInfo AbstractBraceApi::ParseParamTypeInfo(const DslData::ISyntaxComponent& syntax)const
    {
        return GetInterpreter().ParseParamTypeInfo(syntax);
    }
    bool AbstractBraceApi::CanAssign(int destType, int destObjTypeId, int srcType, int srcObjTypeId)const
    {
        return GetInterpreter().CanAssign(destType, destObjTypeId, srcType, srcObjTypeId);
    }
    FuncInfo* AbstractBraceApi::PushFuncInfo(const std::string& name)const
    {
        return GetInterpreter().PushFuncInfo(name);
    }
    void AbstractBraceApi::PopFuncInfo(void)const
    {
        GetInterpreter().PopFuncInfo();
    }
    int AbstractBraceApi::GenNextUniqueId(void)const
    {
        return GetInterpreter().GenNextUniqueId();
    }
    int AbstractBraceApi::CurBlockId(void)const
    {
        return GetInterpreter().CurBlockId();
    }
    std::vector<int>& AbstractBraceApi::CurBlockObjVars(void)const
    {
        return GetInterpreter().CurBlockObjVars();
    }
    void AbstractBraceApi::PushBlock(void)const
    {
        GetInterpreter().PushBlock();
    }
    void AbstractBraceApi::PopBlock(void)const
    {
        GetInterpreter().PopBlock();
    }
    int AbstractBraceApi::AllocGlobalVariable(const std::string& name, int type, int objTypeId)const
    {
        return GetInterpreter().AllocGlobalVariable(name, type, objTypeId);
    }
    int AbstractBraceApi::AllocVariable(const std::string& name, int type, int objTypeId)const
    {
        return GetInterpreter().AllocVariable(name, type, objTypeId);
    }
    int AbstractBraceApi::AllocConst(int tok_type, const std::string& value, int& type)const
    {
        return GetInterpreter().AllocConst(tok_type, value, type);
    }
    void AbstractBraceApi::LogInfo(const std::string& msg)const
    {
        GetInterpreter().LogInfo(msg);
    }
    void AbstractBraceApi::LogWarn(const std::string& msg)const
    {
        GetInterpreter().LogWarn(msg);
    }
    void AbstractBraceApi::LogError(const std::string& msg)const
    {
        GetInterpreter().LogError(msg);
    }
    void AbstractBraceApi::AddSyntaxComponent(DslData::ISyntaxComponent* p)const
    {
        GetInterpreter().AddSyntaxComponent(p);
    }
    void AbstractBraceApi::AddApiInstance(IBraceApi* p)const
    {
        GetInterpreter().AddApiInstance(p);
    }
    BraceApiExecutor AbstractBraceApi::LoadHelper(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& resultInfo)const
    {
        return GetInterpreter().Load(syntaxUnit, resultInfo);
    }

    bool AbstractBraceApi::IsForceQuit(void)const
    {
        return GetInterpreter().IsForceQuit();
    }
    FuncInfo* AbstractBraceApi::GlobalFuncInfo(void)const
    {
        return GetInterpreter().GlobalFuncInfo();
    }
    VariableInfo* AbstractBraceApi::GlobalVariables(void)const
    {
        return GetInterpreter().GlobalVariables();
    }
    const FuncInfo* AbstractBraceApi::CurRuntimeFuncInfo(void)const
    {
        return GetInterpreter().CurRuntimeFuncInfo();
    }
    VariableInfo* AbstractBraceApi::CurRuntimeVariables(void)const
    {
        return GetInterpreter().CurRuntimeVariables();
    }
    void AbstractBraceApi::PushRuntimeStack(const FuncInfo* funcInfo)const
    {
        GetInterpreter().PushRuntimeStack(funcInfo);
    }
    void AbstractBraceApi::PopRuntimeStack(void)const
    {
        GetInterpreter().PopRuntimeStack();
    }

    FunctionExecutor::FunctionExecutor(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_Func(nullptr), m_Args(), m_ArgLoadInfos(), m_ArgAssigns(), m_ResultInfo(), m_ResultAssign(nullptr), m_CodeExecutor(nullptr)
    {
    }
    void FunctionExecutor::Reset(void)
    {
        m_Func = nullptr;
        m_Args.clear();
        m_ArgLoadInfos.clear(); 
        m_ArgAssigns.clear();
        m_ResultInfo = BraceApiLoadInfo();
        m_ResultAssign = nullptr;

        m_CodeExecutor = nullptr;
    }
    void FunctionExecutor::Build(const FuncInfo& callerFunc, const std::string& func)
    {
        //fake a FunctionData, we only need funcname and line.
        DslData::FunctionData funcData;
        funcData.GetName().SetIdentifier(func);
        std::vector<BraceApiExecutor> args;
        std::vector<BraceApiLoadInfo> argLoadInfos;
        BraceApiLoadInfo resultInfo;
        auto* f = GetFuncInfo(func);
        if (nullptr == f)
            return;
        for (int ix = 0; ix < static_cast<int>(f->Params.size()); ++ix) {
            BraceApiLoadInfo argInfo;
            std::string argName = GenTempVarName();
            argInfo.Type = f->Params[ix].Type;
            argInfo.ObjectTypeId = f->Params[ix].ObjectTypeId;
            argInfo.VarIndex = AllocVariable(argName, argInfo.Type, argInfo.ObjectTypeId);
            args.push_back(nullptr);
            argLoadInfos.push_back(std::move(argInfo));
        }
        LoadCall(callerFunc, funcData, args, argLoadInfos, resultInfo, m_CodeExecutor);
    }
    bool FunctionExecutor::IsValid(void)const
    {
        return !m_CodeExecutor.isNull();
    }
    int FunctionExecutor::Run(VariableInfo& gvars, VariableInfo& lvars)const
    {
        if (!m_CodeExecutor.isNull())
            return m_CodeExecutor(gvars, lvars);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int FunctionExecutor::GetArgCount(void)const
    {
        return static_cast<int>(m_ArgLoadInfos.size());
    }
    const BraceApiLoadInfo* FunctionExecutor::ArgInfo(int ix) const 
    {
        if (ix < 0 || ix >= static_cast<int>(m_ArgLoadInfos.size()))
            return nullptr; 
        return &m_ArgLoadInfos[ix]; 
    }
    const BraceApiLoadInfo* FunctionExecutor::ResultInfo(void) const 
    { 
        return &m_ResultInfo; 
    }
    bool FunctionExecutor::LoadCall(const FuncInfo& curFunc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
    {
        const std::string& func = data.GetId();
        m_Func = GetFuncInfo(func);
        if (nullptr == m_Func) {
            std::stringstream ss;
            ss << "func " << func << " undefined, line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        std::swap(m_Args, args);
        std::swap(m_ArgLoadInfos, argLoadInfos);

        int num = static_cast<int>(m_ArgLoadInfos.size());
        for (int ix = 0; ix < num; ++ix) {
            auto& argLoadInfo = m_ArgLoadInfos[ix];
            auto realArgType = argLoadInfo.GetLoadTimeRealType(curFunc);
            if (ix < static_cast<int>(m_Func->Params.size())) {
                auto& paramInfo = m_Func->Params[ix];
                if (paramInfo.IsRef) {
                    if (paramInfo.Type != realArgType.Type && paramInfo.ObjectTypeId != realArgType.ObjectTypeId) {
                        std::stringstream ss;
                        ss << "func arg " << ix << " dismatch error, line " << data.GetLine();
                        LogError(ss.str());
                    }
                }
                else {
                    if (!CanAssign(paramInfo.Type, paramInfo.ObjectTypeId, realArgType.Type, realArgType.ObjectTypeId)) {
                        std::stringstream ss;
                        ss << "func arg " << ix << " dismatch error, line " << data.GetLine();
                        LogError(ss.str());
                    }
                }
                auto ptr = GetVarAssignPtr(paramInfo.Type, paramInfo.IsRef, realArgType.Type, argLoadInfo.Type == BRACE_DATA_TYPE_REF);
                m_ArgAssigns.push_back(ptr);
            };
        }
        m_ResultInfo.Type = m_Func->RetValue.Type;
        m_ResultInfo.ObjectTypeId = m_Func->RetValue.ObjectTypeId;
        m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type, m_ResultInfo.ObjectTypeId);
        m_ResultAssign = GetVarAssignPtr(m_ResultInfo.Type, false, m_Func->RetValue.Type, false);
        resultInfo = m_ResultInfo;
        executor.attach(this, &FunctionExecutor::Execute);
        return true;
    }
    int FunctionExecutor::Execute(VariableInfo& gvars, VariableInfo& lvars)const
    {
        //push args
        auto& lastVars = lvars;
        for (auto& arg : m_Args) {
            if (!arg.isNull())
                arg(gvars, lvars);
        }
        //run curFunc
        int r = BRACE_FLOW_CONTROL_NORMAL;
        PushRuntimeStack(m_Func);
        auto& vars = *CurRuntimeVariables();
        for (int ix = 0; ix < static_cast<int>(m_ArgLoadInfos.size()) && ix < static_cast<int>(m_ArgAssigns.size()); ++ix) {
            auto& destInfo = m_Func->Params[ix];
            auto& srcInfo = m_ArgLoadInfos[ix];
            if (destInfo.IsRef) {
                vars.ReferenceVars[destInfo.VarIndex] = ReferenceInfo(srcInfo.Type, srcInfo.ObjectTypeId, srcInfo.VarIndex, srcInfo.IsGlobal ? &gvars : &lastVars);
            }
            auto ptr = m_ArgAssigns[ix];
            if (srcInfo.IsGlobal)
                (*ptr)(vars, destInfo.VarIndex, gvars, srcInfo.VarIndex);
            else
                (*ptr)(vars, destInfo.VarIndex, lastVars, srcInfo.VarIndex);
        }
        for (auto& p : m_Func->Codes) {
            r = p(gvars, vars);
            if (IsForceQuit())
                goto EXIT;
            switch (r) {
            case BRACE_FLOW_CONTROL_RETURN:
                r = BRACE_FLOW_CONTROL_NORMAL;
                goto EXIT;
            case BRACE_FLOW_CONTROL_EXCEPTION:
                break;
            case BRACE_FLOW_CONTROL_EFFECT:
                break;
            }
        }
    EXIT:
        if (m_ResultAssign) {
            (*m_ResultAssign)(lastVars, m_ResultInfo.VarIndex, vars, m_Func->RetValue.VarIndex);
        }
        for (auto& sptr : vars.ObjectVars) {
            sptr = nullptr;
        }
        PopRuntimeStack();
        return r;
    }

    SimpleBraceApiBase::SimpleBraceApiBase(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_Args(), m_ArgLoadInfos(), m_ResultInfo()
    {
    }
    bool SimpleBraceApiBase::LoadCall(const FuncInfo& func, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
    {
        std::swap(m_Args, args);
        std::swap(m_ArgLoadInfos, argLoadInfos);
        bool r = TypeInference(func, data, m_ArgLoadInfos, resultInfo);
        if (r) {
            m_ResultInfo = resultInfo;
            executor.attach(this, &SimpleBraceApiBase::ExecuteImpl);
        }
        return r;
    }
    bool SimpleBraceApiBase::TypeInference(const FuncInfo& func, const DslData::FunctionData& data, const std::vector<BraceApiLoadInfo>& argInfos, BraceApiLoadInfo& resultInfo)const
    {
        const std::string apiName = data.GetId();
        auto* p = GetFuncApiTypeInfo(apiName);
        if (nullptr != p) {
            int num = static_cast<int>(argInfos.size());
            for (int ix = 0; ix < num; ++ix) {
                auto& argLoadInfo = argInfos[ix];
                auto realArgType = argLoadInfo.GetLoadTimeRealType(func);
                if (ix < static_cast<int>(p->Params.size())) {
                    auto& paramInfo = p->Params[ix];
                    if (paramInfo.IsRef) {
                        if (paramInfo.Type != realArgType.Type && paramInfo.ObjectTypeId != realArgType.ObjectTypeId) {
                            std::stringstream ss;
                            ss << "api " << apiName << " arg " << ix << " dismatch error, line " << data.GetLine();
                            LogError(ss.str());
                        }
                    }
                    else {
                        if (!CanAssign(paramInfo.Type, paramInfo.ObjectTypeId, realArgType.Type, realArgType.ObjectTypeId)) {
                            std::stringstream ss;
                            ss << "api " << apiName << " arg " << ix << " dismatch error, line " << data.GetLine();
                            LogError(ss.str());
                        }
                    }
                }
            }
            if (p->RetValue.Type != BRACE_DATA_TYPE_UNKNOWN) {
                resultInfo.Type = p->RetValue.Type;
                resultInfo.ObjectTypeId = p->RetValue.ObjectTypeId;
                resultInfo.VarIndex = AllocVariable(GenTempVarName(), resultInfo.Type, resultInfo.ObjectTypeId);
            }
            else {
                resultInfo = BraceApiLoadInfo();
            }
            return true;
        }
        else {
            std::stringstream ss;
            ss << "can't find api type info, you must override TypeInference to check type info, line " << data.GetLine();
            LogError(ss.str());
            resultInfo = BraceApiLoadInfo();
            return false;
        }
    }
    int SimpleBraceApiBase::ExecuteImpl(VariableInfo& gvars, VariableInfo& lvars)const
    {
        for (auto& op : m_Args) {
            if (!op.isNull())
                op(gvars, lvars);
        }
        Execute(gvars, lvars, m_ArgLoadInfos, m_ResultInfo);
        return Brace::BRACE_FLOW_CONTROL_NORMAL;
    }

    class GlobalVarDecl final : public AbstractBraceApi
    {
    public:
        GlobalVarDecl(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //@var : type; or @var : objType<: type params :>;
            DslData::ISyntaxComponent* param1 = data.GetParam(0);
            DslData::ISyntaxComponent* param2 = data.GetParam(1);
            if (!param1 || !param2)
                return false;
            const std::string& varId = param1->GetId();
            int varType = BRACE_DATA_TYPE_UNKNOWN;
            int objTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            const std::string& typeName = param2->GetId();
            varType = GetDataType(typeName);
            if (varType == BRACE_DATA_TYPE_OBJECT)
                objTypeId = GetObjectTypeId(*param2);

            auto* varInfo = GetVarInfo(varId);
            if (nullptr != varInfo) {
                //type check
                std::stringstream ss;
                ss << "local var redefine " << varId << " line " << data.GetLine();
                LogError(ss.str());
                return false;
            }
            else {
                //decl var
                if (varType == BRACE_DATA_TYPE_UNKNOWN) {
                    std::stringstream ss;
                    ss << "unknown type " << typeName << " line " << data.GetLine();
                    LogError(ss.str());
                    return false;
                }
            }
            AllocGlobalVariable(varId, varType, objTypeId);
            return true;
        }
    };
    class LocalVarDecl final : public AbstractBraceApi
    {
    public:
        LocalVarDecl(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //$var : type; or $var : objType<: type params :>;
            DslData::ISyntaxComponent* param1 = data.GetParam(0);
            DslData::ISyntaxComponent* param2 = data.GetParam(1);
            if (!param1 || !param2)
                return false;
            const std::string& varId = param1->GetId();
            int varType = BRACE_DATA_TYPE_UNKNOWN;
            int objTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            const std::string& typeName = param2->GetId();
            varType = GetDataType(typeName);
            if (varType == BRACE_DATA_TYPE_OBJECT)
                objTypeId = GetObjectTypeId(*param2);

            auto* varInfo = GetVarInfo(varId);
            if (nullptr != varInfo) {
                //type check
                std::stringstream ss;
                ss << "local var redefine " << varId << " line " << data.GetLine();
                LogError(ss.str());
                return false;
            }
            else {
                //decl var
                if (varType == BRACE_DATA_TYPE_UNKNOWN) {
                    std::stringstream ss;
                    ss << "unknown type " << typeName << " line " << data.GetLine();
                    LogError(ss.str());
                    return false;
                }
            }
            AllocVariable(varId, varType, objTypeId);
            return true;
        }
    };
    class GlobalVarSet final : public AbstractBraceApi
    {
    public:
        GlobalVarSet(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_Exp(), m_Fptr(nullptr), m_VarIndex(INVALID_INDEX), m_SrcVarIndex(INVALID_INDEX)
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //@var = exp; or @var : type = exp;
            DslData::ISyntaxComponent* param1 = data.GetParam(0);
            DslData::ISyntaxComponent* param2 = data.GetParam(1);
            if (!param1 || !param2)
                return false;
            BraceApiLoadInfo argLoadInfo;
            m_Exp = LoadHelper(*param2, argLoadInfo);
            auto realArgType = argLoadInfo.GetLoadTimeRealType(curFunc);
            int varType = BRACE_DATA_TYPE_UNKNOWN;
            int objTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            DslData::FunctionData* pFunc = nullptr;
            if (param1->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                pFunc = static_cast<DslData::FunctionData*>(param1);
                const std::string& typeName = pFunc->GetParamId(1);
                varType = GetDataType(typeName);
                if (varType == BRACE_DATA_TYPE_OBJECT)
                    objTypeId = GetObjectTypeId(*pFunc->GetParam(1));
            }
            const std::string& varId = nullptr != pFunc ? pFunc->GetParamId(0) : param1->GetId();

            m_SrcVarIndex = argLoadInfo.VarIndex;
            bool srcIsRef = argLoadInfo.Type == BRACE_DATA_TYPE_REF;

            auto* funcInfo = GlobalFuncInfo();
            if (nullptr == funcInfo) {
                std::stringstream ss;
                ss << "Fatal Error, can't find Environment ! name " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
                return false;
            }
            else {
                auto* varInfo = GetGlobalVarInfo(varId);
                if (nullptr != varInfo) {
                    varType = varInfo->Type;
                    objTypeId = varInfo->ObjectTypeId;
                    m_VarIndex = varInfo->VarIndex;
                    //type check
                    if (!CanAssign(varInfo->Type, varInfo->ObjectTypeId, realArgType.Type, realArgType.ObjectTypeId)) {
                        std::stringstream ss;
                        ss << "Can't assign " << GetTypeName(argLoadInfo.Type) << " to " << GetTypeName(varInfo->Type) << " line " << data.GetLine();
                        LogError(ss.str());
                        return false;
                    }
                }
                else {
                    //decl var
                    if (varType == BRACE_DATA_TYPE_UNKNOWN) {
                        varType = realArgType.Type;
                        objTypeId = realArgType.ObjectTypeId;
                    }
                    //type check
                    if (!CanAssign(varType, objTypeId, realArgType.Type, realArgType.ObjectTypeId)) {
                        std::stringstream ss;
                        ss << "Can't assign " << GetTypeName(argLoadInfo.Type) << " to " << GetTypeName(varType) << " line " << data.GetLine();
                        LogError(ss.str());
                        return false;
                    }
                    m_VarIndex = AllocGlobalVariable(varId, varType, objTypeId);
                }
            }
            m_Fptr = GetVarAssignPtr(varType, false, realArgType.Type, srcIsRef);
            if (argLoadInfo.IsGlobal)
                executor.attach(this, &GlobalVarSet::ExecuteFromGlobal);
            else
                executor.attach(this, &GlobalVarSet::ExecuteFromLocal);
            return true;
        }
    private:
        int ExecuteFromGlobal(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Exp.isNull())
                m_Exp(gvars, lvars);
            if (m_Fptr) {
                (*m_Fptr)(gvars, m_VarIndex, gvars, m_SrcVarIndex);
            }
            return 0;
        }
        int ExecuteFromLocal(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Exp.isNull())
                m_Exp(gvars, lvars);
            if (m_Fptr) {
                (*m_Fptr)(gvars, m_VarIndex, lvars, m_SrcVarIndex);
            }
            return 0;
        }
    private:
        BraceApiExecutor m_Exp;
        VarAssignPtr m_Fptr;
        int m_VarIndex;
        int m_SrcVarIndex;
    };
    class GlobalVarGet final : public AbstractBraceApi
    {
    public:
        GlobalVarGet(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadValue(const FuncInfo& curFunc, const DslData::ValueData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            const std::string& varId = data.GetId();
            auto* info = GetGlobalVarInfo(varId);
            if (nullptr != info) {
                resultInfo.Type = info->Type;
                resultInfo.ObjectTypeId = info->ObjectTypeId;
                resultInfo.VarIndex = info->VarIndex;
                resultInfo.IsGlobal = info->IsGlobal;
                resultInfo.IsTempVar = false;
            }
            else {
                std::stringstream ss;
                ss << "undefined global var " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
                return false;
            }
            executor = nullptr;
            return true;
        }
    };
    class LocalVarSet final : public AbstractBraceApi
    {
    public:
        LocalVarSet(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_Exp(), m_Fptr(nullptr), m_VarIndex(INVALID_INDEX), m_SrcVarIndex(INVALID_INDEX)
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //$var = exp; or $var : type = exp;
            DslData::ISyntaxComponent* param1 = data.GetParam(0);
            DslData::ISyntaxComponent* param2 = data.GetParam(1);
            if (!param1 || !param2)
                return false;
            BraceApiLoadInfo argLoadInfo;
            m_Exp = LoadHelper(*param2, argLoadInfo);
            auto realArgType = argLoadInfo.GetLoadTimeRealType(curFunc);
            int varType = BRACE_DATA_TYPE_UNKNOWN;
            int objTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            bool addNew = false;
            DslData::FunctionData* pFunc = nullptr;
            if (param1->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                addNew = true;
                pFunc = static_cast<DslData::FunctionData*>(param1);
                const std::string& typeName = pFunc->GetParamId(1);
                varType = GetDataType(typeName);
                if (varType == BRACE_DATA_TYPE_OBJECT)
                    objTypeId = GetObjectTypeId(*pFunc->GetParam(1));
            }
            const std::string& varId = nullptr != pFunc ? pFunc->GetParamId(0) : param1->GetId();
            
            m_SrcVarIndex = argLoadInfo.VarIndex;
            bool srcIsRef = argLoadInfo.Type == BRACE_DATA_TYPE_REF;

            bool isRef = false;
            auto* varInfo = GetVarInfo(varId);
            if (nullptr != varInfo) {
                if (addNew) {
                    std::stringstream ss;
                    ss << "duplicated var define " << varId << " type " << GetTypeName(varInfo->Type) << " line " << data.GetLine();
                    LogError(ss.str());
                    return false;
                }
                else {
                    varType = varInfo->Type;
                    m_VarIndex = varInfo->VarIndex;
                    DataTypeInfo realVarType(varType, varInfo->ObjectTypeId);
                    if (varType == BRACE_DATA_TYPE_REF) {
                        auto& ri = curFunc.VarInitInfo.ReferenceVars[m_VarIndex];
                        realVarType = DataTypeInfo(ri.Type, ri.ObjectTypeId);
                        isRef = true;
                        varType = realVarType.Type;
                        objTypeId = realVarType.ObjectTypeId;
                    }
                    //type check
                    if (!CanAssign(realVarType.Type, realVarType.ObjectTypeId, realArgType.Type, realArgType.ObjectTypeId)) {
                        std::stringstream ss;
                        ss << "Can't assign " << GetTypeName(argLoadInfo.Type) << " to " << GetTypeName(varInfo->Type) << " line " << data.GetLine();
                        LogError(ss.str());
                        return false;
                    }
                }
            }
            else {
                //decl var
                if (varType == BRACE_DATA_TYPE_UNKNOWN) {
                    varType = realArgType.Type;
                    objTypeId = realArgType.ObjectTypeId;
                }
                //type check
                if (!CanAssign(varType, objTypeId, realArgType.Type, realArgType.ObjectTypeId)) {
                    std::stringstream ss;
                    ss << "Can't assign " << GetTypeName(argLoadInfo.Type) << " to " << GetTypeName(varType) << " line " << data.GetLine();
                    LogError(ss.str());
                    return false;
                }
                m_VarIndex = AllocVariable(varId, varType, objTypeId);
            }
            
            m_Fptr = GetVarAssignPtr(varType, isRef, realArgType.Type, srcIsRef);
            if (argLoadInfo.IsGlobal)
                executor.attach(this, &LocalVarSet::ExecuteFromGlobal);
            else
                executor.attach(this, &LocalVarSet::ExecuteFromLocal);
            return true;
        }
    private:
        int ExecuteFromGlobal(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Exp.isNull())
                m_Exp(gvars, lvars);
            if (m_Fptr) {
                (*m_Fptr)(lvars, m_VarIndex, gvars, m_SrcVarIndex);
            }
            return 0;
        }
        int ExecuteFromLocal(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Exp.isNull())
                m_Exp(gvars, lvars);
            if (m_Fptr) {
                (*m_Fptr)(lvars, m_VarIndex, lvars, m_SrcVarIndex);
            }
            return 0;
        }
    private:
        BraceApiExecutor m_Exp;
        VarAssignPtr m_Fptr;
        int m_VarIndex;
        int m_SrcVarIndex;
    };
    class LocalVarGet final : public AbstractBraceApi
    {
    public:
        LocalVarGet(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadValue(const FuncInfo& curFunc, const DslData::ValueData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            const std::string& varId = data.GetId();
            auto* info = GetVarInfo(varId);
            if (nullptr != info) {
                resultInfo.Type = info->Type;
                resultInfo.ObjectTypeId = info->ObjectTypeId;
                resultInfo.VarIndex = info->VarIndex;
                resultInfo.IsGlobal = info->IsGlobal;
                resultInfo.IsTempVar = false;
            }
            else {
                std::stringstream ss;
                ss << "undefined local var " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
                return false;
            }
            executor = nullptr;
            return true;
        }
    };
    class ConstGet final : public AbstractBraceApi
    {
    public:
        ConstGet(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadValue(const FuncInfo& curFunc, const DslData::ValueData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            const std::string& varId = data.GetId();
            auto* info = GetConstInfo(data.GetIdType(), varId);
            if (nullptr != info) {
                resultInfo.Type = info->Type;
                resultInfo.ObjectTypeId = info->ObjectTypeId;
                resultInfo.VarIndex = info->VarIndex;
                resultInfo.IsGlobal = info->IsGlobal;
            }
            else {
                resultInfo.VarIndex = AllocConst(data.GetIdType(), varId, resultInfo.Type);
                resultInfo.IsGlobal = true;
            }
            executor = nullptr;
            return true;
        }
    };
    class BreakExp final : public AbstractBraceApi
    {
    public:
        BreakExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadValue(const FuncInfo& curFunc, const DslData::ValueData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            resultInfo = BraceApiLoadInfo();
            executor.attach(this, &BreakExp::Execute);
            return false;
        }
    private:
        int Execute(VariableInfo& gvars, VariableInfo& lvars)const
        {
            return BRACE_FLOW_CONTROL_BREAK;
        }
    };
    class ContinueExp final : public AbstractBraceApi
    {
    public:
        ContinueExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadValue(const FuncInfo& curFunc, const DslData::ValueData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            resultInfo = BraceApiLoadInfo();
            executor.attach(this, &ContinueExp::Execute);
            return false;
        }
    private:
        int Execute(VariableInfo& gvars, VariableInfo& lvars)const
        {
            return BRACE_FLOW_CONTROL_CONTINUE;
        }
    };
    class ReturnExp final : public AbstractBraceApi
    {
    public:
        ReturnExp(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_Arg(), m_LoadInfo(), m_ResultInfo(), m_Assign(nullptr)
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //return(...); or return <- expression;
            m_ResultInfo.Type = curFunc.RetValue.Type;
            m_ResultInfo.ObjectTypeId = curFunc.RetValue.ObjectTypeId;
            m_ResultInfo.VarIndex = curFunc.RetValue.VarIndex;
            if (!data.IsHighOrder()) {
                if (data.IsOperatorParamClass() && data.GetParamNum() == 2) {
                    auto* exp = data.GetParam(1);
                    m_Arg = LoadHelper(*exp, m_LoadInfo);
                }
                else {
                    auto* exp = data.GetParam(0);
                    m_Arg = LoadHelper(*exp, m_LoadInfo);
                }
                m_Assign = GetVarAssignPtr(m_ResultInfo.Type, false, m_LoadInfo.Type, m_LoadInfo.GetLoadTimeRealType(curFunc).Type == BRACE_DATA_TYPE_REF);
                if (m_LoadInfo.IsGlobal)
                    executor.attach(this, &ReturnExp::ExecuteG);
                else
                    executor.attach(this, &ReturnExp::ExecuteL);
                return true;
            }
            std::stringstream ss;
            ss << "return syntax error, line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        virtual bool LoadStatement(const FuncInfo& curFunc, const DslData::StatementData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //return symbol;
            m_ResultInfo.Type = curFunc.RetValue.Type;
            m_ResultInfo.ObjectTypeId = curFunc.RetValue.ObjectTypeId;
            m_ResultInfo.VarIndex = curFunc.RetValue.VarIndex;
            if (data.GetFunctionNum() == 2) {
                auto* f1 = data.GetFirst()->AsValue();
                auto* f2 = data.GetSecond()->AsValue();
                if (f1 && f2) {
                    m_Arg = LoadHelper(*f2, m_LoadInfo);
                    m_Assign = GetVarAssignPtr(m_ResultInfo.Type, false, m_LoadInfo.GetLoadTimeRealType(curFunc).Type, m_LoadInfo.Type == BRACE_DATA_TYPE_REF);
                    if (m_LoadInfo.IsGlobal)
                        executor.attach(this, &ReturnExp::ExecuteG);
                    else
                        executor.attach(this, &ReturnExp::ExecuteL);
                    return true;
                }
            }
            std::stringstream ss;
            ss << "return syntax error, line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
    private:
        int ExecuteG(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Arg.isNull())
                m_Arg(gvars, lvars);
            if (m_Assign) {
                (*m_Assign)(lvars, m_ResultInfo.VarIndex, gvars, m_LoadInfo.VarIndex);
            }
            return BRACE_FLOW_CONTROL_RETURN;
        }
        int ExecuteL(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Arg.isNull())
                m_Arg(gvars, lvars);
            if (m_Assign) {
                (*m_Assign)(lvars, m_ResultInfo.VarIndex, lvars, m_LoadInfo.VarIndex);
            }
            return BRACE_FLOW_CONTROL_RETURN;
        }
    private:
        BraceApiExecutor m_Arg;
        BraceApiLoadInfo m_LoadInfo;
        BraceApiLoadInfo m_ResultInfo;
        VarAssignPtr m_Assign;
    };
    class FunctionDefine final : public AbstractBraceApi
    {
    public:
        FunctionDefine(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //func(name){...};
            if (data.IsHighOrder()) {
                const std::string& func = data.GetLowerOrderFunction().GetParamId(0);
                auto* curFunc = PushFuncInfo(func);
                int num = data.GetParamNum();
                for (int ix = 0; ix < num; ++ix) {
                    auto* exp = data.GetParam(ix);
                    BraceApiLoadInfo expLoadInfo;
                    auto statement = LoadHelper(*exp, expLoadInfo);
                    if (!statement.isNull())
                        curFunc->Codes.push_back(std::move(statement));
                }
                resultInfo = BraceApiLoadInfo();
                executor = nullptr;
                PopFuncInfo();
                return true;
            }
            else {
                std::stringstream ss;
                ss << "func syntax error " << data.GetParamId(0) << " line " << data.GetLine();
                LogError(ss.str());
            }
            return false;
        }
        virtual bool LoadStatement(const FuncInfo& curFunc, const DslData::StatementData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //func(name)params($a:int32,$b:int8,...)int{...}; or func(name)params($a:int32,$b:int8,...){...};
            bool hasError = false;
            if (data.GetFunctionNum() == 2) {
                auto* f1 = data.GetFirst()->AsFunction();
                auto* f2 = data.GetSecond()->AsFunction();
                if (f1 && !f1->IsHighOrder() && f1->HaveParam() && f2 && f2->IsHighOrder() && f2->HaveStatement()) {
                    const std::string& func = f1->GetParamId(0);
                    auto* newFunc = PushFuncInfo(func);
                    auto& callData = f2->GetLowerOrderFunction();
                    for (int ix = 0; ix < callData.GetParamNum(); ++ix) {
                        auto* p = callData.GetParam(ix);
                        if (p->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                            auto* pf = static_cast<const DslData::FunctionData*>(p);
                            if (pf->IsOperatorParamClass() && pf->GetId() == ":") {
                                auto& name = pf->GetParamId(0);
                                DslData::FunctionData* typeFunc = nullptr;
                                auto* typeParam = pf->GetParam(1);
                                auto pti = ParseParamTypeInfo(*typeParam);
                                if (pti.IsRef) {
                                    int varIndex = AllocVariable(name, BRACE_DATA_TYPE_REF, PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ);
                                    newFunc->VarInitInfo.ReferenceVars[varIndex] = ReferenceInfo(pti.Type, pti.ObjectTypeId, INVALID_INDEX, nullptr);
                                    newFunc->Params.push_back(ParamRetInfo(name, pti.Type, pti.ObjectTypeId, varIndex, true));
                                }
                                else{
                                    int varIndex = AllocVariable(name, pti.Type, pti.ObjectTypeId);
                                    newFunc->Params.push_back(ParamRetInfo(name, pti.Type, pti.ObjectTypeId, varIndex, false));
                                }
                            }
                        }
                        else {
                            hasError = true;
                        }
                    }
                    int num = f2->GetParamNum();
                    for (int ix = 0; ix < num; ++ix) {
                        auto* exp = f2->GetParam(ix);
                        BraceApiLoadInfo expLoadInfo;
                        auto statement = LoadHelper(*exp, expLoadInfo);
                        if (!statement.isNull())
                            newFunc->Codes.push_back(std::move(statement));
                    }
                    resultInfo = BraceApiLoadInfo();
                    executor = nullptr;
                    PopFuncInfo();
                    return true;
                }
                else {
                    hasError = true;
                }
            }
            else if (data.GetFunctionNum() == 3) {
                auto* f1 = data.GetFirst()->AsFunction();
                auto* f2 = data.GetSecond()->AsFunction();
                auto* f3 = data.GetThird()->AsFunction();
                if (f1 && !f1->IsHighOrder() && f1->HaveParam() &&
                    f2 && !f2->IsHighOrder() && f2->HaveParam() &&
                    f3 && f3->HaveStatement()) {
                    const std::string& func = f1->GetParamId(0);
                    auto* newFunc = PushFuncInfo(func);
                    auto& callData = *f2;
                    for (int ix = 0; ix < callData.GetParamNum(); ++ix) {
                        auto* p = callData.GetParam(ix);
                        if (p->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                            auto* pf = static_cast<const DslData::FunctionData*>(p);
                            if (pf->IsOperatorParamClass() && pf->GetId() == ":") {
                                auto& name = pf->GetParamId(0);
                                DslData::FunctionData* typeFunc = nullptr;
                                auto* typeParam = pf->GetParam(1);
                                auto pti = ParseParamTypeInfo(*typeParam);
                                if (pti.IsRef) {
                                    int varIndex = AllocVariable(name, BRACE_DATA_TYPE_REF, PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ);
                                    newFunc->VarInitInfo.ReferenceVars[varIndex] = ReferenceInfo(pti.Type, pti.ObjectTypeId, INVALID_INDEX, nullptr);
                                    newFunc->Params.push_back(ParamRetInfo(name, pti.Type, pti.ObjectTypeId, varIndex, true));
                                }
                                else {
                                    int varIndex = AllocVariable(name, pti.Type, pti.ObjectTypeId);
                                    newFunc->Params.push_back(ParamRetInfo(name, pti.Type, pti.ObjectTypeId, varIndex, false));
                                }
                            }
                        }
                        else {
                            hasError = true;
                        }
                    }
                    if (f3->IsHighOrder() && f3->GetLowerOrderFunction().GetParamClassUnmasked() == DslData::FunctionData::PARAM_CLASS_ANGLE_BRACKET_COLON) {
                        auto& typeName = f3->GetId();
                        int type = GetDataType(typeName);
                        int objTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
                        if (type == BRACE_DATA_TYPE_OBJECT) {
                            objTypeId = GetObjectTypeId(f3->GetLowerOrderFunction());
                        }
                        std::string tname = GenTempVarName();
                        int varIndex = AllocVariable(tname, type, objTypeId);
                        newFunc->RetValue = ParamRetInfo(tname, type, objTypeId, varIndex);
                    }
                    else if (!f3->IsHighOrder()) {
                        auto& typeName = f3->GetId();
                        int type = GetDataType(typeName);
                        int objTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
                        if (type == BRACE_DATA_TYPE_OBJECT) {
                            objTypeId = GetObjectTypeId(f3->GetName());
                        }
                        std::string tname = GenTempVarName();
                        int varIndex = AllocVariable(tname, type, objTypeId);
                        newFunc->RetValue = ParamRetInfo(tname, type, objTypeId, varIndex);
                    }
                    else {
                        hasError = true;
                    }
                    int num = f3->GetParamNum();
                    for (int ix = 0; ix < num; ++ix) {
                        auto* exp = f3->GetParam(ix);
                        BraceApiLoadInfo expLoadInfo;
                        auto statement = LoadHelper(*exp, expLoadInfo);
                        if (!statement.isNull())
                            newFunc->Codes.push_back(std::move(statement));
                    }
                    resultInfo = BraceApiLoadInfo();
                    executor = nullptr;
                    PopFuncInfo();
                    if (!hasError) {
                        return true;
                    }
                }
                else {
                    hasError = true;
                }
            }
            if (hasError) {
                auto* f = data.GetFirst()->AsFunction();
                std::stringstream ss;
                ss << "func syntax error " << (f ? f->GetParamId(0) : std::string("noname")) << " line " << data.GetLine();
                LogError(ss.str());
            }
            return false;
        }
    };
    UnaryOperatorBaseExp::UnaryOperatorBaseExp(BraceScript& interpreter, bool isAssignment) :AbstractBraceApi(interpreter), m_IsAssignment(isAssignment), m_Op1(), m_LoadInfo1(), m_ResultInfo()
    {
    }
    bool UnaryOperatorBaseExp::LoadCall(const FuncInfo& curFunc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
    {
        m_Op1 = args[0];
        m_LoadInfo1 = argLoadInfos[0];
        int resultType = BRACE_DATA_TYPE_UNKNOWN;
        bool r = BuildExecutor(data, m_LoadInfo1.GetLoadTimeRealType(curFunc), resultType, executor);
        if (m_IsAssignment) {
            m_ResultInfo = m_LoadInfo1;
        }
        else {
            m_ResultInfo.Type = resultType;
            m_ResultInfo.ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type, m_ResultInfo.ObjectTypeId);
        }
        resultInfo = m_ResultInfo;
        return r;
    }
    BinaryOperatorBaseExp::BinaryOperatorBaseExp(BraceScript& interpreter, bool isAssignment) :AbstractBraceApi(interpreter), m_IsAssignment(isAssignment), m_Op1(), m_Op2(), m_LoadInfo1(), m_LoadInfo2(), m_ResultInfo()
    {
    }
    bool BinaryOperatorBaseExp::LoadCall(const FuncInfo& curFunc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
    {
        m_Op1 = args[0];
        m_Op2 = args[1];
        m_LoadInfo1 = argLoadInfos[0];
        m_LoadInfo2 = argLoadInfos[1];
        int resultType = BRACE_DATA_TYPE_UNKNOWN;
        bool r = BuildExecutor(data, m_LoadInfo1.GetLoadTimeRealType(curFunc), m_LoadInfo2.GetLoadTimeRealType(curFunc), resultType, executor);
        if (m_IsAssignment) {
            m_ResultInfo = m_LoadInfo1;
        }
        else {
            m_ResultInfo.Type = resultType;
            m_ResultInfo.ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type, m_ResultInfo.ObjectTypeId);
        }
        resultInfo = m_ResultInfo;
        return r;
    }
    class CondExp final : public AbstractBraceApi
    {
    public:
        CondExp(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_Op1(), m_Op2(), m_Op3(), m_LoadInfo1(), m_LoadInfo2(), m_LoadInfo3(), m_ResultInfo()
        {
        }
    protected:
        virtual bool LoadStatement(const FuncInfo& curFunc, const DslData::StatementData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            auto* funcData1 = data.GetFirst()->AsFunction();
            auto* funcData2 = data.GetSecond()->AsFunction();
            if (funcData1->IsHighOrder() && funcData1->HaveLowerOrderParam() && funcData2->GetId() == ":" && funcData2->HaveParamOrStatement()) {
                auto* cond = funcData1->GetLowerOrderFunction().GetParam(0);
                auto* op1 = funcData1->GetParam(0);
                auto* op2 = funcData2->GetParam(0);
                m_Op1 = LoadHelper(*cond, m_LoadInfo1);
                m_Op2 = LoadHelper(*op1, m_LoadInfo2);
                m_Op3 = LoadHelper(*op2, m_LoadInfo3);
                auto realType1 = m_LoadInfo1.GetLoadTimeRealType(curFunc);
                auto realType2 = m_LoadInfo2.GetLoadTimeRealType(curFunc);
                auto realType3 = m_LoadInfo3.GetLoadTimeRealType(curFunc);
                m_ResultInfo.ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
                if (realType2.Type == BRACE_DATA_TYPE_OBJECT && realType2.Type == realType3.Type && realType2.ObjectTypeId == realType3.ObjectTypeId) {
                    m_ResultInfo.Type = realType2.Type;
                    m_ResultInfo.ObjectTypeId = realType2.ObjectTypeId;
                }
                if (realType2.Type == BRACE_DATA_TYPE_STRING || realType3.Type == BRACE_DATA_TYPE_STRING) {
                    m_ResultInfo.Type = BRACE_DATA_TYPE_STRING;
                    executor.attach(this, &CondExp::ExecuteString);
                }
                else if (realType2.Type == BRACE_DATA_TYPE_BOOL && realType3.Type == BRACE_DATA_TYPE_BOOL) {
                    m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
                    executor.attach(this, &CondExp::ExecuteBool);
                }
                else if (NeedFloatArithUnit(realType2.Type, realType3.Type)) {
                    m_ResultInfo.Type = GetMaxType(realType2.Type, realType3.Type);
                    executor.attach(this, &CondExp::ExecuteFloat);
                }
                else if (NeedUnsignedArithUnit(realType2.Type, realType3.Type)) {
                    m_ResultInfo.Type = GetMaxType(realType2.Type, realType3.Type);
                    executor.attach(this, &CondExp::ExecuteUInt);
                }
                else {
                    m_ResultInfo.Type = GetMaxType(realType2.Type, realType3.Type);
                    executor.attach(this, &CondExp::ExecuteInt);
                }
                m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type, m_ResultInfo.ObjectTypeId);
                return true;
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
                return false;
            }
        }
    private:
        int ExecuteInt(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Op1.isNull())
                m_Op1(gvars, lvars);
            bool v = VarGetBoolean(m_LoadInfo1.IsGlobal ? gvars : lvars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            if (v) {
                if (!m_Op2.isNull())
                    m_Op2(gvars, lvars);
                int64_t val = VarGetI64(m_LoadInfo2.IsGlobal ? gvars : lvars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
                VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            else {
                if (!m_Op3.isNull())
                    m_Op3(gvars, lvars);
                int64_t val = VarGetI64(m_LoadInfo3.IsGlobal ? gvars : lvars, m_LoadInfo3.Type, m_LoadInfo3.VarIndex);
                VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteUInt(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Op1.isNull())
                m_Op1(gvars, lvars);
            bool v = VarGetBoolean(m_LoadInfo1.IsGlobal ? gvars : lvars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            if (v) {
                if (!m_Op2.isNull())
                    m_Op2(gvars, lvars);
                uint64_t val = VarGetU64(m_LoadInfo2.IsGlobal ? gvars : lvars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
                VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            else {
                if (!m_Op3.isNull())
                    m_Op3(gvars, lvars);
                uint64_t val = VarGetU64(m_LoadInfo3.IsGlobal ? gvars : lvars, m_LoadInfo3.Type, m_LoadInfo3.VarIndex);
                VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteFloat(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Op1.isNull())
                m_Op1(gvars, lvars);
            bool v = VarGetBoolean(m_LoadInfo1.IsGlobal ? gvars : lvars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            if (v) {
                if (!m_Op2.isNull())
                    m_Op2(gvars, lvars);
                double val = VarGetF64(m_LoadInfo2.IsGlobal ? gvars : lvars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
                VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            else {
                if (!m_Op3.isNull())
                    m_Op3(gvars, lvars);
                double val = VarGetF64(m_LoadInfo3.IsGlobal ? gvars : lvars, m_LoadInfo3.Type, m_LoadInfo3.VarIndex);
                VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteString(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Op1.isNull())
                m_Op1(gvars, lvars);
            bool v = VarGetBoolean(m_LoadInfo1.IsGlobal ? gvars : lvars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            if (v) {
                if (!m_Op2.isNull())
                    m_Op2(gvars, lvars);
                std::string val = VarGetStr(m_LoadInfo2.IsGlobal ? gvars : lvars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
                VarSetStr(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            else {
                if (!m_Op3.isNull())
                    m_Op3(gvars, lvars);
                std::string val = VarGetStr(m_LoadInfo3.IsGlobal ? gvars : lvars, m_LoadInfo3.Type, m_LoadInfo3.VarIndex);
                VarSetStr(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteBool(VariableInfo& gvars, VariableInfo& lvars) const
        {
            if (!m_Op1.isNull())
                m_Op1(gvars, lvars);
            bool v = VarGetBoolean(m_LoadInfo1.IsGlobal ? gvars : lvars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            if (v) {
                if (!m_Op2.isNull())
                    m_Op2(gvars, lvars);
                bool val = VarGetBoolean(m_LoadInfo2.IsGlobal ? gvars : lvars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
                VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            else {
                if (!m_Op3.isNull())
                    m_Op3(gvars, lvars);
                bool val = VarGetBoolean(m_LoadInfo3.IsGlobal ? gvars : lvars, m_LoadInfo3.Type, m_LoadInfo3.VarIndex);
                VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiExecutor m_Op3;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_LoadInfo3;
        BraceApiLoadInfo m_ResultInfo;
    };
    class EchoExp final : public AbstractBraceApi
    {
    public:
        EchoExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(const FuncInfo& curFunc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            std::swap(m_Args, args);
            std::swap(m_ArgLoadInfos, argLoadInfos);
            resultInfo = BraceApiLoadInfo();
            executor.attach(this, &EchoExp::Execute);
            return true;
        }
    private:
        int Execute(VariableInfo& gvars, VariableInfo& lvars)const
        {
            for (auto& p : m_Args) {
                if (!p.isNull())
                    p(gvars, lvars);
            }
            std::stringstream ss;
            for (auto& info : m_ArgLoadInfos) {
                if (info.Type != BRACE_DATA_TYPE_UNKNOWN) {
                    if (info.IsGlobal)
                        ss << VarGetStr(gvars, info.Type, info.VarIndex);
                    else
                        ss << VarGetStr(lvars, info.Type, info.VarIndex);
                }
            }
            LogInfo(ss.str());
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        std::vector<BraceApiExecutor> m_Args;
        std::vector<BraceApiLoadInfo> m_ArgLoadInfos;
    };

    class IfExp final : public AbstractBraceApi
    {
    public:
        IfExp(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_Clauses()
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& funcData, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            if (funcData.IsHighOrder()) {
                auto* cond = funcData.GetLowerOrderFunction().GetParam(0);
                Clause item;
                item.Condition = LoadHelper(*cond, item.LoadInfo);
                PushBlock();
                for (int ix = 0; ix < funcData.GetParamNum(); ++ix) {
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*funcData.GetParam(ix), argLoadInfo);
                    if (!statement.isNull())
                        item.Statements.push_back(std::move(statement));
                }
                item.ObjVars = CurBlockObjVars();
                PopBlock();
                m_Clauses.push_back(std::move(item));
                executor.attach(this, &IfExp::Execute);
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << funcData.GetId() << " line " << funcData.GetLine();
                LogError(ss.str());
            }
            return true;
        }
        virtual bool LoadStatement(const FuncInfo& curFunc, const DslData::StatementData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //if(exp) func(args);
            int funcNum = data.GetFunctionNum();
            if (funcNum == 2) {
                auto* first = data.GetFirst()->AsFunction();
                auto* second = data.GetSecond()->AsFunction();
                const std::string& firstId = first->GetId();
                const std::string& secondId = second->GetId();
                if (firstId == "if" && !first->HaveStatement() && !first->HaveExternScript() &&
                    !secondId.empty() && !second->HaveStatement() && !second->HaveExternScript()) {
                    Clause item;
                    if (first->GetParamNum() > 0) {
                        auto* cond = first->GetParam(0);
                        item.Condition = LoadHelper(*cond, item.LoadInfo);
                    }
                    else {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << first->GetId() << " line " << first->GetLine();
                        LogError(ss.str());
                    }
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*second, argLoadInfo);
                    if (!statement.isNull())
                        item.Statements.push_back(std::move(statement));
                    m_Clauses.push_back(std::move(item));
                    executor.attach(this, &IfExp::Execute);
                    return true;
                }
            }
            //standard if
            for (int ix = 0; ix < data.GetFunctionNum(); ++ix) {
                auto* fd = data.GetFunction(ix);
                auto* fData = fd->AsFunction();
                if (fData->GetId() == "if" || fData->GetId() == "elseif") {
                    Clause item;
                    if (fData->IsHighOrder() && fData->GetLowerOrderFunction().GetParamNum() > 0) {
                        auto* cond = fData->GetLowerOrderFunction().GetParam(0);
                        item.Condition = LoadHelper(*cond, item.LoadInfo);
                    }
                    else {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << fData->GetId() << " line " << fData->GetLine();
                        LogError(ss.str());
                    }
                    PushBlock();
                    for (int iix = 0; iix < fData->GetParamNum(); ++iix) {
                        BraceApiLoadInfo argLoadInfo;
                        auto statement = LoadHelper(*fData->GetParam(iix), argLoadInfo);
                        if (!statement.isNull())
                            item.Statements.push_back(std::move(statement));
                    }
                    item.ObjVars = CurBlockObjVars();
                    PopBlock();
                    m_Clauses.push_back(std::move(item));
                }
                else if (fData->GetId() == "else") {
                    if (fData != data.GetLast()) {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << fData->GetId() << " line " << fData->GetLine();
                        LogError(ss.str());
                    }
                    else {
                        Clause item;
                        PushBlock();
                        for (int iix = 0; iix < fData->GetParamNum(); ++iix) {
                            BraceApiLoadInfo argLoadInfo;
                            auto statement = LoadHelper(*fData->GetParam(iix), argLoadInfo);
                            if (!statement.isNull())
                                item.Statements.push_back(std::move(statement));
                        }
                        item.ObjVars = CurBlockObjVars();
                        PopBlock();
                        m_Clauses.push_back(std::move(item));
                    }
                }
                else {
                    //error
                    std::stringstream ss;
                    ss << "BraceScript error, " << fData->GetId() << " line " << fData->GetLine();
                    LogError(ss.str());
                }
            }
            executor.attach(this, &IfExp::Execute);
            return true;
        }
    private:
        int Execute(VariableInfo& gvars, VariableInfo& lvars)const
        {
            int ct = static_cast<int>(m_Clauses.size());
            for (int ix = 0; ix < ct; ++ix) {
                auto& clause = m_Clauses[ix];
                if (!clause.Condition.isNull())
                    clause.Condition(gvars, lvars);
                if (VarGetBoolean(clause.LoadInfo.IsGlobal ? gvars : lvars, clause.LoadInfo.Type, clause.LoadInfo.VarIndex)) {
                    for (auto& statement : clause.Statements) {
                        int v = statement(gvars, lvars);
                        if (IsForceQuit())
                            break;
                        if (v != BRACE_FLOW_CONTROL_NORMAL) {
                            FreeObjVars(lvars, clause.ObjVars);
                            return v;
                        }
                    }
                    FreeObjVars(lvars, clause.ObjVars);
                    break;
                }
                else if (ix == ct - 1 && clause.LoadInfo.Type == BRACE_DATA_TYPE_UNKNOWN) {
                    for (auto& statement : clause.Statements) {
                        int v = statement(gvars, lvars);
                        if (IsForceQuit())
                            break;
                        if (v != BRACE_FLOW_CONTROL_NORMAL) {
                            FreeObjVars(lvars, clause.ObjVars);
                            return v;
                        }
                    }
                    FreeObjVars(lvars, clause.ObjVars);
                    break;
                }
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        struct Clause
        {
            BraceApiExecutor Condition;
            BraceApiLoadInfo LoadInfo;
            std::vector<BraceApiExecutor> Statements;
            std::vector<int> ObjVars;
        };

        std::vector<Clause> m_Clauses;
    };
    class WhileExp final : public AbstractBraceApi
    {
    public:
        WhileExp(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_Condition(), m_LoadInfo(), m_Statements()
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& funcData, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            if (funcData.IsHighOrder()) {
                auto* cond = funcData.GetLowerOrderFunction().GetParam(0);
                m_Condition = LoadHelper(*cond, m_LoadInfo);
                PushBlock();
                for (int ix = 0; ix < funcData.GetParamNum(); ++ix) {
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*funcData.GetParam(ix), argLoadInfo);
                    if (!statement.isNull())
                        m_Statements.push_back(std::move(statement));
                }
                m_ObjVars = CurBlockObjVars();
                PopBlock();
                executor.attach(this, &WhileExp::Execute);
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << funcData.GetId() << " line " << funcData.GetLine();
                LogError(ss.str());
            }
            return true;
        }
        virtual bool LoadStatement(const FuncInfo& curFunc, const DslData::StatementData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //while(exp) func(args);
            if (data.GetFunctionNum() == 2) {
                auto* first = data.GetFirst()->AsFunction();
                auto* second = data.GetSecond()->AsFunction();
                const std::string& firstId = first->GetId();
                const std::string& secondId = second->GetId();
                if (firstId == "while" && !first->HaveStatement() && !first->HaveExternScript() &&
                    !secondId.empty() && !second->HaveStatement() && !second->HaveExternScript()) {
                    if (first->GetParamNum() > 0) {
                        auto* cond = first->GetParam(0);
                        m_Condition = LoadHelper(*cond, m_LoadInfo);
                    }
                    else {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << first->GetId() << " line " << first->GetLine();
                        LogError(ss.str());
                    }
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*second, argLoadInfo);
                    if (!statement.isNull())
                        m_Statements.push_back(std::move(statement));
                    executor.attach(this, &WhileExp::Execute);
                    return true;
                }
            }
            return false;
        }
    private:
        int Execute(VariableInfo& gvars, VariableInfo& lvars)const
        {
            for (; ; ) {
                if (!m_Condition.isNull())
                    m_Condition(gvars, lvars);
                if (VarGetBoolean(m_LoadInfo.IsGlobal ? gvars : lvars, m_LoadInfo.Type, m_LoadInfo.VarIndex)) {
                    for (auto& statement : m_Statements) {
                        int v = statement(gvars, lvars);
                        if (IsForceQuit()) {
                            FreeObjVars(lvars, m_ObjVars);
                            return v;
                        }
                        if (v == BRACE_FLOW_CONTROL_CONTINUE) {
                            break;
                        }
                        else if (v != BRACE_FLOW_CONTROL_NORMAL) {
                            FreeObjVars(lvars, m_ObjVars);
                            if (v == BRACE_FLOW_CONTROL_BREAK)
                                return BRACE_FLOW_CONTROL_NORMAL;
                            return v;
                        }
                    }
                }
                else {
                    break;
                }
            }
            FreeObjVars(lvars, m_ObjVars);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Condition;
        BraceApiLoadInfo m_LoadInfo;
        std::vector<BraceApiExecutor> m_Statements;
        std::vector<int> m_ObjVars;
    };
    class LoopExp final : public AbstractBraceApi
    {
    public:
        LoopExp(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_IteratorIndex(INVALID_INDEX), m_Count(), m_LoadInfo(), m_Statements()
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& funcData, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            if (funcData.IsHighOrder()) {
                auto* count = funcData.GetLowerOrderFunction().GetParam(0);
                m_Count = LoadHelper(*count, m_LoadInfo);
                PushBlock();
                m_IteratorIndex = AllocVariable("$$", m_LoadInfo.Type, m_LoadInfo.ObjectTypeId);
                for (int ix = 0; ix < funcData.GetParamNum(); ++ix) {
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*funcData.GetParam(ix), argLoadInfo);
                    if (!statement.isNull())
                        m_Statements.push_back(std::move(statement));
                }
                m_ObjVars = CurBlockObjVars();
                PopBlock();
                executor.attach(this, &LoopExp::Execute);
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << funcData.GetId() << " line " << funcData.GetLine();
                LogError(ss.str());
            }
            return true;
        }
        virtual bool LoadStatement(const FuncInfo& curFunc, const DslData::StatementData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //loop(exp) func(args);
            if (data.GetFunctionNum() == 2) {
                auto* first = data.GetFirst()->AsFunction();
                auto* second = data.GetSecond()->AsFunction();
                const std::string& firstId = first->GetId();
                const std::string& secondId = second->GetId();
                if (firstId == "loop" && !first->HaveStatement() && !first->HaveExternScript() &&
                    !secondId.empty() && !second->HaveStatement() && !second->HaveExternScript()) {
                    if (first->GetParamNum() > 0) {
                        auto* exp = first->GetParam(0);
                        m_Count = LoadHelper(*exp, m_LoadInfo);
                        m_IteratorIndex = AllocVariable("$$", m_LoadInfo.Type, m_LoadInfo.ObjectTypeId);
                    }
                    else {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << first->GetId() << " line " << first->GetLine();
                    }
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*second, argLoadInfo);
                    if (!statement.isNull())
                        m_Statements.push_back(std::move(statement));
                    executor.attach(this, &LoopExp::Execute);
                    return true;
                }
            }
            return false;
        }
    private:
        int Execute(VariableInfo& gvars, VariableInfo& lvars)const
        {
            if (!m_Count.isNull())
                m_Count(gvars, lvars);
            long ct = static_cast<long>(VarGetI64(m_LoadInfo.IsGlobal ? gvars : lvars, m_LoadInfo.Type, m_LoadInfo.VarIndex));
            for (int i = 0; i < ct; ++i) {
                VarSetI64(lvars, m_LoadInfo.Type, m_IteratorIndex, i);
                for (auto& statement : m_Statements) {
                    int v = statement(gvars, lvars);
                    if (IsForceQuit()) {
                        FreeObjVars(lvars, m_ObjVars);
                        return v;
                    }
                    if (v == BRACE_FLOW_CONTROL_CONTINUE) {
                        break;
                    }
                    else if (v != BRACE_FLOW_CONTROL_NORMAL) {
                        FreeObjVars(lvars, m_ObjVars);
                        if (v == BRACE_FLOW_CONTROL_BREAK)
                            return BRACE_FLOW_CONTROL_NORMAL;
                        return v;
                    }
                }
            }
            FreeObjVars(lvars, m_ObjVars);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        int m_IteratorIndex;
        BraceApiExecutor m_Count;
        BraceApiLoadInfo m_LoadInfo;
        std::vector<BraceApiExecutor> m_Statements;
        std::vector<int> m_ObjVars;
    };
    class ForeachExp final : public AbstractBraceApi
    {
    public:
        ForeachExp(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_IteratorIsUnsigned(false), m_IteratorIndex(INVALID_INDEX), m_Elements(), m_ElementLoadInfos(), m_Statements()
        {
        }
    protected:
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& funcData, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            int iteratorType = BRACE_DATA_TYPE_UNKNOWN;
            int iteratorObjTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            if (funcData.IsHighOrder()) {
                auto& callData = funcData.GetLowerOrderFunction();
                int num = callData.GetParamNum();
                bool typeMatch = true;
                int type = BRACE_DATA_TYPE_UNKNOWN;
                int objTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
                for (int ix = 0; ix < num; ++ix) {
                    auto* exp = callData.GetParam(ix); BraceApiLoadInfo elemLoadInfo;
                    auto e = LoadHelper(*exp, elemLoadInfo);
                    if (elemLoadInfo.Type != BRACE_DATA_TYPE_UNKNOWN) {
                        if (type == BRACE_DATA_TYPE_UNKNOWN) {
                            type = elemLoadInfo.Type;
                            objTypeId = elemLoadInfo.ObjectTypeId;
                        }
                        else if (type != elemLoadInfo.Type || objTypeId != elemLoadInfo.ObjectTypeId) {
                            typeMatch = false;
                        }
                    }
                    else {
                        typeMatch = false;
                    }
                    m_Elements.push_back(std::move(e));
                    m_ElementLoadInfos.push_back(std::move(elemLoadInfo));
                }
                iteratorType = type;
                iteratorObjTypeId = objTypeId;
                if (!typeMatch) {
                    std::stringstream ss;
                    ss << "BraceScript error, foreach list type dismatch, " << callData.GetId() << " line " << callData.GetLine();
                    LogError(ss.str());
                }
            }
            PushBlock();
            m_IteratorIsUnsigned = IsUnsignedType(iteratorType);
            m_IteratorIndex = AllocVariable("$$", iteratorType, iteratorObjTypeId);
            if (funcData.HaveStatement()) {
                int fnum = funcData.GetParamNum();
                for (int ix = 0; ix < fnum; ++ix) {
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*funcData.GetParam(ix), argLoadInfo);
                    if (!statement.isNull())
                        m_Statements.push_back(std::move(statement));
                }
            }
            m_ObjVars = CurBlockObjVars();
            PopBlock();
            executor.attach(this, &ForeachExp::Execute);
            return true;
        }
        virtual bool LoadStatement(const FuncInfo& curFunc, const DslData::StatementData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            //foreach(exp1,exp2,...) func(args);
            if (data.GetFunctionNum() == 2) {
                auto* first = data.GetFirst()->AsFunction();
                auto* second = data.GetSecond()->AsFunction();
                const std::string& firstId = first->GetId();
                const std::string& secondId = second->GetId();
                if (firstId == "foreach" && !first->HaveStatement() && !first->HaveExternScript() &&
                    !secondId.empty() && !second->HaveStatement() && !second->HaveExternScript()) {
                    int num = first->GetParamNum();
                    if (num > 0) {
                        bool typeMatch = true;
                        int type = BRACE_DATA_TYPE_UNKNOWN;
                        int objTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
                        for (int ix = 0; ix < num; ++ix) {
                            auto* exp = first->GetParam(ix);
                            BraceApiLoadInfo elemLoadInfo;
                            auto e = LoadHelper(*exp, elemLoadInfo);
                            if (elemLoadInfo.Type != BRACE_DATA_TYPE_UNKNOWN) {
                                if (type == BRACE_DATA_TYPE_UNKNOWN) {
                                    type = elemLoadInfo.Type;
                                    objTypeId = elemLoadInfo.ObjectTypeId;
                                }
                                else if (type != elemLoadInfo.Type || objTypeId != elemLoadInfo.ObjectTypeId) {
                                    typeMatch = false;
                                }
                            }
                            else {
                                typeMatch = false;
                            }
                            m_Elements.push_back(std::move(e));
                            m_ElementLoadInfos.push_back(std::move(elemLoadInfo));
                        }
                        m_IteratorIndex = AllocVariable("$$", type, objTypeId);
                        if (!typeMatch) {
                            std::stringstream ss;
                            ss << "BraceScript error, foreach list type dismatch, " << first->GetId() << " line " << first->GetLine();
                            LogError(ss.str());
                        }
                    }
                    else {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << first->GetId() << " line " << first->GetLine();
                        LogError(ss.str());
                    }
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*second, argLoadInfo);
                    if (!statement.isNull())
                        m_Statements.push_back(std::move(statement));
                    executor.attach(this, &ForeachExp::Execute);
                    return true;
                }
            }
            return false;
        }
    private:
        int Execute(VariableInfo& gvars, VariableInfo& lvars)const
        {
            for (int ix = 0; ix < static_cast<int>(m_Elements.size()); ++ix) {
                auto& elem = m_Elements[ix];
                if (!elem.isNull())
                    elem(gvars, lvars);
            }
            for (int ix = 0; ix < static_cast<int>(m_ElementLoadInfos.size()); ++ix) {
                auto& info = m_ElementLoadInfos[ix];
                auto* pvars = &lvars;
                if (info.IsGlobal)
                    pvars = &gvars;
                switch (info.Type) {
                case BRACE_DATA_TYPE_OBJECT: {
                    auto& v = VarGetObject(*pvars, info.VarIndex);
                    VarSetObject(lvars, m_IteratorIndex, v);
                }break;
                case BRACE_DATA_TYPE_STRING: {
                    auto& v = VarGetString(*pvars, info.VarIndex);
                    VarSetString(lvars, m_IteratorIndex, v);
                }break;
                default: {
                    if (m_IteratorIsUnsigned) {
                        auto v = VarGetU64(*pvars, info.Type, info.VarIndex);
                        VarSetU64(lvars, info.Type, m_IteratorIndex, v);
                    }
                    else {
                        auto v = VarGetI64(*pvars, info.Type, info.VarIndex);
                        VarSetI64(lvars, info.Type, m_IteratorIndex, v);
                    }
                }break;
                }
                for (auto& statement : m_Statements) {
                    int v = statement(gvars, lvars);
                    if (IsForceQuit()) {
                        FreeObjVars(lvars, m_ObjVars);
                        return v;
                    }
                    if (v == BRACE_FLOW_CONTROL_CONTINUE) {
                        break;
                    }
                    else if (v != BRACE_FLOW_CONTROL_NORMAL) {
                        FreeObjVars(lvars, m_ObjVars);
                        if (v == BRACE_FLOW_CONTROL_BREAK)
                            return BRACE_FLOW_CONTROL_NORMAL;
                        return v;
                    }
                }
            }
            FreeObjVars(lvars, m_ObjVars);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        bool m_IteratorIsUnsigned;
        int m_IteratorIndex;
        std::vector<BraceApiExecutor> m_Elements;
        std::vector<BraceApiLoadInfo> m_ElementLoadInfos;
        std::vector<BraceApiExecutor> m_Statements;
        std::vector<int> m_ObjVars;
    };
    class ParenthesisExp final : public AbstractBraceApi
    {
    public:
        ParenthesisExp(BraceScript& interpreter) :AbstractBraceApi(interpreter), m_Args(), m_ArgLoadInfos(), m_ResultInfo()
        {
        }
    protected:
        virtual bool LoadCall(const FuncInfo& curFunc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override
        {
            std::swap(m_Args, args);
            std::swap(m_ArgLoadInfos, argLoadInfos);
            if (argLoadInfos.size() > 0) {
                auto& lastLoadInfo = argLoadInfos[argLoadInfos.size() - 1];
                auto lastRealType = lastLoadInfo.GetLoadTimeRealType(curFunc);
                m_ResultInfo = lastLoadInfo;
                m_ResultInfo.Type = lastRealType.Type;
                m_ResultInfo.ObjectTypeId = lastRealType.ObjectTypeId;
                m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type, m_ResultInfo.ObjectTypeId);
                resultInfo = m_ResultInfo;
            }
            executor.attach(this, &ParenthesisExp::Execute);
            return true;
        }
    private:
        int Execute(VariableInfo& gvars, VariableInfo& lvars)const
        {
            for (auto& op : m_Args) {
                if (!op.isNull())
                    op(gvars, lvars);
            }
            if (m_ArgLoadInfos.size() > 0) {
                auto& info = m_ArgLoadInfos[m_ArgLoadInfos.size() - 1];
                int64_t v = VarGetI64(info.IsGlobal ? gvars : lvars, info.Type, info.VarIndex);
                VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v);
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        std::vector<BraceApiExecutor> m_Args;
        std::vector<BraceApiLoadInfo> m_ArgLoadInfos;
        BraceApiLoadInfo m_ResultInfo;
    };

#include "BraceScript_ArithUnit.inl"

    DataTypeInfo BraceApiLoadInfo::GetLoadTimeRealType(const FuncInfo& curFunc) const
    {
        if (Type == BRACE_DATA_TYPE_REF) {
            auto& ri = curFunc.VarInitInfo.ReferenceVars[VarIndex];
            return DataTypeInfo(ri.Type, ri.ObjectTypeId);
        }
        else {
            return DataTypeInfo(Type, ObjectTypeId);
        }
    }
    DataTypeInfo BraceApiLoadInfo::GetLoadTimeRealType(const VariableInfo& vars) const
    {
        if (Type == BRACE_DATA_TYPE_REF) {
            auto& ri = vars.ReferenceVars[VarIndex];
            return DataTypeInfo(ri.Type, ri.ObjectTypeId);
        }
        else {
            return DataTypeInfo(Type, ObjectTypeId);
        }
    }

    int VariableInfo::AllocVariable(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
        case BRACE_DATA_TYPE_INT8:
        case BRACE_DATA_TYPE_INT16:
        case BRACE_DATA_TYPE_INT32:
        case BRACE_DATA_TYPE_INT64:
        case BRACE_DATA_TYPE_UINT8:
        case BRACE_DATA_TYPE_UINT16:
        case BRACE_DATA_TYPE_UINT32:
        case BRACE_DATA_TYPE_UINT64:
        case BRACE_DATA_TYPE_FLOAT:
        case BRACE_DATA_TYPE_DOUBLE: {
            int ix = static_cast<int>(NumericVars.size());
            NumericValue nv{};
            NumericVars.push_back(nv);
            return ix;
        }
        case BRACE_DATA_TYPE_STRING: {
            int ix = static_cast<int>(StringVars.size());
            StringVars.push_back(std::string());
            return ix;
        }
        case BRACE_DATA_TYPE_OBJECT: {
            int ix = static_cast<int>(ObjectVars.size());
            ObjectVars.push_back(nullptr);
            return ix;
        }
        case BRACE_DATA_TYPE_REF: {
            int ix = static_cast<int>(ReferenceVars.size());
            ReferenceVars.push_back(ReferenceInfo());
            return ix;
        }
        }
        return INVALID_INDEX;
    }

    VariableInfo* FuncInfo::AllocVariableInfo(void)const
    {
        if (VariableInfoPool->empty()) {
            auto* p = new VariableInfo();
            *p = VarInitInfo;
            VariableInfoStore->push_back(p);
            return p;
        }
        else {
            auto* p = VariableInfoPool->back();
            VariableInfoPool->pop_back();
            return p;
        }
    }
    void FuncInfo::RecycleVariableInfo(VariableInfo* p)const
    {
        VariableInfoPool->push_back(p);
    }
    void FuncInfo::ShrinkPool(int max_num)const
    {
        while (static_cast<int>(VariableInfoPool->size()) > max_num) {
            auto* p = VariableInfoPool->front();
            VariableInfoPool->pop_front();
            auto it = std::find(VariableInfoStore->begin(), VariableInfoStore->end(), p);
            if (it != VariableInfoStore->end()) {
                delete p;
                VariableInfoStore->erase(it);
            }
        }
    }
    FuncInfo::FuncInfo(void)
    {
        VariableInfoPool = new std::deque<VariableInfo*>();
        VariableInfoStore = new std::vector<VariableInfo*>();
    }
    FuncInfo::FuncInfo(const FuncInfo& other)
    {
        VariableInfoPool = new std::deque<VariableInfo*>();
        VariableInfoStore = new std::vector<VariableInfo*>();

        Name = other.Name;
        Params = other.Params;
        RetValue = other.RetValue;
        VarTypeInfos = other.VarTypeInfos;
        Codes = other.Codes;
        VarInitInfo = other.VarInitInfo;
    }
    FuncInfo::FuncInfo(FuncInfo&& other) noexcept
    {
        VariableInfoPool = other.VariableInfoPool;
        other.VariableInfoPool = nullptr;
        VariableInfoStore = other.VariableInfoStore;
        other.VariableInfoStore = nullptr;

        Name = std::move(other.Name);
        Params = std::move(other.Params);
        RetValue = std::move(other.RetValue);
        VarTypeInfos = std::move(other.VarTypeInfos);
        Codes = std::move(other.Codes);
        VarInitInfo = std::move(other.VarInitInfo);
    }
    FuncInfo::~FuncInfo(void)
    {
        if (VariableInfoPool) {
            VariableInfoPool->clear();
            delete VariableInfoPool;
            VariableInfoPool = nullptr;
        }
        if (VariableInfoStore) {
            for (auto* p : *VariableInfoStore) {
                delete p;
            }
            VariableInfoStore->clear();
            delete VariableInfoStore;
            VariableInfoStore = nullptr;
        }
    }

    FuncInfo* BraceScript::GlobalFuncInfo(void)const
    {
        return m_GlobalFunc;
    }
    VariableInfo* BraceScript::GlobalVariables(void)const
    {
        return m_GlobalVariables;
    }
    const FuncInfo* BraceScript::CurRuntimeFuncInfo(void)const
    {
        auto& runtimeStack = GetRuntimeStack();
        if (runtimeStack.empty()) {
            return m_GlobalFunc;
        }
        return runtimeStack.top().Func;
    }
    VariableInfo* BraceScript::CurRuntimeVariables(void)const
    {
        auto& runtimeStack = GetRuntimeStack();
        if (runtimeStack.empty()) {
            return m_GlobalVariables;
        }
        return runtimeStack.top().Variables;
    }
    void BraceScript::PushRuntimeStack(const FuncInfo* funcInfo)
    {
        auto& runtimeStack = GetRuntimeStack();
        RuntimeStackInfo rsi{};
        rsi.Func = funcInfo;
        rsi.Variables = funcInfo->AllocVariableInfo();
        runtimeStack.push(std::move(rsi));
    }
    void BraceScript::PopRuntimeStack(void)
    {
        auto& runtimeStack = GetRuntimeStack();
        RuntimeStackInfo& info = runtimeStack.top();
        info.Func->RecycleVariableInfo(info.Variables);
        runtimeStack.pop();
    }

    void BraceScript::AddSyntaxComponent(DslData::ISyntaxComponent* p)
    {
        m_AddedSyntaxComponents.push_back(p);
    }
    void BraceScript::AddApiInstance(IBraceApi* p)
    {
        m_ApiInstances.push_back(p);
    }
    IBraceApi* BraceScript::CreateApi(const std::string& name)
    {
        auto it = m_ApiFactories.find(name);
        if (it != m_ApiFactories.end()) {
            auto* p = it->second->Create(*this);
            if (p)
                AddApiInstance(p);
            return p;
        }
        else {
            return nullptr;
        }
    }

    void BraceScript::LogInfo(const std::string& info)
    {
        if (OnInfo)
            OnInfo(info);
    }
    void BraceScript::LogWarn(const std::string& warn)
    {
        m_HasWarn = true;
        if (OnWarn)
            OnWarn(warn);
    }
    void BraceScript::LogError(const std::string& error)
    {
        m_HasError = true;
        if (OnError)
            OnError(error);
    }
    int BraceScript::GetObjectTypeId(const DslData::ISyntaxComponent& typeSyntax)const
    {
        if (OnGetObjectTypeId)
            return OnGetObjectTypeId(typeSyntax);
        return PREDEFINED_BRACE_OBJECT_TYPE_UNKNOWN;
    }
    const char* BraceScript::GetObjectTypeName(int objTypeId)const
    {
        if (OnGetObjectTypeName)
            return OnGetObjectTypeName(objTypeId);
        return "unknown";
    }
    ParamTypeInfo BraceScript::ParseParamTypeInfo(const DslData::ISyntaxComponent& syntax)const
    {
        //&typename<:typeparams:>
        ParamTypeInfo tinfo{};
        if (syntax.GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
            auto& funcData = static_cast<const DslData::FunctionData&>(syntax);
            if (funcData.GetId() == "&") {
                tinfo.IsRef = true;
                auto* pTypeDesc = funcData.GetParam(0);
                if (pTypeDesc->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                    auto& tfuncData = static_cast<const DslData::FunctionData&>(*pTypeDesc);
                    if (tfuncData.GetParamClassUnmasked() == DslData::FunctionData::PARAM_CLASS_ANGLE_BRACKET_COLON) {
                        tinfo.Type = GetDataType(tfuncData.GetId());
                        tinfo.ObjectTypeId = GetObjectTypeId(tfuncData);
                    }
                }
                else if (pTypeDesc->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_VALUE) {
                    tinfo.Type = GetDataType(pTypeDesc->GetId());
                    tinfo.ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
                }
            }
            else if (funcData.GetParamClassUnmasked() == DslData::FunctionData::PARAM_CLASS_ANGLE_BRACKET_COLON) {
                tinfo.Type = GetDataType(funcData.GetId());
                tinfo.ObjectTypeId = GetObjectTypeId(funcData);
                tinfo.IsRef = false;
            }
        }
        else if (syntax.GetSyntaxType() == DslData::ISyntaxComponent::TYPE_VALUE) {
            tinfo.Type = GetDataType(syntax.GetId());
            tinfo.ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            tinfo.IsRef = false;
        }
        return tinfo;
    }
    bool BraceScript::CanAssign(int destType, int destObjTypeId, int srcType, int srcObjTypeId) const
    {
        if (destType == BRACE_DATA_TYPE_OBJECT && srcType == BRACE_DATA_TYPE_OBJECT) {
            if (destObjTypeId == srcObjTypeId || srcObjTypeId == PREDEFINED_BRACE_OBJECT_TYPE_NULL) {
                return true;
            }
            else if(OnObjectAssignCheck) {
                return OnObjectAssignCheck(destObjTypeId, srcObjTypeId);
            }
            else {
                return false;
            }
        }
        else {
            return Brace::CanAssign(destType, srcType);
        }
    }
    const FuncApiTypeInfo* BraceScript::GetFuncApiTypeInfo(const std::string& name)const
    {
        auto it = m_FuncApiTypeInfos.find(name);
        if (it != m_FuncApiTypeInfos.end()) {
            return &(it->second);
        }
        return nullptr;
    }
    FuncApiTypeInfo* BraceScript::GetFuncApiTypeInfo(const std::string& name)
    {
        auto it = m_FuncApiTypeInfos.find(name);
        if (it != m_FuncApiTypeInfos.end()) {
            return &(it->second);
        }
        return nullptr;
    }
    const FuncInfo* BraceScript::GetFuncInfo(const std::string& name)const
    {
        auto it = m_Funcs.find(name);
        if (it != m_Funcs.end())
            return &(it->second);
        return nullptr;
    }
    FuncInfo* BraceScript::GetFuncInfo(const std::string& name)
    {
        auto it = m_Funcs.find(name);
        if (it != m_Funcs.end())
            return &(it->second);
        return nullptr;
    }
    const FuncInfo* BraceScript::CurFuncInfo(void)const
    {
        if (m_FuncInfoStack.empty())
            return m_GlobalFunc;
        return m_FuncInfoStack.top();
    }
    FuncInfo* BraceScript::CurFuncInfo(void)
    {
        if (m_FuncInfoStack.empty())
            return m_GlobalFunc;
        return m_FuncInfoStack.top();
    }
    FuncInfo* BraceScript::PushFuncInfo(const std::string& name)
    {
        FuncInfo* p = GetOrAddFuncInfo(name);
        m_FuncInfoStack.push(p);
        PushBlock();
        return p;
    }
    void BraceScript::PopFuncInfo(void)
    {
        PopBlock();
        m_FuncInfoStack.pop();
    }
    int BraceScript::CurBlockId(void)const
    {
        if (m_LexicalScopeStack.empty())
            return 0;
        return m_LexicalScopeStack.back().BlockId;
    }
    const std::vector<int>& BraceScript::CurBlockObjVars(void)const {
        return m_LexicalScopeStack.back().ObjVars;
    }
    std::vector<int>& BraceScript::CurBlockObjVars(void) {
        return m_LexicalScopeStack.back().ObjVars;
    }
    void BraceScript::PushBlock(void)
    {
        ++m_LastBlockId;
        BlockInfo bi(m_LastBlockId);
        m_LexicalScopeStack.push_back(std::move(bi));
    }
    void BraceScript::PopBlock(void)
    {
        m_LexicalScopeStack.pop_back();
    }
    std::string BraceScript::CalcVarKey(const std::string& name, int blockId)const
    {
        std::string key = name + "__" + std::to_string(blockId);
        return key;
    }
    std::string BraceScript::CalcConstKey(int tok_type, const std::string& value)const
    {
        if (tok_type == DslData::ValueData::VALUE_TYPE_STRING) {
            return "\"" + value + "\"";
        }
        else {
            return "[" + value + "]";
        }
    }
    int BraceScript::AllocGlobalVariable(const std::string& name, int type, int objTypeId)
    {
        auto it = m_GlobalFunc->VarTypeInfos.find(name);
        if (it == m_GlobalFunc->VarTypeInfos.end()) {
            int index = m_GlobalFunc->VarInitInfo.AllocVariable(type);
            m_GlobalFunc->VarTypeInfos.insert(std::make_pair(name, VarInfo(name, type, objTypeId, index, true)));
            return index;
        }
        else {
            return it->second.VarIndex;
        }
    }
    auto BraceScript::FindVariable(FuncInfo* curFunc, const std::string& name, std::string& key, int& level) const -> decltype(curFunc->VarTypeInfos.end())
    {
        key = CalcVarKey(name, CurBlockId());
        std::string fkey = key;
        int curLevel = static_cast<int>(m_LexicalScopeStack.size());
        decltype(curFunc->VarTypeInfos.end()) it;
        while (curLevel >= 0) {
            it = curFunc->VarTypeInfos.find(fkey);
            if (it != curFunc->VarTypeInfos.end())
                break;
            --curLevel;
            if (curLevel > 0)
                fkey = CalcVarKey(name, m_LexicalScopeStack[curLevel - 1].BlockId);
            else
                fkey = CalcVarKey(name, 0);
        }
        return it;
    }
    int BraceScript::AllocVariable(const std::string& name, int type, int objTypeId)
    {
        auto* curFunc = CurFuncInfo();
        std::string key = CalcVarKey(name, CurBlockId());
        auto it = curFunc->VarTypeInfos.find(key);
        if (it == curFunc->VarTypeInfos.end()) {
            int index = curFunc->VarInitInfo.AllocVariable(type);
            curFunc->VarTypeInfos.insert(std::make_pair(key, VarInfo(name, type, objTypeId, index)));
            if (type == BRACE_DATA_TYPE_OBJECT) {
                auto& bi = m_LexicalScopeStack.back();
                bi.ObjVars.push_back(index);
            }
            return index;
        }
        else {
            std::stringstream ss;
            ss << "INTERNAL BraceScript error, duplicated var: " << name << " type: " << GetDataTypeName(type) << " obj type id: " << GetObjectTypeName(objTypeId) << " exists var index: " << it->second.VarIndex;
            LogError(ss.str());
            return -1;
        }
    }
    int BraceScript::AllocConst(int tok_type, const std::string& value, int& type)
    {
        std::string key = CalcConstKey(tok_type, value);
        auto* curFunc = GlobalFuncInfo();
        auto it = curFunc->VarTypeInfos.find(key);
        if (it == curFunc->VarTypeInfos.end()) {
            int index = INVALID_INDEX;
            type = BRACE_DATA_TYPE_UNKNOWN;
            switch (tok_type) {
            case DslData::ValueData::VALUE_TYPE_IDENTIFIER:
                if (value == "true" || value == "false") {
                    type = BRACE_DATA_TYPE_BOOL;
                    index = curFunc->VarInitInfo.AllocVariable(type);
                    curFunc->VarInitInfo.NumericVars[index].BoolVal = value == "true";
                }
                else if (value == "null") {
                    type = BRACE_DATA_TYPE_OBJECT;
                    index = curFunc->VarInitInfo.AllocVariable(type);
                    curFunc->VarInitInfo.ObjectVars[index] = nullptr;
                }
                break;
            case DslData::ValueData::VALUE_TYPE_STRING:
                type = BRACE_DATA_TYPE_STRING;
                index = curFunc->VarInitInfo.AllocVariable(type);
                curFunc->VarInitInfo.StringVars[index] = value;
                break;
            case DslData::ValueData::VALUE_TYPE_NUM:
                if (value.find('.', 0) != std::string::npos) {
                    double v = StrToDouble(value);
                    if (v >= std::numeric_limits<float>::min() && v <= std::numeric_limits<float>::max()) {
                        type = BRACE_DATA_TYPE_FLOAT;
                        index = curFunc->VarInitInfo.AllocVariable(type);
                        curFunc->VarInitInfo.NumericVars[index].FloatVal = static_cast<float>(v);
                    }
                    else {
                        type = BRACE_DATA_TYPE_DOUBLE;
                        index = curFunc->VarInitInfo.AllocVariable(type);
                        curFunc->VarInitInfo.NumericVars[index].DoubleVal = v;
                    }
                }
                else if (value.length() > 0 && value[0] == '-') {
                    int64_t v = StrToInt64(value);
                    if (v >= std::numeric_limits<int32_t>::min()) {
                        type = BRACE_DATA_TYPE_INT32;
                        index = curFunc->VarInitInfo.AllocVariable(type);
                        curFunc->VarInitInfo.NumericVars[index].Int32Val = static_cast<int32_t>(v);
                    }
                    else if (v >= std::numeric_limits<int64_t>::min()) {
                        type = BRACE_DATA_TYPE_INT64;
                        index = curFunc->VarInitInfo.AllocVariable(type);
                        curFunc->VarInitInfo.NumericVars[index].Int64Val = v;
                    }
                }
                else {
                    uint64_t v = StrToUInt64(value);
                    if (v <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max())) {
                        type = BRACE_DATA_TYPE_INT32;
                        index = curFunc->VarInitInfo.AllocVariable(type);
                        curFunc->VarInitInfo.NumericVars[index].Int32Val = static_cast<int32_t>(v);
                    }
                    else if (v <= std::numeric_limits<uint32_t>::max()) {
                        type = BRACE_DATA_TYPE_UINT32;
                        index = curFunc->VarInitInfo.AllocVariable(type);
                        curFunc->VarInitInfo.NumericVars[index].UInt32Val = static_cast<uint32_t>(v);
                    }
                    else if (v <= static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
                        type = BRACE_DATA_TYPE_INT64;
                        index = curFunc->VarInitInfo.AllocVariable(type);
                        curFunc->VarInitInfo.NumericVars[index].Int64Val = static_cast<int64_t>(v);
                    }
                    else if (v <= std::numeric_limits<uint64_t>::max()) {
                        type = BRACE_DATA_TYPE_UINT64;
                        index = curFunc->VarInitInfo.AllocVariable(type);
                        curFunc->VarInitInfo.NumericVars[index].UInt64Val = v;
                    }
                }
                break;
            }
            if (type != BRACE_DATA_TYPE_UNKNOWN) {
                if(type==BRACE_DATA_TYPE_OBJECT)
                    curFunc->VarTypeInfos.insert(std::make_pair(key, VarInfo(value, type, PREDEFINED_BRACE_OBJECT_TYPE_NULL, index, true)));
                else
                    curFunc->VarTypeInfos.insert(std::make_pair(key, VarInfo(value, type, PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ, index, true)));
            }
            return index;
        }
        else {
            return it->second.VarIndex;
        }
    }
    BraceApiExecutor BraceScript::Load(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& resultInfo)
    {
        BraceApiExecutor tempExecutor;
        if (DoFilterLoad(syntaxUnit, resultInfo, tempExecutor)) {
            return tempExecutor;
        }
        switch (syntaxUnit.GetSyntaxType()) {
        case DslData::ISyntaxComponent::TYPE_VALUE:
            return LoadValue(static_cast<const DslData::ValueData&>(syntaxUnit), resultInfo);
        case DslData::ISyntaxComponent::TYPE_FUNCTION:
            return LoadFunction(static_cast<const DslData::FunctionData&>(syntaxUnit), resultInfo);
        case DslData::ISyntaxComponent::TYPE_STATEMENT:
            return LoadStatement(static_cast<const DslData::StatementData&>(syntaxUnit), resultInfo);
        default:
            return BraceApiExecutor();
        }
    }
    BraceApiExecutor BraceScript::LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& resultInfo)
    {
        BraceApiExecutor executor;
        int idType = data.GetIdType();
        if (idType == DslData::ValueData::VALUE_TYPE_IDENTIFIER) {
            const std::string& id = data.GetId();
            auto* p = CreateApi(id);
            if (nullptr != p) {
                //Converts the name to a function without arguments
                auto* fd = new DslData::FunctionData();
                AddSyntaxComponent(fd);
                fd->SetName(data);
                fd->SetParamClass(DslData::FunctionData::PARAM_CLASS_PARENTHESIS);
                if (!p->Load(*fd, resultInfo, executor)) {
                    //error
                    std::stringstream ss;
                    ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                    LogError(ss.str());
                }
                return executor;
            }
            else if (id == "break") {
                auto* pBreak = new BreakExp(*this);
                AddApiInstance(pBreak);
                pBreak->Load(data, resultInfo, executor);
                return executor;
            }
            else if (id == "continue") {
                auto* pContinue = new ContinueExp(*this);
                AddApiInstance(pContinue);
                pContinue->Load(data, resultInfo, executor);
                return executor;
            }
            else if (id == "true" || id == "false" || id == "null") {
                auto* pConstGet = new ConstGet(*this);
                AddApiInstance(pConstGet);
                pConstGet->Load(data, resultInfo, executor);
                return executor;
            }
            else if (id.length() > 0 && id[0] == '$') {
                auto* pLocalGet = new LocalVarGet(*this);
                AddApiInstance(pLocalGet);
                pLocalGet->Load(data, resultInfo, executor);
                return executor;
            }
            else if (id.length() > 0 && id[0] == '@') {
                auto* pGlobalGet = new GlobalVarGet(*this);
                AddApiInstance(pGlobalGet);
                pGlobalGet->Load(data, resultInfo, executor);
                return executor;
            }
            else if (!DoLoadValueFailed(data, resultInfo, executor)) {
                //error
                std::stringstream ss;
                ss << "BraceScript error, var must start with '$' or '@', " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
            }
            return executor;
        }
        else {
            auto* pConstGet = new ConstGet(*this);
            AddApiInstance(pConstGet);
            pConstGet->Load(data, resultInfo, executor);
            return executor;
        }
    }
    static inline void ConvertMember(DslData::ISyntaxComponent* p, int paramClass)
    {
        if (p->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_VALUE) {
            auto* pvd = static_cast<DslData::ValueData*>(p);
            if (pvd->IsIdentifier() && (paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD
                || paramClass == DslData::FunctionData::PARAM_CLASS_POINTER
                || paramClass == DslData::FunctionData::PARAM_CLASS_QUESTION_PERIOD)) {
                pvd->SetType(DslData::ValueData::VALUE_TYPE_STRING);
            }
        }
    }
    BraceApiExecutor BraceScript::LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo)
    {
        BraceApiExecutor executor;
        if (data.HaveParam()) {
            auto& callData = data;
            if (!callData.HaveId() && !callData.IsHighOrder() && (callData.GetParamClassUnmasked() == DslData::FunctionData::PARAM_CLASS_PARENTHESIS || callData.GetParamClassUnmasked() == DslData::FunctionData::PARAM_CLASS_BRACKET)) {
                switch (callData.GetParamClassUnmasked()) {
                case DslData::FunctionData::PARAM_CLASS_PARENTHESIS: {
                    int num = callData.GetParamNum();
                    if (num == 1) {
                        auto* param = callData.GetParam(0);
                        return Load(*param, resultInfo);
                    }
                    else {
                        auto* p = new ParenthesisExp(*this);
                        AddApiInstance(p);
                        p->Load(data, resultInfo, executor);
                        return executor;
                    }
                }break;
                case DslData::FunctionData::PARAM_CLASS_BRACKET: {
                    auto* p = CreateApi("array");
                    p->Load(data, resultInfo, executor);
                    return executor;
                }break;
                }
            }
            else if (!callData.HaveParam()) {
                //regeneration
                return Load(callData.GetName(), resultInfo);
            }
            else {
                int paramClass = callData.GetParamClassUnmasked();
                auto& op = callData.GetId();
                if (callData.IsOperatorParamClass() && ((op.length() == 1 && op[0] == '=') ||
                    (op.length() == 2 && op[0] == '+' && op[1] == '=') ||
                    (op.length() == 2 && op[0] == '-' && op[1] == '=') ||
                    (op.length() == 2 && op[0] == '*' && op[1] == '=') ||
                    (op.length() == 2 && op[0] == '/' && op[1] == '=') ||
                    (op.length() == 2 && op[0] == '%' && op[1] == '=') ||
                    (op.length() == 2 && op[0] == '&' && op[1] == '=') ||
                    (op.length() == 2 && op[0] == '|' && op[1] == '=') ||
                    (op.length() == 3 && op[0] == '>' && op[1] == '>' && op[2] == '=') ||
                    (op.length() == 3 && op[0] == '<' && op[1] == '<' && op[2] == '='))) {//assignment
                    DslData::FunctionData* pFunc = nullptr;
                    auto* pParam = callData.GetParam(0);
                    if (pParam && pParam->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                        auto* innerCall = static_cast<DslData::FunctionData*>(pParam);
                        if (nullptr != innerCall) {
                            //obj.property = val -> memberset(obj, property, val)
                            //obj.property += val -> memberset(obj, property, memberget(obj, property) + val)
                            int innerParamClass = innerCall->GetParamClassUnmasked();
                            if (innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD ||
                                innerParamClass == DslData::FunctionData::PARAM_CLASS_BRACKET ||
                                innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACE ||
                                innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACKET ||
                                innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD_PARENTHESIS) {
                                auto* newCall = new DslData::FunctionData();
                                AddSyntaxComponent(newCall);
                                if (innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD)
                                    newCall->SetName(DslData::ValueData("memberset", DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                                else
                                    newCall->SetName(DslData::ValueData("collectionset", DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                                newCall->SetParamClass(DslData::FunctionData::PARAM_CLASS_PARENTHESIS);
                                if (innerCall->IsHighOrder()) {
                                    newCall->AddParamCopyFrom(innerCall->GetLowerOrderFunction());
                                    auto* p = newCall->AddParamCopyFrom(*innerCall->GetParam(0));
                                    ConvertMember(p, innerParamClass);
                                    if (op.length() == 1) {
                                        newCall->AddParamCopyFrom(*callData.GetParam(1));
                                    }
                                    else {
                                        auto* newCalc = newCall->AddFunctionParam();
                                        newCalc->SetName(DslData::ValueData(op.substr(0, op.length() - 1), DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                                        
                                        auto* newGet = newCalc->AddFunctionParam();
                                        if (innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD)
                                            newGet->SetName(DslData::ValueData("memberget", DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                                        else
                                            newGet->SetName(DslData::ValueData("collectionget", DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                                        newGet->AddParamCopyFrom(innerCall->GetLowerOrderFunction());
                                        newGet->AddParamCopyFrom(*innerCall->GetParam(0));

                                        newCalc->AddParamCopyFrom(*callData.GetParam(1));
                                    }
                                }
                                else {
                                    newCall->AddParamCopyFrom(innerCall->GetName());
                                    auto* p = newCall->AddParamCopyFrom(*innerCall->GetParam(0));
                                    ConvertMember(p, innerParamClass);
                                    if (op.length() == 1) {
                                        newCall->AddParamCopyFrom(*callData.GetParam(1));
                                    }
                                    else {
                                        auto* newCalc = newCall->AddFunctionParam();
                                        newCalc->SetName(DslData::ValueData(op.substr(0, op.length() - 1), DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                                        
                                        auto* newGet = newCalc->AddFunctionParam();
                                        if (innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD)
                                            newGet->SetName(DslData::ValueData("memberget", DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                                        else
                                            newGet->SetName(DslData::ValueData("collectionget", DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                                        newGet->AddParamCopyFrom(innerCall->GetName());
                                        newGet->AddParamCopyFrom(*innerCall->GetParam(0));

                                        newCalc->AddParamCopyFrom(*callData.GetParam(1));
                                    }
                                }

                                return Load(*newCall, resultInfo);
                            }
                            else if (op.length() == 1 && innerCall->GetId() == ":" && innerCall->GetParamNum() == 2) {
                                pFunc = innerCall;
                            }
                        }
                    }
                    if (op.length() == 1) {
                        IBraceApi* api0 = nullptr;
                        const std::string& varId = pFunc ? pFunc->GetParamId(0) : callData.GetParamId(0);
                        if (varId.length() > 0 && varId[0] == '$') {
                            api0 = new LocalVarSet(*this);
                            AddApiInstance(api0);
                        }
                        else if (varId.length() > 0 && varId[0] == '@') {
                            api0 = new GlobalVarSet(*this);
                            AddApiInstance(api0);
                        }
                        if (nullptr != api0) {
                            api0->Load(data, resultInfo, executor);
                            return executor;
                        }
                    }
                }
                else if (op == "+" && callData.GetParamNum() == 1) {
                    auto* p = new PositiveExp(*this, false);
                    AddApiInstance(p);
                    p->Load(callData, resultInfo, executor);
                    return executor;
                }
                else if (op == "-" && callData.GetParamNum() == 1) {
                    auto* p = new NegativeExp(*this, false);
                    AddApiInstance(p);
                    p->Load(callData, resultInfo, executor);
                    return executor;
                }
                else if (op == "<-") {
                    //Single-parameter statements, written without parentheses
                    if (callData.GetParamNum() == 2) {
                        auto* p = CreateApi(callData.GetParamId(0));
                        p->Load(callData, resultInfo, executor);
                        return executor;
                    }
                }
                else if (op == "=>") {
                    //lambda expression
                    auto* p = CreateApi("lambda");
                    p->Load(callData, resultInfo, executor);
                    return executor;
                }
                else if (op == ":") {
                    //decl expression
                    if (callData.GetParamNum() == 2) {
                        auto* p1 = callData.GetParam(0);
                        auto* p2 = callData.GetParam(1);
                        if (p1->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_VALUE &&
                            (p2->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_VALUE ||
                                (p2->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION && static_cast<DslData::FunctionData*>(p2)->GetParamClassUnmasked() == DslData::FunctionData::PARAM_CLASS_ANGLE_BRACKET_COLON))) {
                            const std::string& id = p1->GetId();
                            if (id.length() > 0 && id[0] == '$') {
                                auto* pLocalDecl = new LocalVarDecl(*this);
                                AddApiInstance(pLocalDecl);
                                pLocalDecl->Load(data, resultInfo, executor);
                                return executor;
                            }
                            else if (id.length() > 0 && id[0] == '@') {
                                auto* pGlobalDecl = new GlobalVarDecl(*this);
                                AddApiInstance(pGlobalDecl);
                                pGlobalDecl->Load(data, resultInfo, executor);
                                return executor;
                            }
                        }
                    }
                }
                else {
                    if (callData.IsHighOrder()) {
                        auto& innerCall = callData.GetLowerOrderFunction();
                        int innerParamClass = innerCall.GetParamClassUnmasked();
                        if (paramClass == DslData::FunctionData::PARAM_CLASS_PARENTHESIS && (
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD ||
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_BRACKET ||
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACE ||
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACKET ||
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD_PARENTHESIS)) {
                            //obj.member(a,b,...) or obj[member](a,b,...) or obj.(member)(a,b,...) or obj.[member](a,b,...) or obj.{member}(a,b,...) -> membercall(obj,member,a,b,...)
                            std::string apiName;
                            std::string member = innerCall.GetParamId(0);
                            if (member == "orderby" || member == "orderbydesc" || member == "where" || member == "top") {
                                apiName = "linq";
                            }
                            else if (innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD) {
                                apiName = "membercall";
                            }
                            else {
                                apiName = "collectioncall";
                            }
                            auto* newCall = new DslData::FunctionData();
                            AddSyntaxComponent(newCall);
                            newCall->SetName(DslData::ValueData(apiName, DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                            newCall->SetParamClass(DslData::FunctionData::PARAM_CLASS_PARENTHESIS);
                            if (innerCall.IsHighOrder()) {
                                newCall->AddParamCopyFrom(innerCall.GetLowerOrderFunction());
                                auto* p = newCall->AddParamCopyFrom(*innerCall.GetParam(0));
                                ConvertMember(p, innerParamClass);
                                for (int i = 0; i < callData.GetParamNum(); ++i) {
                                    newCall->AddParamCopyFrom(*callData.GetParam(i));
                                }
                            }
                            else {
                                newCall->AddParamCopyFrom(innerCall.GetName());
                                auto* p = newCall->AddParamCopyFrom(*innerCall.GetParam(0));
                                ConvertMember(p, innerParamClass);
                                for (int i = 0; i < callData.GetParamNum(); ++i) {
                                    newCall->AddParamCopyFrom(*callData.GetParam(i));
                                }
                            }

                            return Load(*newCall, resultInfo);
                        }
                    }
                    if (paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD ||
                        paramClass == DslData::FunctionData::PARAM_CLASS_BRACKET ||
                        paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACE ||
                        paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACKET ||
                        paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD_PARENTHESIS) {
                        //obj.property or obj[property] or obj.(property) or obj.[property] or obj.{property} -> memberget(obj,property)
                        auto* newCall = new DslData::FunctionData();
                        AddSyntaxComponent(newCall);
                        if (paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD)
                            newCall->SetName(DslData::ValueData("memberget", DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                        else
                            newCall->SetName(DslData::ValueData("collectionget", DslData::ValueData::VALUE_TYPE_IDENTIFIER));
                        newCall->SetParamClass(DslData::FunctionData::PARAM_CLASS_PARENTHESIS);
                        if (callData.IsHighOrder()) {
                            newCall->AddParamCopyFrom(callData.GetLowerOrderFunction());
                            auto* p = newCall->AddParamCopyFrom(*callData.GetParam(0));
                            ConvertMember(callData.GetParam(0), callData.GetParamClassUnmasked());
                        }
                        else {
                            newCall->AddParamCopyFrom(callData.GetName());
                            auto* p = newCall->AddParamCopyFrom(*callData.GetParam(0));
                            ConvertMember(callData.GetParam(0), callData.GetParamClassUnmasked());
                        }

                        return Load(*newCall, resultInfo);
                    }
                }
            }
        }
        else {
            if (data.HaveStatement()) {
                if (!data.HaveId() && !data.IsHighOrder()) {
                    auto* p = CreateApi("hashtable");
                    p->Load(data, resultInfo, executor);
                    return executor;
                }
            }
            else if (!data.HaveExternScript()) {
                //degeneration
                return Load(data.GetName(), resultInfo);
            }
        }
        IBraceApi* api = nullptr;
        const std::string& name = data.GetId();
        if (m_Funcs.find(name) != m_Funcs.end()) {
            api = new FunctionExecutor(*this);
            AddApiInstance(api);
        }
        else {
            api = CreateApi(name);
        }
        if (nullptr != api) {
            if (!api->Load(data, resultInfo, executor)) {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
            }
        }
        else {
            if (!DoLoadFunctionFailed(data, resultInfo, executor)) {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
            }
        }
        return executor;
    }
    BraceApiExecutor BraceScript::LoadStatement(const DslData::StatementData& data, BraceApiLoadInfo& resultInfo)
    {
        BraceApiExecutor executor;
        IBraceApi* ret = CreateApi(data.GetId());
        if (nullptr != ret) {
            auto* first = data.GetFirst()->AsValue();
            if (nullptr != first) {
                //convert command line to function call
                auto* fd = new DslData::FunctionData();
                AddSyntaxComponent(fd);
                fd->SetName(*first);
                for (int argi = 1; argi < data.GetFunctionNum(); ++argi) {
                    auto* pfd = data.GetFunction(argi);
                    if (nullptr != pfd) {
                        fd->AddParamCopyFrom(*pfd);
                    }
                }
                if (!ret->Load(*fd, resultInfo, executor)) {
                    //error
                    std::stringstream ss;
                    ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                    LogError(ss.str());
                }
                return executor;
            }
            if (!ret->Load(data, resultInfo, executor)) {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
            }
        }
        else if (!DoLoadStatementFailed(data, resultInfo, executor)) {
            //error
            std::stringstream ss;
            ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
            LogError(ss.str());
        }
        return executor;
    }

    bool BraceScript::DoFilterLoad(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
    {
        if (OnFilterLoad)
            return OnFilterLoad(syntaxUnit, resultInfo, executor);
        return false;
    }
    bool BraceScript::DoLoadValueFailed(const DslData::ValueData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
    {
        if (OnLoadValueFailed)
            return OnLoadValueFailed(data, resultInfo, executor);
        return false;
    }
    bool BraceScript::DoLoadFunctionFailed(const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
    {
        if (OnLoadFunctionFailed)
            return OnLoadFunctionFailed(data, resultInfo, executor);
        return false;
    }
    bool BraceScript::DoLoadStatementFailed(const DslData::StatementData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
    {
        if (OnLoadStatementFailed)
            return OnLoadStatementFailed(data, resultInfo, executor);
        return false;
    }
    
    void BraceScript::RegisterInnerApis(void)
    {
        RegisterApi("+", new BraceApiFactoryWithArgs<AddExp, bool>(false));
        RegisterApi("-", new BraceApiFactoryWithArgs<SubExp, bool>(false));
        RegisterApi("*", new BraceApiFactoryWithArgs<MulExp, bool>(false));
        RegisterApi("/", new BraceApiFactoryWithArgs<DivExp, bool>(false));
        RegisterApi("%", new BraceApiFactoryWithArgs<ModExp, bool>(false));
        RegisterApi("&", new BraceApiFactoryWithArgs<BitAndExp, bool>(false));
        RegisterApi("|", new BraceApiFactoryWithArgs<BitOrExp, bool>(false));
        RegisterApi("^", new BraceApiFactoryWithArgs<BitXorExp, bool>(false));
        RegisterApi("~", new BraceApiFactoryWithArgs<BitNotExp, bool>(false));
        RegisterApi("<<", new BraceApiFactoryWithArgs<LShiftExp, bool>(false));
        RegisterApi(">>", new BraceApiFactoryWithArgs<RShiftExp, bool>(false));

        RegisterApi("+=", new BraceApiFactoryWithArgs<AddExp, bool>(true));
        RegisterApi("-=", new BraceApiFactoryWithArgs<SubExp, bool>(true));
        RegisterApi("*=", new BraceApiFactoryWithArgs<MulExp, bool>(true));
        RegisterApi("/=", new BraceApiFactoryWithArgs<DivExp, bool>(true));
        RegisterApi("%=", new BraceApiFactoryWithArgs<ModExp, bool>(true));
        RegisterApi("&=", new BraceApiFactoryWithArgs<BitAndExp, bool>(true));
        RegisterApi("|=", new BraceApiFactoryWithArgs<BitOrExp, bool>(true));
        RegisterApi("^=", new BraceApiFactoryWithArgs<BitXorExp, bool>(true));
        RegisterApi("<<=", new BraceApiFactoryWithArgs<LShiftExp, bool>(true));
        RegisterApi(">>=", new BraceApiFactoryWithArgs<RShiftExp, bool>(true));

        RegisterApi("++", new BraceApiFactoryWithArgs<IncExp, bool>(true));
        RegisterApi("--", new BraceApiFactoryWithArgs<DecExp, bool>(true));

        RegisterApi(">", new BraceApiFactoryWithArgs<GreatExp, bool>(false));
        RegisterApi(">=", new BraceApiFactoryWithArgs<GreatEqualExp, bool>(false));
        RegisterApi("<", new BraceApiFactoryWithArgs<LessExp, bool>(false));
        RegisterApi("<=", new BraceApiFactoryWithArgs<LessEqualExp, bool>(false));
        RegisterApi("==", new BraceApiFactoryWithArgs<EqualExp, bool>(false));
        RegisterApi("!=", new BraceApiFactoryWithArgs<NotEqualExp, bool>(false));
        RegisterApi("&&", new BraceApiFactoryWithArgs<AndExp, bool>(false));
        RegisterApi("||", new BraceApiFactoryWithArgs<OrExp, bool>(false));
        RegisterApi("!", new BraceApiFactoryWithArgs<NotExp, bool>(false));
        RegisterApi("?", new BraceApiFactory<CondExp>());
        RegisterApi("echo", new BraceApiFactory<EchoExp>());
        RegisterApi("if", new BraceApiFactory<IfExp>());
        RegisterApi("while", new BraceApiFactory<WhileExp>());
        RegisterApi("loop", new BraceApiFactory<LoopExp>());
        RegisterApi("foreach", new BraceApiFactory<ForeachExp>());
        RegisterApi("return", new BraceApiFactory<ReturnExp>());
        RegisterApi("func", new BraceApiFactory<FunctionDefine>());

        /// Because we didn't implement Object internally, we kept these apis, but we had to implement them externally
        /// -----------------------------------------------------------------------------------------------------------
        /// RegisterApi("membercall", new BraceApiFactory<MemberCallExp>());
        /// RegisterApi("memberset", new BraceApiFactory<MemberSetExp>());
        /// RegisterApi("memberget", new BraceApiFactory<MemberGetExp>());
        /// RegisterApi("collectioncall", new BraceApiFactory<CollectionCallExp>());
        /// RegisterApi("collectionset", new BraceApiFactory<CollectionSetExp>());
        /// RegisterApi("collectionget", new BraceApiFactory<CollectionGetExp>());
        /// RegisterApi("linq", new BraceApiFactory<LinqExp>());
        /// RegisterApi("lambda", new BraceApiFactory<LambdaExp>());
        /// RegisterApi("array", new BraceApiFactory<ArrayExp>());
        /// RegisterApi("hashtable", new BraceApiFactory<HashtableExp>());
        /// RegisterApi("looplist", new BraceApiFactory<LoopListExp>());
        /// ----------------------------------------------------------------------------------------------------------
    }
    void BraceScript::Init(void)
    {
        m_ForceQuit = false;
        m_HasWarn = false;
        m_HasError = false;
        m_NextUniqueId = 0;
        m_LastBlockId = 0;

        std::string name = "global";
        auto pair = m_Funcs.insert(std::make_pair(name, FuncInfo()));
        auto* p = &(pair.first->second);
        m_GlobalFunc = p;
        p->Name = name;
        m_GlobalVariables = &(p->VarInitInfo);
    }
    void BraceScript::Release(void)
    {
        m_LexicalScopeStack.clear();
        m_FuncInfoStack = FuncInfoStack();
        m_RuntimeStack = RuntimeStack();

        m_GlobalFunc = nullptr;
        m_GlobalVariables = nullptr;

        m_Funcs.clear();
        for (auto* p : m_ApiInstances) {
            delete p;
        }
        m_ApiInstances.clear();
        for (auto* p : m_AddedSyntaxComponents) {
            delete p;
        }
        m_AddedSyntaxComponents.clear();
        m_FuncApiTypeInfos.clear();
    }
    const RuntimeStack& BraceScript::GetRuntimeStack(void)const
    {
        RuntimeStack* p = nullptr;
        if (OnGetRuntimeStack) {
            p = OnGetRuntimeStack();
        }
        if (nullptr != p)
            return *p;
        else
            return m_RuntimeStack;
    }
    RuntimeStack& BraceScript::GetRuntimeStack(void)
    {
        RuntimeStack* p = nullptr;
        if (OnGetRuntimeStack) {
            p = OnGetRuntimeStack();
        }
        if (nullptr != p)
            return *p;
        else
            return m_RuntimeStack;
    }

    BraceScript::BraceScript(void) :m_NextUniqueId(0), m_LastBlockId(0), m_ForceQuit(false), m_HasWarn(false), m_HasError(false), m_GlobalFunc(nullptr), m_GlobalVariables(nullptr), m_FailbackApi(nullptr), m_ContextObject(nullptr)
    {
        RegisterInnerApis();
        Init();
    }
    BraceScript::~BraceScript(void)
    {
        Release();

        m_ContextObject = nullptr;

        for (auto& pair : m_ApiFactories) {
            delete pair.second;
        }
        m_ApiFactories.clear();
    }
    void BraceScript::RegisterApi(const std::string& id, IBraceApiFactory* pApiFactory)
    {
        std::string str = id;
        RegisterApi(std::move(str), pApiFactory);
    }
    void BraceScript::RegisterApi(std::string&& id, IBraceApiFactory* pApiFactory)
    {
        auto it = m_ApiFactories.find(id);
        if (it == m_ApiFactories.end()) {
            m_ApiFactories.insert(std::make_pair(std::move(id), pApiFactory));
        }
    }
    void BraceScript::SetFailbackApi(AbstractBraceApi* pFailbackApi)
    {
        m_FailbackApi = pFailbackApi;
    }
    AbstractBraceApi* BraceScript::GetFailbackApi(void)const
    {
        return m_FailbackApi;
    }
    void BraceScript::SetContextObject(IBraceObject* pContext)
    {
        m_ContextObject = pContext;
    }
    IBraceObject* BraceScript::GetContextObject(void)const
    {
        return m_ContextObject;
    }
    void BraceScript::Reset(void)
    {
        Release();
        Init();
    }
    void BraceScript::LoadFuncApiTypeInfo(const DslData::DslFile& dslInfos)
    {
        for (int ix = 0; ix < dslInfos.GetDslInfoNum(); ++ix) {
            auto* p = dslInfos.GetDslInfo(ix);
            if (nullptr != p && p->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_STATEMENT && p->GetId() == "func") {
                //func(name)params(argname : type, ...)rettype;
                std::string id{};
                FuncApiTypeInfo tinfo{};
                auto* pStatement = static_cast<DslData::StatementData*>(p);
                if (pStatement->GetFunctionNum() == 3) {
                    auto pinfo = ParseParamTypeInfo(*pStatement->GetThird());
                    tinfo.RetValue.Type = pinfo.Type;
                    tinfo.RetValue.ObjectTypeId = pinfo.ObjectTypeId;
                }
                if (pStatement->GetFunctionNum() >= 2) {
                    auto* first = pStatement->GetFirst()->AsFunction();
                    if (nullptr != first) {
                        id = first->GetParamId(0);
                    }
                    auto* second = pStatement->GetSecond()->AsFunction();
                    if (nullptr != second) {
                        for (int ix = 0; ix < second->GetParamNum(); ++ix) {
                            auto* pParam = second->GetParam(ix);
                            if (pParam->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION){
                                if (pParam->GetId() == ":") {
                                    auto* pParamFunc = static_cast<DslData::FunctionData*>(pParam);
                                    auto* pTypeDesc = pParamFunc->GetParam(1);
                                    ParamTypeInfo ptinfo = ParseParamTypeInfo(*pTypeDesc);
                                    tinfo.Params.push_back(std::move(ptinfo));
                                }
                                else {
                                    ParamTypeInfo ptinfo = ParseParamTypeInfo(*pParam);
                                    tinfo.Params.push_back(std::move(ptinfo));
                                }
                            }
                            else if (pParam->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_VALUE) {
                                ParamTypeInfo ptinfo = ParseParamTypeInfo(*pParam);
                                tinfo.Params.push_back(std::move(ptinfo));
                            }
                        }
                    }
                }
                AddFuncApiTypeInfo(std::move(id), std::move(tinfo));
            }
        }
    }
    void BraceScript::AddFuncApiTypeInfo(const std::string& name, const FuncApiTypeInfo& info)
    {
        std::string cname = name;
        FuncApiTypeInfo cinfo = info;
        AddFuncApiTypeInfo(std::move(cname), std::move(cinfo));
    }
    void BraceScript::AddFuncApiTypeInfo(std::string&& name, FuncApiTypeInfo&& info)
    {
        auto it = m_FuncApiTypeInfos.find(name);
        if (it == m_FuncApiTypeInfos.end()) {
            m_FuncApiTypeInfos.insert(std::make_pair(std::move(name), std::move(info)));
        }
    }
    FuncInfo* BraceScript::GetOrAddFuncInfo(const std::string& name)
    {
        FuncInfo* p;
        auto it = m_Funcs.find(name);
        if (it == m_Funcs.end()) {
            auto pair = m_Funcs.insert(std::make_pair(name, FuncInfo()));
            p = &(pair.first->second);
            p->Name = name;
        }
        else {
            p = &(it->second);
        }
        return p;
    }
    void BraceScript::LoadScript(const DslData::DslFile& file)
    {
        for (int ix = 0; ix < file.GetDslInfoNum(); ++ix) {
            auto* p = file.GetDslInfo(ix);
            BraceApiLoadInfo resultInfo;
            auto executor = Load(*p, resultInfo);
            if (!executor.isNull()) {
                m_GlobalFunc->Codes.push_back(std::move(executor));
            }
        }
    }
    void BraceScript::Run(void)
    {
        Run(0);
    }
    void BraceScript::Run(int start)
    {
        if (nullptr == m_GlobalFunc || start < 0)
            return;
        auto* curFunc = m_GlobalFunc;
        auto& codes = curFunc->Codes;
        int num = static_cast<int>(codes.size());
        for (int ix = start; ix < num; ++ix) {
            auto& p = codes[ix];
            int r = p(*m_GlobalVariables, *m_GlobalVariables);
            if (IsForceQuit())
                break;
            switch (r) {
            case BRACE_FLOW_CONTROL_RETURN:
                r = BRACE_FLOW_CONTROL_NORMAL;
                break;
            case BRACE_FLOW_CONTROL_EXCEPTION:
                break;
            case BRACE_FLOW_CONTROL_EFFECT:
                break;
            }
        }
        /// for REPL, global vars aren't free here, call Reset or Destructor to free explicitly
        /*
        for (auto& sptr : m_GlobalVariables->ObjectVars) {
            sptr = nullptr;
        }
        */
    }
    int BraceScript::GetGlobalCodeNum(void)const
    {
        if (nullptr == m_GlobalFunc)
            return INVALID_INDEX;
        auto* curFunc = m_GlobalFunc;
        return static_cast<int>(curFunc->Codes.size());
    }
}