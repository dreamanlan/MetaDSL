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
                    executor.attach(this, &AddExp::ExecuteGGBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLBoolBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLStringBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGGString);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLLString);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGLString);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetString(vars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetStr(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &SubExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGDoubleBoth);
                }

                break;
            }
        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &MulExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGDoubleBoth);
                }

                break;
            }
        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &DivExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGDoubleBoth);
                }

                break;
            }
        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetFloat(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetDouble(vars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetF64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &ModExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &LShiftExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &RShiftExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &BitAndExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &BitOrExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &BitXorExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &GreatExp::ExecuteGGBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLBoolBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLStringBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGGString);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLLString);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGLString);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &GreatEqualExp::ExecuteGGBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLBoolBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLStringBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGGString);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLLString);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGLString);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &LessExp::ExecuteGGBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLBoolBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLStringBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGGString);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLLString);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGLString);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &LessEqualExp::ExecuteGGBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLBoolBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLStringBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGGString);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLLString);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGLString);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &EqualExp::ExecuteGGBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLBoolBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLStringBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGGString);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLLString);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGLString);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &NotEqualExp::ExecuteGGBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLBoolBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLFloatBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLFloatBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLDoubleBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLDoubleBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLStringBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLStringBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGGString);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLLString);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGLString);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGGFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLLFloat);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGLFloat);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGGUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLLUInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGLUInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGGInt);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLLInt);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGLInt);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        float v1 = VarGetFloat(vars, m_LoadInfo1.VarIndex);
        float v2 = VarGetFloat(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetDouble(vars, m_LoadInfo1.VarIndex);
        double v2 = VarGetDouble(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        const std::string& v1 = VarGetString(vars, m_LoadInfo1.VarIndex);
        const std::string& v2 = VarGetString(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetI64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetU64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetU64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        double v1 = VarGetF64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        double v2 = VarGetF64(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        std::string v1 = VarGetStr(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        std::string v2 = VarGetStr(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &AndExp::ExecuteGGBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLBoolBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AndExp::ExecuteGGBool);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AndExp::ExecuteLLBool);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AndExp::ExecuteGLBool);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &AndExp::ExecuteLGBool);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBoolean(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBool(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &OrExp::ExecuteGGBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLBoolBoth);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLBoolBoth);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLUInt8Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLUInt8Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLUInt16Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLUInt16Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLUInt32Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLUInt32Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLUInt64Both);
                }
                else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLUInt64Both);
                }
                else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &OrExp::ExecuteGGBool);
            }
            else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &OrExp::ExecuteLLBool);
            }
            else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                executor.attach(this, &OrExp::ExecuteGLBool);
            }
            else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                executor.attach(this, &OrExp::ExecuteLGBool);
            }

        }

        return true;
    }
private:
    int ExecuteGGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBool(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        int8_t v2 = VarGetInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        int16_t v2 = VarGetInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        int32_t v2 = VarGetInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        int64_t v2 = VarGetInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(vars, m_LoadInfo2.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
            m_Op2();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBoolean(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        bool v2 = VarGetBoolean(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBool(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
        if (!m_Op1.isNull())
            m_Op1();
        if (!m_Op2.isNull())
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
                    executor.attach(this, &BitNotExp::ExecuteGInt8Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGInt16Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGInt32Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGInt64Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGUInt8Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGUInt16Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGUInt32Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGUInt64Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLUInt64Both);
                }

                break;
            }
        }
        else if (IsUnsignedType(resultType)) {
            if (m_LoadInfo1.IsGlobal) {
                executor.attach(this, &BitNotExp::ExecuteGUInt);
            }
            else {
                executor.attach(this, &BitNotExp::ExecuteLUInt);
            }

        }
        else {
            if (m_LoadInfo1.IsGlobal) {
                executor.attach(this, &BitNotExp::ExecuteGInt);
            }
            else {
                executor.attach(this, &BitNotExp::ExecuteLInt);
            }

        }
        return true;
    }
private:
    int ExecuteGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        VarSetInt8(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        VarSetInt16(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        VarSetInt32(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        VarSetInt64(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        VarSetUInt8(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        VarSetUInt16(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        VarSetUInt32(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        VarSetUInt64(vars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetI64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetI64(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetI64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetU64(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetU64(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt(void) const
    {
        if (!m_Op1.isNull())
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
                    executor.attach(this, &NotExp::ExecuteGBoolBoth);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGInt8Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGInt16Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGInt32Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGInt64Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGUInt8Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGUInt16Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGUInt32Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGUInt64Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLUInt64Both);
                }

                break;
            }
        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_LoadInfo1.IsGlobal) {
                executor.attach(this, &NotExp::ExecuteGBool);
            }
            else {
                executor.attach(this, &NotExp::ExecuteLBool);
            }

        }
        return true;
    }
private:
    int ExecuteGBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBool(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLBoolBoth(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBool(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int8_t v1 = VarGetInt8(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int8_t v1 = VarGetInt8(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int16_t v1 = VarGetInt16(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int16_t v1 = VarGetInt16(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int32_t v1 = VarGetInt32(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int32_t v1 = VarGetInt32(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        int64_t v1 = VarGetInt64(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        int64_t v1 = VarGetInt64(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint8_t v1 = VarGetUInt8(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt8Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint8_t v1 = VarGetUInt8(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint16_t v1 = VarGetUInt16(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt16Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint16_t v1 = VarGetUInt16(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint32_t v1 = VarGetUInt32(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt32Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint32_t v1 = VarGetUInt32(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        uint64_t v1 = VarGetUInt64(srcVars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt64Both(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        uint64_t v1 = VarGetUInt64(vars, m_LoadInfo1.VarIndex);
        VarSetBool(vars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGBool(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        auto& srcVars = *GlobalVariables();
        bool v1 = VarGetBoolean(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLBool(void) const
    {
        if (!m_Op1.isNull())
            m_Op1();
        auto& vars = *CurRuntimeVariables();
        bool v1 = VarGetBoolean(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
        VarSetBoolean(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

};