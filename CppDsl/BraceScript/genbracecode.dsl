script(main)
{
    $braceTypes = ["BRACE_DATA_TYPE_BOOL", "BRACE_DATA_TYPE_INT8", "BRACE_DATA_TYPE_INT16", "BRACE_DATA_TYPE_INT32", "BRACE_DATA_TYPE_INT64"
        , "BRACE_DATA_TYPE_UINT8", "BRACE_DATA_TYPE_UINT16", "BRACE_DATA_TYPE_UINT32", "BRACE_DATA_TYPE_UINT64"
        , "BRACE_DATA_TYPE_FLOAT", "BRACE_DATA_TYPE_DOUBLE"];
    $braceTypeNames = ["Bool", "Int8", "Int16", "Int32", "Int64"
        , "UInt8", "UInt16", "UInt32", "UInt64"
        , "Float", "Double"];
    $cppTypes = ["bool", "int8_t", "int16_t", "int32_t", "int64_t"
        , "uint8_t", "uint16_t", "uint32_t", "uint64_t"
        , "float", "double"];
    $specTypeNames = ["String", "Object"];

    call("writeVarAssign", $braceTypeNames, $specTypeNames);

    call("writeVarCastAssign", $braceTypeNames, $cppTypes);

    echo("\tVarAssignPtr GetVarAssignPtr(int varType, bool isRef, int srcVarType, bool srcIsRef)");
    echo("\t{");
    
    echo("\t\tif(isRef && srcIsRef){");
    $refMark = "FromToRef";
    call("writeSwitch", $braceTypes, $braceTypeNames, $refMark);
    echo("\t\t}");
    echo("\t\telse if(srcIsRef){");
    $refMark = "FromRef";
    call("writeSwitch", $braceTypes, $braceTypeNames, $refMark);
    echo("\t\t}");
    echo("\t\telse if(isRef){");
    $refMark = "ToRef";
    call("writeSwitch", $braceTypes, $braceTypeNames, $refMark);
    echo("\t\t}");
    echo("\t\telse{");
    $refMark = "";
    call("writeSwitch", $braceTypes, $braceTypeNames, $refMark);
    echo("\t\t}");

    echo("\t\treturn nullptr;");
    echo("\t}");

    echo();
    echo();

    call("writeBinaryExp", "AddExp", "+");
    call("writeBinaryExp", "SubExp", "-");
    call("writeBinaryExp", "MulExp", "*");
    call("writeBinaryExp", "DivExp", "/");
    call("writeBinaryExp", "ModExp", "%");
    call("writeBinaryExp", "LShiftExp", "<<");
    call("writeBinaryExp", "RShiftExp", ">>");
    call("writeBinaryExp", "BitAndExp", "&");
    call("writeBinaryExp", "BitOrExp", "|");
    call("writeBinaryExp", "BitXorExp", "^");
    call("writeBinaryExp", "GreatExp", ">");
    call("writeBinaryExp", "GreatEqualExp", ">=");
    call("writeBinaryExp", "LessExp", "<");
    call("writeBinaryExp", "LessEqualExp", "<=");
    call("writeBinaryExp", "EqualExp", "==");
    call("writeBinaryExp", "NotEqualExp", "!=");
    call("writeBinaryExp", "AndExp", "&&");
    call("writeBinaryExp", "OrExp", "||");

    call("writeUnaryNumericExp", "BitNotExp", "~");
    call("writeUnaryNumericExp", "IncExp", "++");
    call("writeUnaryNumericExp", "DecExp", "--");
    call("writeUnaryNumericExp", "PositiveExp", "+");
    call("writeUnaryNumericExp", "NegativeExp", "-");
    call("writeNotExp");

    return(0);
};
script(writeVarAssign)args($braceTypeNames, $specTypeNames)
{
    //VarAssign
    loop(listsize($braceTypeNames)){
        $typeName = $braceTypeNames[$$];

        writeblock
        {:
    static inline void VarAssign{% $typeName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].{% $typeName %}Val = srcInfo.NumericVars[srcIndex].{% $typeName %}Val;
    }
        :};        
    };
    //VarAssignFromRef
    loop(listsize($braceTypeNames)){
        $typeName = $braceTypeNames[$$];

        writeblock
        {:
    static inline void VarAssignFromRef{% $typeName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].{% $typeName %}Val = sri.Vars->NumericVars[sri.VarIndex].{% $typeName %}Val;
    }
        :};        
    };
    //VarAssignToRef
    loop(listsize($braceTypeNames)){
        $typeName = $braceTypeNames[$$];

        writeblock
        {:
    static inline void VarAssignToRef{% $typeName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].{% $typeName %}Val = srcInfo.NumericVars[srcIndex].{% $typeName %}Val;
    }
        :};        
    };
    //VarAssignFromToRef
    loop(listsize($braceTypeNames)){
        $typeName = $braceTypeNames[$$];

        writeblock
        {:
    static inline void VarAssignFromToRef{% $typeName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].{% $typeName %}Val = sri.Vars->NumericVars[sri.VarIndex].{% $typeName %}Val;
    }
        :};        
    };
    //--------------
    //VarAssign
    loop(listsize($specTypeNames)){
        $typeName = $specTypeNames[$$];

        writeblock
        {:
    static inline void VarAssign{% $typeName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.{% $typeName %}Vars[destIndex] = srcInfo.{% $typeName %}Vars[srcIndex];
    }
        :};        
    };
    //VarAssignFromRef
    loop(listsize($specTypeNames)){
        $typeName = $specTypeNames[$$];

        writeblock
        {:
    static inline void VarAssignFromRef{% $typeName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.{% $typeName %}Vars[destIndex] = sri.Vars->{% $typeName %}Vars[sri.VarIndex];
    }
        :};        
    };
    //VarAssignToRef
    loop(listsize($specTypeNames)){
        $typeName = $specTypeNames[$$];

        writeblock
        {:
    static inline void VarAssignToRef{% $typeName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->{% $typeName %}Vars[ri.VarIndex] = srcInfo.{% $typeName %}Vars[srcIndex];
    }
        :};        
    };
    //VarAssignFromToRef
    loop(listsize($specTypeNames)){
        $typeName = $specTypeNames[$$];

        writeblock
        {:
    static inline void VarAssignFromToRef{% $typeName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->{% $typeName %}Vars[ri.VarIndex] = sri.Vars->{% $typeName %}Vars[sri.VarIndex];
    }
        :};        
    };
};
script(writeVarCastAssign)args($braceTypeNames, $cppTypes)
{
    //VarCastAssign
    loop(listsize($braceTypeNames)){
        $firstName = $braceTypeNames[$$];
        $firstType = $cppTypes[$$];
        
        loop(listsize($braceTypeNames)){
            $secondName = $braceTypeNames[$$];
            $secondType = $cppTypes[$$];

            if($firstName==$secondName){
            }
            elseif($firstName=="Bool" && ($secondName=="Float" || $secondName=="Double")){
            }
            elseif($secondName=="Bool" && ($firstName=="Float" || $firstName=="Double")){
            }
            else{
                writeblock
                {:
    static inline void VarCastAssign{% $firstName %}{% $secondName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.NumericVars[destIndex].{% $firstName %}Val = static_cast<{% $firstType %}>(srcInfo.NumericVars[srcIndex].{% $secondName %}Val);
    }
                :};
            };
        };
    };

    //VarCastAssignFromRef
    loop(listsize($braceTypeNames)){
        $firstName = $braceTypeNames[$$];
        $firstType = $cppTypes[$$];
        
        loop(listsize($braceTypeNames)){
            $secondName = $braceTypeNames[$$];
            $secondType = $cppTypes[$$];

            if($firstName==$secondName){
            }
            elseif($firstName=="Bool" && ($secondName=="Float" || $secondName=="Double")){
            }
            elseif($secondName=="Bool" && ($firstName=="Float" || $firstName=="Double")){
            }
            else{
                writeblock
                {:
    static inline void VarCastAssignFromRef{% $firstName %}{% $secondName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        info.NumericVars[destIndex].{% $firstName %}Val = static_cast<{% $firstType %}>(sri.Vars->NumericVars[sri.VarIndex].{% $secondName %}Val);
    }
                :};
            };
        };
    };

    //VarCastAssignToRef
    loop(listsize($braceTypeNames)){
        $firstName = $braceTypeNames[$$];
        $firstType = $cppTypes[$$];
        
        loop(listsize($braceTypeNames)){
            $secondName = $braceTypeNames[$$];
            $secondType = $cppTypes[$$];

            if($firstName==$secondName){
            }
            elseif($firstName=="Bool" && ($secondName=="Float" || $secondName=="Double")){
            }
            elseif($secondName=="Bool" && ($firstName=="Float" || $firstName=="Double")){
            }
            else{
                writeblock
                {:
    static inline void VarCastAssignToRef{% $firstName %}{% $secondName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        ri.Vars->NumericVars[ri.VarIndex].{% $firstName %}Val = static_cast<{% $firstType %}>(srcInfo.NumericVars[srcIndex].{% $secondName %}Val);
    }
                :};
            };
        };
    };

    //VarCastAssignFromToRef
    loop(listsize($braceTypeNames)){
        $firstName = $braceTypeNames[$$];
        $firstType = $cppTypes[$$];
        
        loop(listsize($braceTypeNames)){
            $secondName = $braceTypeNames[$$];
            $secondType = $cppTypes[$$];

            if($firstName==$secondName){
            }
            elseif($firstName=="Bool" && ($secondName=="Float" || $secondName=="Double")){
            }
            elseif($secondName=="Bool" && ($firstName=="Float" || $firstName=="Double")){
            }
            else{
                writeblock
                {:
    static inline void VarCastAssignFromToRef{% $firstName %}{% $secondName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        auto& ri = info.ReferenceVars[destIndex];
        auto& sri = srcInfo.ReferenceVars[srcIndex];
        ri.Vars->NumericVars[ri.VarIndex].{% $firstName %}Val = static_cast<{% $firstType %}>(sri.Vars->NumericVars[sri.VarIndex].{% $secondName %}Val);
    }
                :};
            };
        };
    };

};
script(writeSwitch)args($braceTypes, $braceTypeNames, $refMark)
{
    echo("\t\t\tswitch(varType){");
    loop(listsize($braceTypes)){
        $first = $braceTypes[$$];
        $firstTypeName = $braceTypeNames[$$];

        echo("\t\t\tcase {0}:", $first);
        echo("\t\t\t\tswitch(srcVarType){");
        loop(listsize($braceTypes)){
            $second = $braceTypes[$$];
            $secondTypeName = $braceTypeNames[$$];

            if($first==$second){
                echo("\t\t\t\tcase {0}:", $second);
                echo("\t\t\t\t\treturn VarAssign{0}{1};", $refMark, $firstTypeName);
            }
            elseif($first=="BRACE_DATA_TYPE_BOOL" && ($second=="BRACE_DATA_TYPE_FLOAT" || $second=="BRACE_DATA_TYPE_DOUBLE")){

            }
            elseif($second=="BRACE_DATA_TYPE_BOOL" && ($first=="BRACE_DATA_TYPE_FLOAT" || $first=="BRACE_DATA_TYPE_DOUBLE")){

            }
            else{
                echo("\t\t\t\tcase {0}:", $second);
                echo("\t\t\t\t\treturn VarCastAssign{0}{1}{2};", $refMark, $firstTypeName, $secondTypeName);
            };
        };
        echo("\t\t\t\t}");
    };
    writeblock
    {:
                case BRACE_DATA_TYPE_STRING: {
                    switch (srcVarType) {
                    case BRACE_DATA_TYPE_STRING:
                        return VarAssign{% $refMark %}String;
                    }
                }break;
                case BRACE_DATA_TYPE_OBJECT: {
                    switch (srcVarType) {
                    case BRACE_DATA_TYPE_OBJECT:
                        return VarAssign{% $refMark %}Object;
                    }
                }break;
    :};
    echo("\t\t\t}");
};
script(getBinaryExecuteCode)args($postfix, $operandType, $varGet, $varSet, $opr)
{
    return(block
    {:
        int ExecuteGG2G{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            {% $varSet %}(srcVars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteGL2G{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars1 = *GlobalVariables();
            auto& srcVars2 = vars;
            {% $operandType %} v1 = {% $varGet %}(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            {% $varSet %}(srcVars1, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteGG{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteLL{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            {% $operandType %} v1 = {% $varGet %}(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteGL{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars1 = *GlobalVariables();
            auto& srcVars2 = vars;
            {% $operandType %} v1 = {% $varGet %}(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteLG{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars1 = vars;
            auto& srcVars2 = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    :});
};
script(getUnaryExecuteCode)args($postfix, $operandType, $varGet, $varSet, $opr)
{
    return(block
    {:    
        int ExecuteG2G{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $varSet %}(srcVars, m_ResultInfo.Type, m_ResultInfo.VarIndex, {% $opr %} v1);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteG{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, {% $opr %} v1);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteL{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            auto& vars = *CurRuntimeVariables();
            {% $operandType %} v1 = {% $varGet %}(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, {% $opr %} v1);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    :});
};
script(getBinaryExecuteCodeBoth)args($postfix, $operandType, $varGet, $varSet, $opr)
{
    return(block
    {:
        int ExecuteGG2G{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars, m_LoadInfo2.VarIndex);
            {% $varSet %}(srcVars, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteGL2G{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars1 = *GlobalVariables();
            auto& srcVars2 = vars;
            {% $operandType %} v1 = {% $varGet %}(srcVars1, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars2, m_LoadInfo2.VarIndex);
            {% $varSet %}(srcVars1, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteGG{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteLL{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            {% $operandType %} v1 = {% $varGet %}(vars, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(vars, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteGL{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars1 = *GlobalVariables();
            auto& srcVars2 = vars;
            {% $operandType %} v1 = {% $varGet %}(srcVars1, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars2, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteLG{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            if (!m_Op2.isNull())
                m_Op2();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars1 = vars;
            auto& srcVars2 = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars1, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars2, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    :});
};
script(getUnaryExecuteCodeBoth)args($postfix, $operandType, $varGet, $varSet, $opr)
{
    return(block
    {:    
        int ExecuteG2G{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.VarIndex);
            {% $varSet %}(srcVars, m_ResultInfo.VarIndex, {% $opr %} v1);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteG{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            auto& vars = *CurRuntimeVariables();
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.VarIndex, {% $opr %} v1);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteL{% $postfix %}(void) const
        {
            if (!m_Op1.isNull())
                m_Op1();
            auto& vars = *CurRuntimeVariables();
            {% $operandType %} v1 = {% $varGet %}(vars, m_LoadInfo1.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.VarIndex, {% $opr %} v1);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    :});
};
script(getBinaryExecuteBuildCode)args($className, $postfix)
{
    return(block
    {:
                if (m_IsAssignment && m_LoadInfo1.IsGlobal) {
                    if(m_LoadInfo2.IsGlobal){
                        executor.attach(this, &{% $className %}::ExecuteGG2G{% $postfix %});
                    }
                    else{
                        executor.attach(this, &{% $className %}::ExecuteGL2G{% $postfix %});
                    }
                }
                else if (m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &{% $className %}::ExecuteGG{% $postfix %});
                } else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &{% $className %}::ExecuteLL{% $postfix %});
                } else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &{% $className %}::ExecuteGL{% $postfix %});
                } else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor.attach(this, &{% $className %}::ExecuteLG{% $postfix %});
                }
    :});
};
script(getUnaryExecuteBuildCode)args($className, $postfix)
{
    return(block
    {:
                if (m_IsAssignment && m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &{% $className %}::ExecuteG2G{% $postfix %});
                }
                else if(m_LoadInfo1.IsGlobal) {
                    executor.attach(this, &{% $className %}::ExecuteG{% $postfix %});
                } else {
                    executor.attach(this, &{% $className %}::ExecuteL{% $postfix %});
                }
    :});
};
script(writeBinaryExp)args($className, $op)
{
    $strOps = {
        "+" => true,
        ">" => true,
        ">=" => true,
        "<" => true,
        "<=" => true,
        "==" => true,
        "!=" => true
    };
    $floatOps = {
        "+" => true,
        "-" => true,
        "*" => true,
        "/" => true
    };
    $cmpOps = {
        ">" => true,
        ">=" => true,
        "<" => true,
        "<=" => true,
        "==" => true,
        "!=" => true
    };
    $logicOps = {
        "&&" => true,
        "||" => true
    };

    $checkString = hashtableget($strOps, $op);
    $checkFloat = hashtableget($floatOps, $op);
    $boolRet = hashtableget($cmpOps, $op);
    $logicArith = hashtableget($logicOps, $op);

    $maxType = "BRACE_DATA_TYPE_UINT64";
    $buildArithExecutor = "";

    if($boolRet){
        $maxType = "BRACE_DATA_TYPE_STRING";
        $buildArithExecutor = block
        {:
            else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
                resultType = BRACE_DATA_TYPE_BOOL;
                switch (m_LoadInfo1.Type) {
                case BRACE_DATA_TYPE_BOOL:
{% getBinaryExecuteBuildCode($className, "BoolBoth"); %}
                    break;
                case BRACE_DATA_TYPE_INT8:
{% getBinaryExecuteBuildCode($className, "Int8Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT16:
{% getBinaryExecuteBuildCode($className, "Int16Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT32:
{% getBinaryExecuteBuildCode($className, "Int32Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT64:
{% getBinaryExecuteBuildCode($className, "Int64Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT8:
{% getBinaryExecuteBuildCode($className, "UInt8Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT16:
{% getBinaryExecuteBuildCode($className, "UInt16Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT32:
{% getBinaryExecuteBuildCode($className, "UInt32Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT64:
{% getBinaryExecuteBuildCode($className, "UInt64Both"); %}
                    break;
                case BRACE_DATA_TYPE_FLOAT:
{% getBinaryExecuteBuildCode($className, "FloatBoth"); %}
                    break;
                case BRACE_DATA_TYPE_DOUBLE:
{% getBinaryExecuteBuildCode($className, "DoubleBoth"); %}
                    break;
                case BRACE_DATA_TYPE_STRING:
{% getBinaryExecuteBuildCode($className, "StringBoth"); %}
                    break;
                }
            }
            else if (NeedStringArithUnit(load1.Type, load2.Type)) {
                resultType = BRACE_DATA_TYPE_BOOL;
{% getBinaryExecuteBuildCode($className, "String"); %}
            }
            else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
                resultType = BRACE_DATA_TYPE_BOOL;
{% getBinaryExecuteBuildCode($className, "Float"); %}
            }
            else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
                resultType = BRACE_DATA_TYPE_BOOL;
{% getBinaryExecuteBuildCode($className, "UInt"); %}
            }
            else {
                resultType = BRACE_DATA_TYPE_BOOL;
{% getBinaryExecuteBuildCode($className, "Int"); %}
            }
        :};
        $executeCode = block
        {:
{% getBinaryExecuteCodeBoth("BoolBoth", "bool", "VarGetBool", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("Int8Both", "int8_t", "VarGetInt8", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("Int16Both", "int16_t", "VarGetInt16", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("Int32Both", "int32_t", "VarGetInt32", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("Int64Both", "int64_t", "VarGetInt64", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("UInt8Both", "uint8_t", "VarGetUInt8", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("UInt16Both", "uint16_t", "VarGetUInt16", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("UInt32Both", "uint32_t", "VarGetUInt32", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("UInt64Both", "uint64_t", "VarGetUInt64", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("FloatBoth", "float", "VarGetFloat", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("DoubleBoth", "double", "VarGetDouble", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("StringBoth", "const std::string&", "VarGetString", "VarSetBool", $op); %}
{% getBinaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetBoolean", $op); %}
{% getBinaryExecuteCode("UInt", "uint64_t", "VarGetU64", "VarSetBoolean", $op); %}
{% getBinaryExecuteCode("Float", "double", "VarGetF64", "VarSetBoolean", $op); %}
{% getBinaryExecuteCode("String", "std::string", "VarGetStr", "VarSetBoolean", $op); %}
        :};
    }
    elseif($checkString){
        $maxType = "BRACE_DATA_TYPE_STRING";
        $buildArithExecutor = block
        {:
            else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
                resultType = m_LoadInfo1.Type;
                switch (m_LoadInfo1.Type) {
                case BRACE_DATA_TYPE_BOOL:
{% getBinaryExecuteBuildCode($className, "BoolBoth"); %}
                    break;
                case BRACE_DATA_TYPE_INT8:
{% getBinaryExecuteBuildCode($className, "Int8Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT16:
{% getBinaryExecuteBuildCode($className, "Int16Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT32:
{% getBinaryExecuteBuildCode($className, "Int32Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT64:
{% getBinaryExecuteBuildCode($className, "Int64Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT8:
{% getBinaryExecuteBuildCode($className, "UInt8Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT16:
{% getBinaryExecuteBuildCode($className, "UInt16Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT32:
{% getBinaryExecuteBuildCode($className, "UInt32Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT64:
{% getBinaryExecuteBuildCode($className, "UInt64Both"); %}
                    break;
                case BRACE_DATA_TYPE_FLOAT:
{% getBinaryExecuteBuildCode($className, "FloatBoth"); %}
                    break;
                case BRACE_DATA_TYPE_DOUBLE:
{% getBinaryExecuteBuildCode($className, "DoubleBoth"); %}
                    break;
                case BRACE_DATA_TYPE_STRING:
{% getBinaryExecuteBuildCode($className, "StringBoth"); %}
                    break;
                }
            }
            else if (NeedStringArithUnit(load1.Type, load2.Type)) {
{% getBinaryExecuteBuildCode($className, "String"); %}
            }
            else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
{% getBinaryExecuteBuildCode($className, "Float"); %}
            }
            else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
{% getBinaryExecuteBuildCode($className, "UInt"); %}
            }
            else {
{% getBinaryExecuteBuildCode($className, "Int"); %}
            }
        :};
        $executeCode = block
        {:
{% getBinaryExecuteCodeBoth("BoolBoth", "bool", "VarGetBool", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("Int8Both", "int8_t", "VarGetInt8", "VarSetInt8", $op); %}
{% getBinaryExecuteCodeBoth("Int16Both", "int16_t", "VarGetInt16", "VarSetInt16", $op); %}
{% getBinaryExecuteCodeBoth("Int32Both", "int32_t", "VarGetInt32", "VarSetInt32", $op); %}
{% getBinaryExecuteCodeBoth("Int64Both", "int64_t", "VarGetInt64", "VarSetInt64", $op); %}
{% getBinaryExecuteCodeBoth("UInt8Both", "uint8_t", "VarGetUInt8", "VarSetUInt8", $op); %}
{% getBinaryExecuteCodeBoth("UInt16Both", "uint16_t", "VarGetUInt16", "VarSetUInt16", $op); %}
{% getBinaryExecuteCodeBoth("UInt32Both", "uint32_t", "VarGetUInt32", "VarSetUInt32", $op); %}
{% getBinaryExecuteCodeBoth("UInt64Both", "uint64_t", "VarGetUInt64", "VarSetUInt64", $op); %}
{% getBinaryExecuteCodeBoth("FloatBoth", "float", "VarGetFloat", "VarSetFloat", $op); %}
{% getBinaryExecuteCodeBoth("DoubleBoth", "double", "VarGetDouble", "VarSetDouble", $op); %}
{% getBinaryExecuteCodeBoth("StringBoth", "const std::string&", "VarGetString", "VarSetString", $op); %}
{% getBinaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetI64", $op); %}
{% getBinaryExecuteCode("UInt", "uint64_t", "VarGetU64", "VarSetU64", $op); %}
{% getBinaryExecuteCode("Float", "double", "VarGetF64", "VarSetF64", $op); %}
{% getBinaryExecuteCode("String", "std::string", "VarGetStr", "VarSetStr", $op); %}
        :};
    }
    elseif($checkFloat){
        $maxType = "BRACE_DATA_TYPE_DOUBLE";
        $buildArithExecutor = block
        {:
            else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
                resultType = m_LoadInfo1.Type;
                switch (m_LoadInfo1.Type) {
                case BRACE_DATA_TYPE_INT8:
{% getBinaryExecuteBuildCode($className, "Int8Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT16:
{% getBinaryExecuteBuildCode($className, "Int16Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT32:
{% getBinaryExecuteBuildCode($className, "Int32Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT64:
{% getBinaryExecuteBuildCode($className, "Int64Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT8:
{% getBinaryExecuteBuildCode($className, "UInt8Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT16:
{% getBinaryExecuteBuildCode($className, "UInt16Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT32:
{% getBinaryExecuteBuildCode($className, "UInt32Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT64:
{% getBinaryExecuteBuildCode($className, "UInt64Both"); %}
                    break;
                case BRACE_DATA_TYPE_FLOAT:
{% getBinaryExecuteBuildCode($className, "FloatBoth"); %}
                    break;
                case BRACE_DATA_TYPE_DOUBLE:
{% getBinaryExecuteBuildCode($className, "DoubleBoth"); %}
                    break;
                }
            }
            else if (NeedFloatArithUnit(load1.Type, load2.Type)) {
{% getBinaryExecuteBuildCode($className, "Float"); %}
            }
            else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
{% getBinaryExecuteBuildCode($className, "UInt"); %}
            }
            else {
{% getBinaryExecuteBuildCode($className, "Int"); %}
            }
        :};
        $executeCode = block
        {:
{% getBinaryExecuteCodeBoth("Int8Both", "int8_t", "VarGetInt8", "VarSetInt8", $op); %}
{% getBinaryExecuteCodeBoth("Int16Both", "int16_t", "VarGetInt16", "VarSetInt16", $op); %}
{% getBinaryExecuteCodeBoth("Int32Both", "int32_t", "VarGetInt32", "VarSetInt32", $op); %}
{% getBinaryExecuteCodeBoth("Int64Both", "int64_t", "VarGetInt64", "VarSetInt64", $op); %}
{% getBinaryExecuteCodeBoth("UInt8Both", "uint8_t", "VarGetUInt8", "VarSetUInt8", $op); %}
{% getBinaryExecuteCodeBoth("UInt16Both", "uint16_t", "VarGetUInt16", "VarSetUInt16", $op); %}
{% getBinaryExecuteCodeBoth("UInt32Both", "uint32_t", "VarGetUInt32", "VarSetUInt32", $op); %}
{% getBinaryExecuteCodeBoth("UInt64Both", "uint64_t", "VarGetUInt64", "VarSetUInt64", $op); %}
{% getBinaryExecuteCodeBoth("FloatBoth", "float", "VarGetFloat", "VarSetFloat", $op); %}
{% getBinaryExecuteCodeBoth("DoubleBoth", "double", "VarGetDouble", "VarSetDouble", $op); %}
{% getBinaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetI64", $op); %}
{% getBinaryExecuteCode("UInt", "uint64_t", "VarGetU64", "VarSetU64", $op); %}
{% getBinaryExecuteCode("Float", "double", "VarGetF64", "VarSetF64", $op); %}
        :};
    }
    elseif($logicArith){
        $maxType = "BRACE_DATA_TYPE_UINT64";
        $buildArithExecutor = block
        {:
            else if (m_LoadInfo1.Type == m_LoadInfo2.Type) {
                resultType = BRACE_DATA_TYPE_BOOL;
                switch (m_LoadInfo1.Type) {
                case BRACE_DATA_TYPE_BOOL:
{% getBinaryExecuteBuildCode($className, "BoolBoth"); %}
                    break;
                case BRACE_DATA_TYPE_INT8:
{% getBinaryExecuteBuildCode($className, "Int8Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT16:
{% getBinaryExecuteBuildCode($className, "Int16Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT32:
{% getBinaryExecuteBuildCode($className, "Int32Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT64:
{% getBinaryExecuteBuildCode($className, "Int64Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT8:
{% getBinaryExecuteBuildCode($className, "UInt8Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT16:
{% getBinaryExecuteBuildCode($className, "UInt16Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT32:
{% getBinaryExecuteBuildCode($className, "UInt32Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT64:
{% getBinaryExecuteBuildCode($className, "UInt64Both"); %}
                    break;
                }
            }
            else {
                resultType = BRACE_DATA_TYPE_BOOL;
{% getBinaryExecuteBuildCode($className, "Bool"); %}
            }
        :};
        $executeCode = block
        {:
{% getBinaryExecuteCodeBoth("BoolBoth", "bool", "VarGetBool", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("Int8Both", "int8_t", "VarGetInt8", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("Int16Both", "int16_t", "VarGetInt16", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("Int32Both", "int32_t", "VarGetInt32", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("Int64Both", "int64_t", "VarGetInt64", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("UInt8Both", "uint8_t", "VarGetUInt8", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("UInt16Both", "uint16_t", "VarGetUInt16", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("UInt32Both", "uint32_t", "VarGetUInt32", "VarSetBool", $op); %}
{% getBinaryExecuteCodeBoth("UInt64Both", "uint64_t", "VarGetUInt64", "VarSetBool", $op); %}
{% getBinaryExecuteCode("Bool", "bool", "VarGetBoolean", "VarSetBoolean", $op); %}
        :};
    }
    else{
        $maxType = "BRACE_DATA_TYPE_UINT64";
        $buildArithExecutor = block
        {:
            else if (m_LoadInfo1.Type == m_LoadInfo2.Type && m_LoadInfo1.Type != BRACE_DATA_TYPE_BOOL) {
                resultType = m_LoadInfo1.Type;
                switch (m_LoadInfo1.Type) {
                case BRACE_DATA_TYPE_INT8:
{% getBinaryExecuteBuildCode($className, "Int8Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT16:
{% getBinaryExecuteBuildCode($className, "Int16Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT32:
{% getBinaryExecuteBuildCode($className, "Int32Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT64:
{% getBinaryExecuteBuildCode($className, "Int64Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT8:
{% getBinaryExecuteBuildCode($className, "UInt8Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT16:
{% getBinaryExecuteBuildCode($className, "UInt16Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT32:
{% getBinaryExecuteBuildCode($className, "UInt32Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT64:
{% getBinaryExecuteBuildCode($className, "UInt64Both"); %}
                    break;
                }
            }
            else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
{% getBinaryExecuteBuildCode($className, "UInt"); %}
            }
            else {
{% getBinaryExecuteBuildCode($className, "Int"); %}
            }
        :};
        $executeCode = block
        {:
{% getBinaryExecuteCodeBoth("Int8Both", "int8_t", "VarGetInt8", "VarSetInt8", $op); %}
{% getBinaryExecuteCodeBoth("Int16Both", "int16_t", "VarGetInt16", "VarSetInt16", $op); %}
{% getBinaryExecuteCodeBoth("Int32Both", "int32_t", "VarGetInt32", "VarSetInt32", $op); %}
{% getBinaryExecuteCodeBoth("Int64Both", "int64_t", "VarGetInt64", "VarSetInt64", $op); %}
{% getBinaryExecuteCodeBoth("UInt8Both", "uint8_t", "VarGetUInt8", "VarSetUInt8", $op); %}
{% getBinaryExecuteCodeBoth("UInt16Both", "uint16_t", "VarGetUInt16", "VarSetUInt16", $op); %}
{% getBinaryExecuteCodeBoth("UInt32Both", "uint32_t", "VarGetUInt32", "VarSetUInt32", $op); %}
{% getBinaryExecuteCodeBoth("UInt64Both", "uint64_t", "VarGetUInt64", "VarSetUInt64", $op); %}
{% getBinaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetI64", $op); %}
{% getBinaryExecuteCode("UInt", "uint64_t", "VarGetU64", "VarSetU64", $op); %}
        :};
    };

    writeblock
    {:
    class {% $className %} final : public BinaryArithLogicBaseExp
    {
    public:
        {% $className %}(BraceScript& interpreter, bool isAssignment) :BinaryArithLogicBaseExp(interpreter, isAssignment)
        {
        }
    protected:
        virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, const DataTypeInfo& load2, int& resultType, BraceApiExecutor& executor) const override
        {
            resultType = GetMaxType(load1.Type, load2.Type);
            if (resultType > {% $maxType %}) {
                std::stringstream ss;
                ss << "operator {% $op %}, operand type dismatch, " << GetDataTypeName(load1.Type) << " and " << GetDataTypeName(load2.Type) << ", line " << data.GetLine();
                LogError(ss.str());
                return false;
            }
{% $buildArithExecutor %}
            return true;
        }
    private:
{% $executeCode %}
    };
    :};
};
script(writeUnaryNumericExp)args($className, $op)
{
    if($op=="~"){
        $maxType = "BRACE_DATA_TYPE_UINT64";
        $buildArithExecutor = block
        {:
            else if (m_LoadInfo1.Type >= BRACE_DATA_TYPE_INT8 && m_LoadInfo1.Type <= BRACE_DATA_TYPE_UINT64) {
                resultType = m_LoadInfo1.Type;
                switch (m_LoadInfo1.Type) {
                case BRACE_DATA_TYPE_INT8:
{% getUnaryExecuteBuildCode($className, "Int8Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT16:
{% getUnaryExecuteBuildCode($className, "Int16Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT32:
{% getUnaryExecuteBuildCode($className, "Int32Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT64:
{% getUnaryExecuteBuildCode($className, "Int64Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT8:
{% getUnaryExecuteBuildCode($className, "UInt8Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT16:
{% getUnaryExecuteBuildCode($className, "UInt16Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT32:
{% getUnaryExecuteBuildCode($className, "UInt32Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT64:
{% getUnaryExecuteBuildCode($className, "UInt64Both"); %}
                    break;
                }
            }
            else if(IsUnsignedType(resultType)) {
{% getUnaryExecuteBuildCode($className, "UInt"); %}
            }
            else {
{% getUnaryExecuteBuildCode($className, "Int"); %}
            }
        :};

        $executeCode = block
        {:
{% getUnaryExecuteCodeBoth("Int8Both", "int8_t", "VarGetInt8", "VarSetInt8", $op); %}
{% getUnaryExecuteCodeBoth("Int16Both", "int16_t", "VarGetInt16", "VarSetInt16", $op); %}
{% getUnaryExecuteCodeBoth("Int32Both", "int32_t", "VarGetInt32", "VarSetInt32", $op); %}
{% getUnaryExecuteCodeBoth("Int64Both", "int64_t", "VarGetInt64", "VarSetInt64", $op); %}
{% getUnaryExecuteCodeBoth("UInt8Both", "uint8_t", "VarGetUInt8", "VarSetUInt8", $op); %}
{% getUnaryExecuteCodeBoth("UInt16Both", "uint16_t", "VarGetUInt16", "VarSetUInt16", $op); %}
{% getUnaryExecuteCodeBoth("UInt32Both", "uint32_t", "VarGetUInt32", "VarSetUInt32", $op); %}
{% getUnaryExecuteCodeBoth("UInt64Both", "uint64_t", "VarGetUInt64", "VarSetUInt64", $op); %}
{% getUnaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetI64", $op); %}
{% getUnaryExecuteCode("UInt", "uint64_t", "VarGetU64", "VarSetU64", $op); %}
        :};
    }
    elseif ($op == "-") {
        $maxType = "BRACE_DATA_TYPE_DOUBLE";
        $buildArithExecutor = block
        {:
            else if (IsSignedType(m_LoadInfo1.Type) || IsFloatType(m_LoadInfo1.Type)) {
                resultType = m_LoadInfo1.Type;
                switch (m_LoadInfo1.Type) {
                case BRACE_DATA_TYPE_INT8:
{% getUnaryExecuteBuildCode($className, "Int8Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT16:
{% getUnaryExecuteBuildCode($className, "Int16Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT32:
{% getUnaryExecuteBuildCode($className, "Int32Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT64:
{% getUnaryExecuteBuildCode($className, "Int64Both"); %}
                    break;
                case BRACE_DATA_TYPE_FLOAT:
{% getUnaryExecuteBuildCode($className, "FloatBoth"); %}
                    break;
                case BRACE_DATA_TYPE_DOUBLE:
{% getUnaryExecuteBuildCode($className, "DoubleBoth"); %}
                    break;
                }
            }
            else {
{% getUnaryExecuteBuildCode($className, "Int"); %}
            }
        :};

        $executeCode = block
        {:
{% getUnaryExecuteCodeBoth("Int8Both", "int8_t", "VarGetInt8", "VarSetInt8", $op); %}
{% getUnaryExecuteCodeBoth("Int16Both", "int16_t", "VarGetInt16", "VarSetInt16", $op); %}
{% getUnaryExecuteCodeBoth("Int32Both", "int32_t", "VarGetInt32", "VarSetInt32", $op); %}
{% getUnaryExecuteCodeBoth("Int64Both", "int64_t", "VarGetInt64", "VarSetInt64", $op); %}
{% getUnaryExecuteCodeBoth("FloatBoth", "float", "VarGetFloat", "VarSetFloat", $op); %}
{% getUnaryExecuteCodeBoth("DoubleBoth", "double", "VarGetDouble", "VarSetDouble", $op); %}
{% getUnaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetI64", $op); %}
{% getUnaryExecuteCode("Float", "double", "VarGetF64", "VarSetF64", $op); %}
        :};
    }
    else{
        $maxType = "BRACE_DATA_TYPE_DOUBLE";
        $buildArithExecutor = block
        {:
            else if (m_LoadInfo1.Type >= BRACE_DATA_TYPE_INT8 && m_LoadInfo1.Type <= BRACE_DATA_TYPE_DOUBLE) {
                resultType = m_LoadInfo1.Type;
                switch (m_LoadInfo1.Type) {
                case BRACE_DATA_TYPE_INT8:
{% getUnaryExecuteBuildCode($className, "Int8Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT16:
{% getUnaryExecuteBuildCode($className, "Int16Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT32:
{% getUnaryExecuteBuildCode($className, "Int32Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT64:
{% getUnaryExecuteBuildCode($className, "Int64Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT8:
{% getUnaryExecuteBuildCode($className, "UInt8Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT16:
{% getUnaryExecuteBuildCode($className, "UInt16Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT32:
{% getUnaryExecuteBuildCode($className, "UInt32Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT64:
{% getUnaryExecuteBuildCode($className, "UInt64Both"); %}
                    break;
                case BRACE_DATA_TYPE_FLOAT:
{% getUnaryExecuteBuildCode($className, "FloatBoth"); %}
                    break;
                case BRACE_DATA_TYPE_DOUBLE:
{% getUnaryExecuteBuildCode($className, "DoubleBoth"); %}
                    break;
                }
            }
            else if(IsFloatType(resultType)) {
{% getUnaryExecuteBuildCode($className, "Float"); %}
            }
            else if(IsUnsignedType(resultType)) {
{% getUnaryExecuteBuildCode($className, "UInt"); %}
            }
            else {
{% getUnaryExecuteBuildCode($className, "Int"); %}
            }
        :};

        $executeCode = block
        {:
{% getUnaryExecuteCodeBoth("Int8Both", "int8_t", "VarGetInt8", "VarSetInt8", $op); %}
{% getUnaryExecuteCodeBoth("Int16Both", "int16_t", "VarGetInt16", "VarSetInt16", $op); %}
{% getUnaryExecuteCodeBoth("Int32Both", "int32_t", "VarGetInt32", "VarSetInt32", $op); %}
{% getUnaryExecuteCodeBoth("Int64Both", "int64_t", "VarGetInt64", "VarSetInt64", $op); %}
{% getUnaryExecuteCodeBoth("UInt8Both", "uint8_t", "VarGetUInt8", "VarSetUInt8", $op); %}
{% getUnaryExecuteCodeBoth("UInt16Both", "uint16_t", "VarGetUInt16", "VarSetUInt16", $op); %}
{% getUnaryExecuteCodeBoth("UInt32Both", "uint32_t", "VarGetUInt32", "VarSetUInt32", $op); %}
{% getUnaryExecuteCodeBoth("UInt64Both", "uint64_t", "VarGetUInt64", "VarSetUInt64", $op); %}
{% getUnaryExecuteCodeBoth("FloatBoth", "float", "VarGetFloat", "VarSetFloat", $op); %}
{% getUnaryExecuteCodeBoth("DoubleBoth", "double", "VarGetDouble", "VarSetDouble", $op); %}
{% getUnaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetI64", $op); %}
{% getUnaryExecuteCode("UInt", "uint64_t", "VarGetU64", "VarSetU64", $op); %}
{% getUnaryExecuteCode("Float", "double", "VarGetF64", "VarSetF64", $op); %}
        :};
    };
    writeblock
    {:
    class {% $className %} final : public UnaryArithLogicBaseExp
    {
    public:
        {% $className %}(BraceScript& interpreter, bool isAssignment) :UnaryArithLogicBaseExp(interpreter, isAssignment)
        {
        }
    protected:
        virtual bool BuildExecutor(const DslData::FunctionData& data, const DataTypeInfo& load1, int& resultType, BraceApiExecutor& executor) const override
        {
            resultType = load1.Type;
            if (resultType >= {% $maxType %}) {
                std::stringstream ss;
                ss << "operator {% $op %}, operand type dismatch, " << GetDataTypeName(m_LoadInfo1.Type) << ", line " << data.GetLine();
                LogError(ss.str());
                return false;
            }
{% $buildArithExecutor %}
            return true;
        }
    private:
{% $executeCode %}
    };
    :};
};
script(writeNotExp)
{
    writeblock
    {:
    class NotExp final : public UnaryArithLogicBaseExp
    {
    public:
        NotExp(BraceScript& interpreter, bool isAssignment) :UnaryArithLogicBaseExp(interpreter, isAssignment)
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
{% getUnaryExecuteBuildCode("NotExp", "BoolBoth"); %}
                    break;
                case BRACE_DATA_TYPE_INT8:
{% getUnaryExecuteBuildCode("NotExp", "Int8Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT16:
{% getUnaryExecuteBuildCode("NotExp", "Int16Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT32:
{% getUnaryExecuteBuildCode("NotExp", "Int32Both"); %}
                    break;
                case BRACE_DATA_TYPE_INT64:
{% getUnaryExecuteBuildCode("NotExp", "Int64Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT8:
{% getUnaryExecuteBuildCode("NotExp", "UInt8Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT16:
{% getUnaryExecuteBuildCode("NotExp", "UInt16Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT32:
{% getUnaryExecuteBuildCode("NotExp", "UInt32Both"); %}
                    break;
                case BRACE_DATA_TYPE_UINT64:
{% getUnaryExecuteBuildCode("NotExp", "UInt64Both"); %}
                    break;
                }
            }
            else {
                resultType = BRACE_DATA_TYPE_BOOL;
{% getUnaryExecuteBuildCode("NotExp", "Bool"); %}
            }
            return true;
        }
    private:
{% getUnaryExecuteCodeBoth("BoolBoth", "bool", "VarGetBool", "VarSetBool", "!"); %}
{% getUnaryExecuteCodeBoth("Int8Both", "int8_t", "VarGetInt8", "VarSetBool", "!"); %}
{% getUnaryExecuteCodeBoth("Int16Both", "int16_t", "VarGetInt16", "VarSetBool", "!"); %}
{% getUnaryExecuteCodeBoth("Int32Both", "int32_t", "VarGetInt32", "VarSetBool", "!"); %}
{% getUnaryExecuteCodeBoth("Int64Both", "int64_t", "VarGetInt64", "VarSetBool", "!"); %}
{% getUnaryExecuteCodeBoth("UInt8Both", "uint8_t", "VarGetUInt8", "VarSetBool", "!"); %}
{% getUnaryExecuteCodeBoth("UInt16Both", "uint16_t", "VarGetUInt16", "VarSetBool", "!"); %}
{% getUnaryExecuteCodeBoth("UInt32Both", "uint32_t", "VarGetUInt32", "VarSetBool", "!"); %}
{% getUnaryExecuteCodeBoth("UInt64Both", "uint64_t", "VarGetUInt64", "VarSetBool", "!"); %}
{% getUnaryExecuteCode("Bool", "bool", "VarGetBoolean", "VarSetBoolean", "!"); %}
    };
    :};
};