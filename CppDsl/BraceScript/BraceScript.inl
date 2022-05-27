
static inline int32_t StrToInt32(const std::string& value)
{
    try {
        return std::stoi(value, nullptr, 0);
    }
    catch (std::out_of_range const&) {
        try {
            return static_cast<int32_t>(std::stoull(value, nullptr, 0));
        }
        catch (...) {
            return 0;
        }
    }
    catch (...) {
        return 0;
    }
}
static inline int64_t StrToInt64(const std::string& value)
{
    try {
        return std::stoll(value, nullptr, 0);
    }
    catch (std::out_of_range const&) {
        try {
            return static_cast<int64_t>(std::stoull(value, nullptr, 0));
        }
        catch (...) {
            return 0;
        }
    }
    catch (...) {
        return 0;
    }
}
static inline uint32_t StrToUInt32(const std::string& value)
{
    try {
        return std::stoul(value, nullptr, 0);
    }
    catch (std::out_of_range const&) {
        try {
            return static_cast<uint32_t>(std::stoull(value, nullptr, 0));
        }
        catch (...) {
            return 0;
        }
    }
    catch (...) {
        return 0;
    }
}
static inline uint64_t StrToUInt64(const std::string& value)
{
    try {
        return std::stoull(value, nullptr, 0);
    }
    catch (std::out_of_range const&) {
        return 0;
    }
    catch (...) {
        return 0;
    }
}
static inline float StrToFloat(const std::string& value)
{
    try {
        return std::stof(value);
    }
    catch (std::out_of_range const&) {
        try {
            return static_cast<float>(std::stod(value));
        }
        catch (...) {
            return 0;
        }
    }
    catch (...) {
        return 0;
    }
}
static inline double StrToDouble(const std::string& value)
{
    try {
        return std::stod(value);
    }
    catch (std::out_of_range const&) {
        return 0;
    }
    catch (...) {
        return 0;
    }
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

#define DEFINE_VAR_ASSIGN(POSTFIX, NAME) \
    static inline void VarAssign##POSTFIX(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)\
    {\
        info.NAME[destIndex] = srcInfo.NAME[srcIndex];\
    }

#define DEFINE_VAR_CAST_ASSIGN(POSTFIX, DESTNAME, DESTTYPE, SRCNAME) \
    static inline void VarCastAssign##POSTFIX(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)\
    {\
        info.DESTNAME[destIndex] = static_cast<DESTTYPE>(srcInfo.SRCNAME[srcIndex]);\
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
    DEFINE_VAR_GET(Object, ObjectVars, IBraceObject*);

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
    DEFINE_VAR_SET(Object, ObjectVars, IBraceObject*);

    DEFINE_VAR_ASSIGN(Bool, BoolVars);
    DEFINE_VAR_ASSIGN(Int8, Int8Vars);
    DEFINE_VAR_ASSIGN(Int16, Int16Vars);
    DEFINE_VAR_ASSIGN(Int32, Int32Vars);
    DEFINE_VAR_ASSIGN(Int64, Int64Vars);
    DEFINE_VAR_ASSIGN(Uint8, Uint8Vars);
    DEFINE_VAR_ASSIGN(Uint16, Uint16Vars);
    DEFINE_VAR_ASSIGN(Uint32, Uint32Vars);
    DEFINE_VAR_ASSIGN(Uint64, Uint64Vars);
    DEFINE_VAR_ASSIGN(Float, FloatVars);
    DEFINE_VAR_ASSIGN(Double, DoubleVars);
    DEFINE_VAR_ASSIGN(String, StringVars);
    DEFINE_VAR_ASSIGN(Object, ObjectVars);
    DEFINE_VAR_CAST_ASSIGN(BoolInt8, BoolVars, bool, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(BoolInt16, BoolVars, bool, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(BoolInt32, BoolVars, bool, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(BoolInt64, BoolVars, bool, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(BoolUint8, BoolVars, bool, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(BoolUint16, BoolVars, bool, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(BoolUint32, BoolVars, bool, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(BoolUint64, BoolVars, bool, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(Int8Bool, Int8Vars, int8_t, BoolVars);
    DEFINE_VAR_CAST_ASSIGN(Int8Int16, Int8Vars, int8_t, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(Int8Int32, Int8Vars, int8_t, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(Int8Int64, Int8Vars, int8_t, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(Int8Uint8, Int8Vars, int8_t, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(Int8Uint16, Int8Vars, int8_t, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(Int8Uint32, Int8Vars, int8_t, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(Int8Uint64, Int8Vars, int8_t, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(Int8Float, Int8Vars, int8_t, FloatVars);
    DEFINE_VAR_CAST_ASSIGN(Int8Double, Int8Vars, int8_t, DoubleVars);
    DEFINE_VAR_CAST_ASSIGN(Int16Bool, Int16Vars, int16_t, BoolVars);
    DEFINE_VAR_CAST_ASSIGN(Int16Int8, Int16Vars, int16_t, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(Int16Int32, Int16Vars, int16_t, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(Int16Int64, Int16Vars, int16_t, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(Int16Uint8, Int16Vars, int16_t, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(Int16Uint16, Int16Vars, int16_t, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(Int16Uint32, Int16Vars, int16_t, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(Int16Uint64, Int16Vars, int16_t, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(Int16Float, Int16Vars, int16_t, FloatVars);
    DEFINE_VAR_CAST_ASSIGN(Int16Double, Int16Vars, int16_t, DoubleVars);
    DEFINE_VAR_CAST_ASSIGN(Int32Bool, Int32Vars, int32_t, BoolVars);
    DEFINE_VAR_CAST_ASSIGN(Int32Int8, Int32Vars, int32_t, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(Int32Int16, Int32Vars, int32_t, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(Int32Int64, Int32Vars, int32_t, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(Int32Uint8, Int32Vars, int32_t, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(Int32Uint16, Int32Vars, int32_t, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(Int32Uint32, Int32Vars, int32_t, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(Int32Uint64, Int32Vars, int32_t, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(Int32Float, Int32Vars, int32_t, FloatVars);
    DEFINE_VAR_CAST_ASSIGN(Int32Double, Int32Vars, int32_t, DoubleVars);
    DEFINE_VAR_CAST_ASSIGN(Int64Bool, Int64Vars, int64_t, BoolVars);
    DEFINE_VAR_CAST_ASSIGN(Int64Int8, Int64Vars, int64_t, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(Int64Int16, Int64Vars, int64_t, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(Int64Int32, Int64Vars, int64_t, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(Int64Uint8, Int64Vars, int64_t, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(Int64Uint16, Int64Vars, int64_t, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(Int64Uint32, Int64Vars, int64_t, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(Int64Uint64, Int64Vars, int64_t, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(Int64Float, Int64Vars, int64_t, FloatVars);
    DEFINE_VAR_CAST_ASSIGN(Int64Double, Int64Vars, int64_t, DoubleVars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Bool, Uint8Vars, uint8_t, BoolVars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Int8, Uint8Vars, uint8_t, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Int16, Uint8Vars, uint8_t, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Int32, Uint8Vars, uint8_t, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Int64, Uint8Vars, uint8_t, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Uint16, Uint8Vars, uint8_t, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Uint32, Uint8Vars, uint8_t, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Uint64, Uint8Vars, uint8_t, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Float, Uint8Vars, uint8_t, FloatVars);
    DEFINE_VAR_CAST_ASSIGN(Uint8Double, Uint8Vars, uint8_t, DoubleVars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Bool, Uint16Vars, uint16_t, BoolVars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Int8, Uint16Vars, uint16_t, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Int16, Uint16Vars, uint16_t, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Int32, Uint16Vars, uint16_t, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Int64, Uint16Vars, uint16_t, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Uint8, Uint16Vars, uint16_t, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Uint32, Uint16Vars, uint16_t, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Uint64, Uint16Vars, uint16_t, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Float, Uint16Vars, uint16_t, FloatVars);
    DEFINE_VAR_CAST_ASSIGN(Uint16Double, Uint16Vars, uint16_t, DoubleVars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Bool, Uint32Vars, uint32_t, BoolVars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Int8, Uint32Vars, uint32_t, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Int16, Uint32Vars, uint32_t, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Int32, Uint32Vars, uint32_t, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Int64, Uint32Vars, uint32_t, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Uint8, Uint32Vars, uint32_t, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Uint16, Uint32Vars, uint32_t, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Uint64, Uint32Vars, uint32_t, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Float, Uint32Vars, uint32_t, FloatVars);
    DEFINE_VAR_CAST_ASSIGN(Uint32Double, Uint32Vars, uint32_t, DoubleVars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Bool, Uint64Vars, uint64_t, BoolVars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Int8, Uint64Vars, uint64_t, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Int16, Uint64Vars, uint64_t, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Int32, Uint64Vars, uint64_t, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Int64, Uint64Vars, uint64_t, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Uint8, Uint64Vars, uint64_t, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Uint16, Uint64Vars, uint64_t, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Uint32, Uint64Vars, uint64_t, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Float, Uint64Vars, uint64_t, FloatVars);
    DEFINE_VAR_CAST_ASSIGN(Uint64Double, Uint64Vars, uint64_t, DoubleVars);
    DEFINE_VAR_CAST_ASSIGN(FloatInt8, FloatVars, float, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(FloatInt16, FloatVars, float, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(FloatInt32, FloatVars, float, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(FloatInt64, FloatVars, float, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(FloatUint8, FloatVars, float, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(FloatUint16, FloatVars, float, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(FloatUint32, FloatVars, float, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(FloatUint64, FloatVars, float, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(FloatDouble, FloatVars, float, DoubleVars);
    DEFINE_VAR_CAST_ASSIGN(DoubleInt8, DoubleVars, double, Int8Vars);
    DEFINE_VAR_CAST_ASSIGN(DoubleInt16, DoubleVars, double, Int16Vars);
    DEFINE_VAR_CAST_ASSIGN(DoubleInt32, DoubleVars, double, Int32Vars);
    DEFINE_VAR_CAST_ASSIGN(DoubleInt64, DoubleVars, double, Int64Vars);
    DEFINE_VAR_CAST_ASSIGN(DoubleUint8, DoubleVars, double, Uint8Vars);
    DEFINE_VAR_CAST_ASSIGN(DoubleUint16, DoubleVars, double, Uint16Vars);
    DEFINE_VAR_CAST_ASSIGN(DoubleUint32, DoubleVars, double, Uint32Vars);
    DEFINE_VAR_CAST_ASSIGN(DoubleUint64, DoubleVars, double, Uint64Vars);
    DEFINE_VAR_CAST_ASSIGN(DoubleFloat, DoubleVars, double, FloatVars);

    VarAssignPtr GetVarAssignPtr(int varType, int srcVarType)
    {
        switch (varType) {
        case BRACE_DATA_TYPE_BOOL: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarAssignBool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignBoolInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignBoolInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignBoolInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignBoolInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignBoolUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignBoolUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignBoolUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignBoolUint64;
            }
        }break;
        case BRACE_DATA_TYPE_INT8: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignInt8Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarAssignInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignInt8Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignInt8Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignInt8Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignInt8Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignInt8Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignInt8Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignInt8Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignInt8Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignInt8Double;
            }
        }break;
        case BRACE_DATA_TYPE_INT16: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignInt16Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignInt16Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarAssignInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignInt16Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignInt16Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignInt16Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignInt16Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignInt16Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignInt16Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignInt16Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignInt16Double;
            }
        }break;
        case BRACE_DATA_TYPE_INT32: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignInt32Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignInt32Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignInt32Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarAssignInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignInt32Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignInt32Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignInt32Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignInt32Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignInt32Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignInt32Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignInt32Double;
            }
        }break;
        case BRACE_DATA_TYPE_INT64: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignInt64Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignInt64Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignInt64Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignInt64Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarAssignInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignInt64Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignInt64Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignInt64Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignInt64Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignInt64Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignInt64Double;
            }
        }break;
        case BRACE_DATA_TYPE_UINT8: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignUint8Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignUint8Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignUint8Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignUint8Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignUint8Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarAssignUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignUint8Int16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignUint8Int32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignUint8Int64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignUint8Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignUint8Double;
            }
        }break;
        case BRACE_DATA_TYPE_UINT16: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignUint16Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignUint16Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignUint16Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignUint16Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignUint16Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignUint16Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarAssignUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignUint16Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignUint16Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignUint16Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignUint16Double;
            }
        }break;
        case BRACE_DATA_TYPE_UINT32: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignUint32Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignUint32Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignUint32Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignUint32Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignUint32Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignUint32Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignUint32Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarAssignUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignUint32Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignUint32Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignUint32Double;
            }
        }break;
        case BRACE_DATA_TYPE_UINT64: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignUint64Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignUint64Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignUint64Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignUint64Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignUint64Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignUint64Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignUint64Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignUint64Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarAssignUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignUint64Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignUint64Double;
            }
        }break;
        case BRACE_DATA_TYPE_FLOAT: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFloatInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFloatInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFloatInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFloatInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFloatUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFloatUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFloatUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFloatUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarAssignFloat;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFloatDouble;
            }
        }break;
        case BRACE_DATA_TYPE_DOUBLE: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignDoubleInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignDoubleInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignDoubleInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignDoubleInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignDoubleUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignDoubleUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignDoubleUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignDoubleUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignDoubleFloat;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarAssignDouble;
            }
        }break;
        case BRACE_DATA_TYPE_STRING: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_STRING:
                return VarAssignString;
            }
        }break;
        case BRACE_DATA_TYPE_OBJECT: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_OBJECT:
                return VarAssignObject;
            }
        }break;
        }
        return nullptr;
    }
    const char* GetBraceDataTypeName(int type)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            return "bool";
        case BRACE_DATA_TYPE_INT8:
            return "int8";
        case BRACE_DATA_TYPE_INT16:
            return "int16";
        case BRACE_DATA_TYPE_INT32:
            return "int32";
        case BRACE_DATA_TYPE_INT64:
            return "int64";
        case BRACE_DATA_TYPE_UINT8:
            return "uint8";
        case BRACE_DATA_TYPE_UINT16:
            return "uint16";
        case BRACE_DATA_TYPE_UINT32:
            return "uint32";
        case BRACE_DATA_TYPE_UINT64:
            return "uint64";
        case BRACE_DATA_TYPE_FLOAT:
            return "float";
        case BRACE_DATA_TYPE_DOUBLE:
            return "double";
        case BRACE_DATA_TYPE_STRING:
            return "string";
        case BRACE_DATA_TYPE_OBJECT:
            return "object";
        default:
            return "unknown";
        }
    }
    int GetBraceDataType(const std::string& typeName)
    {
        if (typeName == "bool")
            return BRACE_DATA_TYPE_BOOL;
        else if (typeName == "int8")
            return BRACE_DATA_TYPE_INT8;
        else if (typeName == "int16")
            return BRACE_DATA_TYPE_INT16;
        else if (typeName == "int32")
            return BRACE_DATA_TYPE_INT32;
        else if (typeName == "int64")
            return BRACE_DATA_TYPE_INT64;
        else if (typeName == "uint8")
            return BRACE_DATA_TYPE_UINT8;
        else if (typeName == "uint16")
            return BRACE_DATA_TYPE_UINT16;
        else if (typeName == "uint32")
            return BRACE_DATA_TYPE_UINT32;
        else if (typeName == "uint64")
            return BRACE_DATA_TYPE_UINT64;
        else if (typeName == "float")
            return BRACE_DATA_TYPE_FLOAT;
        else if (typeName == "double")
            return BRACE_DATA_TYPE_DOUBLE;
        else if (typeName == "string")
            return BRACE_DATA_TYPE_STRING;
        else
            return BRACE_DATA_TYPE_OBJECT;
    }
    static inline bool NeedFloatArithUnit(int type1, int type2)
    {
        bool b1 = false;
        bool b2 = false;
        switch (type1) {
        case BRACE_DATA_TYPE_FLOAT:
        case BRACE_DATA_TYPE_DOUBLE:
            b1 = true;
            break;
        }
        switch (type2) {
        case BRACE_DATA_TYPE_FLOAT:
        case BRACE_DATA_TYPE_DOUBLE:
            b2 = true;
            break;
        }
        return b1 || b2;
    }
    static inline bool CanAssign(int destType, int srcType)
    {
        switch (destType) {
        case BRACE_DATA_TYPE_BOOL: {
            switch (srcType) {
            case BRACE_DATA_TYPE_BOOL:
            case BRACE_DATA_TYPE_INT8:
            case BRACE_DATA_TYPE_INT16:
            case BRACE_DATA_TYPE_INT32:
            case BRACE_DATA_TYPE_INT64:
            case BRACE_DATA_TYPE_UINT8:
            case BRACE_DATA_TYPE_UINT16:
            case BRACE_DATA_TYPE_UINT32:
            case BRACE_DATA_TYPE_UINT64:
                return true;
            }
        }break;
        case BRACE_DATA_TYPE_INT8:
        case BRACE_DATA_TYPE_INT16:
        case BRACE_DATA_TYPE_INT32:
        case BRACE_DATA_TYPE_INT64:
        case BRACE_DATA_TYPE_UINT8:
        case BRACE_DATA_TYPE_UINT16:
        case BRACE_DATA_TYPE_UINT32:
        case BRACE_DATA_TYPE_UINT64: {
            switch (srcType) {
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
            case BRACE_DATA_TYPE_DOUBLE:
                return true;
            }
        }break;
        case BRACE_DATA_TYPE_FLOAT:
        case BRACE_DATA_TYPE_DOUBLE: {
            switch (srcType) {
            case BRACE_DATA_TYPE_INT8:
            case BRACE_DATA_TYPE_INT16:
            case BRACE_DATA_TYPE_INT32:
            case BRACE_DATA_TYPE_INT64:
            case BRACE_DATA_TYPE_UINT8:
            case BRACE_DATA_TYPE_UINT16:
            case BRACE_DATA_TYPE_UINT32:
            case BRACE_DATA_TYPE_UINT64:
            case BRACE_DATA_TYPE_FLOAT:
            case BRACE_DATA_TYPE_DOUBLE:
                return true;
            }
        }break;
        case BRACE_DATA_TYPE_STRING: {
            switch (srcType) {
            case BRACE_DATA_TYPE_STRING:
                return true;
            }
        }break;
        case BRACE_DATA_TYPE_OBJECT: {
            switch (srcType) {
            case BRACE_DATA_TYPE_OBJECT:
                return true;
            }
        }break;
        }
        return false;
    }
    static inline bool VarGetBoolean(VariableInfo& info, int type, int index)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            return info.BoolVars[index];
        case BRACE_DATA_TYPE_INT8:
            return info.Int8Vars[index] != 0;
        case BRACE_DATA_TYPE_INT16:
            return info.Int16Vars[index] != 0;
        case BRACE_DATA_TYPE_INT32:
            return info.Int32Vars[index] != 0;
        case BRACE_DATA_TYPE_INT64:
            return info.Int64Vars[index] != 0;
        case BRACE_DATA_TYPE_UINT8:
            return info.Uint8Vars[index] != 0;
        case BRACE_DATA_TYPE_UINT16:
            return info.Uint16Vars[index] != 0;
        case BRACE_DATA_TYPE_UINT32:
            return info.Uint32Vars[index] != 0;
        case BRACE_DATA_TYPE_UINT64:
            return info.Uint64Vars[index] != 0;
        case BRACE_DATA_TYPE_FLOAT:
            return info.FloatVars[index] != 0;
        case BRACE_DATA_TYPE_DOUBLE:
            return info.DoubleVars[index] != 0;
        }
        return false;
    }
    static inline int64_t VarGetI64(VariableInfo& info, int type, int index)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            return info.BoolVars[index] ? 1 : 0;
        case BRACE_DATA_TYPE_INT8:
            return info.Int8Vars[index];
        case BRACE_DATA_TYPE_INT16:
            return info.Int16Vars[index];
        case BRACE_DATA_TYPE_INT32:
            return info.Int32Vars[index];
        case BRACE_DATA_TYPE_INT64:
            return info.Int64Vars[index];
        case BRACE_DATA_TYPE_UINT8:
            return info.Uint8Vars[index];
        case BRACE_DATA_TYPE_UINT16:
            return info.Uint16Vars[index];
        case BRACE_DATA_TYPE_UINT32:
            return info.Uint32Vars[index];
        case BRACE_DATA_TYPE_UINT64:
            return static_cast<int64_t>(info.Uint64Vars[index]);
        case BRACE_DATA_TYPE_FLOAT:
            return static_cast<int64_t>(info.FloatVars[index]);
        case BRACE_DATA_TYPE_DOUBLE:
            return static_cast<int64_t>(info.DoubleVars[index]);
        }
        return 0;
    }
    static inline uint64_t VarGetU64(VariableInfo& info, int type, int index)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            return static_cast<uint64_t>(info.BoolVars[index] ? 1 : 0);
        case BRACE_DATA_TYPE_INT8:
            return static_cast<uint64_t>(info.Int8Vars[index]);
        case BRACE_DATA_TYPE_INT16:
            return static_cast<uint64_t>(info.Int16Vars[index]);
        case BRACE_DATA_TYPE_INT32:
            return static_cast<uint64_t>(info.Int32Vars[index]);
        case BRACE_DATA_TYPE_INT64:
            return static_cast<uint64_t>(info.Int64Vars[index]);
        case BRACE_DATA_TYPE_UINT8:
            return info.Uint8Vars[index];
        case BRACE_DATA_TYPE_UINT16:
            return info.Uint16Vars[index];
        case BRACE_DATA_TYPE_UINT32:
            return info.Uint32Vars[index];
        case BRACE_DATA_TYPE_UINT64:
            return info.Uint64Vars[index];
        case BRACE_DATA_TYPE_FLOAT:
            return static_cast<uint64_t>(info.FloatVars[index]);
        case BRACE_DATA_TYPE_DOUBLE:
            return static_cast<uint64_t>(info.DoubleVars[index]);
        }
        return 0;
    }
    static inline double VarGetF64(VariableInfo& info, int type, int index)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            return info.BoolVars[index] ? 1 : 0;
        case BRACE_DATA_TYPE_INT8:
            return info.Int8Vars[index];
        case BRACE_DATA_TYPE_INT16:
            return info.Int16Vars[index];
        case BRACE_DATA_TYPE_INT32:
            return info.Int32Vars[index];
        case BRACE_DATA_TYPE_INT64:
            return static_cast<double>(info.Int64Vars[index]);
        case BRACE_DATA_TYPE_UINT8:
            return info.Uint8Vars[index];
        case BRACE_DATA_TYPE_UINT16:
            return info.Uint16Vars[index];
        case BRACE_DATA_TYPE_UINT32:
            return info.Uint32Vars[index];
        case BRACE_DATA_TYPE_UINT64:
            return static_cast<double>(info.Uint64Vars[index]);
        case BRACE_DATA_TYPE_FLOAT:
            return info.FloatVars[index];
        case BRACE_DATA_TYPE_DOUBLE:
            return info.DoubleVars[index];
        }
        return 0;
    }
    static inline std::string VarGetStr(VariableInfo& info, int type, int index)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            return info.BoolVars[index] ? "true" : "false";
        case BRACE_DATA_TYPE_INT8:
            return std::to_string(info.Int8Vars[index]);
        case BRACE_DATA_TYPE_INT16:
            return std::to_string(info.Int16Vars[index]);
        case BRACE_DATA_TYPE_INT32:
            return std::to_string(info.Int32Vars[index]);
        case BRACE_DATA_TYPE_INT64:
            return std::to_string(info.Int64Vars[index]);
        case BRACE_DATA_TYPE_UINT8:
            return std::to_string(info.Uint8Vars[index]);
        case BRACE_DATA_TYPE_UINT16:
            return std::to_string(info.Uint16Vars[index]);
        case BRACE_DATA_TYPE_UINT32:
            return std::to_string(info.Uint32Vars[index]);
        case BRACE_DATA_TYPE_UINT64:
            return std::to_string(info.Uint64Vars[index]);
        case BRACE_DATA_TYPE_FLOAT:
            return std::to_string(info.FloatVars[index]);
        case BRACE_DATA_TYPE_DOUBLE:
            return std::to_string(info.DoubleVars[index]);
        case BRACE_DATA_TYPE_STRING:
            return info.StringVars[index];
        }
        return std::string();
    }
    static inline void VarSetBoolean(VariableInfo& info, int type, int index, bool val)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            info.BoolVars[index] = val;
            break;
        case BRACE_DATA_TYPE_INT8:
            info.Int8Vars[index] = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_INT16:
            info.Int16Vars[index] = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_INT32:
            info.Int32Vars[index] = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_INT64:
            info.Int64Vars[index] = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.Uint8Vars[index] = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.Uint16Vars[index] = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.Uint32Vars[index] = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.Uint64Vars[index] = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.FloatVars[index] = static_cast<float>(val ? 1 : 0);
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.DoubleVars[index] = static_cast<double>(val ? 1 : 0);
            break;
        }
    }
    static inline void VarSetI64(VariableInfo& info, int type, int index, int64_t val)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            info.BoolVars[index] = val != 0;
            break;
        case BRACE_DATA_TYPE_INT8:
            info.Int8Vars[index] = static_cast<int8_t>(val);
            break;
        case BRACE_DATA_TYPE_INT16:
            info.Int16Vars[index] = static_cast<int16_t>(val);
            break;
        case BRACE_DATA_TYPE_INT32:
            info.Int32Vars[index] = static_cast<int32_t>(val);
            break;
        case BRACE_DATA_TYPE_INT64:
            info.Int64Vars[index] = val;
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.Uint8Vars[index] = static_cast<uint8_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.Uint16Vars[index] = static_cast<uint16_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.Uint32Vars[index] = static_cast<uint32_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.Uint64Vars[index] = static_cast<uint64_t>(val);
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.FloatVars[index] = static_cast<float>(val);
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.DoubleVars[index] = static_cast<double>(val);
            break;
        }
    }
    static inline void VarSetU64(VariableInfo& info, int type, int index, uint64_t val)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            info.BoolVars[index] = val != 0;
            break;
        case BRACE_DATA_TYPE_INT8:
            info.Int8Vars[index] = static_cast<int8_t>(val);
            break;
        case BRACE_DATA_TYPE_INT16:
            info.Int16Vars[index] = static_cast<int16_t>(val);
            break;
        case BRACE_DATA_TYPE_INT32:
            info.Int32Vars[index] = static_cast<int32_t>(val);
            break;
        case BRACE_DATA_TYPE_INT64:
            info.Int64Vars[index] = static_cast<int64_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.Uint8Vars[index] = static_cast<uint8_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.Uint16Vars[index] = static_cast<uint16_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.Uint32Vars[index] = static_cast<uint32_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.Uint64Vars[index] = val;
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.FloatVars[index] = static_cast<float>(val);
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.DoubleVars[index] = static_cast<double>(val);
            break;
        }
    }
    static inline void VarSetF64(VariableInfo& info, int type, int index, double val)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            info.BoolVars[index] = val != 0;
            break;
        case BRACE_DATA_TYPE_INT8:
            info.Int8Vars[index] = static_cast<int8_t>(val);
            break;
        case BRACE_DATA_TYPE_INT16:
            info.Int16Vars[index] = static_cast<int16_t>(val);
            break;
        case BRACE_DATA_TYPE_INT32:
            info.Int32Vars[index] = static_cast<int32_t>(val);
            break;
        case BRACE_DATA_TYPE_INT64:
            info.Int64Vars[index] = static_cast<int64_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.Uint8Vars[index] = static_cast<uint8_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.Uint16Vars[index] = static_cast<uint16_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.Uint32Vars[index] = static_cast<uint32_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.Uint64Vars[index] = static_cast<uint64_t>(val);
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.FloatVars[index] = static_cast<float>(val);
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.DoubleVars[index] = static_cast<double>(val);
            break;
        }
    }
    static inline void VarSetStr(VariableInfo& info, int type, int index, const std::string& val)
    {
        switch (type) {
        case BRACE_DATA_TYPE_BOOL:
            info.BoolVars[index] = val == "true";
            break;
        case BRACE_DATA_TYPE_INT8:
            info.Int8Vars[index] = StrToInt32(val);
            break;
        case BRACE_DATA_TYPE_INT16:
            info.Int16Vars[index] = StrToInt32(val);
            break;
        case BRACE_DATA_TYPE_INT32:
            info.Int32Vars[index] = StrToInt32(val);
            break;
        case BRACE_DATA_TYPE_INT64:
            info.Int64Vars[index] = StrToInt64(val);
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.Uint8Vars[index] = StrToUInt32(val);
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.Uint16Vars[index] = StrToUInt32(val);
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.Uint32Vars[index] = StrToUInt32(val);
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.Uint64Vars[index] = StrToUInt64(val);
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.FloatVars[index] = static_cast<float>(StrToInt64(val));
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.DoubleVars[index] = static_cast<double>(StrToInt64(val));
            break;
        case BRACE_DATA_TYPE_STRING:
            info.StringVars[index] = val;
            break;
        }
    }

#define DEF_BINARY_ARITH_EXECUTE(POSTFIX, OPERAND_TYPE, VARGET, VARSET, OPERATOR)   \
    int ExecuteGG##POSTFIX(void) const\
    {\
        if (m_Op1)\
            m_Op1();\
        if (m_Op2)\
            m_Op2();\
        auto& vars = *CurRuntimeStack().Variables;\
        auto& srcVars = *GlobalVariables();\
        OPERAND_TYPE v1 = VARGET(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);\
        OPERAND_TYPE v2 = VARGET(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);\
        VARSET(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 OPERATOR v2);\
        return BRACE_FLOW_CONTROL_NORMAL;\
    }\
    int ExecuteLL##POSTFIX(void) const\
    {\
        if (m_Op1)\
            m_Op1();\
        if (m_Op2)\
            m_Op2();\
        auto& vars = *CurRuntimeStack().Variables;\
        OPERAND_TYPE v1 = VARGET(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);\
        OPERAND_TYPE v2 = VARGET(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);\
        VARSET(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 OPERATOR v2);\
        return BRACE_FLOW_CONTROL_NORMAL;\
    }\
    int ExecuteGL##POSTFIX(void) const\
    {\
        if (m_Op1)\
            m_Op1();\
        if (m_Op2)\
            m_Op2();\
        auto& vars = *CurRuntimeStack().Variables;\
        auto& srcVars1 = *GlobalVariables();\
        auto& srcVars2 = vars;\
        OPERAND_TYPE v1 = VARGET(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);\
        OPERAND_TYPE v2 = VARGET(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);\
        VARSET(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 OPERATOR v2);\
        return BRACE_FLOW_CONTROL_NORMAL;\
    }\
    int ExecuteLG##POSTFIX(void) const\
    {\
        if (m_Op1)\
            m_Op1();\
        if (m_Op2)\
            m_Op2();\
        auto& vars = *CurRuntimeStack().Variables;\
        auto& srcVars1 = vars;\
        auto& srcVars2 = *GlobalVariables();\
        OPERAND_TYPE v1 = VARGET(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);\
        OPERAND_TYPE v2 = VARGET(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);\
        VARSET(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 OPERATOR v2);\
        return BRACE_FLOW_CONTROL_NORMAL;\
    }

#define DEF_UNARY_ARITH_EXECUTE(POSTFIX, OPERAND_TYPE, VARGET, VARSET, OPERATOR)   \
    int ExecuteG##POSTFIX(void) const\
    {\
        if (m_Op1)\
            m_Op1();\
        auto& vars = *CurRuntimeStack().Variables;\
        auto& srcVars = *GlobalVariables();\
        OPERAND_TYPE v1 = VARGET(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);\
        VARSET(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, OPERATOR v1);\
        return BRACE_FLOW_CONTROL_NORMAL;\
    }\
    int ExecuteL##POSTFIX(void) const\
    {\
        if (m_Op1)\
            m_Op1();\
        auto& vars = *CurRuntimeStack().Variables;\
        OPERAND_TYPE v1 = VARGET(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);\
        VARSET(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, OPERATOR v1);\
        return BRACE_FLOW_CONTROL_NORMAL;\
    }

#define BUILD_BINARY_ARITH_EXECUTOR(CLASSNAME, POSTFIX)    \
    if(m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {\
        executor = std::bind(&CLASSNAME::ExecuteGG##POSTFIX, this);\
    } else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {\
        executor = std::bind(&CLASSNAME::ExecuteLL##POSTFIX, this);\
    } else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {\
        executor = std::bind(&CLASSNAME::ExecuteGL##POSTFIX, this);\
    } else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {\
        executor = std::bind(&CLASSNAME::ExecuteLG##POSTFIX, this);\
    }


#define BUILD_UNARY_ARITH_EXECUTOR(CLASSNAME, POSTFIX)    \
    if(m_LoadInfo1.IsGlobal) {\
        executor = std::bind(&CLASSNAME::ExecuteG##POSTFIX, this);\
    } else {\
        executor = std::bind(&CLASSNAME::ExecuteL##POSTFIX, this);\
    }