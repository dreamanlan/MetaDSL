use std::cell::RefCell;
use std::collections::{
    HashMap, VecDeque
};
use std::rc::Rc;
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
struct ListSizeExp
{

}
impl<'a> Default for ListSizeExp<'a>
{
    fn default() -> Self
    {
        ListSizeExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListSizeExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListSizeExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListSizeExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::Array(arr) = opd0 {
                return DslCalculatorValue::Ulong(arr.borrow().len() as u64);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListGetExp
{

}
impl<'a> Default for ListGetExp<'a>
{
    fn default() -> Self
    {
        ListGetExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListGetExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListGetExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListGetExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let mut default = DslCalculatorValue::Null;
            if operands.len() >= 3 {
                default = operands[2].clone();
            }
            if let DslCalculatorValue::Array(arr) = opd0 {
                let ix = opd1.to_u64() as usize;
                if ix < arr.borrow().len() {
                    return arr.borrow()[ix].clone();
                }
                else {
                    return default;
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListSetExp
{

}
impl<'a> Default for ListSetExp<'a>
{
    fn default() -> Self
    {
        ListSetExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListSetExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListSetExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListSetExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            if let DslCalculatorValue::Array(arr) = opd0 {
                let ix = opd1.to_u64() as usize;
                if ix < arr.borrow().len() {
                    arr.borrow_mut()[ix] = opd2.clone();
                    return DslCalculatorValue::Bool(true);
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListIndexOfExp
{

}
impl<'a> Default for ListIndexOfExp<'a>
{
    fn default() -> Self
    {
        ListIndexOfExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListIndexOfExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListIndexOfExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListIndexOfExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Array(arr) = opd0 {
                if let Some(ix) = arr.borrow().iter().position(|x| x == opd1) {
                    return DslCalculatorValue::Long(ix as i64);
                }
                else {
                    return DslCalculatorValue::Long(-1);
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListAddExp
{

}
impl<'a> Default for ListAddExp<'a>
{
    fn default() -> Self
    {
        ListAddExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListAddExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListAddExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListAddExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Array(arr) = opd0 {
                arr.borrow_mut().push(opd1.clone());
                return DslCalculatorValue::Bool(true);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListRemoveExp
{

}
impl<'a> Default for ListRemoveExp<'a>
{
    fn default() -> Self
    {
        ListRemoveExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListRemoveExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListRemoveExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListRemoveExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Array(arr) = opd0 {
                let ix_opt = arr.borrow().iter().position(|x| x == opd1);
                if let Some(ix) = ix_opt {
                    arr.borrow_mut().remove(ix);
                    return DslCalculatorValue::Bool(true);
                }
                else {
                    return DslCalculatorValue::Bool(false);
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListInsertExp
{

}
impl<'a> Default for ListInsertExp<'a>
{
    fn default() -> Self
    {
        ListInsertExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListInsertExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListInsertExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListInsertExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            if let DslCalculatorValue::Array(arr) = opd0 {
                let ix = opd1.to_u64() as usize;
                if ix < arr.borrow().len() {
                    arr.borrow_mut().insert(ix, opd2.clone());
                    return DslCalculatorValue::Bool(true);
                }
                else {
                    return DslCalculatorValue::Bool(false);
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListRemoveAtExp
{

}
impl<'a> Default for ListRemoveAtExp<'a>
{
    fn default() -> Self
    {
        ListRemoveAtExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListRemoveAtExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListRemoveAtExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListRemoveAtExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Array(arr) = opd0 {
                let ix = opd1.to_u64() as usize;
                if ix < arr.borrow().len() {
                    arr.borrow_mut().remove(ix);
                    return DslCalculatorValue::Bool(true);
                }
                else {
                    return DslCalculatorValue::Bool(false);
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListClearExp
{

}
impl<'a> Default for ListClearExp<'a>
{
    fn default() -> Self
    {
        ListClearExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListClearExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListClearExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListClearExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::Array(arr) = opd0 {
                arr.borrow_mut().clear();
                return DslCalculatorValue::Bool(true);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListSplitExp
{

}
impl<'a> Default for ListSplitExp<'a>
{
    fn default() -> Self
    {
        ListSplitExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListSplitExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListSplitExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListSplitExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Array(arr) = opd0 {
                let ct = opd1.to_u64() as usize;
                let list_of_list = arr.borrow().chunks(ct)
                    .map(|v| DslCalculatorValue::Array(Rc::new(RefCell::new(v.to_vec()))))
                    .collect::<Vec<DslCalculatorValue>>();
                return DslCalculatorValue::Array(Rc::new(RefCell::new(list_of_list)));
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}

#[add_abstract_and_simple_expression_fields]
struct HashtableSizeExp
{

}
impl<'a> Default for HashtableSizeExp<'a>
{
    fn default() -> Self
    {
        HashtableSizeExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableSizeExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableSizeExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for HashtableSizeExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                return DslCalculatorValue::Ulong(hash.borrow().len() as u64);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct HashtableGetExp
{

}
impl<'a> Default for HashtableGetExp<'a>
{
    fn default() -> Self
    {
        HashtableGetExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableGetExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableGetExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for HashtableGetExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let mut default = DslCalculatorValue::Null;
            if operands.len() >= 3 {
                default = operands[2].clone();
            }
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                if let Some(v) = hash.borrow().get(opd1) {
                    return v.clone();
                }
                else {
                    return default;
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct HashtableSetExp
{

}
impl<'a> Default for HashtableSetExp<'a>
{
    fn default() -> Self
    {
        HashtableSetExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableSetExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableSetExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for HashtableSetExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                if let Some(v) = hash.borrow_mut().get_mut(opd1) {
                    *v = opd2.clone();
                    return DslCalculatorValue::Bool(true);
                }
                else {
                    hash.borrow_mut().insert(opd1.clone(), opd2.clone());
                    return DslCalculatorValue::Bool(false);
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct HashtableAddExp
{

}
impl<'a> Default for HashtableAddExp<'a>
{
    fn default() -> Self
    {
        HashtableAddExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableAddExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableAddExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for HashtableAddExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 3 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            let opd2 = &operands[2];
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                if hash.borrow().contains_key(opd1) {
                    return DslCalculatorValue::Bool(false);
                }
                else {
                    hash.borrow_mut().insert(opd1.clone(), opd2.clone());
                    return DslCalculatorValue::Bool(true);
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct HashtableRemoveExp
{

}
impl<'a> Default for HashtableRemoveExp<'a>
{
    fn default() -> Self
    {
        HashtableRemoveExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableRemoveExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableRemoveExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for HashtableRemoveExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                let ret = hash.borrow_mut().remove(opd1).is_some();
                return DslCalculatorValue::Bool(ret);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct HashtableClearExp
{

}
impl<'a> Default for HashtableClearExp<'a>
{
    fn default() -> Self
    {
        HashtableClearExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableClearExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableClearExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for HashtableClearExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                hash.borrow_mut().clear();
                return DslCalculatorValue::Bool(true);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct HashtableKeysExp
{

}
impl<'a> Default for HashtableKeysExp<'a>
{
    fn default() -> Self
    {
        HashtableKeysExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableKeysExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableKeysExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for HashtableKeysExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                let keys = hash.borrow().keys()
                    .map(|x| x.clone())
                    .collect::<Vec<DslCalculatorValue>>();
                return DslCalculatorValue::Array(Rc::new(RefCell::new(keys)));
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct HashtableValuesExp
{

}
impl<'a> Default for HashtableValuesExp<'a>
{
    fn default() -> Self
    {
        HashtableValuesExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableValuesExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableValuesExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for HashtableValuesExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                let values = hash.borrow().values()
                    .map(|x| x.clone())
                    .collect::<Vec<DslCalculatorValue>>();
                return DslCalculatorValue::Array(Rc::new(RefCell::new(values)));
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct ListHashtableExp
{

}
impl<'a> Default for ListHashtableExp<'a>
{
    fn default() -> Self
    {
        ListHashtableExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for ListHashtableExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for ListHashtableExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for ListHashtableExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                let pairs = hash.borrow().iter()
                    .map(|(k, v)| DslCalculatorValue::Tuple2(Box::new((k.clone(), v.clone()))))
                    .collect::<Vec<DslCalculatorValue>>();
                return DslCalculatorValue::Array(Rc::new(RefCell::new(pairs)));
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct HashtableSplitExp
{

}
impl<'a> Default for HashtableSplitExp<'a>
{
    fn default() -> Self
    {
        HashtableSplitExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for HashtableSplitExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for HashtableSplitExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for HashtableSplitExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::HashMap(hash) = opd0 {
                let ct = opd1.to_u64() as usize;
                let list_of_hash = Self::split_hashmap(hash, ct);
                return DslCalculatorValue::Array(Rc::new(RefCell::new(list_of_hash)));
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
impl<'a> HashtableSplitExp<'a>
{
    fn split_hashmap(map: &Rc<RefCell<HashMap<DslCalculatorValue, DslCalculatorValue>>>, n: usize) -> Vec<DslCalculatorValue>
    {
        let mut result = Vec::new();
        let mut chunk = HashMap::new();
        let mut count = 0;

        for (k, v) in map.borrow().iter() {
            chunk.insert(k.clone(), v.clone());
            count += 1;
            if count == n {
                result.push(DslCalculatorValue::HashMap(Rc::new(RefCell::new(chunk))));
                chunk = HashMap::new();
                count = 0;
            }
        }
        if !chunk.is_empty() {
            result.push(DslCalculatorValue::HashMap(Rc::new(RefCell::new(chunk))));
        }
        return result;
    }
}

#[add_abstract_and_simple_expression_fields]
pub struct DequeExp<'a>
{
}
impl<'a> Default for DequeExp<'a>
{
    fn default() -> Self
    {
        DequeExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DequeExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DequeExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DequeExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        let mut r = VecDeque::new();
        for oper in operands.iter() {
            r.push_back(oper.clone());
        }
        return DslCalculatorValue::Deque(Rc::new(RefCell::new(r)));
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DequeSizeExp
{

}
impl<'a> Default for DequeSizeExp<'a>
{
    fn default() -> Self
    {
        DequeSizeExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DequeSizeExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DequeSizeExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DequeSizeExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::Deque(deque) = opd0 {
                return DslCalculatorValue::Ulong(deque.borrow().len() as u64);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DequeFrontExp
{

}
impl<'a> Default for DequeFrontExp<'a>
{
    fn default() -> Self
    {
        DequeFrontExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DequeFrontExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DequeFrontExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DequeFrontExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::Deque(deque) = opd0 {
                if let Some(v) = deque.borrow().front() {
                    return v.clone();
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DequeBackExp
{

}
impl<'a> Default for DequeBackExp<'a>
{
    fn default() -> Self
    {
        DequeBackExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DequeBackExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DequeBackExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DequeBackExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::Deque(deque) = opd0 {
                if let Some(v) = deque.borrow().back() {
                    return v.clone();
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DequePushBackExp
{

}
impl<'a> Default for DequePushBackExp<'a>
{
    fn default() -> Self
    {
        DequePushBackExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DequePushBackExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DequePushBackExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DequePushBackExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Deque(deque) = opd0 {
                deque.borrow_mut().push_back(opd1.clone());
                return DslCalculatorValue::Bool(true);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DequePopBackExp
{

}
impl<'a> Default for DequePopBackExp<'a>
{
    fn default() -> Self
    {
        DequePopBackExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DequePopBackExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DequePopBackExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DequePopBackExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::Deque(deque) = opd0 {
                if let Some(v) = deque.borrow_mut().pop_back() {
                    return v;
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DequePushFrontExp
{

}
impl<'a> Default for DequePushFrontExp<'a>
{
    fn default() -> Self
    {
        DequePushFrontExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DequePushFrontExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DequePushFrontExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DequePushFrontExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 2 {
            let opd0 = &operands[0];
            let opd1 = &operands[1];
            if let DslCalculatorValue::Deque(deque) = opd0 {
                deque.borrow_mut().push_front(opd1.clone());
                return DslCalculatorValue::Bool(true);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DequePopFrontExp
{

}
impl<'a> Default for DequePopFrontExp<'a>
{
    fn default() -> Self
    {
        DequePopFrontExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DequePopFrontExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DequePopFrontExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DequePopFrontExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::Deque(deque) = opd0 {
                if let Some(v) = deque.borrow_mut().pop_front() {
                    return v;
                }
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}
#[add_abstract_and_simple_expression_fields]
struct DequeClearExp
{

}
impl<'a> Default for DequeClearExp<'a>
{
    fn default() -> Self
    {
        DequeClearExp {
            m_exps: None,

            m_calculator: None,
            m_dsl: None,
        }
    }
}
impl<'a> IExpression<'a> for DequeClearExp<'a>
{
    impl_expression_with_abstract!();
}
impl<'a> AbstractExpression<'a> for DequeClearExp<'a>
{
    impl_abstract_expression!();
    impl_abstract_with_simple!();
}
impl<'a> SimpleExpressionBase<'a> for DequeClearExp<'a>
{
    fn on_calc(&mut self, operands: &Vec<DslCalculatorValue>) -> DslCalculatorValue
    {
        if operands.len() >= 1 {
            let opd0 = &operands[0];
            if let DslCalculatorValue::Deque(deque) = opd0 {
                deque.borrow_mut().clear();
                return DslCalculatorValue::Bool(true);
            }
        }
        return DslCalculatorValue::Null;
    }

    impl_simple_expression!();
}