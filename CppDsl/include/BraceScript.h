
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
    enum PredefinedBraceObjectTypeIdEnum
    {
        PREDEFINED_BRACE_OBJECT_TYPE_UNKNOWN = -1,
        PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ = 0,
        PREDEFINED_BRACE_OBJECT_TYPE_NULL,
        PREDEFINED_BRACE_OBJECT_TYPE_ANY,
        PREDEFINED_BRACE_OBJECT_TYPE_NUM
    };

    struct DataTypeInfo
    {
        int Type;
        int ObjectTypeId;

        DataTypeInfo(void) :Type(BRACE_DATA_TYPE_UNKNOWN), ObjectTypeId(PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ) {}
        DataTypeInfo(int type, int objTypeId) :Type(type), ObjectTypeId(objTypeId)
        {}

        static inline bool IsSameType(const DataTypeInfo& a, const DataTypeInfo& b)
        {
            return a.Type == b.Type && a.ObjectTypeId == b.ObjectTypeId;
        }
    };
    struct RegisterInfo : public DataTypeInfo
    {
        int VarIndex;

        RegisterInfo(void) :VarIndex(INVALID_INDEX) {}
    };
    struct ParamTypeInfo final : public DataTypeInfo
    {
        bool IsRef;

        ParamTypeInfo(void) :IsRef(false)
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
        }
        ParamTypeInfo(int type, int objTypeId, bool isRef) :DataTypeInfo(type, objTypeId), IsRef(isRef)
        {}
    };
    struct OperandTypeInfo final : public DataTypeInfo
    {
        bool IsGlobal;

        OperandTypeInfo(void) :IsGlobal(false)
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
        }
        OperandTypeInfo(int type, int objTypeId, bool isGlobal) :DataTypeInfo(type, objTypeId), IsGlobal(isGlobal)
        {}
    };
    struct VarInfo final : public RegisterInfo
    {
        std::string Name;

        VarInfo(void) :Name()
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            VarIndex = INVALID_INDEX;
        }
        VarInfo(const std::string& name, int type, int objTypeId, int index) :Name(name)
        {
            Type = type;
            ObjectTypeId = objTypeId;
            VarIndex = index;
        }
    };
    struct ParamRetInfo final : public RegisterInfo
    {
        bool IsRef;
        std::string Name;

        ParamRetInfo(void) :IsRef(false), Name()
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            VarIndex = INVALID_INDEX;
        }
        ParamRetInfo(const std::string& name, int type, int objTypeId, int index) :IsRef(false), Name(name)
        {
            Type = type;
            ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            VarIndex = index;
        }
        ParamRetInfo(const std::string& name, int type, int objTypeId, int index, bool isRef) :IsRef(isRef), Name(name)
        {
            Type = type;
            ObjectTypeId = objTypeId;
            VarIndex = index;
        }
    };
    struct VariableInfo;
    struct FuncInfo;
    struct OperandLoadtimeInfo final : public RegisterInfo
    {
        bool IsGlobal;
        bool IsTempVar;
        bool IsConst;
        std::string Name;

        OperandLoadtimeInfo(void) :IsGlobal(false), IsTempVar(true), IsConst(false), Name()
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            VarIndex = INVALID_INDEX;
        }

        OperandTypeInfo GetLoadTimeRealType(const FuncInfo& func) const;
        OperandTypeInfo GetLoadTimeRealType(const VariableInfo& vars) const;

        static inline bool IsSameVar(const OperandLoadtimeInfo& a, const OperandLoadtimeInfo& b)
        {
            return a.Type == b.Type && a.ObjectTypeId == b.ObjectTypeId && a.VarIndex == b.VarIndex && a.IsGlobal == b.IsGlobal;
        }
    };
    struct OperandRuntimeInfo final
    {
        int8_t Type;
        int8_t IsGlobal;
        int16_t VarIndex;
        int32_t ObjectTypeId;

        OperandRuntimeInfo(void):Type(BRACE_DATA_TYPE_UNKNOWN), IsGlobal(false), VarIndex(INVALID_INDEX), ObjectTypeId(PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ)
        {}
        OperandRuntimeInfo(int type, int objTypeId, int varIndex, bool isGlobal) :Type(type), IsGlobal(isGlobal ? 1 : 0), VarIndex(varIndex), ObjectTypeId(objTypeId)
        {}
        OperandRuntimeInfo(const OperandLoadtimeInfo& loadInfo):Type(loadInfo.Type), IsGlobal(loadInfo.IsGlobal ? 1 : 0), VarIndex(loadInfo.VarIndex), ObjectTypeId(loadInfo.ObjectTypeId)
        {}
        OperandRuntimeInfo& operator=(const OperandLoadtimeInfo& loadInfo)
        {
            Type = loadInfo.Type;
            IsGlobal = loadInfo.IsGlobal ? 1 : 0;
            VarIndex = loadInfo.VarIndex;
            ObjectTypeId = loadInfo.ObjectTypeId;
            return *this;
        }
    };
    struct ReferenceInfo final : public RegisterInfo
    {
        VariableInfo* Vars;

        ReferenceInfo(void):Vars(nullptr)
        {
            Type = BRACE_DATA_TYPE_UNKNOWN;
            ObjectTypeId = PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
            VarIndex = INVALID_INDEX;
        }
        ReferenceInfo(int type, int objTypeId, int index, VariableInfo* vars) :Vars(vars)
        {
            Type = type;
            ObjectTypeId = objTypeId;
            VarIndex = index;
        }
        static ReferenceInfo BuildFromRuntimeInfo(const OperandRuntimeInfo& runtimeInfo, VariableInfo* vars);
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
        std::vector<std::shared_ptr<void>> ObjectVars;
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

    static inline constexpr int GetDataTypeSize(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            return 1;
        case BRACE_DATA_TYPE_INT8:
        case BRACE_DATA_TYPE_UINT8:
            return 1;
        case BRACE_DATA_TYPE_INT16:
        case BRACE_DATA_TYPE_UINT16:
            return 2;
        case BRACE_DATA_TYPE_INT32:
        case BRACE_DATA_TYPE_UINT32:
        case BRACE_DATA_TYPE_FLOAT:
            return 4;
        case BRACE_DATA_TYPE_INT64:
        case BRACE_DATA_TYPE_UINT64:
        case BRACE_DATA_TYPE_DOUBLE:
            return 8;
        case BRACE_DATA_TYPE_OBJECT:
        case BRACE_DATA_TYPE_REF:
            return static_cast<int>(sizeof(void*));
        case BRACE_DATA_TYPE_STRING:
            return 0;
        default:
            return 0;
        }
    }
    static inline constexpr int GetMaxType(int type1, int type2)
    {
        return type1 < type2 ? type2 : type1;
    }
    static inline constexpr bool IsUnknownType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_UNKNOWN:
            return true;
        }
        return false;
    }
    static inline constexpr bool IsSignedType(int type)
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
    static inline constexpr bool IsUnsignedType(int type)
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
    static inline constexpr bool IsFloatType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_FLOAT:
        case BRACE_DATA_TYPE_DOUBLE:
            return true;
        }
        return false;
    }
    static inline constexpr bool IsBoolType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            return true;
        }
        return false;
    }
    static inline constexpr bool IsStringType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_STRING:
            return true;
        }
        return false;
    }
    static inline constexpr bool IsObjectType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_OBJECT:
            return true;
        }
        return false;
    }
    static inline constexpr bool IsReferenceType(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_REF:
            return true;
        }
        return false;
    }

    static inline constexpr bool IsUnknownObject(int objTypeId)
    {
        return objTypeId == PREDEFINED_BRACE_OBJECT_TYPE_UNKNOWN;
    }
    static inline constexpr bool IsNotObject(int objTypeId)
    {
        return objTypeId == PREDEFINED_BRACE_OBJECT_TYPE_NOTOBJ;
    }
    static inline constexpr bool IsNullObject(int objTypeId)
    {
        return objTypeId == PREDEFINED_BRACE_OBJECT_TYPE_NULL;
    }
    static inline constexpr bool IsAnyObject(int objTypeId)
    {
        return objTypeId == PREDEFINED_BRACE_OBJECT_TYPE_ANY;
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
    DEFINE_VAR_GET(String, StringVars, std::string&);
    DEFINE_VAR_GET(Object, ObjectVars, std::shared_ptr<void>&);
    DEFINE_VAR_GET(Ref, ReferenceVars, ReferenceInfo&);

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
    DEFINE_VAR_SET(Object, ObjectVars, const std::shared_ptr<void>&);
    DEFINE_VAR_SET(Ref, ReferenceVars, const ReferenceInfo&);

    static inline void VarSetString(VariableInfo& info, int index, std::string&& val)
    {
        info.StringVars[index] = std::move(val);
    }
    static inline void VarSetObject(VariableInfo& info, int index, std::shared_ptr<void>&& val)
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
    using BraceApiExecutor = Delegation<int(VariableInfo&,VariableInfo&)>;
    class IBraceApi
    {
    public:
        virtual bool Load(const DslData::ISyntaxComponent& syntax, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor) = 0;
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

    struct FuncApiTypeInfo final
    {
        std::vector<ParamTypeInfo> Params;
        DataTypeInfo RetValue;
    };
    struct Instruction final
    {
        uint64_t Opcode : 7;
        uint64_t ResultIsGlobal : 1;
        uint64_t ResultType : 4;
        uint64_t FirstIsGlobal : 1;
        uint64_t FirstType : 4;
        uint64_t SecondIsGlobal : 1;
        uint64_t SecondType : 4;
        uint64_t ResultVarIndex : 14;
        uint64_t FirstVarIndex : 14;
        uint64_t SecondVarIndex : 14;
    };
    struct FuncInfo final
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

        FuncInfo(void);
        FuncInfo(const FuncInfo& other);
        FuncInfo(FuncInfo&& other) noexcept;
        ~FuncInfo(void);
    private:
        /// Members of FuncInfo are immutable at run time, except for VaraibleInfoPool & VariableInfoStore, which uses Pointers 
        /// to preserve the const semantics of FuncInfo. 
        /// Stack operations are used to use recently used memory for better locality, while deques are used to shrink memory.
        std::deque<VariableInfo*>* VariableInfoPool;
        std::vector<VariableInfo*>* VariableInfoStore;
    };

    struct RuntimeStackInfo final
    {
        const FuncInfo* Func;
        VariableInfo* Variables;
    };

    class IBraceApiFactory
    {
    public:
        virtual IBraceApi* Create(BraceScript& interpreter) = 0;
    public:
        virtual ~IBraceApiFactory(void) {}
    };

    class AbstractBraceApi;
    class BraceApiImplHelper
    {
    public:
        virtual ~BraceApiImplHelper(void) {}
    protected:
        const char* GetTypeName(int type)const { return GetDataTypeName(type); }
        std::string GenTempVarName(void)const;
        FuncApiTypeInfo* GetFuncApiTypeInfo(const std::string& name)const;
        FuncInfo* GetFuncInfo(const std::string& name)const;
        VarInfo* GetGlobalVarInfo(const std::string& name)const;
        VarInfo* GetVarInfo(const std::string& name)const;
        VarInfo* GetConstInfo(int tok_type, const std::string& name)const;
        int GetObjectTypeId(const DslData::ISyntaxComponent& typeSyntax)const;
        const char* GetObjectTypeName(int objTypeId)const;
        ParamTypeInfo ParseParamTypeInfo(const DslData::ISyntaxComponent& syntax)const;
        bool CanAssign(int destType, int destObjTypeId, int srcType, int srcObjTypeId)const;
        FuncInfo* PushFuncInfo(const std::string& name)const;
        void PopFuncInfo(void)const;
        int GenNextUniqueId(void)const;
        int CurBlockId(void)const;
        std::vector<int>& CurBlockObjVars(void)const;
        std::vector<Instruction>& CurBasicBlock(void)const;
        void PushBlock(void)const;
        void PopBlock(void)const;
        int AllocGlobalVariable(const std::string& name, int type, int objTypeId)const;
        int AllocVariable(const std::string& name, int type, int objTypeId)const;
        int AllocConst(int tok_type, const std::string& value, int& type, int& objTypeId)const;
        void LogInfo(const std::string& msg)const;
        void LogWarn(const std::string& msg)const;
        void LogError(const std::string& msg)const;
        void AddSyntaxComponent(DslData::ISyntaxComponent* p)const;
        void AddApiInstance(IBraceApi* p)const;
        BraceApiExecutor LoadHelper(const DslData::ISyntaxComponent& syntaxUnit, OperandLoadtimeInfo& resultInfo)const;
    protected:
        bool IsForceQuit(void)const;
        FuncInfo* GlobalFuncInfo(void)const;
        VariableInfo* GlobalVariables(void)const;
        const FuncInfo* CurRuntimeFuncInfo(void)const;
        VariableInfo* CurRuntimeVariables(void)const;
        void PushRuntimeStack(const FuncInfo* funcInfo)const;
        void PopRuntimeStack(void)const;
    protected:
        FuncInfo* CurFuncInfo(void)const;
        AbstractBraceApi* GetFailbackApi(void)const;
        const std::shared_ptr<void>& GetContextObject(void)const;
    protected:
        BraceApiImplHelper(BraceScript& interpreter) :m_Interpreter(interpreter)
        {}
        BraceScript& GetInterpreter(void)const { return m_Interpreter; }
    private:
        BraceApiImplHelper(const BraceApiImplHelper&) = delete;
        BraceApiImplHelper& operator=(const BraceApiImplHelper&) = delete;
        BraceApiImplHelper(BraceApiImplHelper&&) noexcept = delete;
        BraceApiImplHelper& operator=(BraceApiImplHelper&&) noexcept = delete;
    private:
        BraceScript& m_Interpreter;
    protected:
        static void FreeObjVars(VariableInfo& vars, const std::vector<int>& objVars);
    };

    class AbstractBraceApi : public IBraceApi, public BraceApiImplHelper
    {
        friend class FunctionExecutor;
    public:
        virtual bool Load(const DslData::ISyntaxComponent& syntax, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor) override;
    protected:
        virtual bool LoadValue(const FuncInfo& curFunc, const DslData::ValueData& data, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadFunction(const FuncInfo& curFunc, const DslData::FunctionData& data, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        virtual bool LoadStatement(const FuncInfo& curFunc, const DslData::StatementData& data, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor)
        {
            return false;
        }
        //ArgLoadInfos and ARgs that use non-const references are used to support operations such as std::swap or rvalue reference and to allow passes to failback without modification 
        virtual bool LoadCall(const FuncInfo& curFunc, const DslData::FunctionData& data, std::vector<OperandLoadtimeInfo>& argLoadInfos, std::vector<BraceApiExecutor>& args, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor)
        {
            return false;
        }
    protected:
        AbstractBraceApi(BraceScript& interpreter) :BraceApiImplHelper(interpreter)
        {}
    private:
        AbstractBraceApi(const AbstractBraceApi&) = delete;
        AbstractBraceApi& operator=(const AbstractBraceApi&) = delete;
        AbstractBraceApi(AbstractBraceApi&&) noexcept = delete;
        AbstractBraceApi& operator=(AbstractBraceApi&&) noexcept = delete;
    };

    class FunctionExecutor final : public AbstractBraceApi
    {
    public:
        FunctionExecutor(BraceScript& interpreter);
    public:
        void Reset(void);
        void Build(const std::string& func) { Build(*CurFuncInfo(), func); }
        void Build(const FuncInfo& callerFunc, const std::string& func);
        bool IsValid(void)const;
        int Run(VariableInfo& gvars, VariableInfo& lvars)const;
        int GetArgCount(void)const;
        const OperandRuntimeInfo* ArgInfo(int ix) const;
        const OperandRuntimeInfo* ResultInfo(void) const;
    protected:
        virtual bool LoadCall(const FuncInfo& curFunc, const DslData::FunctionData& data, std::vector<OperandLoadtimeInfo>& argLoadInfos, std::vector<BraceApiExecutor>& args, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor) override;
    private:
        int Execute(VariableInfo& gvars, VariableInfo& lvars)const;
    private:
        const FuncInfo* m_Func;
        std::vector<BraceApiExecutor> m_Args;
        std::vector<OperandRuntimeInfo> m_ArgInfos;
        std::vector<VarAssignPtr> m_ArgAssigns;
        OperandRuntimeInfo m_ResultInfo;
        VarAssignPtr m_ResultAssign;

        BraceApiExecutor m_CodeExecutor;
    };

    class UnaryOperatorBaseExp : public AbstractBraceApi
    {
    public:
        UnaryOperatorBaseExp(BraceScript& interpreter, bool isAssignment);
    protected:
        virtual bool LoadCall(const FuncInfo& curFunc, const DslData::FunctionData& data, std::vector<OperandLoadtimeInfo>& argLoadInfos, std::vector<BraceApiExecutor>& args, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor) override;
    protected:
        virtual bool BuildExecutor(const DslData::FunctionData& data, bool argIsRef, const OperandTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const = 0;
    protected:
        bool m_IsAssignment;
        BraceApiExecutor m_Op1;
        OperandRuntimeInfo m_ArgInfo1;
        OperandRuntimeInfo m_ResultInfo;
    };
    class BinaryOperatorBaseExp : public AbstractBraceApi
    {
    public:
        BinaryOperatorBaseExp(BraceScript& interpreter, bool isAssignment);
    protected:
        virtual bool LoadCall(const FuncInfo& curFunc, const DslData::FunctionData& data, std::vector<OperandLoadtimeInfo>& argLoadInfos, std::vector<BraceApiExecutor>& args, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor) override;
    protected:
        virtual bool BuildExecutor(const DslData::FunctionData& data, bool arg1IsRef, bool arg2IsRef, const OperandTypeInfo& load1, const OperandTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const = 0;
    protected:
        bool m_IsAssignment;
        BraceApiExecutor m_Op1;
        BraceApiExecutor m_Op2;
        OperandRuntimeInfo m_ArgInfo1;
        OperandRuntimeInfo m_ArgInfo2;
        OperandRuntimeInfo m_ResultInfo;
    };

    /// <summary>
    /// Convenient but not efficient
    /// </summary>
    class SimpleBraceApiBase : public AbstractBraceApi
    {
    public:
        SimpleBraceApiBase(BraceScript& interpreter);
    protected:
        virtual bool LoadCall(const FuncInfo& func, const DslData::FunctionData& data, std::vector<OperandLoadtimeInfo>& argLoadInfos, std::vector<BraceApiExecutor>& args, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor) override;
    protected:
        virtual bool TypeInference(const FuncInfo& func, const DslData::FunctionData& data, const std::vector<OperandLoadtimeInfo>& argInfos, OperandLoadtimeInfo& resultInfo);
        virtual void Execute(VariableInfo& gvars, VariableInfo& lvars, const std::vector<OperandRuntimeInfo>& argInfos, const OperandRuntimeInfo& resultInfo)const = 0;
    private:
        int ExecuteImpl(VariableInfo& gvars, VariableInfo& lvars)const;
    private:
        std::vector<Brace::BraceApiExecutor> m_Args;
        std::vector<Brace::OperandRuntimeInfo> m_ArgInfos;
        Brace::OperandRuntimeInfo m_ResultInfo;
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

    typedef std::stack<FuncInfo*> FuncInfoStack;
    typedef std::stack<RuntimeStackInfo> RuntimeStack;
    typedef std::function<void(const std::string&)> LogDelegation;
    typedef std::function<bool(const DslData::ISyntaxComponent&, OperandLoadtimeInfo&)> LoadTypeInfoDelegation;
    typedef std::function<int(const DslData::ISyntaxComponent&, const LoadTypeInfoDelegation&)> GetObjectTypeIdDelegation;
    typedef std::function<const char* (int)> GetObjectTypeNameDelegation;
    typedef std::function<bool(int,int)> ObjectAssignCheckDelegation;
    typedef std::function<bool(const DslData::ISyntaxComponent&, OperandLoadtimeInfo&, BraceApiExecutor&)> FilterLoadDelegation;
    typedef std::function<bool(const DslData::ValueData&, OperandLoadtimeInfo&, BraceApiExecutor&)> LoadValueFailedDelegation;
    typedef std::function<bool(const DslData::FunctionData&, OperandLoadtimeInfo&, BraceApiExecutor&)> LoadFunctionFailedDelegation;
    typedef std::function<bool(const DslData::StatementData&, OperandLoadtimeInfo&, BraceApiExecutor&)> LoadStatementFailedDelegation;
    typedef std::function<RuntimeStack*(void)> GetRuntimeStackDelegation;
    class BraceScript final
    {
        friend class BraceApiImplHelper;
        struct BlockInfo final
        {
            int BlockId;
            std::vector<int> ObjVars;
            //Standby for simple VM and DAG optimization implementations, Each basic block is implemented as a BraceApiExecutor
            std::vector<Instruction> BasicBlock;

            BlockInfo(int blockId) :BlockId(blockId), ObjVars(), BasicBlock()
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
        /// <summary>
        /// This delegate is used to implement coroutines
        /// </summary>
        GetRuntimeStackDelegation OnGetRuntimeStack;
    public:
        /// Because we didn't implement Object internally, we kept these apis, but we had to implement them externally
        /// See ExternalAPiRef.txt
        /// -----------------------------------------------------------------------------------------------------------
        /// RegisterApi("membercall", new BraceApiFactory<MemberCallExp>());
        /// RegisterApi("memberset", new BraceApiFactory<MemberSetExp>());
        /// RegisterApi("memberget", new BraceApiFactory<MemberGetExp>());
        /// RegisterApi("collectioncall", new BraceApiFactory<CollectionCallExp>());
        /// RegisterApi("collectionset", new BraceApiFactory<CollectionSetExp>());
        /// RegisterApi("collectionget", new BraceApiFactory<CollectionGetExp>());
        /// RegisterApi("linq", new BraceApiFactory<LinqExp>());
        /// RegisterApi("select", new Brace::BraceApiFactory<SelectExp>());
        /// RegisterApi("lambda", new BraceApiFactory<LambdaExp>());
        /// RegisterApi("array", new BraceApiFactory<ArrayExp>());
        /// RegisterApi("hashtable", new BraceApiFactory<HashtableExp>());
        /// RegisterApi("looplist", new BraceApiFactory<LoopListExp>());
        /// -----------------------------------------------------------------------------------------------------------
        void RegisterApi(const std::string& id, IBraceApiFactory* pApiFactory);
        void RegisterApi(std::string&& id, IBraceApiFactory* pApiFactory);
        void SetFailbackApi(AbstractBraceApi* pFailbackApi);
        AbstractBraceApi* GetFailbackApi(void)const;
        void SetContextObject(const std::shared_ptr<void>& pContext);
        const std::shared_ptr<void>& GetContextObject(void)const;
        void Reset(void);
        void LoadFuncApiTypeInfo(const DslData::DslFile& dslInfos);
        void AddFuncApiTypeInfo(const std::string& name, const FuncApiTypeInfo& info);
        void AddFuncApiTypeInfo(std::string&& name, FuncApiTypeInfo&& info);
        FuncInfo* GetOrAddFuncInfo(const std::string& name);
        void LoadScript(const DslData::DslFile& file);
        void Run(void);
        void Run(int start);
        int GetGlobalCodeNum(void)const;
        FuncInfo* GlobalFuncInfo(void)const;
        VariableInfo* GlobalVariables(void)const;
        bool HasWarn(void)const { return m_HasWarn; }
        bool HasError(void)const { return m_HasError; }
        bool IsForceQuit(void)const { return m_ForceQuit; }
        void SetForceQuit(bool forceQuit) { m_ForceQuit = forceQuit; }
    public:
        void AddSyntaxComponent(DslData::ISyntaxComponent* p);
        void AddApiInstance(IBraceApi* p); 
        IBraceApi* CreateApi(const std::string& name);
    private:
        const FuncInfo* CurRuntimeFuncInfo(void)const;
        VariableInfo* CurRuntimeVariables(void)const;
        void PushRuntimeStack(const FuncInfo* funcInfo);
        void PopRuntimeStack(void);
    private:
        void LogInfo(const std::string& info);
        void LogWarn(const std::string& warn);
        void LogError(const std::string& error);
        int GetObjectTypeId(const DslData::ISyntaxComponent& typeSyntax)const;
        const char* GetObjectTypeName(int objTypeId)const;
        ParamTypeInfo ParseParamTypeInfo(const DslData::ISyntaxComponent& syntax)const;
        bool CanAssign(int destType, int destObjTypeId, int srcType, int srcObjTypeId) const;
        const FuncApiTypeInfo* GetFuncApiTypeInfo(const std::string& name)const;
        FuncApiTypeInfo* GetFuncApiTypeInfo(const std::string& name);
        const FuncInfo* GetFuncInfo(const std::string& name)const;
        FuncInfo* GetFuncInfo(const std::string& name);
        const FuncInfo* CurFuncInfo(void)const;
        FuncInfo* CurFuncInfo(void);
        FuncInfo* PushFuncInfo(const std::string& name);
        void PopFuncInfo(void);
        int GenNextUniqueId(void) { return m_NextUniqueId++; }
        int CurBlockId(void)const;
        const std::vector<int>& CurBlockObjVars(void)const;
        std::vector<int>& CurBlockObjVars(void);
        const std::vector<Instruction>& CurBasicBlock(void)const;
        std::vector<Instruction>& CurBasicBlock(void);
        void PushBlock(void);
        void PopBlock(void);
        std::string CalcVarKey(const std::string& name, int level)const;
        std::string CalcConstKey(int tok_type, const std::string& name)const;
        int AllocGlobalVariable(const std::string& name, int type, int objTypeId);
        auto FindVariable(FuncInfo* func, const std::string& name, std::string& key, int& level)const -> decltype(func->VarTypeInfos.end());
        int AllocVariable(const std::string& name, int type, int objTypeId);
        int AllocConst(int tok_type, const std::string& value, int& type, int& objTypeId);
        BraceApiExecutor Load(const DslData::ISyntaxComponent& syntaxUnit, OperandLoadtimeInfo& resultInfo);
    private:
        BraceApiExecutor LoadValue(const DslData::ValueData& data, OperandLoadtimeInfo& resultInfo);
        BraceApiExecutor LoadFunction(const DslData::FunctionData& data, OperandLoadtimeInfo& resultInfo);
        BraceApiExecutor LoadStatement(const DslData::StatementData& data, OperandLoadtimeInfo& resultInfo);
        bool DoFilterLoad(const DslData::ISyntaxComponent& syntaxUnit, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor);
        bool DoLoadValueFailed(const DslData::ValueData& syntaxUnit, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor);
        bool DoLoadFunctionFailed(const DslData::FunctionData& syntaxUnit, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor);
        bool DoLoadStatementFailed(const DslData::StatementData& syntaxUnit, OperandLoadtimeInfo& resultInfo, BraceApiExecutor& executor);
        void RegisterInnerApis(void);
        void Init(void);
        void Release(void);
        bool DoLoadTypeInfo(const DslData::ISyntaxComponent&, OperandLoadtimeInfo&);
        const RuntimeStack& GetRuntimeStack(void)const;
        RuntimeStack& GetRuntimeStack(void);
    private:
        BraceScript(const BraceScript&) = delete;
        BraceScript& operator=(const BraceScript&) = delete;
        BraceScript(BraceScript&&) noexcept = delete;
        BraceScript& operator=(BraceScript&&) noexcept = delete;
    private:
        std::unordered_map<std::string, IBraceApiFactory*> m_ApiFactories;
        std::vector<DslData::ISyntaxComponent*> m_AddedSyntaxComponents;
        std::vector<IBraceApi*> m_ApiInstances;
        std::unordered_map<std::string, FuncApiTypeInfo> m_FuncApiTypeInfos;
        std::unordered_map<std::string, FuncInfo> m_Funcs;

        bool m_ForceQuit;
        bool m_HasWarn;
        bool m_HasError;
        FuncInfoStack m_FuncInfoStack;
        int m_NextUniqueId;
        int m_LastBlockId;
        std::vector<BlockInfo> m_LexicalScopeStack;
        FuncInfo* m_GlobalFunc;
        VariableInfo* m_GlobalVariables;
        RuntimeStack m_RuntimeStack;

        LoadTypeInfoDelegation m_LoadTypeInfo;
        AbstractBraceApi* m_FailbackApi;
        std::shared_ptr<void> m_ContextObj;
    };
}