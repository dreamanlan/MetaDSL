
#include "BraceScript.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace Brace
{
#include "BraceScript.inl"

    bool AbstractBraceApi::Load(const DslData::ISyntaxComponent& syntax, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor)
    {
        bool ret = false;
        switch (syntax.GetSyntaxType()) {
        case DslData::ISyntaxComponent::TYPE_VALUE:
            ret = LoadValue(static_cast<const DslData::ValueData&>(syntax), loadInfo, executor);
            break;
        case DslData::ISyntaxComponent::TYPE_FUNCTION: {
            auto& funcData = static_cast<const DslData::FunctionData&>(syntax);
            ret = LoadFunction(funcData, loadInfo, executor);
            if (!ret && !funcData.IsHighOrder() && funcData.HaveParam()) {
                //Provide a Load specifically for function calls
                int num = funcData.GetParamNum();
                std::vector<BraceApiExecutor> args;
                std::vector<BraceApiLoadInfo> argLoadInfos;
                for (int ix = 0; ix < num; ++ix) {
                    auto* param = funcData.GetParam(ix);
                    BraceApiLoadInfo argLoadInfo;
                    auto p = LoadHelper(*param, argLoadInfo);
                    args.push_back(std::move(p));
                    argLoadInfos.push_back(std::move(argLoadInfo));
                }
                return LoadCall(std::move(args), std::move(argLoadInfos), loadInfo, executor);
            }
            break;
        }
        case DslData::ISyntaxComponent::TYPE_STATEMENT:
            ret = LoadStatement(static_cast<const DslData::StatementData&>(syntax), loadInfo, executor);
            break;
        }
        return ret;
    }

    std::string AbstractBraceApi::GenTempVarName(void)const
    {
        return std::string("_t_") + std::to_string(GenNextUniqueId());
    }
    ProcInfo* AbstractBraceApi::GetProcInfo(const std::string& name)const
    {
        return GetInterpreter().GetProcInfo(name);
    }
    VarTypeInfo* AbstractBraceApi::GetGlobalVarTypeInfo(const std::string& name)const
    {
        auto* info = GetInterpreter().GlobalProcInfo();
        if (nullptr == info)
            return nullptr;
        auto& varInfos = info->VarTypeInfos;
        auto it = varInfos.find(name);
        if (it != varInfos.end()) {
            return &(it->second);
        }
        return nullptr;
    }
    VarTypeInfo* AbstractBraceApi::GetConstTypeInfo(const std::string& name)const
    {
        auto& interpreter = GetInterpreter();
        auto* info = interpreter.GlobalProcInfo();
        if (nullptr == info)
            return nullptr;
        auto& varInfos = info->VarTypeInfos;
        std::string key = interpreter.CalcConstKey(name);
        auto it = varInfos.find(key);
        if (it != varInfos.end()) {
            return &(it->second);
        }
        return nullptr;
    }
    VarTypeInfo* AbstractBraceApi::GetVarTypeInfo(const std::string& name)const
    {
        auto& interpreter = GetInterpreter();
        auto* info = interpreter.CurProcInfo();
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
    bool AbstractBraceApi::CanAssign(int destType, int srcType)const
    {
        return GetInterpreter().CanAssign(destType, srcType);
    }
    ProcInfo* AbstractBraceApi::CurProcInfo(void)const
    {
        return GetInterpreter().CurProcInfo();
    }
    ProcInfo* AbstractBraceApi::PushNewProcInfo(const std::string& name)const
    {
        return GetInterpreter().PushNewProcInfo(name);
    }
    void AbstractBraceApi::PopProcInfo(void)const
    {
        GetInterpreter().PopProcInfo();
    }
    int AbstractBraceApi::GenNextUniqueId(void)const
    {
        return GetInterpreter().GenNextUniqueId();
    }
    int AbstractBraceApi::CurBlockLevel(void)const
    {
        return GetInterpreter().CurBlockLevel();
    }
    void AbstractBraceApi::PushBlock(void)const
    {
        GetInterpreter().PushBlock();
    }
    void AbstractBraceApi::PopBlock(void)const
    {
        GetInterpreter().PopBlock();
    }
    int AbstractBraceApi::AllocGlobalVariable(const std::string& name, int type)const
    {
        return GetInterpreter().AllocGlobalVariable(name, type);
    }
    int AbstractBraceApi::AllocConst(int tok_type, const std::string& value, int& type)const
    {
        return GetInterpreter().AllocConst(tok_type, value, type);
    }
    int AbstractBraceApi::AllocVariable(const std::string& name, int type)const
    {
        return GetInterpreter().AllocVariable(name, type);
    }
    void AbstractBraceApi::LogInfo(const std::string& msg)const
    {
        GetInterpreter().LogInfo(msg);
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
    BraceApiExecutor AbstractBraceApi::LoadHelper(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& loadInfo)const
    {
        return GetInterpreter().Load(syntaxUnit, loadInfo);
    }
    
    ProcInfo* AbstractBraceApi::GlobalProcInfo(void)const
    {
        return GetInterpreter().GlobalProcInfo();
    }
    VariableInfo* AbstractBraceApi::GlobalVariables(void)const
    {
        return GetInterpreter().GlobalVariables();
    }
    RuntimeStackInfo& AbstractBraceApi::CurRuntimeStack(void)const
    {
        return GetInterpreter().CurRuntimeStack();
    }
    void AbstractBraceApi::PushRuntimeStack(const ProcInfo* procInfo)const
    {
        GetInterpreter().PushRuntimeStack(procInfo);
    }
    void AbstractBraceApi::PopRuntimeStack(void)const
    {
        GetInterpreter().PopRuntimeStack();
    }

    class GlobalVarSet final : public AbstractBraceApi
    {
    public:
        GlobalVarSet(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
            m_VarIndex = std::numeric_limits<int>::max();
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            DslData::ISyntaxComponent* param1 = data.GetParam(0);
            DslData::ISyntaxComponent* param2 = data.GetParam(1);
            m_VarId = param1->GetId();
            m_Exp = LoadHelper(*param2, loadInfo);
            m_SrcVarType = loadInfo.Type;
            m_SrcVarIndex = loadInfo.VarIndex;
            auto* procInfo = GlobalProcInfo();
            if (nullptr == procInfo) {
                std::stringstream ss;
                ss << "Fatal Error, can't find Environment ! name " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
            }
            else {
                auto* varInfo = GetGlobalVarTypeInfo(m_VarId);
                if (nullptr != varInfo) {
                    m_VarType = varInfo->Type;
                    m_VarIndex = varInfo->VarIndex;
                    //type check
                    if (!CanAssign(varInfo->Type, loadInfo.Type)) {
                        std::stringstream ss;
                        ss << "Can't assign " << GetTypeName(loadInfo.Type) << " to " << GetTypeName(varInfo->Type) << " line " << data.GetLine();
                        LogError(ss.str());
                    }
                }
                else {
                    //decl var
                    m_VarType = loadInfo.Type;
                    m_VarIndex = AllocGlobalVariable(m_VarId, m_VarType);
                }
            }
            m_Fptr = GetVarAssignPtr(m_VarType, m_SrcVarType);
            executor = std::bind(&GlobalVarSet::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Exp)
                m_Exp();
            if (m_Fptr) {
                auto& vars = *CurRuntimeStack().Variables;
                (*m_Fptr)(vars, m_VarIndex, vars, m_SrcVarIndex);
            }
            return 0;
        }
    private:
        std::string m_VarId;
        BraceApiExecutor m_Exp;
        VarAssignPtr m_Fptr;
        int m_VarType;
        int m_VarIndex;
        int m_SrcVarType;
        int m_SrcVarIndex;
    };
    class GlobalVarGet final : public AbstractBraceApi
    {
    public:
        GlobalVarGet(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            const std::string& varId = data.GetId();
            auto* info = GetGlobalVarTypeInfo(varId);
            if (nullptr != info) {
                loadInfo.Type = info->Type;
                loadInfo.VarIndex = info->VarIndex;
            }
            else {
                loadInfo.Type = BRACE_DATA_TYPE_UNKNOWN;
                loadInfo.VarIndex = INVALID_INDEX;
            }
            executor = nullptr;
            return true;
        }
    };
    class LocalVarSet final : public AbstractBraceApi
    {
    public:
        LocalVarSet(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
            m_VarIndex = std::numeric_limits<int>::max();
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            DslData::ISyntaxComponent* param1 = data.GetParam(0);
            DslData::ISyntaxComponent* param2 = data.GetParam(1);
            m_VarId = param1->GetId();
            m_Exp = LoadHelper(*param2, loadInfo);
            m_SrcVarType = loadInfo.Type;
            m_SrcVarIndex = loadInfo.VarIndex;
            auto* procInfo = CurProcInfo();
            if (nullptr == procInfo) {
                std::stringstream ss;
                ss << "Fatal Error, can't find Environment ! name " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
            }
            else {
                auto* varInfo = GetVarTypeInfo(m_VarId);
                if (nullptr != varInfo) {
                    m_VarType = varInfo->Type;
                    m_VarIndex = varInfo->VarIndex;
                    //type check
                    if (!CanAssign(varInfo->Type, loadInfo.Type)) {
                        std::stringstream ss;
                        ss << "Can't assign " << GetTypeName(loadInfo.Type) << " to " << GetTypeName(varInfo->Type) << " line " << data.GetLine();
                        LogError(ss.str());
                    }
                }
                else {
                    //decl var
                    m_VarType = loadInfo.Type;
                    m_VarIndex = AllocVariable(m_VarId, m_VarType);
                }
            }
            m_Fptr = GetVarAssignPtr(m_VarType, m_SrcVarType);
            executor = std::bind(&LocalVarSet::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Exp)
                m_Exp();
            if (m_Fptr) {
                auto& vars = *CurRuntimeStack().Variables;
                (*m_Fptr)(vars, m_VarIndex, vars, m_SrcVarIndex);
            }
            return 0;
        }
    private:
        std::string m_VarId;
        BraceApiExecutor m_Exp;
        VarAssignPtr m_Fptr;
        int m_VarType;
        int m_VarIndex;
        int m_SrcVarType;
        int m_SrcVarIndex;
    };
    class LocalVarGet final : public AbstractBraceApi
    {
    public:
        LocalVarGet(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            const std::string& varId = data.GetId();
            auto* info = GetVarTypeInfo(varId);
            if (nullptr != info) {
                loadInfo.Type = info->Type;
                loadInfo.VarIndex = info->VarIndex;
            }
            else {
                loadInfo.Type = BRACE_DATA_TYPE_UNKNOWN;
                loadInfo.VarIndex = INVALID_INDEX;
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
        virtual bool LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            const std::string& varId = data.GetId();
            auto* info = GetConstTypeInfo(varId);
            if (nullptr != info) {
                loadInfo.Type = info->Type;
                loadInfo.VarIndex = info->VarIndex;
            }
            else {
                loadInfo.VarIndex = AllocConst(data.GetIdType(), varId, loadInfo.Type);
            }
            executor = nullptr;
            return true;
        }
    };
    class FunctionCall final : public AbstractBraceApi
    {
    public:
        FunctionCall(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            if (!data.IsHighOrder() && data.HaveParam()) {
                const std::string& func = data.GetId();
                m_Func = GetProcInfo(func);
                int num = data.GetParamNum();
                for (int ix = 0; ix < num; ++ix) {
                    DslData::ISyntaxComponent* param = data.GetParam(ix);
                    BraceApiLoadInfo argLoadInfo;
                    auto p = LoadHelper(*param, argLoadInfo);
                    m_Args.push_back(std::move(p));
                    m_ArgIndexes.push_back(std::move(argLoadInfo));
                    if (ix < m_Func->Params.size()) {
                        auto ptr = GetVarAssignPtr(m_Func->Params[ix].Type, argLoadInfo.Type);
                        m_ArgAssigns.push_back(ptr);
                    };
                }
                m_ResultInfo.Type = m_Func->RetValue.Type;
                m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
                m_ResultAssign = GetVarAssignPtr(m_ResultInfo.Type, m_Func->RetValue.Type);
                loadInfo = m_ResultInfo;
                executor = std::bind(&FunctionCall::Execute, *this);
                return true;
            }
            return false;
        }
    private:
        int Execute(void)
        {
            //push args
            auto& stackInfo = CurRuntimeStack();
            for (auto& arg : m_Args) {
                if (arg)
                    arg();
            }
            //run proc
            int r = BRACE_FLOW_CONTROL_NORMAL;
            PushRuntimeStack(m_Func);
            auto& lastVars = *CurRuntimeStack().LastStackInfo->Variables;
            auto& vars = *CurRuntimeStack().Variables;
            for (int ix = 0; ix < static_cast<int>(m_ArgIndexes.size()) && ix < static_cast<int>(m_ArgAssigns.size()); ++ix) {
                auto& destInfo = m_Func->Params[ix];
                auto& srcInfo = m_ArgIndexes[ix];
                auto ptr = m_ArgAssigns[ix];
                (*ptr)(vars, destInfo.VarIndex, lastVars, srcInfo.VarIndex);
            }
            for (auto& p : m_Func->Codes) {
                r = p();
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
            if (m_ResultAssign)
                (*m_ResultAssign)(lastVars, m_ResultInfo.VarIndex, vars, m_Func->RetValue.VarIndex);
            PopRuntimeStack();
            return r;
        }
    private:
        const ProcInfo* m_Func;
        std::vector<BraceApiExecutor> m_Args;
        std::vector<BraceApiLoadInfo> m_ArgIndexes;
        std::vector<VarAssignPtr> m_ArgAssigns;
        BraceApiLoadInfo m_ResultInfo;
        VarAssignPtr m_ResultAssign;
    };
    class BreakExp final : public AbstractBraceApi
    {
    public:
        BreakExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            loadInfo = BraceApiLoadInfo();
            executor = std::bind(&BreakExp::Execute, *this);
            return false;
        }
    private:
        int Execute(void)
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
        virtual bool LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            loadInfo = BraceApiLoadInfo();
            executor = std::bind(&ContinueExp::Execute, *this);
            return false;
        }
    private:
        int Execute(void)
        {
            return BRACE_FLOW_CONTROL_CONTINUE;
        }
    };
    class ReturnExp final : public AbstractBraceApi
    {
    public:
        ReturnExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //return(...); or return <- expression;
            auto* proc = CurProcInfo();
            m_ResultInfo.Type = proc->RetValue.Type;
            m_ResultInfo.VarIndex = proc->RetValue.VarIndex;
            if (!data.IsHighOrder()) {
                if (data.IsOperatorParamClass() && data.GetParamNum() == 2) {
                    auto* exp = data.GetParam(1);
                    m_Arg = LoadHelper(*exp, m_LoadInfo);
                }
                else {
                    auto* exp = data.GetParam(0);
                    m_Arg = LoadHelper(*exp, m_LoadInfo);
                }
                m_Assign = GetVarAssignPtr(m_ResultInfo.Type, m_LoadInfo.Type);
                executor = std::bind(&ReturnExp::Execute, *this);
                return true;
            }
            std::stringstream ss;
            ss << "return syntax error, line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        virtual bool LoadStatement(const DslData::StatementData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //return symbol;
            auto* proc = CurProcInfo();
            m_ResultInfo.Type = proc->RetValue.Type;
            m_ResultInfo.VarIndex = proc->RetValue.VarIndex;
            if (data.GetFunctionNum() == 2) {
                auto* f1 = data.GetFirst()->AsValue();
                auto* f2 = data.GetSecond()->AsValue();
                if (f1 && f2) {
                    m_Arg = LoadHelper(*f2, m_LoadInfo);
                    m_Assign = GetVarAssignPtr(m_ResultInfo.Type, m_LoadInfo.Type);
                    executor = std::bind(&ReturnExp::Execute, *this);
                    return true;
                }
            }
            std::stringstream ss;
            ss << "return syntax error, line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
    private:
        int Execute(void)
        {
            if (m_Arg)
                m_Arg();
            if (m_Assign) {
                auto& vars = *CurRuntimeStack().Variables;
                (*m_Assign)(vars, m_ResultInfo.VarIndex, vars, m_LoadInfo.VarIndex);
            }
            return BRACE_FLOW_CONTROL_RETURN;
        }
    private:
        BraceApiExecutor m_Arg;
        BraceApiLoadInfo m_LoadInfo;
        BraceApiLoadInfo m_ResultInfo;
        VarAssignPtr m_Assign;
    };
    class LambdaExp final : public AbstractBraceApi
    {
    public:
        LambdaExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //(args) => {...}; or (args)int => {...}; or [...](args) => {...}; or [...](args)int => {...};
            auto* f0 = data.GetParam(0);
            auto* f1 = data.GetParam(1);
            bool hasError = false;
            if (f0 && (f0->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION || 
                    f0->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_STATEMENT) &&
                f1 && f1->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                std::string func = GenTempVarName();
                auto* proc = PushNewProcInfo(func);
                DslData::FunctionData* pCaptures = nullptr;
                DslData::FunctionData* pParams = nullptr;
                if (f0->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                    pParams = static_cast<DslData::FunctionData*>(f0);
                }
                else {
                    DslData::StatementData* pSD = static_cast<DslData::StatementData*>(f0);
                    pParams = pSD->GetFirst()->AsFunction();
                    auto* pRet = pSD->GetSecond();
                    auto* pRetFunc = pRet->AsFunction();
                    auto* pRetVal = pRet->AsValue();
                    if (pRetFunc && pRetFunc->GetParamClassUnmasked() == DslData::FunctionData::PARAM_CLASS_ANGLE_BRACKET_COLON) {
                        auto typeName = pRetFunc->GetId();
                        int type = GetBraceDataType(typeName);
                        std::string tname = GenTempVarName();
                        int varIndex = AllocVariable(tname, type);
                        proc->RetValue = VarInfo(tname, type, varIndex);
                    }
                    else if (pRetVal) {
                        auto typeName = pRetVal->GetId();
                        int type = GetBraceDataType(typeName);
                        std::string tname = GenTempVarName();
                        int varIndex = AllocVariable(tname, type);
                        proc->RetValue = VarInfo(tname, type, varIndex);
                    }
                    else {
                        hasError = true;
                    }
                }
                if (pParams->IsHighOrder())
                    pCaptures = &pParams->GetLowerOrderFunction();
                int num = pParams->GetParamNum();
                for (int ix = 0; ix < num; ++ix) {
                    auto* p = pParams->GetParam(ix);
                    if (p->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                        auto* pf = static_cast<const DslData::FunctionData*>(p);
                        if (pf->IsOperatorParamClass() && pf->GetId() == ":") {
                            auto& name = pf->GetParamId(0);
                            auto& typeName = pf->GetParamId(1);
                            int type = GetBraceDataType(typeName);
                            int varIndex = AllocVariable(name, type);
                            proc->Params.push_back(VarInfo(name, type, varIndex));
                        }
                    }
                    else {
                        hasError = true;
                    }
                }
                auto* pStatements = static_cast<DslData::FunctionData*>(f1);
                num = pStatements->GetParamNum();
                for (int ix = 0; ix < num; ++ix) {
                    auto* exp = pStatements->GetParam(ix);
                    BraceApiLoadInfo expLoadInfo;
                    auto statement = LoadHelper(*exp, expLoadInfo);
                    if (statement)
                        proc->Codes.push_back(std::move(statement));
                }
                loadInfo = BraceApiLoadInfo();
                executor = nullptr;
                PopProcInfo();
                if (!hasError) {
                    return true;
                }
            }
            else {
                hasError = true;
            }
            if(hasError) {
                std::stringstream ss;
                ss << "lambda syntax error, line " << data.GetLine();
                LogError(ss.str());
            }
            return false;
        }
    };
    class FunctionDefine final : public AbstractBraceApi
    {
    public:
        FunctionDefine(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //func(name){...};
            if (data.IsHighOrder()) {
                const std::string& func = data.GetLowerOrderFunction().GetParamId(0);
                auto* proc = PushNewProcInfo(func);
                int num = data.GetParamNum();
                for (int ix = 0; ix < num; ++ix) {
                    auto* exp = data.GetParam(ix);
                    BraceApiLoadInfo expLoadInfo;
                    auto statement = LoadHelper(*exp, expLoadInfo);
                    if (statement)
                        proc->Codes.push_back(std::move(statement));
                }
                loadInfo = BraceApiLoadInfo();
                executor = nullptr;
                PopProcInfo();
                return true;
            }
            else {
                std::stringstream ss;
                ss << "func syntax error " << data.GetParamId(0) << " line " << data.GetLine();
                LogError(ss.str());
            }
            return false;
        }
        virtual bool LoadStatement(const DslData::StatementData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //func(name)args($a:int32,$b:int8,...)int{...}; or func(name)args($a:int32,$b:int8,...){...};
            bool hasError = false;
            if (data.GetFunctionNum() == 2) {
                auto* f1 = data.GetFirst()->AsFunction();
                auto* f2 = data.GetSecond()->AsFunction();
                if (f1 && !f1->IsHighOrder() && f1->HaveParam() && f2 && f2->IsHighOrder() && f2->HaveStatement()) {
                    const std::string& func = f1->GetParamId(0);
                    auto* proc = PushNewProcInfo(func);
                    auto& callData = f2->GetLowerOrderFunction();
                    for (int ix = 0; ix < callData.GetParamNum(); ++ix) {
                        auto* p = callData.GetParam(ix);
                        if (p->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                            auto* pf = static_cast<const DslData::FunctionData*>(p);
                            if (pf->IsOperatorParamClass() && pf->GetId() == ":") {
                                auto& name = pf->GetParamId(0);
                                auto& typeName = pf->GetParamId(1);
                                int type = GetBraceDataType(typeName);
                                int varIndex = AllocVariable(name, type);
                                proc->Params.push_back(VarInfo(name, type, varIndex));
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
                        if (statement)
                            proc->Codes.push_back(std::move(statement));
                    }
                    loadInfo = BraceApiLoadInfo();
                    executor = nullptr;
                    PopProcInfo();
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
                    auto* proc = PushNewProcInfo(func);
                    auto& callData = *f2;
                    for (int ix = 0; ix < callData.GetParamNum(); ++ix) {
                        auto* p = callData.GetParam(ix);
                        if (p->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                            auto* pf = static_cast<const DslData::FunctionData*>(p);
                            if (pf->IsOperatorParamClass() && pf->GetId() == ":") {
                                auto& name = pf->GetParamId(0);
                                auto& typeName = pf->GetParamId(1);
                                int type = GetBraceDataType(typeName);
                                int varIndex = AllocVariable(name, type);
                                proc->Params.push_back(VarInfo(name, type, varIndex));
                            }
                        }
                        else {
                            hasError = true;
                        }
                    }
                    if (f3->IsHighOrder() && f3->GetLowerOrderFunction().GetParamClassUnmasked() == DslData::FunctionData::PARAM_CLASS_ANGLE_BRACKET_COLON) {
                        auto typeName = f3->GetId(); 
                        int type = GetBraceDataType(typeName);
                        std::string tname = GenTempVarName();
                        int varIndex = AllocVariable(tname, type);
                        proc->RetValue = VarInfo(tname, type, varIndex);
                    }
                    else if (!f3->IsHighOrder()) {
                        auto typeName = f3->GetId();
                        int type = GetBraceDataType(typeName);
                        std::string tname = GenTempVarName();
                        int varIndex = AllocVariable(tname, type);
                        proc->RetValue = VarInfo(tname, type, varIndex);
                    }
                    else {
                        hasError = true;
                    }
                    int num = f3->GetParamNum();
                    for (int ix = 0; ix < num; ++ix) {
                        auto* exp = f3->GetParam(ix);
                        BraceApiLoadInfo expLoadInfo;
                        auto statement = LoadHelper(*exp, expLoadInfo);
                        if (statement)
                            proc->Codes.push_back(std::move(statement));
                    }
                    loadInfo = BraceApiLoadInfo();
                    executor = nullptr;
                    PopProcInfo();
                    if (!hasError) {
                        return true;
                    }
                }
                else {
                    hasError = true;
                }
            }
            if(hasError) {
                auto* f = data.GetFirst()->AsFunction();
                std::stringstream ss;
                ss << "func syntax error " << (f ? f->GetParamId(0) : std::string("noname")) << " line " << data.GetLine();
                LogError(ss.str());
            }
            return false;
        }
    };
    class AddExp final : public AbstractBraceApi
    {
    public:
        AddExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&AddExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class SubExp final : public AbstractBraceApi
    {
    public:
        SubExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&SubExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class MulExp final : public AbstractBraceApi
    {
    public:
        MulExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&MulExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class DivExp final : public AbstractBraceApi
    {
    public:
        DivExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&DivExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class ModExp final : public AbstractBraceApi
    {
    public:
        ModExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&ModExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class BitAndExp final : public AbstractBraceApi
    {
    public:
        BitAndExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&BitAndExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class BitOrExp final : public AbstractBraceApi
    {
    public:
        BitOrExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&BitOrExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class BitXorExp final : public AbstractBraceApi
    {
    public:
        BitXorExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&BitXorExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class BitNotExp final : public AbstractBraceApi
    {
    public:
        BitNotExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_LoadInfo1 = argLoadInfos[0];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&BitNotExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_ResultInfo;
    };

    class LShiftExp final : public AbstractBraceApi
    {
    public:
        LShiftExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&LShiftExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class RShiftExp final : public AbstractBraceApi
    {
    public:
        RShiftExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = m_LoadInfo1.Type;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), loadInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&RShiftExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class GreatExp final : public AbstractBraceApi
    {
    public:
        GreatExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&GreatExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class GreatEqualExp final : public AbstractBraceApi
    {
    public:
        GreatEqualExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&GreatEqualExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class LessExp final : public AbstractBraceApi
    {
    public:
        LessExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&LessExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class LessEqualExp final : public AbstractBraceApi
    {
    public:
        LessEqualExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&LessEqualExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class EqualExp final : public AbstractBraceApi
    {
    public:
        EqualExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&EqualExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class NotEqualExp final : public AbstractBraceApi
    {
    public:
        NotEqualExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&NotEqualExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class AndExp final : public AbstractBraceApi
    {
    public:
        AndExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&AndExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class OrExp final : public AbstractBraceApi
    {
    public:
        OrExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_Op2 = args[1];
            m_LoadInfo1 = argLoadInfos[0];
            m_LoadInfo2 = argLoadInfos[1];
            m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&OrExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };
    class NotExp final : public AbstractBraceApi
    {
    public:
        NotExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            m_Op1 = args[0];
            m_LoadInfo1 = argLoadInfos[0];
            m_ResultInfo.Type = BRACE_DATA_TYPE_BOOL;
            m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            loadInfo = m_ResultInfo;
            executor = std::bind(&NotExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            if (m_Op1)
                m_Op1();
            auto& vars = *CurRuntimeStack().Variables;
            int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            VarSetBool(vars, m_ResultInfo.VarIndex, !(v1 != 0));
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Op1;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_ResultInfo;
    };
    class CondExp final : public AbstractBraceApi
    {
    public:
        CondExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadStatement(const DslData::StatementData& statementData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            auto* funcData1 = statementData.GetFirst()->AsFunction();
            auto* funcData2 = statementData.GetSecond()->AsFunction();
            if (funcData1->IsHighOrder() && funcData1->HaveLowerOrderParam() && funcData2->GetId() == ":" && funcData2->HaveParamOrStatement()) {
                auto* cond = funcData1->GetLowerOrderFunction().GetParam(0);
                auto* op1 = funcData1->GetParam(0);
                auto* op2 = funcData2->GetParam(0);
                m_Op1 = LoadHelper(*cond, m_LoadInfo1);
                m_Op2 = LoadHelper(*op1, m_LoadInfo2);
                m_Op3 = LoadHelper(*op2, m_LoadInfo3);
                m_ResultInfo.Type = m_LoadInfo2.Type;
                m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << statementData.GetId() << " line " << statementData.GetLine();
                LogError(ss.str());
            }
            return true;
        }
    private:
        int Execute()
        {
            auto& vars = *CurRuntimeStack().Variables;
            if (m_Op1)
                m_Op1();
            bool v = VarGetBoolean(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            if (v) {
                if (m_Op2)
                    m_Op2();
                int64_t val = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
                VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
            }
            else {
                if (m_Op3)
                    m_Op3();
                int64_t val = VarGetI64(vars, m_LoadInfo3.Type, m_LoadInfo3.VarIndex);
                VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, val);
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
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            std::swap(m_Args, args);
            std::swap(m_ArgLoadInfos, argLoadInfos);
            loadInfo = BraceApiLoadInfo();
            executor = std::bind(&EchoExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            for (auto p : m_Args) {
                if(p)
                    p();
            }
            std::stringstream ss;
            auto& vars = *CurRuntimeStack().Variables;
            for (auto& info : m_ArgLoadInfos) {
                if (info.Type != BRACE_DATA_TYPE_UNKNOWN) {
                    ss << VarGetStr(vars, info.Type, info.VarIndex);
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
        IfExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& funcData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            if (funcData.IsHighOrder()) {
                auto* cond = funcData.GetLowerOrderFunction().GetParam(0);
                Clause item;
                item.Condition = LoadHelper(*cond, item.LoadInfo);
                for (int ix = 0; ix < funcData.GetParamNum(); ++ix) {
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*funcData.GetParam(ix), argLoadInfo);
                    if(statement)
                        item.Statements.push_back(std::move(statement));
                }
                m_Clauses.push_back(std::move(item));
                executor = std::bind(&IfExp::Execute, *this);
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << funcData.GetId() << " line " << funcData.GetLine();
                LogError(ss.str());
            }
            return true;
        }
        virtual bool LoadStatement(const DslData::StatementData& statementData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //简化语法if(exp) func(args);语法的处理
            int funcNum = statementData.GetFunctionNum();
            if (funcNum == 2) {
                auto* first = statementData.GetFirst()->AsFunction();
                auto* second = statementData.GetSecond()->AsFunction();
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
                    if (statement)
                        item.Statements.push_back(std::move(statement));
                    m_Clauses.push_back(std::move(item));
                    executor = std::bind(&IfExp::Execute, *this);
                    return true;
                }
            }
            //标准if语句的处理
            for (int ix = 0; ix < statementData.GetFunctionNum(); ++ix) {
                auto* fd = statementData.GetFunction(ix);
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
                    for (int iix = 0; iix < fData->GetParamNum(); ++iix) {
                        BraceApiLoadInfo argLoadInfo;
                        auto statement = LoadHelper(*fData->GetParam(iix), argLoadInfo);
                        if (statement)
                            item.Statements.push_back(std::move(statement));
                    }
                    m_Clauses.push_back(std::move(item));
                }
                else if (fData->GetId() == "else") {
                    if (fData != statementData.GetLast()) {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << fData->GetId() << " line " << fData->GetLine();
                        LogError(ss.str());
                    }
                    else {
                        Clause item;
                        for (int iix = 0; iix < fData->GetParamNum(); ++iix) {
                            BraceApiLoadInfo argLoadInfo;
                            auto statement = LoadHelper(*fData->GetParam(iix), argLoadInfo);
                            if (statement)
                                item.Statements.push_back(std::move(statement));
                        }
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
            executor = std::bind(&IfExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            auto& vars = *CurRuntimeStack().Variables;
            int ct = static_cast<int>(m_Clauses.size());
            for (int ix = 0; ix < ct; ++ix) {
                auto& clause = m_Clauses[ix];
                clause.Condition();
                if (VarGetBoolean(vars, clause.LoadInfo.Type, clause.LoadInfo.VarIndex)) {
                    for (auto& statement : clause.Statements) {
                        int v = statement();
                        if (v != BRACE_FLOW_CONTROL_NORMAL) {
                            return v;
                        }
                    }
                    break;
                }
                else if (ix == ct - 1) {
                    for (auto& statement : clause.Statements) {
                        int v = statement();
                        if (v != BRACE_FLOW_CONTROL_NORMAL) {
                            return v;
                        }
                    }
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
        };

        std::vector<Clause> m_Clauses;
    };
    class WhileExp final : public AbstractBraceApi
    {
    public:
        WhileExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& funcData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            if (funcData.IsHighOrder()) {
                auto* cond = funcData.GetLowerOrderFunction().GetParam(0);
                m_Condition = LoadHelper(*cond, m_LoadInfo);
                for (int ix = 0; ix < funcData.GetParamNum(); ++ix) {
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*funcData.GetParam(ix), argLoadInfo);
                    if (statement)
                        m_Statements.push_back(std::move(statement));
                }
                executor = std::bind(&WhileExp::Execute, *this);
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << funcData.GetId() << " line " << funcData.GetLine();
                LogError(ss.str());
            }
            return true;
        }
        virtual bool LoadStatement(const DslData::StatementData& statementData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //简化语法while(exp) func(args);语法的处理
            if (statementData.GetFunctionNum() == 2) {
                auto* first = statementData.GetFirst()->AsFunction();
                auto* second = statementData.GetSecond()->AsFunction();
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
                    if (statement)
                        m_Statements.push_back(std::move(statement));
                    executor = std::bind(&WhileExp::Execute, *this);
                    return true;
                }
            }
            return false;
        }
    private:
        int Execute(void)
        {
            auto& vars = *CurRuntimeStack().Variables;
            for (; ; ) {
                m_Condition();
                if (VarGetBoolean(vars, m_LoadInfo.Type, m_LoadInfo.VarIndex)) {
                    for (auto& statement : m_Statements) {
                        int v = statement();
                        if (v == BRACE_FLOW_CONTROL_CONTINUE) {
                            break;
                        }
                        else if (v != BRACE_FLOW_CONTROL_NORMAL) {
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
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        BraceApiExecutor m_Condition;
        BraceApiLoadInfo m_LoadInfo;
        std::vector<BraceApiExecutor> m_Statements;
    };
    class LoopExp final : public AbstractBraceApi
    {
    public:
        LoopExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& funcData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            if (funcData.IsHighOrder()) {
                auto* count = funcData.GetLowerOrderFunction().GetParam(0);
                m_Count = LoadHelper(*count, m_LoadInfo);
                m_IteratorIndex = AllocVariable("$$", m_LoadInfo.Type);
                for (int ix = 0; ix < funcData.GetParamNum(); ++ix) {
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*funcData.GetParam(ix), argLoadInfo);
                    if (statement)
                        m_Statements.push_back(std::move(statement));
                }
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << funcData.GetId() << " line " << funcData.GetLine();
                LogError(ss.str());
            }
            return true;
        }
        virtual bool LoadStatement(const DslData::StatementData& statementData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //简化语法loop(exp) func(args);语法的处理
            if (statementData.GetFunctionNum() == 2) {
                auto* first = statementData.GetFirst()->AsFunction();
                auto* second = statementData.GetSecond()->AsFunction();
                const std::string& firstId = first->GetId();
                const std::string& secondId = second->GetId();
                if (firstId == "loop" && !first->HaveStatement() && !first->HaveExternScript() &&
                    !secondId.empty() && !second->HaveStatement() && !second->HaveExternScript()) {
                    if (first->GetParamNum() > 0) {
                        auto* exp = first->GetParam(0);
                        m_Count = LoadHelper(*exp, m_LoadInfo);
                        m_IteratorIndex = AllocVariable("$$", m_LoadInfo.Type);
                    }
                    else {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << first->GetId() << " line " << first->GetLine();
                    }
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*second, argLoadInfo);
                    if (statement)
                        m_Statements.push_back(std::move(statement));
                    executor = std::bind(&LoopExp::Execute, *this);
                    return true;
                }
            }
            return false;
        }
    private:
        int Execute(void)
        {
            auto& vars = *CurRuntimeStack().Variables;
            m_Count();
            long ct = VarGetI64(vars, m_LoadInfo.Type, m_LoadInfo.VarIndex);
            for (int i = 0; i < ct; ++i) {
                VarSetI64(vars, m_LoadInfo.Type, m_IteratorIndex, i);
                for (int index = 0; index < m_Statements.size(); ++index) {
                    for (auto& statement : m_Statements) {
                        int v = statement();
                        if (v == BRACE_FLOW_CONTROL_CONTINUE) {
                            break;
                        }
                        else if (v != BRACE_FLOW_CONTROL_NORMAL) {
                            if (v == BRACE_FLOW_CONTROL_BREAK)
                                return BRACE_FLOW_CONTROL_NORMAL;
                            return v;
                        }
                    }
                }
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        int m_IteratorIndex;
        BraceApiExecutor m_Count;
        BraceApiLoadInfo m_LoadInfo;
        std::vector<BraceApiExecutor> m_Statements;
    };
    class LoopListExp final : public AbstractBraceApi
    {
    public:
        LoopListExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& funcData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            if (funcData.IsHighOrder()) {
                auto* list = funcData.GetLowerOrderFunction().GetParam(0);
                m_List = LoadHelper(*list, m_LoadInfo);
                m_IteratorIndex = AllocVariable("$$", m_LoadInfo.Type);
                for (int ix = 0; ix < funcData.GetParamNum(); ++ix) {
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*funcData.GetParam(ix), argLoadInfo);
                    if (statement)
                        m_Statements.push_back(std::move(statement));
                }
                executor = std::bind(&LoopListExp::Execute, *this);
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << funcData.GetId() << " line " << funcData.GetLine();
                LogError(ss.str());
            }
            return true;
        }
        virtual bool LoadStatement(const DslData::StatementData& statementData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //简化语法looplist(exp) func(args);语法的处理
            if (statementData.GetFunctionNum() == 2) {
                auto* first = statementData.GetFirst()->AsFunction();
                auto* second = statementData.GetSecond()->AsFunction();
                const std::string& firstId = first->GetId();
                const std::string& secondId = second->GetId();
                if (firstId == "looplist" && !first->HaveStatement() && !first->HaveExternScript() &&
                    !secondId.empty() && !second->HaveStatement() && !second->HaveExternScript()) {
                    if (first->GetParamNum() > 0) {
                        auto* exp = first->GetParam(0);
                        m_List = LoadHelper(*exp, m_LoadInfo);
                        m_IteratorIndex = AllocVariable("$$", m_LoadInfo.Type);
                    }
                    else {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << first->GetId() << " line " << first->GetLine();
                        LogError(ss.str());
                    }
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*second, argLoadInfo);
                    if (statement)
                        m_Statements.push_back(std::move(statement));
                    executor = std::bind(&LoopListExp::Execute, *this);
                    return true;
                }
            }
            return false;
        }
    private:
        int Execute(void)
        {
            auto& vars = *CurRuntimeStack().Variables;
            m_List();
            auto* obj = VarGetObject(vars, m_LoadInfo.VarIndex);
            if (nullptr != obj) {
                for (auto& e : { obj }) {
                    VarSetObject(vars, m_IteratorIndex, e);
                    for (auto& statement : m_Statements) {
                        int v = statement();
                        if (v == BRACE_FLOW_CONTROL_CONTINUE) {
                            break;
                        }
                        else if (v != BRACE_FLOW_CONTROL_NORMAL) {
                            if (v == BRACE_FLOW_CONTROL_BREAK)
                                return BRACE_FLOW_CONTROL_NORMAL;
                            return v;
                        }
                    }
                }
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        int m_IteratorIndex;
        BraceApiExecutor m_List;
        BraceApiLoadInfo m_LoadInfo;
        std::vector<BraceApiExecutor> m_Statements;
    };
    class ForeachExp final : public AbstractBraceApi
    {
    public:
        ForeachExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadFunction(const DslData::FunctionData& funcData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            if (funcData.IsHighOrder()) {
                auto& callData = funcData.GetLowerOrderFunction();
                int num = callData.GetParamNum();
                bool typeMatch = true;
                int type = BRACE_DATA_TYPE_UNKNOWN;
                for (int ix = 0; ix < num; ++ix) {
                    auto* exp = callData.GetParam(ix); BraceApiLoadInfo elemLoadInfo;
                    auto e = LoadHelper(*exp, elemLoadInfo);
                    if (elemLoadInfo.Type != BRACE_DATA_TYPE_UNKNOWN) {
                        if (type == BRACE_DATA_TYPE_UNKNOWN) {
                            type = elemLoadInfo.Type;
                        }
                        else if (type != elemLoadInfo.Type) {
                            typeMatch = false;
                        }
                    }
                    else {
                        typeMatch = false;
                    }
                    m_Elements.push_back(std::move(e));
                    m_ElementLoadInfos.push_back(std::move(elemLoadInfo));
                }
                m_IteratorIndex = AllocVariable("$$", type);
                if (!typeMatch) {
                    std::stringstream ss;
                    ss << "BraceScript error, foreach list type dismatch, " << callData.GetId() << " line " << callData.GetLine();
                    LogError(ss.str());
                }
            }
            if (funcData.HaveStatement()) {
                int fnum = funcData.GetParamNum();
                for (int ix = 0; ix < fnum; ++ix) {
                    BraceApiLoadInfo argLoadInfo;
                    auto statement = LoadHelper(*funcData.GetParam(ix), argLoadInfo);
                    if (statement)
                        m_Statements.push_back(std::move(statement));
                }
            }
            executor = std::bind(&ForeachExp::Execute, *this);
            return true;
        }
        virtual bool LoadStatement(const DslData::StatementData& statementData, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            //简化语法foreach(exp1,exp2,...) func(args);语法的处理
            if (statementData.GetFunctionNum() == 2) {
                auto* first = statementData.GetFirst()->AsFunction();
                auto* second = statementData.GetSecond()->AsFunction();
                const std::string& firstId = first->GetId();
                const std::string& secondId = second->GetId();
                if (firstId == "foreach" && !first->HaveStatement() && !first->HaveExternScript() &&
                    !secondId.empty() && !second->HaveStatement() && !second->HaveExternScript()) {
                    int num = first->GetParamNum();
                    if (num > 0) {
                        bool typeMatch = true;
                        int type = BRACE_DATA_TYPE_UNKNOWN;
                        for (int ix = 0; ix < num; ++ix) {
                            auto* exp = first->GetParam(ix);
                            BraceApiLoadInfo elemLoadInfo;
                            auto e = LoadHelper(*exp, elemLoadInfo);
                            if (elemLoadInfo.Type != BRACE_DATA_TYPE_UNKNOWN) {
                                if (type == BRACE_DATA_TYPE_UNKNOWN) {
                                    type = elemLoadInfo.Type;
                                }
                                else if (type != elemLoadInfo.Type) {
                                    typeMatch = false;
                                }
                            }
                            else {
                                typeMatch = false;
                            }
                            m_Elements.push_back(std::move(e));
                            m_ElementLoadInfos.push_back(std::move(elemLoadInfo));
                        }
                        m_IteratorIndex = AllocVariable("$$", type);
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
                    if (statement)
                        m_Statements.push_back(std::move(statement));
                    executor = std::bind(&ForeachExp::Execute, *this);
                    return true;
                }
            }
            return false;
        }
    private:
        int Execute(void)
        {
            auto& vars = *CurRuntimeStack().Variables;
            for (int ix = 0; ix < m_Elements.size() && ix < m_ElementLoadInfos.size(); ++ix) {
                m_Elements[ix]();
                auto& info = m_ElementLoadInfos[ix];
                switch (info.Type) {
                case BRACE_DATA_TYPE_OBJECT: {
                    auto* v = VarGetObject(vars, info.VarIndex);
                    VarSetObject(vars, m_IteratorIndex, v);
                }break;
                case BRACE_DATA_TYPE_STRING: {
                    auto v = VarGetString(vars, info.VarIndex);
                    VarSetString(vars, m_IteratorIndex, v);
                }break;
                default: {
                    auto v = VarGetI64(vars, info.Type, info.VarIndex);
                    VarSetI64(vars, m_ElementLoadInfos[0].Type, m_IteratorIndex, v);
                }break;
                }
                for (auto& statement : m_Statements) {
                    int v = statement();
                    if (v == BRACE_FLOW_CONTROL_CONTINUE) {
                        break;
                    }
                    else if (v != BRACE_FLOW_CONTROL_NORMAL) {
                        if (v == BRACE_FLOW_CONTROL_BREAK)
                            return BRACE_FLOW_CONTROL_NORMAL;
                        return v;
                    }
                }
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        int m_IteratorIndex;
        std::vector<BraceApiExecutor> m_Elements;
        std::vector<BraceApiLoadInfo> m_ElementLoadInfos;
        std::vector<BraceApiExecutor> m_Statements;
    };

    class ParenthesisExp final : public AbstractBraceApi
    {
    public:
        ParenthesisExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            std::swap(m_Args, args);
            std::swap(m_ArgLoadInfos, argLoadInfos);
            if (argLoadInfos.size() > 0) {
                m_ResultInfo = argLoadInfos[argLoadInfos.size() - 1];
                m_ResultInfo.VarIndex = AllocVariable(GenTempVarName(), m_ResultInfo.Type);
                loadInfo = m_ResultInfo;
            }
            executor = std::bind(&ParenthesisExp::Execute, *this);
            return true;
        }
    private:
        int Execute(void)
        {
            auto& vars = *CurRuntimeStack().Variables;
            for (auto& op : m_Args) {
                op();
            }
            if (m_ArgLoadInfos.size() > 0) {
                auto& info = m_ArgLoadInfos[m_ArgLoadInfos.size() - 1];
                int64_t v = VarGetI64(vars, info.Type, info.VarIndex);
                VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v);
            }
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    private:
        std::vector<BraceApiExecutor> m_Args;
        std::vector<BraceApiLoadInfo> m_ArgLoadInfos;
        BraceApiLoadInfo m_ResultInfo;
    };
    class ArrayExp final : public AbstractBraceApi
    {
    public:
        ArrayExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            executor = nullptr;
            return true;
        }
    };
    class HashtableExp final : public AbstractBraceApi
    {
    public:
        HashtableExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            executor = nullptr;
            return true;
        }
    };
    class LinqExp final : public AbstractBraceApi
    {
    public:
        LinqExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            executor = nullptr;
            return true;
        }
    };
    class MemberSetExp final : public AbstractBraceApi
    {
    public:
        MemberSetExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            executor = nullptr;
            return true;
        }
    };
    class MemberGetExp final : public AbstractBraceApi
    {
    public:
        MemberGetExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            executor = nullptr;
            return true;
        }
    };
    class MemberCallExp final : public AbstractBraceApi
    {
    public:
        MemberCallExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            executor = nullptr;
            return true;
        }
    };
    class CollectionSetExp final : public AbstractBraceApi
    {
    public:
        CollectionSetExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            executor = nullptr;
            return true;
        }
    };
    class CollectionGetExp final : public AbstractBraceApi
    {
    public:
        CollectionGetExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            executor = nullptr;
            return true;
        }
    };
    class CollectionCallExp final : public AbstractBraceApi
    {
    public:
        CollectionCallExp(BraceScript& interpreter) :AbstractBraceApi(interpreter)
        {
        }
    protected:
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override
        {
            executor = nullptr;
            return true;
        }
    };

    int VariableInfo::AllocVariable(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL: {
            int ix = static_cast<int>(BoolVars.size());
            BoolVars.push_back(false);
            return ix;
        }
        case BRACE_DATA_TYPE_INT8: {
            int ix = static_cast<int>(Int8Vars.size());
            Int8Vars.push_back(0);
            return ix;
        }
        case BRACE_DATA_TYPE_INT16: {
            int ix = static_cast<int>(Int16Vars.size());
            Int16Vars.push_back(0);
            return ix;
        }
        case BRACE_DATA_TYPE_INT32: {
            int ix = static_cast<int>(Int32Vars.size());
            Int32Vars.push_back(0);
            return ix;
        }
        case BRACE_DATA_TYPE_INT64: {
            int ix = static_cast<int>(Int64Vars.size());
            Int64Vars.push_back(0);
            return ix;
        }
        case BRACE_DATA_TYPE_UINT8: {
            int ix = static_cast<int>(Uint8Vars.size());
            Uint8Vars.push_back(0);
            return ix;
        }
        case BRACE_DATA_TYPE_UINT16: {
            int ix = static_cast<int>(Uint16Vars.size());
            Uint16Vars.push_back(0);
            return ix;
        }
        case BRACE_DATA_TYPE_UINT32: {
            int ix = static_cast<int>(Uint32Vars.size());
            Uint32Vars.push_back(0);
            return ix;
        }
        case BRACE_DATA_TYPE_UINT64: {
            int ix = static_cast<int>(Uint64Vars.size());
            Uint64Vars.push_back(0);
            return ix;
        }
        case BRACE_DATA_TYPE_FLOAT: {
            int ix = static_cast<int>(FloatVars.size());
            FloatVars.push_back(0);
            return ix;
        }
        case BRACE_DATA_TYPE_DOUBLE: {
            int ix = static_cast<int>(DoubleVars.size());
            DoubleVars.push_back(0);
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
        }
        return INVALID_INDEX;
    }

    VariableInfo* ProcInfo::AllocVariableInfo(void)const
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
    void ProcInfo::RecycleVariableInfo(VariableInfo* p)const
    {
        VariableInfoPool->push_back(p);
    }
    void ProcInfo::ShrinkPool(int max_num)const
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
    ProcInfo::ProcInfo(void)
    {
        VariableInfoPool = new std::deque<VariableInfo*>();
        VariableInfoStore = new std::vector<VariableInfo*>();
    }
    ProcInfo::ProcInfo(const ProcInfo& other)
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
    ProcInfo::ProcInfo(ProcInfo&& other)
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
    ProcInfo::~ProcInfo(void)
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

    ProcInfo* BraceScript::GlobalProcInfo(void)const
    {
        return m_GlobalProc;
    }
    VariableInfo* BraceScript::GlobalVariables(void)const
    {
        return m_GlobalVariables;
    }
    const RuntimeStackInfo& BraceScript::CurRuntimeStack(void)const
    {
        return m_RuntimeStack.top();
    }
    RuntimeStackInfo& BraceScript::CurRuntimeStack(void)
    {
        return m_RuntimeStack.top();
    }
    void BraceScript::PushRuntimeStack(const ProcInfo* procInfo)
    {
        const RuntimeStackInfo* lastStack = nullptr;
        if (!m_RuntimeStack.empty()) {
            lastStack = &m_RuntimeStack.top();
        }
        RuntimeStackInfo rsi;
        rsi.LastStackInfo = lastStack;
        rsi.Proc = procInfo;
        rsi.Variables = procInfo->AllocVariableInfo();
        m_RuntimeStack.push(std::move(rsi));
        if (m_RuntimeStack.size() == 1) {
            m_GlobalVariables = m_RuntimeStack.top().Variables;
        }
    }
    void BraceScript::PopRuntimeStack(void)
    {
        RuntimeStackInfo& info = m_RuntimeStack.top();
        info.Proc->RecycleVariableInfo(info.Variables);
        m_RuntimeStack.pop();
    }

    void BraceScript::LogInfo(const std::string& info)
    {
        if (OnInfo)
            OnInfo(info);
    }
    void BraceScript::LogError(const std::string& error)
    {
        m_HasError = true;
        if (OnError)
            OnError(error);
    }
    void BraceScript::AddSyntaxComponent(DslData::ISyntaxComponent* p)
    {
        m_AddedSyntaxComponents.push_back(p);
    }
    void BraceScript::AddApiInstance(IBraceApi* p)
    {
        m_ApiInstances.push_back(p);
    }
    bool BraceScript::CanAssign(int destType, int srcType)
    {
        //Object assignment need to be handled further
        return Brace::CanAssign(destType, srcType);
    }
    const ProcInfo* BraceScript::GetProcInfo(const std::string& name)const
    {
        auto it = m_Procs.find(name);
        if (it != m_Procs.end())
            return &(it->second);
        return nullptr;
    }
    ProcInfo* BraceScript::GetProcInfo(const std::string& name)
    {
        auto it = m_Procs.find(name);
        if (it != m_Procs.end())
            return &(it->second);
        return nullptr;
    }
    const ProcInfo* BraceScript::CurProcInfo(void)const
    {
        return m_ProcInfoStack.top();
    }
    ProcInfo* BraceScript::CurProcInfo(void)
    {
        return m_ProcInfoStack.top();
    }
    ProcInfo* BraceScript::PushNewProcInfo(const std::string& name)
    {
        auto pair = m_Procs.insert(std::make_pair(name, ProcInfo()));
        auto* p = &(pair.first->second);
        p->Name = name;
        m_ProcInfoStack.push(p);
        ++m_CurBlockLevel;
        return p;
    }
    void BraceScript::PopProcInfo(void)
    {
        --m_CurBlockLevel;
        m_ProcInfoStack.pop();
    }
    std::string BraceScript::CalcVarKey(const std::string& name, int level)const
    {
        std::string key = name + "__" + std::to_string(level);
        return key;
    }
    std::string BraceScript::CalcConstKey(const std::string& value)const
    {
        std::string key = "\"" + value + "\"";
        return key;
    }
    int BraceScript::AllocGlobalVariable(const std::string& name, int type)
    {
        auto it = m_GlobalProc->VarTypeInfos.find(name);
        if (it == m_GlobalProc->VarTypeInfos.end()) {
            int index = m_GlobalProc->VarInitInfo.AllocVariable(type);
            m_GlobalProc->VarTypeInfos.insert(std::make_pair(name, VarInfo(name, type, index)));
            return index;
        }
        else {
            return it->second.VarIndex;
        }
    }
    int BraceScript::AllocConst(int tok_type, const std::string& value, int& type)
    {
        std::string key = CalcConstKey(value);
        auto* proc = GlobalProcInfo();
        auto it = proc->VarTypeInfos.find(key);
        if (it == proc->VarTypeInfos.end()) {
            int index = INVALID_INDEX;
            type = BRACE_DATA_TYPE_UNKNOWN;
            switch (tok_type) {
            case DslData::ValueData::VALUE_TYPE_IDENTIFIER:
                if (value == "true" || value == "false") {
                    type = BRACE_DATA_TYPE_BOOL;
                    index = proc->VarInitInfo.AllocVariable(type);
                    proc->VarInitInfo.BoolVars[index] = value == "true";
                }
                break;
            case DslData::ValueData::VALUE_TYPE_STRING:
                type = BRACE_DATA_TYPE_STRING;
                index = proc->VarInitInfo.AllocVariable(type);
                proc->VarInitInfo.StringVars[index] = value;
                break;
            case DslData::ValueData::VALUE_TYPE_NUM:
                if (value.find('.', 0) != std::string::npos) {
                    double v = StrToDouble(value);
                    if (v >= std::numeric_limits<float>::min() && v <= std::numeric_limits<float>::max()) {
                        type = BRACE_DATA_TYPE_FLOAT;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.FloatVars[index] = static_cast<float>(v);
                    }
                    else {
                        type = BRACE_DATA_TYPE_DOUBLE;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.DoubleVars[index] = v;
                    }
                }
                else if (value.length() > 0 && value[0] == '-') {
                    int64_t v = StrToInt64(value);
                    if (v >= std::numeric_limits<int8_t>::min()) {
                        type = BRACE_DATA_TYPE_INT8;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Int8Vars[index] = static_cast<int8_t>(v);
                    }
                    else if (v >= std::numeric_limits<int16_t>::min()) {
                        type = BRACE_DATA_TYPE_INT16;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Int16Vars[index] = static_cast<int16_t>(v);
                    }
                    else if (v >= std::numeric_limits<int32_t>::min()) {
                        type = BRACE_DATA_TYPE_INT32;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Int32Vars[index] = static_cast<int32_t>(v);
                    }
                    else if (v >= std::numeric_limits<int64_t>::min()) {
                        type = BRACE_DATA_TYPE_INT64;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Int64Vars[index] = v;
                    }
                }
                else {
                    uint64_t v = StrToUInt64(value);
                    if (v <= static_cast<uint64_t>(std::numeric_limits<int8_t>::max())) {
                        type = BRACE_DATA_TYPE_INT8;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Int8Vars[index] = static_cast<int8_t>(v);
                    }
                    else if (v <= std::numeric_limits<uint8_t>::max()) {
                        type = BRACE_DATA_TYPE_UINT8;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Uint8Vars[index] = static_cast<uint8_t>(v);
                    }
                    else if (v <= static_cast<uint64_t>(std::numeric_limits<int16_t>::max())) {
                        type = BRACE_DATA_TYPE_INT16;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Int16Vars[index] = static_cast<int16_t>(v);
                    }
                    else if (v <= std::numeric_limits<uint16_t>::max()) {
                        type = BRACE_DATA_TYPE_UINT16;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Uint16Vars[index] = static_cast<uint16_t>(v);
                    }
                    else if (v <= static_cast<uint64_t>(std::numeric_limits<int32_t>::max())) {
                        type = BRACE_DATA_TYPE_INT32;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Int32Vars[index] = static_cast<int32_t>(v);
                    }
                    else if (v <= std::numeric_limits<uint32_t>::max()) {
                        type = BRACE_DATA_TYPE_UINT32;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Uint32Vars[index] = static_cast<uint32_t>(v);
                    }
                    else if (v <= static_cast<uint64_t>(std::numeric_limits<int64_t>::max())) {
                        type = BRACE_DATA_TYPE_INT64;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Int64Vars[index] = static_cast<int64_t>(v);
                    }
                    else if (v <= std::numeric_limits<uint64_t>::max()) {
                        type = BRACE_DATA_TYPE_UINT64;
                        index = proc->VarInitInfo.AllocVariable(type);
                        proc->VarInitInfo.Uint64Vars[index] = v;
                    }
                }
                break;
            }
            if (type != BRACE_DATA_TYPE_UNKNOWN) {
                proc->VarTypeInfos.insert(std::make_pair(key, VarInfo(value, type, index)));
            }
            return index;
        }
        else {
            return it->second.VarIndex;
        }
    }
    auto BraceScript::FindVariable(ProcInfo* proc, const std::string& name, std::string& key, int& level) -> decltype(proc->VarTypeInfos.end())
    {
        key = CalcVarKey(name, m_CurBlockLevel);
        std::string fkey = key;
        int curLevel = m_CurBlockLevel;
        decltype(proc->VarTypeInfos.end()) it;
        while (curLevel >= 0) {
            it = proc->VarTypeInfos.find(fkey);
            if (it != proc->VarTypeInfos.end())
                break;
            --curLevel;
            if (curLevel >= 0)
                fkey = CalcVarKey(name, curLevel);
        }
        return it;
    }
    int BraceScript::AllocVariable(const std::string& name, int type)
    {
        auto* proc = CurProcInfo();
        std::string key;
        int level;
        auto it = FindVariable(proc, name, key, level);
        if (it == proc->VarTypeInfos.end()) {
            int index = proc->VarInitInfo.AllocVariable(type);
            proc->VarTypeInfos.insert(std::make_pair(key, VarInfo(name, type, index)));
            return index;
        }
        else {
            return it->second.VarIndex;
        }
    }
    BraceApiExecutor BraceScript::Load(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& loadInfo)
    {
        switch (syntaxUnit.GetSyntaxType()) {
        case DslData::ISyntaxComponent::TYPE_VALUE:
            return LoadValue(static_cast<const DslData::ValueData&>(syntaxUnit), loadInfo);
        case DslData::ISyntaxComponent::TYPE_FUNCTION:
            return LoadFunction(static_cast<const DslData::FunctionData&>(syntaxUnit), loadInfo);
        case DslData::ISyntaxComponent::TYPE_STATEMENT:
            return LoadStatement(static_cast<const DslData::StatementData&>(syntaxUnit), loadInfo);
        default:
            return BraceApiExecutor();
        }
    }
    BraceApiExecutor BraceScript::LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& loadInfo)
    {
        BraceApiExecutor executor;
        int idType = data.GetIdType();
        if (idType == DslData::ValueData::VALUE_TYPE_IDENTIFIER) {
            const std::string& id = data.GetId();
            auto* p = CreateApi(id);
            if (nullptr != p) {
                //将无参数名字转换为无参函数调用
                auto* fd = new DslData::FunctionData();
                AddSyntaxComponent(fd);
                fd->SetName(data);
                fd->SetParamClass(DslData::FunctionData::PARAM_CLASS_PARENTHESIS);
                if (!p->Load(*fd, loadInfo, executor)) {
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
                pBreak->Load(data, loadInfo, executor);
                return executor;
            }
            else if (id == "continue") {
                auto* pContinue = new ContinueExp(*this);
                AddApiInstance(pContinue);
                pContinue->Load(data, loadInfo, executor);
                return executor;
            }
            else if (id == "true" || id == "false") {
                auto* pConstGet = new ConstGet(*this);
                AddApiInstance(pConstGet);
                pConstGet->Load(data, loadInfo, executor);
                return executor;
            }
            else if (id.length() > 0 && id[0] == '$') {
                auto* pLocalGet = new LocalVarGet(*this);
                AddApiInstance(pLocalGet);
                pLocalGet->Load(data, loadInfo, executor);
                return executor;
            }
            else if (id.length() > 0 && id[0] == '@') {
                auto* pGlobalGet = new GlobalVarGet(*this);
                AddApiInstance(pGlobalGet);
                pGlobalGet->Load(data, loadInfo, executor);
                return executor;
            }
            else {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
                return executor;
            }
        }
        else {
            auto* pConstGet = new ConstGet(*this);
            AddApiInstance(pConstGet);
            pConstGet->Load(data, loadInfo, executor);
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
    BraceApiExecutor BraceScript::LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo)
    {
        BraceApiExecutor executor;
        if (data.HaveParam()) {
            auto& callData = data;
            if (!callData.HaveId() && !callData.IsHighOrder() && (callData.GetParamClass() == DslData::FunctionData::PARAM_CLASS_PARENTHESIS || callData.GetParamClass() == DslData::FunctionData::PARAM_CLASS_BRACKET)) {
                switch (callData.GetParamClass()) {
                case DslData::FunctionData::PARAM_CLASS_PARENTHESIS: {
                    int num = callData.GetParamNum();
                    if (num == 1) {
                        auto* param = callData.GetParam(0);
                        return Load(*param, loadInfo);
                    }
                    else {
                        auto* p = new ParenthesisExp(*this);
                        AddApiInstance(p);
                        p->Load(data, loadInfo, executor);
                        return executor;
                    }
                }break;
                case DslData::FunctionData::PARAM_CLASS_BRACKET: {
                    auto* p = new ArrayExp(*this);
                    AddApiInstance(p);
                    p->Load(data, loadInfo, executor);
                    return executor;
                }break;
                default:
                    return executor;
                }
            }
            else if (!callData.HaveParam()) {
                //退化
                return Load(callData.GetName(), loadInfo);
            }
            else {
                int paramClass = callData.GetParamClass();
                auto& op = callData.GetId();
                if (op == "=") {//赋值
                    auto* pParam = callData.GetParam(0);
                    if (pParam && pParam->GetSyntaxType() == DslData::ISyntaxComponent::TYPE_FUNCTION) {
                        auto* innerCall = static_cast<DslData::FunctionData*>(pParam);
                        if (nullptr != innerCall) {
                            //obj.property = val -> dotnetset(obj, property, val)
                            int innerParamClass = innerCall->GetParamClass();
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
                                    ConvertMember(p, innerCall->GetParamClass());
                                    newCall->AddParamCopyFrom(*callData.GetParam(1));
                                }
                                else {
                                    newCall->AddParamCopyFrom(innerCall->GetName());
                                    auto* p = newCall->AddParamCopyFrom(*innerCall->GetParam(0));
                                    ConvertMember(p, innerCall->GetParamClass());
                                    newCall->AddParamCopyFrom(*callData.GetParam(1));
                                }

                                return Load(*newCall, loadInfo);
                            }
                        }
                    }
                    IBraceApi* api0 = nullptr;
                    const std::string& name = callData.GetParamId(0);
                    if (name.length() > 0 && name[0] == '$') {
                        api0 = new LocalVarSet(*this);
                        AddApiInstance(api0);
                    }
                    else {
                        api0 = new GlobalVarSet(*this);
                        AddApiInstance(api0);
                    }
                    if (nullptr != api0) {
                        api0->Load(data, loadInfo, executor);
                    }
                    else {
                        //error
                        std::stringstream ss;
                        ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                        LogError(ss.str());
                    }
                    return executor;
                }
                else if (op == "<-") {
                    //单表达式参数语句
                    if (callData.GetParamNum() == 2) {
                        auto* p = CreateApi(callData.GetParamId(0));
                        p->Load(callData, loadInfo, executor);
                        return executor;
                    }
                }
                else if (op == "=>") {
                    //lambda表达式
                    auto* p = new LambdaExp(*this);
                    AddApiInstance(p);
                    p->Load(callData, loadInfo, executor);
                    return executor;
                }
                else {
                    if (callData.IsHighOrder()) {
                        auto& innerCall = callData.GetLowerOrderFunction();
                        int innerParamClass = innerCall.GetParamClass();
                        if (paramClass == DslData::FunctionData::PARAM_CLASS_PARENTHESIS && (
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD ||
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_BRACKET ||
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACE ||
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACKET ||
                            innerParamClass == DslData::FunctionData::PARAM_CLASS_PERIOD_PARENTHESIS)) {
                            //obj.member(a,b,...) or obj[member](a,b,...) or obj.(member)(a,b,...) or obj.[member](a,b,...) or obj.{member}(a,b,...) -> dotnetcall(obj,member,a,b,...)
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
                                ConvertMember(p, innerCall.GetParamClass());
                                for (int i = 0; i < callData.GetParamNum(); ++i) {
                                    newCall->AddParamCopyFrom(*callData.GetParam(i));
                                }
                            }
                            else {
                                newCall->AddParamCopyFrom(innerCall.GetName());
                                auto* p = newCall->AddParamCopyFrom(*innerCall.GetParam(0));
                                ConvertMember(p, innerCall.GetParamClass());
                                for (int i = 0; i < callData.GetParamNum(); ++i) {
                                    newCall->AddParamCopyFrom(*callData.GetParam(i));
                                }
                            }

                            return Load(*newCall, loadInfo);
                        }
                    }
                    if (paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD ||
                        paramClass == DslData::FunctionData::PARAM_CLASS_BRACKET ||
                        paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACE ||
                        paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD_BRACKET ||
                        paramClass == DslData::FunctionData::PARAM_CLASS_PERIOD_PARENTHESIS) {
                        //obj.property or obj[property] or obj.(property) or obj.[property] or obj.{property} -> dotnetget(obj,property)
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
                            ConvertMember(callData.GetParam(0), callData.GetParamClass());
                        }
                        else {
                            newCall->AddParamCopyFrom(callData.GetName());
                            auto* p = newCall->AddParamCopyFrom(*callData.GetParam(0));
                            ConvertMember(callData.GetParam(0), callData.GetParamClass());
                        }

                        return Load(*newCall, loadInfo);
                    }
                }
            }
        }
        else {
            if (data.HaveStatement()) {
                if (!data.HaveId() && !data.IsHighOrder()) {
                    auto* p = new HashtableExp(*this);
                    AddApiInstance(p);
                    p->Load(data, loadInfo, executor);
                    return executor;
                }
            }
            else if (!data.HaveExternScript()) {
                //退化
                return Load(data.GetName(), loadInfo);
            }
        }
        IBraceApi* api = nullptr;
        const std::string& name = data.GetId();
        if (!data.IsHighOrder() && m_Procs.find(name) != m_Procs.end()) {
            api = new FunctionCall(*this);
            AddApiInstance(api);
        }
        else {
            api = CreateApi(name);
        }
        if (nullptr != api) {
            if (!api->Load(data, loadInfo, executor)) {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
            }
        }
        else {
            //error
            std::stringstream ss;
            ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
            LogError(ss.str());
        }
        return executor;
    }
    BraceApiExecutor BraceScript::LoadStatement(const DslData::StatementData& data, BraceApiLoadInfo& loadInfo)
    {
        BraceApiExecutor executor;
        IBraceApi* ret = CreateApi(data.GetId());
        if (nullptr != ret) {
            auto* first = data.GetFirst()->AsValue();
            if (nullptr != first) {
                //将命令行语法转换为函数调用语法
                auto* fd = new DslData::FunctionData();
                AddSyntaxComponent(fd);
                fd->SetName(*first);
                for (int argi = 1; argi < data.GetFunctionNum(); ++argi) {
                    auto* pfd = data.GetFunction(argi);
                    if (nullptr != pfd) {
                        fd->AddParamCopyFrom(*pfd);
                    }
                }
                if (!ret->Load(*fd, loadInfo, executor)) {
                    //error
                    std::stringstream ss;
                    ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                    LogError(ss.str());
                }
                return executor;
            }
            if (!ret->Load(data, loadInfo, executor)) {
                //error
                std::stringstream ss;
                ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
                LogError(ss.str());
            }
        }
        else {
            //error
            std::stringstream ss;
            ss << "BraceScript error, " << data.GetId() << " line " << data.GetLine();
            LogError(ss.str());
        }
        return executor;
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

    void BraceScript::RegisterInnerApis(void)
    {
        RegisterApi("+", new BraceApiFactory<AddExp>());
        RegisterApi("-", new BraceApiFactory<SubExp>());
        RegisterApi("*", new BraceApiFactory<MulExp>());
        RegisterApi("/", new BraceApiFactory<DivExp>());
        RegisterApi("%", new BraceApiFactory<ModExp>());
        RegisterApi("&", new BraceApiFactory<BitAndExp>());
        RegisterApi("|", new BraceApiFactory<BitOrExp>());
        RegisterApi("^", new BraceApiFactory<BitXorExp>());
        RegisterApi("~", new BraceApiFactory<BitNotExp>());
        RegisterApi("<<", new BraceApiFactory<LShiftExp>());
        RegisterApi(">>", new BraceApiFactory<RShiftExp>());
        RegisterApi(">", new BraceApiFactory<GreatExp>());
        RegisterApi(">=", new BraceApiFactory<GreatEqualExp>());
        RegisterApi("<", new BraceApiFactory<LessExp>());
        RegisterApi("<=", new BraceApiFactory<LessEqualExp>());
        RegisterApi("==", new BraceApiFactory<EqualExp>());
        RegisterApi("!=", new BraceApiFactory<NotEqualExp>());
        RegisterApi("&&", new BraceApiFactory<AndExp>());
        RegisterApi("||", new BraceApiFactory<OrExp>());
        RegisterApi("!", new BraceApiFactory<NotExp>());
        RegisterApi("?", new BraceApiFactory<CondExp>());
        RegisterApi("echo", new BraceApiFactory<EchoExp>());
        RegisterApi("if", new BraceApiFactory<IfExp>());
        RegisterApi("while", new BraceApiFactory<WhileExp>());
        RegisterApi("loop", new BraceApiFactory<LoopExp>());
        RegisterApi("looplist", new BraceApiFactory<LoopListExp>());
        RegisterApi("foreach", new BraceApiFactory<ForeachExp>());
        RegisterApi("return", new BraceApiFactory<ReturnExp>());
        RegisterApi("func", new BraceApiFactory<FunctionDefine>());
        RegisterApi("membercall", new BraceApiFactory<MemberCallExp>());
        RegisterApi("memberset", new BraceApiFactory<MemberSetExp>());
        RegisterApi("memberget", new BraceApiFactory<MemberGetExp>());
        RegisterApi("collectioncall", new BraceApiFactory<CollectionCallExp>());
        RegisterApi("collectionset", new BraceApiFactory<CollectionSetExp>());
        RegisterApi("collectionget", new BraceApiFactory<CollectionGetExp>());
        RegisterApi("linq", new BraceApiFactory<LinqExp>());
        RegisterApi("array", new BraceApiFactory<ArrayExp>());
        RegisterApi("hashtable", new BraceApiFactory<HashtableExp>());
    }
    void BraceScript::Init(void)
    {
        m_HasError = false;
        m_NextUniqueId = 0;

        std::string name = "global";
        auto pair = m_Procs.insert(std::make_pair(name, ProcInfo()));
        auto* p = &(pair.first->second);
        p->Name = name;
    }
    void BraceScript::Release(void)
    {
        m_Procs.clear();
        for (auto* p : m_ApiInstances) {
            delete p;
        }
        m_ApiInstances.clear();
        for (auto* p : m_AddedSyntaxComponents) {
            delete p;
        }
        m_AddedSyntaxComponents.clear();
    }

    BraceScript::BraceScript(void) :m_NextUniqueId(0), m_CurBlockLevel(0), m_HasError(false), m_GlobalProc(nullptr), m_GlobalVariables(nullptr)
    {
        RegisterInnerApis();
        Init();
    }
    BraceScript::~BraceScript(void)
    {
        Release();
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
    void BraceScript::Reset(void)
    {
        Release();
        Init();
    }
    void BraceScript::LoadScript(const DslData::DslFile& file)
    {
        m_CurBlockLevel = 0;
        auto it = m_Procs.find("global");
        m_GlobalProc = &(it->second);
        m_ProcInfoStack.push(&(it->second));
        for (int ix = 0; ix < file.GetDslInfoNum(); ++ix) {
            auto* p = file.GetDslInfo(ix);
            BraceApiLoadInfo loadInfo;
            auto executor = Load(*p, loadInfo);
            if (executor) {
                m_GlobalProc->Codes.push_back(std::move(executor));
            }
        }
        m_ProcInfoStack.pop();
    }
    void BraceScript::Run(void)
    {
        if (nullptr == m_GlobalProc)
            return;
        auto* proc = m_GlobalProc;
        PushRuntimeStack(proc);
        for (auto& p : proc->Codes) {
            int r = p();
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
        PopRuntimeStack();
    }
}