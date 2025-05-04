use std::cell::RefCell;
use crate::dsl::DslLogDelegationBox;

pub type DslLogCell<'a> = RefCell<DslLog<'a>>;
pub struct DslLog<'a>
{
    m_on_log: Option<&'a DslLogDelegationBox<'a>>,
    m_has_error: bool,
}

impl<'a> DslLog<'a>
{
    pub fn new(on_log: &'a DslLogDelegationBox<'a>) -> Self
    {
        Self {
            m_on_log: Some(on_log),
            m_has_error: false,
        }
    }

    pub fn has_error(&self) -> bool
    {
        return self.m_has_error;
    }

    pub fn info(&self, info: &str)
    {
        if let Some(on_log) = &self.m_on_log {
            on_log(info);
        }
    }
    pub fn error(&mut self, info: &str)
    {
        self.m_has_error = true;
        if let Some(on_log) = &self.m_on_log {
            on_log(info);
        }
    }
}
