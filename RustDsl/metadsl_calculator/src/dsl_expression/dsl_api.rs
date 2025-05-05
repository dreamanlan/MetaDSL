use metadsl::dsl::{
    self, FunctionData, ISyntaxComponent, StatementData, SyntaxComponent, ValueData, ValueOrFunction
};
use metadsl_macros::{
    add_abstract_expression_fields,
    impl_expression_with_abstract,
    impl_abstract_expression,
    add_abstract_and_simple_expression_fields,
    impl_abstract_with_simple,
    impl_simple_expression,
};
use crate::dsl_expression::dsl_calculator::{
    DslCalculatorCell,
    DslCalculatorValue,
    IExpression,
    AbstractExpression,
    SimpleExpressionBase,
    ExpressionBox,
    RunStateEnum,
};
//------------------------------------------------------------------------------------
#[add_abstract_and_simple_expression_fields]
struct DummyExp
{

}
impl<'a> Default for DummyExp<'a>
{
    fn default() -> Self
    {
        DummyExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DummyExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DummyExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DummyExp<'a>
{
    fn on_calc(&mut self, _operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
//------------------------------------------------------------------------------------
#[add_abstract_and_simple_expression_fields]
struct AddExp
{
}
impl<'a> Default for AddExp<'a>
{
    fn default() -> Self
    {
        AddExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AddExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AddExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AddExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_string() || v2.is_string() {
            return DslCalculatorValue::String(v1.to_string() + &v2.to_string());
        }
        else if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Double(v1.to_f64() + v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() + v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() + v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct SubExp
{
}
impl<'a> Default for SubExp<'a>
{
    fn default() -> Self
    {
        SubExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for SubExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for SubExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for SubExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Double(v1.to_f64() - v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() - v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() - v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct MulExp
{
}
impl<'a> Default for MulExp<'a>
{
    fn default() -> Self
    {
        MulExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for MulExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for MulExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for MulExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Double(v1.to_f64() * v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() * v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() * v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DivExp
{
}
impl<'a> Default for DivExp<'a>
{
    fn default() -> Self
    {
        DivExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DivExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DivExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DivExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Double(v1.to_f64() / v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() / v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() / v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ModExp
{
}
impl<'a> Default for ModExp<'a>
{
    fn default() -> Self
    {
        ModExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ModExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ModExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ModExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Double(v1.to_f64() % v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() % v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() % v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct BitAndExp
{
}
impl<'a> Default for BitAndExp<'a>
{
    fn default() -> Self
    {
        BitAndExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for BitAndExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for BitAndExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for BitAndExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() & v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() & v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct BitOrExp
{
}
impl<'a> Default for BitOrExp<'a>
{
    fn default() -> Self
    {
        BitOrExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for BitOrExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for BitOrExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for BitOrExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() | v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() | v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct BitXorExp
{
}
impl<'a> Default for BitXorExp<'a>
{
    fn default() -> Self
    {
        BitXorExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for BitXorExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for BitXorExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for BitXorExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() ^ v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() ^ v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct BitNotExp
{
}
impl<'a> Default for BitNotExp<'a>
{
    fn default() -> Self
    {
        BitNotExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for BitNotExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for BitNotExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for BitNotExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 1 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        if v1.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(! v1.to_u64());
        }
        else {
            return DslCalculatorValue::Long(! v1.to_i64());
        }
    }
    impl_simple_expression!();
}

#[add_abstract_and_simple_expression_fields]
struct LShiftExp
{
}
impl<'a> Default for LShiftExp<'a>
{
    fn default() -> Self
    {
        LShiftExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LShiftExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LShiftExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LShiftExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() << v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() << v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct RShiftExp
{
}
impl<'a> Default for RShiftExp<'a>
{
    fn default() -> Self
    {
        RShiftExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for RShiftExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for RShiftExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for RShiftExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Ulong(v1.to_u64() >> v2.to_u64());
        }
        else {
            return DslCalculatorValue::Long(v1.to_i64() >> v2.to_i64());
        }
    }
    impl_simple_expression!();
}

#[add_abstract_and_simple_expression_fields]
struct GreatExp
{
}
impl<'a> Default for GreatExp<'a>
{
    fn default() -> Self
    {
        GreatExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for GreatExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for GreatExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for GreatExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_string() || v2.is_string() {
            return DslCalculatorValue::Bool(v1.to_string() > v2.to_string());
        }
        else if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Bool(v1.to_f64() > v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Bool(v1.to_u64() > v2.to_u64());
        }
        else {
            return DslCalculatorValue::Bool(v1.to_i64() > v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct GreatEqualExp
{
}
impl<'a> Default for GreatEqualExp<'a>
{
    fn default() -> Self
    {
        GreatEqualExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for GreatEqualExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for GreatEqualExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for GreatEqualExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_string() || v2.is_string() {
            return DslCalculatorValue::Bool(v1.to_string() >= v2.to_string());
        }
        else if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Bool(v1.to_f64() >= v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Bool(v1.to_u64() >= v2.to_u64());
        }
        else {
            return DslCalculatorValue::Bool(v1.to_i64() >= v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LessExp
{
}
impl<'a> Default for LessExp<'a>
{
    fn default() -> Self
    {
        LessExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LessExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LessExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LessExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_string() || v2.is_string() {
            return DslCalculatorValue::Bool(v1.to_string() < v2.to_string());
        }
        else if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Bool(v1.to_f64() < v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Bool(v1.to_u64() < v2.to_u64());
        }
        else {
            return DslCalculatorValue::Bool(v1.to_i64() < v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LessEqualExp
{
}
impl<'a> Default for LessEqualExp<'a>
{
    fn default() -> Self
    {
        LessEqualExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LessEqualExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LessEqualExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LessEqualExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_string() || v2.is_string() {
            return DslCalculatorValue::Bool(v1.to_string() <= v2.to_string());
        }
        else if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Bool(v1.to_f64() <= v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Bool(v1.to_u64() <= v2.to_u64());
        }
        else {
            return DslCalculatorValue::Bool(v1.to_i64() <= v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct EqualExp
{
}
impl<'a> Default for EqualExp<'a>
{
    fn default() -> Self
    {
        EqualExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for EqualExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for EqualExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for EqualExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_string() || v2.is_string() {
            return DslCalculatorValue::Bool(v1.to_string() == v2.to_string());
        }
        else if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Bool(v1.to_f64() == v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Bool(v1.to_u64() == v2.to_u64());
        }
        else {
            return DslCalculatorValue::Bool(v1.to_i64() == v2.to_i64());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct NotEqualExp
{
}
impl<'a> Default for NotEqualExp<'a>
{
    fn default() -> Self
    {
        NotEqualExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for NotEqualExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for NotEqualExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for NotEqualExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_string() || v2.is_string() {
            return DslCalculatorValue::Bool(v1.to_string() != v2.to_string());
        }
        else if v1.is_float() || v2.is_float() {
            return DslCalculatorValue::Bool(v1.to_f64() != v2.to_f64());
        }
        else if v1.is_unsigned_integer() && v2.is_unsigned_integer() {
            return DslCalculatorValue::Bool(v1.to_u64() != v2.to_u64());
        }
        else {
            return DslCalculatorValue::Bool(v1.to_i64() != v2.to_i64());
        }
    }
    impl_simple_expression!();
}

#[add_abstract_and_simple_expression_fields]
struct AndExp
{
}
impl<'a> Default for AndExp<'a>
{
    fn default() -> Self
    {
        AndExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AndExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AndExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AndExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_bool() && v2.is_bool() {
            return DslCalculatorValue::Bool(v1.get_bool() && v2.get_bool());
        }
        else {
            return DslCalculatorValue::Bool(v1.to_bool() && v2.to_bool());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct OrExp
{
}
impl<'a> Default for OrExp<'a>
{
    fn default() -> Self
    {
        OrExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for OrExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for OrExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for OrExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        let v2 = &operands[1];
        if v1.is_bool() && v2.is_bool() {
            return DslCalculatorValue::Bool(v1.get_bool() || v2.get_bool());
        }
        else {
            return DslCalculatorValue::Bool(v1.to_bool() || v2.to_bool());
        }
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct NotExp
{
}
impl<'a> Default for NotExp<'a>
{
    fn default() -> Self
    {
        NotExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for NotExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for NotExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for NotExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() != 2 {
            return DslCalculatorValue::Null;
        }
        let v1 = &operands[0];
        if v1.is_bool() {
            return DslCalculatorValue::Bool(! v1.get_bool());
        }
        else {
            return DslCalculatorValue::Bool(! v1.to_bool());
        }
    }
    impl_simple_expression!();
}

#[add_abstract_expression_fields]
pub struct CondExp<'a>
{
    m_op1: Option<ExpressionBox<'a>>,
    m_op2: Option<ExpressionBox<'a>>,
    m_op3: Option<ExpressionBox<'a>>,
}
impl<'a> Default for CondExp<'a>
{
    fn default() -> Self
    {
        CondExp {
            m_op1: None,
            m_op2: None,
            m_op3: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CondExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CondExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        let mut v1 = DslCalculatorValue::Null;
        if let Some(op1) = &mut self.m_op1 {
            v1 = op1.calc();
        }
        if let Some(op2) = &mut self.m_op2 {
            if let Some(op3) = &mut self.m_op3 {
                let v = if v1.to_i64() != 0 { op2.calc() } else { op3.calc() };
                return v;
            }
        }
        return DslCalculatorValue::Null;
    }
    fn load_statement(&mut self, statement: &StatementData) -> bool
    {
        if let Some(f1) = statement.first() {
            if let Some(f2) = statement.second() {
                if let ValueOrFunction::Function(func_data1) = f1 {
                    if let ValueOrFunction::Function(func_data2) = f2 {
                        if func_data1.is_high_order() && func_data1.have_lower_order_param() && func_data2.get_id() == ":" && func_data2.have_param_or_statement() {
                            if let Some(lf) = func_data1.lower_order_function() {
                                if let Some(p) = lf.get_param(0) {
                                    self.m_op1 = self.calculator().borrow_mut().load_syntax_component(p);
                                }
                                if let Some(p) = func_data1.get_param(0) {
                                    self.m_op2 = self.calculator().borrow_mut().load_syntax_component(p);
                                }
                                if let Some(p) = func_data2.get_param(0) {
                                    self.m_op3 = self.calculator().borrow_mut().load_syntax_component(p);
                                }
                            }
                        }
                        else {
                            //error
                            self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", statement.to_script_string(false, &dsl::DEFAULT_DELIM), statement.get_line()));
                        }
                    }
                }
            }
        }
        return true;
    }

    impl_abstract_expression!();
}
struct IfClause<'a>
{
    pub condition: Option<ExpressionBox<'a>>,
    pub expressions: Vec<ExpressionBox<'a>>,
}
impl<'a> IfClause<'a>
{
    pub fn new() -> Self
    {
        IfClause {
            condition: None,
            expressions: Vec::new(),
        }
    }
}
#[add_abstract_expression_fields]
pub struct IfExp<'a>
{
    m_clauses: Vec<IfClause<'a>>,
}
impl<'a> Default for IfExp<'a>
{
    fn default() -> Self
    {
        IfExp {
            m_clauses: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IfExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IfExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        let mut v = DslCalculatorValue::Null;
        let mut ix = 0;
        while ix < self.m_clauses.len() {
            let mut need_run = false;
            if let Some(cond) = &mut self.m_clauses[ix].condition {
                let cond_val = cond.calc();
                if cond_val.to_i64() != 0 {
                    need_run = true;
                }
            }
            else if ix == self.m_clauses.len() - 1 {
                need_run = true;
            }
            if need_run {
                let ct = self.m_clauses[ix].expressions.len();
                let mut exp_ix = 0;
                while exp_ix < ct {
                    let exp = &mut self.m_clauses[ix].expressions[exp_ix];
                    v = exp.calc();
                    if self.need_return() {
                        return v;
                    }
                    exp_ix += 1;
                }
                break;
            }
            ix += 1;
        }
        return v;
    }
    fn load_function(&mut self, func: &FunctionData) -> bool
    {
        if func.is_high_order() {
            let mut item = IfClause::new();
            if let Some(lf) = func.lower_order_function() {
                if let Some(cond) = lf.get_param(0) {
                    item.condition = self.calculator().borrow_mut().load_syntax_component(cond);
                }
            }
            if let Some(ps) = func.params() {
                for p in ps.iter() {
                    if let Some(sub_exp) = self.calculator().borrow_mut().load_syntax_component(p) {
                        item.expressions.push(sub_exp);
                    }
                }
            }
            self.m_clauses.push(item);
        }
        else {
            //error
            self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
        }
        return true;
    }
    fn load_statement(&mut self, statement: &StatementData) -> bool
    {
        //the handling of the simple syntax 'if(exp) func(args);'.
        let func_num = statement.get_function_num();
        if func_num == 2 {
            if let Some(fir) = statement.first() {
                if let Some(sec) = statement.second() {
                    if let ValueOrFunction::Function(first) = fir {
                        if let ValueOrFunction::Function(second) = sec {
                            let first_id = first.get_id();
                            let second_id = second.get_id();
                            if first_id == "if" && !first.have_statement() && !first.have_extern_script() &&
                                    second_id.len() > 0 && !second.have_statement() && !second.have_extern_script() {
                                let mut item = IfClause::new();
                                if first.get_param_num() > 0 {
                                    if let Some(cond) = first.get_param(0) {
                                        item.condition = self.calculator().borrow_mut().load_syntax_component(cond);
                                    }
                                }
                                else {
                                    //error
                                    self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", first.to_script_string(false, &dsl::DEFAULT_DELIM), first.get_line()));
                                }
                                if let Some(sub_exp) = self.calculator().borrow_mut().load_function_syntax(second) {
                                    item.expressions.push(sub_exp);
                                }
                                self.m_clauses.push(item);
                                return true;
                            }
                        }
                    }
                }
            }
        }
        //the handling of the standard if syntax
        if let Some(fs) = statement.functions() {
            let mut ix = 0;
            for fd in fs {
                if let ValueOrFunction::Function(func_data) = fd {
                    if func_data.get_id() == "if" || func_data.get_id() == "elseif" || func_data.get_id() == "elif" {
                        let mut item = IfClause::new();
                        if let Some(lf) = func_data.lower_order_function() {
                            if let Some(cond) = lf.get_param(0) {
                                item.condition = self.calculator().borrow_mut().load_syntax_component(cond);
                            }
                        }
                        else {
                            //error
                            self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func_data.to_script_string(false, &dsl::DEFAULT_DELIM), func_data.get_line()));
                        }
                        if let Some(ps) = func_data.params() {
                            for p in ps.iter() {
                                if let Some(sub_exp) = self.calculator().borrow_mut().load_syntax_component(p) {
                                    item.expressions.push(sub_exp);
                                }
                            }
                        }
                        self.m_clauses.push(item);
                    }
                    else if func_data.get_id() == "else" {
                        if ix < fs.len() - 1 {
                            //error
                            self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func_data.to_script_string(false, &dsl::DEFAULT_DELIM), func_data.get_line()));
                        }
                        else {
                            let mut item = IfClause::new();
                            if let Some(ps) = func_data.params() {
                                for p in ps.iter() {
                                    if let Some(sub_exp) = self.calculator().borrow_mut().load_syntax_component(p) {
                                        item.expressions.push(sub_exp);
                                    }
                                }
                            }
                            self.m_clauses.push(item);
                        }
                    }
                    else {
                        //error
                        self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func_data.to_script_string(false, &dsl::DEFAULT_DELIM), func_data.get_line()));
                    }
                }
                ix += 1;
            }
        }
        return true;
    }

    impl_abstract_expression!();
}
impl<'a> IfExp<'a>
{
    fn need_return(&self) -> bool
    {
        if self.calculator().borrow().run_state() != &RunStateEnum::Normal {
            return true;
        }
        return false;
    }
}

#[add_abstract_and_simple_expression_fields]
struct EchoExp
{

}
impl<'a> Default for EchoExp<'a>
{
    fn default() -> Self
    {
        EchoExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for EchoExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for EchoExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for EchoExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        let r = DslCalculatorValue::Null;
        for oper in operands.iter()
        {
            match oper {
                DslCalculatorValue::Sbyte(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::Ubyte(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::Short(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::Ushort(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::Int(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::Uint(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::Long(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::Ulong(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::I128(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::U128(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::Float(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::Double(val) => {
                    print!("{}", val);
                },
                DslCalculatorValue::String(val) => {
                    print!("{}", val);
                }
                DslCalculatorValue::Bool(val) => {
                    print!("{}", val);
                }
                DslCalculatorValue::Char(val) => {
                    print!("{}", val);
                }
                _ => {
                    print!("");
                }
            }
        }
        return r;
    }

    impl_simple_expression!();
}