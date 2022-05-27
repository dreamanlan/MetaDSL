
#pragma once

#include "Dsl.h"
#include <stack>
#include <deque>
#include <unordered_map>
#include <functional>

namespace Brace
{
    enum BraceFlowControlEnum
    {
        BRACE_FLOW_CONTROL_EXIT = -1,
        BRACE_FLOW_CONTROL_NORMAL = 0,
        BRACE_FLOW_CONTROL_RETURN,
        BRACE_FLOW_CONTROL_BREAK,
        BRACE_FLOW_CONTROL_CONTINUE,
        BRACE_FLOW_CONTROL_EXCEPTION,
        BRACE_FLOW_CONTROL_EFFECT,
        BRACE_FLOW_CONTROL_NUM
    };
    enum BraceDataTypeEnum
    {
        BRACE_DATA_TYPE_UNKNOWN = -1,
        BRACE_DATA_TYPE_BOOL = 0,
        BRACE_DATA_TYPE_INT8,
        BRACE_DATA_TYPE_INT16,
        BRACE_DATA_TYPE_INT32,
        BRACE_DATA_TYPE_INT64,
        BRACE_DATA_TYPE_UINT8,
        BRACE_DATA_TYPE_UINT16,
        BRACE_DATA_TYPE_UINT32,
        BRACE_DATA_TYPE_UINT64,
        BRACE_DATA_TYPE_FLOAT,
        BRACE_DATA_TYPE_DOUBLE,
        BRACE_DATA_TYPE_STRING,
        BRACE_DATA_TYPE_OBJECT,
        BRACE_DATA_TYPE_NUM
    };
    enum BraceObjectTypeIdEnum
    {
        BRACE_OBJECT_UNKNOWN = -1,
        BRACE_OBJECT_ARRAY = 0,
        BRACE_OBJECT_HASHTABLE,
        BRACE_OBJECT_NUM
    };

    struct VariableInfo;
    typedef void (*VarAssignPtr)(VariableInfo&, int, VariableInfo&, int);
    extern VarAssignPtr GetVarAssignPtr(int varType, int srcVarType);
    extern const char* GetBraceDataTypeName(int type);
    extern int GetBraceDataType(const std::string& typeName);

    class IBraceObject
    {
    public:
        virtual int GetObjectTypeId(void)const { return BRACE_OBJECT_UNKNOWN; }
    public:
        virtual ~IBraceObject(void) {}
    };

    template<typename BaseClassT, int TypeId>
    class BaseBraceObjectT : public BaseClassT, public IBraceObject
    {
    public:
        virtual int GetObjectTypeId(void)const override { return TypeId; }
    };

    struct VarTypeInfo
    {
        int Type;
        int VarIndex;
        bool IsGlobal;

        VarTypeInfo(void) :Type(BRACE_DATA_TYPE_UNKNOWN), VarIndex(INVALID_INDEX), IsGlobal(false)
        {}
        VarTypeInfo(int type, int varIndex) :Type(type), VarIndex(varIndex), IsGlobal(false)
        {}
        VarTypeInfo(int type, int varIndex, bool isGlobal) :Type(type), VarIndex(varIndex), IsGlobal(isGlobal)
        {}
    };
    struct VarInfo final : public VarTypeInfo
    {
        std::string Name;

        VarInfo(void) :VarTypeInfo(), Name() 
        {}
        VarInfo(const std::string& name, int type, int index) :VarTypeInfo(type, index), Name(name) 
        {}
        VarInfo(const std::string& name, int type, int index, bool isGlobal) :VarTypeInfo(type, index, isGlobal), Name(name) 
        {}
    };
    struct BraceApiLoadInfo final : public VarTypeInfo
    {
        BraceApiLoadInfo(void) :VarTypeInfo()
        {}
        BraceApiLoadInfo(int type, int varIndex) :VarTypeInfo(type, varIndex)
        {}
        BraceApiLoadInfo(int type, int index, bool isGlobal) :VarTypeInfo(type, index, isGlobal)
        {}
    };

    /// Load can be considered in two ways. One is to prepare the execution environment for the current API. IBraceApi forms a tree code 
    /// structure and compound statements can also be added to the language as an API, runtime performance may depend more on c++ optimization
    /// of function calls.
    /// Another way is to call BraceScript to generate the intermediate instructions, by allowing IBraceApi as instructions, still can 
    /// keep certain extensibility(compound statements need to split into jump, conditional or not), which is equivalent to converting the 
    /// code structure to a linear structure.
    /// We implement first one first.
    class BraceScript;
    //We only need a member function to run, not a virtual function
    using BraceApiExecutor = std::function<int(void)>;
    class IBraceApi
    {
    public:
        virtual bool Load(const DslData::ISyntaxComponent& syntax, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) = 0;
    public:
        virtual ~IBraceApi(void) {}
    protected:
        IBraceApi(void) {}
    private:
        IBraceApi(const IBraceApi&) = delete;
        IBraceApi& operator=(const IBraceApi&) = delete;
        IBraceApi(IBraceApi&&) noexcept = delete;
        IBraceApi& operator=(IBraceApi&&) noexcept = delete;
    };

    struct VariableInfo final
    {
        std::vector<bool> BoolVars;
        std::vector<int8_t> Int8Vars;
        std::vector<int16_t> Int16Vars;
        std::vector<int32_t> Int32Vars;
        std::vector<int64_t> Int64Vars;
        std::vector<uint8_t> Uint8Vars;
        std::vector<uint16_t> Uint16Vars;
        std::vector<uint32_t> Uint32Vars;
        std::vector<uint64_t> Uint64Vars;
        std::vector<float> FloatVars;
        std::vector<double> DoubleVars;
        std::vector<std::string> StringVars;
        std::vector<IBraceObject*> ObjectVars;

        int AllocVariable(int type);
    };

    struct ProcInfo final
    {
        std::string Name;
        std::vector<VarInfo> Params;
        VarInfo RetValue;
        std::unordered_map<std::string, VarInfo> VarTypeInfos;
        std::vector<BraceApiExecutor> Codes;
        VariableInfo VarInitInfo;

        VariableInfo* AllocVariableInfo(void)const;
        void RecycleVariableInfo(VariableInfo* p)const;
        void ShrinkPool(int max_num)const;

        ProcInfo(void);
        ProcInfo(const ProcInfo& other);
        ProcInfo(ProcInfo&& other) noexcept;
        ~ProcInfo(void);
    private:
        /// Members of ProcInfo are immutable at run time, except for VaraibleInfoPool & VariableInfoStore, which uses Pointers 
        /// to preserve the const semantics of ProcInfo. 
        /// Stack operations are used to use recently used memory for better locality, while deques are used to shrink memory.
        std::deque<VariableInfo*>* VariableInfoPool;
        std::vector<VariableInfo*>* VariableInfoStore;
    };

    struct RuntimeStackInfo final
    {
        const RuntimeStackInfo* LastStackInfo;
        const ProcInfo* Proc;
        VariableInfo* Variables;
    };

    class IBraceApiFactory
    {
    public:
        virtual IBraceApi* Create(BraceScript& interpreter) = 0;
    public:
        virtual ~IBraceApiFactory(void) {}
    };

    class AbstractBraceApi : public IBraceApi
    {
    public:
        virtual bool Load(const DslData::ISyntaxComponent& syntax, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor) override;
    protected:
        virtual bool LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadStatement(const DslData::StatementData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadCall(std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor)
        {
            return false;
        }
    protected:
        const char* GetTypeName(int type)const { return GetBraceDataTypeName(type); }
        std::string GenTempVarName(void)const;
        ProcInfo* GetProcInfo(const std::string& name)const;
        VarTypeInfo* GetGlobalVarTypeInfo(const std::string& name)const;
        VarTypeInfo* GetVarTypeInfo(const std::string& name)const;
        VarTypeInfo* GetConstTypeInfo(const std::string& name)const;
        bool CanAssign(int destType, int srcType)const;
        ProcInfo* CurProcInfo(void)const;
        ProcInfo* PushNewProcInfo(const std::string& name)const;
        void PopProcInfo(void)const;
        int GenNextUniqueId(void)const;
        int CurBlockId(void)const;
        void PushBlock(void)const;
        void PopBlock(void)const;
        int AllocGlobalVariable(const std::string& name, int type)const;
        int AllocVariable(const std::string& name, int type)const;
        int AllocConst(int tok_type, const std::string& value, int& type)const;
        void LogInfo(const std::string& msg)const;
        void LogError(const std::string& msg)const;
        void AddSyntaxComponent(DslData::ISyntaxComponent* p)const;
        void AddApiInstance(IBraceApi* p)const;
        BraceApiExecutor LoadHelper(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& loadInfo)const;
    protected:
        ProcInfo* GlobalProcInfo(void)const;
        VariableInfo* GlobalVariables(void)const;
        RuntimeStackInfo& CurRuntimeStack(void)const;
        void PushRuntimeStack(const ProcInfo* procInfo)const;
        void PopRuntimeStack(void)const;
    protected:
        AbstractBraceApi(BraceScript& interpreter) :m_Interpreter(interpreter)
        {}
    private:
        AbstractBraceApi(const AbstractBraceApi&) = delete;
        AbstractBraceApi& operator=(const AbstractBraceApi&) = delete;
        AbstractBraceApi(AbstractBraceApi&&) noexcept = delete;
        AbstractBraceApi& operator=(AbstractBraceApi&&) noexcept = delete;
    private:
        BraceScript& GetInterpreter(void)const { return m_Interpreter; }
    private:
        BraceScript& m_Interpreter;
    };

    template<typename ApiT>
    class BraceApiFactory final : public IBraceApiFactory
    {
    public:
        virtual IBraceApi* Create(BraceScript& interpreter) override
        {
            return new ApiT(interpreter);
        }
    };

    typedef std::stack<ProcInfo*> ProcInfoStack;
    typedef std::stack<RuntimeStackInfo> RuntimeStack;
    typedef std::function<void(const std::string&)> LogDelegation;
    class BraceScript final
    {
        friend class AbstractBraceApi;
    public:
        BraceScript(void);
        ~BraceScript(void);
    public:
        LogDelegation OnInfo;
        LogDelegation OnError;
        void RegisterApi(const std::string& id, IBraceApiFactory* pApiFactory);
        void RegisterApi(std::string&& id, IBraceApiFactory* pApiFactory);
        void Reset(void);
        void LoadScript(const DslData::DslFile& file);
        void Run(void);
        bool HasError(void)const { return m_HasError; }
    private:
        ProcInfo* GlobalProcInfo(void)const;
        VariableInfo* GlobalVariables(void)const;
        const RuntimeStackInfo& CurRuntimeStack(void)const;
        RuntimeStackInfo& CurRuntimeStack(void);
        void PushRuntimeStack(const ProcInfo* procInfo);
        void PopRuntimeStack(void);
    private:
        void LogInfo(const std::string& info);
        void LogError(const std::string& info);
        void AddSyntaxComponent(DslData::ISyntaxComponent* p);
        void AddApiInstance(IBraceApi* p);
        const char* GetTypeName(int type)const { return GetBraceDataTypeName(type); }
        bool CanAssign(int destType, int srcType);
        const ProcInfo* GetProcInfo(const std::string& name)const;
        ProcInfo* GetProcInfo(const std::string& name);
        const ProcInfo* CurProcInfo(void)const;
        ProcInfo* CurProcInfo(void);
        ProcInfo* PushNewProcInfo(const std::string& name);
        void PopProcInfo(void);
        int GenNextUniqueId(void) { return m_NextUniqueId++; }
        int CurBlockId(void)const;
        void PushBlock(void);
        void PopBlock(void);
        std::string CalcVarKey(const std::string& name, int level)const;
        std::string CalcConstKey(const std::string& name)const;
        int AllocGlobalVariable(const std::string& name, int type);
        int AllocConst(int tok_type, const std::string& value, int& type);
        auto FindVariable(ProcInfo* proc, const std::string& name, std::string& key, int& level) -> decltype(proc->VarTypeInfos.end());
        int AllocVariable(const std::string& name, int type);
        BraceApiExecutor Load(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& loadInfo);
    private:
        BraceApiExecutor LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& loadInfo);
        BraceApiExecutor LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo);
        BraceApiExecutor LoadStatement(const DslData::StatementData& data, BraceApiLoadInfo& loadInfo);
        IBraceApi* CreateApi(const std::string& name);
        void RegisterInnerApis(void);
        void Init(void);
        void Release(void);
    private:
        BraceScript(const BraceScript&) = delete;
        BraceScript& operator=(const BraceScript&) = delete;
        BraceScript(BraceScript&&) noexcept = delete;
        BraceScript& operator=(BraceScript&&) noexcept = delete;
    private:
        std::unordered_map<std::string, IBraceApiFactory*> m_ApiFactories;
        std::vector<DslData::ISyntaxComponent*> m_AddedSyntaxComponents;
        std::vector<IBraceApi*> m_ApiInstances;
        std::unordered_map<std::string, ProcInfo> m_Procs;

        bool m_HasError;
        ProcInfoStack m_ProcInfoStack;
        int m_NextUniqueId;
        int m_CurBlockId;
        std::vector<int> m_LexicalScopeStack;
        ProcInfo* m_GlobalProc;
        VariableInfo* m_GlobalVariables;
        RuntimeStack m_RuntimeStack;
    };
}