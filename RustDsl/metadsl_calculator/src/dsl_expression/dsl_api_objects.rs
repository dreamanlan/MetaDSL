use std::rc::Rc;
use std::fmt::Write;
use metadsl::dsl::{
    FunctionData, StatementData, SyntaxComponent, ValueData, ValueOrFunction
};
use metadsl_macros::{
    //add_abstract_expression_fields,
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
};

#[add_abstract_and_simple_expression_fields]
struct FormatExp
{

}
impl<'a> Default for FormatExp<'a>
{
    fn default() -> Self
    {
        FormatExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for FormatExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for FormatExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for FormatExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::String(template) = opd0 {
                let mut result = String::new();
                let mut chars = template.chars().peekable();
                let mut arg_index = 1;

                while let Some(c) = chars.next() {
                    if c == '{' {
                        if let Some(&'{') = chars.peek() {
                            result.push('{');
                            chars.next();
                        } else {
                            let mut format_spec = String::new();
                            let mut in_format_spec = false;

                            while let Some(&ch) = chars.peek() {
                                if ch == '}' {
                                    chars.next();
                                    break;
                                }
                                if ch == ':' {
                                    in_format_spec = true;
                                    chars.next();
                                    continue;
                                }
                                if in_format_spec {
                                    format_spec.push(ch);
                                }
                                chars.next();
                            }

                            if arg_index < operands.len() {
                                let opd = &operands[arg_index];
                                arg_index += 1;

                                match format_spec.as_str() {
                                    "" => Self::format_default(&mut result, opd),
                                    "d" => write!(result, "{}", opd.to_i64()).unwrap(),
                                    "x" => write!(result, "{:x}", opd.to_i64()).unwrap(),
                                    "X" => write!(result, "{:X}", opd.to_i64()).unwrap(),
                                    "o" => write!(result, "{:o}", opd.to_i64()).unwrap(),
                                    "b" => write!(result, "{:b}", opd.to_i64()).unwrap(),
                                    "e" => write!(result, "{:e}", opd.to_f64()).unwrap(),
                                    "E" => write!(result, "{:E}", opd.to_f64()).unwrap(),
                                    "?" => Self::format_debug(&mut result, opd),
                                    _ => result.push_str(&format!("{{:{}}}", format_spec)),
                                }
                            } else {
                                result.push_str(&format!("{{:{}}}", format_spec));
                            }
                        }
                    } else if c == '}' {
                        if let Some(&'}') = chars.peek() {
                            result.push('}');
                            chars.next();
                        } else {
                            //error, missing '}'
                            result.push('}');
                        }
                    } else {
                        result.push(c);
                    }
                }
                return DslCalculatorValue::String(result);
            }
        }
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
impl<'a> FormatExp<'a>
{
    fn format_default(result: &mut String, opd: &DslCalculatorValue)
    {
        if opd.is_signed_integer() {
            write!(result, "{}", opd.to_i64()).unwrap();
        }
        else if opd.is_unsigned_integer() {
            write!(result, "{}", opd.to_u64()).unwrap();
        }
        else if opd.is_signed_128() {
            write!(result, "{}", opd.to_i128()).unwrap();
        }
        else if opd.is_unsigned_128() {
            write!(result, "{}", opd.to_u128()).unwrap();
        }
        else if opd.is_single_float() {
            write!(result, "{}", opd.to_f32()).unwrap();
        }
        else if opd.is_double_float() {
            write!(result, "{}", opd.to_f64()).unwrap();
        }
        else {
            write!(result, "{}", opd.to_string()).unwrap();
        }
    }
    fn format_debug(result: &mut String, opd: &DslCalculatorValue)
    {
        if opd.is_signed_integer() {
            write!(result, "{:?}", opd.to_i64()).unwrap();
        }
        else if opd.is_unsigned_integer() {
            write!(result, "{:?}", opd.to_u64()).unwrap();
        }
        else if opd.is_signed_128() {
            write!(result, "{:?}", opd.to_i128()).unwrap();
        }
        else if opd.is_unsigned_128() {
            write!(result, "{:?}", opd.to_u128()).unwrap();
        }
        else if opd.is_single_float() {
            write!(result, "{:?}", opd.to_f32()).unwrap();
        }
        else if opd.is_double_float() {
            write!(result, "{:?}", opd.to_f64()).unwrap();
        }
        else {
            write!(result, "{:?}", opd.to_string()).unwrap();
        }
    }
}
#[add_abstract_and_simple_expression_fields]
struct CollectionCallExp
{

}
impl<'a> Default for CollectionCallExp<'a>
{
    fn default() -> Self
    {
        CollectionCallExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CollectionCallExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CollectionCallExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for CollectionCallExp<'a>
{
    fn on_calc(&mut self, _operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct CollectionSetExp
{

}
impl<'a> Default for CollectionSetExp<'a>
{
    fn default() -> Self
    {
        CollectionSetExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CollectionSetExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CollectionSetExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for CollectionSetExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            match opd0 {
                DslCalculatorValue::Array(arr) => {
                    let ix = opd1.to_u64() as usize;
                    if ix < arr.borrow().len() {
                        arr.borrow_mut()[ix] = opd2.clone();
                        return DslCalculatorValue::Bool(true);
                    }
                    return DslCalculatorValue::Bool(false);
                }
                DslCalculatorValue::HashMap(hash) => {
                    if let Some(v) = hash.borrow_mut().get_mut(&opd1) {
                        *v = opd2.clone();
                        return DslCalculatorValue::Bool(true);
                    }
                    return DslCalculatorValue::Bool(false);
                }
                DslCalculatorValue::Deque(deque) => {
                    let ix = opd1.to_u64() as usize;
                    if ix < deque.borrow().len() {
                        deque.borrow_mut()[ix] = opd2.clone();
                        return DslCalculatorValue::Bool(true);
                    }
                    return DslCalculatorValue::Bool(false);
                }
                _ => { }
            }
        }
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct CollectionGetExp
{

}
impl<'a> Default for CollectionGetExp<'a>
{
    fn default() -> Self
    {
        CollectionGetExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for CollectionGetExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for CollectionGetExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for CollectionGetExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            match opd0 {
                DslCalculatorValue::Array(arr) => {
                    let ix = opd1.to_u64() as usize;
                    if ix < arr.borrow().len() {
                        return arr.borrow()[ix].clone();
                    }
                }
                DslCalculatorValue::HashMap(hash) => {
                    if let Some(v) = hash.borrow().get(&opd1) {
                        return v.clone();
                    }
                }
                DslCalculatorValue::Deque(deque) => {
                    let ix = opd1.to_u64() as usize;
                    if ix < deque.borrow().len() {
                        return deque.borrow()[ix].clone();
                    }
                }
                _ => { }
            }
        }
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ObjectCallExp
{

}
impl<'a> Default for ObjectCallExp<'a>
{
    fn default() -> Self
    {
        ObjectCallExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ObjectCallExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ObjectCallExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ObjectCallExp<'a>
{
    fn on_calc(&mut self, _operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ObjectSetExp
{

}
impl<'a> Default for ObjectSetExp<'a>
{
    fn default() -> Self
    {
        ObjectSetExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ObjectSetExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ObjectSetExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ObjectSetExp<'a>
{
    fn on_calc(&mut self, _operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ObjectGetExp
{

}
impl<'a> Default for ObjectGetExp<'a>
{
    fn default() -> Self
    {
        ObjectGetExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ObjectGetExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ObjectGetExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ObjectGetExp<'a>
{
    fn on_calc(&mut self, _operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct LinqExp
{

}
impl<'a> Default for LinqExp<'a>
{
    fn default() -> Self
    {
        LinqExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LinqExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LinqExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for LinqExp<'a>
{
    fn on_calc(&mut self, _operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}