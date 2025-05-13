use std::cell::RefCell;
use std::slice::Iter;
use std::iter::Skip;
use std::rc::Rc;
use rand::Rng;
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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
        if let Some(clauses) = &self.m_clauses {
            for ix in 0..clauses.len() {
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
                    for exp_ix in 0..ct {
                        let exp = &mut clauses[ix].borrow_mut().expressions[exp_ix];
                        v = exp.calc();
                        if self.need_return() {
                            return v;
                        }
                    }
                    break;
                }
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
                    if cond_val.to_i64() == 0 {
                        break;
                    }
                }
                let ct = clause.borrow_mut().expressions.len();
                for exp_ix in 0..ct {
                    let exp = &mut clause.borrow_mut().expressions[exp_ix];
                    v = exp.calc();
                    if self.need_continue() {
                        break;
                    }
                    else if self.need_return() {
                        return v;
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
            let mut loop_ct = 0;
            if let Some(cond) = &mut clause.borrow_mut().condition {
                let cond_val = cond.calc();
                loop_ct = cond_val.to_i64();
            }
            for loop_ix in 0..loop_ct {
                self.calculator().borrow_mut().set_variable(&"$$", DslCalculatorValue::Long(loop_ix));
                let ct = clause.borrow_mut().expressions.len();
                for exp_ix in 0..ct {
                    let exp = &mut clause.borrow_mut().expressions[exp_ix];
                    v = exp.calc();
                    if self.need_continue() {
                        break;
                    }
                    else if self.need_return() {
                        return v;
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
            let mut cond_val = DslCalculatorValue::Null;
            if let Some(cond) = &mut clause.borrow_mut().condition {
                cond_val = cond.calc();
            }
            if let DslCalculatorValue::Array(vec) = cond_val {
                for iter_v in vec.iter() {
                    self.calculator().borrow_mut().set_variable(&"$$", iter_v.clone());
                    let ct = clause.borrow_mut().expressions.len();
                    for exp_ix in 0..ct {
                        let exp = &mut clause.borrow_mut().expressions[exp_ix];
                        v = exp.calc();
                        if self.need_continue() {
                            break;
                        }
                        else if self.need_return() {
                            return v;
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
            let val_ct = clause.borrow().list.len();
            for val_ix in 0..val_ct {
                let mut iter_v = DslCalculatorValue::Null;
                if let Some(iter_exp) = clause.borrow_mut().list.get_mut(val_ix) {
                    iter_v = iter_exp.calc();
                }
                self.calculator().borrow_mut().set_variable(&"$$", iter_v);
                let ct = clause.borrow_mut().expressions.len();
                for exp_ix in 0..ct {
                    let exp = &mut clause.borrow_mut().expressions[exp_ix];
                    v = exp.calc();
                    if self.need_continue() {
                        break;
                    }
                    else if self.need_return() {
                        return v;
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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
        return DslCalculatorValue::Null;
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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
            m_exps: None,

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
#[add_abstract_and_simple_expression_fields]
struct RndIntExp
{

}
impl<'a> Default for RndIntExp<'a>
{
    fn default() -> Self
    {
        RndIntExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for RndIntExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for RndIntExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for RndIntExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
			let v1 = operands[0].to_i64();
			let v2 = operands[1].to_i64();
            let mut rnd = rand::thread_rng();
            let v = rnd.gen_range(v1..v2);
            return DslCalculatorValue::Long(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct RndFloatExp
{

}
impl<'a> Default for RndFloatExp<'a>
{
    fn default() -> Self
    {
        RndFloatExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for RndFloatExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for RndFloatExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for RndFloatExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
			let v1 = operands[0].to_f64();
			let v2 = operands[1].to_f64();
            let mut rnd = rand::thread_rng();
            let v = rnd.gen_range(v1..v2);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct PowExp
{

}
impl<'a> Default for PowExp<'a>
{
    fn default() -> Self
    {
        PowExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for PowExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for PowExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for PowExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if opd0.is_integer() && opd1.is_integer() {
                let v1 = opd0.to_i64();
                let v2 = opd1.to_u32();
                let v = v1.pow(v2);
                return DslCalculatorValue::Long(v);
            }
            else {
                let v1 = opd0.to_f64();
                let v2 = opd1.to_f64();
                let v = v1.powf(v2);
                return DslCalculatorValue::Double(v);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct SqrtExp
{

}
impl<'a> Default for SqrtExp<'a>
{
    fn default() -> Self
    {
        SqrtExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for SqrtExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for SqrtExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for SqrtExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if opd0.is_integer() {
                let v1 = opd0.to_i64();
                let v = v1.isqrt();
                return DslCalculatorValue::Long(v);
            }
            else {
                let v1 = opd0.to_f64();
                let v = v1.sqrt();
                return DslCalculatorValue::Double(v);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ExpExp
{

}
impl<'a> Default for ExpExp<'a>
{
    fn default() -> Self
    {
        ExpExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ExpExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ExpExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ExpExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.exp();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Exp2Exp
{

}
impl<'a> Default for Exp2Exp<'a>
{
    fn default() -> Self
    {
        Exp2Exp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Exp2Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Exp2Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Exp2Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.exp2();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ExpM1Exp
{

}
impl<'a> Default for ExpM1Exp<'a>
{
    fn default() -> Self
    {
        ExpM1Exp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ExpM1Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ExpM1Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ExpM1Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.exp_m1();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LnExp
{

}
impl<'a> Default for LnExp<'a>
{
    fn default() -> Self
    {
        LnExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LnExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LnExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LnExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.ln();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Ln1pExp
{

}
impl<'a> Default for Ln1pExp<'a>
{
    fn default() -> Self
    {
        Ln1pExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Ln1pExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Ln1pExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Ln1pExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.ln_1p();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LogExp
{

}
impl<'a> Default for LogExp<'a>
{
    fn default() -> Self
    {
        LogExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LogExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LogExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LogExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let v1 = opd0.to_f64();
            let v2 = opd1.to_f64();
            let v = v1.log(v2);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Log10Exp
{

}
impl<'a> Default for Log10Exp<'a>
{
    fn default() -> Self
    {
        Log10Exp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Log10Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Log10Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Log10Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.log10();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Log2Exp
{

}
impl<'a> Default for Log2Exp<'a>
{
    fn default() -> Self
    {
        Log2Exp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Log2Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Log2Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Log2Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.log2();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct MaxExp
{

}
impl<'a> Default for MaxExp<'a>
{
    fn default() -> Self
    {
        MaxExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for MaxExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for MaxExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for MaxExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let mut is_integer = true;
            for opd in operands {
                if !opd.is_integer() {
                    is_integer = false;
                    break;
                }
            }
            if is_integer {
                let mut v = std::i64::MIN;
                for opd in operands {
                    if !opd.is_integer() {
                        v = opd.to_i64().max(v);
                    }
                }
                return DslCalculatorValue::Long(v);
            }
            else {
                let mut v = std::f64::MIN;
                for opd in operands {
                    if !opd.is_integer() {
                        v = opd.to_f64().max(v);
                    }
                }
                return DslCalculatorValue::Double(v);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct MinExp
{

}
impl<'a> Default for MinExp<'a>
{
    fn default() -> Self
    {
        MinExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for MinExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for MinExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for MinExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let mut is_integer = true;
            for opd in operands {
                if !opd.is_integer() {
                    is_integer = false;
                    break;
                }
            }
            if is_integer {
                let mut v = std::i64::MAX;
                for opd in operands {
                    if !opd.is_integer() {
                        v = opd.to_i64().min(v);
                    }
                }
                return DslCalculatorValue::Long(v);
            }
            else {
                let mut v = std::f64::MAX;
                for opd in operands {
                    if !opd.is_integer() {
                        v = opd.to_f64().min(v);
                    }
                }
                return DslCalculatorValue::Double(v);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct AbsExp
{

}
impl<'a> Default for AbsExp<'a>
{
    fn default() -> Self
    {
        AbsExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AbsExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AbsExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AbsExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if opd0.is_integer() {
                let v1 = opd0.to_i64();
                let v = v1.abs();
                return DslCalculatorValue::Long(v);
            }
            else {
                let v1 = opd0.to_f64();
                let v = v1.abs();
                return DslCalculatorValue::Double(v);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct AbsDiffExp
{

}
impl<'a> Default for AbsDiffExp<'a>
{
    fn default() -> Self
    {
        AbsDiffExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AbsDiffExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AbsDiffExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AbsDiffExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if opd0.is_integer() && opd1.is_integer() {
                let v1 = opd0.to_i64();
                let v2 = opd1.to_i64();
                let v = v1.abs_diff(v2);
                return DslCalculatorValue::Ulong(v);
            }
            else {
                let v1 = opd0.to_i128();
                let v2 = opd1.to_i128();
                let v = v1.abs_diff(v2);
                return DslCalculatorValue::U128(v);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct SigNumExp
{

}
impl<'a> Default for SigNumExp<'a>
{
    fn default() -> Self
    {
        SigNumExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for SigNumExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for SigNumExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for SigNumExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if opd0.is_integer() {
                let v1 = opd0.to_i64();
                let v = v1.signum();
                return DslCalculatorValue::Long(v);
            }
            else {
                let v1 = opd0.to_f64();
                let v = v1.signum();
                return DslCalculatorValue::Double(v);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct FloorExp
{

}
impl<'a> Default for FloorExp<'a>
{
    fn default() -> Self
    {
        FloorExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for FloorExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for FloorExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for FloorExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.floor();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct CeilingExp
{

}
impl<'a> Default for CeilingExp<'a>
{
    fn default() -> Self
    {
        CeilingExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CeilingExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CeilingExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for CeilingExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.ceil();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct RoundExp
{

}
impl<'a> Default for RoundExp<'a>
{
    fn default() -> Self
    {
        RoundExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for RoundExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for RoundExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for RoundExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.round();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct RoundEvenExp
{

}
impl<'a> Default for RoundEvenExp<'a>
{
    fn default() -> Self
    {
        RoundEvenExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for RoundEvenExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for RoundEvenExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for RoundEvenExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.round_ties_even();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct FloorToIntExp
{

}
impl<'a> Default for FloorToIntExp<'a>
{
    fn default() -> Self
    {
        FloorToIntExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for FloorToIntExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for FloorToIntExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for FloorToIntExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.floor() as i64;
            return DslCalculatorValue::Long(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct CeilingToIntExp
{

}
impl<'a> Default for CeilingToIntExp<'a>
{
    fn default() -> Self
    {
        CeilingToIntExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CeilingToIntExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CeilingToIntExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for CeilingToIntExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.ceil() as i64;
            return DslCalculatorValue::Long(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct RoundToIntExp
{

}
impl<'a> Default for RoundToIntExp<'a>
{
    fn default() -> Self
    {
        RoundToIntExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for RoundToIntExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for RoundToIntExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for RoundToIntExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.round() as i64;
            return DslCalculatorValue::Long(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct RoundEvenToIntExp
{

}
impl<'a> Default for RoundEvenToIntExp<'a>
{
    fn default() -> Self
    {
        RoundEvenToIntExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for RoundEvenToIntExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for RoundEvenToIntExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for RoundEvenToIntExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.round_ties_even() as i64;
            return DslCalculatorValue::Long(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct SinExp
{

}
impl<'a> Default for SinExp<'a>
{
    fn default() -> Self
    {
        SinExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for SinExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for SinExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for SinExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.sin();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct CosExp
{

}
impl<'a> Default for CosExp<'a>
{
    fn default() -> Self
    {
        CosExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CosExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CosExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for CosExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.cos();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct TanExp
{

}
impl<'a> Default for TanExp<'a>
{
    fn default() -> Self
    {
        TanExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for TanExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for TanExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for TanExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.tan();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct AsinExp
{

}
impl<'a> Default for AsinExp<'a>
{
    fn default() -> Self
    {
        AsinExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AsinExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AsinExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AsinExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.asin();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct AcosExp
{

}
impl<'a> Default for AcosExp<'a>
{
    fn default() -> Self
    {
        AcosExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AcosExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AcosExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AcosExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.acos();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct AtanExp
{

}
impl<'a> Default for AtanExp<'a>
{
    fn default() -> Self
    {
        AtanExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AtanExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AtanExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AtanExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.atan();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Atan2Exp
{

}
impl<'a> Default for Atan2Exp<'a>
{
    fn default() -> Self
    {
        Atan2Exp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Atan2Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Atan2Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Atan2Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let v1 = opd0.to_f64();
            let v2 = opd1.to_f64();
            let v = v1.atan2(v2);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct SinhExp
{

}
impl<'a> Default for SinhExp<'a>
{
    fn default() -> Self
    {
        SinhExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for SinhExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for SinhExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for SinhExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.sinh();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct CoshExp
{

}
impl<'a> Default for CoshExp<'a>
{
    fn default() -> Self
    {
        CoshExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CoshExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CoshExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for CoshExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.cosh();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct TanhExp
{

}
impl<'a> Default for TanhExp<'a>
{
    fn default() -> Self
    {
        TanhExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for TanhExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for TanhExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for TanhExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.tanh();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct AsinhExp
{

}
impl<'a> Default for AsinhExp<'a>
{
    fn default() -> Self
    {
        AsinhExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AsinhExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AsinhExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AsinhExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.asinh();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct AcoshExp
{

}
impl<'a> Default for AcoshExp<'a>
{
    fn default() -> Self
    {
        AcoshExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AcoshExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AcoshExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AcoshExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.acosh();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct AtanhExp
{

}
impl<'a> Default for AtanhExp<'a>
{
    fn default() -> Self
    {
        AtanhExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for AtanhExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for AtanhExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for AtanhExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.atanh();
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ClampExp
{

}
impl<'a> Default for ClampExp<'a>
{
    fn default() -> Self
    {
        ClampExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ClampExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ClampExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ClampExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            let v1 = opd0.to_f64();
            let v2 = opd1.to_f64();
            let v3 = opd2.to_f64();
            let v = v1.clamp(v2, v3);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Clamp01Exp
{

}
impl<'a> Default for Clamp01Exp<'a>
{
    fn default() -> Self
    {
        Clamp01Exp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Clamp01Exp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Clamp01Exp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Clamp01Exp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_f64();
            let v = v1.clamp(0.0, 1.0);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LerpExp
{

}
impl<'a> Default for LerpExp<'a>
{
    fn default() -> Self
    {
        LerpExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LerpExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LerpExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LerpExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            let a = opd0.to_f64();
            let b = opd1.to_f64();
            let t = opd2.to_f64();
            let v = a + (b - a) * t.clamp(0.0, 1.0);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LerpUnclampedExp
{

}
impl<'a> Default for LerpUnclampedExp<'a>
{
    fn default() -> Self
    {
        LerpUnclampedExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LerpUnclampedExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LerpUnclampedExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LerpUnclampedExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            let a = opd0.to_f64();
            let b = opd1.to_f64();
            let t = opd2.to_f64();
            let v = a + (b - a) * t;
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LerpAngleExp
{

}
impl<'a> Default for LerpAngleExp<'a>
{
    fn default() -> Self
    {
        LerpAngleExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LerpAngleExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LerpAngleExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LerpAngleExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            let a = opd0.to_f64();
            let b = opd1.to_f64();
            let t = opd2.to_f64();
            let mut num = Self::repeat(b - a, 360.0);
            if num > 180.0 {
                num -= 360.0;
            }
            let v = a + num * t.clamp(0.0, 1.0);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
impl<'a> LerpAngleExp<'a>
{
    pub fn repeat(t: f64, length: f64) -> f64
    {
        return (t - (t / length).floor() * length).clamp(0.0, length);
    }
}
#[add_abstract_and_simple_expression_fields]
struct SmoothStepExp
{

}
impl<'a> Default for SmoothStepExp<'a>
{
    fn default() -> Self
    {
        SmoothStepExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for SmoothStepExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for SmoothStepExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for SmoothStepExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            let from = opd0.to_f64();
            let to = opd1.to_f64();
            let mut t = opd2.to_f64();
            t = t.clamp(0.0, 1.0);
            t = -2.0 * t * t * t + 3.0 * t * t;
            let v = to * t + from * (1.0 - t);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ApproximatelyExp
{

}
impl<'a> Default for ApproximatelyExp<'a>
{
    fn default() -> Self
    {
        ApproximatelyExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ApproximatelyExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ApproximatelyExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ApproximatelyExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let a = opd0.to_f64();
            let b = opd1.to_f64();
            let v = Self::approximately(a, b);
            return DslCalculatorValue::Bool(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
impl<'a> ApproximatelyExp<'a>
{
    pub fn approximately(a: f64, b: f64) -> bool
    {
        return (b - a).abs() < (1E-06 * a.abs().max(b.abs())).max(std::f64::EPSILON * 8.0);
    }
}
#[add_abstract_and_simple_expression_fields]
struct IsPowerOfTwoExp
{

}
impl<'a> Default for IsPowerOfTwoExp<'a>
{
    fn default() -> Self
    {
        IsPowerOfTwoExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsPowerOfTwoExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsPowerOfTwoExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsPowerOfTwoExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_i64();
            let v = Self::is_power_of_two(v1);
            return DslCalculatorValue::Bool(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
impl<'a> IsPowerOfTwoExp<'a>
{
    pub fn is_power_of_two(iv: i64) -> bool
    {
        let v = iv as f64;
        let n = v.log2().round() as u32;
        return 2_i64.pow(n) == iv;
    }
}
#[add_abstract_and_simple_expression_fields]
struct ClosestPowerOfTwoExp
{

}
impl<'a> Default for ClosestPowerOfTwoExp<'a>
{
    fn default() -> Self
    {
        ClosestPowerOfTwoExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ClosestPowerOfTwoExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ClosestPowerOfTwoExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ClosestPowerOfTwoExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_i64();
            let v = Self::closest_power_of_two(v1);
            return DslCalculatorValue::Long(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
impl<'a> ClosestPowerOfTwoExp<'a>
{
    pub fn closest_power_of_two(iv: i64) -> i64
    {
        let v = iv as f64;
        let n = v.log2().round() as u32;
        return 2_i64.pow(n);
    }
}
#[add_abstract_and_simple_expression_fields]
struct NextPowerOfTwoExp
{

}
impl<'a> Default for NextPowerOfTwoExp<'a>
{
    fn default() -> Self
    {
        NextPowerOfTwoExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for NextPowerOfTwoExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for NextPowerOfTwoExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for NextPowerOfTwoExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let v1 = opd0.to_i64();
            let v = Self::next_power_of_two(v1);
            return DslCalculatorValue::Long(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
impl<'a> NextPowerOfTwoExp<'a>
{
    pub fn next_power_of_two(iv: i64) -> i64
    {
        let v = iv as f64;
        let n = v.log2().ceil() as u32;
        return 2_i64.pow(n);
    }
}
#[add_abstract_and_simple_expression_fields]
struct DistExp
{

}
impl<'a> Default for DistExp<'a>
{
    fn default() -> Self
    {
        DistExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DistExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DistExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DistExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            let v1 = opd0.to_f64();
            let v2 = opd1.to_f64();
            let v3 = opd2.to_f64();
            let v = v1.clamp(v2, v3);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DistSqrExp
{

}
impl<'a> Default for DistSqrExp<'a>
{
    fn default() -> Self
    {
        DistSqrExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DistSqrExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DistSqrExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DistSqrExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 4 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            let opd3 = &operands[3];
            let x1 = opd0.to_f64();
            let y1 = opd1.to_f64();
            let x2 = opd2.to_f64();
            let y2 = opd3.to_f64();
            let v = (x1-x2).powi(2) + (y1-y2).powi(2);
            return DslCalculatorValue::Double(v);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct IsEmptyExp
{

}
impl<'a> Default for IsEmptyExp<'a>
{
    fn default() -> Self
    {
        IsEmptyExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for IsEmptyExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for IsEmptyExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for IsEmptyExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                let v = v1.len() == 0;
                return DslCalculatorValue::Bool(v);
            }
        }
        return DslCalculatorValue::Bool(true);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Str2IntExp
{

}
impl<'a> Default for Str2IntExp<'a>
{
    fn default() -> Self
    {
        Str2IntExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Str2IntExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Str2IntExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Str2IntExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                if let Result::Ok(v) = v1.parse::<i32>() {
                    return DslCalculatorValue::Int(v);
                }
            }
        }
        return DslCalculatorValue::Int(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Str2UintExp
{

}
impl<'a> Default for Str2UintExp<'a>
{
    fn default() -> Self
    {
        Str2UintExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Str2UintExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Str2UintExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Str2UintExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                if let Result::Ok(v) = v1.parse::<u32>() {
                    return DslCalculatorValue::Uint(v);
                }
            }
        }
        return DslCalculatorValue::Uint(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Str2LongExp
{

}
impl<'a> Default for Str2LongExp<'a>
{
    fn default() -> Self
    {
        Str2LongExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Str2LongExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Str2LongExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Str2LongExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                if let Result::Ok(v) = v1.parse::<i64>() {
                    return DslCalculatorValue::Long(v);
                }
            }
        }
        return DslCalculatorValue::Long(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Str2UlongExp
{

}
impl<'a> Default for Str2UlongExp<'a>
{
    fn default() -> Self
    {
        Str2UlongExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Str2UlongExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Str2UlongExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Str2UlongExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                if let Result::Ok(v) = v1.parse::<u64>() {
                    return DslCalculatorValue::Ulong(v);
                }
            }
        }
        return DslCalculatorValue::Ulong(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Str2FloatExp
{

}
impl<'a> Default for Str2FloatExp<'a>
{
    fn default() -> Self
    {
        Str2FloatExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Str2FloatExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Str2FloatExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Str2FloatExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                if let Result::Ok(v) = v1.parse::<f32>() {
                    return DslCalculatorValue::Float(v);
                }
            }
        }
        return DslCalculatorValue::Float(0.0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Str2DoubleExp
{

}
impl<'a> Default for Str2DoubleExp<'a>
{
    fn default() -> Self
    {
        Str2DoubleExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Str2DoubleExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Str2DoubleExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Str2DoubleExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                if let Result::Ok(v) = v1.parse::<f64>() {
                    return DslCalculatorValue::Double(v);
                }
            }
        }
        return DslCalculatorValue::Double(0.0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Hex2IntExp
{

}
impl<'a> Default for Hex2IntExp<'a>
{
    fn default() -> Self
    {
        Hex2IntExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Hex2IntExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Hex2IntExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Hex2IntExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                let hex_str = v1.trim_start_matches("0x");
                if let Result::Ok(v) = i32::from_str_radix(hex_str, 16) {
                    return DslCalculatorValue::Int(v);
                }
            }
        }
        return DslCalculatorValue::Int(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Hex2UintExp
{

}
impl<'a> Default for Hex2UintExp<'a>
{
    fn default() -> Self
    {
        Hex2UintExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Hex2UintExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Hex2UintExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Hex2UintExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                let hex_str = v1.trim_start_matches("0x");
                if let Result::Ok(v) = u32::from_str_radix(hex_str, 16) {
                    return DslCalculatorValue::Uint(v);
                }
            }
        }
        return DslCalculatorValue::Uint(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Hex2LongExp
{

}
impl<'a> Default for Hex2LongExp<'a>
{
    fn default() -> Self
    {
        Hex2LongExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Hex2LongExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Hex2LongExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Hex2LongExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                let hex_str = v1.trim_start_matches("0x");
                if let Result::Ok(v) = i64::from_str_radix(hex_str, 16) {
                    return DslCalculatorValue::Long(v);
                }
            }
        }
        return DslCalculatorValue::Long(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct Hex2UlongExp
{

}
impl<'a> Default for Hex2UlongExp<'a>
{
    fn default() -> Self
    {
        Hex2UlongExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for Hex2UlongExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for Hex2UlongExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for Hex2UlongExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(v1) = opd0 {
                let hex_str = v1.trim_start_matches("0x");
                if let Result::Ok(v) = u64::from_str_radix(hex_str, 16) {
                    return DslCalculatorValue::Ulong(v);
                }
            }
        }
        return DslCalculatorValue::Ulong(0);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ToHexExp
{

}
impl<'a> Default for ToHexExp<'a>
{
    fn default() -> Self
    {
        ToHexExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ToHexExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ToHexExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ToHexExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            let mut upper_case = false;
            if operands.len() >= 2 {
                upper_case = operands[1].to_bool();
            }
            let s = match opd0 {
                DslCalculatorValue::Sbyte(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                DslCalculatorValue::Ubyte(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                DslCalculatorValue::Short(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                DslCalculatorValue::Ushort(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                DslCalculatorValue::Int(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                DslCalculatorValue::Uint(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                DslCalculatorValue::Long(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                DslCalculatorValue::Ulong(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                DslCalculatorValue::I128(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                DslCalculatorValue::U128(v1) => {
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
                _ => {
                    let v1 = opd0.to_i64();
                    if upper_case {
                        format!("{:X}", v1)
                    }
                    else {
                        format!("{:x}", v1)
                    }
                }
            };
            return DslCalculatorValue::String(s);
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}

fn append_vals_to_string(sb: &mut String, vals: &Vec<DslCalculatorValue>)
{
    for oper in vals.iter()
    {
        match oper {
            DslCalculatorValue::Sbyte(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::Ubyte(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::Short(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::Ushort(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::Int(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::Uint(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::Long(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::Ulong(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::I128(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::U128(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::Float(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::Double(val) => {
                sb.extend(format!("{}", val).chars());
            },
            DslCalculatorValue::String(val) => {
                sb.extend(format!("{}", val).chars());
            }
            DslCalculatorValue::Bool(val) => {
                sb.extend(format!("{}", val).chars());
            }
            DslCalculatorValue::Char(val) => {
                sb.extend(format!("{}", val).chars());
            }
            _ => {
            }
        };
    }
}
#[add_abstract_and_simple_expression_fields]
struct StrConcatExp
{

}
impl<'a> Default for StrConcatExp<'a>
{
    fn default() -> Self
    {
        StrConcatExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for StrConcatExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for StrConcatExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for StrConcatExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        let mut sb = String::new();
        append_vals_to_string(&mut sb, operands);
        return DslCalculatorValue::String(sb);
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct SubStringExp
{

}
impl<'a> Default for SubStringExp<'a>
{
    fn default() -> Self
    {
        SubStringExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for SubStringExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for SubStringExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for SubStringExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::String(s) = opd0 {
                let start = opd1.to_u32() as usize;
                let mut end = s.len();
                if operands.len() >= 3 {
                    end = start + operands[2].to_u32() as usize;
                }
                return DslCalculatorValue::String(s[start..end].to_string());
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_expression_fields]
pub struct StringAppendExp<'a>
{
    m_var_id: Option<String>,
    m_var_ix: i32,
    m_is_global: bool,
    m_exps: Option<Vec<ExpressionBox<'a>>>,
}
impl<'a> Default for StringAppendExp<'a>
{
    fn default() -> Self
    {
        StringAppendExp {
            m_var_id: None,
            m_var_ix: std::i32::MAX,
            m_is_global: false,
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for StringAppendExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for StringAppendExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        if self.m_var_ix == std::i32::MAX {
            let mut var_ix = std::i32::MAX;
            let mut is_global = false;
            if let Some(var_id) = &self.m_var_id {
                var_ix = self.calculator().borrow().get_local_variable_index(var_id);
                if var_ix == std::i32::MAX {
                    var_ix = self.calculator().borrow().get_global_variable_index(var_id);
                    if var_ix < std::i32::MAX {
                        is_global = true;
                    }
                }
                if var_ix == std::i32::MAX {
                    self.calculator().borrow().error(&format!("unassigned local/global var '{0}'", var_id));
                    return DslCalculatorValue::Null;
                }
            }
            self.m_var_ix = var_ix;
            self.m_is_global = is_global;
        }
        let mut vals = Vec::new();
        if let Some(exps) = &mut self.m_exps {
            for iter_exp in exps {
                let iter_v = iter_exp.calc();
                vals.push(iter_v);
            }
        }
        if self.m_is_global {
            if let Some(r) = self.calculator().borrow_mut().get_global_varaible_by_index_mut(self.m_var_ix) {
                if let DslCalculatorValue::String(s) = r {
                    append_vals_to_string(s, &vals);
                }
            }
        }
        else {
            if let Some(r) = self.calculator().borrow_mut().get_local_varaible_by_index_mut(self.m_var_ix) {
                if let DslCalculatorValue::String(s) = r {
                    append_vals_to_string(s, &vals);
                }
            }
        }
        return DslCalculatorValue::Null;
    }
    fn load_function(&mut self) -> bool
    {
        if let SyntaxComponent::Function(func) = self.syntax_component() {
            if func.is_high_order() {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
            else {
                let mut var_id = None;
                let mut exps = Vec::new();
                if let Some(ps) = func.params() {
                    if ps.len() > 0 {
                        var_id = Some(ps[0].get_id().clone());
                    }
                    for p in ps.iter().skip(1) {
                        if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                            exps.push(sub_exp);
                        }
                    }
                }
                self.m_var_id = var_id;
                self.m_exps = Some(exps);
            }
        }
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_expression_fields]
pub struct StringAppendLineExp<'a>
{
    m_var_id: Option<String>,
    m_var_ix: i32,
    m_is_global: bool,
    m_exps: Option<Vec<ExpressionBox<'a>>>,
}
impl<'a> Default for StringAppendLineExp<'a>
{
    fn default() -> Self
    {
        StringAppendLineExp {
            m_var_id: None,
            m_var_ix: std::i32::MAX,
            m_is_global: false,
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for StringAppendLineExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for StringAppendLineExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        if self.m_var_ix == std::i32::MAX {
            let mut var_ix = std::i32::MAX;
            let mut is_global = false;
            if let Some(var_id) = &self.m_var_id {
                var_ix = self.calculator().borrow().get_local_variable_index(var_id);
                if var_ix == std::i32::MAX {
                    var_ix = self.calculator().borrow().get_global_variable_index(var_id);
                    if var_ix < std::i32::MAX {
                        is_global = true;
                    }
                }
                if var_ix == std::i32::MAX {
                    self.calculator().borrow().error(&format!("unassigned local/global var '{0}'", var_id));
                    return DslCalculatorValue::Null;
                }
            }
            self.m_var_ix = var_ix;
            self.m_is_global = is_global;
        }
        let mut vals = Vec::new();
        if let Some(exps) = &mut self.m_exps {
            for iter_exp in exps {
                let iter_v = iter_exp.calc();
                vals.push(iter_v);
            }
        }
        if self.m_is_global {
            if let Some(r) = self.calculator().borrow_mut().get_global_varaible_by_index_mut(self.m_var_ix) {
                if let DslCalculatorValue::String(s) = r {
                    append_vals_to_string(s, &vals);
                    s.push('\n');
                }
            }
        }
        else {
            if let Some(r) = self.calculator().borrow_mut().get_local_varaible_by_index_mut(self.m_var_ix) {
                if let DslCalculatorValue::String(s) = r {
                    append_vals_to_string(s, &vals);
                    s.push('\n');
                }
            }
        }
        return DslCalculatorValue::Null;
    }
    fn load_function(&mut self) -> bool
    {
        if let SyntaxComponent::Function(func) = self.syntax_component() {
            if func.is_high_order() {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
            else {
                let mut var_id = None;
                let mut exps = Vec::new();
                if let Some(ps) = func.params() {
                    if ps.len() > 0 {
                        var_id = Some(ps[0].get_id().clone());
                    }
                    for p in ps.iter().skip(1) {
                        if let Some(sub_exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                            exps.push(sub_exp);
                        }
                    }
                }
                self.m_var_id = var_id;
                self.m_exps = Some(exps);
            }
        }
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct StringJoinExp
{

}
impl<'a> Default for StringJoinExp<'a>
{
    fn default() -> Self
    {
        StringJoinExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for StringJoinExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for StringJoinExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for StringJoinExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(sep) = opd0 {
                let s = operands.iter().skip(1).flat_map(Self::variant_to_strings).collect::<Vec<String>>().join(sep);
                return DslCalculatorValue::String(s);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
impl<'a> StringJoinExp<'a>
{
    fn variant_to_strings(variant: &DslCalculatorValue) -> Vec<String> {
        match variant {
            DslCalculatorValue::String(s) => vec![s.clone()],
            DslCalculatorValue::Array(arr) => arr.iter().flat_map(Self::variant_to_strings).collect(),
            _ => vec![variant.to_string()],
        }
    }
}
#[add_abstract_and_simple_expression_fields]
struct StringSplitExp
{

}
impl<'a> Default for StringSplitExp<'a>
{
    fn default() -> Self
    {
        StringSplitExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for StringSplitExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for StringSplitExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for StringSplitExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(s) = opd0 {
                let arr = s.split(|c|Self::is_sep(c, operands.iter().skip(1))).map(|elem|DslCalculatorValue::String(String::from(elem))).collect();
                return DslCalculatorValue::Array(arr);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
impl<'a> StringSplitExp<'a>
{
    fn is_sep(c: char, iter: Skip<Iter<'_, DslCalculatorValue>>) -> bool {
        for opd in iter {
            match opd {
                DslCalculatorValue::String(s) => {
                    if let Some(sc) = s.chars().next() {
                        if sc == c {
                            return true;
                        }
                    }
                }
                DslCalculatorValue::Char(sc) => {
                    if *sc == c {
                        return true;
                    }
                }
                _ => {
                    if opd.to_char() == c {
                        return true;
                    }
                }
            }
        }
        return false;
    }
}

