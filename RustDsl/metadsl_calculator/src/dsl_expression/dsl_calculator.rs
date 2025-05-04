use std::cell::RefCell;
use std::rc::Rc;
use std::hash::{Hash, Hasher};
use std::collections::{BTreeMap, HashMap, VecDeque};
use std::collections::hash_map::Keys;
use metadsl::dsl::{self, FunctionData, StatementData, ValueData, ValueOrFunction, EMPTY_STRING};
use metadsl::dsl::{
    ISyntaxComponent,
    SyntaxComponent,
    DslFile,
    DslLogDelegationBox
};
use metadsl_macros::{
    add_abstract_expression_fields,
    impl_expression_with_abstract,
    impl_abstract_expression,
    add_abstract_and_simple_expression_fields,
    impl_abstract_with_simple,
    impl_simple_expression,
};

pub type ExpressionFactory<'a> = dyn Fn() -> ExpressionBox<'a> + 'a;
pub type ExpressionFactoryBox<'a> = Box<ExpressionFactory<'a>>;

pub type ExpressionBox<'a> = Box<dyn IExpression<'a> + 'a>;
pub type FuncInfoCell<'a> = RefCell<FuncInfo<'a>>;
pub type DslCalculatorCell<'a> = RefCell<DslCalculator<'a>>;

pub type GetVariableDelegation<'a> = dyn Fn(&str) -> Option<&'a DslCalculatorValue<'a>>;
pub type SetVariableDelegation<'a> = dyn FnMut(&str, DslCalculatorValue<'a>) -> bool;
pub type LoadFailbackDelegation<'a> = dyn Fn(&SyntaxComponent, &DslCalculator<'a>) -> Option<ExpressionBox<'a>>;

pub type GetVariableDelegationBox<'a> = Box<GetVariableDelegation<'a>>;
pub type SetVariableDelegationBox<'a> = Box<SetVariableDelegation<'a>>;
pub type LoadFailbackDelegationBox<'a> = Box<LoadFailbackDelegation<'a>>;

pub fn create_expression_factory<'a, T>() -> ExpressionFactoryBox<'a> where T: IExpression<'a> + Default + 'a
{
    return Box::new(|| Box::new(T::default()));
}
#[derive(Clone)]
pub enum DslCalculatorValue<'a>
{
    Null,
    Sbyte(i8),
    Ubyte(u8),
    Short(i16),
    Ushort(u16),
    Int(i32),
    Uint(u32),
    Long(i64),
    Ulong(u64),
    I128(i128),
    U128(u128),
    Float(f32),
    Double(f64),
    String(String),
    Bool(bool),
    Char(char),
    Array(Vec<DslCalculatorValue<'a>>),
    HashMap(HashMap<DslCalculatorValue<'a>, DslCalculatorValue<'a>>),
    Object(Rc<dyn IObjectDispatch<'a> + 'a>),
}
impl<'a> Hash for DslCalculatorValue<'a>
{
    fn hash<H>(&self, state: &mut H) where H: Hasher
    {
        match self
        {
            DslCalculatorValue::Null => {
                state.write_u8(0);
            },
            DslCalculatorValue::Sbyte(val) => {
                state.write_u8(1);
                state.write_i8(*val);
            },
            DslCalculatorValue::Ubyte(val) => {
                state.write_u8(2);
                state.write_u8(*val);
            },
            DslCalculatorValue::Short(val) => {
                state.write_u8(3);
                state.write_i16(*val);
            },
            DslCalculatorValue::Ushort(val) => {
                state.write_u8(4);
                state.write_u16(*val);
            },
            DslCalculatorValue::Int(val) => {
                state.write_u8(5);
                state.write_i32(*val);
            },
            DslCalculatorValue::Uint(val) => {
                state.write_u8(6);
                state.write_u32(*val);
            },
            DslCalculatorValue::Long(val) => {
                state.write_u8(7);
                state.write_i64(*val);
            },
            DslCalculatorValue::Ulong(val) => {
                state.write_u8(8);
                state.write_u64(*val);
            },
            DslCalculatorValue::I128(val) => {
                state.write_u8(9);
                state.write_i128(*val);
            },
            DslCalculatorValue::U128(val) => {
                state.write_u8(10);
                state.write_u128(*val);
            },
            DslCalculatorValue::Float(val) => {
                state.write_u8(11);
                state.write_i64((*val * 1000000.0f32) as i64);
            },
            DslCalculatorValue::Double(val) => {
                state.write_u8(12);
                state.write_i64((*val * 1000000.0f64) as i64);
            },
            DslCalculatorValue::String(val) => {
                state.write_u8(13);
                state.write_u32(val.len() as u32);
            },
            DslCalculatorValue::Bool(val) => {
                state.write_u8(14);
                state.write_u32(*val as u32);
            },
            DslCalculatorValue::Char(val) => {
                state.write_u8(15);
                state.write_u32(*val as u32);
            },
            DslCalculatorValue::Array(val) => {
                state.write_u8(16);
                state.write_u32(val.len() as u32);
                for val in val.iter() {
                    val.hash(state);
                }
            },
            DslCalculatorValue::HashMap(val) => {
                state.write_u8(17);
                state.write_u32(val.len() as u32);
                for (key, val) in val.iter() {
                    key.hash(state);
                    val.hash(state);
                }
            },
            DslCalculatorValue::Object(val) => {
                state.write_u8(18);
                state.write_u32(val.get_type_id());
            },
        }
    }
}
impl<'a> PartialEq for DslCalculatorValue<'a>
{
    fn eq(&self, other: &Self) -> bool
    {
        let ret = match (self, other) {
            (DslCalculatorValue::Null, DslCalculatorValue::Null) => true,
            (DslCalculatorValue::Sbyte(val1), DslCalculatorValue::Sbyte(val2)) => val1 == val2,
            (DslCalculatorValue::Ubyte(val1), DslCalculatorValue::Ubyte(val2)) => val1 == val2,
            (DslCalculatorValue::Short(val1), DslCalculatorValue::Short(val2)) => val1 == val2,
            (DslCalculatorValue::Ushort(val1), DslCalculatorValue::Ushort(val2)) => val1 == val2,
            (DslCalculatorValue::Int(val1), DslCalculatorValue::Int(val2)) => val1 == val2,
            (DslCalculatorValue::Uint(val1), DslCalculatorValue::Uint(val2)) => val1 == val2,
            (DslCalculatorValue::Long(val1), DslCalculatorValue::Long(val2)) => val1 == val2,
            (DslCalculatorValue::Ulong(val1), DslCalculatorValue::Ulong(val2)) => val1 == val2,
            (DslCalculatorValue::I128(val1), DslCalculatorValue::I128(val2)) => val1 == val2,
            (DslCalculatorValue::U128(val1), DslCalculatorValue::U128(val2)) => val1 == val2,
            (DslCalculatorValue::Float(val1), DslCalculatorValue::Float(val2)) => val1 == val2,
            (DslCalculatorValue::Double(val1), DslCalculatorValue::Double(val2)) => val1 == val2,
            (DslCalculatorValue::String(val1), DslCalculatorValue::String(val2)) => val1 == val2,
            (DslCalculatorValue::Bool(val1), DslCalculatorValue::Bool(val2)) => val1 == val2,
            (DslCalculatorValue::Char(val1), DslCalculatorValue::Char(val2)) => val1 == val2,
            (DslCalculatorValue::Array(val1), DslCalculatorValue::Array(val2)) => val1 == val2,
            (DslCalculatorValue::HashMap(_val1), DslCalculatorValue::HashMap(_val2)) => false,
            (_, _) => false,
        };
        return ret;
    }
}
impl<'a> Eq for DslCalculatorValue<'a>
{

}
pub trait IObjectDispatch<'a>
{
    fn get_type_id(&self) -> u32;
    fn get_dispatch_id(&self, name: &str) -> u32;
    fn get_property(&self, disp_id: u32) -> Option<DslCalculatorValue<'a>>;
    fn set_property(&mut self, disp_id: u32, val: &DslCalculatorValue<'a>);
    fn invoke_method(&mut self, disp_id: u32, args: &Vec<DslCalculatorValue<'a>>) -> Option<DslCalculatorValue<'a>>;
}
pub trait IExpression<'a>
{
    fn calc(&mut self) -> DslCalculatorValue<'a>;
    fn load(&mut self, dsl: &SyntaxComponent, calculator: &'a DslCalculatorCell<'a>) -> bool;
}
pub trait AbstractExpression<'a> : IExpression<'a>
{
    fn calc(&mut self) -> DslCalculatorValue<'a>
    {
        let ret = self.do_calc();
        return ret;
    }
    fn load(&mut self, dsl: &SyntaxComponent, calculator: &'a DslCalculatorCell<'a>) -> bool
    {
        self.impl_set_calculator(calculator);
        self.impl_set_syntax_component(dsl.clone());

        match dsl {
            SyntaxComponent::Value(value_data) => {
                return self.load_value(&value_data);
            }
            SyntaxComponent::Function(func_data) => {
                if func_data.have_param() {
                    let ret = self.load_function(func_data);
                    if !ret {
                        let mut args: Vec<ExpressionBox> = Vec::new();
                        if let Some(ps) = func_data.params() {
                            for param in ps.iter() {
                                if let Some(syn) = self.calculator().borrow_mut().load_syntax_component(param) {
                                    args.push(syn);
                                }
                            }
                        }
                        return self.load_expressions(&mut args);
                    }
                    return ret;
                }
                else {
                    return self.load_function(func_data);
                }
            }
            SyntaxComponent::Statement(statement_data) => {
                return self.load_statement(statement_data);
            }
        }
    }
    fn to_string(&self) -> String
    {
        return format!("{} line:{}", std::any::type_name::<Self>(), self.syntax_component().get_line());
    }
    fn load_value(&mut self, _val: &ValueData) -> bool { return false; }
    fn load_expressions(&mut self, _exps: &mut Vec<ExpressionBox>) -> bool { return false; }
    fn load_function(&mut self, _func: &FunctionData) -> bool { return false; }
    fn load_statement(&mut self, _statement: &StatementData) -> bool { return false; }
    fn do_calc(&mut self) -> DslCalculatorValue<'a>;

    fn calculator(&self) -> &'a DslCalculatorCell<'a>
    {
        return self.impl_calculator();
    }
    fn syntax_component(&self) -> &SyntaxComponent
    {
        return self.impl_syntax_component();
    }

    fn impl_calculator(&self) -> &'a DslCalculatorCell<'a>;
    fn impl_syntax_component(&self) -> &SyntaxComponent;
    fn impl_set_calculator(&mut self, calculator: &'a DslCalculatorCell<'a>);
    fn impl_set_syntax_component(&mut self, dsl: SyntaxComponent);
}

pub trait SimpleExpressionBase<'a> : AbstractExpression<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let mut operands = self.calculator().borrow_mut().new_calculator_value_list();
        for exp in self.impl_get_expressions_mut().iter_mut() {
            let v = exp.calc();
            operands.push(v);
        }
        let r = self.on_calc(&mut operands);
        self.calculator().borrow_mut().recycle_calculator_value_list(operands);
        return r;
    }
    fn load_expressions(&mut self, exps: &'a mut Vec<ExpressionBox<'a>>) -> bool
    {
        let exps_moved = std::mem::take(exps);
        self.impl_set_expressions(exps_moved);
        return true;
    }
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue<'a>>) -> DslCalculatorValue<'a>;

    fn impl_get_expressions(&self) -> &Vec<ExpressionBox<'a>>;
    fn impl_get_expressions_mut(&mut self) -> &mut Vec<ExpressionBox<'a>>;
    fn impl_set_expressions(&mut self, exps: Vec<ExpressionBox<'a>>);
}

#[add_abstract_expression_fields]
pub struct ArgsGet<'a>
{
}
impl<'a> Default for ArgsGet<'a>
{
    fn default() -> Self
    {
        Self {
            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ArgsGet<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ArgsGet<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        if let Some(ps) = self.calculator().borrow().arguments() {
            let ret = DslCalculatorValue::Array(ps.clone());
            return ret;
        }
        return DslCalculatorValue::Null;
    }
    fn load_function(&mut self, _func_data: &FunctionData) -> bool
    {
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_expression_fields]
pub struct ArgGet<'a>
{
    m_arg_index: Option<ExpressionBox<'a>>,
}
impl<'a> Default for ArgGet<'a>
{
    fn default() -> Self
    {
        ArgGet {
            m_arg_index: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ArgGet<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ArgGet<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let mut uix = 0;
        if let Some(arg_index) = &mut self.m_arg_index {
            if let DslCalculatorValue::Int(ix) = arg_index.calc() {
                uix = ix as usize;
            }
        }
        let mut ret = DslCalculatorValue::Null;
        let cell = self.calculator();
        if let Some(args) = cell.borrow().arguments() {
            if uix < args.len() {
                ret = args[uix].clone();
            }
        }
        return ret;
    }
    fn load_function(&mut self, func_data: &FunctionData) -> bool
    {
        if let Some(arg) = func_data.get_param(0) {
            let v = self.calculator().borrow_mut().load_syntax_component(arg);
            self.m_arg_index = v;
        }
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_expression_fields]
pub struct ArgNumGet<'a>
{}
impl<'a> Default for ArgNumGet<'a>
{
    fn default() -> Self
    {
        ArgNumGet {
            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ArgNumGet<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ArgNumGet<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        if let Some(args) = self.calculator().borrow().arguments() {
            let ret = args.len() as i32;
            return DslCalculatorValue::Int(ret);
        }
        return DslCalculatorValue::Null;
    }
    fn load_function(&mut self, _func_data: &FunctionData) -> bool
    {
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_expression_fields]
pub struct GlobalVarSet<'a>
{
    m_var_id: Option<String>,
    m_op: Option<ExpressionBox<'a>>,
    m_var_ix: i32,
}
impl<'a> Default for GlobalVarSet<'a>
{
    fn default() -> Self
    {
        GlobalVarSet {
            m_var_id: None,
            m_op: None,
            m_var_ix: 0,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for GlobalVarSet<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for GlobalVarSet<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let mut v =  DslCalculatorValue::Null;
        if let Some(op) = &mut self.m_op {
            v = op.calc();
        }
        if self.m_var_ix < std::i32::MAX {
            self.calculator().borrow_mut().set_global_varaible_by_index(self.m_var_ix, v.clone());
        }
        else if let Some(var_id) = &self.m_var_id {
            if var_id.len() > 0 {
                let ix = self.calculator().borrow_mut().alloc_global_variable_index(&var_id);
                self.m_var_ix = ix;
                if self.m_var_ix < std::i32::MAX {
                    self.calculator().borrow_mut().set_global_varaible_by_index(self.m_var_ix, v.clone());
                }
                else {
                    self.calculator().borrow_mut().set_global_variable(&var_id, v.clone());
                }
            }
        }
        return v;
    }
    fn load_function(&mut self, func_data: &FunctionData) -> bool
    {
        let param1 = func_data.get_param(0);
        let param2 = func_data.get_param(1);
        if let Some(p1) = param1 {
            self.m_var_id = Some(String::from(p1.get_id()));
        }
        if let Some(p2) = param2 {
            let v = self.calculator().borrow_mut().load_syntax_component(p2);
            self.m_op = v;
        }
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_expression_fields]
pub struct GlobalVarGet<'a>
{
    m_var_id: Option<String>,
    m_var_ix: i32,
}
impl<'a> Default for GlobalVarGet<'a>
{
    fn default() -> Self
    {
        GlobalVarGet {
            m_var_id: None,
            m_var_ix: 0,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for GlobalVarGet<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for GlobalVarGet<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let mut ret = DslCalculatorValue::Null;
        let mut is_break = false;
        let mut is_continue = false;
        if let Some(var_id) = &self.m_var_id {
            if var_id == "break" {
                is_break = true;
            }
            else if var_id == "continue" {
                is_continue = true;
            }
        }
        if is_break {
            self.calculator().borrow_mut().set_run_state(RunStateEnum::Break);
            return ret;
        }
        else if is_continue {
            self.calculator().borrow_mut().set_run_state(RunStateEnum::Continue);
            return ret;
        }
        else if self.m_var_ix < std::i32::MAX {
            if let Some(v) = self.calculator().borrow().get_global_varaible_by_index(self.m_var_ix) {
                ret = v.clone();
            }
        }
        else if let Some(var_id) = &self.m_var_id {
            let var_ix = self.calculator().borrow().get_global_variable_index(var_id);
            self.m_var_ix = var_ix;
            if self.m_var_ix < std::i32::MAX {
                if let Some(v) = self.calculator().borrow().get_global_varaible_by_index(self.m_var_ix) {
                    ret = v.clone();
                }
            }
            else if let Some(v) = self.calculator().borrow().get_global_variable(var_id) {
                ret = v.clone();
            }
            else {
                self.calculator().borrow().error(&format!("unassigned global var '{0}'", var_id));
            }
        }
        return ret;
    }
    fn load_value(&mut self, val_data: &ValueData) -> bool
    {
        self.m_var_id = Some(String::from(val_data.get_id()));
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_expression_fields]
pub struct LocalVarSet<'a>
{
    m_var_id: Option<String>,
    m_op: Option<ExpressionBox<'a>>,
    m_var_ix: i32,
}
impl<'a> Default for LocalVarSet<'a>
{
    fn default() -> Self
    {
        LocalVarSet {
            m_var_id: None,
            m_op: None,
            m_var_ix: 0,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LocalVarSet<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LocalVarSet<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let mut v = DslCalculatorValue::Null;
        if let Some(op) = &mut self.m_op {
            v = op.calc().clone();
        }
        if self.m_var_ix < std::i32::MAX {
            self.calculator().borrow_mut().set_local_varaible_by_index(self.m_var_ix, v.clone());
        }
        else {
            let mut var_ix = std::i32::MAX;
            if let Some(var_id) = &self.m_var_id {
                var_ix = self.calculator().borrow_mut().alloc_local_variable_index(var_id);
            }
            if var_ix < std::i32::MAX {
                self.m_var_ix = var_ix;
                self.calculator().borrow_mut().set_local_varaible_by_index(var_ix, v.clone());
            }
            else {
                if let Some(var_id) = &self.m_var_id {
                    self.calculator().borrow().error(&format!("unassigned local var '{0}'", var_id));
                }
            }
        }
        return v;
    }
    fn load_function(&mut self, func_data: &FunctionData) -> bool
    {
        if let Some(param1) = func_data.get_param(0) {
            if let Some(param2) = func_data.get_param(1) {
                self.m_var_id = Some(String::from(param1.get_id()));
                let op = self.calculator().borrow_mut().load_syntax_component(param2);
                self.m_op = op;
            }
        }
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_expression_fields]
pub struct LocalVarGet<'a>
{
    m_var_id: Option<String>,
    m_var_ix: i32,
}
impl<'a> Default for LocalVarGet<'a>
{
    fn default() -> Self
    {
        LocalVarGet {
            m_var_id: None,
            m_var_ix: 0,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for LocalVarGet<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for LocalVarGet<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let mut ret = DslCalculatorValue::Null;
        if self.m_var_ix < std::i32::MAX {
            if let Some(r) = self.calculator().borrow().get_local_varaible_by_index(self.m_var_ix) {
                ret = r.clone();
            }
        }
        else {
            let mut var_ix = std::i32::MAX;
            if let Some(var_id) = &self.m_var_id {
                var_ix = self.calculator().borrow().get_local_variable_index(var_id);
            }
            if var_ix < std::i32::MAX {
                self.m_var_ix = var_ix;
                if let Some(r) = self.calculator().borrow().get_local_varaible_by_index(var_ix) {
                    ret = r.clone();
                }
            }
            else {
                if let Some(var_id) = &self.m_var_id {
                    self.calculator().borrow().error(&format!("unassigned local var '{0}'", var_id));
                }
            }
        }
        return ret;
    }
    fn load_value(&mut self, val_data: &ValueData) -> bool
    {
        self.m_var_id = Some(String::from(val_data.get_id()));
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_expression_fields]
pub struct ConstGet<'a>
{
    m_val: DslCalculatorValue<'a>,
}
impl<'a> Default for ConstGet<'a>
{
    fn default() -> Self
    {
        ConstGet {
            m_val: DslCalculatorValue::Null,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ConstGet<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ConstGet<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let v = &self.m_val;
        return v.clone();
    }
    fn load_value(&mut self, val_data: &ValueData) -> bool
    {
        let id = val_data.get_id();
        let id_type = val_data.get_id_type();
        if id_type == dsl::NUM_TOKEN {
            //TryParseNumeric(id, out m_Val);
            if let Ok(v) = id.parse::<f64>() {
                self.m_val = DslCalculatorValue::Double(v);
            }
            else if let Ok(v) = id.parse::<i64>() {
                self.m_val = DslCalculatorValue::Long(v);
            }
            else if let Ok(v) = id.parse::<u64>() {
                self.m_val = DslCalculatorValue::Ulong(v);
            }
        }
        else {
            if id_type == dsl::ID_TOKEN {
                if id == "true" || id=="false" || id=="True" || id=="False" {
                    self.m_val = DslCalculatorValue::Bool(id=="true" || id=="True");
                }
                else {
                    self.m_val = DslCalculatorValue::String(id.clone());
                }
            }
            else {
                self.m_val = DslCalculatorValue::String(id.clone());
            }
        }
        return true;
    }

    impl_abstract_expression!();
}

#[add_abstract_expression_fields]
pub struct FunctionCall<'a>
{
    m_func: Option<String>,

    m_args: Vec<ExpressionBox<'a>>,
}
impl<'a> Default for FunctionCall<'a>
{
    fn default() -> Self
    {
        FunctionCall {
            m_func: None,
            m_args: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for FunctionCall<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for FunctionCall<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let mut args = self.calculator().borrow_mut().new_calculator_value_list();
        for arg in self.m_args.iter_mut() {
            let o = arg.calc();
            args.push(o);
        }
        let mut r = DslCalculatorValue::Null;
        if let Some(func) = &self.m_func {
            r = self.calculator().borrow_mut().calc_n(func, &mut args);
        }
        self.calculator().borrow_mut().recycle_calculator_value_list(args);
        return r;
    }
    fn load_function(&mut self, func_data: &FunctionData) -> bool
    {
        if !func_data.is_high_order() && func_data.have_param() {
            self.m_func = Some(String::from(func_data.get_id()));
            if let Some(ps) = func_data.params() {
                for p in ps.iter() {
                    let vopt = self.calculator().borrow_mut().load_syntax_component(p);
                    if let Some(v) = vopt {
                        self.m_args.push(v);
                    }
                }
            }
            return true;
        }
        return false;
    }

    impl_abstract_expression!();
}
#[add_abstract_expression_fields]
pub struct ParenthesisExp<'a>
{
    m_expressions: Vec<ExpressionBox<'a>>,
}
impl<'a> Default for ParenthesisExp<'a>
{
    fn default() -> Self
    {
        ParenthesisExp {
            m_expressions: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ParenthesisExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ParenthesisExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let mut v = DslCalculatorValue::Null;
        for exp in self.m_expressions.iter_mut() {
            v = exp.calc();
        }
        return v;
    }
    fn load_function(&mut self, func_data: &FunctionData) -> bool
    {
        if let Some(ps) = func_data.params() {
            for p in ps.iter() {
                let vopt = self.calculator().borrow_mut().load_syntax_component(p);
                if let Some(v) = vopt {
                    self.m_expressions.push(v);
                }
            }
        }
        return true;
    }

    impl_abstract_expression!();
}
#[add_abstract_and_simple_expression_fields]
pub struct ArrayExp<'a>
{
}
impl<'a> Default for ArrayExp<'a>
{
    fn default() -> Self
    {
        ArrayExp {
            m_exps: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ArrayExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ArrayExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ArrayExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue<'a>>) -> DslCalculatorValue<'a>
    {
        let mut r = Vec::new();
        for oper in operands.iter() {
            r.push(oper.clone());
        }
        return DslCalculatorValue::Array(r);
    }

    impl_simple_expression!();
}
#[add_abstract_expression_fields]
pub struct HashtableExp<'a>
{
    m_expressions: Vec<ExpressionBox<'a>>,
}
impl<'a> Default for HashtableExp<'a>
{
    fn default() -> Self
    {
        HashtableExp {
            m_expressions: Vec::new(),

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableExp<'a>
{
    fn do_calc(&mut self) -> DslCalculatorValue<'a>
    {
        let mut dict = HashMap::<DslCalculatorValue<'a>, DslCalculatorValue<'a>>::new();
        let mut i = 0;
        while i + 1 < self.m_expressions.len() {
            let key = self.m_expressions[i].calc();
            let val = self.m_expressions[i + 1].calc();
            dict.insert(key, val);
            i += 2;
        }
        let r = DslCalculatorValue::HashMap(dict);
        return r;
    }
    fn load_function(&mut self, func_data: &FunctionData) -> bool
    {
        if let Some(ps) = func_data.params() {
            for p in ps.iter() {
                if let SyntaxComponent::Function(fd) = &p {
                    if fd.get_param_num() == 2 {
                        if let Some(p) = fd.get_param(0) {
                            let exp_key = self.calculator().borrow_mut().load_syntax_component(p);
                            if let Some(key) = exp_key {
                                self.m_expressions.push(key);
                            }
                        }
                        if let Some(p) = fd.get_param(1) {
                            let exp_val = self.calculator().borrow_mut().load_syntax_component(p);
                            if let Some(val) = exp_val {
                                self.m_expressions.push(val);
                            }
                        }
                    }
                }
            }
        }
        return true;
    }

    impl_abstract_expression!();
}
#[derive(PartialEq)]
pub enum RunStateEnum
{
    Normal = 0,
    Break,
    Continue,
    Return,
    Redirect,
}
pub struct FuncInfo<'a>
{
    pub local_var_indexes: HashMap<String, i32>,
    pub codes: Vec<ExpressionBox<'a>>,
}
impl<'a> FuncInfo<'a>
{
    pub fn clear(&mut self)
    {
        self.local_var_indexes.clear();
        self.codes.clear();
    }
    pub fn add_arg_name_index(&mut self, arg_name: &str)
    {
        let ix = self.local_var_indexes.len() as i32;
        self.local_var_indexes.insert(String::from(arg_name), -1 - ix);
    }
    pub fn build_arg_name_indexes(&mut self, arg_names: &'a Vec<String>)
    {
        let mut ix = 0;
        while ix < arg_names.len() {
            self.add_arg_name_index(&arg_names[ix]);
            ix += 1;
        }
    }
    pub fn new() -> Self
    {
        Self {
            local_var_indexes: HashMap::new(),
            codes: Vec::new(),
        }
    }
}
pub struct StackInfo<'a>
{
    pub func_name: &'a str,
    pub args: Vec<DslCalculatorValue<'a>>,
    pub local_vars: Vec<DslCalculatorValue<'a>>,
}
impl<'a> Default for StackInfo<'a>
{
    fn default() -> Self
    {
        Self {
            func_name: &EMPTY_STRING,
            args: Vec::new(),
            local_vars: Vec::new(),
        }
    }
}
impl<'a> StackInfo<'a>
{
    pub fn init(&mut self, func_name: &'a str, func_info: &FuncInfoCell<'a>)
    {
        self.func_name = func_name;
        let len = func_info.borrow().local_var_indexes.len();
        let mut ix = 0;
        while ix < len {
            self.local_vars.push(DslCalculatorValue::Null);
            ix += 1;
        }
    }
    pub fn clear(&mut self)
    {
        self.func_name = &EMPTY_STRING;
        self.args.clear();
        self.local_vars.clear();
    }
}
pub struct DslCalculator<'a>
{
    pub on_log: Option<&'a DslLogDelegationBox<'a>>,
    pub on_get_variable: Option<&'a GetVariableDelegationBox<'a>>,
    pub on_set_variable: Option<&'a mut SetVariableDelegationBox<'a>>,
    pub on_load_failback: Option<&'a LoadFailbackDelegationBox<'a>>,

    m_inited: bool,
    m_run_state: RunStateEnum,
    m_funcs: HashMap<String, FuncInfoCell<'a>>,
    m_stack: VecDeque<StackInfo<'a>>,
    m_named_global_variable_indexes: HashMap<String, i32>,
    m_global_variables: Vec<DslCalculatorValue<'a>>,
    m_api_factories: HashMap<&'a str, ExpressionFactoryBox<'a>>,
    m_api_docs: BTreeMap<&'a str, &'a str>,
    m_func_calls: Vec<FunctionData>,
    m_value_list_pool: RefCell<SimpleObjectPool<Vec<DslCalculatorValue<'a>>>>,
    m_stack_info_pool: RefCell<SimpleObjectPool<StackInfo<'a>>>,
    m_self_cell: Option<&'a DslCalculatorCell<'a>>,
}
impl<'a> DslCalculator<'a>
{
    pub fn inited(&self) -> bool
    {
        return self.m_inited;
    }
    pub fn init(&mut self, cell: &'a DslCalculatorCell<'a>)
    {
        self.m_inited = true;
        self.m_self_cell = Some(cell);

        self.register_api("args", "args() api", create_expression_factory::<ArgsGet>());
        self.register_api("arg", "arg(ix) api", create_expression_factory::<ArgGet>());
        self.register_api("argnum", "argnum() api", create_expression_factory::<ArgNumGet>());
        /*
        self.register_api("+", "add operator", CreateExpressionFactory::<AddExp>());
        self.register_api("-", "sub operator", CreateExpressionFactory::<SubExp>());
        self.register_api("*", "mul operator", CreateExpressionFactory::<MulExp>());
        self.register_api("/", "div operator", CreateExpressionFactory::<DivExp>());
        self.register_api("%", "mod operator", CreateExpressionFactory::<ModExp>());
        self.register_api("&", "bitand operator", CreateExpressionFactory::<BitAndExp>());
        self.register_api("|", "bitor operator", CreateExpressionFactory::<BitOrExp>());
        self.register_api("^", "bitxor operator", CreateExpressionFactory::<BitXorExp>());
        self.register_api("~", "bitnot operator", CreateExpressionFactory::<BitNotExp>());
        self.register_api("<<", "left shift operator", CreateExpressionFactory::<LShiftExp>());
        self.register_api(">>", "right shift operator", CreateExpressionFactory::<RShiftExp>());
        self.register_api("max", "max(v1,v2) api", CreateExpressionFactory::<MaxExp>());
        self.register_api("min", "min(v1,v2) api", CreateExpressionFactory::<MinExp>());
        self.register_api("abs", "abs(v) api", CreateExpressionFactory::<AbsExp>());
        self.register_api("sin", "sin(v) api", CreateExpressionFactory::<SinExp>());
        self.register_api("cos", "cos(v) api", CreateExpressionFactory::<CosExp>());
        self.register_api("tan", "tan(v) api", CreateExpressionFactory::<TanExp>());
        self.register_api("asin", "asin(v) api", CreateExpressionFactory::<AsinExp>());
        self.register_api("acos", "acos(v) api", CreateExpressionFactory::<AcosExp>());
        self.register_api("atan", "atan(v) api", CreateExpressionFactory::<AtanExp>());
        self.register_api("atan2", "atan2(v1,v2) api", CreateExpressionFactory::<Atan2Exp>());
        self.register_api("sinh", "sinh(v) api", CreateExpressionFactory::<SinhExp>());
        self.register_api("cosh", "cosh(v) api", CreateExpressionFactory::<CoshExp>());
        self.register_api("tanh", "tanh(v) api", CreateExpressionFactory::<TanhExp>());
        self.register_api("rndint", "rndint(min,max) api", CreateExpressionFactory::<RndIntExp>());
        self.register_api("rndfloat", "rndfloat(min,max) api", CreateExpressionFactory::<RndFloatExp>());
        self.register_api("pow", "pow(v1,v2) api", CreateExpressionFactory::<PowExp>());
        self.register_api("sqrt", "sqrt(v) api", CreateExpressionFactory::<SqrtExp>());
        self.register_api("exp", "exp(v) api", CreateExpressionFactory::<ExpExp>());
        self.register_api("exp2", "exp2(v) api", CreateExpressionFactory::<Exp2Exp>());
        self.register_api("log", "log(v) api", CreateExpressionFactory::<LogExp>());
        self.register_api("log2", "log2(v) api", CreateExpressionFactory::<Log2Exp>());
        self.register_api("log10", "log10(v) api", CreateExpressionFactory::<Log10Exp>());
        self.register_api("floor", "floor(v) api", CreateExpressionFactory::<FloorExp>());
        self.register_api("ceiling", "ceiling(v) api", CreateExpressionFactory::<CeilingExp>());
        self.register_api("round", "round(v) api", CreateExpressionFactory::<RoundExp>());
        self.register_api("floortoint", "floortoint(v) api", CreateExpressionFactory::<FloorToIntExp>());
        self.register_api("ceilingtoint", "ceilingtoint(v) api", CreateExpressionFactory::<CeilingToIntExp>());
        self.register_api("roundtoint", "roundtoint(v) api", CreateExpressionFactory::<RoundToIntExp>());
        self.register_api("bool", "bool(v) api", CreateExpressionFactory::<BoolExp>());
        self.register_api("sbyte", "sbyte(v) api", CreateExpressionFactory::<SByteExp>());
        self.register_api("byte", "byte(v) api", CreateExpressionFactory::<ByteExp>());
        self.register_api("char", "char(v) api", CreateExpressionFactory::<CharExp>());
        self.register_api("short", "short(v) api", CreateExpressionFactory::<ShortExp>());
        self.register_api("ushort", "ushort(v) api", CreateExpressionFactory::<UShortExp>());
        self.register_api("int", "int(v) api", CreateExpressionFactory::<IntExp>());
        self.register_api("uint", "uint(v) api", CreateExpressionFactory::<UIntExp>());
        self.register_api("long", "long(v) api", CreateExpressionFactory::<LongExp>());
        self.register_api("ulong", "ulong(v) api", CreateExpressionFactory::<ULongExp>());
        self.register_api("float", "float(v) api", CreateExpressionFactory::<FloatExp>());
        self.register_api("double", "double(v) api", CreateExpressionFactory::<DoubleExp>());
        self.register_api("decimal", "decimal(v) api", CreateExpressionFactory::<DecimalExp>());
        self.register_api("ftoi", "ftoi(v) api", CreateExpressionFactory::<FtoiExp>());
        self.register_api("itof", "itof(v) api", CreateExpressionFactory::<ItofExp>());
        self.register_api("ftou", "ftou(v) api", CreateExpressionFactory::<FtouExp>());
        self.register_api("utof", "utof(v) api", CreateExpressionFactory::<UtofExp>());
        self.register_api("dtol", "dtol(v) api", CreateExpressionFactory::<DtolExp>());
        self.register_api("ltod", "ltod(v) api", CreateExpressionFactory::<LtodExp>());
        self.register_api("dtou", "dtou(v) api", CreateExpressionFactory::<DtouExp>());
        self.register_api("utod", "utod(v) api", CreateExpressionFactory::<UtodExp>());
        self.register_api("lerp", "lerp(a,b,t) api", CreateExpressionFactory::<LerpExp>());
        self.register_api("lerpunclamped", "lerpunclamped(a,b,t) api", CreateExpressionFactory::<LerpUnclampedExp>());
        self.register_api("lerpangle", "lerpangle(a,b,t) api", CreateExpressionFactory::<LerpAngleExp>());
        self.register_api("smoothstep", "smoothstep(from,to,t) api", CreateExpressionFactory::<SmoothStepExp>());
        self.register_api("clamp01", "clamp01(v) api", CreateExpressionFactory::<Clamp01Exp>());
        self.register_api("clamp", "clamp(v,v1,v2) api", CreateExpressionFactory::<ClampExp>());
        self.register_api("approximately", "approximately(v1,v2) api", CreateExpressionFactory::<ApproximatelyExp>());
        self.register_api("ispoweroftwo", "ispoweroftwo(v) api", CreateExpressionFactory::<IsPowerOfTwoExp>());
        self.register_api("closestpoweroftwo", "closestpoweroftwo(v) api", CreateExpressionFactory::<ClosestPowerOfTwoExp>());
        self.register_api("nextpoweroftwo", "nextpoweroftwo(v) api", CreateExpressionFactory::<NextPowerOfTwoExp>());
        self.register_api("dist", "dist(x1,y1,x2,y2) api", CreateExpressionFactory::<DistExp>());
        self.register_api("distsqr", "distsqr(x1,y1,x2,y2) api", CreateExpressionFactory::<DistSqrExp>());
        self.register_api(">", "great operator", CreateExpressionFactory::<GreatExp>());
        self.register_api(">=", "great equal operator", CreateExpressionFactory::<GreatEqualExp>());
        self.register_api("<", "less operator", CreateExpressionFactory::<LessExp>());
        self.register_api("<=", "less equal operator", CreateExpressionFactory::<LessEqualExp>());
        self.register_api("==", "equal operator", CreateExpressionFactory::<EqualExp>());
        self.register_api("!=", "not equal operator", CreateExpressionFactory::<NotEqualExp>());
        self.register_api("&&", "logical and operator", CreateExpressionFactory::<AndExp>());
        self.register_api("||", "logical or operator", CreateExpressionFactory::<OrExp>());
        self.register_api("!", "logical not operator", CreateExpressionFactory::<NotExp>());
        self.register_api("?", "conditional expression", CreateExpressionFactory::<CondExp>());
        self.register_api("if", "if(cond)func(args); or if(cond){...}[elseif/elif(cond){...}else{...}]; statement", CreateExpressionFactory::<IfExp>());
        self.register_api("while", "while(cond)func(args); or while(cond){...}; statement, iterator is $$", CreateExpressionFactory::<WhileExp>());
        self.register_api("loop", "loop(ct)func(args); or loop(ct){...}; statement, iterator is $$", CreateExpressionFactory::<LoopExp>());
        self.register_api("looplist", "looplist(list)func(args); or looplist(list){...}; statement, iterator is $$", CreateExpressionFactory::<LoopListExp>());
        self.register_api("foreach", "foreach(args)func(args); or foreach(args){...}; statement, iterator is $$", CreateExpressionFactory::<ForeachExp>());
        self.register_api("format", "format(fmt,arg1,arg2,...) api", CreateExpressionFactory::<FormatExp>());
        self.register_api("gettypeassemblyname", "gettypeassemblyname(obj) api", CreateExpressionFactory::<GetTypeAssemblyNameExp>());
        self.register_api("gettypefullname", "gettypefullname(obj) api", CreateExpressionFactory::<GetTypeFullNameExp>());
        self.register_api("gettypename", "gettypename(obj) api", CreateExpressionFactory::<GetTypeNameExp>());
        self.register_api("gettype", "gettype(type_str) api", CreateExpressionFactory::<GetTypeExp>());
        self.register_api("changetype", "changetype(obj,type_str) api", CreateExpressionFactory::<ChangeTypeExp>());
        self.register_api("parseenum", "parseenum(type_str,val_str) api", CreateExpressionFactory::<ParseEnumExp>());
        self.register_api("objectcall", "objectcall api, fn implementation, using csharp object syntax", CreateExpressionFactory::<DotnetCallExp>());
        self.register_api("objectset", "objectset api, fn implementation, using csharp object syntax", CreateExpressionFactory::<DotnetSetExp>());
        self.register_api("objectget", "objectget api, fn implementation, using csharp object syntax", CreateExpressionFactory::<DotnetGetExp>());
        self.register_api("collectioncall", "collectioncall api, fn implementation, using csharp object syntax", CreateExpressionFactory::<CollectionCallExp>());
        self.register_api("collectionset", "collectionset api, fn implementation, using csharp object syntax", CreateExpressionFactory::<CollectionSetExp>());
        self.register_api("collectionget", "collectionget api, fn implementation, using csharp object syntax", CreateExpressionFactory::<CollectionGetExp>());
        self.register_api("linq", "linq(list,method,arg1,arg2,...) statement, fn implementation, using obj.method(arg1,arg2,...) syntax, method can be orderby/orderbydesc/where/top, iterator is $$", CreateExpressionFactory::<LinqExp>());
        self.register_api("isnull", "isnull(obj) api", CreateExpressionFactory::<IsNullExp>());
        self.register_api("null", "null() api", CreateExpressionFactory::<NullExp>());
        self.register_api("equalsnull", "equalsnull(obj) api", CreateExpressionFactory::<EqualsNullExp>());
        self.register_api("objectload", "objectload(dll_path) api", CreateExpressionFactory::<DotnetLoadExp>());
        self.register_api("objectnew", "objectnew(assembly,type_name,arg1,arg2,...) api", CreateExpressionFactory::<DotnetNewExp>());
        self.register_api("destroyobject", "destroyobject(obj[,bool_modify_asset]) api", CreateExpressionFactory::<DestroyObjectExp>());
        self.register_api("getcomponent", "getcomponent(obj,type) api", CreateExpressionFactory::<GetComponentExp>());
        self.register_api("getcomponents", "getcomponents(obj,type) api", CreateExpressionFactory::<GetComponentsExp>());
        self.register_api("getcomponentinchildren", "getcomponentinchildren(obj,type) api", CreateExpressionFactory::<GetComponentInChildrenExp>());
        self.register_api("getcomponentsinchildren", "getcomponentsinchildren(obj,type) api", CreateExpressionFactory::<GetComponentsInChildrenExp>());
        self.register_api("substring", "substring(str[,start,len]) function", CreateExpressionFactory::<SubstringExp>());
        self.register_api("newstringbuilder", "newstringbuilder() api", CreateExpressionFactory::<NewStringBuilderExp>());
        self.register_api("appendformat", "appendformat(sb,fmt,arg1,arg2,...) api", CreateExpressionFactory::<AppendFormatExp>());
        self.register_api("appendformatline", "appendformatline(sb,fmt,arg1,arg2,...) api", CreateExpressionFactory::<AppendFormatLineExp>());
        self.register_api("stringbuilder_tostring", "stringbuilder_tostring(sb)", CreateExpressionFactory::<StringBuilderToStringExp>());
        self.register_api("stringjoin", "stringjoin(sep,list) api", CreateExpressionFactory::<StringJoinExp>());
        self.register_api("stringsplit", "stringsplit(str,sep_list) api", CreateExpressionFactory::<StringSplitExp>());
        self.register_api("stringtrim", "stringtrim(str) api", CreateExpressionFactory::<StringTrimExp>());
        self.register_api("stringtrimstart", "stringtrimstart(str) api", CreateExpressionFactory::<StringTrimStartExp>());
        self.register_api("stringtrimend", "stringtrimend(str) api", CreateExpressionFactory::<StringTrimEndExp>());
        self.register_api("stringtolower", "stringtolower(str) api", CreateExpressionFactory::<StringToLowerExp>());
        self.register_api("stringtoupper", "stringtoupper(str) api", CreateExpressionFactory::<StringToUpperExp>());
        self.register_api("stringreplace", "stringreplace(str,key,rep_str) api", CreateExpressionFactory::<StringReplaceExp>());
        self.register_api("stringreplacechar", "stringreplacechar(str,key,char_as_str) api", CreateExpressionFactory::<StringReplaceCharExp>());
        self.register_api("makestring", "makestring(char1_as_str_or_int,char2_as_str_or_int,...) api", CreateExpressionFactory::<MakeStringExp>());
        self.register_api("stringcontains", "stringcontains(str,str_or_list_1,str_or_list_2,...) api", CreateExpressionFactory::<StringContainsExp>());
        self.register_api("stringnotcontains", "stringnotcontains(str,str_or_list_1,str_or_list_2,...) api", CreateExpressionFactory::<StringNotContainsExp>());
        self.register_api("stringcontainsany", "stringcontainsany(str,str_or_list_1,str_or_list_2,...) api", CreateExpressionFactory::<StringContainsAnyExp>());
        self.register_api("stringnotcontainsany", "stringnotcontainsany(str,str_or_list_1,str_or_list_2,...) api", CreateExpressionFactory::<StringNotContainsAnyExp>());
        self.register_api("str2int", "str2int(str) api", CreateExpressionFactory::<Str2IntExp>());
        self.register_api("str2uint", "str2uint(str) api", CreateExpressionFactory::<Str2UintExp>());
        self.register_api("str2long", "str2long(str) api", CreateExpressionFactory::<Str2LongExp>());
        self.register_api("str2ulong", "str2ulong(str) api", CreateExpressionFactory::<Str2UlongExp>());
        self.register_api("str2float", "str2float(str) api", CreateExpressionFactory::<Str2FloatExp>());
        self.register_api("str2double", "str2double(str) api", CreateExpressionFactory::<Str2DoubleExp>());
        self.register_api("hex2int", "hex2int(str) api", CreateExpressionFactory::<Hex2IntExp>());
        self.register_api("hex2uint", "hex2uint(str) api", CreateExpressionFactory::<Hex2UintExp>());
        self.register_api("hex2long", "hex2long(str) api", CreateExpressionFactory::<Hex2LongExp>());
        self.register_api("hex2ulong", "hex2ulong(str) api", CreateExpressionFactory::<Hex2UlongExp>());
        self.register_api("datetimestr", "datetimestr(fmt) api", CreateExpressionFactory::<DatetimeStrExp>());
        self.register_api("longdatestr", "longdatestr() api", CreateExpressionFactory::<LongDateStrExp>());
        self.register_api("longtimestr", "longtimestr() api", CreateExpressionFactory::<LongTimeStrExp>());
        self.register_api("shortdatestr", "shortdatestr() api", CreateExpressionFactory::<ShortDateStrExp>());
        self.register_api("shorttimestr", "shorttimestr() api", CreateExpressionFactory::<ShortTimeStrExp>());
        self.register_api("isnullorempty", "isnullorempty(str) api", CreateExpressionFactory::<IsNullOrEmptyExp>());
        self.register_api("array", "[v1,v2,...] or array(v1,v2,...) object", CreateExpressionFactory::<ArrayExp>());
        self.register_api("toarray", "toarray(list) api", CreateExpressionFactory::<ToArrayExp>());
        self.register_api("listsize", "listsize(list) api", CreateExpressionFactory::<ListSizeExp>());
        self.register_api("list", "list(v1,v2,...) object", CreateExpressionFactory::<ListExp>());
        self.register_api("listget", "listget(list,index[,defval]) api", CreateExpressionFactory::<ListGetExp>());
        self.register_api("listset", "listset(list,index,val) api", CreateExpressionFactory::<ListSetExp>());
        self.register_api("listindexof", "listindexof(list,val) api", CreateExpressionFactory::<ListIndexOfExp>());
        self.register_api("listadd", "listadd(list,val) api", CreateExpressionFactory::<ListAddExp>());
        self.register_api("listremove", "listremove(list,val) api", CreateExpressionFactory::<ListRemoveExp>());
        self.register_api("listinsert", "listinsert(list,index,val) api", CreateExpressionFactory::<ListInsertExp>());
        self.register_api("listremoveat", "listremoveat(list,index) api", CreateExpressionFactory::<ListRemoveAtExp>());
        self.register_api("listclear", "listclear(list) api", CreateExpressionFactory::<ListClearExp>());
        self.register_api("listsplit", "listsplit(list,ct) api, return list of list", CreateExpressionFactory::<ListSplitExp>());
        self.register_api("hashtablesize", "hashtablesize(hash) api", CreateExpressionFactory::<HashtableSizeExp>());
        self.register_api("hashtable", "{k1=>v1,k2=>v2,...} or {k1:v1,k2:v2,...} or hashtable(k1=>v1,k2=>v2,...) or hashtable(k1:v1,k2:v2,...) object", CreateExpressionFactory::<HashtableExp>());
        self.register_api("hashtableget", "hashtableget(hash,key[,defval]) api", CreateExpressionFactory::<HashtableGetExp>());
        self.register_api("hashtableset", "hashtableset(hash,key,val) api", CreateExpressionFactory::<HashtableSetExp>());
        self.register_api("hashtableadd", "hashtableadd(hash,key,val) api", CreateExpressionFactory::<HashtableAddExp>());
        self.register_api("hashtableremove", "hashtableremove(hash,key) api", CreateExpressionFactory::<HashtableRemoveExp>());
        self.register_api("hashtableclear", "hashtableclear(hash) api", CreateExpressionFactory::<HashtableClearExp>());
        self.register_api("hashtablekeys", "hashtablekeys(hash) api", CreateExpressionFactory::<HashtableKeysExp>());
        self.register_api("hashtablevalues", "hashtablevalues(hash) api", CreateExpressionFactory::<HashtableValuesExp>());
        self.register_api("listhashtable", "listhashtable(hash) api, return list of pair", CreateExpressionFactory::<ListHashtableExp>());
        self.register_api("hashtablesplit", "hashtablesplit(hash,ct) api, return list of hashtable", CreateExpressionFactory::<HashtableSplitExp>());
        self.register_api("peek", "peek(queue_or_stack) api", CreateExpressionFactory::<PeekExp>());
        self.register_api("stacksize", "stacksize(stack) api", CreateExpressionFactory::<StackSizeExp>());
        self.register_api("stack", "stack(v1,v2,...) object", CreateExpressionFactory::<StackExp>());
        self.register_api("push", "push(stack,v) api", CreateExpressionFactory::<PushExp>());
        self.register_api("pop", "pop(stack) api", CreateExpressionFactory::<PopExp>());
        self.register_api("stackclear", "stackclear(stack) api", CreateExpressionFactory::<StackClearExp>());
        self.register_api("queuesize", "queuesize(queue) api", CreateExpressionFactory::<QueueSizeExp>());
        self.register_api("queue", "queue(v1,v2,...) object", CreateExpressionFactory::<QueueExp>());
        self.register_api("enqueue", "enqueue(queue,v) api", CreateExpressionFactory::<EnqueueExp>());
        self.register_api("dequeue", "dequeue(queue) api", CreateExpressionFactory::<DequeueExp>());
        self.register_api("queueclear", "queueclear(queue) api", CreateExpressionFactory::<QueueClearExp>());
        self.register_api("setenv", "setenv(k,v) api", CreateExpressionFactory::<SetEnvironmentExp>());
        self.register_api("getenv", "getenv(k) api", CreateExpressionFactory::<GetEnvironmentExp>());
        self.register_api("expand", "expand(str) api", CreateExpressionFactory::<ExpandEnvironmentsExp>());
        self.register_api("envs", "envs() api", CreateExpressionFactory::<EnvironmentsExp>());
        self.register_api("cd", "cd(path) api", CreateExpressionFactory::<SetCurrentDirectoryExp>());
        self.register_api("pwd", "pwd() api", CreateExpressionFactory::<GetCurrentDirectoryExp>());
        self.register_api("cmdline", "cmdline() api", CreateExpressionFactory::<CommandLineExp>());
        self.register_api("cmdlineargs", "cmdlineargs(prev_arg) or cmdlineargs() api, first return next arg, second return array of arg", CreateExpressionFactory::<CommandLineArgsExp>());
        self.register_api("os", "os() api", CreateExpressionFactory::<OsExp>());
        self.register_api("osplatform", "osplatform() api", CreateExpressionFactory::<OsPlatformExp>());
        self.register_api("osversion", "osversion() api", CreateExpressionFactory::<OsVersionExp>());
        self.register_api("getfullpath", "getfullpath(path) api", CreateExpressionFactory::<GetFullPathExp>());
        self.register_api("getpathroot", "getpathroot(path) api", CreateExpressionFactory::<GetPathRootExp>());
        self.register_api("getrandomfilename", "getrandomfilename() api", CreateExpressionFactory::<GetRandomFileNameExp>());
        self.register_api("gettempfilename", "gettempfilename() api", CreateExpressionFactory::<GetTempFileNameExp>());
        self.register_api("gettemppath", "gettemppath() api", CreateExpressionFactory::<GetTempPathExp>());
        self.register_api("hasextension", "hasextension(path) api", CreateExpressionFactory::<HasExtensionExp>());
        self.register_api("ispathrooted", "ispathrooted(path) api", CreateExpressionFactory::<IsPathRootedExp>());
        self.register_api("getfilename", "getfilename(path) api", CreateExpressionFactory::<GetFileNameExp>());
        self.register_api("getfilenamewithoutextension", "getfilenamewithoutextension(path) api", CreateExpressionFactory::<GetFileNameWithoutExtensionExp>());
        self.register_api("getextension", "getextension(path) api", CreateExpressionFactory::<GetExtensionExp>());
        self.register_api("getdirectoryname", "getdirectoryname(path) api", CreateExpressionFactory::<GetDirectoryNameExp>());
        self.register_api("combinepath", "combinepath(path1,path2) api", CreateExpressionFactory::<CombinePathExp>());
        self.register_api("changeextension", "changeextension(path,ext) api", CreateExpressionFactory::<ChangeExtensionExp>());
        self.register_api("quotepath", "quotepath(path[,only_needed,single_quote]) api", CreateExpressionFactory::<QuotePathExp>());
        self.register_api("debugbreak", "debugbreak() api", CreateExpressionFactory::<DebugBreakExp>());
        self.register_api("debuglog", "debuglog(fmt,arg1,arg2,...) api", CreateExpressionFactory::<DebugLogExp>());
        self.register_api("debugwarning", "debugwarning(fmt,arg1,arg2,...) api", CreateExpressionFactory::<DebugWarningExp>());
        self.register_api("debugerror", "debugerror(fmt,arg1,arg2,...) api", CreateExpressionFactory::<DebugErrorExp>());
        self.register_api("callstack", "callstack() api", CreateExpressionFactory::<CallStackExp>());
        self.register_api("call", "call(func_name,arg1,arg2,...) api", CreateExpressionFactory::<CallExp>());
        self.register_api("return", "return([val]) api", CreateExpressionFactory::<ReturnExp>());
        self.register_api("redirect", "redirect(arg1,arg2,...) api", CreateExpressionFactory::<RedirectExp>());

        self.register_api("direxist", "direxist(dir) api", CreateExpressionFactory::<DirectoryExistExp>());
        self.register_api("fileexist", "fileexist(file) api", CreateExpressionFactory::<FileExistExp>());
        self.register_api("listdirs", "listdirs(dir,filter_list_or_str_1,filter_list_or_str_2,...) api", CreateExpressionFactory::<ListDirectoriesExp>());
        self.register_api("listfiles", "listfiles(dir,filter_list_or_str_1,filter_list_or_str_2,...) api", CreateExpressionFactory::<ListFilesExp>());
        self.register_api("listalldirs", "listalldirs(dir,filter_list_or_str_1,filter_list_or_str_2,...) api", CreateExpressionFactory::<ListAllDirectoriesExp>());
        self.register_api("listallfiles", "listallfiles(dir,filter_list_or_str_1,filter_list_or_str_2,...) api", CreateExpressionFactory::<ListAllFilesExp>());
        self.register_api("createdir", "createdir(dir) api", CreateExpressionFactory::<CreateDirectoryExp>());
        self.register_api("copydir", "copydir(dir1,dir2,filter_list_or_str_1,filter_list_or_str_2,...) api, include subdir", CreateExpressionFactory::<CopyDirectoryExp>());
        self.register_api("movedir", "movedir(dir1,dir2) api", CreateExpressionFactory::<MoveDirectoryExp>());
        self.register_api("deletedir", "deletedir(dir) api", CreateExpressionFactory::<DeleteDirectoryExp>());
        self.register_api("copyfile", "copyfile(file1,file2) api", CreateExpressionFactory::<CopyFileExp>());
        self.register_api("copyfiles", "copyfiles(dir1,dir2,filter_list_or_str_1,filter_list_or_str_2,...) api, dont include subdir", CreateExpressionFactory::<CopyFilesExp>());
        self.register_api("movefile", "movefile(file1,file2) api", CreateExpressionFactory::<MoveFileExp>());
        self.register_api("deletefile", "deletefile(file) api", CreateExpressionFactory::<DeleteFileExp>());
        self.register_api("deletefiles", "deletefiles(dir,filter_list_or_str_1,filter_list_or_str_2,...) api, dont include subdir", CreateExpressionFactory::<DeleteFilesExp>());
        self.register_api("deleteallfiles", "deleteallfiles(dir,filter_list_or_str_1,filter_list_or_str_2,...) api, include subdir", CreateExpressionFactory::<DeleteAllFilesExp>());
        self.register_api("getfileinfo", "getfileinfo(file) api", CreateExpressionFactory::<GetFileInfoExp>());
        self.register_api("getdirinfo", "getdirinfo(dir) api", CreateExpressionFactory::<GetDirectoryInfoExp>());
        self.register_api("getdriveinfo", "getdriveinfo(drive) api", CreateExpressionFactory::<GetDriveInfoExp>());
        self.register_api("getdrivesinfo", "getdrivesinfo() api", CreateExpressionFactory::<GetDrivesInfoExp>());
        self.register_api("readalllines", "readalllines(file[,encoding]) api", CreateExpressionFactory::<ReadAllLinesExp>());
        self.register_api("writealllines", "writealllines(file,lines[,encoding]) api", CreateExpressionFactory::<WriteAllLinesExp>());
        self.register_api("readalltext", "readalltext(file[,encoding]) api", CreateExpressionFactory::<ReadAllTextExp>());
        self.register_api("writealltext", "writealltext(file,txt[,encoding]) api", CreateExpressionFactory::<WriteAllTextExp>());
        self.register_api("process", "process(file,arg_str) or process(file,arg_str){[options;]} api", CreateExpressionFactory::<CommandExp>());
        self.register_api("command", "command{win{:cmd_str:};unix{:cmd_str:};common{:cmd_str:};[options;]} api", CreateExpressionFactory::<CommandExp>());
        self.register_api("kill", "kill(name_or_pid) api", CreateExpressionFactory::<KillExp>());
        self.register_api("killme", "killme([exit_code]) api", CreateExpressionFactory::<KillMeExp>());
        self.register_api("pid", "pid() api", CreateExpressionFactory::<GetCurrentProcessIdExp>());
        self.register_api("plist", "plist([filter]) api, return list", CreateExpressionFactory::<ListProcessesExp>());
        self.register_api("wait", "wait(time) api", CreateExpressionFactory::<WaitExp>());
        self.register_api("waitall", "waitall([timeout]) api, wait all task to exit", CreateExpressionFactory::<WaitAllExp>());
        self.register_api("waitstartinterval", "waitstartinterval(time) or waitstartinterval() api, used in Task.Wait for process/command", CreateExpressionFactory::<WaitStartIntervalExp>());
        self.register_api("cleanupcompletedtasks", "cleanupcompletedtasks() api", CreateExpressionFactory::<CleanupCompletedTasksExp>());
        self.register_api("gettaskcount", "gettaskcount() api", CreateExpressionFactory::<GetTaskCountExp>());
        self.register_api("calcmd5", "calcmd5(file) api", CreateExpressionFactory::<CalcMd5Exp>());
        */
    }
    pub fn register_api(&mut self, name: &'a str, doc: &'a str, factory: ExpressionFactoryBox<'a>)
    {
        self.m_api_factories.remove(name);
        self.m_api_factories.insert(name, factory);

        self.m_api_docs.remove(name);
        self.m_api_docs.insert(name, doc);
    }
    pub fn api_docs(&self) -> &BTreeMap<&str, &str>
    {
        return &self.m_api_docs;
    }
    pub fn clear(&mut self)
    {
        self.m_funcs.clear();
        self.m_stack.clear();
        self.m_named_global_variable_indexes.clear();
        self.m_global_variables.clear();
    }
    pub fn clear_global_variables(&mut self)
    {
        self.m_named_global_variable_indexes.clear();
        self.m_global_variables.clear();
    }
    pub fn global_variable_names(&self) -> Keys<String, i32>
    {
        return self.m_named_global_variable_indexes.keys();
    }
    pub fn get_global_variable(&self, v: &str) -> Option<&DslCalculatorValue<'a>>
    {
        if let Some(callback) = &self.on_get_variable {
            if let Some(val) = callback(v) {
                return Some(val);
            }
        }
        if let Some(index) = self.m_named_global_variable_indexes.get(v) {
            if let Some(r) = self.get_global_varaible_by_index(*index) {
                return Some(r);
            }
        }
        return None;
    }
    pub fn set_global_variable(&mut self, v: &str, val: DslCalculatorValue<'a>) -> bool
    {
        if let Some(callback) = self.on_set_variable.as_deref_mut() {
            return callback(v, val);
        }
        else if let Some(index) = self.m_named_global_variable_indexes.get(v) {
            self.set_global_varaible_by_index(*index, val);
            return true;
        }
        else {
            let ix = self.m_named_global_variable_indexes.len();
            self.m_named_global_variable_indexes.insert(String::from(v), ix as i32);
            self.m_global_variables.push(val);
            return true;
        }
    }
    pub fn load_dsl_file(&mut self, dsl_file: &str)
    {
        if let Some(callback) = self.on_log {
            let mut file = DslFile::new();
            if file.load(dsl_file, callback) {
                for info in file.dsl_infos().iter() {
                    self.load_dsl_info(info);
                }
            }
        }
    }
    pub fn load_dsl_info(&mut self, info: &SyntaxComponent)
    {
        if info.get_id() != "script" {
            return;
        }
        let mut is_valid = false;
        let mut id: &str = "";
        let mut func: Option<&FunctionData> = None;
        let mut func_info: FuncInfo<'a> = FuncInfo::new();
        match info {
            SyntaxComponent::Function(f) => {
                if f.is_high_order() {
                    id = f.get_id();
                    func = Some(f);
                    is_valid = true;
                }
            }
            SyntaxComponent::Statement(statement) => {
                if statement.get_function_num() == 2 {
                    if let Some(vf) = statement.first() {
                        if let ValueOrFunction::Function(f) = vf {
                            id = f.get_param_id(0);
                        }
                    }
                    if let Some(vf) = statement.second() {
                        if let ValueOrFunction::Function(f) = vf {
                            func = Some(f);
                            is_valid = true;
                            if f.get_id() == "args" && f.is_high_order() {
                                if let Some(lf) = f.lower_order_function() {
                                    if let Some(ps) = lf.params() {
                                        for p in ps.iter() {
                                            let arg_name = p.get_id();
                                            func_info.add_arg_name_index(arg_name);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
            _ => {
                return;
            }
        };

        if !is_valid {
            return;
        }

        if let Some(f) = func {
            if let Some(ps) = f.params() {
                for comp in ps.iter() {
                    if let Some(exp) = self.load_syntax_component(comp) {
                        func_info.codes.push(exp);
                    }
                }
            }
        }
        self.m_funcs.remove(id);
        self.m_funcs.insert(String::from(id), RefCell::new(func_info));
    }
    pub fn load_dsl_func(&mut self, func: &str, dsl_func: &FunctionData)
    {
        self.load_dsl_func_with_args(func, None, dsl_func);
    }
    pub fn load_dsl_func_with_args(&mut self, func: &str, arg_names: Option<&'a Vec<String>>, dsl_func: &FunctionData)
    {
        let mut func_info = FuncInfo::new();
        if let Some(names) = arg_names {
            if names.len() > 0 {
                func_info.build_arg_name_indexes(names);
            }
        }
        if let Some(ps) = dsl_func.params() {
            self.load_dsl_statements(ps, &mut func_info.codes);
        }
        self.m_funcs.remove(func);
        self.m_funcs.insert(String::from(func), RefCell::new(func_info));
    }
    pub fn load_dsl_statements(&mut self, statements: &Vec<SyntaxComponent>, exps: &mut Vec<ExpressionBox<'a>>)
    {
        for comp in statements.iter() {
            if comp.is_valid() {
                if let Some(exp) = self.load_syntax_component(comp) {
                    exps.push(exp);
                }
            }
        }
    }
    pub fn check_func_xrefs(&self)
    {
        for func in self.m_func_calls.iter() {
            if self.m_funcs.contains_key(func.get_id()) {
                continue;
            }
            //error
            self.error(&format!("DslCalculator error, unknown func '{}', {} line {}", func.get_id(), func.to_script_string(false, &dsl::DEFAULT_DELIM), func.get_line()));
        }
    }
    pub fn new_calculator_value_list(&self) -> Vec<DslCalculatorValue<'a>>
    {
        return self.m_value_list_pool.borrow_mut().alloc();
    }
    pub fn recycle_calculator_value_list(&self, mut list: Vec<DslCalculatorValue<'a>>)
    {
        list.clear();
        self.m_value_list_pool.borrow_mut().recycle(list);
    }
    pub fn calc_0(&mut self, func: &'a str) -> DslCalculatorValue<'a>
    {
        let mut args = self.m_value_list_pool.borrow_mut().alloc();
        let r = self.calc_n(func, &mut args);
        args.clear();
        self.m_value_list_pool.borrow_mut().recycle(args);
        return r;
    }
    pub fn calc_1(&mut self, func: &'a str, arg1: DslCalculatorValue<'a>) -> DslCalculatorValue<'a>
    {
        let mut args = self.new_calculator_value_list();
        args.push(arg1);
        let r = self.calc_n(func, &mut args);
        self.recycle_calculator_value_list(args);
        return r;
    }
    pub fn calc_2(&mut self, func: &'a str, arg1: DslCalculatorValue<'a>, arg2: DslCalculatorValue<'a>) -> DslCalculatorValue<'a>
    {
        let mut args = self.new_calculator_value_list();
        args.push(arg1);
        args.push(arg2);
        let r = self.calc_n(func, &mut args);
        self.recycle_calculator_value_list(args);
        return r;
    }
    pub fn calc_3(&mut self, func: &'a str, arg1: DslCalculatorValue<'a>, arg2: DslCalculatorValue<'a>, arg3: DslCalculatorValue<'a>) -> DslCalculatorValue<'a>
    {
        let mut args = self.new_calculator_value_list();
        args.push(arg1);
        args.push(arg2);
        args.push(arg3);
        let r = self.calc_n(func, &mut args);
        self.recycle_calculator_value_list(args);
        return r;
    }
    pub fn calc_n(&mut self, func: &'a str, args: &mut Vec<DslCalculatorValue<'a>>) -> DslCalculatorValue<'a>
    {
        self.local_stack_push(func, Some(args));
        let mut ret = DslCalculatorValue::Null;
        if let Some(func_info) = self.m_funcs.get(func) {
            for exp in func_info.borrow_mut().codes.iter_mut() {
                ret = exp.calc();
                if self.m_run_state == RunStateEnum::Return {
                    self.m_run_state = RunStateEnum::Normal;
                    break;
                }
                else if self.m_run_state == RunStateEnum::Redirect {
                    break;
                }
            }
        }
        else {
            //error
            self.error(&format!("DslCalculator error, unknown func {}", func));
            return DslCalculatorValue::Null;
        }
        self.local_stack_pop();
        return ret;
    }
    pub fn calc_in_current_context(&mut self, func: &str) -> DslCalculatorValue<'a>
    {
        let mut ret = DslCalculatorValue::Null;
        if let Some(func_info) = self.m_funcs.get(func) {
            for exp in func_info.borrow_mut().codes.iter_mut() {
                ret = exp.calc();
                if self.m_run_state == RunStateEnum::Return {
                    self.m_run_state = RunStateEnum::Normal;
                    break;
                }
                else if self.m_run_state == RunStateEnum::Redirect {
                    break;
                }
            }
        }
        return ret;
    }
    pub fn run_state(&self) -> &RunStateEnum
    {
        return &self.m_run_state;
    }
    pub fn set_run_state(&mut self, value: RunStateEnum)
    {
        self.m_run_state = value;
    }
    pub fn error(&self, info: &str)
    {
        if let Some(onlog) = self.on_log {
            onlog(info);
        }
    }
    pub fn arguments(&self) -> Option<&Vec<DslCalculatorValue<'a>>>
    {
        if let Some(stack_info) = self.m_stack.back() {
            return Some(&stack_info.args);
        }
        return None;
    }
    pub fn arguments_mut(&mut self) -> Option<&mut Vec<DslCalculatorValue<'a>>>
    {
        if let Some(stack_info) = self.m_stack.back_mut() {
            return Some(&mut stack_info.args);
        }
        return None;
    }
    pub fn get_variable(&self, v: &str) -> Option<&DslCalculatorValue<'a>>
    {
        let mut result = None;
        if let Some(c) = v.chars().next() {
            if c == '@' {
                result = self.get_global_variable(v);
            }
            else if c == '$' {
                result = self.get_local_variable(v);
            }
            else {
                result = self.get_global_variable(v);
            }
        }
        return result;
    }
    pub fn set_variable(&mut self, v: &str, val: DslCalculatorValue<'a>)
    {
        if let Some(c) = v.chars().next() {
            if c == '@' {
                self.set_global_variable(v, val);
            }
            else if c == '$' {
                self.set_local_variable(v, val);
            }
            else {
                self.set_global_variable(v, val);
            }
        }
    }
    pub fn load_syntax_component(&mut self, comp: &SyntaxComponent) -> Option<ExpressionBox<'a>>
    {
        match comp {
            SyntaxComponent::Value(value_data) => {
                let id_type = value_data.get_id_type();
                if id_type == dsl::ID_TOKEN {
                    let id = value_data.get_id();
                    if let Some(mut p) = self.create_api(id) {
                        //Convert a parameterless name into a parameterless function call.
                        let mut fd = FunctionData::new();
                        if let Some(name) = fd.name_mut() {
                            name.copy_from(value_data);
                        }
                        fd.set_parenthesis_param_class();
                        if let Some(cell) = self.m_self_cell {
                            if !p.load(&SyntaxComponent::Function(fd), cell) {
                                //error
                                self.error(&format!("DslCalculator error, {0} line {1}", comp.to_script_string(false, &dsl::DEFAULT_DELIM), comp.get_line()));
                            }
                        }
                        return Some(p);
                    }
                    else if id == "true" || id == "false" {
                        let mut const_exp = ConstGet::<'a>::default();
                        if let Some(cell) = self.m_self_cell {
                            AbstractExpression::load(&mut const_exp, comp, cell);
                        }
                        return Some(Box::new(const_exp));
                    }
                    else if id.len() > 0 && id.chars().next() == Some('$') {
                        let mut var_exp = LocalVarGet::default();
                        if let Some(cell) = self.m_self_cell {
                            AbstractExpression::load(&mut var_exp, comp, cell);
                        }
                        return Some(Box::new(var_exp));
                    }
                    else {
                        let mut var_exp = GlobalVarGet::default();
                        if let Some(cell) = self.m_self_cell {
                            AbstractExpression::load(&mut var_exp, comp, cell);
                        }
                        return Some(Box::new(var_exp));
                    }
                }
                else {
                    let mut const_exp = ConstGet::default();
                    if let Some(cell) = self.m_self_cell {
                        AbstractExpression::load(&mut const_exp, comp, cell);
                    }
                    return Some(Box::new(const_exp));
                }
            }
            SyntaxComponent::Function(func_data) => {
                if func_data.have_param() {
                    if !func_data.have_id() && !func_data.is_high_order() && (func_data.get_param_class() == dsl::PARAM_CLASS_PARENTHESIS || func_data.get_param_class() == dsl::PARAM_CLASS_BRACKET) {
                        match func_data.get_param_class() {
                            dsl::PARAM_CLASS_PARENTHESIS => {
                                let num = func_data.get_param_num();
                                if num == 1 {
                                    if let Some(param) = func_data.get_param(0) {
                                        return self.load_syntax_component(param);
                                    }
                                    else {
                                        return None;
                                    }
                                }
                                else {
                                    let mut exp = ParenthesisExp::default();
                                    if let Some(cell) = self.m_self_cell {
                                        AbstractExpression::load(&mut exp, comp, cell);
                                    }
                                    return Some(Box::new(exp));
                                }
                            }
                            dsl::PARAM_CLASS_BRACKET => {
                                    let mut exp = ArrayExp::default();
                                    if let Some(cell) = self.m_self_cell {
                                        AbstractExpression::load(&mut exp, comp, cell);
                                    }
                                    return Some(Box::new(exp));
                                }
                            _ => {
                                return None;
                            }
                        }
                    }
                    else if !func_data.have_param() {
                        //degeneration
                        if let Some(value_data) = func_data.name() {
                            return self.load_syntax_component(&SyntaxComponent::Value(value_data.as_ref().clone()));
                        }
                        return None;
                    }
                    else {
                        let param_class = func_data.get_param_class();
                        let op = func_data.get_id();
                        if op == "=" {//assignment
                            if let Some(syn) = func_data.get_param(0) {
                                if let SyntaxComponent::Function(inner_call) = syn {
                                    //obj.property = val -> objectset(obj, property, val)
                                    let inner_param_class = inner_call.get_param_class();
                                    if inner_param_class == dsl::PARAM_CLASS_PERIOD ||
                                        inner_param_class == dsl::PARAM_CLASS_BRACKET {
                                        let mut new_call = FunctionData::new();
                                        if inner_param_class == dsl::PARAM_CLASS_PERIOD {
                                            new_call.set_name(Box::new(ValueData::from_string_type(String::from("objectset"), dsl::ID_TOKEN)));
                                        }
                                        else {
                                            new_call.set_name(Box::new(ValueData::from_string_type(String::from("collectionset"), dsl::ID_TOKEN)));
                                        }
                                        new_call.set_parenthesis_param_class();
                                        if inner_call.is_high_order() {
                                            if let Some(f) = inner_call.lower_order_function() {
                                                new_call.add_function_param(f.as_ref().clone());
                                            }
                                            if let Some(param) = inner_call.get_param(0) {
                                                new_call.add_syntax_component_param(self.convert_member(param.clone(), inner_call.get_param_class()));
                                            }
                                            if let Some(param) = inner_call.get_param(1) {
                                                new_call.add_syntax_component_param(param.clone());
                                            }
                                        }
                                        else {
                                            if let Some(v) = inner_call.name() {
                                                new_call.add_value_param(v.as_ref().clone());
                                            }
                                            if let Some(param) = inner_call.get_param(0) {
                                                new_call.add_syntax_component_param(self.convert_member(param.clone(), inner_call.get_param_class()));
                                            }
                                            if let Some(param) = inner_call.get_param(1) {
                                                new_call.add_syntax_component_param(param.clone());
                                            }
                                        }

                                        return self.load_syntax_component(&SyntaxComponent::Function(new_call));
                                    }
                                }
                            }
                            let name = func_data.get_param_id(0);
                            if let Some(cell) = self.m_self_cell {
                                if name.len() > 0 && name.chars().next() == Some('$') {
                                    let mut exp = LocalVarSet::default();
                                    AbstractExpression::load(&mut exp, comp, cell);
                                    return Some(Box::new(exp));
                                }
                                else {
                                    let mut exp = GlobalVarSet::default();
                                    AbstractExpression::load(&mut exp, comp, cell);
                                    return Some(Box::new(exp));
                                }
                            }
                            //error
                            self.error(&format!("DslCalculator error, {0} line {1}", func_data.to_script_string(false, &dsl::DEFAULT_DELIM), func_data.get_line()));
                            return None;
                        }
                        else {
                            if func_data.is_high_order() {
                                if let Some(inner_call) = func_data.lower_order_function() {
                                    let inner_param_class = inner_call.get_param_class();
                                    if param_class == dsl::PARAM_CLASS_PARENTHESIS && (inner_param_class == dsl::PARAM_CLASS_PERIOD || inner_param_class == dsl::PARAM_CLASS_BRACKET) {
                                        //obj.member(a,b,...) or obj[member](a,b,...) or obj.(member)(a,b,...) or obj.[member](a,b,...) or obj.{member}(a,b,...) -> objectcall(obj,member,a,b,...)
                                        let api_name;
                                        let member = inner_call.get_param_id(0);
                                        if member == "orderby" || member == "orderbydesc" || member == "where" || member == "top" {
                                            api_name = "linq";
                                        }
                                        else if inner_param_class == dsl::PARAM_CLASS_PERIOD {
                                            api_name = "objectcall";
                                        }
                                        else {
                                            api_name = "collectioncall";
                                        }
                                        let mut new_call = FunctionData::new();
                                        new_call.set_name(Box::new(ValueData::from_string_type(String::from(api_name), dsl::ID_TOKEN)));
                                        new_call.set_parenthesis_param_class();
                                        if inner_call.is_high_order() {
                                            if let Some(f) = inner_call.lower_order_function() {
                                                new_call.add_function_param(f.as_ref().clone());
                                            }
                                            if let Some(param) = inner_call.get_param(0) {
                                                new_call.add_syntax_component_param(self.convert_member(param.clone(), inner_call.get_param_class()));
                                            }
                                            if let Some(ps) = func_data.params() {
                                                for p in ps.iter() {
                                                    new_call.add_syntax_component_param(p.clone());
                                                }
                                            }
                                        }
                                        else {
                                            if let Some(v) = inner_call.name() {
                                                new_call.add_value_param(v.as_ref().clone());
                                            }
                                            if let Some(param) = inner_call.get_param(0) {
                                                new_call.add_syntax_component_param(self.convert_member(param.clone(), inner_call.get_param_class()));
                                            }
                                            if let Some(ps) = func_data.params() {
                                                for p in ps.iter() {
                                                    new_call.add_syntax_component_param(p.clone());
                                                }
                                            }
                                        }

                                        return self.load_syntax_component(&SyntaxComponent::Function(new_call));
                                    }
                                }
                            }
                            if param_class == dsl::PARAM_CLASS_PERIOD || param_class == dsl::PARAM_CLASS_BRACKET {
                                //obj.property or obj[property] or obj.(property) or obj.[property] or obj.{property} -> objectget(obj,property)
                                let mut new_call = FunctionData::new();
                                if param_class == dsl::PARAM_CLASS_PERIOD {
                                    new_call.set_name(Box::new(ValueData::from_string_type(String::from("objectget"), dsl::ID_TOKEN)));
                                }
                                else {
                                    new_call.set_name(Box::new(ValueData::from_string_type(String::from("collectionget"), dsl::ID_TOKEN)));
                                }
                                new_call.set_parenthesis_param_class();
                                if func_data.is_high_order() {
                                    if let Some(f) = func_data.lower_order_function() {
                                        new_call.add_function_param(f.as_ref().clone());
                                    }
                                    if let Some(param) = func_data.get_param(0) {
                                        new_call.add_syntax_component_param(self.convert_member(param.clone(), func_data.get_param_class()));
                                    }
                                }
                                else {
                                    if let Some(v) = func_data.name() {
                                        new_call.add_value_param(v.as_ref().clone());
                                    }
                                    if let Some(param) = func_data.get_param(0) {
                                        new_call.add_syntax_component_param(self.convert_member(param.clone(), func_data.get_param_class()));
                                    }
                                }

                                return self.load_syntax_component(&SyntaxComponent::Function(new_call));
                            }
                        }
                    }
                }
                else {
                    if func_data.have_statement() {
                        if !func_data.have_id() && !func_data.is_high_order() {
                            let mut exp = HashtableExp::default();
                            if let Some(cell) = self.m_self_cell {
                                AbstractExpression::load(&mut exp, comp, cell);
                            }
                            return Some(Box::new(exp));
                        }
                    }
                    else if !func_data.have_extern_script() {
                        //degeneration
                        if let Some(value_data) = func_data.name() {
                            return self.load_syntax_component(&SyntaxComponent::Value(value_data.as_ref().clone()));
                        }
                    }
                }
            }
            SyntaxComponent::Statement(_statement_data) => {
            }
        }

        if let Some(mut ret) = self.create_api(comp.get_id()) {
            if let SyntaxComponent::Statement(st_data) = comp {
                //Convert command line syntax into function call syntax.
                if let Some(fd) = DslSyntaxTransformer::try_transform_command_line_like_syntax(st_data) {
                    if let Some(cell) = self.m_self_cell {
                        if ret.load(&SyntaxComponent::Function(fd), cell) {
                            return Some(ret);
                        }
                    }
                }
            }
            if let Some(cell) = self.m_self_cell {
                if ret.load(comp, cell) {
                    return Some(ret);
                }
            }
            //error
            self.error(&format!("DslCalculator error, {0} line {1}", comp.to_script_string(false, &dsl::DEFAULT_DELIM), comp.get_line()));
            return None;
        }
        // We enable the function to be called before it is defined, so failover is done first
        if let Some(on_load_failback) = self.on_load_failback {
            if let Some(exp) = on_load_failback(comp, self) {
                return Some(exp);
            }
        }
        if let SyntaxComponent::Function(func_data) = comp {
            if !func_data.is_high_order() {
                let fc: Box<FunctionCall<'a>> = Box::new(FunctionCall::<'a>::default());
                self.m_func_calls.push(func_data.clone());
                return Some(fc);
            }
            else {
                //error
                self.error(&format!("DslCalculator error, {0} line {1}", comp.to_script_string(false, &dsl::DEFAULT_DELIM), comp.get_line()));
            }
        }
        return None;
    }
    fn alloc_global_variable_index(&mut self, name: &str) -> i32
    {
        if let Some(callback) = self.on_get_variable {
            if let Some(val) = callback(name) {
                if let DslCalculatorValue::Int(i) = val {
                    return *i;
                }
            }
        }
        let mut ix = std::i32::MAX;
        if self.m_named_global_variable_indexes.get(name).is_none() {
            ix = self.m_named_global_variable_indexes.len() as i32;
            self.m_named_global_variable_indexes.insert(String::from(name), ix);
            self.m_global_variables.push(DslCalculatorValue::Null);
        }
        return ix;
    }
    fn alloc_local_variable_index(&mut self, name: &str) -> i32
    {
        let mut ix = std::i32::MAX;
        if let Some(func_info) = self.func_info() {
            if func_info.borrow().local_var_indexes.get(name).is_none() {
                ix = func_info.borrow().local_var_indexes.len() as i32;
                func_info.borrow_mut().local_var_indexes.insert(String::from(name), ix);
                if let Some(vars) = self.local_variables_mut() {
                    vars.push(DslCalculatorValue::Null);
                }
            }
        }
        return ix;
    }
    fn get_global_variable_index(&self, name: &str) -> i32
    {
        let mut ix = std::i32::MAX;
        if let Some(i) = self.m_named_global_variable_indexes.get(name) {
            ix = *i;
        }
        return ix;
    }
    fn get_local_variable_index(&self, name: &str) -> i32
    {
        let mut ix = std::i32::MAX;
        if let Some(func_info) = self.func_info() {
            if let Some(i) = func_info.borrow().local_var_indexes.get(name) {
                ix = *i;
            }
        }
        return ix;
    }
    fn get_global_varaible_by_index(&self, ix: i32) -> Option<&DslCalculatorValue<'a>>
    {
        if ix >= 0 && (ix as usize) < self.m_global_variables.len() {
            return Some(&self.m_global_variables[ix as usize]);
        }
        return None;
    }
    fn get_local_varaible_by_index(&self, ix: i32) -> Option<&DslCalculatorValue<'a>>
    {
        if ix >= 0 {
            if let Some(vars) = self.local_variables() {
                if (ix as usize) < vars.len() {
                    return Some(&vars[ix as usize]);
                }
            }
        }
        else if let Some(args) = self.arguments() {
            let arg_ix = -1 - ix;
            if arg_ix >= 0 && (arg_ix as usize) < args.len() {
                return Some(&args[arg_ix as usize]);
            }
        }
        return None;
    }
    fn set_global_varaible_by_index(&mut self, ix: i32, val: DslCalculatorValue<'a>)
    {
        if ix >= 0 && (ix as usize) < self.m_global_variables.len() {
            self.m_global_variables[ix as usize] = val;
        }
    }
    fn set_local_varaible_by_index(&mut self, ix: i32, val: DslCalculatorValue<'a>)
    {
        if ix >= 0 {
            if let Some(vars) = self.local_variables_mut() {
                if (ix as usize) < vars.len() {
                    vars[ix as usize] = val;
                }
            }
        }
        else if let Some(args) = self.arguments_mut() {
            let arg_ix: i32 = -1 - ix;
            if arg_ix >= 0 && (arg_ix as usize) < args.len() {
                args[arg_ix as usize] = val;
            }
        }
    }

    fn local_stack_push(&mut self, func: &'a str, args: Option<&mut Vec<DslCalculatorValue<'a>>>)
    {
        let mut si = self.alloc_stack_info();
        if let Some(mut vs) = args {
            si.args.append(&mut vs);
        }
        if !self.fill_func_info(&mut si, func) {
            self.recycle_stack_info(&mut si);
            return;
        }
        self.m_stack.push_back(si);
    }
    fn fill_func_info(&self, si: &mut StackInfo<'a>, func: &'a str) -> bool
    {
        if let Some(func_info) = self.m_funcs.get(func) {
            si.init(func, func_info);
            return true;
        }
        si.clear();
        return false;
    }
    fn local_stack_pop(&mut self)
    {
        if let Some(mut poped) = self.m_stack.pop_back() {
            poped.clear();
            self.recycle_stack_info(&mut poped);
        }
    }
    fn convert_member(&self, mut p: SyntaxComponent, param_class: i32) -> SyntaxComponent
    {
        if let SyntaxComponent::Value(pvd) = &mut p {
            if pvd.is_id() && (param_class == dsl::PARAM_CLASS_PERIOD
                || param_class == dsl::PARAM_CLASS_POINTER) {
                pvd.set_type(dsl::STRING_TOKEN);
                return SyntaxComponent::Value(pvd.clone());
            }
        }
        return p;
    }

    fn create_api(&self, name: &str) -> Option<ExpressionBox<'a>>
    {
        if let Some(factory) = self.m_api_factories.get(name) {
            return Some(factory());
        }
        return None;
    }

    fn get_local_variable(&self, v: &str) -> Option<&DslCalculatorValue<'a>>
    {
        if let Some(func_info) = self.func_info() {
            if let Some(index) = func_info.borrow().local_var_indexes.get(v) {
                if let Some(val) = self.get_local_varaible_by_index(*index) {
                    return Some(val);
                }
            }
        }
        return None;
    }
    fn set_local_variable(&mut self, v: &str, val: DslCalculatorValue<'a>)
    {
        let mut index = std::i32::MAX;
        if let Some(func_info) = self.func_info() {
            if let Some(ix) = func_info.borrow().local_var_indexes.get(v) {
                index = *ix;
            }
            else {
                let ix = func_info.borrow().local_var_indexes.len() as i32;
                func_info.borrow_mut().local_var_indexes.insert(String::from(v), ix);
            }
        }
        else {
            return;
        }
        if index == std::i32::MAX {
            if let Some(vars) = self.local_variables_mut() {
                vars.push(val);
            }
        }
        else {
            self.set_local_varaible_by_index(index, val);
        }
    }
    fn func_info(&self) -> Option<&FuncInfoCell<'a>>
    {
        if let Some(stack_info) = self.m_stack.back() {
            if let Some(func_info) = self.m_funcs.get(stack_info.func_name) {
                return Some(&func_info);
            }
        }
        return None;
    }
    fn local_variables(&self) -> Option<&Vec<DslCalculatorValue<'a>>>
    {
        if let Some(stack_info) = self.m_stack.back() {
            return Some(&stack_info.local_vars);
        }
        return None;
    }
    fn local_variables_mut(&mut self) -> Option<&mut Vec<DslCalculatorValue<'a>>>
    {
        if let Some(stack_info) = self.m_stack.back_mut() {
            return Some(&mut stack_info.local_vars);
        }
        return None;
    }

    pub fn alloc_stack_info(&mut self) -> StackInfo<'a>
    {
        return self.m_stack_info_pool.borrow_mut().alloc();
    }
    pub fn recycle_stack_info(&mut self, stack_info: &mut StackInfo<'a>)
    {
        let si = std::mem::take(stack_info);
        self.m_stack_info_pool.borrow_mut().recycle(si);
    }

    pub fn new_cell() -> DslCalculatorCell<'a>
    {
        let cell = RefCell::new(Self::new());
        return cell;
    }
    fn new() -> Self {
        Self {
            on_log: None,
            on_get_variable: None,
            on_set_variable: None,
            on_load_failback: None,

            m_inited: false,
            m_run_state: RunStateEnum::Normal,
            m_funcs: HashMap::new(),
            m_stack: VecDeque::new(),
            m_named_global_variable_indexes: HashMap::new(),
            m_global_variables: Vec::new(),
            m_api_factories: HashMap::new(),
            m_api_docs: BTreeMap::new(),
            m_func_calls: Vec::new(),
            m_value_list_pool: RefCell::new(SimpleObjectPool::new_with_size(32)),
            m_stack_info_pool: RefCell::new(SimpleObjectPool::new_with_size(32)),
            m_self_cell: None,
        }
    }
}
pub struct DslSyntaxTransformer;
impl DslSyntaxTransformer
{
    pub fn try_transform_command_line_like_syntax(statement_data: &StatementData) -> Option<FunctionData>
    {
        if let Some(first) = statement_data.first() {
            if let ValueOrFunction::Value(v) = first {
                if v.have_id() {
                    //Convert command line style to function style
                    let mut func = FunctionData::new();
                    func.set_name(Box::new(v.clone()));
                    func.set_param_class(dsl::PARAM_CLASS_PARENTHESIS);
                    if let Some(fs) = statement_data.functions() {
                        for f in fs.iter() {
                            match f {
                                ValueOrFunction::Value(vd) => {
                                    func.add_value_param(vd.clone());
                                }
                                ValueOrFunction::Function(fd) => {
                                    func.add_function_param(fd.clone());
                                }
                            }
                        }
                    }
                    return Some(func);
                }
            }
        }
        return None;
    }
}
pub struct SimpleObjectPool<T>
{
    m_unused_objects: VecDeque<T>,
    m_pool_size: usize,
}
impl<T> SimpleObjectPool<T> where T : Default
{
    pub fn init(&mut self, init_pool_size: usize)
    {
        for _i in [0..init_pool_size] {
            let t = T::default();
            self.recycle(t);
        }
    }
    pub fn alloc(&mut self) -> T
    {
        if self.m_unused_objects.len() > 0 {
            if let Some(t) = self.m_unused_objects.pop_front() {
                return t;
            }
        }
        let t = T::default();
        return t;
    }
    pub fn recycle(&mut self, t: T)
    {
        if self.m_unused_objects.len() < self.m_pool_size {
            self.m_unused_objects.push_back(t);
        }
    }
    pub fn clear(&mut self)
    {
        self.m_unused_objects.clear();
    }
    pub fn count(&self) -> usize
    {
        return self.m_unused_objects.len();
    }

    pub fn new() -> Self
    {
        Self {
            m_unused_objects: VecDeque::new(),
            m_pool_size: 4096,
        }
    }
    pub fn new_with_size(init_pool_size: usize) -> Self
    {
        let mut obj = Self::new();
        obj.init(init_pool_size);
        return obj;
    }
}
