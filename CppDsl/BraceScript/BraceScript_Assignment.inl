#ifndef BRACE_SCRIPT_INC
#include "BraceScript.h"
#include <stdexcept>
#include <sstream>
#include <algorithm>
#include <limits>
#endif

namespace Brace
{
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
        info.NumericVars[destIndex].BoolVal = srcInfo.NumericVars[srcIndex].BoolVal;
    }
    static inline void VarAssignInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = srcInfo.NumericVars[srcIndex].Int8Val;
    }
    static inline void VarAssignInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = srcInfo.NumericVars[srcIndex].Int16Val;
    }
    static inline void VarAssignInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = srcInfo.NumericVars[srcIndex].Int32Val;
    }
    static inline void VarAssignInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = srcInfo.NumericVars[srcIndex].Int64Val;
    }
    static inline void VarAssignUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = srcInfo.NumericVars[srcIndex].UInt8Val;
    }
    static inline void VarAssignUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = srcInfo.NumericVars[srcIndex].UInt16Val;
    }
    static inline void VarAssignUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = srcInfo.NumericVars[srcIndex].UInt32Val;
    }
    static inline void VarAssignUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = srcInfo.NumericVars[srcIndex].UInt64Val;
    }
    static inline void VarAssignFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = srcInfo.NumericVars[srcIndex].FloatVal;
    }
    static inline void VarAssignDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = srcInfo.NumericVars[srcIndex].DoubleVal;
    }
    static inline void VarAssignFromRefBool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].BoolVal = sri.Vars->NumericVars[sri.VarIndex].BoolVal;
    }
    static inline void VarAssignFromRefInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = sri.Vars->NumericVars[sri.VarIndex].Int8Val;
    }
    static inline void VarAssignFromRefInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = sri.Vars->NumericVars[sri.VarIndex].Int16Val;
    }
    static inline void VarAssignFromRefInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = sri.Vars->NumericVars[sri.VarIndex].Int32Val;
    }
    static inline void VarAssignFromRefInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = sri.Vars->NumericVars[sri.VarIndex].Int64Val;
    }
    static inline void VarAssignFromRefUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = sri.Vars->NumericVars[sri.VarIndex].UInt8Val;
    }
    static inline void VarAssignFromRefUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = sri.Vars->NumericVars[sri.VarIndex].UInt16Val;
    }
    static inline void VarAssignFromRefUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = sri.Vars->NumericVars[sri.VarIndex].UInt32Val;
    }
    static inline void VarAssignFromRefUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = sri.Vars->NumericVars[sri.VarIndex].UInt64Val;
    }
    static inline void VarAssignFromRefFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = sri.Vars->NumericVars[sri.VarIndex].FloatVal;
    }
    static inline void VarAssignFromRefDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = sri.Vars->NumericVars[sri.VarIndex].DoubleVal;
    }
    static inline void VarAssignToRefBool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = srcInfo.NumericVars[srcIndex].BoolVal;
    }
    static inline void VarAssignToRefInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = srcInfo.NumericVars[srcIndex].Int8Val;
    }
    static inline void VarAssignToRefInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = srcInfo.NumericVars[srcIndex].Int16Val;
    }
    static inline void VarAssignToRefInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = srcInfo.NumericVars[srcIndex].Int32Val;
    }
    static inline void VarAssignToRefInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = srcInfo.NumericVars[srcIndex].Int64Val;
    }
    static inline void VarAssignToRefUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = srcInfo.NumericVars[srcIndex].UInt8Val;
    }
    static inline void VarAssignToRefUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = srcInfo.NumericVars[srcIndex].UInt16Val;
    }
    static inline void VarAssignToRefUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = srcInfo.NumericVars[srcIndex].UInt32Val;
    }
    static inline void VarAssignToRefUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = srcInfo.NumericVars[srcIndex].UInt64Val;
    }
    static inline void VarAssignToRefFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = srcInfo.NumericVars[srcIndex].FloatVal;
    }
    static inline void VarAssignToRefDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = srcInfo.NumericVars[srcIndex].DoubleVal;
    }
    static inline void VarAssignFromToRefBool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = sri.Vars->NumericVars[sri.VarIndex].BoolVal;
    }
    static inline void VarAssignFromToRefInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = sri.Vars->NumericVars[sri.VarIndex].Int8Val;
    }
    static inline void VarAssignFromToRefInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = sri.Vars->NumericVars[sri.VarIndex].Int16Val;
    }
    static inline void VarAssignFromToRefInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = sri.Vars->NumericVars[sri.VarIndex].Int32Val;
    }
    static inline void VarAssignFromToRefInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = sri.Vars->NumericVars[sri.VarIndex].Int64Val;
    }
    static inline void VarAssignFromToRefUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = sri.Vars->NumericVars[sri.VarIndex].UInt8Val;
    }
    static inline void VarAssignFromToRefUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = sri.Vars->NumericVars[sri.VarIndex].UInt16Val;
    }
    static inline void VarAssignFromToRefUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = sri.Vars->NumericVars[sri.VarIndex].UInt32Val;
    }
    static inline void VarAssignFromToRefUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = sri.Vars->NumericVars[sri.VarIndex].UInt64Val;
    }
    static inline void VarAssignFromToRefFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = sri.Vars->NumericVars[sri.VarIndex].FloatVal;
    }
    static inline void VarAssignFromToRefDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = sri.Vars->NumericVars[sri.VarIndex].DoubleVal;
    }
    static inline void VarAssignString(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.StringVars[destIndex] = srcInfo.StringVars[srcIndex];
    }
    static inline void VarAssignObject(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.ObjectVars[destIndex] = srcInfo.ObjectVars[srcIndex];
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
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignBoolInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignBoolInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignBoolInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignBoolUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignBoolUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignBoolUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignBoolUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignInt8UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignInt8UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignInt8UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignInt8UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignInt16UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignInt16UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignInt16UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignInt16UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignInt32UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignInt32UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignInt32UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignInt32UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignInt64UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignInt64UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignInt64UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignInt64UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignUInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignUInt8Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignUInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignUInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignUInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignUInt8UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignUInt8UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignUInt8UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignUInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignUInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignUInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignUInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignUInt16Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignUInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignUInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignUInt16UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignUInt16UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignUInt16UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignUInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignUInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignUInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignUInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignUInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignUInt32Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignUInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignUInt32UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignUInt32UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignUInt32UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignUInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignUInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignUInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignUInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignUInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignUInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignUInt64Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignUInt64UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignUInt64UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignUInt64UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignUInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignUInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignFloatInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignFloatInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignFloatInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignFloatInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignFloatUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignFloatUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignFloatUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignFloatUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignFloatDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignDoubleInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignDoubleInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignDoubleInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignDoubleInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignDoubleUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignDoubleUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignDoubleUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignDoubleUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignDoubleFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignFromRefBoolInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefBoolInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefBoolInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefBoolInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefBoolUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefBoolUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefBoolUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefBoolUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromRefInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefInt8UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefInt8UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefInt8UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefInt8UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromRefInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromRefInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromRefInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefInt16UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefInt16UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefInt16UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefInt16UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromRefInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromRefInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromRefInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefInt32UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefInt32UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefInt32UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefInt32UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromRefInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromRefInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromRefInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefInt64UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefInt64UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefInt64UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefInt64UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromRefInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromRefUInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromRefUInt8Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefUInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefUInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefUInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefUInt8UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefUInt8UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefUInt8UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefUInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromRefUInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromRefUInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromRefUInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefUInt16Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefUInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefUInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefUInt16UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefUInt16UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefUInt16UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefUInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromRefUInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromRefUInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromRefUInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefUInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefUInt32Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefUInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefUInt32UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefUInt32UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefUInt32UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefUInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromRefUInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromRefUInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromRefUInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefUInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefUInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefUInt64Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefUInt64UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefUInt64UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefUInt64UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefUInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromRefUInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromRefFloatInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefFloatInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefFloatInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefFloatInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefFloatUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefFloatUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefFloatUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefFloatUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefFloatDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromRefDoubleInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromRefDoubleInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromRefDoubleInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromRefDoubleInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromRefDoubleUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromRefDoubleUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromRefDoubleUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromRefDoubleUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromRefDoubleFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignToRefBoolInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefBoolInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefBoolInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefBoolInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefBoolUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefBoolUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefBoolUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefBoolUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignToRefInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefInt8UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefInt8UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefInt8UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefInt8UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignToRefInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignToRefInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignToRefInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefInt16UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefInt16UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefInt16UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefInt16UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignToRefInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignToRefInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignToRefInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefInt32UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefInt32UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefInt32UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefInt32UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignToRefInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignToRefInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignToRefInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefInt64UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefInt64UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefInt64UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefInt64UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignToRefInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignToRefUInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignToRefUInt8Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefUInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefUInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefUInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefUInt8UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefUInt8UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefUInt8UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefUInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignToRefUInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignToRefUInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignToRefUInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefUInt16Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefUInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefUInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefUInt16UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefUInt16UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefUInt16UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefUInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignToRefUInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignToRefUInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignToRefUInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefUInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefUInt32Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefUInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefUInt32UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefUInt32UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefUInt32UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefUInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignToRefUInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignToRefUInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].BoolVal);
    }
    static inline void VarCastAssignToRefUInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefUInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefUInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefUInt64Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefUInt64UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefUInt64UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefUInt64UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefUInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignToRefUInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignToRefFloatInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefFloatInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefFloatInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefFloatInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefFloatUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefFloatUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefFloatUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefFloatUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefFloatDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(srcInfo.NumericVars[srcIndex].DoubleVal);
    }
    static inline void VarCastAssignToRefDoubleInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].Int8Val);
    }
    static inline void VarCastAssignToRefDoubleInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].Int16Val);
    }
    static inline void VarCastAssignToRefDoubleInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].Int32Val);
    }
    static inline void VarCastAssignToRefDoubleInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].Int64Val);
    }
    static inline void VarCastAssignToRefDoubleUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].UInt8Val);
    }
    static inline void VarCastAssignToRefDoubleUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].UInt16Val);
    }
    static inline void VarCastAssignToRefDoubleUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].UInt32Val);
    }
    static inline void VarCastAssignToRefDoubleUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].UInt64Val);
    }
    static inline void VarCastAssignToRefDoubleFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(srcInfo.NumericVars[srcIndex].FloatVal);
    }
    static inline void VarCastAssignFromToRefBoolInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefBoolInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefBoolInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefBoolInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefBoolUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefBoolUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefBoolUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefBoolUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].BoolVal = static_cast<bool>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromToRefInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefInt8UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefInt8UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefInt8UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefInt8UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromToRefInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int8Val = static_cast<int8_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromToRefInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromToRefInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefInt16UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefInt16UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefInt16UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefInt16UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromToRefInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int16Val = static_cast<int16_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromToRefInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromToRefInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefInt32UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefInt32UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefInt32UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefInt32UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromToRefInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int32Val = static_cast<int32_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromToRefInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromToRefInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefInt64UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefInt64UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefInt64UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefInt64UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromToRefInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].Int64Val = static_cast<int64_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromToRefUInt8Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromToRefUInt8Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefUInt8Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefUInt8Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefUInt8Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefUInt8UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefUInt8UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefUInt8UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefUInt8Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromToRefUInt8Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt8Val = static_cast<uint8_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromToRefUInt16Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromToRefUInt16Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefUInt16Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefUInt16Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefUInt16Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefUInt16UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefUInt16UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefUInt16UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefUInt16Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromToRefUInt16Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt16Val = static_cast<uint16_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromToRefUInt32Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromToRefUInt32Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefUInt32Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefUInt32Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefUInt32Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefUInt32UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefUInt32UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefUInt32UInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefUInt32Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromToRefUInt32Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt32Val = static_cast<uint32_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromToRefUInt64Bool(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].BoolVal);
    }
    static inline void VarCastAssignFromToRefUInt64Int8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefUInt64Int16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefUInt64Int32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefUInt64Int64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefUInt64UInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefUInt64UInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefUInt64UInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefUInt64Float(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
    }
    static inline void VarCastAssignFromToRefUInt64Double(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].UInt64Val = static_cast<uint64_t>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromToRefFloatInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefFloatInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefFloatInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefFloatInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefFloatUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefFloatUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefFloatUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefFloatUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefFloatDouble(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].FloatVal = static_cast<float>(sri.Vars->NumericVars[sri.VarIndex].DoubleVal);
    }
    static inline void VarCastAssignFromToRefDoubleInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].Int8Val);
    }
    static inline void VarCastAssignFromToRefDoubleInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].Int16Val);
    }
    static inline void VarCastAssignFromToRefDoubleInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].Int32Val);
    }
    static inline void VarCastAssignFromToRefDoubleInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].Int64Val);
    }
    static inline void VarCastAssignFromToRefDoubleUInt8(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].UInt8Val);
    }
    static inline void VarCastAssignFromToRefDoubleUInt16(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].UInt16Val);
    }
    static inline void VarCastAssignFromToRefDoubleUInt32(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].UInt32Val);
    }
    static inline void VarCastAssignFromToRefDoubleUInt64(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].UInt64Val);
    }
    static inline void VarCastAssignFromToRefDoubleFloat(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].DoubleVal = static_cast<double>(sri.Vars->NumericVars[sri.VarIndex].FloatVal);
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
                    return VarCastAssignFromToRefBoolUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefBoolUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefBoolUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefBoolUInt64;
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
                    return VarCastAssignFromToRefInt8UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefInt8UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefInt8UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefInt8UInt64;
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
                    return VarCastAssignFromToRefInt16UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefInt16UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefInt16UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefInt16UInt64;
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
                    return VarCastAssignFromToRefInt32UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefInt32UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefInt32UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefInt32UInt64;
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
                    return VarCastAssignFromToRefInt64UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefInt64UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefInt64UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefInt64UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromToRefInt64Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromToRefInt64Double;
                }
            case BRACE_DATA_TYPE_UINT8:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignFromToRefUInt8Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignFromToRefUInt8Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignFromToRefUInt8Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignFromToRefUInt8Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignFromToRefUInt8Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarAssignFromToRefUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefUInt8UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefUInt8UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefUInt8UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromToRefUInt8Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromToRefUInt8Double;
                }
            case BRACE_DATA_TYPE_UINT16:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignFromToRefUInt16Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignFromToRefUInt16Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignFromToRefUInt16Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignFromToRefUInt16Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignFromToRefUInt16Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignFromToRefUInt16UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarAssignFromToRefUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefUInt16UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefUInt16UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromToRefUInt16Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromToRefUInt16Double;
                }
            case BRACE_DATA_TYPE_UINT32:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignFromToRefUInt32Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignFromToRefUInt32Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignFromToRefUInt32Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignFromToRefUInt32Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignFromToRefUInt32Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignFromToRefUInt32UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefUInt32UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarAssignFromToRefUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefUInt32UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromToRefUInt32Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromToRefUInt32Double;
                }
            case BRACE_DATA_TYPE_UINT64:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignFromToRefUInt64Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignFromToRefUInt64Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignFromToRefUInt64Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignFromToRefUInt64Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignFromToRefUInt64Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignFromToRefUInt64UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefUInt64UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefUInt64UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarAssignFromToRefUInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromToRefUInt64Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromToRefUInt64Double;
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
                    return VarCastAssignFromToRefFloatUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefFloatUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefFloatUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefFloatUInt64;
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
                    return VarCastAssignFromToRefDoubleUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromToRefDoubleUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromToRefDoubleUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromToRefDoubleUInt64;
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
                    return VarCastAssignFromRefBoolUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefBoolUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefBoolUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefBoolUInt64;
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
                    return VarCastAssignFromRefInt8UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefInt8UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefInt8UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefInt8UInt64;
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
                    return VarCastAssignFromRefInt16UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefInt16UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefInt16UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefInt16UInt64;
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
                    return VarCastAssignFromRefInt32UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefInt32UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefInt32UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefInt32UInt64;
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
                    return VarCastAssignFromRefInt64UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefInt64UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefInt64UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefInt64UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromRefInt64Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromRefInt64Double;
                }
            case BRACE_DATA_TYPE_UINT8:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignFromRefUInt8Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignFromRefUInt8Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignFromRefUInt8Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignFromRefUInt8Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignFromRefUInt8Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarAssignFromRefUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefUInt8UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefUInt8UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefUInt8UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromRefUInt8Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromRefUInt8Double;
                }
            case BRACE_DATA_TYPE_UINT16:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignFromRefUInt16Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignFromRefUInt16Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignFromRefUInt16Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignFromRefUInt16Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignFromRefUInt16Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignFromRefUInt16UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarAssignFromRefUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefUInt16UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefUInt16UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromRefUInt16Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromRefUInt16Double;
                }
            case BRACE_DATA_TYPE_UINT32:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignFromRefUInt32Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignFromRefUInt32Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignFromRefUInt32Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignFromRefUInt32Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignFromRefUInt32Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignFromRefUInt32UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefUInt32UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarAssignFromRefUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefUInt32UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromRefUInt32Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromRefUInt32Double;
                }
            case BRACE_DATA_TYPE_UINT64:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignFromRefUInt64Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignFromRefUInt64Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignFromRefUInt64Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignFromRefUInt64Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignFromRefUInt64Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignFromRefUInt64UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefUInt64UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefUInt64UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarAssignFromRefUInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignFromRefUInt64Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignFromRefUInt64Double;
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
                    return VarCastAssignFromRefFloatUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefFloatUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefFloatUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefFloatUInt64;
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
                    return VarCastAssignFromRefDoubleUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFromRefDoubleUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFromRefDoubleUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFromRefDoubleUInt64;
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
                    return VarCastAssignToRefBoolUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefBoolUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefBoolUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefBoolUInt64;
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
                    return VarCastAssignToRefInt8UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefInt8UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefInt8UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefInt8UInt64;
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
                    return VarCastAssignToRefInt16UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefInt16UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefInt16UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefInt16UInt64;
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
                    return VarCastAssignToRefInt32UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefInt32UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefInt32UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefInt32UInt64;
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
                    return VarCastAssignToRefInt64UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefInt64UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefInt64UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefInt64UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignToRefInt64Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignToRefInt64Double;
                }
            case BRACE_DATA_TYPE_UINT8:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignToRefUInt8Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignToRefUInt8Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignToRefUInt8Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignToRefUInt8Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignToRefUInt8Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarAssignToRefUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefUInt8UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefUInt8UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefUInt8UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignToRefUInt8Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignToRefUInt8Double;
                }
            case BRACE_DATA_TYPE_UINT16:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignToRefUInt16Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignToRefUInt16Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignToRefUInt16Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignToRefUInt16Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignToRefUInt16Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignToRefUInt16UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarAssignToRefUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefUInt16UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefUInt16UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignToRefUInt16Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignToRefUInt16Double;
                }
            case BRACE_DATA_TYPE_UINT32:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignToRefUInt32Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignToRefUInt32Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignToRefUInt32Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignToRefUInt32Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignToRefUInt32Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignToRefUInt32UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefUInt32UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarAssignToRefUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefUInt32UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignToRefUInt32Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignToRefUInt32Double;
                }
            case BRACE_DATA_TYPE_UINT64:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignToRefUInt64Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignToRefUInt64Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignToRefUInt64Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignToRefUInt64Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignToRefUInt64Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignToRefUInt64UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefUInt64UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefUInt64UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarAssignToRefUInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignToRefUInt64Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignToRefUInt64Double;
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
                    return VarCastAssignToRefFloatUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefFloatUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefFloatUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefFloatUInt64;
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
                    return VarCastAssignToRefDoubleUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignToRefDoubleUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignToRefDoubleUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignToRefDoubleUInt64;
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
                    return VarCastAssignBoolUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignBoolUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignBoolUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignBoolUInt64;
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
                    return VarCastAssignInt8UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignInt8UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignInt8UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignInt8UInt64;
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
                    return VarCastAssignInt16UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignInt16UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignInt16UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignInt16UInt64;
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
                    return VarCastAssignInt32UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignInt32UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignInt32UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignInt32UInt64;
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
                    return VarCastAssignInt64UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignInt64UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignInt64UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignInt64UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignInt64Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignInt64Double;
                }
            case BRACE_DATA_TYPE_UINT8:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignUInt8Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignUInt8Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignUInt8Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignUInt8Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignUInt8Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarAssignUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignUInt8UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignUInt8UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignUInt8UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignUInt8Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignUInt8Double;
                }
            case BRACE_DATA_TYPE_UINT16:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignUInt16Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignUInt16Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignUInt16Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignUInt16Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignUInt16Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignUInt16UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarAssignUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignUInt16UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignUInt16UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignUInt16Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignUInt16Double;
                }
            case BRACE_DATA_TYPE_UINT32:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignUInt32Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignUInt32Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignUInt32Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignUInt32Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignUInt32Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignUInt32UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignUInt32UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarAssignUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignUInt32UInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignUInt32Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignUInt32Double;
                }
            case BRACE_DATA_TYPE_UINT64:
                switch (srcVarType) {
                case BRACE_DATA_TYPE_BOOL:
                    return VarCastAssignUInt64Bool;
                case BRACE_DATA_TYPE_INT8:
                    return VarCastAssignUInt64Int8;
                case BRACE_DATA_TYPE_INT16:
                    return VarCastAssignUInt64Int16;
                case BRACE_DATA_TYPE_INT32:
                    return VarCastAssignUInt64Int32;
                case BRACE_DATA_TYPE_INT64:
                    return VarCastAssignUInt64Int64;
                case BRACE_DATA_TYPE_UINT8:
                    return VarCastAssignUInt64UInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignUInt64UInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignUInt64UInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarAssignUInt64;
                case BRACE_DATA_TYPE_FLOAT:
                    return VarCastAssignUInt64Float;
                case BRACE_DATA_TYPE_DOUBLE:
                    return VarCastAssignUInt64Double;
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
                    return VarCastAssignFloatUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignFloatUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignFloatUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignFloatUInt64;
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
                    return VarCastAssignDoubleUInt8;
                case BRACE_DATA_TYPE_UINT16:
                    return VarCastAssignDoubleUInt16;
                case BRACE_DATA_TYPE_UINT32:
                    return VarCastAssignDoubleUInt32;
                case BRACE_DATA_TYPE_UINT64:
                    return VarCastAssignDoubleUInt64;
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
            return info.NumericVars[index].BoolVal;
        case BRACE_DATA_TYPE_INT8:
            return info.NumericVars[index].Int8Val != 0;
        case BRACE_DATA_TYPE_INT16:
            return info.NumericVars[index].Int16Val != 0;
        case BRACE_DATA_TYPE_INT32:
            return info.NumericVars[index].Int32Val != 0;
        case BRACE_DATA_TYPE_INT64:
            return info.NumericVars[index].Int64Val != 0;
        case BRACE_DATA_TYPE_UINT8:
            return info.NumericVars[index].UInt8Val != 0;
        case BRACE_DATA_TYPE_UINT16:
            return info.NumericVars[index].UInt16Val != 0;
        case BRACE_DATA_TYPE_UINT32:
            return info.NumericVars[index].UInt32Val != 0;
        case BRACE_DATA_TYPE_UINT64:
            return info.NumericVars[index].UInt64Val != 0;
        case BRACE_DATA_TYPE_FLOAT:
            return info.NumericVars[index].FloatVal != 0;
        case BRACE_DATA_TYPE_DOUBLE:
            return info.NumericVars[index].DoubleVal != 0;
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
            return info.NumericVars[index].BoolVal ? 1 : 0;
        case BRACE_DATA_TYPE_INT8:
            return info.NumericVars[index].Int8Val;
        case BRACE_DATA_TYPE_INT16:
            return info.NumericVars[index].Int16Val;
        case BRACE_DATA_TYPE_INT32:
            return info.NumericVars[index].Int32Val;
        case BRACE_DATA_TYPE_INT64:
            return info.NumericVars[index].Int64Val;
        case BRACE_DATA_TYPE_UINT8:
            return info.NumericVars[index].UInt8Val;
        case BRACE_DATA_TYPE_UINT16:
            return info.NumericVars[index].UInt16Val;
        case BRACE_DATA_TYPE_UINT32:
            return info.NumericVars[index].UInt32Val;
        case BRACE_DATA_TYPE_UINT64:
            return static_cast<int64_t>(info.NumericVars[index].UInt64Val);
        case BRACE_DATA_TYPE_FLOAT:
            return static_cast<int64_t>(info.NumericVars[index].FloatVal);
        case BRACE_DATA_TYPE_DOUBLE:
            return static_cast<int64_t>(info.NumericVars[index].DoubleVal);
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
            return static_cast<uint64_t>(info.NumericVars[index].BoolVal ? 1 : 0);
        case BRACE_DATA_TYPE_INT8:
            return static_cast<uint64_t>(info.NumericVars[index].Int8Val);
        case BRACE_DATA_TYPE_INT16:
            return static_cast<uint64_t>(info.NumericVars[index].Int16Val);
        case BRACE_DATA_TYPE_INT32:
            return static_cast<uint64_t>(info.NumericVars[index].Int32Val);
        case BRACE_DATA_TYPE_INT64:
            return static_cast<uint64_t>(info.NumericVars[index].Int64Val);
        case BRACE_DATA_TYPE_UINT8:
            return info.NumericVars[index].UInt8Val;
        case BRACE_DATA_TYPE_UINT16:
            return info.NumericVars[index].UInt16Val;
        case BRACE_DATA_TYPE_UINT32:
            return info.NumericVars[index].UInt32Val;
        case BRACE_DATA_TYPE_UINT64:
            return info.NumericVars[index].UInt64Val;
        case BRACE_DATA_TYPE_FLOAT:
            return static_cast<uint64_t>(info.NumericVars[index].FloatVal);
        case BRACE_DATA_TYPE_DOUBLE:
            return static_cast<uint64_t>(info.NumericVars[index].DoubleVal);
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
            return info.NumericVars[index].BoolVal ? 1 : 0;
        case BRACE_DATA_TYPE_INT8:
            return info.NumericVars[index].Int8Val;
        case BRACE_DATA_TYPE_INT16:
            return info.NumericVars[index].Int16Val;
        case BRACE_DATA_TYPE_INT32:
            return info.NumericVars[index].Int32Val;
        case BRACE_DATA_TYPE_INT64:
            return static_cast<double>(info.NumericVars[index].Int64Val);
        case BRACE_DATA_TYPE_UINT8:
            return info.NumericVars[index].UInt8Val;
        case BRACE_DATA_TYPE_UINT16:
            return info.NumericVars[index].UInt16Val;
        case BRACE_DATA_TYPE_UINT32:
            return info.NumericVars[index].UInt32Val;
        case BRACE_DATA_TYPE_UINT64:
            return static_cast<double>(info.NumericVars[index].UInt64Val);
        case BRACE_DATA_TYPE_FLOAT:
            return info.NumericVars[index].FloatVal;
        case BRACE_DATA_TYPE_DOUBLE:
            return info.NumericVars[index].DoubleVal;
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
            return info.NumericVars[index].BoolVal ? "true" : "false";
        case BRACE_DATA_TYPE_INT8:
            return std::to_string(info.NumericVars[index].Int8Val);
        case BRACE_DATA_TYPE_INT16:
            return std::to_string(info.NumericVars[index].Int16Val);
        case BRACE_DATA_TYPE_INT32:
            return std::to_string(info.NumericVars[index].Int32Val);
        case BRACE_DATA_TYPE_INT64:
            return std::to_string(info.NumericVars[index].Int64Val);
        case BRACE_DATA_TYPE_UINT8:
            return std::to_string(info.NumericVars[index].UInt8Val);
        case BRACE_DATA_TYPE_UINT16:
            return std::to_string(info.NumericVars[index].UInt16Val);
        case BRACE_DATA_TYPE_UINT32:
            return std::to_string(info.NumericVars[index].UInt32Val);
        case BRACE_DATA_TYPE_UINT64:
            return std::to_string(info.NumericVars[index].UInt64Val);
        case BRACE_DATA_TYPE_FLOAT:
            return std::to_string(info.NumericVars[index].FloatVal);
        case BRACE_DATA_TYPE_DOUBLE:
            return std::to_string(info.NumericVars[index].DoubleVal);
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
            info.NumericVars[index].BoolVal = val;
            break;
        case BRACE_DATA_TYPE_INT8:
            info.NumericVars[index].Int8Val = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_INT16:
            info.NumericVars[index].Int16Val = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_INT32:
            info.NumericVars[index].Int32Val = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_INT64:
            info.NumericVars[index].Int64Val = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.NumericVars[index].UInt8Val = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.NumericVars[index].UInt16Val = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.NumericVars[index].UInt32Val = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.NumericVars[index].UInt64Val = val ? 1 : 0;
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.NumericVars[index].FloatVal = static_cast<float>(val ? 1 : 0);
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.NumericVars[index].DoubleVal = static_cast<double>(val ? 1 : 0);
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
            info.NumericVars[index].BoolVal = val != 0;
            break;
        case BRACE_DATA_TYPE_INT8:
            info.NumericVars[index].Int8Val = static_cast<int8_t>(val);
            break;
        case BRACE_DATA_TYPE_INT16:
            info.NumericVars[index].Int16Val = static_cast<int16_t>(val);
            break;
        case BRACE_DATA_TYPE_INT32:
            info.NumericVars[index].Int32Val = static_cast<int32_t>(val);
            break;
        case BRACE_DATA_TYPE_INT64:
            info.NumericVars[index].Int64Val = val;
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.NumericVars[index].UInt8Val = static_cast<uint8_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.NumericVars[index].UInt16Val = static_cast<uint16_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.NumericVars[index].UInt32Val = static_cast<uint32_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.NumericVars[index].UInt64Val = static_cast<uint64_t>(val);
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.NumericVars[index].FloatVal = static_cast<float>(val);
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.NumericVars[index].DoubleVal = static_cast<double>(val);
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
            info.NumericVars[index].BoolVal = val != 0;
            break;
        case BRACE_DATA_TYPE_INT8:
            info.NumericVars[index].Int8Val = static_cast<int8_t>(val);
            break;
        case BRACE_DATA_TYPE_INT16:
            info.NumericVars[index].Int16Val = static_cast<int16_t>(val);
            break;
        case BRACE_DATA_TYPE_INT32:
            info.NumericVars[index].Int32Val = static_cast<int32_t>(val);
            break;
        case BRACE_DATA_TYPE_INT64:
            info.NumericVars[index].Int64Val = static_cast<int64_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.NumericVars[index].UInt8Val = static_cast<uint8_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.NumericVars[index].UInt16Val = static_cast<uint16_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.NumericVars[index].UInt32Val = static_cast<uint32_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.NumericVars[index].UInt64Val = val;
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.NumericVars[index].FloatVal = static_cast<float>(val);
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.NumericVars[index].DoubleVal = static_cast<double>(val);
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
            info.NumericVars[index].BoolVal = val != 0;
            break;
        case BRACE_DATA_TYPE_INT8:
            info.NumericVars[index].Int8Val = static_cast<int8_t>(val);
            break;
        case BRACE_DATA_TYPE_INT16:
            info.NumericVars[index].Int16Val = static_cast<int16_t>(val);
            break;
        case BRACE_DATA_TYPE_INT32:
            info.NumericVars[index].Int32Val = static_cast<int32_t>(val);
            break;
        case BRACE_DATA_TYPE_INT64:
            info.NumericVars[index].Int64Val = static_cast<int64_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.NumericVars[index].UInt8Val = static_cast<uint8_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.NumericVars[index].UInt16Val = static_cast<uint16_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.NumericVars[index].UInt32Val = static_cast<uint32_t>(val);
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.NumericVars[index].UInt64Val = static_cast<uint64_t>(val);
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.NumericVars[index].FloatVal = static_cast<float>(val);
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.NumericVars[index].DoubleVal = static_cast<double>(val);
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
            info.NumericVars[index].BoolVal = val == "true";
            break;
        case BRACE_DATA_TYPE_INT8:
            info.NumericVars[index].Int8Val = static_cast<int8_t>(StrToInt32(val));
            break;
        case BRACE_DATA_TYPE_INT16:
            info.NumericVars[index].Int16Val = static_cast<int16_t>(StrToInt32(val));
            break;
        case BRACE_DATA_TYPE_INT32:
            info.NumericVars[index].Int32Val = StrToInt32(val);
            break;
        case BRACE_DATA_TYPE_INT64:
            info.NumericVars[index].Int64Val = StrToInt64(val);
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.NumericVars[index].UInt8Val = static_cast<uint8_t>(StrToUInt32(val));
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.NumericVars[index].UInt16Val = static_cast<uint16_t>(StrToUInt32(val));
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.NumericVars[index].UInt32Val = StrToUInt32(val);
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.NumericVars[index].UInt64Val = StrToUInt64(val);
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.NumericVars[index].FloatVal = static_cast<float>(StrToInt64(val));
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.NumericVars[index].DoubleVal = static_cast<double>(StrToInt64(val));
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
            info.NumericVars[index].BoolVal = val == "true";
            break;
        case BRACE_DATA_TYPE_INT8:
            info.NumericVars[index].Int8Val = static_cast<int8_t>(StrToInt32(val));
            break;
        case BRACE_DATA_TYPE_INT16:
            info.NumericVars[index].Int16Val = static_cast<int16_t>(StrToInt32(val));
            break;
        case BRACE_DATA_TYPE_INT32:
            info.NumericVars[index].Int32Val = StrToInt32(val);
            break;
        case BRACE_DATA_TYPE_INT64:
            info.NumericVars[index].Int64Val = StrToInt64(val);
            break;
        case BRACE_DATA_TYPE_UINT8:
            info.NumericVars[index].UInt8Val = static_cast<uint8_t>(StrToUInt32(val));
            break;
        case BRACE_DATA_TYPE_UINT16:
            info.NumericVars[index].UInt16Val = static_cast<uint16_t>(StrToUInt32(val));
            break;
        case BRACE_DATA_TYPE_UINT32:
            info.NumericVars[index].UInt32Val = StrToUInt32(val);
            break;
        case BRACE_DATA_TYPE_UINT64:
            info.NumericVars[index].UInt64Val = StrToUInt64(val);
            break;
        case BRACE_DATA_TYPE_FLOAT:
            info.NumericVars[index].FloatVal = static_cast<float>(StrToInt64(val));
            break;
        case BRACE_DATA_TYPE_DOUBLE:
            info.NumericVars[index].DoubleVal = static_cast<double>(StrToInt64(val));
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

    static constexpr inline bool NeedStringArithUnit(int type1, int type2)
    {
        int type = GetMaxType(type1, type2);
        if (type >= BRACE_DATA_TYPE_STRING)
            return true;
        else
            return false;
    }
    static constexpr inline bool NeedFloatArithUnit(int type1, int type2)
    {
        int type = GetMaxType(type1, type2);
        if (type >= BRACE_DATA_TYPE_FLOAT)
            return true;
        else
            return false;
    }
    static constexpr inline bool NeedUnsignedArithUnit(int type1, int type2)
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
    static constexpr inline bool CanAssign(int destType, int srcType)
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
}