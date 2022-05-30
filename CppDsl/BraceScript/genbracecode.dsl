script(main)
{
    $braceTypes = ["BRACE_DATA_TYPE_BOOL", "BRACE_DATA_TYPE_INT8", "BRACE_DATA_TYPE_INT16", "BRACE_DATA_TYPE_INT32", "BRACE_DATA_TYPE_INT64"
        , "BRACE_DATA_TYPE_UINT8", "BRACE_DATA_TYPE_UINT16", "BRACE_DATA_TYPE_UINT32", "BRACE_DATA_TYPE_UINT64"
        , "BRACE_DATA_TYPE_FLOAT", "BRACE_DATA_TYPE_DOUBLE"];
    $braceTypeNames = ["Bool", "Int8", "Int16", "Int32", "Int64"
        , "Uint8", "Uint16", "Uint32", "Uint64"
        , "Float", "Double"];
    $cppTypes = ["bool", "int8_t", "int16_t", "int32_t", "int64_t"
        , "uint8_t", "uint16_t", "uint32_t", "uint64_t"
        , "float", "double"];
    $fullTypeNames = ["Bool", "Int8", "Int16", "Int32", "Int64"
        , "Uint8", "Uint16", "Uint32", "Uint64"
        , "Float", "Double", "String", "Object"];

    call("writeVarAssign", $fullTypeNames);

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

    call("writeBitNotExp");
    call("writeNotExp");

    return(0);
};
script(writeVarAssign)args($fullTypeNames)
{
    //VarAssign
    loop(listsize($fullTypeNames)){
        $typeName = $fullTypeNames[$$];

        writeblock
        {:
    static inline void VarAssign{% $typeName %}(VariableInfo& info, int destIndex, VariableInfo& srcInfo, int srcIndex)
    {
        info.{% $typeName %}Vars[destIndex] = srcInfo.{% $typeName %}Vars[srcIndex];
    }
        :};        
    };
    //VarAssignFromRef
    loop(listsize($fullTypeNames)){
        $typeName = $fullTypeNames[$$];

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
    loop(listsize($fullTypeNames)){
        $typeName = $fullTypeNames[$$];

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
    loop(listsize($fullTypeNames)){
        $typeName = $fullTypeNames[$$];

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
        info.{% $firstName %}Vars[destIndex] = static_cast<{% $firstType %}>(srcInfo.{% $secondName %}Vars[srcIndex]);
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
        info.{% $firstName %}Vars[destIndex] = static_cast<{% $firstType %}>(sri.Vars->{% $secondName %}Vars[sri.VarIndex]);
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
        ri.Vars->{% $firstName %}Vars[ri.VarIndex] = static_cast<{% $firstType %}>(srcInfo.{% $secondName %}Vars[srcIndex]);
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
        ri.Vars->{% $firstName %}Vars[ri.VarIndex] = static_cast<{% $firstType %}>(sri.Vars->{% $secondName %}Vars[sri.VarIndex]);
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
        int ExecuteGG{% $postfix %}(void) const
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteLL{% $postfix %}(void) const
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            {% $operandType %} v1 = {% $varGet %}(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(vars, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteGL{% $postfix %}(void) const
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
            auto& srcVars1 = *GlobalVariables();
            auto& srcVars2 = vars;
            {% $operandType %} v1 = {% $varGet %}(srcVars1, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $operandType %} v2 = {% $varGet %}(srcVars2, m_LoadInfo2.Type, m_LoadInfo2.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, v1 {% $opr %} v2);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteLG{% $postfix %}(void) const
        {
            if (m_Op1)
                m_Op1();
            if (m_Op2)
                m_Op2();
            auto& vars = *CurRuntimeStack().Variables;
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
        int ExecuteG{% $postfix %}(void) const
        {
            if (m_Op1)
                m_Op1();
            auto& vars = *CurRuntimeStack().Variables;
            auto& srcVars = *GlobalVariables();
            {% $operandType %} v1 = {% $varGet %}(srcVars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, {% $opr %} v1);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
        int ExecuteL{% $postfix %}(void) const
        {
            if (m_Op1)
                m_Op1();
            auto& vars = *CurRuntimeStack().Variables;
            {% $operandType %} v1 = {% $varGet %}(vars, m_LoadInfo1.Type, m_LoadInfo1.VarIndex);
            {% $varSet %}(vars, m_ResultInfo.Type, m_ResultInfo.VarIndex, {% $opr %} v1);
            return BRACE_FLOW_CONTROL_NORMAL;
        }
    :});
};
script(getBinaryExecuteBuildCode)args($className, $postfix)
{
    return(block
    {:
                if(m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&{% $className %}::ExecuteGG{% $postfix %}, this);
                } else if (!m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&{% $className %}::ExecuteLL{% $postfix %}, this);
                } else if (m_LoadInfo1.IsGlobal && !m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&{% $className %}::ExecuteGL{% $postfix %}, this);
                } else if (!m_LoadInfo1.IsGlobal && m_LoadInfo2.IsGlobal) {
                    executor = std::bind(&{% $className %}::ExecuteLG{% $postfix %}, this);
                }
    :});
};
script(getUnaryExecuteBuildCode)args($className, $postfix)
{
    return(block
    {:
                if(m_LoadInfo1.IsGlobal) {
                    executor = std::bind(&{% $className %}::ExecuteG{% $postfix %}, this);
                } else {
                    executor = std::bind(&{% $className %}::ExecuteL{% $postfix %}, this);
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
{% getBinaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetI64", $op); %}
{% getBinaryExecuteCode("UInt", "uint64_t", "VarGetU64", "VarSetU64", $op); %}
{% getBinaryExecuteCode("Float", "double", "VarGetF64", "VarSetF64", $op); %}
        :};
    }
    elseif($logicArith){
        $maxType = "BRACE_DATA_TYPE_UINT64";
        $buildArithExecutor = block
        {:
            else {
                resultType = BRACE_DATA_TYPE_BOOL;
{% getBinaryExecuteBuildCode($className, "Bool"); %}
            }
        :};
        $executeCode = block
        {:
{% getBinaryExecuteCode("Bool", "bool", "VarGetBoolean", "VarSetBoolean", $op); %}
        :};
    }
    else{
        $maxType = "BRACE_DATA_TYPE_UINT64";
        $buildArithExecutor = block
        {:
            else if (NeedUnsignedArithUnit(load1.Type, load2.Type)) {
{% getBinaryExecuteBuildCode($className, "UInt"); %}
            }
            else {
{% getBinaryExecuteBuildCode($className, "Int"); %}
            }
        :};
        $executeCode = block
        {:
{% getBinaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetI64", $op); %}
{% getBinaryExecuteCode("UInt", "uint64_t", "VarGetU64", "VarSetU64", $op); %}
        :};
    };

    writeblock
    {:
    class {% $className %} final : public BinaryArithLogicBaseExp
    {
    public:
        {% $className %}(BraceScript& interpreter) :BinaryArithLogicBaseExp(interpreter)
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
script(writeBitNotExp)
{
    writeblock
    {:
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
            else if(IsUnsignedType(resultType)) {
{% getUnaryExecuteBuildCode("BitNotExp", "UInt"); %}
            }
            else {
{% getUnaryExecuteBuildCode("BitNotExp", "Int"); %}
            }
            return true;
        }
    private:
{% getUnaryExecuteCode("Int", "int64_t", "VarGetI64", "VarSetI64", "~"); %}
{% getUnaryExecuteCode("UInt", "uint64_t", "VarGetU64", "VarSetU64", "~"); %}
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
            else {
                resultType = BRACE_DATA_TYPE_BOOL;
{% getUnaryExecuteBuildCode("NotExp", "Bool"); %}
            }
            return true;
        }
    private:
{% getUnaryExecuteCode("Bool", "bool", "VarGetBoolean", "VarSetBoolean", "!"); %}
    };
    :};
};