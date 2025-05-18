use std::{cmp::Ordering, u32};
use std::cell::RefCell;
use std::rc::Rc;
use std::fmt::Write;
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
#[add_abstract_expression_fields]
pub struct ObjectNewExp<'a>
{
    m_class_name: Option<String>,
}
impl<'a> Default for ObjectNewExp<'a>
{
    fn default() -> Self
    {
        ObjectNewExp {
            m_class_name: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ObjectNewExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ObjectNewExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        if let Some(name) = &self.m_class_name {
            if let Some(v) = self.calculator().borrow_mut().new_object(name) {
                return DslCalculatorValue::Object(v.borrow().get_object_id());
            }
        }
        return DslCalculatorValue::Null;
    }
    fn load_function(&mut self) -> bool
    {
        let mut class_name = None;
        if let SyntaxComponent::Function(func) = self.syntax_component() {
            if func.is_high_order() {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
            else if func.get_param_num() == 1 {
                class_name = Some(func.get_param_id(0).clone());
            }
            else {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
        }
        self.m_class_name = class_name;
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ObjectReleaseExp
{

}
impl<'a> Default for ObjectReleaseExp<'a>
{
    fn default() -> Self
    {
        ObjectReleaseExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ObjectReleaseExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ObjectReleaseExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ObjectReleaseExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() == 1 {
            let opd = &operands[0];
            if let DslCalculatorValue::Object(obj_id) = opd {
                let mut obj_opt = None;
                if let Some(obj) = self.calculator().borrow().get_object(*obj_id) {
                    obj_opt = Some(obj.clone());
                }
                if let Some(obj) = &obj_opt {
                    self.calculator().borrow_mut().unhold_object(obj);
                    return DslCalculatorValue::Bool(true);
                }
            }
        }
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ObjNewWithStrExp
{

}
impl<'a> Default for ObjNewWithStrExp<'a>
{
    fn default() -> Self
    {
        ObjNewWithStrExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ObjNewWithStrExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ObjNewWithStrExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ObjNewWithStrExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() == 1 {
            let opd = &operands[0];
            if let DslCalculatorValue::String(name) = opd {
                if let Some(obj) = self.calculator().borrow_mut().new_object(&name) {
                    return DslCalculatorValue::Object(obj.borrow().get_object_id());
                }
            }
        }
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ObjGetClassNameExp
{

}
impl<'a> Default for ObjGetClassNameExp<'a>
{
    fn default() -> Self
    {
        ObjGetClassNameExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ObjGetClassNameExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ObjGetClassNameExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ObjGetClassNameExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() == 1 {
            let opd = &operands[0];
            if let DslCalculatorValue::Object(obj_id) = opd {
                let mut obj_opt = None;
                if let Some(obj) = self.calculator().borrow().get_object(*obj_id) {
                    obj_opt = Some(obj.clone());
                }
                if let Some(obj) = &obj_opt {
                    let name = String::from(obj.borrow().get_class_name());
                    return DslCalculatorValue::String(name);
                }
            }
        }
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ObjGetDispIdExp
{

}
impl<'a> Default for ObjGetDispIdExp<'a>
{
    fn default() -> Self
    {
        ObjGetDispIdExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ObjGetDispIdExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ObjGetDispIdExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ObjGetDispIdExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() == 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Object(obj_id) = opd0 {
                let mut obj_opt = None;
                if let Some(obj) = self.calculator().borrow().get_object(*obj_id) {
                    obj_opt = Some(obj.clone());
                }
                if let Some(obj) = &obj_opt {
                    if let DslCalculatorValue::String(name) = opd1 {
                        let disp_id = obj.borrow().get_dispatch_id(name);
                        return DslCalculatorValue::Uint(disp_id);
                    }
                }
            }
        }
        return DslCalculatorValue::Uint(u32::MAX);
    }
    impl_simple_expression!();
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
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Object(obj_id) = opd0 {
                let mut obj_opt = None;
                if let Some(obj) = self.calculator().borrow().get_object(*obj_id) {
                    obj_opt = Some(obj.clone());
                }
                if let Some(obj) = obj_opt {
                    let disp_id = opd1.to_u32();
                    let args = &operands.iter().skip(2).collect::<Vec<&DslCalculatorValue>>();
                    if let Some(v) = obj.borrow_mut().invoke_method(disp_id, args) {
                        return v;
                    }
                }
            }
        }
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
                DslCalculatorValue::Object(obj_id) => {
                    let mut obj_opt = None;
                    if let Some(obj) = self.calculator().borrow().get_object(*obj_id) {
                        obj_opt = Some(obj.clone());
                    }
                    if let Some(obj) = obj_opt {
                        let disp_id = opd1.to_u32();
                        obj.borrow_mut().set_property(disp_id, &opd2);
                        return DslCalculatorValue::Bool(true);
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
                DslCalculatorValue::Object(obj_id) => {
                    let mut obj_opt = None;
                    if let Some(obj) = self.calculator().borrow().get_object(*obj_id) {
                        obj_opt = Some(obj.clone());
                    }
                    if let Some(obj) = obj_opt {
                        let disp_id = opd1.to_u32();
                        if let Some(v) = obj.borrow().get_property(disp_id) {
                            return v;
                        }
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
    disp_id: u32,
}
impl<'a> Default for ObjectCallExp<'a>
{
    fn default() -> Self
    {
        ObjectCallExp {
            disp_id: u32::MAX,
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
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Object(obj_id) = opd0 {
                let mut obj_opt = None;
                if let Some(obj) = self.calculator().borrow().get_object(*obj_id) {
                    obj_opt = Some(obj.clone());
                }
                if let Some(obj) = obj_opt {
                    if self.disp_id == u32::MAX {
                        if let DslCalculatorValue::String(name) = opd1 {
                            self.disp_id = obj.borrow().get_dispatch_id(name);
                        }
                    }
                    if self.disp_id != u32::MAX {
                        let args = &operands.iter().skip(2).collect::<Vec<&DslCalculatorValue>>();
                        if let Some(v) = obj.borrow_mut().invoke_method(self.disp_id, args) {
                            return v;
                        }
                    }
                }
            }
        }
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ObjectSetExp
{
    disp_id: u32,
}
impl<'a> Default for ObjectSetExp<'a>
{
    fn default() -> Self
    {
        ObjectSetExp {
            disp_id: u32::MAX,
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
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            if let DslCalculatorValue::Object(obj_id) = opd0 {
                let mut obj_opt = None;
                if let Some(obj) = self.calculator().borrow().get_object(*obj_id) {
                    obj_opt = Some(obj.clone());
                }
                if let Some(obj) = obj_opt {
                    if self.disp_id == u32::MAX {
                        if let DslCalculatorValue::String(name) = opd1 {
                            self.disp_id = obj.borrow().get_dispatch_id(name);
                        }
                    }
                    if self.disp_id != u32::MAX {
                        obj.borrow_mut().set_property(self.disp_id, opd2);
                        return DslCalculatorValue::Bool(true);
                    }
                }
            }
        }
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ObjectGetExp
{
    disp_id: u32,
}
impl<'a> Default for ObjectGetExp<'a>
{
    fn default() -> Self
    {
        ObjectGetExp {
            disp_id: u32::MAX,
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
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Object(obj_id) = opd0 {
                let mut obj_opt = None;
                if let Some(obj) = self.calculator().borrow().get_object(*obj_id) {
                    obj_opt = Some(obj.clone());
                }
                if let Some(obj) = obj_opt {
                    if self.disp_id == u32::MAX {
                        if let DslCalculatorValue::String(name) = opd1 {
                            self.disp_id = obj.borrow().get_dispatch_id(name);
                        }
                    }
                    if self.disp_id != u32::MAX {
                        if let Some(v) = obj.borrow().get_property(self.disp_id) {
                            return v;
                        }
                    }
                }
            }
        }
        return DslCalculatorValue::Null;
    }
    impl_simple_expression!();
}
#[add_abstract_expression_fields]
struct LinqExp<'a>
{
    m_list: Option<ExpressionBox<'a>>,
    m_method: Option<ExpressionBox<'a>>,
    m_exps: Option<Rc<RefCell<Vec<ExpressionBox<'a>>>>>,
}
impl<'a> Default for LinqExp<'a>
{
    fn default() -> Self
    {
        LinqExp {
            m_list: None,
            m_method: None,
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
    fn do_calc(&mut self) -> DslCalculatorValue
    {
        let mut list_val = DslCalculatorValue::Null;
        let mut method_val = DslCalculatorValue::Null;
        if let Some(list) = &mut self.m_list {
            list_val = list.calc();
        }
        if let Some(method) = &mut self.m_method {
            method_val = method.calc();
        }
        let mut exps_owned = None;
        if let Some(exps) = &mut self.m_exps {
            exps_owned = Some(exps.clone());
        }
        if let DslCalculatorValue::String(method) = &method_val {
            let asc = method == "orderby";
            let desc = method == "orderbydesc";
            if asc || desc {
                let list_cloned = list_val.clone();
                if let DslCalculatorValue::Array(list) = &list_cloned {
                    if let Some(exps) = &exps_owned {
                        list.borrow_mut().sort_by(|a, b| {
                            let mut a_cmp_val = DslCalculatorValue::Null;
                            let mut b_cmp_val = DslCalculatorValue::Null;
                            self.calculator().borrow_mut().set_variable("$$", a.clone());
                            for exp in exps.borrow_mut().iter_mut() {
                                a_cmp_val = exp.calc();
                            }
                            self.calculator().borrow_mut().set_variable("$$", b.clone());
                            for exp in exps.borrow_mut().iter_mut() {
                                b_cmp_val = exp.calc();
                            }

                            if let DslCalculatorValue::String(a_str) = &a_cmp_val {
                                if let DslCalculatorValue::String(b_str) = &b_cmp_val {
                                    let mut r = Ordering::Equal;
                                    if a_str > b_str {
                                        r = Ordering::Greater;
                                    }
                                    else if a_str < b_str {
                                        r = Ordering::Less;
                                    }
                                    if desc {
                                        r = r.reverse();
                                    }
                                    return r;
                                }
                            }
                            let a_val = &a_cmp_val.to_f64();
                            let b_val = &b_cmp_val.to_f64();
                            let mut r = Ordering::Equal;
                            if a_val > b_val {
                                r = Ordering::Greater;
                            }
                            else if a_val < b_val {
                                r = Ordering::Less;
                            }
                            if desc {
                                r = r.reverse();
                            }
                            return r;
                        });
                    }
                }
                return list_cloned;
            }
            else if method == "where" {
                if let DslCalculatorValue::Array(list) = &list_val {
                    let mut rs = Vec::new();
                    for item in list.borrow().iter() {
                        if let Some(exps) = &exps_owned {
                            self.calculator().borrow_mut().set_variable("$$", item.clone());
                            let mut val = DslCalculatorValue::Null;
                            for exp in exps.borrow_mut().iter_mut() {
                                val = exp.calc();
                            }
                            if val.to_bool() {
                                rs.push(item.clone());
                            }
                        }
                    }
                    return DslCalculatorValue::Array(Rc::new(RefCell::new(rs)));
                }
                else {
                    return list_val.clone();
                }
            }
            else if method == "top" {
                let mut ct = 0;
                if let Some(exps) = &exps_owned {
                    let mut val = DslCalculatorValue::Null;
                    for exp in exps.borrow_mut().iter_mut() {
                        val = exp.calc();
                    }
                    ct = val.to_u32();
                }
                if let DslCalculatorValue::Array(list) = &list_val {
                    let mut rs = Vec::new();
                    let mut ix = 0;
                    for item in list.borrow().iter() {
                        if ix < ct {
                            rs.push(item.clone());
                        }
                        ix += 1;
                    }
                    return DslCalculatorValue::Array(Rc::new(RefCell::new(rs)));
                }
                else {
                    return list_val.clone();
                }
            }
        }
        return DslCalculatorValue::Null;
    }
    fn load_function(&mut self) -> bool
    {
        if let SyntaxComponent::Function(func) = self.syntax_component() {
            let num = func.get_param_num();
            if func.is_high_order() {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
            else if num > 2 {
                let mut list = None;
                let mut method = None;
                if let Some(param0) = func.get_param(0) {
                    list = DslCalculator::load_syntax_component(self.calculator(), param0);
                }
                if let Some(param1) = func.get_param(1) {
                    method = DslCalculator::load_syntax_component(self.calculator(), param1);
                }
                let mut exps = Vec::new();
                for i in 2..num {
                    if let Some(p) = func.get_param(i) {
                        if let Some(exp) = DslCalculator::load_syntax_component(self.calculator(), p) {
                            exps.push(exp);
                        }
                    }
                }
                self.m_list = list;
                self.m_method = method;
                self.m_exps = Some(Rc::new(RefCell::new(exps)));
            }
            else {
                //error
                self.calculator().borrow().error(&format!("DslCalculator error, {} line {}", func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
            }
        }
        return true;
    }

    impl_abstract_expression!();
}