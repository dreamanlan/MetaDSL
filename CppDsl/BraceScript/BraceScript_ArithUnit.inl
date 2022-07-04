
class AddExp final : public BinaryOperatorBaseExp
{
public:
    AddExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator +, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GBoolBoth);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GBoolBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGBoolBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLBoolBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLBoolBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AddExp::ExecuteGG2GStringBoth);
                    }
                    else {
                        executor.attach(this, &AddExp::ExecuteGL2GStringBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGGStringBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLLStringBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGLStringBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGG2GString);
                }
                else {
                    executor.attach(this, &AddExp::ExecuteGL2GString);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGGString);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLLString);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGLString);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &AddExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &AddExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &AddExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &AddExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AddExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetString(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetString(gvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetString(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetString(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetString(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetString(lvars, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetStr(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetStr(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetStr(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetStr(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetStr(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetStr(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 + v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class SubExp final : public BinaryOperatorBaseExp
{
public:
    SubExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator -, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type && load1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &SubExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &SubExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteLGDoubleBoth);
                }

                break;
            }
        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &SubExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &SubExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &SubExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &SubExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &SubExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 - v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class MulExp final : public BinaryOperatorBaseExp
{
public:
    MulExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator *, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type && load1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &MulExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &MulExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteLGDoubleBoth);
                }

                break;
            }
        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &MulExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &MulExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &MulExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &MulExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &MulExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 * v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class DivExp final : public BinaryOperatorBaseExp
{
public:
    DivExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator /, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type && load1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &DivExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &DivExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteLGDoubleBoth);
                }

                break;
            }
        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &DivExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &DivExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &DivExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &DivExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &DivExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 / v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class ModExp final : public BinaryOperatorBaseExp
{
public:
    ModExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator %, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type && load1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &ModExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &ModExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &ModExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &ModExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &ModExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &ModExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &ModExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &ModExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &ModExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &ModExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &ModExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &ModExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &ModExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &ModExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &ModExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &ModExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &ModExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &ModExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &ModExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &ModExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 % v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class LShiftExp final : public BinaryOperatorBaseExp
{
public:
    LShiftExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator <<, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type && load1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LShiftExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &LShiftExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LShiftExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &LShiftExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LShiftExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &LShiftExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LShiftExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &LShiftExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LShiftExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &LShiftExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LShiftExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &LShiftExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LShiftExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &LShiftExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LShiftExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &LShiftExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &LShiftExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LShiftExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &LShiftExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LShiftExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 << v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class RShiftExp final : public BinaryOperatorBaseExp
{
public:
    RShiftExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator >>, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type && load1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &RShiftExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &RShiftExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &RShiftExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &RShiftExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &RShiftExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &RShiftExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &RShiftExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &RShiftExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &RShiftExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &RShiftExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &RShiftExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &RShiftExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &RShiftExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &RShiftExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &RShiftExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &RShiftExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &RShiftExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &RShiftExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &RShiftExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &RShiftExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >> v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class BitAndExp final : public BinaryOperatorBaseExp
{
public:
    BitAndExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator &, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type && load1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitAndExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &BitAndExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitAndExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &BitAndExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitAndExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &BitAndExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitAndExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &BitAndExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitAndExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &BitAndExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitAndExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &BitAndExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitAndExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &BitAndExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitAndExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &BitAndExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &BitAndExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &BitAndExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &BitAndExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitAndExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 & v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class BitOrExp final : public BinaryOperatorBaseExp
{
public:
    BitOrExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator |, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type && load1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitOrExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &BitOrExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitOrExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &BitOrExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitOrExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &BitOrExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitOrExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &BitOrExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitOrExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &BitOrExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitOrExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &BitOrExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitOrExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &BitOrExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitOrExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &BitOrExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &BitOrExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &BitOrExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &BitOrExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitOrExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 | v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class BitXorExp final : public BinaryOperatorBaseExp
{
public:
    BitXorExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator ^, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type && load1.Type != BRACE_DATA_TYPE_BOOL) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitXorExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &BitXorExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitXorExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &BitXorExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitXorExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &BitXorExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitXorExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &BitXorExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitXorExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &BitXorExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitXorExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &BitXorExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitXorExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &BitXorExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &BitXorExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &BitXorExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &BitXorExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteLGUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &BitXorExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &BitXorExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &BitXorExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 ^ v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class GreatExp final : public BinaryOperatorBaseExp
{
public:
    GreatExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator >, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GBoolBoth);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GBoolBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGBoolBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLBoolBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLBoolBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatExp::ExecuteGG2GStringBoth);
                    }
                    else {
                        executor.attach(this, &GreatExp::ExecuteGL2GStringBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGGStringBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLLStringBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGLStringBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGG2GString);
                }
                else {
                    executor.attach(this, &GreatExp::ExecuteGL2GString);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGGString);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLLString);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGLString);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &GreatExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &GreatExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &GreatExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &GreatExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 > v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class GreatEqualExp final : public BinaryOperatorBaseExp
{
public:
    GreatEqualExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator >=, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GBoolBoth);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GBoolBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGBoolBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLBoolBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLBoolBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &GreatEqualExp::ExecuteGG2GStringBoth);
                    }
                    else {
                        executor.attach(this, &GreatEqualExp::ExecuteGL2GStringBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGGStringBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLLStringBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGLStringBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGG2GString);
                }
                else {
                    executor.attach(this, &GreatEqualExp::ExecuteGL2GString);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGGString);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLLString);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGLString);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &GreatEqualExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &GreatEqualExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &GreatEqualExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &GreatEqualExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &GreatEqualExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 >= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class LessExp final : public BinaryOperatorBaseExp
{
public:
    LessExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator <, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GBoolBoth);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GBoolBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGBoolBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLBoolBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLBoolBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessExp::ExecuteGG2GStringBoth);
                    }
                    else {
                        executor.attach(this, &LessExp::ExecuteGL2GStringBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGGStringBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLLStringBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGLStringBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGG2GString);
                }
                else {
                    executor.attach(this, &LessExp::ExecuteGL2GString);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGGString);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLLString);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGLString);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &LessExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &LessExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LessExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &LessExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 < v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class LessEqualExp final : public BinaryOperatorBaseExp
{
public:
    LessEqualExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator <=, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GBoolBoth);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GBoolBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGBoolBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLBoolBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLBoolBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &LessEqualExp::ExecuteGG2GStringBoth);
                    }
                    else {
                        executor.attach(this, &LessEqualExp::ExecuteGL2GStringBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGGStringBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLLStringBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGLStringBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGG2GString);
                }
                else {
                    executor.attach(this, &LessEqualExp::ExecuteGL2GString);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGGString);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLLString);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGLString);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &LessEqualExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &LessEqualExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &LessEqualExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &LessEqualExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &LessEqualExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 <= v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class EqualExp final : public BinaryOperatorBaseExp
{
public:
    EqualExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator ==, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GBoolBoth);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GBoolBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGBoolBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLBoolBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLBoolBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &EqualExp::ExecuteGG2GStringBoth);
                    }
                    else {
                        executor.attach(this, &EqualExp::ExecuteGL2GStringBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGGStringBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLLStringBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGLStringBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGG2GString);
                }
                else {
                    executor.attach(this, &EqualExp::ExecuteGL2GString);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGGString);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLLString);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGLString);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &EqualExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &EqualExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &EqualExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &EqualExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &EqualExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 == v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class NotEqualExp final : public BinaryOperatorBaseExp
{
public:
    NotEqualExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_STRING) {
            std::stringstream ss;
            ss << "operator !=, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GBoolBoth);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GBoolBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGBoolBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLBoolBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLBoolBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GFloatBoth);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GFloatBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGFloatBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLFloatBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLFloatBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GDoubleBoth);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GDoubleBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGDoubleBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLDoubleBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLDoubleBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGDoubleBoth);
                }

                break;
            case BRACE_DATA_TYPE_STRING:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &NotEqualExp::ExecuteGG2GStringBoth);
                    }
                    else {
                        executor.attach(this, &NotEqualExp::ExecuteGL2GStringBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGGStringBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLLStringBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGLStringBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteLGStringBoth);
                }

                break;
            }
        }
        else if (NeedStringArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGG2GString);
                }
                else {
                    executor.attach(this, &NotEqualExp::ExecuteGL2GString);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGGString);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLLString);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGLString);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLGString);
            }

        }
        else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGG2GFloat);
                }
                else {
                    executor.attach(this, &NotEqualExp::ExecuteGL2GFloat);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGGFloat);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLLFloat);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGLFloat);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLGFloat);
            }

        }
        else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGG2GUInt);
                }
                else {
                    executor.attach(this, &NotEqualExp::ExecuteGL2GUInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGGUInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLLUInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGLUInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLGUInt);
            }

        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &NotEqualExp::ExecuteGG2GInt);
                }
                else {
                    executor.attach(this, &NotEqualExp::ExecuteGL2GInt);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGGInt);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLLInt);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteGLInt);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &NotEqualExp::ExecuteLGInt);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        float v2 = VarGetFloat(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        double v2 = VarGetDouble(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(gvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGStringBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        const std::string& v1 = VarGetString(lvars, m_ArgInfo1.VarIndex);
        const std::string& v2 = VarGetString(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetI64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetU64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        double v2 = VarGetF64(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGString(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        std::string v1 = VarGetStr(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        std::string v2 = VarGetStr(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 != v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class AndExp final : public BinaryOperatorBaseExp
{
public:
    AndExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator &&, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AndExp::ExecuteGG2GBoolBoth);
                    }
                    else {
                        executor.attach(this, &AndExp::ExecuteGL2GBoolBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGBoolBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLBoolBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLBoolBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AndExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &AndExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AndExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &AndExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AndExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &AndExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AndExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &AndExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AndExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &AndExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AndExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &AndExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AndExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &AndExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &AndExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &AndExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &AndExp::ExecuteGG2GBool);
                }
                else {
                    executor.attach(this, &AndExp::ExecuteGL2GBool);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AndExp::ExecuteGGBool);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AndExp::ExecuteLLBool);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &AndExp::ExecuteGLBool);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &AndExp::ExecuteLGBool);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 && v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class OrExp final : public BinaryOperatorBaseExp
{
public:
    OrExp(BraceScript& interpreter, bool isAssignment) :BinaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, const VarTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = GetMaxType(load1.Type, load2.Type);
        if (resultType > BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator ||, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type == load2.Type) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &OrExp::ExecuteGG2GBoolBoth);
                    }
                    else {
                        executor.attach(this, &OrExp::ExecuteGL2GBoolBoth);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGBoolBoth);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLBoolBoth);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLBoolBoth);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &OrExp::ExecuteGG2GInt8Both);
                    }
                    else {
                        executor.attach(this, &OrExp::ExecuteGL2GInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &OrExp::ExecuteGG2GInt16Both);
                    }
                    else {
                        executor.attach(this, &OrExp::ExecuteGL2GInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &OrExp::ExecuteGG2GInt32Both);
                    }
                    else {
                        executor.attach(this, &OrExp::ExecuteGL2GInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &OrExp::ExecuteGG2GInt64Both);
                    }
                    else {
                        executor.attach(this, &OrExp::ExecuteGL2GInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &OrExp::ExecuteGG2GUInt8Both);
                    }
                    else {
                        executor.attach(this, &OrExp::ExecuteGL2GUInt8Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGUInt8Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLUInt8Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLUInt8Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &OrExp::ExecuteGG2GUInt16Both);
                    }
                    else {
                        executor.attach(this, &OrExp::ExecuteGL2GUInt16Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGUInt16Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLUInt16Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLUInt16Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &OrExp::ExecuteGG2GUInt32Both);
                    }
                    else {
                        executor.attach(this, &OrExp::ExecuteGL2GUInt32Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGUInt32Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLUInt32Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLUInt32Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    if (load2.IsGlobal) {
                        executor.attach(this, &OrExp::ExecuteGG2GUInt64Both);
                    }
                    else {
                        executor.attach(this, &OrExp::ExecuteGL2GUInt64Both);
                    }
                }
                else if (load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGGUInt64Both);
                }
                else if (!load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLLUInt64Both);
                }
                else if (load1.IsGlobal && !load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGLUInt64Both);
                }
                else if (!load1.IsGlobal && load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteLGUInt64Both);
                }

                break;
            }
        }
        else {
            resultType = BRACE_DATA_TYPE_BOOL;
            if (m_IsAssignment && load1.IsGlobal) {
                if (load2.IsGlobal) {
                    executor.attach(this, &OrExp::ExecuteGG2GBool);
                }
                else {
                    executor.attach(this, &OrExp::ExecuteGL2GBool);
                }
            }
            else if (load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &OrExp::ExecuteGGBool);
            }
            else if (!load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &OrExp::ExecuteLLBool);
            }
            else if (load1.IsGlobal && !load2.IsGlobal) {
                executor.attach(this, &OrExp::ExecuteGLBool);
            }
            else if (!load1.IsGlobal && load2.IsGlobal) {
                executor.attach(this, &OrExp::ExecuteLGBool);
            }

        }

        return true;
    }
private:
    int ExecuteGG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBool(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        int8_t v2 = VarGetInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        int16_t v2 = VarGetInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        int32_t v2 = VarGetInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        int64_t v2 = VarGetInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        uint8_t v2 = VarGetUInt8(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        uint16_t v2 = VarGetUInt16(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        uint32_t v2 = VarGetUInt32(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(lvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        uint64_t v2 = VarGetUInt64(gvars, m_ArgInfo2.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteGG2GBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGL2GBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGGBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLLBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGLBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(lvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLGBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        if (!m_Op2.isNull())
            m_Op2(gvars, lvars);
        bool v1 = VarGetBoolean(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        bool v2 = VarGetBoolean(gvars, m_ArgInfo2.Type, m_ArgInfo2.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 || v2);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class BitNotExp final : public UnaryOperatorBaseExp
{
public:
    BitNotExp(BraceScript& interpreter, bool isAssignment) :UnaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = load1.Type;
        if (resultType >= BRACE_DATA_TYPE_UINT64) {
            std::stringstream ss;
            ss << "operator ~, operand type dismatch, " << GetDataTypeName(load1.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type >= BRACE_DATA_TYPE_INT8 && load1.Type <= BRACE_DATA_TYPE_UINT64) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteG2GInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGInt8Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteG2GInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGInt16Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteG2GInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGInt32Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteG2GInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGInt64Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteG2GUInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGUInt8Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteG2GUInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGUInt16Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteG2GUInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGUInt32Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteG2GUInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &BitNotExp::ExecuteGUInt64Both);
                }
                else {
                    executor.attach(this, &BitNotExp::ExecuteLUInt64Both);
                }

                break;
            }
        }
        else if (IsUnsignedType(resultType)) {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &BitNotExp::ExecuteG2GUInt);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &BitNotExp::ExecuteGUInt);
            }
            else {
                executor.attach(this, &BitNotExp::ExecuteLUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &BitNotExp::ExecuteG2GInt);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &BitNotExp::ExecuteGInt);
            }
            else {
                executor.attach(this, &BitNotExp::ExecuteLInt);
            }

        }

        return true;
    }
private:
    int ExecuteG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ~v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class IncExp final : public UnaryOperatorBaseExp
{
public:
    IncExp(BraceScript& interpreter, bool isAssignment) :UnaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = load1.Type;
        if (resultType >= BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator ++, operand type dismatch, " << GetDataTypeName(load1.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type >= BRACE_DATA_TYPE_INT8 && load1.Type <= BRACE_DATA_TYPE_DOUBLE) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGInt8Both);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGInt16Both);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGInt32Both);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGInt64Both);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GUInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGUInt8Both);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GUInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGUInt16Both);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GUInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGUInt32Both);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GUInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGUInt64Both);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GFloatBoth);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGFloatBoth);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteG2GDoubleBoth);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &IncExp::ExecuteGDoubleBoth);
                }
                else {
                    executor.attach(this, &IncExp::ExecuteLDoubleBoth);
                }

                break;
            }
        }
        else if (IsFloatType(resultType)) {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &IncExp::ExecuteG2GFloat);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &IncExp::ExecuteGFloat);
            }
            else {
                executor.attach(this, &IncExp::ExecuteLFloat);
            }

        }
        else if (IsUnsignedType(resultType)) {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &IncExp::ExecuteG2GUInt);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &IncExp::ExecuteGUInt);
            }
            else {
                executor.attach(this, &IncExp::ExecuteLUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &IncExp::ExecuteG2GInt);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &IncExp::ExecuteGInt);
            }
            else {
                executor.attach(this, &IncExp::ExecuteLInt);
            }

        }

        return true;
    }
private:
    int ExecuteG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, ++v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class DecExp final : public UnaryOperatorBaseExp
{
public:
    DecExp(BraceScript& interpreter, bool isAssignment) :UnaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = load1.Type;
        if (resultType >= BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator --, operand type dismatch, " << GetDataTypeName(load1.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type >= BRACE_DATA_TYPE_INT8 && load1.Type <= BRACE_DATA_TYPE_DOUBLE) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGInt8Both);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGInt16Both);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGInt32Both);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGInt64Both);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GUInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGUInt8Both);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GUInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGUInt16Both);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GUInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGUInt32Both);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GUInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGUInt64Both);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GFloatBoth);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGFloatBoth);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteG2GDoubleBoth);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &DecExp::ExecuteGDoubleBoth);
                }
                else {
                    executor.attach(this, &DecExp::ExecuteLDoubleBoth);
                }

                break;
            }
        }
        else if (IsFloatType(resultType)) {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &DecExp::ExecuteG2GFloat);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &DecExp::ExecuteGFloat);
            }
            else {
                executor.attach(this, &DecExp::ExecuteLFloat);
            }

        }
        else if (IsUnsignedType(resultType)) {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &DecExp::ExecuteG2GUInt);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &DecExp::ExecuteGUInt);
            }
            else {
                executor.attach(this, &DecExp::ExecuteLUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &DecExp::ExecuteG2GInt);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &DecExp::ExecuteGInt);
            }
            else {
                executor.attach(this, &DecExp::ExecuteLInt);
            }

        }

        return true;
    }
private:
    int ExecuteG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, --v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class PositiveExp final : public UnaryOperatorBaseExp
{
public:
    PositiveExp(BraceScript& interpreter, bool isAssignment) :UnaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = load1.Type;
        if (resultType >= BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator +, operand type dismatch, " << GetDataTypeName(load1.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type >= BRACE_DATA_TYPE_INT8 && load1.Type <= BRACE_DATA_TYPE_DOUBLE) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGInt8Both);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGInt16Both);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGInt32Both);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGInt64Both);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GUInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGUInt8Both);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GUInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGUInt16Both);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GUInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGUInt32Both);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GUInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGUInt64Both);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLUInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GFloatBoth);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGFloatBoth);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteG2GDoubleBoth);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &PositiveExp::ExecuteGDoubleBoth);
                }
                else {
                    executor.attach(this, &PositiveExp::ExecuteLDoubleBoth);
                }

                break;
            }
        }
        else if (IsFloatType(resultType)) {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &PositiveExp::ExecuteG2GFloat);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &PositiveExp::ExecuteGFloat);
            }
            else {
                executor.attach(this, &PositiveExp::ExecuteLFloat);
            }

        }
        else if (IsUnsignedType(resultType)) {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &PositiveExp::ExecuteG2GUInt);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &PositiveExp::ExecuteGUInt);
            }
            else {
                executor.attach(this, &PositiveExp::ExecuteLUInt);
            }

        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &PositiveExp::ExecuteG2GInt);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &PositiveExp::ExecuteGInt);
            }
            else {
                executor.attach(this, &PositiveExp::ExecuteLInt);
            }

        }

        return true;
    }
private:
    int ExecuteG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt8(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt16(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt32(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetUInt64(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetU64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetU64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, +v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class NegativeExp final : public UnaryOperatorBaseExp
{
public:
    NegativeExp(BraceScript& interpreter, bool isAssignment) :UnaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = load1.Type;
        if (resultType >= BRACE_DATA_TYPE_DOUBLE) {
            std::stringstream ss;
            ss << "operator -, operand type dismatch, " << GetDataTypeName(load1.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (IsSignedType(load1.Type) || IsFloatType(load1.Type)) {
            resultType = load1.Type;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteG2GInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteGInt8Both);
                }
                else {
                    executor.attach(this, &NegativeExp::ExecuteLInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteG2GInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteGInt16Both);
                }
                else {
                    executor.attach(this, &NegativeExp::ExecuteLInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteG2GInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteGInt32Both);
                }
                else {
                    executor.attach(this, &NegativeExp::ExecuteLInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteG2GInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteGInt64Both);
                }
                else {
                    executor.attach(this, &NegativeExp::ExecuteLInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_FLOAT:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteG2GFloatBoth);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteGFloatBoth);
                }
                else {
                    executor.attach(this, &NegativeExp::ExecuteLFloatBoth);
                }

                break;
            case BRACE_DATA_TYPE_DOUBLE:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteG2GDoubleBoth);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NegativeExp::ExecuteGDoubleBoth);
                }
                else {
                    executor.attach(this, &NegativeExp::ExecuteLDoubleBoth);
                }

                break;
            }
        }
        else {
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &NegativeExp::ExecuteG2GInt);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &NegativeExp::ExecuteGInt);
            }
            else {
                executor.attach(this, &NegativeExp::ExecuteLInt);
            }

        }

        return true;
    }
private:
    int ExecuteG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(gvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetInt8(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(gvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetInt16(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(gvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetInt32(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(gvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetInt64(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        VarSetFloat(gvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(gvars, m_ArgInfo1.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLFloatBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        float v1 = VarGetFloat(lvars, m_ArgInfo1.VarIndex);
        VarSetFloat(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        VarSetDouble(gvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(gvars, m_ArgInfo1.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLDoubleBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetDouble(lvars, m_ArgInfo1.VarIndex);
        VarSetDouble(lvars, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetI64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetI64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLFloat(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        double v1 = VarGetF64(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetF64(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, -v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }


};
class NotExp final : public UnaryOperatorBaseExp
{
public:
    NotExp(BraceScript& interpreter, bool isAssignment) :UnaryOperatorBaseExp(interpreter, isAssignment)
    {
    }
protected:
    virtual bool BuildExecutor(const DslData::FunctionData& data, const VarTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const override
    {
        resultType = load1.Type;
        if (resultType >= BRACE_DATA_TYPE_FLOAT) {
            std::stringstream ss;
            ss << "can't bit not type " << GetDataTypeName(load1.Type) << ", line " << data.GetLine();
            LogError(ss.str());
            return false;
        }
        else if (load1.Type <= BRACE_DATA_TYPE_UINT64) {
            resultType = BRACE_DATA_TYPE_BOOL;
            switch (load1.Type) {
            case BRACE_DATA_TYPE_BOOL:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteG2GBoolBoth);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGBoolBoth);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLBoolBoth);
                }

                break;
            case BRACE_DATA_TYPE_INT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteG2GInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGInt8Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_INT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteG2GInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGInt16Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_INT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteG2GInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGInt32Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_INT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteG2GInt64Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGInt64Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLInt64Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT8:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteG2GUInt8Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGUInt8Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLUInt8Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT16:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteG2GUInt16Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGUInt16Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLUInt16Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT32:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteG2GUInt32Both);
                }
                else if (load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteGUInt32Both);
                }
                else {
                    executor.attach(this, &NotExp::ExecuteLUInt32Both);
                }

                break;
            case BRACE_DATA_TYPE_UINT64:
                if (m_IsAssignment && load1.IsGlobal) {
                    executor.attach(this, &NotExp::ExecuteG2GUInt64Both);
                }
                else if (load1.IsGlobal) {
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
            if (m_IsAssignment && load1.IsGlobal) {
                executor.attach(this, &NotExp::ExecuteG2GBool);
            }
            else if (load1.IsGlobal) {
                executor.attach(this, &NotExp::ExecuteGBool);
            }
            else {
                executor.attach(this, &NotExp::ExecuteLBool);
            }

        }
        return true;
    }
private:
    int ExecuteG2GBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        bool v1 = VarGetBool(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLBoolBoth(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        bool v1 = VarGetBool(lvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int8_t v1 = VarGetInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int16_t v1 = VarGetInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int32_t v1 = VarGetInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        int64_t v1 = VarGetInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt8Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint8_t v1 = VarGetUInt8(lvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt16Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint16_t v1 = VarGetUInt16(lvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt32Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint32_t v1 = VarGetUInt32(lvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(gvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(gvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLUInt64Both(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        uint64_t v1 = VarGetUInt64(lvars, m_ArgInfo1.VarIndex);
        VarSetBool(lvars, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

    int ExecuteG2GBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetBoolean(gvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteGBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        bool v1 = VarGetBoolean(gvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }
    int ExecuteLBool(Brace::VariableInfo& gvars, Brace::VariableInfo& lvars) const
    {
        if (!m_Op1.isNull())
            m_Op1(gvars, lvars);
        bool v1 = VarGetBoolean(lvars, m_ArgInfo1.Type, m_ArgInfo1.VarIndex);
        VarSetBoolean(lvars, m_ResultInfo.Type, m_ResultInfo.VarIndex, !v1);
        return BRACE_FLOW_CONTROL_NORMAL;
    }

};
