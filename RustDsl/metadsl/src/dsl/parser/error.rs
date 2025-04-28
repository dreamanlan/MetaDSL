use std::cell::RefCell;
use crate::dsl::common::log::DslLogCell;
use crate::dsl::parser::token::DslTokenCell;
use crate::dsl::parser::string::{get_symbol_name, get_production_name};

pub type DslErrorCell<'a> = RefCell<DslError<'a>>;
pub struct DslError<'a>
{
    m_log: &'a DslLogCell
}

impl<'a> DslError<'a>
{
    pub fn new(log: &'a DslLogCell) -> Self
    {
        Self {
            m_log: log
        }
    }

    pub fn mismatch(&self, terminal: i16, token: i16, dsl_token: &DslTokenCell) -> i16
    {
        self.m_log.borrow_mut().error(&format!("[error] expecting {} but found {}, last token {} line {}, cur token {} line {}", get_symbol_name(terminal), get_symbol_name(token), dsl_token.borrow().get_last_token(), dsl_token.borrow().get_last_line_number(), *dsl_token.borrow().get_cur_token(), dsl_token.borrow().get_line_number()));
        return token;
    }

    pub fn no_entry(&self, production_number: i16, nonterminal: i16, token: i16,_levell: i32, dsl_token: &DslTokenCell) -> i16
    {
        self.m_log.borrow_mut().error(&format!("[error] syntax error: skipping input {}, last token {} line {}, cur token {} line {} [production: {} nonterminal: {} ]", get_symbol_name(token), dsl_token.borrow().get_last_token(), dsl_token.borrow().get_last_line_number(), dsl_token.borrow().get_cur_token(), dsl_token.borrow().get_line_number(), get_production_name(production_number), get_symbol_name(nonterminal)));
        let new_token = dsl_token.borrow_mut().get(); // advance the input
        return new_token;
    }

    pub fn input_left(&self, dsl_token: &DslTokenCell)
    {
        self.m_log.borrow_mut().error(&format!("[error] input left, last token {} line {}, cur token {} line {}", dsl_token.borrow().get_last_token(), dsl_token.borrow().get_last_line_number(), dsl_token.borrow().get_cur_token(), dsl_token.borrow().get_line_number()));
    }

    pub fn message(&self, message: &str, dsl_token: &DslTokenCell)
    {
        self.m_log.borrow_mut().error(&format!("[info] {}, last token {} line {}, cur token {} line {}", message, dsl_token.borrow().get_last_token(), dsl_token.borrow().get_last_line_number(), dsl_token.borrow().get_cur_token(), dsl_token.borrow().get_line_number()));
    }
}