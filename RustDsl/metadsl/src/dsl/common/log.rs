use std::cell::RefCell;
use crate::dsl::DslLogDelegationBox;

pub type DslLogCell = RefCell<DslLog>;
pub struct DslLog
{
    m_on_log: Option<DslLogDelegationBox>,
    m_has_error: bool,
}

impl DslLog
{
    pub fn new(on_log: DslLogDelegationBox) -> Self
    {
        DslLog {
            m_on_log: Some(on_log),
            m_has_error: false,
        }
    }

    pub fn has_error(&self) -> bool
    {
        return self.m_has_error;
    }

    pub fn info(&self, info: &String)
    {
        if let Some(on_log) = &self.m_on_log {
            on_log(info);
        }
    }
    pub fn error(&mut self, info: &String)
    {
        self.m_has_error = true;
        if let Some(on_log) = &self.m_on_log {
            on_log(info);
        }
    }
}
