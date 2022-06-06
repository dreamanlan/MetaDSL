
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
        BRACE_PREDEFINED_OBJECT_TYPE_CONTEXT,
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
    struct VariableInfo;
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
        DataTypeInfo GetLoadTimeRealType(const VariableInfo& vars) const;
    };
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

    union NumericValue final
    {
        bool BoolVal;
        int8_t Int8Val;
        int16_t Int16Val;
        int32_t Int32Val;
        int64_t Int64Val;
        uint8_t UInt8Val;
        uint16_t UInt16Val;
        uint32_t UInt32Val;
        uint64_t UInt64Val;
        float FloatVal;
        double DoubleVal;
    };
    struct VariableInfo final
    {
        std::vector<NumericValue> NumericVars;
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
    static inline bool IsFloatType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_FLOAT:
        case BRACE_DATA_TYPE_DOUBLE:
            return true;
        }
        return false;
    }
    static inline bool IsBoolType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            return true;
        }
        return false;
    }
    static inline bool IsStringType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_STRING:
            return true;
        }
        return false;
    }

#define DEFINE_VAR_GET_NUMERIC(POSTFIX, NAME, TYPE) \
    static inline TYPE VarGet##POSTFIX(VariableInfo& info, int index)\
    {\
        return info.NumericVars[index].NAME;\
    }

#define DEFINE_VAR_SET_NUMERIC(POSTFIX, NAME, TYPE) \
    static inline void VarSet##POSTFIX(VariableInfo& info, int index, TYPE val)\
    {\
        info.NumericVars[index].NAME = val;\
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

    DEFINE_VAR_GET_NUMERIC(Bool, BoolVal, bool);
    DEFINE_VAR_GET_NUMERIC(Int8, Int8Val, int8_t);
    DEFINE_VAR_GET_NUMERIC(Int16, Int16Val, int16_t);
    DEFINE_VAR_GET_NUMERIC(Int32, Int32Val, int32_t);
    DEFINE_VAR_GET_NUMERIC(Int64, Int64Val, int64_t);
    DEFINE_VAR_GET_NUMERIC(UInt8, UInt8Val, uint8_t);
    DEFINE_VAR_GET_NUMERIC(UInt16, UInt16Val, uint16_t);
    DEFINE_VAR_GET_NUMERIC(UInt32, UInt32Val, uint32_t);
    DEFINE_VAR_GET_NUMERIC(UInt64, UInt64Val, uint64_t);
    DEFINE_VAR_GET_NUMERIC(Float, FloatVal, float);
    DEFINE_VAR_GET_NUMERIC(Double, DoubleVal, double);
    DEFINE_VAR_GET(String, StringVars, const std::string&);
    DEFINE_VAR_GET(Object, ObjectVars, const std::shared_ptr<IBraceObject>&);
    DEFINE_VAR_GET(Ref, ReferenceVars, const ReferenceInfo&);

    DEFINE_VAR_SET_NUMERIC(Bool, BoolVal, bool);
    DEFINE_VAR_SET_NUMERIC(Int8, Int8Val, int8_t);
    DEFINE_VAR_SET_NUMERIC(Int16, Int16Val, int16_t);
    DEFINE_VAR_SET_NUMERIC(Int32, Int32Val, int32_t);
    DEFINE_VAR_SET_NUMERIC(Int64, Int64Val, int64_t);
    DEFINE_VAR_SET_NUMERIC(UInt8, UInt8Val, uint8_t);
    DEFINE_VAR_SET_NUMERIC(UInt16, UInt16Val, uint16_t);
    DEFINE_VAR_SET_NUMERIC(UInt32, UInt32Val, uint32_t);
    DEFINE_VAR_SET_NUMERIC(UInt64, UInt64Val, uint64_t);
    DEFINE_VAR_SET_NUMERIC(Float, FloatVal, float);
    DEFINE_VAR_SET_NUMERIC(Double, DoubleVal, double);
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
    using BraceApiExecutor = Delegation<int(void)>;
    class IBraceApi
    {
    public:
        virtual bool Load(const DslData::ISyntaxComponent& syntax, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) = 0;
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
        friend class FunctionExecutor;
    public:
        virtual bool Load(const DslData::ISyntaxComponent& syntax, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override;
    protected:
        virtual bool LoadValue(const ProcInfo& curProc, const DslData::ValueData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadFunction(const ProcInfo& curProc, const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadStatement(const ProcInfo& curProc, const DslData::StatementData& data, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadHighOrderCall(const ProcInfo& curProc, const DslData::FunctionData& data, BraceApiExecutor& lowerFunc, BraceApiLoadInfo& lowerFuncInfo)
        {
            return false;
        }
        virtual bool LoadCall(const ProcInfo& curProc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor)
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
        BraceApiExecutor LoadHelper(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& resultInfo)const;
    protected:
        ProcInfo* GlobalProcInfo(void)const;
        VariableInfo* GlobalVariables(void)const;
        const ProcInfo* CurRuntimeProcInfo(void)const;
        VariableInfo* CurRuntimeVariables(void)const;
        void PushRuntimeStack(const ProcInfo* procInfo)const;
        void PopRuntimeStack(void)const;
    protected:
        AbstractBraceApi(BraceScript& interpreter) :m_Interpreter(interpreter)
        {}
    private:
        ProcInfo* CurProcInfo(void)const;
        AbstractBraceApi* GetFailbackApi(void)const;
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

    class FunctionExecutor final : public AbstractBraceApi
    {
    public:
        FunctionExecutor(BraceScript& interpreter);
    public:
        void Reset(void);
        void Build(const std::string& func) { Build(*CurProcInfo(), func); }
        void Build(const ProcInfo& callerProc, const std::string& func);
        bool IsValid(void)const;
        int Run(void)const;
        int GetArgCount(void)const;
        const BraceApiLoadInfo* ArgInfo(int ix) const;
        const BraceApiLoadInfo* ResultInfo(void) const;
    protected:
        virtual bool LoadCall(const ProcInfo& curProc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override;
    private:
        int Execute(void)const;
    private:
        const ProcInfo* m_Func;
        std::vector<BraceApiExecutor> m_Args;
        std::vector<BraceApiLoadInfo> m_ArgLoadInfos;
        std::vector<VarAssignPtr> m_ArgAssigns;
        BraceApiLoadInfo m_ResultInfo;
        VarAssignPtr m_ResultAssign;

        BraceApiExecutor m_CodeExecutor;
    };

    class UnaryOperatorBaseExp : public AbstractBraceApi
    {
    public:
        UnaryOperatorBaseExp(BraceScript& interpreter, bool isAssignment);
    protected:
        virtual bool LoadCall(const ProcInfo& curProc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override;
    protected:
        virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const = 0;
    protected:
        bool m_IsAssignment;
        BraceApiExecutor m_Op1;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_ResultInfo;
    };
    class BinaryOperatorBaseExp : public AbstractBraceApi
    {
    public:
        BinaryOperatorBaseExp(BraceScript& interpreter, bool isAssignment);
    protected:
        virtual bool LoadCall(const ProcInfo& curProc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override;
    protected:
        virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const = 0;
    protected:
        bool m_IsAssignment;
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        BraceApiLoadInfo m_LoadInfo1;
        BraceApiLoadInfo m_LoadInfo2;
        BraceApiLoadInfo m_ResultInfo;
    };

    /// <summary>
    /// Convenient but not efficient
    /// </summary>
    class SimpleBraceApiBase : public AbstractBraceApi
    {
    public:
        SimpleBraceApiBase(BraceScript& interpreter);
    protected:
        virtual bool LoadCall(const ProcInfo& proc, const DslData::FunctionData& data, std::vector<BraceApiExecutor>& args, std::vector<BraceApiLoadInfo>& argLoadInfos, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor) override;
    protected:
        virtual bool TypeInference(const ProcInfo& proc, const DslData::FunctionData& data, const std::vector<BraceApiLoadInfo>& argInfos, BraceApiLoadInfo& resultInfo)const
        {
            resultInfo = Brace::BraceApiLoadInfo();
            return true;
        }
        virtual void Execute(VariableInfo& gvars, VariableInfo& lvars, const std::vector<BraceApiLoadInfo>& argInfos, const BraceApiLoadInfo& resultInfo)const = 0;
    private:
        int ExecuteImpl(void)const;
    private:
        std::vector<Brace::BraceApiExecutor> m_Args;
        std::vector<Brace::BraceApiLoadInfo> m_ArgLoadInfos;
        Brace::BraceApiLoadInfo m_ResultInfo;
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
    template<typename ApiT, typename... Args>
    class CtorBinder
    {};
    template<typename ApiT, typename A1>
    class CtorBinder<ApiT, A1>
    {
    public:
        CtorBinder(A1 a1) :m_A1(a1)
        {}
        IBraceApi* ctor(BraceScript& interpreter)
        {
            return new ApiT(interpreter, m_A1);
        }
    private:
        A1 m_A1;
    };
    template<typename ApiT, typename A1, typename A2>
    class CtorBinder<ApiT, A1, A2>
    {
    public:
        CtorBinder(A1 a1, A2 a2) :m_A1(a1), m_A2(a2)
        {}
        IBraceApi* ctor(BraceScript& interpreter)
        {
            return new ApiT(interpreter, m_A1, m_A2);
        }
    private:
        A1 m_A1;
        A2 m_A2;
    };
    template<typename ApiT, typename A1, typename A2, typename A3>
    class CtorBinder<ApiT, A1, A2, A3>
    {
    public:
        CtorBinder(A1 a1, A2 a2, A3 a3) :m_A1(a1), m_A2(a2), m_A3(a3)
        {}
        IBraceApi* ctor(BraceScript& interpreter)
        {
            return new ApiT(interpreter, m_A1, m_A2, m_A3);
        }
    private:
        A1 m_A1;
        A2 m_A2;
        A3 m_A3;
    };
    template<typename ApiT, typename... Args>
    class BraceApiFactoryWithArgs final : public IBraceApiFactory
    {
    public:
        BraceApiFactoryWithArgs(Args... args) :m_Binder(args...)
        {}
        virtual IBraceApi* Create(BraceScript& interpreter) override
        {
            return m_Binder.ctor(interpreter);
        }
    private:
        CtorBinder<ApiT, Args...> m_Binder;
    };

    typedef std::stack<ProcInfo*> ProcInfoStack;
    typedef std::stack<RuntimeStackInfo> RuntimeStack;
    typedef std::function<void(const std::string&)> LogDelegation;
    typedef std::function<int(const DslData::ISyntaxComponent&)> GetObjectTypeIdDelegation;
    typedef std::function<const char* (int)> GetObjectTypeNameDelegation;
    typedef std::function<bool(int,int)> ObjectAssignCheckDelegation;
    typedef std::function<bool(const DslData::ISyntaxComponent&, BraceApiLoadInfo&, BraceApiExecutor&)> FilterLoadDelegation;
    typedef std::function<bool(const DslData::ValueData&, BraceApiLoadInfo&, BraceApiExecutor&)> LoadValueFailedDelegation;
    typedef std::function<bool(const DslData::FunctionData&, BraceApiLoadInfo&, BraceApiExecutor&)> LoadFunctionFailedDelegation;
    typedef std::function<bool(const DslData::StatementData&, BraceApiLoadInfo&, BraceApiExecutor&)> LoadStatementFailedDelegation;
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
        FilterLoadDelegation OnFilterLoad;
        LoadValueFailedDelegation OnLoadValueFailed;
        LoadFunctionFailedDelegation OnLoadFunctionFailed;
        LoadStatementFailedDelegation OnLoadStatementFailed;
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
        void SetFailbackApi(AbstractBraceApi* pFailbackApi);
        AbstractBraceApi* GetFailbackApi(void)const;
        void SetContextObject(IBraceObject* pContext);
        IBraceObject* GetContextObject(void)const;
        void Reset(void);
        void LoadScript(const DslData::DslFile& file);
        void Run(void);
        ProcInfo* GlobalProcInfo(void)const;
        VariableInfo* GlobalVariables(void)const;
        bool HasWarn(void)const { return m_HasWarn; }
        bool HasError(void)const { return m_HasError; }
    public:
        void AddSyntaxComponent(DslData::ISyntaxComponent* p);
        void AddApiInstance(IBraceApi* p); 
        IBraceApi* CreateApi(const std::string& name);
    private:
        const ProcInfo* CurRuntimeProcInfo(void)const;
        VariableInfo* CurRuntimeVariables(void)const;
        void PushRuntimeStack(const ProcInfo* procInfo);
        void PopRuntimeStack(void);
    private:
        void LogInfo(const std::string& info);
        void LogWarn(const std::string& warn);
        void LogError(const std::string& error);
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
        BraceApiExecutor Load(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& resultInfo);
    private:
        BraceApiExecutor LoadValue(const DslData::ValueData& data, BraceApiLoadInfo& resultInfo);
        BraceApiExecutor LoadFunction(const DslData::FunctionData& data, BraceApiLoadInfo& resultInfo);
        BraceApiExecutor LoadStatement(const DslData::StatementData& data, BraceApiLoadInfo& resultInfo);
        bool DoFilterLoad(const DslData::ISyntaxComponent& syntaxUnit, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor);
        bool DoLoadValueFailed(const DslData::ValueData& syntaxUnit, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor);
        bool DoLoadFunctionFailed(const DslData::FunctionData& syntaxUnit, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor);
        bool DoLoadStatementFailed(const DslData::StatementData& syntaxUnit, BraceApiLoadInfo& resultInfo, BraceApiExecutor& executor);
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
        int m_LastBlockId;
        std::vector<BlockInfo> m_LexicalScopeStack;
        ProcInfo* m_GlobalProc;
        VariableInfo* m_GlobalVariables;
        RuntimeStack m_RuntimeStack;

        AbstractBraceApi* m_FailbackApi;
        IBraceObject* m_ContextObject;
    };
}