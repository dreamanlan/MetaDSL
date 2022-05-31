class AddExp final : public BinaryArithLogicBaseExp
{
public:
    AddExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator +, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLBoolBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGDoubleBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGGStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLLStringBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteGLStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AddExp::ExecuteLGStringBoth, this);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteGGString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteLLString, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteGLString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteLGString, this);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AddExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars, m_LoadInfo2.VarIndex);
        VarSetString(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetString(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetString(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetString(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetStr(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetStr(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetStr(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetStr(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class SubExp final : public BinaryArithLogicBaseExp
{
public:
    SubExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator -, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&SubExp::ExecuteLGDoubleBoth, this);
                }

                break;
            }
        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&SubExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class MulExp final : public BinaryArithLogicBaseExp
{
public:
    MulExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator *, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&MulExp::ExecuteLGDoubleBoth, this);
                }

                break;
            }
        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&MulExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class DivExp final : public BinaryArithLogicBaseExp
{
public:
    DivExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator /, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&DivExp::ExecuteLGDoubleBoth, this);
                }

                break;
            }
        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&DivExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class ModExp final : public BinaryArithLogicBaseExp
{
public:
    ModExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator %, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&ModExp::ExecuteLGUInt64Both, this);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&ModExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&ModExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&ModExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&ModExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&ModExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&ModExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&ModExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&ModExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class LShiftExp final : public BinaryArithLogicBaseExp
{
public:
    LShiftExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator <<, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LShiftExp::ExecuteLGUInt64Both, this);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LShiftExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LShiftExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LShiftExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LShiftExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LShiftExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LShiftExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LShiftExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LShiftExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class RShiftExp final : public BinaryArithLogicBaseExp
{
public:
    RShiftExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator >>, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&RShiftExp::ExecuteLGUInt64Both, this);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&RShiftExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&RShiftExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&RShiftExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&RShiftExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&RShiftExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&RShiftExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&RShiftExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&RShiftExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class BitAndExp final : public BinaryArithLogicBaseExp
{
public:
    BitAndExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator &, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitAndExp::ExecuteLGUInt64Both, this);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitAndExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitAndExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitAndExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitAndExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitAndExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitAndExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitAndExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitAndExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class BitOrExp final : public BinaryArithLogicBaseExp
{
public:
    BitOrExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator |, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitOrExp::ExecuteLGUInt64Both, this);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitOrExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitOrExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitOrExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitOrExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitOrExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitOrExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitOrExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitOrExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class BitXorExp final : public BinaryArithLogicBaseExp
{
public:
    BitXorExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator ^, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&BitXorExp::ExecuteLGUInt64Both, this);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitXorExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitXorExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitXorExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitXorExp::ExecuteLGUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitXorExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitXorExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitXorExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&BitXorExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class GreatExp final : public BinaryArithLogicBaseExp
{
public:
    GreatExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator >, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLBoolBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGDoubleBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGGStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLLStringBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteGLStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatExp::ExecuteLGStringBoth, this);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteGGString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteLLString, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteGLString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteLGString, this);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteLGUInt, this);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class GreatEqualExp final : public BinaryArithLogicBaseExp
{
public:
    GreatEqualExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator >=, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLBoolBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGDoubleBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGGStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLLStringBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteGLStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&GreatEqualExp::ExecuteLGStringBoth, this);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteGGString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteLLString, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteGLString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteLGString, this);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteLGUInt, this);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&GreatEqualExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class LessExp final : public BinaryArithLogicBaseExp
{
public:
    LessExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator <, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLBoolBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGDoubleBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGGStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLLStringBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteGLStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessExp::ExecuteLGStringBoth, this);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteGGString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteLLString, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteGLString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteLGString, this);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteLGUInt, this);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class LessEqualExp final : public BinaryArithLogicBaseExp
{
public:
    LessEqualExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator <=, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLBoolBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGDoubleBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGGStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLLStringBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteGLStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&LessEqualExp::ExecuteLGStringBoth, this);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteGGString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteLLString, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteGLString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteLGString, this);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteLGUInt, this);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&LessEqualExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class EqualExp final : public BinaryArithLogicBaseExp
{
public:
    EqualExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator ==, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLBoolBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGDoubleBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGGStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLLStringBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteGLStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&EqualExp::ExecuteLGStringBoth, this);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteGGString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteLLString, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteGLString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteLGString, this);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteLGUInt, this);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&EqualExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class NotEqualExp final : public BinaryArithLogicBaseExp
{
public:
    NotEqualExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator !=, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLBoolBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGUInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLFloatBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLFloatBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGFloatBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLDoubleBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLDoubleBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGDoubleBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGGStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLLStringBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteGLStringBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&NotEqualExp::ExecuteLGStringBoth, this);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteGGString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteLLString, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteGLString, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteLGString, this);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteGGFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteLLFloat, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteGLFloat, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteLGFloat, this);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteGGUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteLLUInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteGLUInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteLGUInt, this);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteGGInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteLLInt, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteGLInt, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&NotEqualExp::ExecuteLGInt, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        float v1 = VarGetFloat(srcVars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        float v1 = VarGetFloat(srcVars1, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetDouble(srcVars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetDouble(srcVars1, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        const std::string& v1 = VarGetString(srcVars1, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        double v1 = VarGetF64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        double v1 = VarGetF64(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        std::string v1 = VarGetStr(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class AndExp final : public BinaryArithLogicBaseExp
{
public:
    AndExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator &&, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGGBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLLBoolBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGLBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLGBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&AndExp::ExecuteLGUInt64Both, this);
                }

                break;
            }
        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AndExp::ExecuteGGBool, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AndExp::ExecuteLLBool, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AndExp::ExecuteGLBool, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&AndExp::ExecuteLGBool, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGBool(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBoolean(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBool(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBoolean(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBool(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBoolean(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBool(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBoolean(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class OrExp final : public BinaryArithLogicBaseExp
{
public:
    OrExp(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator ||, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGGBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLLBoolBoth, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGLBoolBoth, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLGBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGGInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLLInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGLInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLGInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGGInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLLInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGLInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLGInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGGInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLLInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGLInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLGInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGGInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLLInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGLInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLGInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGGUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLLUInt8Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGLUInt8Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLGUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGGUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLLUInt16Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGLUInt16Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLGUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGGUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLLUInt32Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGLUInt32Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLGUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGGUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLLUInt64Both, this);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteGLUInt64Both, this);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&OrExp::ExecuteLGUInt64Both, this);
                }

                break;
            }
        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&OrExp::ExecuteGGBool, this);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&OrExp::ExecuteLLBool, this);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor = std::bind(&OrExp::ExecuteGLBool, this);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor = std::bind(&OrExp::ExecuteLGBool, this);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBool(srcVars1, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars1, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars1, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars1, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars1, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars1, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars1, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars1, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars1, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(srcVars2, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGGBool(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBoolean(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBool(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBoolean(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBool(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = *GlobalVariables();
        auto& srcVars2 = vars;
        bool v1 = VarGetBoolean(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBool(void) const
    {
        if (m_Op1)
            m_Op1();
        if (m_Op2)
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars1 = vars;
        auto& srcVars2 = *GlobalVariables();
        bool v1 = VarGetBoolean(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class BitNotExp final : public UnaryArithLogicBaseExp
{
public:
    BitNotExp(BraceScript& interpreter) :UnaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = load1.Type;
        if (resultType >= BRACE_DATA_TYPE_FLOAT) {
            std::stringstream ss;
            ss << "can't bit not type " << GetDataTypeName(m_LoadInfo1.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type >= BRACE_DATA_TYPE_INT8 && m_LoadInfo1.Type <= BRACE_DATA_TYPE_UINT64) {
            resultType = m_LoadInfo1.Type;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&BitNotExp::ExecuteGInt8Both, this);
                }
                else {
                    executor = std::bind(&BitNotExp::ExecuteLInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&BitNotExp::ExecuteGInt16Both, this);
                }
                else {
                    executor = std::bind(&BitNotExp::ExecuteLInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&BitNotExp::ExecuteGInt32Both, this);
                }
                else {
                    executor = std::bind(&BitNotExp::ExecuteLInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&BitNotExp::ExecuteGInt64Both, this);
                }
                else {
                    executor = std::bind(&BitNotExp::ExecuteLInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&BitNotExp::ExecuteGUInt8Both, this);
                }
                else {
                    executor = std::bind(&BitNotExp::ExecuteLUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&BitNotExp::ExecuteGUInt16Both, this);
                }
                else {
                    executor = std::bind(&BitNotExp::ExecuteLUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&BitNotExp::ExecuteGUInt32Both, this);
                }
                else {
                    executor = std::bind(&BitNotExp::ExecuteLUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&BitNotExp::ExecuteGUInt64Both, this);
                }
                else {
                    executor = std::bind(&BitNotExp::ExecuteLUInt64Both, this);
                }

                break;
            }
        }
        else if (IsUnsignedType(resultType)) {
            if (m_LoadInfo1.IsGlobal) {
                executor = std::bind(&BitNotExp::ExecuteGUInt, this);
            }
            else {
                executor = std::bind(&BitNotExp::ExecuteLUInt, this);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal) {
                executor = std::bind(&BitNotExp::ExecuteGInt, this);
            }
            else {
                executor = std::bind(&BitNotExp::ExecuteLInt, this);
            }

        }
        return true;
    }
private:
    int ExecuteGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

};
class NotExp final : public UnaryArithLogicBaseExp
{
public:
    NotExp(BraceScript& interpreter) :UnaryArithLogicBaseExp(interpreter)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = load1.Type;
        if (resultType >= BRACE_DATA_TYPE_FLOAT) {
            std::stringstream ss;
            ss << "can't bit not type " << GetDataTypeName(load1.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (m_LoadInfo1.Type <= BRACE_DATA_TYPE_UINT64) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (m_LoadInfo1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&NotExp::ExecuteGBoolBoth, this);
                }
                else {
                    executor = std::bind(&NotExp::ExecuteLBoolBoth, this);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&NotExp::ExecuteGInt8Both, this);
                }
                else {
                    executor = std::bind(&NotExp::ExecuteLInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&NotExp::ExecuteGInt16Both, this);
                }
                else {
                    executor = std::bind(&NotExp::ExecuteLInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&NotExp::ExecuteGInt32Both, this);
                }
                else {
                    executor = std::bind(&NotExp::ExecuteLInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&NotExp::ExecuteGInt64Both, this);
                }
                else {
                    executor = std::bind(&NotExp::ExecuteLInt64Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&NotExp::ExecuteGUInt8Both, this);
                }
                else {
                    executor = std::bind(&NotExp::ExecuteLUInt8Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&NotExp::ExecuteGUInt16Both, this);
                }
                else {
                    executor = std::bind(&NotExp::ExecuteLUInt16Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&NotExp::ExecuteGUInt32Both, this);
                }
                else {
                    executor = std::bind(&NotExp::ExecuteLUInt32Both, this);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&NotExp::ExecuteGUInt64Both, this);
                }
                else {
                    executor = std::bind(&NotExp::ExecuteLUInt64Both, this);
                }

                break;
            }
        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal) {
                executor = std::bind(&NotExp::ExecuteGBool, this);
            }
            else {
                executor = std::bind(&NotExp::ExecuteLBool, this);
            }

        }
        return true;
    }
private:
    int ExecuteGBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLBoolBoth(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt8Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt16Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt32Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt64Both(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGBool(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBoolean(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLBool(void) const
    {
        if (m_Op1)
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBoolean(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

};
