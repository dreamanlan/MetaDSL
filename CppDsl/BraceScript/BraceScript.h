
#pragma once

#include "Dsl.h"
#include <stack>
#include <deque>
#include <unordered_map>
#include <functional>
#include <memory>

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
        BRACE_DATA_TYPE_UINT8,
        BRACE_DATA_TYPE_INT16,
        BRACE_DATA_TYPE_UINT16,
        BRACE_DATA_TYPE_INT32,
        BRACE_DATA_TYPE_UINT32,
        BRACE_DATA_TYPE_INT64,
        BRACE_DATA_TYPE_UINT64,
        BRACE_DATA_TYPE_FLOAT,
        BRACE_DATA_TYPE_DOUBLE,
        BRACE_DATA_TYPE_STRING,
        BRACE_DATA_TYPE_OBJECT,
        BRACE_DATA_TYPE_REF,
        BRACE_DATA_TYPE_NUM
    };
    enum BraceObjectTypeIdEnum
    {
        BRACE_PREDEFINED_OBJECT_TYPE_UNKNOWN = -1,
        BRACE_PREDEFINED_OBJECT_TYPE_NOTOBJ = 0,
        BRACE_PREDEFINED_OBJECT_TYPE_NULL,
        BRACE_PREDEFINED_OBJECT_TYPE_NUM
    };

    class IBraceObject
    {
    public:
        virtual int GetObjectTypeId(void)const = 0;
    public:
        virtual ~IBraceObject(void) {}
    };

    template<int kObjTypeId>
    class BraceObjectBaseT : public IBraceObject
    {
    public:
        static const int ObjTypeId = kObjTypeId;
    public:
        virtual int GetObjectTypeId(void)const override { return ObjTypeId; }
    };

    struct DataTypeInfo
    {
        int Type;
        int ObjectTypeId;

        DataTypeInfo(void) = default;
        DataTypeInfo(int type, int objTypeId) :Type(type), ObjectTypeId(objTypeId)
        {}
    };
    struct RegisterInfo : public DataTypeInfo
    {
        int VarIndex;

        RegisterInfo(void) = default;
    };
    struct GlobalLocalRegisterInfo : public RegisterInfo
    {
        bool IsGlobal;

        GlobalLocalRegisterInfo(void) = default;
    };
    struct VarInfo final : public GlobalLocalRegisterInfo
    {
        std::string Name;

        VarInfo(void) :Name()
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = BRACE_PREDEFINED_OBJECT_TYPE_NOTOBJ;
            VarIndex = INVALID_INDEX;
            IsGlobal = false;
        }
        VarInfo(const std::string& name, int type, int objTypeId, int index) :Name(name)
        {
            Type = type;
            ObjectTypeId = objTypeId;
            VarIndex = index;
            IsGlobal = false;
        }
        VarInfo(const std::string& name, int type, int objTypeId, int index, bool isGlobal) :Name(name)
        {
            Type = type;
            ObjectTypeId = objTypeId;
            VarIndex = index;
            IsGlobal = isGlobal;
        }
    };
    struct ParamRetInfo final : public RegisterInfo
    {
        std::string Name;
        bool IsRef;

        ParamRetInfo(void) :Name(), IsRef(false)
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = BRACE_PREDEFINED_OBJECT_TYPE_NOTOBJ;
            VarIndex = INVALID_INDEX;
        }
        ParamRetInfo(const std::string& name, int type, int objTypeId, int index) :Name(name), IsRef(false)
        {
            Type = type;
            ObjectTypeId = BRACE_PREDEFINED_OBJECT_TYPE_NOTOBJ;
            VarIndex = index;
        }
        ParamRetInfo(const std::string& name, int type, int objTypeId, int index, bool isRef) :Name(name), IsRef(isRef)
        {
            Type = type;
            ObjectTypeId = objTypeId;
            VarIndex = index;
        }
    };
    struct ProcInfo;
    struct BraceApiLoadInfo final : public GlobalLocalRegisterInfo
    {
        bool IsTempVar;

        BraceApiLoadInfo(void) :IsTempVar(true)
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = BRACE_PREDEFINED_OBJECT_TYPE_NOTOBJ;
            VarIndex = INVALID_INDEX;
            IsGlobal = false;
        }

        DataTypeInfo GetLoadTimeRealType(const ProcInfo& proc) const;
    };
    struct VariableInfo;
    struct ReferenceInfo final : public RegisterInfo
    {
        VariableInfo* Vars;

        ReferenceInfo(void):Vars(nullptr)
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = BRACE_PREDEFINED_OBJECT_TYPE_NOTOBJ;
            VarIndex = INVALID_INDEX;
        }
        ReferenceInfo(int type, int index, VariableInfo* vars) :Vars(vars)
        {
            Type = type;
            ObjectTypeId = BRACE_PREDEFINED_OBJECT_TYPE_NOTOBJ;
            VarIndex = index;
        }
        ReferenceInfo(int type, int objTypeId, int index, VariableInfo* vars) :Vars(vars)
        {
            Type = type;
            ObjectTypeId = objTypeId;
            VarIndex = index;
        }
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
        std::vector<std::shared_ptr<IBraceObject>> ObjectVars;
        std::vector<ReferenceInfo> ReferenceVars;

        int AllocVariable(int type);
    };

    typedef void (*VarAssignPtr)(VariableInfo&, int, VariableInfo&, int);
    extern VarAssignPtr GetVarAssignPtr(int varType, bool isRef, int srcVarType, bool srcIsRef);
    extern const char* GetDataTypeName(int type);
    extern int GetDataType(const std::string& typeName);

    extern bool VarGetBoolean(VariableInfo& info, int type, int index);
    extern int64_t VarGetI64(VariableInfo& info, int type, int index);
    extern uint64_t VarGetU64(VariableInfo& info, int type, int index);
    extern double VarGetF64(VariableInfo& info, int type, int index);
    extern std::string VarGetStr(VariableInfo& info, int type, int index);
    extern void VarSetBoolean(VariableInfo& info, int type, int index, bool val);
    extern void VarSetI64(VariableInfo& info, int type, int index, int64_t val);
    extern void VarSetU64(VariableInfo& info, int type, int index, uint64_t val);
    extern void VarSetF64(VariableInfo& info, int type, int index, double val);
    extern void VarSetStr(VariableInfo& info, int type, int index, const std::string& val);
    extern void VarSetStr(VariableInfo& info, int type, int index, std::string&& val);

    static inline int GetMaxType(int type1, int type2)
    {
        return type1 < type2 ? type2 : type1;
    }
    static inline bool IsSignedType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_INT8:
        case BRACE_DATA_TYPE_INT16:
        case BRACE_DATA_TYPE_INT32:
        case BRACE_DATA_TYPE_INT64:
            return true;
        }
        return false;
    }
    static inline bool IsUnsignedType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_UINT8:
        case BRACE_DATA_TYPE_UINT16:
        case BRACE_DATA_TYPE_UINT32:
        case BRACE_DATA_TYPE_UINT64:
            return true;
        }
        return false;
    }

#define DEFINE_VAR_GET(POSTFIX, NAME, TYPE) \
    static inline TYPE VarGet##POSTFIX(VariableInfo& info, int index)\
    {\
        return info.NAME[index];\
    }

#define DEFINE_VAR_SET(POSTFIX, NAME, TYPE) \
    static inline void VarSet##POSTFIX(VariableInfo& info, int index, TYPE val)\
    {\
        info.NAME[index] = val;\
    }

    DEFINE_VAR_GET(Bool, BoolVars, bool);
    DEFINE_VAR_GET(Int8, Int8Vars, int8_t);
    DEFINE_VAR_GET(Int16, Int16Vars, int16_t);
    DEFINE_VAR_GET(Int32, Int32Vars, int32_t);
    DEFINE_VAR_GET(Int64, Int64Vars, int64_t);
    DEFINE_VAR_GET(Uint8, Uint8Vars, uint8_t);
    DEFINE_VAR_GET(Uint16, Uint16Vars, uint16_t);
    DEFINE_VAR_GET(Uint32, Uint32Vars, uint32_t);
    DEFINE_VAR_GET(Uint64, Uint64Vars, uint64_t);
    DEFINE_VAR_GET(Float, FloatVars, float);
    DEFINE_VAR_GET(Double, DoubleVars, double);
    DEFINE_VAR_GET(String, StringVars, const std::string&);
    DEFINE_VAR_GET(Object, ObjectVars, const std::shared_ptr<IBraceObject>&);
    DEFINE_VAR_GET(Ref, ReferenceVars, const ReferenceInfo&);

    DEFINE_VAR_SET(Bool, BoolVars, bool);
    DEFINE_VAR_SET(Int8, Int8Vars, int8_t);
    DEFINE_VAR_SET(Int16, Int16Vars, int16_t);
    DEFINE_VAR_SET(Int32, Int32Vars, int32_t);
    DEFINE_VAR_SET(Int64, Int64Vars, int64_t);
    DEFINE_VAR_SET(Uint8, Uint8Vars, uint8_t);
    DEFINE_VAR_SET(Uint16, Uint16Vars, uint16_t);
    DEFINE_VAR_SET(Uint32, Uint32Vars, uint32_t);
    DEFINE_VAR_SET(Uint64, Uint64Vars, uint64_t);
    DEFINE_VAR_SET(Float, FloatVars, float);
    DEFINE_VAR_SET(Double, DoubleVars, double);
    DEFINE_VAR_SET(String, StringVars, const std::string&);
    DEFINE_VAR_SET(Object, ObjectVars, const std::shared_ptr<IBraceObject>&);
    DEFINE_VAR_SET(Ref, ReferenceVars, const ReferenceInfo&);

    static inline void VarSetString(VariableInfo& info, int index, std::string&& val)
    {
        info.StringVars[index] = std::move(val);
    }
    static inline void VarSetObject(VariableInfo& info, int index, std::shared_ptr<IBraceObject>&& val)
    {
        info.ObjectVars[index] = std::move(val);
    }

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

    struct ProcInfo final
    {
        std::string Name;
        std::vector<ParamRetInfo> Params;
        ParamRetInfo RetValue;
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
        virtual bool LoadValue(ProcInfo& proc, const DslData::ValueData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadFunction(ProcInfo& proc, const DslData::FunctionData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadStatement(ProcInfo& proc, const DslData::StatementData& data, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadCall(ProcInfo& proc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>&& args, std::vector<BraceApiLoadInfo>&& argLoadInfos, BraceApiLoadInfo& loadInfo, BraceApiExecutor& executor)
        {
            return false;
        }
    protected:
        const char* GetTypeName(int type)const { return GetDataTypeName(type); }
        std::string GenTempVarName(void)const;
        ProcInfo* GetProcInfo(const std::string& name)const;
        VarInfo* GetGlobalVarInfo(const std::string& name)const;
        VarInfo* GetVarInfo(const std::string& name)const;
        VarInfo* GetConstInfo(const std::string& name)const;
        int GetObjectTypeId(const DslData::ISyntaxComponent& typeSyntax)const;
        const char* GetObjectTypeName(int objTypeId)const;
        bool CanAssign(int destType, int destObjTypeId, int srcType, int srcObjTypeId)const;
        ProcInfo* PushNewProcInfo(const std::string& name)const;
        void PopProcInfo(void)const;
        int GenNextUniqueId(void)const;
        int CurBlockId(void)const;
        std::vector<int>& CurBlockObjVars(void)const;
        void PushBlock(void)const;
        void PopBlock(void)const;
        int AllocGlobalVariable(const std::string& name, int type)const;
        int AllocGlobalVariable(const std::string& name, int type, int objTypeId)const;
        int AllocVariable(const std::string& name, int type)const;
        int AllocVariable(const std::string& name, int type, int objTypeId)const;
        int AllocConst(int tok_type, const std::string& value, int& type)const;
        void LogInfo(const std::string& msg)const;
        void LogWarn(const std::string& msg)const;
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
        ProcInfo* CurProcInfo(void)const;
    private:
        AbstractBraceApi(const AbstractBraceApi&) = delete;
        AbstractBraceApi& operator=(const AbstractBraceApi&) = delete;
        AbstractBraceApi(AbstractBraceApi&&) noexcept = delete;
        AbstractBraceApi& operator=(AbstractBraceApi&&) noexcept = delete;
    private:
        BraceScript& GetInterpreter(void)const { return m_Interpreter; }
    private:
        BraceScript& m_Interpreter;
    protected:
        static void FreeObjVars(VariableInfo& vars, const std::vector<int>& objVars);
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
    typedef std::function<int(const DslData::ISyntaxComponent&)> GetObjectTypeIdDelegation;
    typedef std::function<const char* (int)> GetObjectTypeNameDelegation;
    typedef std::function<bool(int,int)> ObjectAssignCheckDelegation;
    class BraceScript final
    {
        friend class AbstractBraceApi;
        struct BlockInfo final
        {
            int BlockId;
            std::vector<int> ObjVars;

            BlockInfo(int blockId) :BlockId(blockId), ObjVars()
            {}
        };
    public:
        BraceScript(void);
        ~BraceScript(void);
    public:
        LogDelegation OnInfo;
        LogDelegation OnWarn;
        LogDelegation OnError;
        GetObjectTypeIdDelegation OnGetObjectTypeId;
        GetObjectTypeNameDelegation OnGetObjectTypeName;
        ObjectAssignCheckDelegation OnObjectAssignCheck;
    public:
        /// Because we didn't implement Object internally, we kept these apis, but we had to implement them externally
        /// See ExternaAPiRef.txt
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
        /// -----------------------------------------------------------------------------------------------------------
        void RegisterApi(const std::string& id, IBraceApiFactory* pApiFactory);
        void RegisterApi(std::string&& id, IBraceApiFactory* pApiFactory);
        void Reset(void);
        void LoadScript(const DslData::DslFile& file);
        void Run(void);
        bool HasWarn(void)const { return m_HasWarn; }
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
        void LogWarn(const std::string& warn);
        void LogError(const std::string& error);
        void AddSyntaxComponent(DslData::ISyntaxComponent* p);
        void AddApiInstance(IBraceApi* p);
        int GetObjectTypeId(const DslData::ISyntaxComponent& typeSyntax)const;
        const char* GetObjectTypeName(int objTypeId)const;
        bool CanAssign(int destType, int destObjTypeId, int srcType, int srcObjTypeId) const;
        const ProcInfo* GetProcInfo(const std::string& name)const;
        ProcInfo* GetProcInfo(const std::string& name);
        const ProcInfo* CurProcInfo(void)const;
        ProcInfo* CurProcInfo(void);
        ProcInfo* PushNewProcInfo(const std::string& name);
        void PopProcInfo(void);
        int GenNextUniqueId(void) { return m_NextUniqueId++; }
        int CurBlockId(void)const;
        const std::vector<int>& CurBlockObjVars(void)const;
        std::vector<int>& CurBlockObjVars(void);
        void PushBlock(void);
        void PopBlock(void);
        std::string CalcVarKey(const std::string& name, int level)const;
        std::string CalcConstKey(const std::string& name)const;
        int AllocGlobalVariable(const std::string& name, int type);
        int AllocGlobalVariable(const std::string& name, int type, int objTypeId);
        auto FindVariable(ProcInfo* proc, const std::string& name, std::string& key, int& level)const -> decltype(proc->VarTypeInfos.end());
        int AllocVariable(const std::string& name, int type);
        int AllocVariable(const std::string& name, int type, int objTypeId);
        int AllocConst(int tok_type, const std::string& value, int& type);
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

        bool m_HasWarn;
        bool m_HasError;
        ProcInfoStack m_ProcInfoStack;
        int m_NextUniqueId;
        int m_NextBlockId;
        std::vector<BlockInfo> m_LexicalScopeStack;
        ProcInfo* m_GlobalProc;
        VariableInfo* m_GlobalVariables;
        RuntimeStack m_RuntimeStack;
    };
}