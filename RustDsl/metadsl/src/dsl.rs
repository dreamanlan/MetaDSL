use std::cell::RefCell;
use std::boxed::Box;
use std::vec::Vec;
use std::collections::{BTreeMap, HashMap};
use std::fs;
use std::io::{Cursor, Write};
use regex::Regex;
use metadsl_macros::{add_abstract_syntax_component_fields, impl_abstract_syntax_component};
use cfg_if::cfg_if;

use crate::dsl::common::action::*;
use crate::dsl::parser::parser::*;
use crate::dsl::common::log::{DslLog, DslLogCell};
use crate::dsl::parser::error::{DslError, DslErrorCell};
use crate::dsl::parser::token::{DslToken, DslTokenCell};

pub mod common;
pub mod parser;

pub type DslLogDelegation = dyn Fn(&str);
pub type DslLogDelegationBox = Box<DslLogDelegation>;

pub type SyntaxComponentBox = Box<SyntaxComponent>;
pub type ValueDataBox = Box<ValueData>;
pub type FunctionDataBox = Box<FunctionData>;
pub type StatementDataBox = Box<StatementData>;
pub type DslFileBox<'a> = Box<DslFile<'a>>;
pub type SyntaxComponentCell = RefCell<SyntaxComponent>;
pub type ValueDataCell = RefCell<ValueData>;
pub type FunctionDataCell = RefCell<FunctionData>;
pub type StatementDataCell = RefCell<StatementData>;
pub type DslFileCell<'a> = RefCell<DslFile<'a>>;

const DSL_BINARY_CODE_BEGIN_STATEMENT: i32 = 1;
const DSL_BINARY_CODE_END_STATEMENT: i32 = 2;
//const DSL_BINARY_CODE_END_STATEMENT_WITH_COMMA: i32 = 3;
//const DSL_BINARY_CODE_END_STATEMENT_WITH_SEMI_COLON: i32 = 4;
const DSL_BINARY_CODE_BEGIN_FUNCTION: i32 = 5;
const DSL_BINARY_CODE_END_FUNCTION: i32 = 6;
//const DSL_BINARY_CODE_END_FUNCTION_WITH_COMMA: i32 = 7;
//const DSL_BINARY_CODE_END_FUNCTION_WITH_SEMI_COLON: i32 = 8;
const DSL_BINARY_CODE_BEGIN_VALUE: i32 = 9;
const DSL_BINARY_CODE_END_VALUE: i32 = 10;
//const DSL_BINARY_CODE_END_VALUE_WITH_COMMA: i32 = 11;
//const DSL_BINARY_CODE_END_VALUE_WITH_SEMI_COLON: i32 = 12;
const DSL_BINARY_CODE_VALUE_TYPE_BEGIN: i32 = 13;
const DSL_BINARY_CODE_VALUE_TYPE_END: i32 = DSL_BINARY_CODE_VALUE_TYPE_BEGIN + MAX_TYPE;
const DSL_BINARY_CODE_PARAM_OR_EXTERN_CLASS_BEGIN: i32 = DSL_BINARY_CODE_VALUE_TYPE_END + 1;

#[derive(Clone)]
pub struct SyntaxComponentCommentsInfo
{
    m_first_comments: Vec<String>,
    m_first_comment_on_new_line: bool,
    m_last_comments: Vec<String>,
    m_last_comment_on_new_line: bool
}

impl SyntaxComponentCommentsInfo
{
    fn new() -> Self
    {
        return SyntaxComponentCommentsInfo
        {
            m_first_comments: Vec::new(),
            m_first_comment_on_new_line: false,
            m_last_comments: Vec::new(),
            m_last_comment_on_new_line: false
        };
    }
}

pub const ID_TOKEN: i32 = 0;
pub const NUM_TOKEN: i32 = 1;
pub const STRING_TOKEN: i32 = 2;
pub const DOLLAR_STRING_TOKEN: i32 = 3;
pub const MAX_TYPE: i32 = 3;

pub const SEPARATOR_NOTHING: i32 = 0;
pub const SEPARATOR_COMMA: i32 = 1;
pub const SEPARATOR_SEMICOLON: i32 = 2;

pub const PARAM_CLASS_MIN: i32 = 0;
pub const PARAM_CLASS_NOTHING: i32 = PARAM_CLASS_MIN;
pub const PARAM_CLASS_PARENTHESIS: i32 = 1;
pub const PARAM_CLASS_BRACKET: i32 = 2;
pub const PARAM_CLASS_PERIOD: i32 = 3;
pub const PARAM_CLASS_POINTER: i32 = 4;
pub const PARAM_CLASS_STATEMENT: i32 = 5;
pub const PARAM_CLASS_EXTERN_SCRIPT: i32 = 6;
pub const PARAM_CLASS_PARENTHESIS_COLON: i32 = 7;
pub const PARAM_CLASS_BRACKET_COLON: i32 = 8;
pub const PARAM_CLASS_ANGLE_BRACKET_COLON: i32 = 9;
pub const PARAM_CLASS_PARENTHESIS_PERCENT: i32 = 10;
pub const PARAM_CLASS_BRACKET_PERCENT: i32 = 11;
pub const PARAM_CLASS_BRACE_PERCENT: i32 = 12;
pub const PARAM_CLASS_ANGLE_BRACKET_PERCENT: i32 = 13;
pub const PARAM_CLASS_COLON_COLON: i32 = 14;
pub const PARAM_CLASS_PERIOD_STAR: i32 = 15;
pub const PARAM_CLASS_POINTER_STAR: i32 = 16;
pub const PARAM_CLASS_OPERATOR: i32 = 17;
pub const PARAM_CLASS_TERNARY_OPERATOR: i32 = 18;
pub const PARAM_CLASS_QUESTION_NULLABLE_OPERATOR: i32 = 19;
pub const PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR: i32 = 20;
pub const PARAM_CLASS_MAX: i32 = 21;
pub const PARAM_CLASS_WRAP_INFIX_CALL_MASK: i32 = 0x20;
pub const PARAM_CLASS_UNMASK: i32 = 0x1F;

pub static EMPTY_STRING: String = String::new();
pub static mut NONE_MUT: Option<SyntaxComponentCommentsInfo> = None;

/// <summary>
/// A scripting data parsing tool based on function-style syntax. Can be used as a DSL meta-language.
/// </summary>
/// <remarks>
/// The current implementation of obfuscation requires that the script not contain the ` character.
/// In addition, the design of the encryption and decryption table in the test code requires that
/// the script not contain identifiers in the form of "_number_".
/// </remarks>
pub trait ISyntaxComponent
{
    fn is_valid(&self) -> bool
    {
        return self.impl_is_valid();
    }
    fn get_id(&self) -> &String
    {
        return self.impl_get_id();
    }
    fn get_id_type(&self) -> i32
    {
        return self.impl_get_id_type();
    }
    fn get_line(&self) -> i32
    {
        return self.impl_get_line();
    }
    fn to_script_string(&self, include_comment: bool) -> String
    {
        return self.impl_to_script_string(include_comment);
    }
    fn have_id(&self) -> bool
    {
        return self.impl_have_id();
    }

    fn set_seperator(&mut self, sep: i32)
    {
        self.impl_set_seperator(sep);
    }
    fn get_seperator(&self) -> i32
    {
        return self.impl_get_seperator();
    }
    fn get_sep_char(&self) -> char
    {
        return self.impl_get_sep_char();
    }

    fn set_empty_separator(&mut self)
    {
        self.impl_set_empty_separator();
    }
    fn set_comma_separator(&mut self)
    {
        self.impl_set_comma_separator();
    }
    fn set_semi_colon_separator(&mut self)
    {
        self.impl_set_semi_colon_separator();
    }
    fn is_empty_separator(&self) -> bool
    {
        return self.impl_is_empty_separator();
    }
    fn is_comma_separator(&self) -> bool
    {
        return self.impl_is_comma_separator();
    }
    fn is_semi_colon_separator(&self) -> bool
    {
        return self.impl_is_semi_colon_separator();
    }

    fn calc_first_comment(&self) -> String
    {
        if DslFile::dont_load_comments() {
            return String::new();
        }
        if let Some(cmts_info) = self.impl_get_comments_info() {
            return cmts_info.m_first_comments.join(&EMPTY_STRING);
        }
        else {
            return String::new();
        }
    }
    fn calc_last_comment(&self) -> String
    {
        if DslFile::dont_load_comments() {
            return String::new();
        }
        if let Some(cmts_info) = self.impl_get_comments_info() {
            return cmts_info.m_last_comments.join(&EMPTY_STRING);
        }
        else {
            return String::new();
        }
    }
    fn copy_comments(&mut self, other: &dyn ISyntaxComponent)
    {
        self.copy_first_comments(other);
        self.copy_last_comments(other);
    }
    fn copy_first_comments(&mut self, other: &dyn ISyntaxComponent)
    {
        if DslFile::dont_load_comments() {
            return;
        }
        if let Some(cmts) = other.first_comments() {
            if let Some(tcmts) = self.first_comments_mut() {
                for cmt in cmts {
                    tcmts.push(cmt.clone());
                }
            }
            self.set_first_comment_on_new_line(other.first_comment_on_new_line());
        }
    }
    fn copy_last_comments(&mut self, other: &dyn ISyntaxComponent)
    {
        if DslFile::dont_load_comments() {
            return;
        }
        if let Some(cmts) = other.last_comments() {
            if let Some(tcmts) = self.last_comments_mut() {
                for cmt in cmts {
                    tcmts.push(cmt.clone());
                }
            }
            self.set_last_comment_on_new_line(other.last_comment_on_new_line());
        }
    }

    fn first_comments(&self) -> Option<&Vec<String>>
    {
        if DslFile::dont_load_comments() {
            return None;
        }
        if let Some(cmts_info) = self.impl_get_comments_info() {
            return Some(&cmts_info.m_first_comments);
        }
        else {
            return None;
        }
    }
    fn first_comments_mut(&mut self) -> Option<&mut Vec<String>>
    {
        if DslFile::dont_load_comments() {
            return None;
        }
        if let Some(cmts_info) = self.impl_get_comments_info_mut() {
            return Some(&mut cmts_info.m_first_comments);
        }
        else {
            return None;
        }
    }
    fn first_comment_on_new_line(&self) -> bool
    {
        if DslFile::dont_load_comments() {
            return false;
        }
        if let Some(cmts_info) = self.impl_get_comments_info() {
            return cmts_info.m_first_comment_on_new_line;
        }
        else {
            return false;
        }
    }
    fn set_first_comment_on_new_line(&mut self, value: bool)
    {
        if DslFile::dont_load_comments() {
            return;
        }
        if let Some(cmts_info) = self.impl_get_comments_info_mut() {
            cmts_info.m_first_comment_on_new_line = value;
        }
    }
    fn last_comments(&self) -> Option<&Vec<String>>
    {
        if DslFile::dont_load_comments() {
            return None;
        }
        if let Some(cmts_info) = self.impl_get_comments_info() {
            return Some(&cmts_info.m_last_comments);
        }
        else {
            return None;
        }
    }
    fn last_comments_mut(&mut self) -> Option<&mut Vec<String>>
    {
        if DslFile::dont_load_comments() {
            return None;
        }
        if let Some(cmts_info) = self.impl_get_comments_info_mut() {
            return Some(&mut cmts_info.m_last_comments);
        }
        else {
            return None;
        }
    }
    fn last_comment_on_new_line(&self) -> bool
    {
        if DslFile::dont_load_comments() {
            return false;
        }
        if let Some(cmts_info) = self.impl_get_comments_info() {
            return cmts_info.m_last_comment_on_new_line;
        }
        else {
            return false;
        }
    }
    fn set_last_comment_on_new_line(&mut self, value: bool)
    {
        if DslFile::dont_load_comments() {
            return;
        }
        if let Some(cmts_info) = self.impl_get_comments_info_mut() {
            cmts_info.m_last_comment_on_new_line = value;
        }
    }

    fn impl_is_valid(&self) -> bool;
    fn impl_get_id(&self) -> &String;
    fn impl_get_id_type(&self) -> i32;
    fn impl_get_line(&self) -> i32;
    fn impl_to_script_string(&self, include_comment: bool) -> String;
    fn impl_have_id(&self) -> bool;

    fn impl_set_seperator(&mut self, sep: i32);
    fn impl_get_seperator(&self) -> i32;
    fn impl_get_sep_char(&self) -> char;

    fn impl_set_empty_separator(&mut self);
    fn impl_set_comma_separator(&mut self);
    fn impl_set_semi_colon_separator(&mut self);
    fn impl_is_empty_separator(&self) -> bool;
    fn impl_is_comma_separator(&self) -> bool;
    fn impl_is_semi_colon_separator(&self) -> bool;

    fn impl_get_comments_info(&self) -> &Option<SyntaxComponentCommentsInfo>;
    fn impl_get_comments_info_mut(&mut self) -> &mut Option<SyntaxComponentCommentsInfo>;
}

#[derive(Clone)]
pub enum SyntaxComponent
{
    Value(ValueData),
    Function(FunctionData),
    Statement(StatementData)
}
impl ISyntaxComponent for SyntaxComponent
{
    fn impl_is_valid(&self) -> bool
    {
        return match self {
            SyntaxComponent::Value(v) => v.impl_is_valid(),
            SyntaxComponent::Function(f) => f.impl_is_valid(),
            SyntaxComponent::Statement(s) => s.impl_is_valid(),
        };
    }
    fn impl_get_id(&self) -> &String
    {
        return match self {
            SyntaxComponent::Value(v) => v.impl_get_id(),
            SyntaxComponent::Function(f) => f.impl_get_id(),
            SyntaxComponent::Statement(s) => s.impl_get_id(),
        };
    }
    fn impl_get_id_type(&self) -> i32
    {
        return match self {
            SyntaxComponent::Value(v) => v.impl_get_id_type(),
            SyntaxComponent::Function(f) => f.impl_get_id_type(),
            SyntaxComponent::Statement(s) => s.impl_get_id_type(),
        };
    }
    fn impl_get_line(&self) -> i32
    {
        return match self {
            SyntaxComponent::Value(v) => v.impl_get_line(),
            SyntaxComponent::Function(f) => f.impl_get_line(),
            SyntaxComponent::Statement(s) => s.impl_get_line(),
        };
    }
    fn impl_to_script_string(&self, include_comment: bool) -> String {
        return match self {
            SyntaxComponent::Value(v) => v.impl_to_script_string(include_comment),
            SyntaxComponent::Function(f) => f.impl_to_script_string(include_comment),
            SyntaxComponent::Statement(s) => s.impl_to_script_string(include_comment),
        }
    }
    fn impl_have_id(&self) -> bool {
        return match self {
            SyntaxComponent::Value(v) => v.impl_have_id(),
            SyntaxComponent::Function(f) => f.impl_have_id(),
            SyntaxComponent::Statement(s) => s.impl_have_id(),
        }
    }
    fn impl_set_seperator(&mut self, sep: i32) {
        return match self {
            SyntaxComponent::Value(v) => v.impl_set_seperator(sep),
            SyntaxComponent::Function(f) => f.impl_set_seperator(sep),
            SyntaxComponent::Statement(s) => s.impl_set_seperator(sep),
        }
    }
    fn impl_get_seperator(&self) -> i32 {
        return match self {
            SyntaxComponent::Value(v) => v.impl_get_seperator(),
            SyntaxComponent::Function(f) => f.impl_get_seperator(),
            SyntaxComponent::Statement(s) => s.impl_get_seperator(),
        }
    }
    fn impl_get_sep_char(&self) -> char {
        return match self {
            SyntaxComponent::Value(v) => v.impl_get_sep_char(),
            SyntaxComponent::Function(f) => f.impl_get_sep_char(),
            SyntaxComponent::Statement(s) => s.impl_get_sep_char(),
        }
    }

    fn impl_set_empty_separator(&mut self) {
        return match self {
            SyntaxComponent::Value(v) => v.impl_set_empty_separator(),
            SyntaxComponent::Function(f) => f.impl_set_empty_separator(),
            SyntaxComponent::Statement(s) => s.impl_set_empty_separator(),
        }
    }
    fn impl_set_comma_separator(&mut self) {
        return match self {
            SyntaxComponent::Value(v) => v.impl_set_comma_separator(),
            SyntaxComponent::Function(f) => f.impl_set_comma_separator(),
            SyntaxComponent::Statement(s) => s.impl_set_comma_separator(),
        }
    }
    fn impl_set_semi_colon_separator(&mut self) {
        return match self {
            SyntaxComponent::Value(v) => v.impl_set_semi_colon_separator(),
            SyntaxComponent::Function(f) => f.impl_set_semi_colon_separator(),
            SyntaxComponent::Statement(s) => s.impl_set_semi_colon_separator(),
        }
    }
    fn impl_is_empty_separator(&self) -> bool {
        return match self {
            SyntaxComponent::Value(v) => v.impl_is_empty_separator(),
            SyntaxComponent::Function(f) => f.impl_is_empty_separator(),
            SyntaxComponent::Statement(s) => s.impl_is_empty_separator(),
        }
    }
    fn impl_is_comma_separator(&self) -> bool {
        return match self {
            SyntaxComponent::Value(v) => v.impl_is_comma_separator(),
            SyntaxComponent::Function(f) => f.impl_is_comma_separator(),
            SyntaxComponent::Statement(s) => s.impl_is_comma_separator(),
        }
    }
    fn impl_is_semi_colon_separator(&self) -> bool {
        return match self {
            SyntaxComponent::Value(v) => v.impl_is_semi_colon_separator(),
            SyntaxComponent::Function(f) => f.impl_is_semi_colon_separator(),
            SyntaxComponent::Statement(s) => s.impl_is_semi_colon_separator(),
        }
    }

    fn impl_get_comments_info(&self) -> &Option<SyntaxComponentCommentsInfo> {
        return match self {
            SyntaxComponent::Value(v) => v.impl_get_comments_info(),
            SyntaxComponent::Function(f) => f.impl_get_comments_info(),
            SyntaxComponent::Statement(s) => s.impl_get_comments_info(),
        }
    }
    fn impl_get_comments_info_mut(&mut self) -> &mut Option<SyntaxComponentCommentsInfo> {
        return match self {
            SyntaxComponent::Value(v) => v.impl_get_comments_info_mut(),
            SyntaxComponent ::Function(f) => f.impl_get_comments_info_mut(),
            SyntaxComponent::Statement(s) => s.impl_get_comments_info_mut(),
        }
    }
}

#[derive(Clone)]
pub enum ValueOrFunction
{
    Value(ValueData),
    Function(FunctionData)
}
impl ISyntaxComponent for ValueOrFunction
{
    fn impl_is_valid(&self) -> bool
    {
        return match self {
            ValueOrFunction::Value(v) => v.impl_is_valid(),
            ValueOrFunction::Function(f) => f.impl_is_valid(),
        };
    }
    fn impl_get_id(&self) -> &String
    {
        return match self {
            ValueOrFunction::Value(v) => v.impl_get_id(),
            ValueOrFunction::Function(f) => f.impl_get_id(),
        };
    }
    fn impl_get_id_type(&self) -> i32
    {
        return match self {
            ValueOrFunction::Value(v) => v.impl_get_id_type(),
            ValueOrFunction::Function(f) => f.impl_get_id_type(),
        };
    }
    fn impl_get_line(&self) -> i32
    {
        return match self {
            ValueOrFunction::Value(v) => v.impl_get_line(),
            ValueOrFunction::Function(f) => f.impl_get_line(),
        };
    }
    fn impl_to_script_string(&self, include_comment: bool) -> String {
        return match self {
            ValueOrFunction::Value(v) => v.impl_to_script_string(include_comment),
            ValueOrFunction::Function(f) => f.impl_to_script_string(include_comment),
        }
    }
    fn impl_have_id(&self) -> bool {
        return match self {
            ValueOrFunction::Value(v) => v.impl_have_id(),
            ValueOrFunction::Function(f) => f.impl_have_id(),
        }
    }
    fn impl_set_seperator(&mut self, sep: i32) {
        return match self {
            ValueOrFunction::Value(v) => v.impl_set_seperator(sep),
            ValueOrFunction::Function(f) => f.impl_set_seperator(sep),
        }
    }
    fn impl_get_seperator(&self) -> i32 {
        return match self {
            ValueOrFunction::Value(v) => v.impl_get_seperator(),
            ValueOrFunction::Function(f) => f.impl_get_seperator(),
        }
    }
    fn impl_get_sep_char(&self) -> char {
        return match self {
            ValueOrFunction::Value(v) => v.impl_get_sep_char(),
            ValueOrFunction::Function(f) => f.impl_get_sep_char(),
        }
    }

    fn impl_set_empty_separator(&mut self) {
        return match self {
            ValueOrFunction::Value(v) => v.impl_set_empty_separator(),
            ValueOrFunction::Function(f) => f.impl_set_empty_separator(),
        }
    }
    fn impl_set_comma_separator(&mut self) {
        return match self {
            ValueOrFunction::Value(v) => v.impl_set_comma_separator(),
            ValueOrFunction::Function(f) => f.impl_set_comma_separator(),
        }
    }
    fn impl_set_semi_colon_separator(&mut self) {
        return match self {
            ValueOrFunction::Value(v) => v.impl_set_semi_colon_separator(),
            ValueOrFunction::Function(f) => f.impl_set_semi_colon_separator(),
        }
    }
    fn impl_is_empty_separator(&self) -> bool {
        return match self {
            ValueOrFunction::Value(v) => v.impl_is_empty_separator(),
            ValueOrFunction::Function(f) => f.impl_is_empty_separator(),
        }
    }
    fn impl_is_comma_separator(&self) -> bool {
        return match self {
            ValueOrFunction::Value(v) => v.impl_is_comma_separator(),
            ValueOrFunction::Function(f) => f.impl_is_comma_separator(),
        }
    }
    fn impl_is_semi_colon_separator(&self) -> bool {
        return match self {
            ValueOrFunction::Value(v) => v.impl_is_semi_colon_separator(),
            ValueOrFunction::Function(f) => f.impl_is_semi_colon_separator(),
        }
    }

    fn impl_get_comments_info(&self) -> &Option<SyntaxComponentCommentsInfo> {
        return match self {
            ValueOrFunction::Value(v) => v.impl_get_comments_info(),
            ValueOrFunction::Function(f) => f.impl_get_comments_info(),
        }
    }
    fn impl_get_comments_info_mut(&mut self) -> &mut Option<SyntaxComponentCommentsInfo> {
        return match self {
            ValueOrFunction::Value(v) => v.impl_get_comments_info_mut(),
            ValueOrFunction::Function(f) => f.impl_get_comments_info_mut(),
        }
    }
}

/// <summary>
/// Used to describe variables, constants, and no-argument command statements.
/// May appear in function call argument lists and function statement lists.
/// </summary>
#[add_abstract_syntax_component_fields]
pub struct ValueData
{
    m_type: i32,
    m_id: String,
    m_line: i32,

    m_comments_info: Option<SyntaxComponentCommentsInfo>,
}
impl Clone for ValueData
{
    fn clone(&self) -> Self
    {
        let mut new = Self::new();
        new.copy_form(&self);
        return new;
    }
}
impl ISyntaxComponent for ValueData
{
    fn impl_is_valid(&self) -> bool
    {
        return self.impl_have_id();
    }
    fn impl_get_id(&self) -> &String
    {
        return &self.m_id;
    }
    fn impl_get_id_type(&self) -> i32
    {
        return self.m_type;
    }
    fn impl_get_line(&self) -> i32
    {
        return self.m_line;
    }
    fn impl_to_script_string(&self, include_comment: bool) -> String
    {
cfg_if!{
    if #[cfg(feature="full_version")] {
        if include_comment {
            return self.calc_first_comment() + &Utility::quote_str_with_str_def_delim(&self.m_id, self.m_type) + &self.calc_last_comment();
        }
        else {
            return Utility::quote_str_with_str_def_delim(&self.m_id, self.m_type);
        }
    }
    else{
        return type_name::<Self>();
    }
}
    }
    fn impl_have_id(&self) -> bool
    {
        return !self.m_id.is_empty() || self.m_type == STRING_TOKEN;
    }

    fn impl_get_comments_info(&self) -> &Option<SyntaxComponentCommentsInfo>
    {
        return &self.m_comments_info;
    }
    fn impl_get_comments_info_mut(&mut self) -> &mut Option<SyntaxComponentCommentsInfo>
    {
        return &mut self.m_comments_info;
    }

    impl_abstract_syntax_component!();
}
impl ValueData
{
    pub fn set_id(&mut self, id: String)
    {
        self.m_id = id;
    }
    pub fn set_type(&mut self, _type: i32)
    {
        self.m_type = _type;
    }
    pub fn set_line(&mut self, line: i32)
    {
        self.m_line = line;
    }
    pub fn is_id(&self) -> bool
    {
        return ID_TOKEN == self.m_type;
    }
    pub fn is_number(&self) -> bool
    {
        return NUM_TOKEN == self.m_type;
    }
    pub fn is_string(&self) -> bool
    {
        return STRING_TOKEN == self.m_type;
    }
    pub fn is_dollar_string(&self) -> bool
    {
        return DOLLAR_STRING_TOKEN == self.m_type;
    }
    pub fn clear(&mut self)
    {
        self.m_type = ID_TOKEN;
        self.m_id = String::new();
        self.m_line = -1;
    }
    pub fn copy_form(&mut self, other: &ValueData)
    {
        self.m_type = other.m_type;
        self.m_id = other.m_id.clone();
        self.m_line = other.m_line;

        self.set_seperator(other.get_seperator());

        if !DslFile::dont_load_comments() {
            self.copy_comments(other);
        }
    }

    pub fn new() -> Self
    {
        ValueData {
            m_type : ID_TOKEN,
            m_id : String::new(),
            m_line : -1,
            m_separator : SEPARATOR_NOTHING,
            m_comments_info: None,
        }
    }
    pub fn from_string(val: String) -> Self
    {
        let mut _type = ID_TOKEN;
        let vx = u32::from_str_radix(&val[2..], 16);
        let v = val.parse::<f32>();
        let v2 = val.parse::<i32>();
        if Some(0) == val.find("0x") && vx.is_ok() {
            _type = NUM_TOKEN;
        }
        else if v.is_ok() || v2.is_ok() {

            _type = NUM_TOKEN;
        }
        else if Utility::need_quote(&val) {
            _type = STRING_TOKEN;
        }
        else {
            _type = ID_TOKEN;
        }

        ValueData {
            m_type : _type,
            m_id : val,
            m_line : -1,
            m_separator : SEPARATOR_NOTHING,
            m_comments_info: None,
        }
    }
    pub fn from_string_type(val: String, _type: i32) -> Self
    {
        ValueData {
            m_type : _type,
            m_id : val,
            m_line : -1,
            m_separator : SEPARATOR_NOTHING,
            m_comments_info: None,
        }
    }
}
/// <summary>
/// Function data, which may appear in function headers and argument lists.
/// </summary>
#[add_abstract_syntax_component_fields]
pub struct FunctionData
{
    m_is_high_order: bool,
    m_name: Option<ValueDataBox>,
    m_lower_order_function: Option<FunctionDataBox>,
    m_params: Option<Vec<SyntaxComponent>>,
    m_param_class: i32,

    m_comments_info: Option<SyntaxComponentCommentsInfo>,
    m_comments: Option<Vec<String>>,
}
impl Clone for FunctionData
{
    fn clone(&self) -> Self
    {
        let mut new = Self::new();
        new.copy_form(&self);
        return new;
    }
}
impl ISyntaxComponent for FunctionData
{
    fn impl_is_valid(&self) -> bool
    {
        return self.impl_have_id() || self.have_param_or_statement();
    }
    fn impl_get_id(&self) -> &String
    {
        if let Some(name) = &self.m_name {
            return name.get_id();
        }
        else if let Some(func) = &self.m_lower_order_function {
            return func.get_id();
        }
        else {
            return &EMPTY_STRING;
        }
    }
    fn impl_get_id_type(&self) -> i32
    {
        if let Some(name) = &self.m_name {
            return name.get_id_type();
        }
        else if let Some(func) = &self.m_lower_order_function {
            return func.get_id_type();
        }
        else {
            return ID_TOKEN;
        }
    }
    fn impl_get_line(&self) -> i32
    {
        if let Some(name) = &self.m_name {
            return name.get_line();
        }
        else if let Some(func) = &self.m_lower_order_function {
            return func.get_line();
        }
        else {
            if let Some(params) = &self.m_params {
                for p in params {
                    let line;
                    match p {
                        SyntaxComponent::Value(val) => {
                            line = val.get_line();
                        }
                        SyntaxComponent::Function(func) => {
                            line = func.get_line();
                        }
                        SyntaxComponent::Statement(stmt) => {
                            line = stmt.get_line();
                        }
                    }
                    if line >= 0 {
                        return line;
                    }
                }
            }
            return -1;
        }
    }
    fn impl_to_script_string(&self, include_comment: bool) -> String
    {
cfg_if! {
    if #[cfg(feature="full_version")] {
        if include_comment {
            return self.calc_first_comment() + &Utility::get_func_str_with_str_def_delim(self, true) + &self.calc_comment() + &self.calc_last_comment();
        }
        else {
            return Utility::get_func_str_with_str_def_delim(self, true);
        }
    }
    else {
        return type_name::<Self>();
    }
}
    }
    fn impl_have_id(&self) -> bool
    {
        if let Some(name) = &self.m_name {
            return name.have_id();
        }
        else if let Some(func) = &self.m_lower_order_function {
            return func.have_id();
        }
        else {
            return false;
        }
    }

    fn impl_get_comments_info(&self) -> &Option<SyntaxComponentCommentsInfo>
    {
        return &self.m_comments_info;
    }
    fn impl_get_comments_info_mut(&mut self) -> &mut Option<SyntaxComponentCommentsInfo>
    {
        if DslFile::dont_load_comments() {
            return &mut self.m_comments_info;
        }
        if self.m_comments_info.is_none() {
            self.m_comments_info = Some(SyntaxComponentCommentsInfo::new());
        }
        return &mut self.m_comments_info;
    }

    impl_abstract_syntax_component!();
}
impl FunctionData
{
    pub fn calc_comment(&self) -> String
    {
        if DslFile::dont_load_comments() {
            return String::new();
        }
        if let Some(cmts) = &self.m_comments {
            let mut cmt = cmts.join("");
            if !self.have_statement() && !self.have_extern_script() {
                if let Some(func) = &self.m_lower_order_function {
                    cmt = func.calc_comment() + &cmt;
                }
            }
            return cmt;
        }
        else {
            return String::new();
        }
    }
    pub fn comments(&self) -> Option<&Vec<String>>
    {
        if DslFile::dont_load_comments() {
            return None;
        }
        if let Some(cmts) = &self.m_comments {
            return Some(cmts);
        }
        else {
            return None;
        }
    }
    pub fn comments_mut(&mut self) -> Option<&mut Vec<String>>
    {
        if DslFile::dont_load_comments() {
            return None;
        }
        if let Some(cmts) = &mut self.m_comments {
            return Some(cmts);
        }
        else {
            return None;
        }
    }

    pub fn params(&self) -> &Option<Vec<SyntaxComponent>>
    {
        return &self.m_params;
    }
    pub fn params_mut(&mut self) -> &mut Option<Vec<SyntaxComponent>>
    {
        self.prepare_params();
        return &mut self.m_params;
    }
    pub fn set_params(&mut self, value: Option<Vec<SyntaxComponent>>)
    {
        self.m_params = value;
        if let Some(_params) = &self.m_params {
            if PARAM_CLASS_NOTHING == self.m_param_class {
                self.m_param_class = PARAM_CLASS_PARENTHESIS;
            }
        }
        else {
            self.m_param_class = PARAM_CLASS_NOTHING;
        }
    }
    pub fn is_high_order(&self) -> bool
    {
        return self.m_is_high_order;
    }
    pub fn name(&self) -> &Option<ValueDataBox>
    {
        return &self.m_name;
    }
    pub fn name_mut(&mut self) -> &mut Option<ValueDataBox>
    {
        return &mut self.m_name;
    }
    pub fn set_name(&mut self, value: Option<ValueDataBox>)
    {
        self.m_name = value;
        self.m_lower_order_function = None;
        self.m_is_high_order = false;
    }
    pub fn lower_order_function(&self) -> &Option<FunctionDataBox>
    {
        return &self.m_lower_order_function;
    }
    pub fn lower_order_function_mut(&mut self) -> &mut Option<FunctionDataBox>
    {
        return &mut self.m_lower_order_function;
    }
    pub fn set_lower_order_function(&mut self, value: Option<FunctionDataBox>) {
        self.m_name = None;
        self.m_lower_order_function = value;
        self.m_is_high_order = true;
    }
    pub fn thir_or_lower_order_call(&self) -> Option<&FunctionData>
    {
        if self.have_param() {
            return Some(self);
        }
        else if self.have_lower_order_param() {
            if let Some(func) = &self.m_lower_order_function {
                return Some(func.as_ref());
            }
            else {
                return None;
            }
        }
        else {
            return None;
        }
    }
    pub fn this_or_lower_order_statement(&self) -> Option<&FunctionData>
    {
        if self.have_statement() {
            return Some(self);
        }
        else if self.have_lower_order_statement() {
            if let Some(func) = &self.m_lower_order_function {
                return Some(func.as_ref());
            }
            else {
                return None;
            }
        }
        else {
            return None;
        }
    }
    pub fn this_or_lower_order_script(&self) -> Option<&FunctionData>
    {
        if self.have_extern_script() {
            return Some(self);
        }
        else if self.have_lower_order_extern_script() {
            if let Some(func) = &self.m_lower_order_function {
                return Some(func.as_ref());
            }
            else {
                return None;
            }
        }
        else {
            return None;
        }
    }
    pub fn have_lower_order_param(&self) -> bool
    {
        if let Some(func) = &self.m_lower_order_function {
            if func.have_param() {
                return true;
            }
        }
        return false;
    }
    pub fn have_lower_order_statement(&self) -> bool
    {
        if let Some(func) = &self.m_lower_order_function {
            if func.have_statement() {
                return true;
            }
        }
        return false;
    }
    pub fn have_lower_order_extern_script(&self) -> bool
    {
        if let Some(func) = &self.m_lower_order_function {
            if func.have_extern_script() {
                return true;
            }
        }
        return false;
    }
    pub fn set_param_class(&mut self, r#type: i32)
    {
        let inner_type = r#type & PARAM_CLASS_UNMASK;
        if inner_type >= PARAM_CLASS_MIN && inner_type < PARAM_CLASS_MAX {
            self.m_param_class = r#type;
        }
    }
    pub fn get_param_class(&self) -> i32
    {
        return self.m_param_class;
    }
    pub fn get_param_class_unmasked(&self) -> i32
    {
        let param_class = self.m_param_class & PARAM_CLASS_UNMASK;
        return param_class;
    }
    pub fn have_param_class_infix_flag(&self) -> bool
    {
        let infix = self.m_param_class & PARAM_CLASS_WRAP_INFIX_CALL_MASK;
        return infix == PARAM_CLASS_WRAP_INFIX_CALL_MASK;
    }
    pub fn set_infix_operator_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_WRAP_INFIX_CALL_MASK | PARAM_CLASS_OPERATOR;
    }
    pub fn set_operator_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_OPERATOR;
    }
    pub fn set_question_nullable_operator_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_QUESTION_NULLABLE_OPERATOR;
    }
    pub fn set_exclamation_nullable_operator_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR;
    }
    pub fn set_ternary_operator_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_TERNARY_OPERATOR;
    }
    pub fn set_parenthesis_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_PARENTHESIS;
    }
    pub fn set_bracket_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_BRACKET;
    }
    pub fn set_colon_colon_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_COLON_COLON;
    }
    pub fn set_period_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_PERIOD;
    }
    pub fn set_period_star_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_PERIOD_STAR;
    }
    pub fn set_pointer_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_POINTER;
    }
    pub fn set_pointer_star_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_POINTER_STAR;
    }
    pub fn set_parenthesis_colon_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_PARENTHESIS_COLON;
    }
    pub fn set_bracket_colon_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_BRACKET_COLON;
    }
    pub fn set_angle_bracket_colon_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_ANGLE_BRACKET_COLON;
    }
    pub fn set_parenthesis_percent_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_PARENTHESIS_PERCENT;
    }
    pub fn set_bracket_percent_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_BRACKET_PERCENT;
    }
    pub fn set_brace_percent_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_BRACE_PERCENT;
    }
    pub fn set_angle_bracket_percent_param_class(&mut self)
    {
        self.m_param_class = PARAM_CLASS_ANGLE_BRACKET_PERCENT;
    }
    pub fn is_operator_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_OPERATOR;
    }
    pub fn is_question_nullable_operator_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_QUESTION_NULLABLE_OPERATOR;
    }
    pub fn is_exclamation_nullable_operator_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR;
    }
    pub fn is_ternary_operator_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_TERNARY_OPERATOR;
    }
    pub fn is_parenthesis_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_PARENTHESIS;
    }
    pub fn is_bracket_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_BRACKET;
    }
    pub fn is_colon_colon_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_COLON_COLON;
    }
    pub fn is_period_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_PERIOD;
    }
    pub fn is_period_star_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_PERIOD_STAR;
    }
    pub fn is_pointer_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_POINTER;
    }
    pub fn is_pointer_star_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_POINTER_STAR;
    }
    pub fn is_parenthesis_colon_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_PARENTHESIS_COLON;
    }
    pub fn is_bracket_colon_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_BRACKET_COLON;
    }
    pub fn is_angle_bracket_colon_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_ANGLE_BRACKET_COLON;
    }
    pub fn is_parenthesis_percent_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_PARENTHESIS_PERCENT;
    }
    pub fn is_bracket_percent_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_BRACKET_PERCENT;
    }
    pub fn is_brace_percent_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_BRACE_PERCENT;
    }
    pub fn is_angle_bracket_percent_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_ANGLE_BRACKET_PERCENT;
    }
    pub fn is_member_param_class(&self) -> bool
    {
        let param_class = self.get_param_class_unmasked();
        return param_class == PARAM_CLASS_COLON_COLON ||
            param_class == PARAM_CLASS_PERIOD ||
            param_class == PARAM_CLASS_PERIOD_STAR ||
            param_class == PARAM_CLASS_POINTER ||
            param_class == PARAM_CLASS_POINTER_STAR;
    }
    pub fn have_param_or_statement(&self) -> bool
    {
        return PARAM_CLASS_NOTHING != self.m_param_class;
    }
    pub fn have_param(&self) -> bool
    {
        return self.have_param_or_statement() && !self.have_statement() && !self.have_extern_script();
    }
    pub fn have_statement(&self) -> bool
    {
        return PARAM_CLASS_STATEMENT == self.m_param_class;
    }
    pub fn have_extern_script(&self) -> bool
    {
        return PARAM_CLASS_EXTERN_SCRIPT == self.m_param_class;
    }
    pub fn get_param_num(&self) -> usize
    {
        if let Some(params) = &self.m_params {
            return params.len();
        }
        return 0;
    }
    pub fn set_param(&mut self, index: usize, data: SyntaxComponent)
    {
        if let Some(params) = &mut self.m_params {
            if index < params.len() {
                params[index] = data;
            }
        }
    }
    pub fn get_param(&self, index: usize) -> Option<&SyntaxComponent>
    {
        if let Some(params) = &self.m_params {
            if index < params.len() {
                return Some(&params[index]);
            }
        }
        return None;
    }
    pub fn get_param_mut(&mut self, index: usize) -> Option<&mut SyntaxComponent>
    {
        if let Some(params) = &mut self.m_params {
            if index < params.len() {
                return Some(&mut params[index]);
            }
        }
        return None;
    }
    pub fn get_param_id(&self, index: usize) -> Option<&String>
    {
        if let Some(params) = &self.m_params {
            if index < params.len() {
                let param = &params[index];
                match param {
                    SyntaxComponent::Value(param) => {
                        return Some(param.get_id());
                    }
                    SyntaxComponent::Function(param) => {
                        return Some(param.get_id());
                    }
                    SyntaxComponent::Statement(param) => {
                        return Some(param.get_id());
                    }
                }
            }
        }
        return None;
    }
    pub fn clear_params(&mut self)
    {
        self.prepare_params();
        if let Some(params) = &mut self.m_params {
            params.clear();
        }
    }
    pub fn add_string_param(&mut self, id: String)
    {
        self.prepare_params();
        if let Some(params) = &mut self.m_params {
            params.push(SyntaxComponent::Value(ValueData::from_string(id)));
        }
        if PARAM_CLASS_NOTHING as i32 == self.m_param_class {
            self.m_param_class = PARAM_CLASS_PARENTHESIS as i32;
        }
    }
    pub fn add_string_type_param(&mut self, id: String, r#type: i32)
    {
        self.prepare_params();
        if let Some(params) = &mut self.m_params {
            params.push(SyntaxComponent::Value(ValueData::from_string_type(id, r#type)));
        }
        if PARAM_CLASS_NOTHING as i32 == self.m_param_class {
            self.m_param_class = PARAM_CLASS_PARENTHESIS as i32;
        }
    }
    pub fn add_value_param(&mut self, param: ValueData)
    {
        self.prepare_params();
        if let Some(params) = &mut self.m_params {
            params.push(SyntaxComponent::Value(param));
        }
        if PARAM_CLASS_NOTHING as i32 == self.m_param_class {
            self.m_param_class = PARAM_CLASS_PARENTHESIS as i32;
        }
    }
    pub fn add_function_param(&mut self, param: FunctionData)
    {
        self.prepare_params();
        if let Some(params) = &mut self.m_params {
            params.push(SyntaxComponent::Function(param));
        }
        if PARAM_CLASS_NOTHING as i32 == self.m_param_class {
            self.m_param_class = PARAM_CLASS_PARENTHESIS as i32;
        }
    }
    pub fn add_statement_param(&mut self, param: StatementData)
    {
        self.prepare_params();
        if let Some(params) = &mut self.m_params {
            params.push(SyntaxComponent::Statement(param));
        }
        if PARAM_CLASS_NOTHING as i32 == self.m_param_class {
            self.m_param_class = PARAM_CLASS_PARENTHESIS as i32;
        }
    }
    pub fn add_syntax_component_param(&mut self, param: SyntaxComponent)
    {
        self.prepare_params();
        if let Some(params) = &mut self.m_params {
            params.push(param);
        }
        if PARAM_CLASS_NOTHING as i32 == self.m_param_class {
            self.m_param_class = PARAM_CLASS_PARENTHESIS as i32;
        }
    }
    pub fn clear(&mut self)
    {
        self.m_name = None;
        self.m_lower_order_function = None;
        self.m_is_high_order = false;
        self.m_params = None;
        self.m_param_class = PARAM_CLASS_NOTHING;

        self.m_comments_info = None;
    }
    pub fn copy_form(&mut self, other: &FunctionData)
    {
        self.m_is_high_order = other.m_is_high_order;
        if let Some(v) = &other.m_name {
            self.m_name = Some(Box::new(Utility::clone_value(v.as_ref())));
        }
        else {
            self.m_name = None;
        }
        if let Some(func) = &other.m_lower_order_function {
            self.m_lower_order_function = Some(Box::new(Utility::clone_function(func.as_ref())));
        }
        else {
            self.m_lower_order_function = None;
        }
        self.m_param_class = other.m_param_class;
        if let Some(params) = &other.m_params {
            self.clear_params();
            if let Some(ps) = &mut self.m_params {
                for p in params {
                    ps.push(Utility::clone_syntax_component(p));
                }
            }
        }
        else {
            self.m_params = None;
        }

        self.set_seperator(other.get_seperator());

        if !DslFile::dont_load_comments() {
            if let Some(cmts) = &other.m_comments {
                if let Some(ncmts) = &mut self.m_comments {
                    for c in cmts {
                        ncmts.push(c.clone());
                    }
                }
            }
            self.copy_comments(other);
        }
    }
    fn prepare_params(&mut self)
    {
        if self.m_params.is_none() {
            self.m_params = Some(Vec::new());
        }
    }

    pub fn new() -> Self
    {
        FunctionData {
            m_is_high_order: false,
            m_name: None,
            m_lower_order_function: None,
            m_params: None,
            m_param_class: PARAM_CLASS_NOTHING,

            m_comments_info: None,
            m_comments: None,
            m_separator: SEPARATOR_NOTHING,
        }
    }
}
/// <summary>
/// A statement data consists of multiple function items connected together.
/// </summary>
/// <remarks>
/// Note: Why do the members of StatementData use FunctionData[] instead of ISyntaxComponent[]?
/// 1. Although FunctionData can be reduced to ValueData syntactically, it cannot be StatementData. Thus, conceptually, it cannot be equivalent to ISyntaxComponent.
/// 2. In terms of design, FunctionData should take into account the reduction scenario and try not to occupy additional space when reduced.
/// </remarks>
#[add_abstract_syntax_component_fields]
pub struct StatementData
{
    m_value_or_functions: Option<Vec<ValueOrFunction>>,
    m_comments_info: Option<SyntaxComponentCommentsInfo>,
}
impl Clone for StatementData
{
    fn clone(&self) -> Self
    {
        let mut new = Self::new();
        new.copy_form(&self);
        return new;
    }
}
impl ISyntaxComponent for StatementData
{
    fn impl_is_valid(&self) -> bool
    {
        let mut ret = true;
        if let Some(v_or_fs) = &self.m_value_or_functions {
            if v_or_fs.len() <= 0 {
                ret = false;
            }
            else {
                for item in v_or_fs {
                    match item {
                        ValueOrFunction::Value(v) => {
                            ret = ret && v.is_valid();
                        }
                        ValueOrFunction::Function(f) => {
                            ret = ret && f.is_valid();
                        }
                    }
                }
            }
        }
        return ret;
    }
    fn impl_get_id(&self) -> &String
    {
        if let Some(v_or_fs) = &self.m_value_or_functions {
            if v_or_fs.len() <= 0 {
                return &EMPTY_STRING;
            }
            else {
                if let Some(item) = v_or_fs.first() {
                    match item {
                        ValueOrFunction::Value(v) => {
                            if v.have_id() {
                                return v.get_id();
                            }
                        }
                        ValueOrFunction::Function(f) => {
                            if f.have_id() {
                                return f.get_id();
                            }
                        }
                    }
                }
            }
        }
        return &EMPTY_STRING;
    }
    fn impl_get_id_type(&self) -> i32
    {
        if let Some(v_or_fs) = &self.m_value_or_functions {
            if v_or_fs.len() <= 0 {
                return ID_TOKEN;
            }
            else {
                if let Some(item) = v_or_fs.first() {
                    match item {
                        ValueOrFunction::Value(v) => {
                            if v.have_id() {
                                return v.get_id_type();
                            }
                        }
                        ValueOrFunction::Function(f) => {
                            if f.have_id() {
                                return f.get_id_type();
                            }
                        }
                    }
                }
            }
        }
        return ID_TOKEN;
    }
    fn impl_get_line(&self) -> i32
    {
        if let Some(v_or_fs) = &self.m_value_or_functions {
            if v_or_fs.len() <= 0 {
                return ID_TOKEN;
            }
            else {
                for item in v_or_fs {
                    let line = item.get_line();
                    if line >= 0 {
                        return line;
                    }
                }
            }
        }
        return -1;
    }
    fn impl_to_script_string(&self, include_comment: bool) -> String
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        if self.m_value_or_functions.is_none() {
            return String::new();
        }
        //In contrast to the write method, here the output is a single line with no indentation.
        if let Some(v_or_f) = self.first() {
            if let ValueOrFunction::Function(f) = v_or_f {
                if let Some(call_data) = f.lower_order_function() {
                    if call_data.is_ternary_operator_param_class() {
                        //The ternary operator is represented as op1(cond)(true_val)op2(false_val)
                        if call_data.have_id() && call_data.have_param_or_statement() {
                            let mut line = String::from("/*[?:]*/");
                            if self.get_function_num() == 2 {
                                if let Some(v_or_f2) = self.second() {
                                    if let ValueOrFunction::Function(f2) = v_or_f2 {
                                        if f2.have_id() && f2.have_param_or_statement() {
                                            line = format!("{} {} {}", &call_data.get_param(0).unwrap().to_script_string(include_comment), call_data.get_id(), &f.get_param(0).unwrap().to_script_string(include_comment));
                                            line = format!("{} {} {}", &line, f2.get_id(), &f2.get_param(0).unwrap().to_script_string(include_comment));
                                        }
                                    }
                                }
                            }
                            if include_comment {
                                return self.calc_first_comment() + &line + &self.calc_last_comment();
                            }
                            else {
                                return line;
                            }
                        }
                        else {
                            if include_comment {
                                return self.calc_first_comment() + &self.calc_last_comment();
                            }
                            else {
                                return String::new();
                            }
                        }
                    }
                }
            }
        }
        let mut str_builder = String::new();
        if include_comment {
            str_builder.extend(self.calc_first_comment().chars());
        }
        if let Some(v_or_fs) = self.functions() {
            for f in v_or_fs {
                str_builder.extend(f.to_script_string(include_comment).chars());
            }
        }
        if include_comment {
            str_builder.extend(self.calc_last_comment().chars());
        }
        return str_builder;
    }
    else {
        return type_name::<Self>();
    }
}
    }
    fn impl_have_id(&self) -> bool
    {
        if let Some(v_or_fs) = &self.m_value_or_functions {
            if v_or_fs.len() <= 0 {
                return false;
            }
            else {
                if let Some(item) = v_or_fs.first() {
                    match item {
                        ValueOrFunction::Value(v) => {
                            return v.have_id();
                        }
                        ValueOrFunction::Function(f) => {
                            return f.have_id();
                        }
                    }
                }
            }
        }
        return false;
    }

    fn impl_get_comments_info(&self) -> &Option<SyntaxComponentCommentsInfo>
    {
        return &self.m_comments_info;
    }
    fn impl_get_comments_info_mut(&mut self) -> &mut Option<SyntaxComponentCommentsInfo>
    {
        if DslFile::dont_load_comments() {
            return &mut self.m_comments_info;
        }
        if self.m_comments_info.is_none() {
            self.m_comments_info = Some(SyntaxComponentCommentsInfo::new());
        }
        return &mut self.m_comments_info;
    }

    impl_abstract_syntax_component!();
}
impl StatementData
{
    pub fn get_function_num(&self) -> usize
    {
        if let Some(v_or_fs) = &self.m_value_or_functions {
            return v_or_fs.len();
        }
        return 0;
    }
    pub fn set_function(&mut self, index: usize, v_or_f: ValueOrFunction)
    {
        if let Some(v_or_fs) = &mut self.m_value_or_functions {
            if index < v_or_fs.len() {
                v_or_fs[index] = v_or_f;
            }
        }
    }
    pub fn get_function(&self, index: usize) -> Option<&ValueOrFunction>
    {
        if let Some(v_or_fs) = &self.m_value_or_functions {
            if index < v_or_fs.len() {
                return Some(&v_or_fs[index]);
            }
        }
        return None;
    }
    pub fn get_function_mut(&mut self, index: usize) -> Option<&mut ValueOrFunction>
    {
        if let Some(v_or_fs) = &mut self.m_value_or_functions {
            if index < v_or_fs.len() {
                return Some(&mut v_or_fs[index]);
            }
        }
        return None;
    }
    pub fn get_function_id(&self, index: usize) -> &String
    {
        if let Some(v_or_fs) = &self.m_value_or_functions {
            if index < v_or_fs.len() {
                return v_or_fs[index].get_id();
            }
        }
        return &EMPTY_STRING;
    }
    pub fn add_function(&mut self, func: ValueOrFunction)
    {
        self.prepare_value_or_functions();
        if let Some(value_or_functions) = &mut self.m_value_or_functions {
            value_or_functions.push(func);
        }
    }
    pub fn functions(&self) -> &Option<Vec<ValueOrFunction>>
    {
        return &self.m_value_or_functions;
    }
    pub fn functions_mut(&mut self) -> &mut Option<Vec<ValueOrFunction>>
    {
        self.prepare_value_or_functions();
        return &mut self.m_value_or_functions;
    }
    pub fn first(&self) -> Option<&ValueOrFunction>
    {
        if let Some(value_or_functions) = &self.m_value_or_functions {
            if value_or_functions.len() > 0 {
                return Some(&value_or_functions[0]);
            }
        }
        return None;
    }
    pub fn first_mut(&mut self) -> Option<&mut ValueOrFunction>
    {
        if let Some(value_or_functions) = &mut self.m_value_or_functions {
            if value_or_functions.len() > 0 {
                return Some(&mut value_or_functions[0]);
            }
        }
        return None;
    }
    pub fn second(&self) -> Option<&ValueOrFunction>
    {
        if let Some(value_or_functions) = &self.m_value_or_functions {
            if value_or_functions.len() > 1 {
                return Some(&value_or_functions[1]);
            }
        }
        return None;
    }
    pub fn second_mut(&mut self) -> Option<&mut ValueOrFunction>
    {
        if let Some(value_or_functions) = &mut self.m_value_or_functions {
            if value_or_functions.len() > 1 {
                return Some(&mut value_or_functions[1]);
            }
        }
        return None;
    }
    pub fn third(&self) -> Option<&ValueOrFunction>
    {
        if let Some(value_or_functions) = &self.m_value_or_functions {
            if value_or_functions.len() > 2 {
                return Some(&value_or_functions[2]);
            }
        }
        return None;
    }
    pub fn third_mut(&mut self) -> Option<&mut ValueOrFunction>
    {
        if let Some(value_or_functions) = &mut self.m_value_or_functions {
            if value_or_functions.len() > 2 {
                return Some(&mut value_or_functions[2]);
            }
        }
        return None;
    }
    pub fn last(&self) -> Option<&ValueOrFunction>
    {
        if let Some(value_or_functions) = &self.m_value_or_functions {
            if value_or_functions.len() > 0 {
                let len = value_or_functions.len();
                return Some(&value_or_functions[len - 1]);
            }
        }
        return None;
    }
    pub fn last_mut(&mut self) -> Option<&mut ValueOrFunction>
    {
        if let Some(value_or_functions) = &mut self.m_value_or_functions {
            if value_or_functions.len() > 0 {
                let len = value_or_functions.len();
                return Some(&mut value_or_functions[len - 1]);
            }
        }
        return None;
    }
    pub fn clear(&mut self)
    {
        self.m_value_or_functions = None;
        self.m_comments_info = None;
    }
    pub fn copy_form(&mut self, other: &StatementData)
    {
        if let Some(other_value_or_functions) = &other.m_value_or_functions {
            self.prepare_value_or_functions();
            if let Some(value_or_functions) = &mut self.m_value_or_functions {
                value_or_functions.clear();
                for f in other_value_or_functions {
                    let nf = Utility::clone_value_or_function(f);
                    value_or_functions.push(nf);
                }
            }
        }
        else {
            self.m_value_or_functions = None;
        }

        self.set_seperator(other.get_seperator());

        if !DslFile::dont_load_comments() {
            self.copy_comments(other);
        }
    }
    fn prepare_value_or_functions(&mut self)
    {
        if self.m_value_or_functions.is_none() {
            self.m_value_or_functions = Some(Vec::new());
        }
    }

    pub fn new() -> Self
    {
        StatementData {
            m_value_or_functions: None,
            m_comments_info: None,

            m_separator: SEPARATOR_NOTHING,
        }
    }
}

pub struct DslFile<'a>
{
    m_name_tags: HashMap<String, u32>,
    m_dsl_infos: Vec<SyntaxComponent>,
    m_nullable_syntax_enabled: bool,
    m_string_begin_delimiter: String,
    m_string_end_delimiter: String,
    m_script_begin_delimiter: String,
    m_script_end_delimiter: String,

    m_on_token_can_eat_char: Option<TokenCanEatCharDelegationBox<'a>>,
    m_on_get_token: Option<GetTokenDelegationBox<'a>>,
    m_on_before_add_function: Option<BeforeAddFunctionDelegationBox<'a>>,
    m_on_add_function: Option<AddFunctionDelegationBox<'a>>,
    m_on_before_end_statement: Option<BeforeEndStatementDelegationBox<'a>>,
    m_on_end_statement: Option<EndStatementDelegationBox<'a>>,
    m_on_before_build_operator: Option<BeforeBuildOperatorDelegationBox<'a>>,
    m_on_build_operator: Option<BuildOperatorDelegationBox<'a>>,
    m_on_set_function_id: Option<SetFunctionIdDelegationBox<'a>>,
    m_on_before_build_high_order: Option<BeforeBuildHighOrderDelegationBox<'a>>,
    m_on_build_high_order: Option<BuildHighOrderDelegationBox<'a>>,
}

pub const BINARY_IDENTITY: &str = "BDSL";

static mut DONT_LOAD_COMMENTS: bool = false;

impl<'a> DslFile<'a>
{
    pub fn dsl_infos(&self) -> &Vec<SyntaxComponent>
    {
        return &self.m_dsl_infos;
    }
    pub fn add_dsl_info(&mut self, data: SyntaxComponent)
    {
        self.m_dsl_infos.push(data);
    }
    pub fn clear(&mut self)
    {
        self.m_dsl_infos.clear();
    }

    pub fn load(&mut self, file: String, log_callback: DslLogDelegationBox) -> bool
    {
        if let Ok(content) = fs::read_to_string(file) {
            //logCallback(format!("DslFile.Load {0}:\n{1}", file, content));
            return self.load_from_string(content, log_callback);
        }
        return false;
    }
    pub fn load_from_string(&mut self, _content: String, log_callback: DslLogDelegationBox) -> bool
    {
        let content = DslFile::mac_2_unix(&_content);

        self.m_dsl_infos.clear();
        let log = DslLogCell::new(DslLog::new(log_callback));

        let error = DslErrorCell::new(DslError::new(&log));
        let action = DslActionCell::new(DslAction::new(&log));
        let tokens = DslTokenCell::new(DslToken::new(&action, &log, content, self.m_nullable_syntax_enabled));

        if let Some(on_get_token) = &self.m_on_get_token {
            tokens.borrow_mut().set_on_get_token(&Box::new(on_get_token));
        }
        if let Some(on_token_can_eat_char) = &self.m_on_token_can_eat_char {
            tokens.borrow_mut().set_on_token_can_eat_char(&Box::new(on_token_can_eat_char));
        }

        action.borrow_mut().set_dsl_token(&tokens);
        action.borrow_mut().set_name_tags(self.m_name_tags.clone());

        if let Some(on_before_add_function) = &self.m_on_before_add_function {
            action.borrow_mut().set_on_before_add_function(on_before_add_function);
        }
        if let Some(on_add_function) = &self.m_on_add_function {
            action.borrow_mut().set_on_add_function(on_add_function);
        }
        if let Some(on_before_end_statement) = &self.m_on_before_end_statement {
            action.borrow_mut().set_on_before_end_statement(on_before_end_statement);
        }
        if let Some(on_end_statement) = &self.m_on_end_statement {
            action.borrow_mut().set_on_end_statement(on_end_statement);
        }
        if let Some(on_before_build_operator) = &self.m_on_before_build_operator {
            action.borrow_mut().set_on_before_build_operator(on_before_build_operator);
        }
        if let Some(on_build_operator) = &self.m_on_build_operator {
            action.borrow_mut().set_on_build_operator(on_build_operator);
        }
        if let Some(on_set_function_id) = &self.m_on_set_function_id {
            action.borrow_mut().set_on_set_function_id(on_set_function_id);
        }
        if let Some(on_before_build_high_order) = &self.m_on_before_build_high_order {
            action.borrow_mut().set_on_before_build_high_order(on_before_build_high_order);
        }
        if let Some(on_build_high_order) = &self.m_on_build_high_order {
            action.borrow_mut().set_on_build_high_order(on_build_high_order);
        }

        parse(&action, &tokens, &error, 0);

        if log.borrow().has_error() {
            self.m_dsl_infos.clear();
        }
        else {
            self.m_dsl_infos.extend(std::mem::take(action.borrow_mut().get_script_datas()));
        }
        if !tokens.borrow().string_begin_delimiter().is_empty() {
            self.m_string_begin_delimiter = tokens.borrow().string_begin_delimiter().clone();
        }
        if !tokens.borrow().string_end_delimiter().is_empty() {
            self.m_string_end_delimiter = tokens.borrow().string_end_delimiter().clone();
        }
        if !tokens.borrow().script_begin_delimiter().is_empty() {
            self.m_script_begin_delimiter = tokens.borrow().script_begin_delimiter().clone();
        }
        if !tokens.borrow().script_end_delimiter().is_empty() {
            self.m_script_end_delimiter = tokens.borrow().script_end_delimiter().clone();
        }
        return !log.borrow().has_error();
    }
    pub fn save(&self, file: String)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        let mut sb = String::new();
        if self.m_string_begin_delimiter != "\"" || self.m_string_end_delimiter != "\"" {
            sb.push_str(&format!("@@delimiter(string, \"{0}\", \"{1}\");", self.m_string_begin_delimiter, self.m_string_end_delimiter));
            sb.push('\n');
        }
        if self.m_script_begin_delimiter != "{:" || self.m_script_end_delimiter != ":}" {
            sb.push_str(&format!("@@delimiter(script, \"{0}\", \"{1}\");", self.m_script_begin_delimiter, self.m_script_end_delimiter));
            sb.push('\n');
        }
        for info in &self.m_dsl_infos {
            Utility::write_syntax_component(&mut sb, &info, 0, true, true, &DelimiterInfo::new(&self.m_string_begin_delimiter, &self.m_string_end_delimiter, &self.m_script_begin_delimiter, &self.m_script_end_delimiter));
        }
        if let Result::Err(_e) = fs::write(file, sb) {

        }
    }
}
    }
    pub fn to_script_string(&self) -> String
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        let mut sb = String::new();
        for info in &self.m_dsl_infos {
            Utility::write_syntax_component(&mut sb, &info, 0, true, false, &DelimiterInfo {
                string_begin_delimiter: &self.m_string_begin_delimiter,
                string_end_delimiter: &self.m_string_end_delimiter,
                script_begin_delimiter: &self.m_script_begin_delimiter,
                script_end_delimiter: &self.m_script_end_delimiter,
            });
        }
        return sb;
    }
    else {
        return type_name::<Self>();
    }
}
    }

    pub fn load_binary_file(&mut self, file: &String, reuse_key_buffer: &mut Vec<String>, reuse_id_buffer: &mut Vec<String>)
    {
        if let Ok(code) = fs::read(file) {
            self.load_binary_code(&code, reuse_key_buffer, reuse_id_buffer);
        }
    }
    pub fn load_binary_code(&mut self, binary_code: &[u8], reuse_key_buffer: &mut Vec<String>, reuse_id_buffer: &mut Vec<String>)
    {
        self.m_dsl_infos.clear();
        if binary_code.len() < BINARY_IDENTITY.len() {
            return;
        }
        let mut pos = BINARY_IDENTITY.len();
        let bytes_len = Utility::read_int(binary_code, pos) as usize;
        pos += 4;
        let bytes2_len = Utility::read_int(binary_code, pos) as usize;
        pos += 4;
        let key_count = Utility::read_int(binary_code, pos) as usize;
        pos += 4;
        let bytes_start = pos;
        let bytes2_start = bytes_start + bytes_len;
        let key_start = bytes2_start + bytes2_len;
        if reuse_key_buffer.capacity() < key_count {
            reuse_key_buffer.reserve(key_count - reuse_key_buffer.capacity());
        }
        reuse_key_buffer.clear();
        let keys = reuse_key_buffer;
        pos = key_start;
        let mut i = 0;
        while i < key_count {
            let mut byte_count = 0;
            let len = Utility::read_7bit_encoded_int(binary_code, pos, &mut byte_count);
            if len >= 0 {
                pos += byte_count;
                let key = std::str::from_utf8(&binary_code[pos..(pos + len as usize)]).unwrap();
                keys.push(String::from(key));
                pos += len as usize;
            }
            else {
                break;
            }
            i += 1;
        }
        if reuse_id_buffer.capacity() < bytes2_len as usize {
            reuse_id_buffer.reserve(bytes2_len as usize - reuse_id_buffer.capacity());
        }
        reuse_id_buffer.clear();
        let identifiers = reuse_id_buffer;
        let mut i = bytes2_start;
        while i < bytes2_start + bytes2_len && i < binary_code.len() {
            let mut byte_count = 0;
            let ix = Utility::read_7bit_encoded_int(binary_code, i, &mut byte_count);
            if ix >= 0 {
                i += byte_count - 1;
            }
            else {
                break;
            }
            if ix >= 0 && ix < keys.len() as i32 {
                identifiers.push(keys[ix as usize].clone());
            }
            else {
                identifiers.push(String::new());
            }
            i += 1;
        }
        let infos = Utility::read_binary(binary_code, bytes_start, bytes_len, identifiers);
        self.m_dsl_infos.extend(infos);
    }
    pub fn save_binary_file(&self, file: String)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        let mut stream: Cursor<Vec<u8>> = Cursor::new(Vec::new());
        let mut identifiers: Vec<String> = Vec::new();
        for info in self.dsl_infos().iter() {
            Utility::write_binary(&mut stream, &mut identifiers, info);
        }

        let bytes = stream.get_ref();
        let mut dict: BTreeMap<String, i32> = BTreeMap::new();
        for key in identifiers.iter() {
            dict.insert(key.clone(), 0);
        }
        let vec_keys: Vec<String> = dict.keys().cloned().collect();
        let keys = &vec_keys[0..vec_keys.len()];

        let mut ms: Cursor<Vec<u8>> = Cursor::new(Vec::new());
        for key in identifiers.iter() {
            if let Ok(ix) = keys.binary_search(key) {
                Utility::write_7bit_encoded_int(&mut ms, ix);
            }
        }
        let bytes2 = ms.get_ref();

        let mut bdsl: Cursor<Vec<u8>> = Cursor::new(Vec::new());
        let _ = bdsl.write(BINARY_IDENTITY.as_bytes());
        Utility::write_int(&mut bdsl, bytes.len() as i32);
        Utility::write_int(&mut bdsl, bytes2.len() as i32);
        Utility::write_int(&mut bdsl, keys.len() as i32);
        let _ = bdsl.write(&bytes[0..]);
        let _ = bdsl.write(&bytes2[0..]);
        for str in keys.iter() {
            let bstr = str.as_bytes();
            Utility::write_7bit_encoded_int(&mut bdsl, bstr.len());
            let _ = bdsl.write(bstr);
        }
        let _ = fs::write(file, bdsl.get_ref());
    }
}
    }

    pub fn set_name_tags(&mut self, tags: HashMap<String, u32>)
    {
        self.m_name_tags = tags;
    }
    pub fn name_tags(&self) -> &HashMap<String, u32>
    {
        return &self.m_name_tags;
    }
    pub fn set_string_delimiter(&mut self, begin: String, end: String)
    {
        self.m_string_begin_delimiter = begin;
        self.m_string_end_delimiter = end;
    }
    pub fn set_script_delimiter(&mut self, begin: String, end: String)
    {
        self.m_script_begin_delimiter = begin;
        self.m_script_end_delimiter = end;
    }
    pub fn nullable_syntax_enabled(&self) -> bool
    {
        return self.m_nullable_syntax_enabled;
    }
    pub fn set_nullable_syntax_enabled(&mut self, value: bool)
    {
        self.m_nullable_syntax_enabled = value;
    }
    pub fn string_begin_delimiter(&self) -> &String
    {
        return &self.m_string_begin_delimiter;
    }
    pub fn string_end_delimiter(&self) -> &String
    {
        return &self.m_string_end_delimiter;
    }
    pub fn script_begin_delimiter(&self) -> &String
    {
        return &self.m_script_begin_delimiter;
    }
    pub fn script_end_delimiter(&mut self) -> &String
    {
        return &self.m_script_end_delimiter;
    }
    pub fn on_token_can_eat_char(&self) -> &Option<TokenCanEatCharDelegationBox<'a>>
    {
        return &self.m_on_token_can_eat_char;
    }
    pub fn set_on_token_can_eat_char(&mut self, value: TokenCanEatCharDelegationBox<'a>)
    {
        self.m_on_token_can_eat_char = Some(value);
    }
    pub fn on_get_token(&self) -> &Option<GetTokenDelegationBox<'a>>
    {
        return &self.m_on_get_token;
    }
    pub fn set_on_get_token(&mut self, value: GetTokenDelegationBox<'a>)
    {
        self.m_on_get_token = Some(value);
    }
    pub fn on_before_add_function(&self) -> &Option<BeforeAddFunctionDelegationBox<'a>>
    {
        return &self.m_on_before_add_function;
    }
    pub fn set_on_before_add_function(&mut self, value: BeforeAddFunctionDelegationBox<'a>)
    {
        self.m_on_before_add_function = Some(value);
    }
    pub fn on_add_function(&self) -> &Option<AddFunctionDelegationBox<'a>>
    {
        return &self.m_on_add_function;
    }
    pub fn set_on_add_function(&mut self, value: AddFunctionDelegationBox<'a>)
    {
        self.m_on_add_function = Some(value);
    }
    pub fn on_before_end_statement(&self) -> &Option<BeforeEndStatementDelegationBox<'a>>
    {
        return &self.m_on_before_end_statement;
    }
    pub fn set_on_before_end_statement(&mut self, value: BeforeEndStatementDelegationBox<'a>)
    {
        self.m_on_before_end_statement = Some(value);
    }
    pub fn on_end_statement(&self) -> &Option<EndStatementDelegationBox<'a>>
    {
        return &self.m_on_end_statement;
    }
    pub fn set_on_end_statement(&mut self, value: EndStatementDelegationBox<'a>)
    {
        self.m_on_end_statement = Some(value);
    }
    pub fn on_before_build_operator(&self) -> &Option<BeforeBuildOperatorDelegationBox<'a>>
    {
        return &self.m_on_before_build_operator;
    }
    pub fn set_on_before_build_operator(&mut self, value: BeforeBuildOperatorDelegationBox<'a>)
    {
        self.m_on_before_build_operator = Some(value);
    }
    pub fn on_build_operator(&self) -> &Option<BuildOperatorDelegationBox<'a>>
    {
        return &self.m_on_build_operator;
    }
    pub fn set_on_build_operator(&mut self, value: BuildOperatorDelegationBox<'a>)
    {
        self.m_on_build_operator = Some(value);
    }
    pub fn on_set_function_id(&self) -> &Option<SetFunctionIdDelegationBox<'a>>
    {
        return &self.m_on_set_function_id;
    }
    pub fn set_on_set_function_id(&mut self, value: SetFunctionIdDelegationBox<'a>)
    {
        self.m_on_set_function_id = Some(value);
    }
    pub fn on_before_build_high_order(&self) -> &Option<BeforeBuildHighOrderDelegationBox<'a>>
    {
        return &self.m_on_before_build_high_order;
    }
    pub fn set_on_before_build_high_order(&mut self, value: BeforeBuildHighOrderDelegationBox<'a>)
    {
        self.m_on_before_build_high_order = Some(value);
    }
    pub fn on_build_high_order(&self) -> &Option<BuildHighOrderDelegationBox<'a>>
    {
        return &self.m_on_build_high_order;
    }
    pub fn set_on_build_high_order(&mut self, value: BuildHighOrderDelegationBox<'a>)
    {
        self.m_on_build_high_order = Some(value);
    }

    pub fn new() -> Self
    {
        DslFile {
            m_name_tags: HashMap::new(),
            m_dsl_infos: Vec::new(),
            m_nullable_syntax_enabled: true,
            m_string_begin_delimiter: String::from("\""),
            m_string_end_delimiter: String::from("\""),
            m_script_begin_delimiter: String::from("{:"),
            m_script_end_delimiter: String::from(":}"),

            m_on_token_can_eat_char: None,
            m_on_get_token: None,
            m_on_before_add_function: None,
            m_on_add_function: None,
            m_on_before_end_statement: None,
            m_on_end_statement: None,
            m_on_before_build_operator: None,
            m_on_build_operator: None,
            m_on_set_function_id: None,
            m_on_before_build_high_order: None,
            m_on_build_high_order: None,
        }
    }

    pub fn dont_load_comments() -> bool
    {
        unsafe {
            return DONT_LOAD_COMMENTS;
        }
    }
    pub fn set_dont_load_comments(value: bool)
    {
        unsafe {
            DONT_LOAD_COMMENTS = value;
        }
    }
    pub fn is_binary_dsl(data: &[u8], start: usize) -> bool
    {
        if data.len() < BINARY_IDENTITY.len() {
            return false;
        }
        let mut r = true;
        let mut i = 0;
        while i < BINARY_IDENTITY.len() && start + i < data.len() {
            if BINARY_IDENTITY.as_bytes()[i] != data[start + i] {
                r = false;
                break;
            }
            i += 1;
        }
        return r;
    }

    pub fn mac_2_unix(txt: &String) -> String
    {
        let re = Regex::new(r"\r(?!\n)").unwrap();
        let txt = re.replace_all(txt, "\n").replace("\r\n", "n");
        return txt;
    }
    pub fn text_2_dos(txt: &String) -> String
    {
        let re = Regex::new(r"(?<!\r)\n").unwrap();
        let txt = re.replace_all(txt, "\r\n").replace('r', "\r\n");
        return txt;
    }
    pub fn text_2_unix(txt: String) -> String
    {
        return txt.replace("\r\n", "\n").replace('\r', "\n");
    }
    pub fn text_2_mac(txt: String) -> String
    {
        return txt.replace("\r\n", "\r").replace('\n', "\r");
    }
}

pub struct DelimiterInfo<'a>
{
    pub string_begin_delimiter: &'a str,
    pub string_end_delimiter: &'a str,
    pub script_begin_delimiter: &'a str,
    pub script_end_delimiter: &'a str,
}
impl<'a> DelimiterInfo<'a>
{
    pub fn new_def() -> Self
    {
        DelimiterInfo {
            string_begin_delimiter: &"\"",
            string_end_delimiter: &"\"",
            script_begin_delimiter: &"{:",
            script_end_delimiter: &":}",
        }
    }
    pub fn new(str_begin_delim: &'a String, str_end_delim: &'a String, scp_begin_delim: &'a String, scp_end_delim: &'a String) -> Self
    {
        DelimiterInfo {
            string_begin_delimiter: str_begin_delim,
            string_end_delimiter: str_end_delim,
            script_begin_delimiter: scp_begin_delim,
            script_end_delimiter: scp_end_delim,
        }
    }
}
pub struct Utility;
impl Utility
{
    fn clone_syntax_component(syntax: &SyntaxComponent) -> SyntaxComponent
    {
        match syntax {
            SyntaxComponent::Value(val) => {
                return SyntaxComponent::Value(Utility::clone_value(val));
            }
            SyntaxComponent::Function(func) => {
                return SyntaxComponent::Function(Utility::clone_function(func));
            }
            SyntaxComponent::Statement(stm) => {
                return SyntaxComponent::Statement(Utility::clone_statement(stm));
            }
        }
    }
    fn clone_value_or_function(syntax: &ValueOrFunction) -> ValueOrFunction
    {
        match syntax {
            ValueOrFunction::Value(val) => {
                return ValueOrFunction::Value(Utility::clone_value(val));
            }
            ValueOrFunction::Function(func) => {
                return ValueOrFunction::Function(Utility::clone_function(func));
            }
        }
    }
    fn clone_value(val: &ValueData) -> ValueData
    {
        let mut nval = ValueData::new();
        nval.copy_form(val);
        return nval;
    }
    fn clone_function(func: &FunctionData) -> FunctionData
    {
        let mut nfunc = FunctionData::new();
        nfunc.copy_form(func);
        return nfunc;
    }
    fn clone_statement(stm: &StatementData) -> StatementData
    {
        let mut nstm = StatementData::new();
        nstm.copy_form(stm);
        return nstm;
    }
    fn read_int(bytes: &[u8], pos: usize) -> i32
    {
        if pos + 3 < bytes.len() {
            return bytes[pos] as i32 | ((bytes[pos + 1] as i32) << 8) | ((bytes[pos + 2] as i32) << 16) | ((bytes[pos + 3] as i32) << 24);
        }
        else {
            return 0;
        }
    }
    fn read_7bit_encoded_int(bytes: &[u8], _pos: usize, byte_count: &mut usize) -> i32
    {
        let mut pos = _pos;
        let mut num: i32 = -1;
        *byte_count = 0;
        if pos < bytes.len() {
            let mut bit_count = 0;
            let mut b: u8;
            num = 0;
            loop {
                if bit_count == 3 {
                    num = -1;
                    break;
                }
                b = bytes[pos];
                pos += 1;
                num |= ((b & 0x7F) as i32) << bit_count;
                bit_count += 7;
                if pos < bytes.len() && (b & 0x80) != 0 {
                }
                else{
                    break;
                }
            }
            *byte_count = bit_count / 7;
        }
        return num;
    }
    fn write_int(s: &mut Cursor<Vec<u8>>, val: i32)
    {
        let b1 = val as u8;
        let b2 = (val >> 8) as u8;
        let b3 = (val >> 16) as u8;
        let b4 = (val >> 24) as u8;
        let _ = s.write(&[b1]);
        let _ = s.write(&[b2]);
        let _ = s.write(&[b3]);
        let _ = s.write(&[b4]);
    }
    fn write_7bit_encoded_int(s: &mut Cursor<Vec<u8>>, val: usize)
    {
        let mut num: u32 = val as u32;
        while num >= 128 {
            let _ = s.write(&[(num | 0x80) as u8]);
            num >>= 7;
        }
        let _ = s.write(&[num as u8]);
    }

    pub fn write_syntax_component(stream: &mut String, data: &SyntaxComponent, indent: i32, first_line_no_indent: bool, is_last_of_statement: bool, delim: &DelimiterInfo)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        match data {
            SyntaxComponent::Value(val) => {
                Self::write_value_data(stream, val, indent, first_line_no_indent, is_last_of_statement);
            }
            SyntaxComponent::Function(call) => {
                Self::write_function_data(stream, call, indent, first_line_no_indent, is_last_of_statement, delim);
            }
            SyntaxComponent::Statement(stmt) => {
                Self::write_statement_data(stream, stmt, indent, first_line_no_indent, is_last_of_statement, delim);
            }
        }
    }
}
    }

    pub fn write_value_data(stream: &mut String, data: &ValueData, indent: i32, first_line_no_indent: bool, is_last_of_statement: bool)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        Self::write_first_comments(stream, data, indent, first_line_no_indent);
        Self::write_text(stream, &data.to_script_string(false), if first_line_no_indent { 0 } else { indent });
        if is_last_of_statement {
            stream.push(data.get_sep_char());
        }
        Self::write_last_comments(stream, data, indent, is_last_of_statement);
    }
}
    }

    pub fn write_function_data(stream: &mut String, data: &FunctionData, indent: i32, first_line_no_indent: bool, is_last_of_statement: bool, delim: &DelimiterInfo)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        //string lineNo = format!("/* {0} */", data.get_line());
        //write_line(stream, lineNo, indent);
        Self::write_first_comments(stream, data, indent, first_line_no_indent);
        if data.have_param_or_statement() {
            if data.is_operator_param_class() {
                let param_num = data.get_param_num();
                if param_num == 1 {
                    Self::write_text(stream, "", if first_line_no_indent { 0 } else { indent });
                    if data.is_high_order() {
                        if let Some(lo_func) = data.lower_order_function() {
                            Self::write_function_data(stream, lo_func, indent, if param_num > 0 { true } else { first_line_no_indent }, false, delim);
                        }
                    }
                    else if data.have_id() {
                        let mut line;
                        if data.have_param_class_infix_flag() {
                            line = String::from("`") + data.get_id();
                        }
                        else {
                            line = data.get_id().clone();
                        }
                        line = Self::quote_value(&line, data.get_id_type(), &delim.string_begin_delimiter, &delim.string_end_delimiter);
                        Self::write_text(stream, &line, if param_num > 0 { 0 } else { if first_line_no_indent { 0 } else { indent } });
                    }
                    Self::write_text(stream, " ", 0);
                    if let Some(param) = data.get_param(0) {
                        Self::write_syntax_component(stream, param, indent, true, false, delim);
                    }
                }
                else {
                    if param_num > 0 {
                        if let Some(param) = data.get_param(0) {
                            Self::write_syntax_component(stream, param, indent, first_line_no_indent, false, delim);
                        }
                        Self::write_text(stream, " ", 0);
                    }
                    if data.is_high_order() {
                        if let Some(lo_func) = data.lower_order_function() {
                            Self::write_function_data(stream, lo_func, indent, if param_num > 0 { true } else { first_line_no_indent }, false, delim);
                        }
                    }
                    else if data.have_id() {
                        let mut line;
                        if data.have_param_class_infix_flag() {
                            line = String::from("`") + data.get_id();
                        }
                        else {
                            line = data.get_id().clone();
                        }
                        line = Self::quote_value(&line, data.get_id_type(), delim.string_begin_delimiter, delim.string_end_delimiter);
                        Self::write_text(stream, &line, if param_num > 0 { 0 } else { if first_line_no_indent { 0 } else { indent } });
                    }
                    if param_num > 1 {
                        Self::write_text(stream, " ", 0);
                        if let Some(param) = data.get_param(1) {
                            Self::write_syntax_component(stream, param, indent, true, false, delim);
                        }
                    }
                }
            }
            else {
                if data.is_high_order() {
                    if let Some(lo_func) = data.lower_order_function() {
                        Self::write_function_data(stream, lo_func, indent, first_line_no_indent, false, delim);
                    }
                }
                else if data.have_id() {
                    let line = Self::quote_value(data.get_id(), data.get_id_type(), delim.string_begin_delimiter, delim.string_end_delimiter);
                    Self::write_text(stream, &line, if first_line_no_indent { 0 } else { indent });
                }
                else {
                    Self::write_text(stream, "", if first_line_no_indent { 0 } else { indent });
                }
                if data.is_question_nullable_operator_param_class() {
                    Self::write_text(stream, "?", 0);
                }
                else if data.is_exclamation_nullable_operator_param_class() {
                    Self::write_text(stream, "!", 0);
                }
                else if data.have_statement() || data.have_extern_script() {
                    if data.is_high_order() {
                        if let Some(lo_func) = data.lower_order_function() {
                            Self::write_last_comments(stream, lo_func.as_ref(), indent, false);
                        }
                    }
                    else if data.have_id() {
                        if let Some(name) = data.name() {
                            Self::write_last_comments(stream, name.as_ref(), indent, false);
                        }
                    }
                    Self::write_statement_or_extern_script(stream, data, indent, delim);
                }
                else {
                    let lbracket;
                    let rbracket;
                    let param_class = data.get_param_class_unmasked();
                    match param_class {
                        PARAM_CLASS_PARENTHESIS => {
                            lbracket = "(";
                            rbracket = ")";
                        }
                        PARAM_CLASS_BRACKET => {
                            lbracket = "[";
                            rbracket = "]";
                        }
                        PARAM_CLASS_PERIOD => {
                            lbracket = ".";
                            rbracket = &EMPTY_STRING;
                        }
                        PARAM_CLASS_COLON_COLON => {
                            lbracket = "::";
                            rbracket = &EMPTY_STRING;
                        }
                        PARAM_CLASS_POINTER => {
                            lbracket = "->";
                            rbracket = &EMPTY_STRING;
                        }
                        PARAM_CLASS_BRACKET_COLON => {
                            lbracket = "[:";
                            rbracket = ":]";
                        }
                        PARAM_CLASS_PARENTHESIS_COLON => {
                            lbracket = "(:";
                            rbracket = ":)";
                        }
                        PARAM_CLASS_ANGLE_BRACKET_COLON => {
                            lbracket = "<:";
                            rbracket = ":>";
                        }
                        PARAM_CLASS_BRACE_PERCENT => {
                            lbracket = "{%";
                            rbracket = "%}";
                        }
                        PARAM_CLASS_BRACKET_PERCENT => {
                            lbracket = "[%";
                            rbracket = "%]";
                        }
                        PARAM_CLASS_PARENTHESIS_PERCENT => {
                            lbracket = "(%";
                            rbracket = "%)";
                        }
                        PARAM_CLASS_ANGLE_BRACKET_PERCENT => {
                            lbracket = "<%";
                            rbracket = "%>";
                        }
                        PARAM_CLASS_PERIOD_STAR => {
                            lbracket = ".*";
                            rbracket = &EMPTY_STRING;
                        }
                        PARAM_CLASS_POINTER_STAR => {
                            lbracket = "->*";
                            rbracket = &EMPTY_STRING;
                        }
                        _ => {
                            lbracket = &EMPTY_STRING;
                            rbracket = &EMPTY_STRING;
                        }
                    }
                    stream.push_str(lbracket);
                    let ct = data.get_param_num();
                    let mut i = 0;
                    while i < ct {
                        if i > 0 {
                            stream.push(' ');
                        }
                        if let Some(param) = data.get_param(i) {
                            let sep = param.get_sep_char();
                            if PARAM_CLASS_PERIOD == param_class
                                    || PARAM_CLASS_POINTER == param_class
                                    || PARAM_CLASS_PERIOD_STAR == param_class
                                    || PARAM_CLASS_POINTER_STAR == param_class {
                                stream.push_str(&param.to_script_string(true));
                            }
                            else {
                                Self::write_syntax_component(stream, param, indent, true, false, delim);
                            }
                            stream.push(sep);
                        }
                        i += 1;
                    }
                    stream.push_str(rbracket);
                }
            }
        }
        else {
            if data.is_high_order() {
                if let Some(lo_func) = data.lower_order_function() {
                    Self::write_function_data(stream, lo_func, indent, first_line_no_indent, false, delim);
                }
            }
            else if data.have_id() {
                let line = Self::quote_value(data.get_id(), data.get_id_type(), delim.string_begin_delimiter, delim.string_end_delimiter);
                Self::write_text(stream, &line, if first_line_no_indent { 0 } else { indent });
            }
        }
        if is_last_of_statement {
            stream.push(data.get_sep_char());
        }
        if let Some(cmts) = data.comments() {
            for cmt in cmts.iter() {
                Self::write_text(stream, cmt, 1);
            }
        }
        Self::write_last_comments(stream, data, indent, is_last_of_statement);
    }
}
    }

    pub fn write_statement_data(stream: &mut String, data: &StatementData, indent: i32, first_line_no_indent: bool, is_last_of_statement: bool, delim: &DelimiterInfo)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        Self::write_first_comments(stream, data, indent, first_line_no_indent);
        let func_num = data.get_function_num();
        let mut scp_str = String::new();
        let mut call_data_opt: Option<&FunctionData> = None;
        if let Some(v_or_f) = data.first() {
            if let ValueOrFunction::Function(f) = v_or_f {
                if let Some(p0) = f.get_param(0) {
                    scp_str = p0.to_script_string(true);
                }
                if f.is_ternary_operator_param_class() {
                    if let Some(lo_func) = f.lower_order_function() {
                        call_data_opt = Some(lo_func.as_ref());
                    }
                }
            }
        }
        if let Some(call_data) = call_data_opt {
            //The ternary operator is represented as op1(cond)(true_val)op2(false_val)
            if call_data.have_id() && call_data.have_param_or_statement() {
                let mut handled = false;
                if func_num == 2 {
                    if let Some(v_or_f) = data.get_function(1) {
                        if let ValueOrFunction::Function(func_data) = v_or_f {
                            if func_data.have_id() && func_data.have_param_or_statement() {
                                let mut p0_str = String::new();
                                let mut f0_str = String::new();
                                if let Some(p0) = call_data.get_param(0) {
                                    p0_str = p0.to_script_string(true);
                                }
                                if let Some(f0) = func_data.get_param(0) {
                                    f0_str = f0.to_script_string(true);
                                }
                                let mut line = format!("{0} {1} {2}", p0_str, call_data.get_id(), &scp_str);
                                line = format!("{0} {1} {2}", line, func_data.get_id(), f0_str);
                                Self::write_text(stream, &line, if first_line_no_indent { 0 } else { indent });
                                handled = true;
                            }
                        }
                    }
                }
                if !handled {
                    Self::write_text(stream, "/*[?:]*/", if first_line_no_indent { 0 } else { indent });
                }
            }
        }
        else {
            let mut last_func_no_param = false;
            let mut last_func_no_statement = false;
            let mut i = 0;
            while i < func_num {
                if let Some(v_or_f) = data.get_function(i) {
                    match v_or_f {
                        ValueOrFunction::Value(val) => {
                            let mut no_indent = false;
                            if i > 0 {
                                if last_func_no_param && last_func_no_statement {
                                    Self::write_text(stream, " ", 0);
                                    no_indent = true;
                                }
                                else if last_func_no_statement {
                                    no_indent = true;
                                }
                                else {
                                    Self::write_line(stream, "", 0);
                                    no_indent = false;
                                }
                            }
                            Self::write_value_data(stream, val, indent, first_line_no_indent && i == 0 || no_indent, false);
                            last_func_no_param = true;
                            last_func_no_statement = true;
                        }
                        ValueOrFunction::Function(func) => {
                            let func_no_param = !func.is_high_order() && (!func.have_param() || func.is_member_param_class());
                            let func_no_statement = !func.have_statement() && !func.have_extern_script();
                            let mut no_indent = false;
                            if i > 0 {
                                if last_func_no_param && last_func_no_statement {
                                    Self::write_text(stream, " ", 0);
                                    no_indent = true;
                                }
                                else if last_func_no_statement && func_no_statement {
                                    no_indent = true;
                                }
                                else {
                                    Self::write_line(stream, "", 0);
                                    no_indent = false;
                                }
                            }
                            Self::write_function_data(stream, func, indent, first_line_no_indent && i == 0 || no_indent, false, delim);
                            last_func_no_param = func_no_param;
                            last_func_no_statement = func_no_statement;
                        }
                    }
                }
                i += 1;
            }
        }
        if is_last_of_statement {
            stream.push(data.get_sep_char());
        }
        Self::write_last_comments(stream, data, indent, is_last_of_statement);
    }
}
    }

    fn need_quote(str: &str) -> bool
    {
        let escape_chars: &str = " \t\r\n{}()[],;~`!%^&*-+=|:<>?/#\\'\"";
        if str.len() == 0 {
            return true;
        }
        let mut have_dot = false;
        let mut not_num = false;
        for c in str.chars() {
            if escape_chars.find(c).is_none() {
                return true;
            }
            if c == '.' {
                have_dot = true;
            }
            else if !not_num && !c.is_digit(10) {
                not_num = true;
            }
            if have_dot && not_num {
                return true;
            }
        }
        return false;
    }

    fn quote_str_with_str_def_delim(str: &str, _type: i32) -> String
    {
        return Self::quote_value(str, _type, "\"", "\"");
    }
    fn quote_value(str: &str, _type: i32, str_begin_delim: &str, str_end_delim: &str) -> String
    {
        match _type {
            DOLLAR_STRING_TOKEN => {
                    return String::from("$") + &Self::quote_string(str, str_begin_delim, str_end_delim);
                }
            STRING_TOKEN => {
                    return Self::quote_string(str, str_begin_delim, str_end_delim);
                }
            NUM_TOKEN | ID_TOKEN => {
                return String::from(str);
            }
            _ => {
                return String::from(str);
            }
        }
    }
    fn quote_string(str: &str, str_begin_delim: &str, str_end_delim: &str) -> String
    {
        let mut sb = String::new();
        sb.push_str(str_begin_delim);
        for c in str.chars() {
            match c {
                '\\' => {
                    sb.push_str("\\\\");
                }
                '"' => {
                    sb.push_str("\\\"");
                }
                '\'' => {
                    sb.push_str("\\\'");
                }
                '\0' => {
                    sb.push_str("\\\0");
                }
                _ => {
                    sb.push(c);
                }
            }
        }
        sb.push_str(str_end_delim);
        return sb;
    }

    fn get_func_str_with_str_def_delim(data: &FunctionData, include_comment: bool) -> String
    {
        return Self::get_func_str(data, include_comment, &String::from("\""), &String::from("\""));
    }
    fn get_func_str(data: &FunctionData, include_comment: bool, str_begin_delim: &String, str_end_delim: &String) -> String
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        let line_no = "";// format!("/* {0} */", data.get_line());
        let mut line = String::new();
        if data.is_high_order() {
            if let Some(func) = data.lower_order_function() {
                line = Self::get_func_str(func.as_ref(), include_comment, &str_begin_delim, &str_end_delim);
            }
        }
        else if data.have_id() {
            if data.have_param_class_infix_flag() {
                let op = String::from("`") + data.get_id();
                line = Self::quote_value(&op, data.get_id_type(), &str_begin_delim, &str_end_delim);
            }
            else {
                line = Self::quote_value(data.get_id(), data.get_id_type(), &str_begin_delim, &str_end_delim);
            }
        }
        if data.have_param_or_statement() {
            if data.is_operator_param_class() {
                match data.get_param_num() {
                    1 => {
                        let mut p1 = String::new();
                        if let Some(param) = data.get_param(0) {
                            match param {
                                SyntaxComponent::Value(v) => {
                                    p1 = v.to_script_string(include_comment);
                                }
                                SyntaxComponent::Function(f) => {
                                    p1 = f.to_script_string(include_comment);
                                }
                                SyntaxComponent::Statement(s) => {
                                    p1 = s.to_script_string(include_comment);
                                }
                            }
                        }
                        return format!("{0} {1}", line, p1);
                    }
                    2 => {
                        let mut p1 = String::new();
                        if let Some(param) = data.get_param(0) {
                            match param {
                                SyntaxComponent::Value(v) => {
                                    p1 = v.to_script_string(include_comment);
                                }
                                SyntaxComponent::Function(f) => {
                                    p1 = f.to_script_string(include_comment);
                                }
                                SyntaxComponent::Statement(s) => {
                                    p1 = s.to_script_string(include_comment);
                                }
                            }
                        }
                        let mut p2 = String::new();
                        if let Some(param) = data.get_param(1) {
                            match param {
                                SyntaxComponent::Value(v) => {
                                    p2 = v.to_script_string(include_comment);
                                }
                                SyntaxComponent::Function(f) => {
                                    p2 = f.to_script_string(include_comment);
                                }
                                SyntaxComponent::Statement(s) => {
                                    p2 = s.to_script_string(include_comment);
                                }
                            }
                        }
                        return format!("{0} {1} {2}", p1, line, p2);
                    }
                    _ => {
                        return line;
                    }
                }
            }
            else if data.is_question_nullable_operator_param_class() {
                if let Some(param) = data.get_param(0) {
                    return format!("{0}{1}?", param.to_script_string(include_comment), line);
                }
                else {
                    return EMPTY_STRING.clone();
                }
            }
            else if data.is_exclamation_nullable_operator_param_class() {
                if let Some(param) = data.get_param(0) {
                    return format!("{0}{1}!", param.to_script_string(include_comment), line);
                }
                else {
                    return EMPTY_STRING.clone();
                }
            }
            else {
                let lbracket;
                let rbracket;
                let param_class = data.get_param_class_unmasked();
                match param_class {
                    PARAM_CLASS_PARENTHESIS => {
                        lbracket = "(";
                        rbracket = ")";
                    }
                    PARAM_CLASS_BRACKET => {
                        lbracket = "[";
                        rbracket = "]";
                    }
                    PARAM_CLASS_PERIOD => {
                        lbracket = ".";
                        rbracket = &EMPTY_STRING;
                    }
                    PARAM_CLASS_COLON_COLON => {
                        lbracket = "::";
                        rbracket = &EMPTY_STRING;
                    }
                    PARAM_CLASS_POINTER => {
                        lbracket = "->";
                        rbracket = &EMPTY_STRING;
                    }
                    PARAM_CLASS_STATEMENT => {
                        lbracket = "{";
                        rbracket = "}";
                    }
                    PARAM_CLASS_EXTERN_SCRIPT => {
                        lbracket = "{:";
                        rbracket = ":}";
                    }
                    PARAM_CLASS_BRACKET_COLON => {
                        lbracket = "[:";
                        rbracket = ":]";
                    }
                    PARAM_CLASS_PARENTHESIS_COLON => {
                        lbracket = "(:";
                        rbracket = ":)";
                    }
                    PARAM_CLASS_ANGLE_BRACKET_COLON => {
                        lbracket = "<:";
                        rbracket = ":>";
                    }
                    PARAM_CLASS_BRACE_PERCENT => {
                        lbracket = "{%";
                        rbracket = "%}";
                    }
                    PARAM_CLASS_BRACKET_PERCENT => {
                        lbracket = "[%";
                        rbracket = "%]";
                    }
                    PARAM_CLASS_PARENTHESIS_PERCENT => {
                        lbracket = "(%";
                        rbracket = "%)";
                    }
                    PARAM_CLASS_ANGLE_BRACKET_PERCENT => {
                        lbracket = "<%";
                        rbracket = "%>";
                    }
                    PARAM_CLASS_PERIOD_STAR => {
                        lbracket = ".*";
                        rbracket = &EMPTY_STRING;
                    }
                    PARAM_CLASS_POINTER_STAR => {
                        lbracket = "->*";
                        rbracket = &EMPTY_STRING;
                    }
                    _ => {
                        lbracket = &EMPTY_STRING;
                        rbracket = &EMPTY_STRING;
                    }
                }
                let mut stream = String::new();
                stream.push_str(lbracket);
                if param_class == PARAM_CLASS_EXTERN_SCRIPT {
                    if let Some(id) = data.get_param_id(0) {
                        stream.push_str(id);
                    }
                }
                else {
                    let ct = data.get_param_num();
                    let mut i = 0;
                    while i < ct {
                        if data.have_param() && i > 0 {
                            stream.push_str(",");
                        }
                        if let Some(param) = data.get_param(i) {
                            if PARAM_CLASS_PERIOD == param_class
                                || PARAM_CLASS_POINTER == param_class
                                || PARAM_CLASS_PERIOD_STAR == param_class
                                || PARAM_CLASS_POINTER_STAR == param_class {
                                stream.push_str(&param.to_script_string(include_comment));
                            }
                            else {
                                stream.push_str(&param.to_script_string(include_comment));
                            }
                        }
                        if data.have_statement() {
                            stream.push_str(";");
                        }
                        i += 1;
                    }
                }
                stream.push_str(rbracket);
                return format!("{0}{1}{2}", line_no, line, stream);
            }
        }
        else {
            return format!("{0}{1}", line_no, line);
        }
    }
    else {
        return EMPTY_STRING.clone();
    }
}
    }

    fn write_statement_or_extern_script(stream: &mut String, data: &FunctionData, _indent: i32, delim: &DelimiterInfo)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        let mut indent = _indent;
        if data.have_statement() {
            Self::write_text(stream, &EMPTY_STRING, 0);
            Self::write_line(stream, "{", indent);
            indent += 1;

            let ct = data.get_param_num();
            let mut i = 0;
            while i < ct {
                if let Some(temp_data) = data.get_param(i) {
                    Self::write_syntax_component(stream, temp_data, indent, false, true, delim);
                }
                i += 1;
            }

            indent -= 1;
            Self::write_text(stream, "}", indent);
        }
        else if data.have_extern_script() {
            Self::write_line(stream, "", 0);
            if let Some(script) = data.get_param_id(0) {
                if !script.find('\n').is_none() {
                    Self::write_line(stream, delim.script_begin_delimiter, indent);
                }
                else {
                    Self::write_text(stream, delim.script_begin_delimiter, indent);
                }
                stream.push_str(script);
                if script.chars().last() == Some('\n') {
                    Self::write_text(stream, delim.script_end_delimiter, indent);
                }
                else {
                    stream.push_str(delim.script_end_delimiter);
                }
            }
        }
    }
}
    }

    fn write_first_comments(stream: &mut String, data: &dyn ISyntaxComponent, indent: i32, first_line_no_indent: bool)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        let mut is_first = true;
        let mut have_comments = false;
        let mut new_line = false;
        if let Some(f_cmts) = data.first_comments() {
            for  cmt in f_cmts.iter() {
                if is_first && !data.first_comment_on_new_line() {
                    Self::write_text(stream, cmt, if first_line_no_indent { 0 } else { indent });
                }
                else {
                    Self::write_line(stream, cmt, if is_first && first_line_no_indent { 0 } else { indent });
                    new_line = true;
                }
                is_first = false;
                have_comments = true;
            }
        }
        if have_comments && !new_line {
            //Line-leading comments must be followed by a newline, otherwise they may comment out the code.
            Self::write_line(stream, "", 0);
        }
    }
}
    }

    fn write_last_comments(stream: &mut String, data: &dyn ISyntaxComponent, indent: i32, is_last_of_statement: bool)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        let mut len = 0;
        if let Some(l_cmts) = data.last_comments() {
            len = l_cmts.len();
        }
        if len > 0 {
            if data.last_comment_on_new_line() {
                Self::write_line(stream, &EMPTY_STRING, 0);
            }
            let mut is_first = true;
            if let Some(l_cmts) = data.last_comments() {
                for cmt in l_cmts.iter() {
                    if is_first && !data.last_comment_on_new_line() {
                        Self::write_text(stream, cmt, 1);
                    }
                    else {
                        Self::write_text(stream, cmt, indent);
                    }
                    if is_last_of_statement {
                        Self::write_line(stream, &EMPTY_STRING, 0);
                    }
                    is_first = false;
                }
            }
        }
        else if is_last_of_statement {
            Self::write_line(stream, &EMPTY_STRING, 0);
        }
    }
}
    }

    fn write_text(stream: &mut String, line: &str, indent: i32)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        let mut i = 0;
        while i < indent {
            stream.push('\t');
            i += 1;
        }
        stream.push_str(line);
    }
}
    }

    fn write_line(stream: &mut String, line: &str, indent: i32)
    {
cfg_if! {
    if #[cfg(feature = "full_version")] {
        Self::write_text(stream, line, indent);
        stream.push_str("\r\n");
    }
}
    }

    fn read_byte(bytes: &[u8], cur_code_index: usize) -> u8
    {
        if cur_code_index < bytes.len() {
            return bytes[cur_code_index];
        }
        else {
            return 0;
        }
    }
    fn read_identifier(identifiers: &Vec<String>, cur_id_index: usize) -> &String
    {
        if cur_id_index < identifiers.len() {
            return &identifiers[cur_id_index];
        }
        else {
            return &EMPTY_STRING;
        }
    }
    fn is_binary_end_code(end_code_start: u8, code: u8, sep: &mut u8) -> bool
    {
        let ret: bool;
        if code >= end_code_start && code <= end_code_start + SEPARATOR_SEMICOLON as u8 - SEPARATOR_NOTHING as u8 {
            *sep = code - end_code_start + SEPARATOR_NOTHING as u8;
            ret = true;
        }
        else {
            *sep = 0;
            ret = false;
        }
        return ret;
    }
    fn read_binary(bytes: &[u8], start: usize, count: usize, identifiers: &mut Vec<String>) -> Vec<SyntaxComponent>
    {
        let mut infos: Vec<SyntaxComponent> = Vec::new();
        let mut cur_code_index = 0;
        let mut cur_id_index = 0;
        while cur_code_index < count {
            while cur_code_index < count {
                let b = bytes[start + cur_code_index];
                if b == DSL_BINARY_CODE_BEGIN_STATEMENT as u8 || b == DSL_BINARY_CODE_BEGIN_FUNCTION as u8 || b == DSL_BINARY_CODE_BEGIN_VALUE as u8 {
                    break;
                }
                cur_code_index += 1;
            }
            if cur_code_index < count {
                if let Some(info) = Self::read_binary2(bytes, start, &mut cur_code_index, identifiers, &mut cur_id_index) {
                    if info.is_valid() {
                        infos.push(info);
                    }
                }
            }
        }
        return infos;
    }
    fn read_binary2(bytes: &[u8], start: usize, cur_code_index: &mut usize, identifiers: &mut Vec<String>, cur_id_index: &mut usize) -> Option<SyntaxComponent>
    {
        let mut ret: Option<SyntaxComponent> = None;
        let code = Self::read_byte(bytes, start + *cur_code_index);
        if code == DSL_BINARY_CODE_BEGIN_VALUE as u8 {
            let mut data = ValueData::new();
            Self::read_binary_value(bytes, start, cur_code_index, identifiers, cur_id_index, &mut data);
            ret = Some(SyntaxComponent::Value(data));
        }
        else if code == DSL_BINARY_CODE_BEGIN_FUNCTION as u8 {
            let mut data = FunctionData::new();
            Self::read_binary_function(bytes, start, cur_code_index, identifiers, cur_id_index, &mut data);
            ret = Some(SyntaxComponent::Function(data));
        }
        else if code == DSL_BINARY_CODE_BEGIN_STATEMENT as u8 {
            let mut data = StatementData::new();
            Self::read_binary_statement(bytes, start, cur_code_index, identifiers, cur_id_index, &mut data);
            ret = Some(SyntaxComponent::Statement(data));
        }
        return ret;
    }
    fn read_binary_value(bytes: &[u8], start: usize, cur_code_index: &mut usize, identifiers: &mut Vec<String>, cur_id_index: &mut usize, data: &mut ValueData)
    {
        let mut code = Self::read_byte(bytes, start + *cur_code_index);
        *cur_code_index += 1;
        if code == DSL_BINARY_CODE_BEGIN_VALUE as u8 {
            code = Self::read_byte(bytes, start + *cur_code_index);
            if code >= DSL_BINARY_CODE_VALUE_TYPE_BEGIN as u8 {
                *cur_code_index += 1;
                data.set_type(code as i32 - DSL_BINARY_CODE_VALUE_TYPE_BEGIN);
                data.set_id(Self::read_identifier(identifiers, *cur_id_index).clone());
                *cur_id_index += 1;
                let mut byte_count = 0;
                let v = Self::read_7bit_encoded_int(bytes, start + *cur_code_index, &mut byte_count);
                data.set_line(v);
                *cur_code_index += byte_count;
            }
            code = Self::read_byte(bytes, start + *cur_code_index);
            let mut sep = 0;
            if Self::is_binary_end_code(DSL_BINARY_CODE_END_VALUE as u8, code, &mut sep) {
                data.set_seperator(sep as i32);
                *cur_code_index += 1;
            }
        }
    }
    fn read_binary_function(bytes: &[u8], start: usize, cur_code_index: &mut usize, identifiers: &mut Vec<String>, cur_id_index: &mut usize, data: &mut FunctionData)
    {
        let mut code = Self::read_byte(bytes, start + *cur_code_index);
        *cur_code_index += 1;
        if code == DSL_BINARY_CODE_BEGIN_FUNCTION as u8 {
            code = Self::read_byte(bytes, start + *cur_code_index);
            if code >= DSL_BINARY_CODE_PARAM_OR_EXTERN_CLASS_BEGIN as u8 {
                *cur_code_index += 1;
                data.set_param_class(code as i32 - DSL_BINARY_CODE_PARAM_OR_EXTERN_CLASS_BEGIN);
                if data.have_param_or_statement() {
                    let mut byte_count = 0;
                    let v = Self::read_7bit_encoded_int(bytes, start + *cur_code_index, &mut byte_count);
                    *cur_code_index += byte_count;
                    if let Some(ps) = data.params_mut() {
                        if v as usize > ps.len() {
                            ps.reserve(v as usize - ps.len());
                        }
                    }
                }
            }
            code = Self::read_byte(bytes, start + *cur_code_index);
            if code == DSL_BINARY_CODE_BEGIN_VALUE as u8 {
                let mut value_data = ValueData::new();
                Self::read_binary_value(bytes, start, cur_code_index, identifiers, cur_id_index, &mut value_data);
                data.set_name(Some(Box::new(value_data)));
            }
            else if code == DSL_BINARY_CODE_BEGIN_FUNCTION as u8 {
                let mut call_data = FunctionData::new();
                Self::read_binary_function(bytes, start, cur_code_index, identifiers, cur_id_index, &mut call_data);
                data.set_lower_order_function(Some(Box::new(call_data)));
            }
            loop {
                code = Self::read_byte(bytes, start + *cur_code_index);
                let mut sep = 0;
                if Self::is_binary_end_code(DSL_BINARY_CODE_END_FUNCTION as u8, code, &mut sep) {
                    data.set_seperator(sep as i32);
                    *cur_code_index += 1;
                    break;
                }
                else {
                    let syntax_data = Self::read_binary2(bytes, start, cur_code_index, identifiers, cur_id_index);
                    if let Some(syn) = syntax_data {
                        data.add_syntax_component_param(syn);
                    }
                    else {
                        break;
                    }
                }
            }
        }
    }
    fn read_binary_statement(bytes: &[u8], start: usize, cur_code_index: &mut usize, identifiers: &mut Vec<String>, cur_id_index: &mut usize, data: &mut StatementData)
    {
        let mut code = Self::read_byte(bytes, start + *cur_code_index);
        *cur_code_index += 1;
        if code == DSL_BINARY_CODE_BEGIN_STATEMENT as u8 {
            let mut byte_count = 0;
            let v = Self::read_7bit_encoded_int(bytes, start + *cur_code_index, &mut byte_count);
            *cur_code_index += byte_count;
            if let Some(fs) = data.functions_mut() {
                if v as usize > fs.len() {
                    fs.reserve(v as usize - fs.len());
                }
            }
            loop {
                code = Self::read_byte(bytes, start + *cur_code_index);
                let mut sep = 0;
                if code == DSL_BINARY_CODE_BEGIN_VALUE as u8 {
                    let mut val_data = ValueData::new();
                    Self::read_binary_value(bytes, start, cur_code_index, identifiers, cur_id_index, &mut val_data);
                    data.add_function(ValueOrFunction::Value(val_data));
                }
                else if code == DSL_BINARY_CODE_BEGIN_FUNCTION as u8 {
                    let mut func_data = FunctionData::new();
                    Self::read_binary_function(bytes, start, cur_code_index, identifiers, cur_id_index, &mut func_data);
                    data.add_function(ValueOrFunction::Function(func_data));
                }
                else if Self::is_binary_end_code(DSL_BINARY_CODE_END_STATEMENT as u8, code, &mut sep) {
                    data.set_seperator(sep as i32);
                    *cur_code_index += 1;
                    break;
                }
                else {
                    break;
                }
            }
        }
    }
    //---------------------------------------------------------------------------------------------
cfg_if! {
    if #[cfg(feature = "full_version")] {
    fn get_binary_end_code(end_code: u8, sep: i32) -> u8
    {
        if sep >= SEPARATOR_NOTHING && sep <= SEPARATOR_SEMICOLON {
            return end_code + (sep - SEPARATOR_NOTHING) as u8;
        }
        else {
            return end_code;
        }
    }
    fn write_binary(stream: &mut Cursor<Vec<u8>>, identifiers: &mut Vec<String>, data: &SyntaxComponent)
    {
        match data {
            SyntaxComponent::Value(val) => {
                Self::write_binary_value(stream, identifiers, val);
            }
            SyntaxComponent::Function(call) => {
                Self::write_binary_function(stream, identifiers, call);
            }
            SyntaxComponent::Statement(statement) => {
                Self::write_binary_statement(stream, identifiers, statement);
            }
        }
    }
    fn write_binary_value(stream: &mut Cursor<Vec<u8>>, identifiers: &mut Vec<String>, data: &ValueData)
    {
        let _ = stream.write(&[DSL_BINARY_CODE_BEGIN_VALUE as u8]);
        let _ = stream.write(&[(DSL_BINARY_CODE_VALUE_TYPE_BEGIN + data.get_id_type()) as u8]);
        identifiers.push(data.get_id().clone());
        Self::write_7bit_encoded_int(stream, data.get_line() as usize);
        let _ = stream.write(&[Self::get_binary_end_code(DSL_BINARY_CODE_END_VALUE as u8, data.get_seperator())]);
    }
    fn write_binary_function(stream: &mut Cursor<Vec<u8>>, identifiers: &mut Vec<String>, data: &FunctionData)
    {
        let _ = stream.write(&[DSL_BINARY_CODE_BEGIN_FUNCTION as u8]);
        let _ = stream.write(&[(DSL_BINARY_CODE_PARAM_OR_EXTERN_CLASS_BEGIN + data.get_param_class()) as u8]);
        if data.have_param_or_statement() {
            Self::write_7bit_encoded_int(stream, data.get_param_num());
        }
        if data.is_high_order() {
            if let Some(func) = data.lower_order_function() {
                Self::write_binary_function(stream, identifiers, func);
            }
        }
        else if let Some(name) = data.name() {
            Self::write_binary_value(stream, identifiers, name);
        }
        if let Some(ps) = data.params() {
            for syntax_data in ps.iter() {
                Self::write_binary(stream, identifiers, syntax_data);
            }
        }
        let _ = stream.write(&[Self::get_binary_end_code(DSL_BINARY_CODE_END_FUNCTION as u8, data.get_seperator())]);
    }
    fn write_binary_statement(stream: &mut Cursor<Vec<u8>>, identifiers: &mut Vec<String>, data: &StatementData)
    {
        let _ = stream.write(&[DSL_BINARY_CODE_BEGIN_STATEMENT as u8]);
        Self::write_7bit_encoded_int(stream, data.get_function_num());
        if let Some(funcs) = data.functions() {
            for f in funcs {
                match f {
                    ValueOrFunction::Value(val) => {
                        Self::write_binary_value(stream, identifiers, val);
                    }
                    ValueOrFunction::Function(func) => {
                        Self::write_binary_function(stream, identifiers, func);
                    }
                }
            }
        }
        let _ = stream.write(&[Self::get_binary_end_code(DSL_BINARY_CODE_END_STATEMENT as u8, data.get_seperator())]);
    }
    }
}
}
