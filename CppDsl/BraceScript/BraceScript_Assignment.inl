
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

static inline void VarAssignBool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.BoolVars[destIndex] = srcInfo.BoolVars[srcIndex];
}
static inline void VarAssignInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = srcInfo.Int8Vars[srcIndex];
}
static inline void VarAssignInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = srcInfo.Int16Vars[srcIndex];
}
static inline void VarAssignInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = srcInfo.Int32Vars[srcIndex];
}
static inline void VarAssignInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = srcInfo.Int64Vars[srcIndex];
}
static inline void VarAssignUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = srcInfo.Uint8Vars[srcIndex];
}
static inline void VarAssignUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = srcInfo.Uint16Vars[srcIndex];
}
static inline void VarAssignUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = srcInfo.Uint32Vars[srcIndex];
}
static inline void VarAssignUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = srcInfo.Uint64Vars[srcIndex];
}
static inline void VarAssignFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = srcInfo.FloatVars[srcIndex];
}
static inline void VarAssignDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = srcInfo.DoubleVars[srcIndex];
}
static inline void VarAssignString(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.StringVars[destIndex] = srcInfo.StringVars[srcIndex];
}
static inline void VarAssignObject(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.ObjectVars[destIndex] = srcInfo.ObjectVars[srcIndex];
}
static inline void VarAssignFromRefBool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.BoolVars[destIndex] = sri.Vars->BoolVars[sri.VarIndex];
}
static inline void VarAssignFromRefInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = sri.Vars->Int8Vars[sri.VarIndex];
}
static inline void VarAssignFromRefInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = sri.Vars->Int16Vars[sri.VarIndex];
}
static inline void VarAssignFromRefInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = sri.Vars->Int32Vars[sri.VarIndex];
}
static inline void VarAssignFromRefInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = sri.Vars->Int64Vars[sri.VarIndex];
}
static inline void VarAssignFromRefUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = sri.Vars->Uint8Vars[sri.VarIndex];
}
static inline void VarAssignFromRefUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = sri.Vars->Uint16Vars[sri.VarIndex];
}
static inline void VarAssignFromRefUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = sri.Vars->Uint32Vars[sri.VarIndex];
}
static inline void VarAssignFromRefUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = sri.Vars->Uint64Vars[sri.VarIndex];
}
static inline void VarAssignFromRefFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = sri.Vars->FloatVars[sri.VarIndex];
}
static inline void VarAssignFromRefDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = sri.Vars->DoubleVars[sri.VarIndex];
}
static inline void VarAssignFromRefString(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.StringVars[destIndex] = sri.Vars->StringVars[sri.VarIndex];
}
static inline void VarAssignFromRefObject(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.ObjectVars[destIndex] = sri.Vars->ObjectVars[sri.VarIndex];
}
static inline void VarAssignToRefBool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->BoolVars[ri.VarIndex] = srcInfo.BoolVars[srcIndex];
}
static inline void VarAssignToRefInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = srcInfo.Int8Vars[srcIndex];
}
static inline void VarAssignToRefInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = srcInfo.Int16Vars[srcIndex];
}
static inline void VarAssignToRefInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = srcInfo.Int32Vars[srcIndex];
}
static inline void VarAssignToRefInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = srcInfo.Int64Vars[srcIndex];
}
static inline void VarAssignToRefUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = srcInfo.Uint8Vars[srcIndex];
}
static inline void VarAssignToRefUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = srcInfo.Uint16Vars[srcIndex];
}
static inline void VarAssignToRefUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = srcInfo.Uint32Vars[srcIndex];
}
static inline void VarAssignToRefUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = srcInfo.Uint64Vars[srcIndex];
}
static inline void VarAssignToRefFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = srcInfo.FloatVars[srcIndex];
}
static inline void VarAssignToRefDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = srcInfo.DoubleVars[srcIndex];
}
static inline void VarAssignToRefString(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->StringVars[ri.VarIndex] = srcInfo.StringVars[srcIndex];
}
static inline void VarAssignToRefObject(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->ObjectVars[ri.VarIndex] = srcInfo.ObjectVars[srcIndex];
}
static inline void VarAssignFromToRefBool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->BoolVars[ri.VarIndex] = sri.Vars->BoolVars[sri.VarIndex];
}
static inline void VarAssignFromToRefInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = sri.Vars->Int8Vars[sri.VarIndex];
}
static inline void VarAssignFromToRefInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = sri.Vars->Int16Vars[sri.VarIndex];
}
static inline void VarAssignFromToRefInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = sri.Vars->Int32Vars[sri.VarIndex];
}
static inline void VarAssignFromToRefInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = sri.Vars->Int64Vars[sri.VarIndex];
}
static inline void VarAssignFromToRefUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = sri.Vars->Uint8Vars[sri.VarIndex];
}
static inline void VarAssignFromToRefUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = sri.Vars->Uint16Vars[sri.VarIndex];
}
static inline void VarAssignFromToRefUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = sri.Vars->Uint32Vars[sri.VarIndex];
}
static inline void VarAssignFromToRefUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = sri.Vars->Uint64Vars[sri.VarIndex];
}
static inline void VarAssignFromToRefFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = sri.Vars->FloatVars[sri.VarIndex];
}
static inline void VarAssignFromToRefDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = sri.Vars->DoubleVars[sri.VarIndex];
}
static inline void VarAssignFromToRefString(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->StringVars[ri.VarIndex] = sri.Vars->StringVars[sri.VarIndex];
}
static inline void VarAssignFromToRefObject(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->ObjectVars[ri.VarIndex] = sri.Vars->ObjectVars[sri.VarIndex];
}
static inline void VarCastAssignBoolInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.BoolVars[destIndex] = static_cast<bool>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignBoolInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.BoolVars[destIndex] = static_cast<bool>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignBoolInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.BoolVars[destIndex] = static_cast<bool>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignBoolInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.BoolVars[destIndex] = static_cast<bool>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignBoolUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.BoolVars[destIndex] = static_cast<bool>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignBoolUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.BoolVars[destIndex] = static_cast<bool>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignBoolUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.BoolVars[destIndex] = static_cast<bool>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignBoolUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.BoolVars[destIndex] = static_cast<bool>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignInt8Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignInt8Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignInt8Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignInt8Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int8Vars[destIndex] = static_cast<int8_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignInt16Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignInt16Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignInt16Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignInt16Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int16Vars[destIndex] = static_cast<int16_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignInt32Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignInt32Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignInt32Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignInt32Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int32Vars[destIndex] = static_cast<int32_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignInt64Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignInt64Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignInt64Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignInt64Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Int64Vars[destIndex] = static_cast<int64_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignUint8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignUint8Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignUint8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignUint8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignUint8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignUint8Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignUint8Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignUint8Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignUint8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignUint8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignUint16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignUint16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignUint16Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignUint16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignUint16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignUint16Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignUint16Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignUint16Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignUint16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignUint16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignUint32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignUint32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignUint32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignUint32Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignUint32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignUint32Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignUint32Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignUint32Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignUint32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignUint32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignUint64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignUint64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignUint64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignUint64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignUint64Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignUint64Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignUint64Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignUint64Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignUint64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignUint64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignFloatInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = static_cast<float>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignFloatInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = static_cast<float>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignFloatInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = static_cast<float>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignFloatInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = static_cast<float>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignFloatUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = static_cast<float>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignFloatUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = static_cast<float>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignFloatUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = static_cast<float>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignFloatUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = static_cast<float>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignFloatDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.FloatVars[destIndex] = static_cast<float>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignDoubleInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = static_cast<double>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignDoubleInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = static_cast<double>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignDoubleInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = static_cast<double>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignDoubleInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = static_cast<double>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignDoubleUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = static_cast<double>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignDoubleUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = static_cast<double>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignDoubleUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = static_cast<double>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignDoubleUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = static_cast<double>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignDoubleFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    info.DoubleVars[destIndex] = static_cast<double>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignFromRefBoolInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.BoolVars[destIndex] = static_cast<bool>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefBoolInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.BoolVars[destIndex] = static_cast<bool>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefBoolInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.BoolVars[destIndex] = static_cast<bool>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefBoolInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.BoolVars[destIndex] = static_cast<bool>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefBoolUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.BoolVars[destIndex] = static_cast<bool>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefBoolUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.BoolVars[destIndex] = static_cast<bool>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefBoolUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.BoolVars[destIndex] = static_cast<bool>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefBoolUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.BoolVars[destIndex] = static_cast<bool>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int8Vars[destIndex] = static_cast<int8_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int16Vars[destIndex] = static_cast<int16_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int32Vars[destIndex] = static_cast<int32_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Int64Vars[destIndex] = static_cast<int64_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint8Vars[destIndex] = static_cast<uint8_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint16Vars[destIndex] = static_cast<uint16_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint32Vars[destIndex] = static_cast<uint32_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefUint64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.Uint64Vars[destIndex] = static_cast<uint64_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefFloatInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = static_cast<float>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefFloatInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = static_cast<float>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefFloatInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = static_cast<float>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefFloatInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = static_cast<float>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefFloatUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = static_cast<float>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefFloatUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = static_cast<float>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefFloatUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = static_cast<float>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefFloatUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = static_cast<float>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefFloatDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.FloatVars[destIndex] = static_cast<float>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefDoubleInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = static_cast<double>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefDoubleInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = static_cast<double>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefDoubleInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = static_cast<double>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefDoubleInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = static_cast<double>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefDoubleUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = static_cast<double>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefDoubleUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = static_cast<double>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefDoubleUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = static_cast<double>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefDoubleUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = static_cast<double>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromRefDoubleFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    info.DoubleVars[destIndex] = static_cast<double>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignToRefBoolInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefBoolInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefBoolInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefBoolInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefBoolUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefBoolUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefBoolUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefBoolUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignToRefInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignToRefInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignToRefInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignToRefInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignToRefUint8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignToRefUint16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignToRefUint32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.BoolVars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignToRefUint64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignToRefFloatInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefFloatInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefFloatInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefFloatInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefFloatUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefFloatUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefFloatUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefFloatUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefFloatDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(srcInfo.DoubleVars[srcIndex]);
}
static inline void VarCastAssignToRefDoubleInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(srcInfo.Int8Vars[srcIndex]);
}
static inline void VarCastAssignToRefDoubleInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(srcInfo.Int16Vars[srcIndex]);
}
static inline void VarCastAssignToRefDoubleInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(srcInfo.Int32Vars[srcIndex]);
}
static inline void VarCastAssignToRefDoubleInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(srcInfo.Int64Vars[srcIndex]);
}
static inline void VarCastAssignToRefDoubleUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(srcInfo.Uint8Vars[srcIndex]);
}
static inline void VarCastAssignToRefDoubleUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(srcInfo.Uint16Vars[srcIndex]);
}
static inline void VarCastAssignToRefDoubleUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(srcInfo.Uint32Vars[srcIndex]);
}
static inline void VarCastAssignToRefDoubleUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(srcInfo.Uint64Vars[srcIndex]);
}
static inline void VarCastAssignToRefDoubleFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(srcInfo.FloatVars[srcIndex]);
}
static inline void VarCastAssignFromToRefBoolInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefBoolInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefBoolInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefBoolInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefBoolUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefBoolUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefBoolUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefBoolUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->BoolVars[ri.VarIndex] = static_cast<bool>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int8Vars[ri.VarIndex] = static_cast<int8_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int16Vars[ri.VarIndex] = static_cast<int16_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int32Vars[ri.VarIndex] = static_cast<int32_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Int64Vars[ri.VarIndex] = static_cast<int64_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint8Vars[ri.VarIndex] = static_cast<uint8_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint16Vars[ri.VarIndex] = static_cast<uint16_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Uint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint32Vars[ri.VarIndex] = static_cast<uint32_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->BoolVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Uint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Uint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Uint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->FloatVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefUint64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->Uint64Vars[ri.VarIndex] = static_cast<uint64_t>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefFloatInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefFloatInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefFloatInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefFloatInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefFloatUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefFloatUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefFloatUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefFloatUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefFloatDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->FloatVars[ri.VarIndex] = static_cast<float>(sri.Vars->DoubleVars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefDoubleInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(sri.Vars->Int8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefDoubleInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(sri.Vars->Int16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefDoubleInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(sri.Vars->Int32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefDoubleInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(sri.Vars->Int64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefDoubleUint8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(sri.Vars->Uint8Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefDoubleUint16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(sri.Vars->Uint16Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefDoubleUint32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(sri.Vars->Uint32Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefDoubleUint64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(sri.Vars->Uint64Vars[sri.VarIndex]);
}
static inline void VarCastAssignFromToRefDoubleFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
{
    auto& ri = info.ReferenceVars[destIndex];
    auto& sri = srcInfo.ReferenceVars[srcIndex];
    ri.Vars->DoubleVars[ri.VarIndex] = static_cast<double>(sri.Vars->FloatVars[sri.VarIndex]);
}

VarAssignPtr GetVarAssignPtr(int varType, bool isRef, int srcVarType, bool srcIsRef)
{
    if (isRef && srcIsRef) {
        switch (varType) {
        case BRACE_DATA_TYPE_BOOL:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarAssignFromToRefBool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefBoolInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefBoolInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefBoolInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefBoolInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefBoolUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefBoolUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefBoolUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefBoolUint64;
            }
        case BRACE_DATA_TYPE_INT8:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromToRefInt8Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarAssignFromToRefInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefInt8Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefInt8Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefInt8Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefInt8Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefInt8Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefInt8Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefInt8Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromToRefInt8Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromToRefInt8Double;
            }
        case BRACE_DATA_TYPE_INT16:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromToRefInt16Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefInt16Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarAssignFromToRefInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefInt16Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefInt16Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefInt16Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefInt16Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefInt16Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefInt16Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromToRefInt16Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromToRefInt16Double;
            }
        case BRACE_DATA_TYPE_INT32:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromToRefInt32Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefInt32Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefInt32Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarAssignFromToRefInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefInt32Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefInt32Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefInt32Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefInt32Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefInt32Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromToRefInt32Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromToRefInt32Double;
            }
        case BRACE_DATA_TYPE_INT64:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromToRefInt64Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefInt64Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefInt64Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefInt64Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarAssignFromToRefInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefInt64Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefInt64Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefInt64Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefInt64Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromToRefInt64Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromToRefInt64Double;
            }
        case BRACE_DATA_TYPE_UINT8:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromToRefUint8Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefUint8Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefUint8Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefUint8Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefUint8Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarAssignFromToRefUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefUint8Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefUint8Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefUint8Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromToRefUint8Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromToRefUint8Double;
            }
        case BRACE_DATA_TYPE_UINT16:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromToRefUint16Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefUint16Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefUint16Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefUint16Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefUint16Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefUint16Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarAssignFromToRefUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefUint16Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefUint16Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromToRefUint16Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromToRefUint16Double;
            }
        case BRACE_DATA_TYPE_UINT32:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromToRefUint32Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefUint32Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefUint32Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefUint32Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefUint32Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefUint32Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefUint32Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarAssignFromToRefUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefUint32Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromToRefUint32Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromToRefUint32Double;
            }
        case BRACE_DATA_TYPE_UINT64:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromToRefUint64Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefUint64Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefUint64Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefUint64Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefUint64Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefUint64Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefUint64Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefUint64Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarAssignFromToRefUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromToRefUint64Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromToRefUint64Double;
            }
        case BRACE_DATA_TYPE_FLOAT:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefFloatInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefFloatInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefFloatInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefFloatInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefFloatUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefFloatUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefFloatUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefFloatUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarAssignFromToRefFloat;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromToRefFloatDouble;
            }
        case BRACE_DATA_TYPE_DOUBLE:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromToRefDoubleInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromToRefDoubleInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromToRefDoubleInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromToRefDoubleInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromToRefDoubleUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromToRefDoubleUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromToRefDoubleUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromToRefDoubleUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromToRefDoubleFloat;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarAssignFromToRefDouble;
            }
        case BRACE_DATA_TYPE_STRING: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_STRING:
                return VarAssignFromToRefString;
            }
        }break;
        case BRACE_DATA_TYPE_OBJECT: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_OBJECT:
                return VarAssignFromToRefObject;
            }
        }break;
        }
    }
    else if (srcIsRef) {
        switch (varType) {
        case BRACE_DATA_TYPE_BOOL:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarAssignFromRefBool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefBoolInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefBoolInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefBoolInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefBoolInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefBoolUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefBoolUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefBoolUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefBoolUint64;
            }
        case BRACE_DATA_TYPE_INT8:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromRefInt8Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarAssignFromRefInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefInt8Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefInt8Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefInt8Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefInt8Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefInt8Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefInt8Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefInt8Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromRefInt8Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromRefInt8Double;
            }
        case BRACE_DATA_TYPE_INT16:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromRefInt16Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefInt16Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarAssignFromRefInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefInt16Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefInt16Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefInt16Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefInt16Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefInt16Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefInt16Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromRefInt16Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromRefInt16Double;
            }
        case BRACE_DATA_TYPE_INT32:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromRefInt32Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefInt32Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefInt32Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarAssignFromRefInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefInt32Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefInt32Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefInt32Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefInt32Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefInt32Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromRefInt32Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromRefInt32Double;
            }
        case BRACE_DATA_TYPE_INT64:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromRefInt64Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefInt64Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefInt64Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefInt64Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarAssignFromRefInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefInt64Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefInt64Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefInt64Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefInt64Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromRefInt64Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromRefInt64Double;
            }
        case BRACE_DATA_TYPE_UINT8:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromRefUint8Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefUint8Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefUint8Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefUint8Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefUint8Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarAssignFromRefUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefUint8Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefUint8Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefUint8Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromRefUint8Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromRefUint8Double;
            }
        case BRACE_DATA_TYPE_UINT16:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromRefUint16Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefUint16Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefUint16Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefUint16Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefUint16Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefUint16Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarAssignFromRefUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefUint16Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefUint16Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromRefUint16Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromRefUint16Double;
            }
        case BRACE_DATA_TYPE_UINT32:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromRefUint32Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefUint32Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefUint32Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefUint32Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefUint32Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefUint32Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefUint32Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarAssignFromRefUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefUint32Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromRefUint32Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromRefUint32Double;
            }
        case BRACE_DATA_TYPE_UINT64:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignFromRefUint64Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefUint64Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefUint64Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefUint64Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefUint64Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefUint64Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefUint64Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefUint64Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarAssignFromRefUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromRefUint64Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromRefUint64Double;
            }
        case BRACE_DATA_TYPE_FLOAT:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefFloatInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefFloatInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefFloatInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefFloatInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefFloatUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefFloatUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefFloatUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefFloatUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarAssignFromRefFloat;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignFromRefFloatDouble;
            }
        case BRACE_DATA_TYPE_DOUBLE:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignFromRefDoubleInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignFromRefDoubleInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignFromRefDoubleInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignFromRefDoubleInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignFromRefDoubleUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignFromRefDoubleUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignFromRefDoubleUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignFromRefDoubleUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignFromRefDoubleFloat;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarAssignFromRefDouble;
            }
        case BRACE_DATA_TYPE_STRING: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_STRING:
                return VarAssignFromRefString;
            }
        }break;
        case BRACE_DATA_TYPE_OBJECT: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_OBJECT:
                return VarAssignFromRefObject;
            }
        }break;
        }
    }
    else if (isRef) {
        switch (varType) {
        case BRACE_DATA_TYPE_BOOL:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarAssignToRefBool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefBoolInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefBoolInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefBoolInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefBoolInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefBoolUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefBoolUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefBoolUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefBoolUint64;
            }
        case BRACE_DATA_TYPE_INT8:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignToRefInt8Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarAssignToRefInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefInt8Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefInt8Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefInt8Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefInt8Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefInt8Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefInt8Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefInt8Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignToRefInt8Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignToRefInt8Double;
            }
        case BRACE_DATA_TYPE_INT16:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignToRefInt16Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefInt16Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarAssignToRefInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefInt16Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefInt16Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefInt16Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefInt16Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefInt16Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefInt16Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignToRefInt16Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignToRefInt16Double;
            }
        case BRACE_DATA_TYPE_INT32:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignToRefInt32Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefInt32Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefInt32Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarAssignToRefInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefInt32Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefInt32Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefInt32Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefInt32Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefInt32Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignToRefInt32Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignToRefInt32Double;
            }
        case BRACE_DATA_TYPE_INT64:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignToRefInt64Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefInt64Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefInt64Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefInt64Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarAssignToRefInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefInt64Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefInt64Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefInt64Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefInt64Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignToRefInt64Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignToRefInt64Double;
            }
        case BRACE_DATA_TYPE_UINT8:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignToRefUint8Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefUint8Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefUint8Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefUint8Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefUint8Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarAssignToRefUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefUint8Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefUint8Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefUint8Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignToRefUint8Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignToRefUint8Double;
            }
        case BRACE_DATA_TYPE_UINT16:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignToRefUint16Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefUint16Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefUint16Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefUint16Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefUint16Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefUint16Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarAssignToRefUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefUint16Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefUint16Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignToRefUint16Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignToRefUint16Double;
            }
        case BRACE_DATA_TYPE_UINT32:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignToRefUint32Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefUint32Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefUint32Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefUint32Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefUint32Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefUint32Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefUint32Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarAssignToRefUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefUint32Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignToRefUint32Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignToRefUint32Double;
            }
        case BRACE_DATA_TYPE_UINT64:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_BOOL:
                return VarCastAssignToRefUint64Bool;
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefUint64Int8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefUint64Int16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefUint64Int32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefUint64Int64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefUint64Uint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefUint64Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefUint64Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarAssignToRefUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignToRefUint64Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignToRefUint64Double;
            }
        case BRACE_DATA_TYPE_FLOAT:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefFloatInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefFloatInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefFloatInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefFloatInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefFloatUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefFloatUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefFloatUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefFloatUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarAssignToRefFloat;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignToRefFloatDouble;
            }
        case BRACE_DATA_TYPE_DOUBLE:
            switch (srcVarType) {
            case BRACE_DATA_TYPE_INT8:
                return VarCastAssignToRefDoubleInt8;
            case BRACE_DATA_TYPE_INT16:
                return VarCastAssignToRefDoubleInt16;
            case BRACE_DATA_TYPE_INT32:
                return VarCastAssignToRefDoubleInt32;
            case BRACE_DATA_TYPE_INT64:
                return VarCastAssignToRefDoubleInt64;
            case BRACE_DATA_TYPE_UINT8:
                return VarCastAssignToRefDoubleUint8;
            case BRACE_DATA_TYPE_UINT16:
                return VarCastAssignToRefDoubleUint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignToRefDoubleUint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignToRefDoubleUint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignToRefDoubleFloat;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarAssignToRefDouble;
            }
        case BRACE_DATA_TYPE_STRING: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_STRING:
                return VarAssignToRefString;
            }
        }break;
        case BRACE_DATA_TYPE_OBJECT: {
            switch (srcVarType) {
            case BRACE_DATA_TYPE_OBJECT:
                return VarAssignToRefObject;
            }
        }break;
        }
    }
    else {
        switch (varType) {
        case BRACE_DATA_TYPE_BOOL:
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
        case BRACE_DATA_TYPE_INT8:
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
        case BRACE_DATA_TYPE_INT16:
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
        case BRACE_DATA_TYPE_INT32:
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
        case BRACE_DATA_TYPE_INT64:
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
        case BRACE_DATA_TYPE_UINT8:
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
                return VarCastAssignUint8Uint16;
            case BRACE_DATA_TYPE_UINT32:
                return VarCastAssignUint8Uint32;
            case BRACE_DATA_TYPE_UINT64:
                return VarCastAssignUint8Uint64;
            case BRACE_DATA_TYPE_FLOAT:
                return VarCastAssignUint8Float;
            case BRACE_DATA_TYPE_DOUBLE:
                return VarCastAssignUint8Double;
            }
        case BRACE_DATA_TYPE_UINT16:
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
        case BRACE_DATA_TYPE_UINT32:
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
        case BRACE_DATA_TYPE_UINT64:
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
        case BRACE_DATA_TYPE_FLOAT:
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
        case BRACE_DATA_TYPE_DOUBLE:
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
    }
    return nullptr;
}
const char* GetDataTypeName(int type)
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
    case BRACE_DATA_TYPE_REF:
        return "reference";
    default:
        return "unknown";
    }
}
int GetDataType(const std::string& typeName)
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
bool VarGetBoolean(VariableInfo& info, int type, int index)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        return VarGetBoolean(*refInfo.Vars, refInfo.Type, refInfo.VarIndex);
    }
    }
    return false;
}
int64_t VarGetI64(VariableInfo& info, int type, int index)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        return VarGetI64(*refInfo.Vars, refInfo.Type, refInfo.VarIndex);
    }
    }
    return 0;
}
uint64_t VarGetU64(VariableInfo& info, int type, int index)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        return VarGetU64(*refInfo.Vars, refInfo.Type, refInfo.VarIndex);
    }
    }
    return 0;
}
double VarGetF64(VariableInfo& info, int type, int index)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        return VarGetF64(*refInfo.Vars, refInfo.Type, refInfo.VarIndex);
    }
    }
    return 0;
}
std::string VarGetStr(VariableInfo& info, int type, int index)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        return VarGetStr(*refInfo.Vars, refInfo.Type, refInfo.VarIndex);
    }
    }
    return std::string();
}
void VarSetBoolean(VariableInfo& info, int type, int index, bool val)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        VarSetBoolean(*refInfo.Vars, refInfo.Type, refInfo.VarIndex, val);
        break;
    }
    }
}
void VarSetI64(VariableInfo& info, int type, int index, int64_t val)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        VarSetI64(*refInfo.Vars, refInfo.Type, refInfo.VarIndex, val);
        break;
    }
    }
}
void VarSetU64(VariableInfo& info, int type, int index, uint64_t val)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        VarSetU64(*refInfo.Vars, refInfo.Type, refInfo.VarIndex, val);
        break;
    }
    }
}
void VarSetF64(VariableInfo& info, int type, int index, double val)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        VarSetF64(*refInfo.Vars, refInfo.Type, refInfo.VarIndex, val);
        break;
    }
    }
}
void VarSetStr(VariableInfo& info, int type, int index, const std::string& val)
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
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        VarSetStr(*refInfo.Vars, refInfo.Type, refInfo.VarIndex, val);
        break;
    }
    }
}
void VarSetStr(VariableInfo& info, int type, int index, std::string&& val)
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
        info.StringVars[index] = std::move(val);
        break;
    case BRACE_DATA_TYPE_REF: {
        auto& refInfo = info.ReferenceVars[index];
        VarSetStr(*refInfo.Vars, refInfo.Type, refInfo.VarIndex, std::move(val));
        break;
    }
    }
}

static inline bool NeedStringArithUnit(int type1, int type2)
{
    int type = GetMaxType(type1, type2);
    if (type >= BRACE_DATA_TYPE_STRING)
        return true;
    else
        return false;
}
static inline bool NeedFloatArithUnit(int type1, int type2)
{
    int type = GetMaxType(type1, type2);
    if (type >= BRACE_DATA_TYPE_FLOAT)
        return true;
    else
        return false;
}
static inline bool NeedUnsignedArithUnit(int type1, int type2)
{
    int type = GetMaxType(type1, type2);
    if (type >= BRACE_DATA_TYPE_UINT64) {
        return true;
    }
    else if (IsUnsignedType(type1) && IsUnsignedType(type2)) {
        return true;
    }
    return false;
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
    case BRACE_DATA_TYPE_REF: {
        switch (srcType) {
        case BRACE_DATA_TYPE_REF:
            return true;
        }
    }break;
    }
    return false;
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