use std::cell::RefCell;
use std::rc::Rc;
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
    DslCalculator,
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
    fn load_statement(&mut self) -> bool
    {
        let mut op1 = None;
        let mut op2 = None;
        let mut op3 = None;
        if let SyntaxComponent::Statement(statement) = self.syntax_component() {
            if let Some(f1) = statement.first() {
                if let Some(f2) = statement.second() {
                    if let ValueOrFunction::Function(func_data1) = f1 {
                        if let ValueOrFunction::Function(func_data2) = f2 {
                            if func_data1.is_high_order() && func_data1.have_lower_order_param() && func_data2.get_id() == ":" && func_data2.have_param_or_statement() {
                                if let Some(lf) = func_data1.lower_order_function() {
                                    if let Some(p) = lf.get_param(0) {
                                        op1 = DslCalculator::load_syntax_component(self.calculator(), p);
                                    }
                                    if let Some(p) = func_data1.get_param(0) {
                                        op2 = DslCalculator::load_syntax_component(self.calculator(), p);
                                    }
                                    if let Some(p) = func_data2.get_param(0) {
                                        op3 = DslCalculator::load_syntax_component(self.calculator(), p);
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
        }
        self.m_op1 = op1;
        self.m_op2 = op2;
        self.m_op3 = op3;
        return true;
    }

    impl_abstract_expression!();
}
struct ExpAndClause<'a>
{
    pub condition: Option<ExpressionBox<'a>>,
    pub expressions: Vec<ExpressionBox<'a>>,
}
impl<'a> ExpAndClause<'a>
{
    pub fn new() -> Self
    {
        ExpAndClause {
            condition: None,
            expressions: Vec::new(),
        }
    }
}
#[add_abstract_expression_fields]
pub struct IfExp<'a>
{
    m_clauses: Option<Vec<RefCell<ExpAndClause<'a>>>>,
}
impl<'a> Default for IfExp<'a>
{
    fn default() -> Self
    {
        IfExp {
            m_clauses: None,

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
        if let Some(clauses) = &self.m_clauses {
            while ix < clauses.len() {
                let mut need_run = false;
                if let Some(cond) = &mut clauses[ix].borrow_mut().condition {
                    let cond_val = cond.calc();
                    if cond_val.to_i64() != 0 {
                        need_run = true;
                    }
                }
                else if ix == clauses.len() - 1 {
                    need_run = true;
                }
                if need_run {
                    let ct = clauses[ix].borrow_mut().expressions.len();
                    let mut exp_ix = 0;
                    while exp_ix < ct {
                        let exp = &mut clauses[ix].borrow_mut().expressions[exp_ix];
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
        }
        return v;
    }
    fn load_function(&mut self) -> bool
    {
        let mut clauses = None;
        if let SyntaxComponent::Function(func) = self.syntax_component() {
            if func.is_high_order() {
                let mut item = ExpAndClause::new();
                if let Some(lf) = func.lower_order_function() {
                    if let Some(cond) = lf.get_param(0) {
                        item.condition = DslCalculator::load_syntax_component(self.calculator(), cond);
                    }
                }
                if let Some(ps) = func.params() {
                    for p in ps.iter() {
                        if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                            item.expressions.push(sub_exp);
                        }
                    }
                }
                let mut items = Vec::new();
                items.push(RefCell::new(item));
                clauses = Some(items);
            }
            else {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
        }
        self.m_clauses = clauses;
        return true;
    }
    fn load_statement(&mut self) -> bool
    {
        //the handling of the simple syntax 'if(exp) func(args);'.
        let mut ret= false;
        let mut clauses = None;
        if let SyntaxComponent::Statement(statement) = self.syntax_component() {
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
                                    let mut item = ExpAndClause::new();
                                    if first.get_param_num() > 0 {
                                        if let Some(cond) = first.get_param(0) {
                                            item.condition = DslCalculator::load_syntax_component(self.calculator(), cond);
                                        }
                                    }
                                    else {
                                        //error
                                        self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", first.to_script_string(false, &dsl::DEFAULT_DELIM), first.get_line()));
                                    }
                                    if let Some(sub_exp) = DslCalculator::load_function_syntax(self.calculator(), second) {
                                        item.expressions.push(sub_exp);
                                    }
                                    let mut items = Vec::new();
                                    items.push(RefCell::new(item));
                                    clauses = Some(items);
                                    ret = true;
                                }
                            }
                        }
                    }
                }
            }
            if !ret {
                //the handling of the standard if syntax
                if let Some(fs) = statement.functions() {
                    let mut items = Vec::new();
                    let mut ix = 0;
                    for fd in fs {
                        if let ValueOrFunction::Function(func_data) = fd {
                            if func_data.get_id() == "if" || func_data.get_id() == "elseif" || func_data.get_id() == "elif" {
                                let mut item = ExpAndClause::new();
                                if let Some(lf) = func_data.lower_order_function() {
                                    if let Some(cond) = lf.get_param(0) {
                                        item.condition = DslCalculator::load_syntax_component(self.calculator(), cond);
                                    }
                                }
                                else {
                                    //error
                                    self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func_data.to_script_string(false, &dsl::DEFAULT_DELIM), func_data.get_line()));
                                }
                                if let Some(ps) = func_data.params() {
                                    for p in ps.iter() {
                                        if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                                            item.expressions.push(sub_exp);
                                        }
                                    }
                                }
                                items.push(RefCell::new(item));
                            }
                            else if func_data.get_id() == "else" {
                                if ix < fs.len() - 1 {
                                    //error
                                    self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func_data.to_script_string(false, &dsl::DEFAULT_DELIM), func_data.get_line()));
                                }
                                else {
                                    let mut item = ExpAndClause::new();
                                    if let Some(ps) = func_data.params() {
                                        for p in ps.iter() {
                                            if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                                                item.expressions.push(sub_exp);
                                            }
                                        }
                                    }
                                    items.push(RefCell::new(item));
                                }
                            }
                            else {
                                //error
                                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func_data.to_script_string(false, &dsl::DEFAULT_DELIM), func_data.get_line()));
                            }
                        }
                        ix += 1;
                    }
                    ret = items.len() > 1;
                    clauses = Some(items);
                }
            }
        }
        self.m_clauses = clauses;
        return ret;
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
#[add_abstract_expression_fields]
pub struct WhileExp<'a>
{
    m_clause: Option<RefCell<ExpAndClause<'a>>>,
}
impl<'a> Default for WhileExp<'a>
{
    fn default() -> Self
    {
        WhileExp {
            m_clause: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for WhileExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for WhileExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        let mut v = DslCalculatorValue::Null;
        if let Some(clause) = &self.m_clause {
            loop {
                if let Some(cond) = &mut clause.borrow_mut().condition {
                    let cond_val = cond.calc();
                    if cond_val.to_i64() != 0 {
                        let ct = clause.borrow_mut().expressions.len();
                        let mut exp_ix = 0;
                        while exp_ix < ct {
                            let exp = &mut clause.borrow_mut().expressions[exp_ix];
                            v = exp.calc();
                            if self.need_continue() {
                                break;
                            }
                            else if self.need_return() {
                                return v;
                            }
                            exp_ix += 1;
                        }
                    }
                    else{
                        break;
                    }
                }
                else{
                    break;
                }
            }
        }
        return v;
    }
    fn load_function(&mut self) -> bool
    {
        let mut clause = None;
        if let SyntaxComponent::Function(func) = self.syntax_component() {
            if func.is_high_order() {
                let mut item = ExpAndClause::new();
                if let Some(lf) = func.lower_order_function() {
                    if let Some(cond) = lf.get_param(0) {
                        item.condition = DslCalculator::load_syntax_component(self.calculator(), cond);
                    }
                }
                if let Some(ps) = func.params() {
                    for p in ps.iter() {
                        if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                            item.expressions.push(sub_exp);
                        }
                    }
                }
                clause = Some(RefCell::new(item));
            }
            else {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
        }
        self.m_clause = clause;
        return true;
    }
    fn load_statement(&mut self) -> bool
    {
        //the handling of the simple syntax 'while(exp) func(args);'
        let mut ret= false;
        let mut clause = None;
        if let SyntaxComponent::Statement(statement) = self.syntax_component() {
            let func_num = statement.get_function_num();
            if func_num == 2 {
                if let Some(fir) = statement.first() {
                    if let Some(sec) = statement.second() {
                        if let ValueOrFunction::Function(first) = fir {
                            if let ValueOrFunction::Function(second) = sec {
                                let first_id = first.get_id();
                                let second_id = second.get_id();
                                if first_id == "while" && !first.have_statement() && !first.have_extern_script() &&
                                        second_id.len() > 0 && !second.have_statement() && !second.have_extern_script() {
                                    let mut item = ExpAndClause::new();
                                    if first.get_param_num() > 0 {
                                        if let Some(cond) = first.get_param(0) {
                                            item.condition = DslCalculator::load_syntax_component(self.calculator(), cond);
                                        }
                                    }
                                    else {
                                        //error
                                        self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", first.to_script_string(false, &dsl::DEFAULT_DELIM), first.get_line()));
                                    }
                                    if let Some(sub_exp) = DslCalculator::load_function_syntax(self.calculator(), second) {
                                        item.expressions.push(sub_exp);
                                    }
                                    clause = Some(RefCell::new(item));
                                    ret = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        self.m_clause = clause;
        return ret;
    }

    impl_abstract_expression!();
}
impl<'a> WhileExp<'a>
{
    fn need_continue(&self) -> bool
    {
        if self.calculator().borrow().run_state() == &RunStateEnum::Continue {
            self.calculator().borrow_mut().set_run_state(RunStateEnum::Normal);
            return true;
        }
        return false;
    }
    fn need_return(&self) -> bool
    {
        if self.calculator().borrow().run_state() != &RunStateEnum::Normal {
            if self.calculator().borrow().run_state() == &RunStateEnum::Break {
                self.calculator().borrow_mut().set_run_state(RunStateEnum::Normal);
            }
            return true;
        }
        return false;
    }
}
#[add_abstract_expression_fields]
pub struct LoopExp<'a>
{
    m_clause: Option<RefCell<ExpAndClause<'a>>>,
}
impl<'a> Default for LoopExp<'a>
{
    fn default() -> Self
    {
        LoopExp {
            m_clause: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LoopExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LoopExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        let mut v = DslCalculatorValue::Null;
        if let Some(clause) = &self.m_clause {
            if let Some(cond) = &mut clause.borrow_mut().condition {
                let cond_val = cond.calc();
                let loop_ct = cond_val.to_i64();
                let mut loop_ix = 0;
                while loop_ix < loop_ct {
                    self.calculator().borrow_mut().set_variable(&"$$", DslCalculatorValue::Long(loop_ix));
                    let ct = clause.borrow_mut().expressions.len();
                    let mut exp_ix = 0;
                    while exp_ix < ct {
                        let exp = &mut clause.borrow_mut().expressions[exp_ix];
                        v = exp.calc();
                        if self.need_continue() {
                            break;
                        }
                        else if self.need_return() {
                            return v;
                        }
                        exp_ix += 1;
                    }
                    loop_ix += 1;
                }
            }
        }
        return v;
    }
    fn load_function(&mut self) -> bool
    {
        let mut clause = None;
        if let SyntaxComponent::Function(func) = self.syntax_component() {
            if func.is_high_order() {
                let mut item = ExpAndClause::new();
                if let Some(lf) = func.lower_order_function() {
                    if let Some(cond) = lf.get_param(0) {
                        item.condition = DslCalculator::load_syntax_component(self.calculator(), cond);
                    }
                }
                if let Some(ps) = func.params() {
                    for p in ps.iter() {
                        if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                            item.expressions.push(sub_exp);
                        }
                    }
                }
                clause = Some(RefCell::new(item));
            }
            else {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
        }
        self.m_clause = clause;
        return true;
    }
    fn load_statement(&mut self) -> bool
    {
        //the handling of the simple syntax 'loop(exp) func(args);'
        let mut ret= false;
        let mut clause = None;
        if let SyntaxComponent::Statement(statement) = self.syntax_component() {
            let func_num = statement.get_function_num();
            if func_num == 2 {
                if let Some(fir) = statement.first() {
                    if let Some(sec) = statement.second() {
                        if let ValueOrFunction::Function(first) = fir {
                            if let ValueOrFunction::Function(second) = sec {
                                let first_id = first.get_id();
                                let second_id = second.get_id();
                                if first_id == "loop" && !first.have_statement() && !first.have_extern_script() &&
                                        second_id.len() > 0 && !second.have_statement() && !second.have_extern_script() {
                                    let mut item = ExpAndClause::new();
                                    if first.get_param_num() > 0 {
                                        if let Some(cond) = first.get_param(0) {
                                            item.condition = DslCalculator::load_syntax_component(self.calculator(), cond);
                                        }
                                    }
                                    else {
                                        //error
                                        self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", first.to_script_string(false, &dsl::DEFAULT_DELIM), first.get_line()));
                                    }
                                    if let Some(sub_exp) = DslCalculator::load_function_syntax(self.calculator(), second) {
                                        item.expressions.push(sub_exp);
                                    }
                                    clause = Some(RefCell::new(item));
                                    ret = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        self.m_clause = clause;
        return ret;
    }

    impl_abstract_expression!();
}
impl<'a> LoopExp<'a>
{
    fn need_continue(&self) -> bool
    {
        if self.calculator().borrow().run_state() == &RunStateEnum::Continue {
            self.calculator().borrow_mut().set_run_state(RunStateEnum::Normal);
            return true;
        }
        return false;
    }
    fn need_return(&self) -> bool
    {
        if self.calculator().borrow().run_state() != &RunStateEnum::Normal {
            if self.calculator().borrow().run_state() == &RunStateEnum::Break {
                self.calculator().borrow_mut().set_run_state(RunStateEnum::Normal);
            }
            return true;
        }
        return false;
    }
}
#[add_abstract_expression_fields]
pub struct LoopListExp<'a>
{
    m_clause: Option<RefCell<ExpAndClause<'a>>>,
}
impl<'a> Default for LoopListExp<'a>
{
    fn default() -> Self
    {
        LoopListExp {
            m_clause: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LoopListExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LoopListExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        let mut v = DslCalculatorValue::Null;
        if let Some(clause) = &self.m_clause {
            if let Some(cond) = &mut clause.borrow_mut().condition {
                let cond_val = cond.calc();
                if let DslCalculatorValue::Array(vec) = cond_val {
                    for iter_v in vec.iter() {
                        self.calculator().borrow_mut().set_variable(&"$$", iter_v.clone());
                        let ct = clause.borrow_mut().expressions.len();
                        let mut exp_ix = 0;
                        while exp_ix < ct {
                            let exp = &mut clause.borrow_mut().expressions[exp_ix];
                            v = exp.calc();
                            if self.need_continue() {
                                break;
                            }
                            else if self.need_return() {
                                return v;
                            }
                            exp_ix += 1;
                        }
                    }
                }
            }
        }
        return v;
    }
    fn load_function(&mut self) -> bool
    {
        let mut clause = None;
        if let SyntaxComponent::Function(func) = self.syntax_component() {
            if func.is_high_order() {
                let mut item = ExpAndClause::new();
                if let Some(lf) = func.lower_order_function() {
                    if let Some(cond) = lf.get_param(0) {
                        item.condition = DslCalculator::load_syntax_component(self.calculator(), cond);
                    }
                }
                if let Some(ps) = func.params() {
                    for p in ps.iter() {
                        if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                            item.expressions.push(sub_exp);
                        }
                    }
                }
                clause = Some(RefCell::new(item));
            }
            else {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
        }
        self.m_clause = clause;
        return true;
    }
    fn load_statement(&mut self) -> bool
    {
        //the handling of the simple syntax 'loop(exp) func(args);'
        let mut ret= false;
        let mut clause = None;
        if let SyntaxComponent::Statement(statement) = self.syntax_component() {
            let func_num = statement.get_function_num();
            if func_num == 2 {
                if let Some(fir) = statement.first() {
                    if let Some(sec) = statement.second() {
                        if let ValueOrFunction::Function(first) = fir {
                            if let ValueOrFunction::Function(second) = sec {
                                let first_id = first.get_id();
                                let second_id = second.get_id();
                                if first_id == "loop" && !first.have_statement() && !first.have_extern_script() &&
                                        second_id.len() > 0 && !second.have_statement() && !second.have_extern_script() {
                                    let mut item = ExpAndClause::new();
                                    if first.get_param_num() > 0 {
                                        if let Some(cond) = first.get_param(0) {
                                            item.condition = DslCalculator::load_syntax_component(self.calculator(), cond);
                                        }
                                    }
                                    else {
                                        //error
                                        self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", first.to_script_string(false, &dsl::DEFAULT_DELIM), first.get_line()));
                                    }
                                    if let Some(sub_exp) = DslCalculator::load_function_syntax(self.calculator(), second) {
                                        item.expressions.push(sub_exp);
                                    }
                                    clause = Some(RefCell::new(item));
                                    ret = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        self.m_clause = clause;
        return ret;
    }

    impl_abstract_expression!();
}
impl<'a> LoopListExp<'a>
{
    fn need_continue(&self) -> bool
    {
        if self.calculator().borrow().run_state() == &RunStateEnum::Continue {
            self.calculator().borrow_mut().set_run_state(RunStateEnum::Normal);
            return true;
        }
        return false;
    }
    fn need_return(&self) -> bool
    {
        if self.calculator().borrow().run_state() != &RunStateEnum::Normal {
            if self.calculator().borrow().run_state() == &RunStateEnum::Break {
                self.calculator().borrow_mut().set_run_state(RunStateEnum::Normal);
            }
            return true;
        }
        return false;
    }
}
struct ListAndClause<'a>
{
    pub list: Vec<ExpressionBox<'a>>,
    pub expressions: Vec<ExpressionBox<'a>>,
}
impl<'a> ListAndClause<'a>
{
    pub fn new() -> Self
    {
        ListAndClause {
            list: Vec::new(),
            expressions: Vec::new(),
        }
    }
}
#[add_abstract_expression_fields]
pub struct ForeachExp<'a>
{
    m_clause: Option<RefCell<ListAndClause<'a>>>,
}
impl<'a> Default for ForeachExp<'a>
{
    fn default() -> Self
    {
        ForeachExp {
            m_clause: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ForeachExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ForeachExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        let mut v = DslCalculatorValue::Null;
        if let Some(clause) = &self.m_clause {
            for iter_exp in &mut clause.borrow_mut().list {
                let iter_v = iter_exp.calc();
                self.calculator().borrow_mut().set_variable(&"$$", iter_v);
                let ct = clause.borrow_mut().expressions.len();
                let mut exp_ix = 0;
                while exp_ix < ct {
                    let exp = &mut clause.borrow_mut().expressions[exp_ix];
                    v = exp.calc();
                    if self.need_continue() {
                        break;
                    }
                    else if self.need_return() {
                        return v;
                    }
                    exp_ix += 1;
                }
            }
        }
        return v;
    }
    fn load_function(&mut self) -> bool
    {
        let mut clause = None;
        if let SyntaxComponent::Function(func) = self.syntax_component() {
            if func.is_high_order() {
                let mut item = ListAndClause::new();
                if let Some(lf) = func.lower_order_function() {
                    if let Some(ps) = lf.params() {
                        for p in ps.iter() {
                            if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                                item.list.push(sub_exp);
                            }
                        }
                    }
                }
                if let Some(ps) = func.params() {
                    for p in ps.iter() {
                        if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                            item.expressions.push(sub_exp);
                        }
                    }
                }
                clause = Some(RefCell::new(item));
            }
            else {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
        }
        self.m_clause = clause;
        return true;
    }
    fn load_statement(&mut self) -> bool
    {
        //the handling of the simple syntax 'loop(exp) func(args);'
        let mut ret= false;
        let mut clause = None;
        if let SyntaxComponent::Statement(statement) = self.syntax_component() {
            let func_num = statement.get_function_num();
            if func_num == 2 {
                if let Some(fir) = statement.first() {
                    if let Some(sec) = statement.second() {
                        if let ValueOrFunction::Function(first) = fir {
                            if let ValueOrFunction::Function(second) = sec {
                                let first_id = first.get_id();
                                let second_id = second.get_id();
                                if first_id == "loop" && !first.have_statement() && !first.have_extern_script() &&
                                        second_id.len() > 0 && !second.have_statement() && !second.have_extern_script() {
                                    let mut item = ListAndClause::new();
                                    if first.get_param_num() > 0 {
                                        if let Some(ps) = first.params() {
                                            for p in ps.iter() {
                                                if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                                                    item.list.push(sub_exp);
                                                }
                                            }
                                        }
                                    }
                                    else {
                                        //error
                                        self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", first.to_script_string(false, &dsl::DEFAULT_DELIM), first.get_line()));
                                    }
                                    if let Some(sub_exp) = DslCalculator::load_function_syntax(self.calculator(), second) {
                                        item.expressions.push(sub_exp);
                                    }
                                    clause = Some(RefCell::new(item));
                                    ret = true;
                                }
                            }
                        }
                    }
                }
            }
        }
        self.m_clause = clause;
        return ret;
    }

    impl_abstract_expression!();
}
impl<'a> ForeachExp<'a>
{
    fn need_continue(&self) -> bool
    {
        if self.calculator().borrow().run_state() == &RunStateEnum::Continue {
            self.calculator().borrow_mut().set_run_state(RunStateEnum::Normal);
            return true;
        }
        return false;
    }
    fn need_return(&self) -> bool
    {
        if self.calculator().borrow().run_state() != &RunStateEnum::Normal {
            if self.calculator().borrow().run_state() == &RunStateEnum::Break {
                self.calculator().borrow_mut().set_run_state(RunStateEnum::Normal);
            }
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

#[add_abstract_and_simple_expression_fields]
struct CallExp
{

}
impl<'a> Default for CallExp<'a>
{
    fn default() -> Self
    {
        CallExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CallExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CallExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for CallExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        let mut r = DslCalculatorValue::Null;
        if operands.len() >= 1 {
            let mut args = self.calculator().borrow_mut().new_calculator_value_list();
            for oper in operands.iter().skip(1) {
                args.push(oper.clone());
            }
            if let DslCalculatorValue::String(func) = &operands[0] {
                r = DslCalculator::calc_n(self.calculator(), func, &mut args);
            }
            self.calculator().borrow_mut().recycle_calculator_value_list(args);
        }
        return r;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ReturnExp
{

}
impl<'a> Default for ReturnExp<'a>
{
    fn default() -> Self
    {
        ReturnExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ReturnExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ReturnExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ReturnExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        self.calculator().borrow_mut().set_run_state(RunStateEnum::Return);
        let mut r = DslCalculatorValue::Null;
        if operands.len() >= 1 {
            r = operands[0].clone();
        }
        return r;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct RedirectExp
{

}
impl<'a> Default for RedirectExp<'a>
{
    fn default() -> Self
    {
        RedirectExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for RedirectExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for RedirectExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for RedirectExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        self.calculator().borrow_mut().set_run_state(RunStateEnum::Redirect);
        if operands.len() >= 1 {
            let args = operands.clone();
            return DslCalculatorValue::Array(args);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}

#[add_abstract_and_simple_expression_fields]
struct IsNullExp
{

}
impl<'a> Default for IsNullExp<'a>
{
    fn default() -> Self
    {
        IsNullExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsNullExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsNullExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsNullExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let r = DslCalculatorValue::Bool(true) == operands[0];
            return DslCalculatorValue::Bool(r);
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct NullExp
{

}
impl<'a> Default for NullExp<'a>
{
    fn default() -> Self
    {
        NullExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for NullExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for NullExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for NullExp<'a>
{
    fn on_calc(&mut self, _operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsStringExp
{

}
impl<'a> Default for IsStringExp<'a>
{
    fn default() -> Self
    {
        IsStringExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsStringExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsStringExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsStringExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_string());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsArrayExp
{

}
impl<'a> Default for IsArrayExp<'a>
{
    fn default() -> Self
    {
        IsArrayExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsArrayExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsArrayExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsArrayExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_array());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsHashmapExp
{

}
impl<'a> Default for IsHashmapExp<'a>
{
    fn default() -> Self
    {
        IsHashmapExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsHashmapExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsHashmapExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsHashmapExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_hash_map());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsObjectExp
{

}
impl<'a> Default for IsObjectExp<'a>
{
    fn default() -> Self
    {
        IsObjectExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsObjectExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsObjectExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsObjectExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_object());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsBoolExp
{

}
impl<'a> Default for IsBoolExp<'a>
{
    fn default() -> Self
    {
        IsBoolExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsBoolExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsBoolExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsBoolExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_bool());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsCharExp
{

}
impl<'a> Default for IsCharExp<'a>
{
    fn default() -> Self
    {
        IsCharExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsCharExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsCharExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsCharExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_char());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsIntegerExp
{

}
impl<'a> Default for IsIntegerExp<'a>
{
    fn default() -> Self
    {
        IsIntegerExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsIntegerExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsIntegerExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsIntegerExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_integer());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsSignedExp
{

}
impl<'a> Default for IsSignedExp<'a>
{
    fn default() -> Self
    {
        IsSignedExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsSignedExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsSignedExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsSignedExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_signed_integer());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsUnsignedExp
{

}
impl<'a> Default for IsUnsignedExp<'a>
{
    fn default() -> Self
    {
        IsUnsignedExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsUnsignedExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsUnsignedExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsUnsignedExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_unsigned_integer());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsInteger128Exp
{

}
impl<'a> Default for IsInteger128Exp<'a>
{
    fn default() -> Self
    {
        IsInteger128Exp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsInteger128Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsInteger128Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsInteger128Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_integer_128());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsSigned128Exp
{

}
impl<'a> Default for IsSigned128Exp<'a>
{
    fn default() -> Self
    {
        IsSigned128Exp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsSigned128Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsSigned128Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsSigned128Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_signed_128());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsUnsigned128Exp
{

}
impl<'a> Default for IsUnsigned128Exp<'a>
{
    fn default() -> Self
    {
        IsUnsigned128Exp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsUnsigned128Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsUnsigned128Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsUnsigned128Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_unsigned_128());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsFloatExp
{

}
impl<'a> Default for IsFloatExp<'a>
{
    fn default() -> Self
    {
        IsFloatExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsFloatExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsFloatExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsFloatExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_float());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsSingleFloatExp
{

}
impl<'a> Default for IsSingleFloatExp<'a>
{
    fn default() -> Self
    {
        IsSingleFloatExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsSingleFloatExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsSingleFloatExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsSingleFloatExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_single_float());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsDoubleFloatExp
{

}
impl<'a> Default for IsDoubleFloatExp<'a>
{
    fn default() -> Self
    {
        IsDoubleFloatExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsDoubleFloatExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsDoubleFloatExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsDoubleFloatExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].is_double_float());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct BoolExp
{

}
impl<'a> Default for BoolExp<'a>
{
    fn default() -> Self
    {
        BoolExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for BoolExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for BoolExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for BoolExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Bool(operands[0].to_bool());
        }
        return DslCalculatorValue::Bool(false);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct CharExp
{

}
impl<'a> Default for CharExp<'a>
{
    fn default() -> Self
    {
        CharExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CharExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CharExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for CharExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Char(operands[0].to_char());
        }
        return DslCalculatorValue::Char('\0');
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct SbyteExp
{

}
impl<'a> Default for SbyteExp<'a>
{
    fn default() -> Self
    {
        SbyteExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for SbyteExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for SbyteExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for SbyteExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Sbyte(operands[0].to_i8());
        }
        return DslCalculatorValue::Sbyte(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct UbyteExp
{

}
impl<'a> Default for UbyteExp<'a>
{
    fn default() -> Self
    {
        UbyteExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for UbyteExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for UbyteExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for UbyteExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Ubyte(operands[0].to_u8());
        }
        return DslCalculatorValue::Ubyte(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ShortExp
{

}
impl<'a> Default for ShortExp<'a>
{
    fn default() -> Self
    {
        ShortExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ShortExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ShortExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ShortExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Short(operands[0].to_i16());
        }
        return DslCalculatorValue::Short(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct UshortExp
{

}
impl<'a> Default for UshortExp<'a>
{
    fn default() -> Self
    {
        UshortExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for UshortExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for UshortExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for UshortExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Ushort(operands[0].to_u16());
        }
        return DslCalculatorValue::Ushort(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IntExp
{

}
impl<'a> Default for IntExp<'a>
{
    fn default() -> Self
    {
        IntExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IntExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IntExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IntExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Int(operands[0].to_i32());
        }
        return DslCalculatorValue::Int(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct UintExp
{

}
impl<'a> Default for UintExp<'a>
{
    fn default() -> Self
    {
        UintExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for UintExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for UintExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for UintExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Uint(operands[0].to_u32());
        }
        return DslCalculatorValue::Uint(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LongExp
{

}
impl<'a> Default for LongExp<'a>
{
    fn default() -> Self
    {
        LongExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LongExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LongExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LongExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Long(operands[0].to_i64());
        }
        return DslCalculatorValue::Long(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct UlongExp
{

}
impl<'a> Default for UlongExp<'a>
{
    fn default() -> Self
    {
        UlongExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for UlongExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for UlongExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for UlongExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Ulong(operands[0].to_u64());
        }
        return DslCalculatorValue::Ulong(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct I128Exp
{

}
impl<'a> Default for I128Exp<'a>
{
    fn default() -> Self
    {
        I128Exp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for I128Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for I128Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for I128Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::I128(operands[0].to_i128());
        }
        return DslCalculatorValue::I128(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct U128Exp
{

}
impl<'a> Default for U128Exp<'a>
{
    fn default() -> Self
    {
        U128Exp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for U128Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for U128Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for U128Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::U128(operands[0].to_u128());
        }
        return DslCalculatorValue::U128(0);
    }

    impl_simple_expression!();
}#[add_abstract_and_simple_expression_fields]
struct FloatExp
{

}
impl<'a> Default for FloatExp<'a>
{
    fn default() -> Self
    {
        FloatExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for FloatExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for FloatExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for FloatExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Float(operands[0].to_f32());
        }
        return DslCalculatorValue::Float(0.0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DoubleExp
{

}
impl<'a> Default for DoubleExp<'a>
{
    fn default() -> Self
    {
        DoubleExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DoubleExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DoubleExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DoubleExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::Double(operands[0].to_f64());
        }
        return DslCalculatorValue::Double(0.0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ToStringExp
{

}
impl<'a> Default for ToStringExp<'a>
{
    fn default() -> Self
    {
        ToStringExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ToStringExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ToStringExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ToStringExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return DslCalculatorValue::String(operands[0].to_string());
        }
        return DslCalculatorValue::String(String::new());
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct GetTypeStrExp
{

}
impl<'a> Default for GetTypeStrExp<'a>
{
    fn default() -> Self
    {
        GetTypeStrExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for GetTypeStrExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for GetTypeStrExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for GetTypeStrExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            return match &operands[0] {
                DslCalculatorValue::Sbyte(_) => DslCalculatorValue::String(String::from("Sbyte")),
                DslCalculatorValue::Ubyte(_) => DslCalculatorValue::String(String::from("Ubyte")),
                DslCalculatorValue::Short(_) => DslCalculatorValue::String(String::from("Short")),
                DslCalculatorValue::Ushort(_) => DslCalculatorValue::String(String::from("Ushort")),
                DslCalculatorValue::Int(_) => DslCalculatorValue::String(String::from("Int")),
                DslCalculatorValue::Uint(_) => DslCalculatorValue::String(String::from("Uint")),
                DslCalculatorValue::Long(_) => DslCalculatorValue::String(String::from("Long")),
                DslCalculatorValue::Ulong(_) => DslCalculatorValue::String(String::from("Ulong")),
                DslCalculatorValue::I128(_) => DslCalculatorValue::String(String::from("I128")),
                DslCalculatorValue::U128(_) => DslCalculatorValue::String(String::from("U128")),
                DslCalculatorValue::Float(_) => DslCalculatorValue::String(String::from("Float")),
                DslCalculatorValue::Double(_) => DslCalculatorValue::String(String::from("Double")),
                DslCalculatorValue::String(_) => DslCalculatorValue::String(String::from("String")),
                DslCalculatorValue::Bool(_) => DslCalculatorValue::String(String::from("Bool")),
                DslCalculatorValue::Char(_) => DslCalculatorValue::String(String::from("Char")),
                DslCalculatorValue::Array(_) => DslCalculatorValue::String(String::from("Array")),
                DslCalculatorValue::HashMap(_) => DslCalculatorValue::String(String::from("HashMap")),
                DslCalculatorValue::Object(_) => DslCalculatorValue::String(String::from("Object")),
                _ => DslCalculatorValue::String(String::from("Null")),
            };
        }
        return DslCalculatorValue::String(String::from("Null"));
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct FtoiExp
{

}
impl<'a> Default for FtoiExp<'a>
{
    fn default() -> Self
    {
        FtoiExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for FtoiExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for FtoiExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for FtoiExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
			let fv = operands[0].to_f32();
			let iv = fv.to_bits() as i32;
            return DslCalculatorValue::Int(iv);
        }
        return DslCalculatorValue::Int(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ItofExp
{

}
impl<'a> Default for ItofExp<'a>
{
    fn default() -> Self
    {
        ItofExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ItofExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ItofExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ItofExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
			let iv = operands[0].to_i32();
			let fv = f32::from_bits(iv as u32);
            return DslCalculatorValue::Float(fv);
        }
        return DslCalculatorValue::Float(0.0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct FtouExp
{

}
impl<'a> Default for FtouExp<'a>
{
    fn default() -> Self
    {
        FtouExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for FtouExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for FtouExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for FtouExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
			let fv = operands[0].to_f32();
			let iv = fv.to_bits();
            return DslCalculatorValue::Uint(iv);
        }
        return DslCalculatorValue::Uint(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct UtofExp
{

}
impl<'a> Default for UtofExp<'a>
{
    fn default() -> Self
    {
        UtofExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for UtofExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for UtofExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for UtofExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
			let iv = operands[0].to_u32();
			let fv = f32::from_bits(iv);
            return DslCalculatorValue::Float(fv);
        }
        return DslCalculatorValue::Float(0.0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DtolExp
{

}
impl<'a> Default for DtolExp<'a>
{
    fn default() -> Self
    {
        DtolExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DtolExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DtolExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DtolExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
			let fv = operands[0].to_f64();
			let lv = fv.to_bits() as i64;
            return DslCalculatorValue::Long(lv);
        }
        return DslCalculatorValue::Long(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LtodExp
{

}
impl<'a> Default for LtodExp<'a>
{
    fn default() -> Self
    {
        LtodExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LtodExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LtodExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LtodExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
			let lv = operands[0].to_i64();
			let fv = f64::from_bits(lv as u64);
            return DslCalculatorValue::Double(fv);
        }
        return DslCalculatorValue::Double(0.0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DtouExp
{

}
impl<'a> Default for DtouExp<'a>
{
    fn default() -> Self
    {
        DtouExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DtouExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DtouExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DtouExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
			let fv = operands[0].to_f64();
			let lv = fv.to_bits();
            return DslCalculatorValue::Ulong(lv);
        }
        return DslCalculatorValue::Ulong(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct UtodExp
{

}
impl<'a> Default for UtodExp<'a>
{
    fn default() -> Self
    {
        UtodExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for UtodExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for UtodExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for UtodExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
			let lv = operands[0].to_u64();
			let fv = f64::from_bits(lv);
            return DslCalculatorValue::Double(fv);
        }
        return DslCalculatorValue::Double(0.0);
    }

    impl_simple_expression!();
}