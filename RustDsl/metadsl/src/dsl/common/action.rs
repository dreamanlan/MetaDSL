use std::collections::HashMap;
use std::collections::VecDeque;
use std::vec::Vec;
use std::cell::RefCell;

use crate::dsl::common::log::DslLogCell;
use crate::dsl::parser::token::{DslToken, DslTokenCell};
use crate::dsl::ValueOrFunction;
use crate::dsl::{
    ISyntaxComponent,
    SyntaxComponent,
    ValueData,
    FunctionData,
    StatementData
};
use crate::dsl;

/*
* Memo: Why use reduction instead of delayed one-time construction
* 1. We have tried to use a temporary structure such as SyntaxMaterial to collect data during the syntax parsing process, and then construct the statement when the statement is completed.
* 2. The temporary structure is very similar to the final semantic data structure. It also needs to represent the recursive structure and be associated with the existing semantic data. The code is repeated and the logic is not clear enough.
* 3. The reduction method has tried its best to reuse the instances constructed in the grammar parsing, and basically does not cause additional memory usage.
* 4. In the reduction mode, the final memory usage is linearly related to the script complexity, so there is no need to worry about taking up too much memory.
* 5. The definition of semantic data takes degradation situations into consideration and tries not to occupy additional space except for necessary data.
*/
pub const OPERATOR_CATEGORY_NORMAL: i32 = 0;
pub const OPERATOR_CATEGORY_TERNARY: i32 = 1;
pub const OPERATOR_CATEGORY_MAXNUM: i32 = 2;

pub const PAIR_TYPE_NONE: i32 = 0;
pub const PAIR_TYPE_QUESTION_COLON: i32 = 1;
pub const PAIR_TYPE_PARENTHESIS: i32 = 2;
pub const PAIR_TYPE_BRACKET: i32 = 3;
pub const PAIR_TYPE_BRACE: i32 = 4;
pub const PAIR_TYPE_BRACKET_COLON: i32 = 5;
pub const PAIR_TYPE_PARENTHESIS_COLON: i32 = 6;
pub const PAIR_TYPE_ANGLE_BRACKET_COLON: i32 = 7;
pub const PAIR_TYPE_BRACE_PERCENT: i32 = 8;
pub const PAIR_TYPE_BRACKET_PERCENT: i32 = 9;
pub const PAIR_TYPE_PARENTHESIS_PERCENT: i32 = 10;
pub const PAIR_TYPE_ANGLE_BRACKET_PERCENT: i32 = 11;
pub const PAIR_TYPE_MAXNUM: i32 = 12;

pub type DslActionCell<'a> = RefCell<DslAction<'a>>;

pub type TokenCanEatCharDelegation<'a> = dyn Fn(&mut String, char) -> bool + 'a;
pub type GetTokenDelegation<'a> = dyn Fn(&DslActionCell, &mut DslToken, &mut str, &mut i16, &mut i32) -> bool + 'a;
pub type BeforeAddFunctionDelegation<'a> = dyn Fn(&mut DslAction) -> bool + 'a;
pub type AddFunctionDelegation<'a> = dyn Fn(&mut DslAction) -> bool + 'a;
pub type BeforeEndStatementDelegation<'a> = dyn Fn(&mut DslAction) -> bool + 'a;
pub type EndStatementDelegation<'a> = dyn Fn(&mut DslAction, &mut StatementData) -> bool + 'a;
pub type BeforeBuildOperatorDelegation<'a> = dyn Fn(&mut DslAction, i32, String, Option<&mut StatementData>) -> bool + 'a;
pub type BuildOperatorDelegation<'a> = dyn Fn(&mut DslAction, i32, String, &mut StatementData) -> bool + 'a;
pub type SetFunctionIdDelegation<'a> = dyn Fn(&mut DslAction) -> bool + 'a;
pub type BeforeBuildHighOrderDelegation<'a> = dyn Fn(&mut DslAction) -> bool + 'a;
pub type BuildHighOrderDelegation<'a> = dyn Fn(&mut DslAction) -> bool + 'a;

pub type TokenCanEatCharDelegationBox<'a> = Box<TokenCanEatCharDelegation<'a>>;
pub type GetTokenDelegationBox<'a> = Box<GetTokenDelegation<'a>>;
pub type BeforeAddFunctionDelegationBox<'a> = Box<BeforeAddFunctionDelegation<'a>>;
pub type AddFunctionDelegationBox<'a> = Box<AddFunctionDelegation<'a>>;
pub type BeforeEndStatementDelegationBox<'a> = Box<BeforeEndStatementDelegation<'a>>;
pub type EndStatementDelegationBox<'a> = Box<EndStatementDelegation<'a>>;
pub type BeforeBuildOperatorDelegationBox<'a> = Box<BeforeBuildOperatorDelegation<'a>>;
pub type BuildOperatorDelegationBox<'a> = Box<BuildOperatorDelegation<'a>>;
pub type SetFunctionIdDelegationBox<'a> = Box<SetFunctionIdDelegation<'a>>;
pub type BeforeBuildHighOrderDelegationBox<'a> = Box<BeforeBuildHighOrderDelegation<'a>>;
pub type BuildHighOrderDelegationBox<'a> = Box<BuildHighOrderDelegation<'a>>;

struct SemanticInfo
{
    token: String,
    value: i32
}

impl SemanticInfo
{
    pub fn new(tok: &str, val: i32) -> Self
    {
        Self
        {
            token: String::from(tok),
            value: val
        }
    }
}

pub struct DslAction<'a>
{
    m_log: &'a DslLogCell<'a>,
    m_dsl_token: Option<&'a DslTokenCell<'a>>,

    m_on_before_add_function: Option<&'a BeforeAddFunctionDelegationBox<'a>>,
    m_on_add_function: Option<&'a AddFunctionDelegationBox<'a>>,
    m_on_before_end_statement: Option<&'a BeforeEndStatementDelegationBox<'a>>,
    m_on_end_statement: Option<&'a EndStatementDelegationBox<'a>>,
    m_on_before_build_operator: Option<&'a BeforeBuildOperatorDelegationBox<'a>>,
    m_on_build_operator: Option<&'a BuildOperatorDelegationBox<'a>>,
    m_on_set_function_id: Option<&'a SetFunctionIdDelegationBox<'a>>,
    m_on_before_build_high_order: Option<&'a BeforeBuildHighOrderDelegationBox<'a>>,
    m_on_build_high_order: Option<&'a BuildHighOrderDelegationBox<'a>>,

    m_script_datas: Vec<SyntaxComponent>,
    m_semantic_stack: VecDeque<SemanticInfo>,
    m_statement_semantic_stack: VecDeque<StatementData>,
    m_pair_type_stack: VecDeque<u32>,
    m_name_tags: HashMap<String, u32>,
}

impl<'a> DslAction<'a>
{
    pub fn new(log: &'a DslLogCell<'a>) -> Self
    {
        Self {
            m_log: log,
            m_dsl_token: None,
            m_script_datas: Vec::new(),

            m_semantic_stack: VecDeque::new(),
            m_statement_semantic_stack: VecDeque::new(),
            m_pair_type_stack: VecDeque::new(),
            m_name_tags: HashMap::new(),

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

    pub fn get_script_datas(&mut self) -> &mut Vec<SyntaxComponent>
    {
        return &mut self.m_script_datas;
    }
    pub fn info(&self, info: &str)
    {
        self.m_log.borrow().info(info);
    }
    pub fn error(&self, info: &str)
    {
        self.m_log.borrow_mut().error(info);
    }

    pub fn on_before_add_function(&self) -> &Option<&BeforeAddFunctionDelegationBox>
    {
        return &self.m_on_before_add_function;
    }
    pub fn set_on_before_add_function(&mut self, value: &'a BeforeAddFunctionDelegationBox)
    {
        self.m_on_before_add_function = Some(value);
    }
    pub fn on_add_function(&self) -> &Option<&AddFunctionDelegationBox>
    {
        return &self.m_on_add_function;
    }
    pub fn set_on_add_function(&mut self, value: &'a AddFunctionDelegationBox)
    {
        self.m_on_add_function = Some(value);
    }
    pub fn on_before_end_statement(&self) -> Option<&'a BeforeEndStatementDelegationBox>
    {
        return self.m_on_before_end_statement;
    }
    pub fn set_on_before_end_statement(&mut self, value: &'a BeforeEndStatementDelegationBox)
    {
        self.m_on_before_end_statement = Some(value);
    }
    pub fn on_end_statement(&self) -> &Option<&EndStatementDelegationBox>
    {
        return &self.m_on_end_statement;
    }
    pub fn set_on_end_statement(&mut self, value: &'a EndStatementDelegationBox)
    {
        self.m_on_end_statement = Some(value);
    }
    pub fn on_before_build_operator(&self) -> &Option<&BeforeBuildOperatorDelegationBox>
    {
        return &self.m_on_before_build_operator;
    }
    pub fn set_on_before_build_operator(&mut self, value: &'a BeforeBuildOperatorDelegationBox)
    {
        self.m_on_before_build_operator = Some(value);
    }
    pub fn on_build_operator(&self) -> &Option<&BuildOperatorDelegationBox>
    {
        return &self.m_on_build_operator;
    }
    pub fn set_on_build_operator(&mut self, value: &'a BuildOperatorDelegationBox)
    {
        self.m_on_build_operator = Some(value);
    }
    pub fn on_set_function_id(&self) -> &Option<&SetFunctionIdDelegationBox>
    {
        return &self.m_on_set_function_id;
    }
    pub fn set_on_set_function_id(&mut self, value: &'a SetFunctionIdDelegationBox)
    {
        self.m_on_set_function_id = Some(value);
    }
    pub fn on_before_build_high_order(&self) -> &Option<&BeforeBuildHighOrderDelegationBox>
    {
        return &self.m_on_before_build_high_order;
    }
    pub fn set_on_before_build_high_order(&mut self, value: &'a BeforeBuildHighOrderDelegationBox)
    {
        self.m_on_before_build_high_order = Some(value);
    }
    pub fn on_build_high_order(&self) -> &Option<&BuildHighOrderDelegationBox>
    {
        return &self.m_on_build_high_order;
    }
    pub fn set_on_build_high_order(&mut self, value: &'a BuildHighOrderDelegationBox)
    {
        self.m_on_build_high_order = Some(value);
    }

    pub fn predict(&self, _production_number: i16, _nonterminal: i16, _token: i16, _level: i32, _last_tok: &str, _last_line_no: i32, _cur_tok: &str, _line_no: i32)
    {
        //mLog.Log("{0} [production: {1} nonterminal: {2} token symbol: {3} last token: {4} line: {5} cur token: {6} line: {7} ]", Dsl.Parser.DslString.GetProductionName(productionNumber), productionNumber, nonterminal, Dsl.Parser.DslString.GetSymbolName(token), lastTok, lastLineNo, curTok, lineNo);
    }
    pub fn execute(&mut self, number: i32)
    {
        match number {
            1 => { self.mark_separator(); }
            2 => { self.end_statement(); }
            3 => { self.push_id(); }
            4 => { self.build_operator(); }
            5 => { self.build_first_ternary_operator(); }
            6 => { self.build_second_ternary_operator(); }
            7 => { self.begin_statement(); }
            8 => { self.add_function(); }
            9 => { self.set_function_id(); }
            10 => { self.build_nullable_operator(); }
            11 => { self.mark_parenthesis_param(); }
            12 => { self.mark_parenthesis_param_end(); }
            13 => { self.build_high_order_function(); }
            14 => { self.mark_bracket_param(); }
            15 => { self.mark_bracket_param_end(); }
            16 => { self.mark_statement(); }
            17 => { self.mark_statement_end(); }
            18 => { self.mark_extern_script(); }
            19 => { self.set_extern_script(); }
            20 => { self.mark_bracket_colon_param(); }
            21 => { self.mark_bracket_colon_param_end(); }
            22 => { self.mark_parenthesis_colon_param(); }
            23 => { self.mark_parenthesis_colon_param_end(); }
            24 => { self.mark_angle_bracket_colon_param(); }
            25 => { self.mark_angle_bracket_colon_param_end(); }
            26 => { self.mark_brace_percent_param(); }
            27 => { self.mark_brace_percent_param_end(); }
            28 => { self.mark_bracket_percent_param(); }
            29 => { self.mark_bracket_percent_param_end(); }
            30 => { self.mark_parenthesis_percent_param(); }
            31 => { self.mark_parenthesis_percent_param_end(); }
            32 => { self.mark_angle_bracket_percent_param(); }
            33 => { self.mark_angle_bracket_percent_param_end(); }
            34 => { self.mark_colon_colon_param(); }
            35 => { self.mark_period_param(); }
            36 => { self.mark_pointer_param(); }
            37 => { self.mark_period_star_param(); }
            38 => { self.mark_pointer_star_param(); }
            39 => { self.push_str(); }
            40 => { self.push_num(); }
            41 => { self.push_dollar_str(); }
            42 => { self.push_comma(); }
            43 => { self.push_semi_colon(); }
            _ => {}
        }
    }

    fn end_statement_impl(&mut self, add_sep: bool)
    {
        if let Some(on_before_end_statement) = self.m_on_before_end_statement {
            on_before_end_statement(self);
        }
        if let Some(mut statement) = self.pop_statement() {
            if let Some(on_end_statement) = self.m_on_end_statement {
                on_end_statement(self, &mut statement);
            }
            let fnum = statement.get_function_num();
            if let Some(v_or_f) = statement.first() {
                if let ValueOrFunction::Function(func) = &v_or_f {
                    if fnum == 1 && func.get_id() == "@@delimiter" &&
                        (func.get_param_num() == 1 || func.get_param_num() == 3) &&
                        !func.is_high_order() {
                        let r#type = func.get_param_id(0);
                        if func.get_param_num() == 3 {
                            let begin = func.get_param_id(1);
                            let end = func.get_param_id(2);
                            if r#type == "string" {
                                self.set_string_delimiter(begin.clone(), end.clone());
                            }
                            else if r#type == "script" {
                                self.set_script_delimiter(begin.clone(), end.clone());
                            }
                            else {
                                //invalid
                            }
                        }
                        else {
                            if r#type == "string" {
                                self.set_string_delimiter(String::new(), String::new());
                            }
                            else if r#type == "script" {
                                self.set_script_delimiter(String::new(), String::new());
                            }
                            else {
                                //invalid
                            }
                        }
                        return;
                    }
                }
            }

            let mut comment_on_new_line: bool = false;
            if let Some(cmts) = self.get_comments(&mut comment_on_new_line) {
                if cmts.len() > 0 {
                    let mut new_line = false;
                    if let Some(tcmts) = statement.last_comments_mut() {
                        if tcmts.len() <= 0 {
                            new_line = true;
                        }
                        tcmts.append(&mut cmts.clone());
                    }
                    if new_line {
                        statement.set_last_comment_on_new_line(comment_on_new_line);
                    }
                }
            }

            if self.m_statement_semantic_stack.is_empty() {
                //Simplification only needs to handle the first level, and the parameters and statement parts
                //should have already been processed when added to the statement.
                let r = Self::simplify_statement_s(&mut statement);
                let mut statement_syntax;
                if let Some(syn) = r {
                    statement_syntax = syn;
                }
                else {
                    statement_syntax = SyntaxComponent::Statement(statement);
                }
                let len = self.m_script_datas.len();
                if !statement_syntax.is_valid() {
                    //The "epsilon" expression has no statement semantics.
                    if len > 0 {
                        let last = &mut self.m_script_datas[len - 1];
                        let mut new_line = false;
                        if let Some(tcmts) = last.last_comments_mut() {
                            if tcmts.len() <= 0 {
                                new_line = true;
                            }
                            if let Some(cmts) = statement_syntax.first_comments() {
                                tcmts.append(&mut cmts.clone());
                            }
                            if let Some(cmts) = statement_syntax.last_comments() {
                                tcmts.append(&mut cmts.clone());
                            }
                        }
                        if new_line {
                            last.set_last_comment_on_new_line(statement_syntax.first_comment_on_new_line());
                        }
                    }
                    return;
                }
                else if let SyntaxComponent::Value(_v) = &statement_syntax {
                    //If the statement is a regular value, move the comment to the previous statement.
                    if len > 0 {
                        let last = &mut self.m_script_datas[len - 1];
                        let mut new_line = false;
                        if let Some(tcmts) = last.last_comments_mut() {
                            if tcmts.len() <= 0 {
                                new_line = true;
                            }
                            if let Some(cmts) = statement_syntax.first_comments() {
                                tcmts.append(&mut cmts.clone());
                            }
                            if let Some(cmts) = statement_syntax.last_comments() {
                                tcmts.append(&mut cmts.clone());
                            }
                        }
                        if new_line {
                            last.set_last_comment_on_new_line(statement_syntax.first_comment_on_new_line());
                        }
                    }
                }
                else {
                    //Move the comment from the previous line of code to the line above.
                    if len > 0 && !statement_syntax.first_comment_on_new_line() {
                        if let Some(cmts) = statement_syntax.first_comments_mut() {
                            if cmts.len() > 0 {
                                let cmt = std::mem::take(&mut cmts[0]);
                                cmts.remove(0);
                                statement_syntax.set_first_comment_on_new_line(true);
                                let last = &mut self.m_script_datas[len - 1];
                                let mut new_line = false;
                                if let Some(tcmts) = last.last_comments_mut() {
                                    if tcmts.len() <= 0 {
                                        new_line = true;
                                    }
                                    tcmts.push(cmt);
                                }
                                if new_line {
                                    last.set_last_comment_on_new_line(false);
                                }
                            }
                        }
                    }
                }
                //Top-level element ends.
                if add_sep && len > 0 {
                    let last_stm = &mut self.m_script_datas[len - 1];
                    last_stm.set_seperator(dsl::SEPARATOR_SEMICOLON);
                }
                self.m_script_datas.push(statement_syntax);
            }
            else {
                //Simplification only needs to handle the first level. The parameters and statement parts
                //should have already been processed when added to the statement.
                let r = Self::simplify_statement_s(&mut statement);
                let mut statement_syntax;
                if let Some(syn) = r {
                    statement_syntax = syn;
                }
                else {
                    statement_syntax = SyntaxComponent::Statement(statement);
                }
                if let Some(v_or_f) = self.get_last_function_mut() {
                    if let ValueOrFunction::Function(func) = v_or_f {
                        let num = func.get_param_num();
                        if func.have_param() {
                            //If it is a comment within the parameters, keep it as it is. Comments on regular values
                            //will be discarded, and if embedded comments are moved to the end of the line, it may
                            //appear inexplicable.
                            //if !statementSyntax.is_valid() {
                            //    return;
                            //}
                        }
                        else if !statement_syntax.is_valid() {
                            //The "epsilon" expression has no statement semantics.
                            if num > 0 {
                                if let Some(cmts1) = statement_syntax.first_comments() {
                                    if cmts1.len() > 0 {
                                        if let Some(last) = func.get_param_mut(num- 1) {
                                            let mut new_line = false;
                                            if let Some(tcmts) = last.last_comments_mut() {
                                                if tcmts.len() <= 0 {
                                                    new_line = true;
                                                }
                                                tcmts.append(&mut cmts1.clone());
                                                if let Some(cmts2) = statement_syntax.last_comments() {
                                                    tcmts.append(&mut cmts2.clone());
                                                }
                                            }
                                            if new_line {
                                                last.set_last_comment_on_new_line(statement_syntax.first_comment_on_new_line());
                                            }
                                        }
                                    }
                                }
                            }
                            //return;
                        }
                        else if let SyntaxComponent::Value(_v) = &statement_syntax {
                            //If the statement is a regular value, move the comment to the previous statement.
                            if num > 0 {
                                if let Some(last) = func.get_param_mut(num- 1) {
                                    let mut new_line = false;
                                    if let Some(tcmts) = last.last_comments_mut() {
                                        if tcmts.len() <= 0 {
                                            new_line = true;
                                        }
                                        if let Some(cmts1) = statement_syntax.first_comments() {
                                            tcmts.append(&mut cmts1.clone());
                                        }
                                        if let Some(cmts2) = statement_syntax.last_comments() {
                                            tcmts.append(&mut cmts2.clone());
                                        }
                                    }
                                    if new_line {
                                        last.set_last_comment_on_new_line(statement_syntax.first_comment_on_new_line());
                                    }
                                }
                            }
                            else if let Some(tcmts) = func.comments_mut() {
                                if let Some(cmts1) = statement_syntax.first_comments() {
                                    tcmts.append(&mut cmts1.clone());
                                }
                                if let Some(cmts2) = statement_syntax.last_comments() {
                                    tcmts.append(&mut cmts2.clone());
                                }
                            }
                        }
                        else {
                            //Move the comment from the previous line of code to the line above.
                            if !statement_syntax.first_comment_on_new_line() {
                                if let Some(cmts) = statement_syntax.first_comments_mut() {
                                    if cmts.len() > 0 {
                                        let cmt = std::mem::take(&mut cmts[0]);
                                        cmts.remove(0);
                                        statement_syntax.set_first_comment_on_new_line(true);
                                        if num > 0 {
                                            if let Some(last) = func.get_param_mut(num - 1) {
                                                let mut new_line = false;
                                                if let Some(tcmts) = last.last_comments_mut() {
                                                    if tcmts.len() <= 0 {
                                                        new_line = true;
                                                    }
                                                    tcmts.push(cmt);
                                                }
                                                if new_line {
                                                    last.set_last_comment_on_new_line(false);
                                                }
                                            }
                                        }
                                        else if func.is_high_order() {
                                            if let Some(lf) = func.lower_order_function_mut() {
                                                if let Some(tcmts) = lf.comments_mut() {
                                                    tcmts.push(cmt);
                                                }
                                            }
                                        }
                                        else if let Some(tcmts) = func.comments_mut() {
                                            tcmts.push(cmt);
                                        }
                                    }
                                }
                            }
                        }

                        if add_sep && num > 0 {
                            let sep = if func.get_param_class_unmasked() == dsl::PARAM_CLASS_STATEMENT { dsl::SEPARATOR_SEMICOLON } else { dsl::SEPARATOR_COMMA };
                            if let Some(last_param) = func.get_param_mut(num - 1) {
                                last_param.set_seperator(sep);
                            }
                        }
                        func.add_syntax_component_param(statement_syntax);
                    }
                }
            }
        }
    }

    pub fn set_dsl_token(&mut self, token: &'a DslTokenCell<'a>)
    {
        self.m_dsl_token = Some(token);
    }
    pub fn set_name_tags(&mut self, tags: HashMap<String, u32>)
    {
        self.m_name_tags = tags;
    }
    pub fn peek_pair_type_stack(&self) -> i32
    {
        let mut tag: u32 = 0;
        return self.peek_pair_type_stack2(&mut tag);
    }
    pub fn peek_pair_type_stack2(&self, tag: &mut u32) -> i32
    {
        let mut ret: i32 = PAIR_TYPE_NONE;
        *tag = 0;
        if let Some(v) = self.m_pair_type_stack.back() {
            let vu = *v;
            *tag = vu >> 8;
            ret = vu as i32 & 0xff;
        }
        return ret;
    }
    pub fn get_pair_type_stack_size(&self) -> usize
    {
        return self.m_pair_type_stack.len();
    }
    pub fn get_pair_type_stack(&self, ix: usize) -> i32
    {
        let mut tag: u32 = 0;
        return self.get_pair_type_stack2(ix, &mut tag);
    }
    pub fn get_pair_type_stack2(&self, ix: usize, tag: &mut u32) -> i32
    {
        let mut ret = PAIR_TYPE_NONE;
        *tag = 0;
        if ix < self.m_pair_type_stack.len() {
            let mut i = 0;
            for v in &self.m_pair_type_stack {
                if i == ix {
                    *tag = *v >> 8;
                    ret = *v as i32 & 0x0ff;
                    break;
                }
                i += 1;
            }
        }
        return ret;
    }
    fn push_pair_type(&mut self, pair_type: i32)
    {
        self.push_pair_type2(pair_type, 0);
    }
    fn push_pair_type2(&mut self, pair_type: i32, tag: u32)
    {
        let v = (tag << 8) + pair_type as u32;
        self.m_pair_type_stack.push_back(v);
    }
    fn pop_pair_type(&mut self)
    {
        if self.m_pair_type_stack.len() > 0 {
            self.m_pair_type_stack.pop_back();
        }
    }

    pub fn mark_separator(&mut self)
    {
        let mut r#type = 0;
        let name = self.pop(&mut r#type);

        if self.m_statement_semantic_stack.len() == 0 {
            if let Some(dsl_info) = self.m_script_datas.last_mut() {
                dsl_info.set_seperator(Self::calc_separator_s(name));
            }
        }
        else {
            if let Some(v_or_f) = self.get_last_function_mut() {
                if let ValueOrFunction::Function(last_func) = v_or_f {
                    let num = last_func.get_param_num();
                    if num > 0 {
                        if let Some(last_param) = last_func.get_param_mut(num - 1) {
                            last_param.set_seperator(Self::calc_separator_s(name));
                        }
                    }
                }
            }
        }
    }
    pub fn build_operator(&mut self)
    {
        let mut r#type = 0;
        let name = self.pop(&mut r#type);

        if let Some(mut arg) = self.pop_statement() {
            if let Some(on_before_build_operator) = self.m_on_before_build_operator {
               on_before_build_operator(self, OPERATOR_CATEGORY_NORMAL, name.clone(), Some(&mut arg));
            }
            if let Some(on_build_operator) = self.m_on_build_operator {
                on_build_operator(self, OPERATOR_CATEGORY_NORMAL, name.clone(), &mut arg);
            }

            let r = Self::simplify_statement_s(&mut arg);
            let mut arg_comp;
            if let Some(syn) = r {
                arg_comp = syn;
            }
            else {
                arg_comp = SyntaxComponent::Statement(arg);
            }

            let mut _statement = Self::new_statement_with_one_function_s();
            if let Some(first) = _statement.first_mut() {
                match first {
                    ValueOrFunction::Value(v) => {
                        v.set_line(self.get_last_line_number());
                    }
                    ValueOrFunction::Function(f) => {
                        if let Some(fname) = f.name_mut() {
                            fname.set_line(self.get_last_line_number());
                        }
                    }
                }
            }

            _statement.copy_first_comments(&arg_comp);
            if let Some(cmts) = arg_comp.first_comments_mut() {
                cmts.clear();
            }

            self.m_statement_semantic_stack.push_back(_statement);

            if let Some(v_or_f) = self.get_last_function_mut() {
                if let ValueOrFunction::Function(func) = v_or_f {
                    if !func.is_valid() {
                        if name.len() > 0 && name.chars().next() == Some('`') {
                            func.set_param_class(dsl::PARAM_CLASS_WRAP_INFIX_CALL_MASK | dsl::PARAM_CLASS_OPERATOR);

                            if let Some(fname) = func.name_mut() {
                                fname.set_id(name[1..].to_string());
                                fname.set_type(r#type);
                            }
                        }
                        else {
                            func.set_param_class(dsl::PARAM_CLASS_OPERATOR);

                            if let Some(fname) = func.name_mut() {
                                fname.set_id(name);
                                fname.set_type(r#type);
                            }
                        }
                        if arg_comp.is_valid() {
                            func.add_syntax_component_param(arg_comp);
                        }
                    }
                }
            }
        }
    }
    pub fn build_first_ternary_operator(&mut self)
    {
        let mut r#type = 0;
        let name = self.pop(&mut r#type);

        if let Some(mut arg) = self.pop_statement() {
            if let Some(on_before_build_operator) = self.m_on_before_build_operator {
                on_before_build_operator(self, OPERATOR_CATEGORY_TERNARY, name.clone(), Some(&mut arg));
            }
            if let Some(on_build_operator) = self.m_on_build_operator {
                on_build_operator(self, OPERATOR_CATEGORY_TERNARY, name.clone(), &mut arg);
            }

            let r = Self::simplify_statement_s(&mut arg);
            let mut arg_comp;
            if let Some(syn) = r {
                arg_comp = syn;
            }
            else {
                arg_comp = SyntaxComponent::Statement(arg);
            }

            let mut _statement = Self::new_statement_with_one_function_s();
            if let Some(mut first) = _statement.first_mut() {
                if let ValueOrFunction::Function(f_func) = &mut first {
                    //The ternary operator is represented as op1(cond)(true_val)op2(false_val)
                    let mut lo_func = FunctionData::new();
                    let mut fname = ValueData::new();
                    fname.set_line(self.get_last_line_number());
                    lo_func.set_name(Box::new(fname));
                    f_func.set_lower_order_function(Box::new(lo_func));
                }
            }
            _statement.copy_first_comments(&arg_comp);
            if let Some(fcmts) = arg_comp.first_comments_mut() {
                fcmts.clear();
            }

            self.m_statement_semantic_stack.push_back(_statement);
            self.push_pair_type(PAIR_TYPE_QUESTION_COLON);

            if let Some(v_or_f) = self.get_last_function_mut() {
                if let ValueOrFunction::Function(l_func) = v_or_f {
                    if !l_func.is_valid() {
                        if let Some(lo_func) = l_func.lower_order_function_mut() {
                            lo_func.set_param_class(dsl::PARAM_CLASS_PARENTHESIS);
                            if let Some(fname) = lo_func.name_mut() {
                                fname.set_id(name);
                                fname.set_type(r#type);
                            }
                            if arg_comp.is_valid() {
                                lo_func.add_syntax_component_param(arg_comp);
                            }
                        }
                        l_func.set_param_class(dsl::PARAM_CLASS_TERNARY_OPERATOR);
                    }
                }
            }
        }
    }
    pub fn build_second_ternary_operator(&mut self)
    {
        let mut r#type = 0;
        let name = self.pop(&mut r#type);

        if let Some(on_before_build_operator) = self.m_on_before_build_operator {
            on_before_build_operator(self, OPERATOR_CATEGORY_TERNARY, name.clone(), None);
        }
        let mut has_statement = false;
        if let Some(statement) = self.get_cur_statement_mut() {
            has_statement = true;

            let mut new_func = FunctionData::new();
            let nfname = ValueData::new();
            new_func.set_name(Box::new(nfname));
            statement.add_function(ValueOrFunction::Function(new_func));
        }

        if  has_statement {
            self.pop_pair_type();
        }

        let last_line_number = self.get_last_line_number();
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                if !func.is_valid() {
                    func.set_param_class(dsl::PARAM_CLASS_TERNARY_OPERATOR);
                    if let Some(fname) = func.name_mut() {
                        fname.set_id(name);
                        fname.set_type(r#type);
                        fname.set_line(last_line_number);
                    }
                }
            }
        }
    }
    pub fn begin_statement(&mut self)
    {
        let mut statement = Self::new_statement_without_function_s();

        let mut comment_on_new_line = false;
        if let Some(cmts) = self.get_comments(&mut comment_on_new_line) {
            if cmts.len() > 0 {
                let mut new_line= false;
                if let Some(fcmts) = statement.first_comments_mut() {
                    if fcmts.len() <= 0 {
                        new_line = true;
                    }
                    fcmts.append(&mut cmts.clone());
                }
                if new_line {
                    statement.set_first_comment_on_new_line(comment_on_new_line);
                }
            }
        }

        self.m_statement_semantic_stack.push_back(statement);
    }
    pub fn end_statement(&mut self)
    {
        self.end_statement_impl(false);
    }
    pub fn add_function(&mut self)
    {
        if let Some(on_before_add_function) = self.m_on_before_add_function {
            on_before_add_function(self);
        }
        if let Some(statement) = self.get_cur_statement_mut() {
            Self::add_new_function_to_statement_s(statement);
        }
        if let Some(on_add_function) = self.m_on_add_function {
            on_add_function(self);
        }
    }
    pub fn set_function_id(&mut self)
    {
        let mut r#type = 0;
        let name = self.pop(&mut r#type);
        let last_line_number = self.get_last_line_number();
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                if !func.is_valid() {
                    if let Some(fname) = func.name_mut() {
                        fname.set_id(name);
                        fname.set_type(r#type);
                        fname.set_line(last_line_number);
                    }
                }
            }
        }
        if let Some(on_set_function_id) = self.m_on_set_function_id {
            on_set_function_id(self);
        }
    }
    pub fn build_nullable_operator(&mut self)
    {
        let mut r#type = 0;
        let name = self.pop(&mut r#type);

        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                if name == "?" {
                    func.set_param_class(dsl::PARAM_CLASS_QUESTION_NULLABLE_OPERATOR);
                }
                else {
                    func.set_param_class(dsl::PARAM_CLASS_EXCLAMATION_NULLABLE_OPERATOR);
                }
            }
        }

        if let Some(on_before_build_high_order) = self.m_on_before_build_high_order {
            on_before_build_high_order(self);
        }
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                let mut temp = FunctionData::new();
                temp.copy_from(func);
                func.clear();
                func.set_lower_order_function(Box::new(temp));
            }
        }
        if let Some(on_build_high_order) = self.m_on_build_high_order {
           on_build_high_order(self);
        }
    }
    pub fn build_high_order_function(&mut self)
    {
        //Higher-order function construction (the current function returns another function).
        if let Some(on_before_build_high_order) = self.m_on_before_build_high_order {
            on_before_build_high_order(self);
        }
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                let mut temp = FunctionData::new();
                temp.copy_from(func);
                func.clear();
                func.set_lower_order_function(Box::new(temp));
            }
        }
        if let Some(on_build_high_order) = self.m_on_build_high_order {
           on_build_high_order(self);
        }
    }
    pub fn mark_parenthesis_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_PARENTHESIS);
            }
        }
        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_PARENTHESIS, tag);
    }
    pub fn mark_parenthesis_param_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_bracket_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_BRACKET);
            }
        }
        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_BRACKET, tag);
    }
    pub fn mark_bracket_param_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_period_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_PERIOD);
            }
        }
    }
    pub fn mark_statement(&mut self)
    {
        let mut comment_on_new_line = false;
        let cmts_moved: Option<Vec<String>> = self.get_comments(&mut comment_on_new_line);

        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                if let Some(mut cmts) = cmts_moved {
                    if func.is_high_order() {
                        if let Some(lo_func) = func.lower_order_function_mut() {
                            if let Some(tcmts) = lo_func.comments_mut() {
                                tcmts.append(&mut cmts);
                            }
                        }
                    }
                    else{
                        if let Some(tcmts) = func.comments_mut() {
                            tcmts.append(&mut cmts);
                        }
                    }
                }
                func.set_param_class(dsl::PARAM_CLASS_STATEMENT);
            }
        }

        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_BRACE, tag);
    }
    pub fn mark_statement_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_extern_script(&mut self)
    {
        let mut comment_on_new_line = false;
        let cmts_moved: Option<Vec<String>> = self.get_comments(&mut comment_on_new_line);

        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                if let Some(mut cmts) = cmts_moved {
                    if func.is_high_order() {
                        if let Some(lo_func) = func.lower_order_function_mut() {
                            if let Some(tcmts) = lo_func.comments_mut() {
                                tcmts.append(&mut cmts);
                            }
                        }
                    }
                    else{
                        if let Some(tcmts) = func.comments_mut() {
                            tcmts.append(&mut cmts);
                        }
                    }
                }
                func.set_param_class(dsl::PARAM_CLASS_EXTERN_SCRIPT);
            }
        }
    }
    pub fn mark_bracket_colon_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_BRACKET_COLON);
            }
        }
        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_BRACKET_COLON, tag);
    }
    pub fn mark_bracket_colon_param_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_parenthesis_colon_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_PARENTHESIS_COLON);
            }
        }
        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_PARENTHESIS_COLON, tag);
    }
    pub fn mark_parenthesis_colon_param_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_angle_bracket_colon_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_ANGLE_BRACKET_COLON);
            }
        }
        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_ANGLE_BRACKET_COLON, tag);
    }
    pub fn mark_angle_bracket_colon_param_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_brace_percent_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_BRACE_PERCENT);
            }
        }
        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_BRACE_PERCENT, tag);
    }
    pub fn mark_brace_percent_param_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_bracket_percent_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_BRACKET_PERCENT);
            }
        }
        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_BRACKET_PERCENT, tag);
    }
    pub fn mark_bracket_percent_param_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_parenthesis_percent_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_PARENTHESIS_PERCENT);
            }
        }
        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_PARENTHESIS_PERCENT, tag);
    }
    pub fn mark_parenthesis_percent_param_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_angle_bracket_percent_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_ANGLE_BRACKET_PERCENT);
            }
        }
        let tag = self.get_name_tag();
        self.push_pair_type2(PAIR_TYPE_ANGLE_BRACKET_PERCENT, tag);
    }
    pub fn mark_angle_bracket_percent_param_end(&mut self)
    {
        self.pop_pair_type();
    }
    pub fn mark_colon_colon_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_COLON_COLON);
            }
        }
    }
    pub fn set_extern_script(&mut self)
    {
        let last_tok = self.get_last_token();
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.add_string_type_param(last_tok, dsl::STRING_TOKEN);
            }
        }
    }
    pub fn mark_pointer_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_POINTER);
            }
        }
    }
    pub fn mark_period_star_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_PERIOD_STAR);
            }
        }
    }
    pub fn mark_pointer_star_param(&mut self)
    {
        if let Some(v_or_f) = self.get_last_function_mut() {
            if let ValueOrFunction::Function(func) = v_or_f {
                func.set_param_class(dsl::PARAM_CLASS_POINTER_STAR);
            }
        }
    }
    fn push_id(&mut self)
    {
        self.push(self.get_last_token(), dsl::ID_TOKEN);
    }
    fn push_num(&mut self)
    {
        self.push(self.get_last_token(), dsl::NUM_TOKEN);
    }
    fn push_str(&mut self)
    {
        self.push(self.get_last_token(), dsl::STRING_TOKEN);
    }
    fn push_dollar_str(&mut self)
    {
        self.push(self.get_last_token(), dsl::DOLLAR_STRING_TOKEN);
    }
    fn push_comma(&mut self)
    {
        self.push(String::from(","), dsl::STRING_TOKEN);
    }
    fn push_semi_colon(&mut self)
    {
        self.push(String::from(";"), dsl::STRING_TOKEN);
    }

    /// ---------------------------------------------------------------
    /// Utility function section.
    /// ---------------------------------------------------------------
    pub fn push(&mut self, s: String, val: i32)
    {
        self.m_semantic_stack.push_back(SemanticInfo::new(&s, val));
    }
    fn pop(&mut self, val: &mut i32) -> String
    {
        *val = 0;
        if self.m_semantic_stack.len() == 0 {
            return String::from("null_stack_!!!");
        }
        let tok: String;
        if let Some(info) = self.m_semantic_stack.pop_back() {
            *val = info.value;
            tok = info.token;
        }
        else {
            tok = String::new();
        }
        return tok;
    }
    fn pop_statement(&mut self) -> Option<StatementData>
    {
        if self.m_statement_semantic_stack.len() == 0 {
            return None;
        }
        let cdata = self.m_statement_semantic_stack.pop_back();
        return cdata;
    }
    pub fn get_cur_statement(&self) -> Option<&StatementData>
    {
        if self.m_statement_semantic_stack.len() == 0 {
            return None;
        }
        let top_data = self.m_statement_semantic_stack.back();
        return top_data;
    }
    pub fn get_cur_statement_mut(&mut self) -> Option<&mut StatementData>
    {
        if self.m_statement_semantic_stack.len() == 0 {
            return None;
        }
        let top_data = self.m_statement_semantic_stack.back_mut();
        return top_data;
    }
    pub fn get_cur_parent_statement(&self) -> Option<&StatementData>
    {
        if self.m_statement_semantic_stack.len() <= 1 {
            return None;
        }
        let mut iter = self.m_statement_semantic_stack.iter().rev();
        let parent_data = iter.nth(1);
        return parent_data;
    }
    pub fn get_cur_parent_statement_mut(&mut self) -> Option<&mut StatementData>
    {
        if self.m_statement_semantic_stack.len() <= 1 {
            return None;
        }
        let mut iter = self.m_statement_semantic_stack.iter_mut().rev();
        let parent_data = iter.nth(1);
        return parent_data;
    }
    pub fn get_first_function(&self) -> Option<&ValueOrFunction>
    {
        if let Some(statement) = self.get_cur_statement() {
            return statement.first();
        }
        return None;
    }
    pub fn get_first_function_mut(&mut self) -> Option<&mut ValueOrFunction>
    {
        if let Some(statement) = self.get_cur_statement_mut() {
            return statement.first_mut();
        }
        return None;
    }
    pub fn get_second_function(&self) -> Option<&ValueOrFunction>
    {
        if let Some(statement) = self.get_cur_statement() {
            return statement.second();
        }
        return None;
    }
    pub fn get_second_function_mut(&mut self) -> Option<&mut ValueOrFunction>
    {
        if let Some(statement) = self.get_cur_statement_mut() {
            return statement.second_mut();
        }
        return None;
    }
    pub fn get_third_function(&self) -> Option<&ValueOrFunction>
    {
        if let Some(statement) = self.get_cur_statement() {
            return statement.third();
        }
        return None;
    }
    pub fn get_third_function_mut(&mut self) -> Option<&mut ValueOrFunction>
    {
        if let Some(statement) = self.get_cur_statement_mut() {
            return statement.third_mut();
        }
        return None;
    }
    pub fn get_last_function(&self) -> Option<&ValueOrFunction>
    {
        if let Some(statement) = self.get_cur_statement() {
            return statement.last();
        }
        return None;
    }
    pub fn get_last_function_mut(&mut self) -> Option<&mut ValueOrFunction>
    {
        if let Some(statement) = self.get_cur_statement_mut() {
            return statement.last_mut();
        }
        return None;
    }
    pub fn get_name_tag(&self) -> u32
    {
        let mut tag: u32 = 0;
        if let Some(v_or_f) = self.get_last_function() {
            if let ValueOrFunction::Function(func) = v_or_f {
                if let Some(t) = self.m_name_tags.get(func.get_id()) {
                    tag = *t;
                }
            }
        }
        return tag;
    }

    fn get_last_token(&self) -> String
    {
        if let Some(tokens) = self.m_dsl_token {
            return tokens.borrow().get_last_token().clone();
        }
        else {
            return String::new();
        }
    }
    fn get_last_line_number(&self) -> i32
    {
        if let Some(tokens) = self.m_dsl_token {
            return tokens.borrow().get_last_line_number();
        }
        else {
            return -1;
        }
    }
    fn get_comments(&self, comment_on_new_line: &mut bool) -> Option<Vec<String>>
    {
        if let Some(tokens) = self.m_dsl_token {
            *comment_on_new_line = tokens.borrow().is_comment_on_new_line();
            let cmts = std::mem::take(tokens.borrow_mut().get_comments_mut());
            tokens.borrow_mut().reset_comments();
            return Some(cmts);
        }
        else {
            *comment_on_new_line = false;
            return None;
        }
    }
    fn set_string_delimiter(&mut self, begin: String, end: String)
    {
        if let Some(tokens) = self.m_dsl_token {
            tokens.borrow_mut().set_string_delimiter(begin, end);
        }
    }
    fn set_script_delimiter(&mut self, begin: String, end: String)
    {
        if let Some(tokens) = self.m_dsl_token {
            tokens.borrow_mut().set_script_delimiter(begin, end);
        }
    }

    pub fn new_statement_with_one_function_s() -> StatementData
    {
        let mut data = StatementData::new();
        let mut func = FunctionData::new();
        let name = ValueData::new();
        func.set_name(Box::new(name));
        data.add_function(ValueOrFunction::Function(func));
        return data;
    }
    pub fn new_statement_without_function_s() -> StatementData
    {
        let data = StatementData::new();
        return data;
    }
    pub fn add_new_function_to_statement_s(data: &mut StatementData)
    {
        let mut func = FunctionData::new();
        let name = ValueData::new();
        func.set_name(Box::new(name));
        data.add_function(ValueOrFunction::Function(func));
    }

    fn simplify_statement_s(data: &mut StatementData) -> Option<SyntaxComponent>
    {
        //Simplify statements (during the process of syntax analysis, they are constructed
        //using complete StatementData for convenience, but here they are simplified to their original
        //types: ValueData/CallData/FunctionData, etc.,
        //mainly involving parameters and statement parts).
        if data.get_function_num() == 1 {
            //Statements with only one function are reduced to the function itself
            //(and further reduced according to the function).
            if let Some(vf) = data.get_function_mut(0) {
                match vf {
                    ValueOrFunction::Value(v) => {
                        let cv = std::mem::take(v);
                        return Some(SyntaxComponent::Value(cv));
                    }
                    ValueOrFunction::Function(f) => {
                        if let Some(r) = Self::simplify_function_s(f) {
                            match r {
                                ValueOrFunction::Value(rv) => {
                                    return Some(SyntaxComponent::Value(rv));
                                }
                                ValueOrFunction::Function(rf) => {
                                    return Some(SyntaxComponent::Function(rf));
                                }
                            }
                        }
                        else {
                            return Some(SyntaxComponent::Function(f.clone()));
                        }
                    }
                }
            }
        }
        else {
            let mut i = 0;
            while i < data.get_function_num() {
                if let Some(func) = data.get_function_mut(i) {
                    match func {
                        ValueOrFunction::Function(f) => {
                            if let Some(v_or_f) = Self::simplify_function_s(f) {
                                *func = v_or_f;
                            }
                        }
                        _ => {}
                    }
                }
                i += 1;
            }
        }
        return None;
    }
    fn simplify_function_s(data: &mut FunctionData) -> Option<ValueOrFunction>
    {
        //Note that in order to save memory, comments are not included in ValueData.
        //The related interfaces have no actual effect!!!
        if !data.have_param_or_statement() {
            //Calls without parameters are reduced to basic value data.
            if data.is_high_order() {
                //This situation should not occur.
                let data_moved = std::mem::take(data);
                return Some(ValueOrFunction::Function(data_moved));
            }
            else {
                if let Some(val) = data.name_mut() {
                    let val_moved = std::mem::take(val.as_mut());
                    return Some(ValueOrFunction::Value(val_moved));
                }
            }
        }

        //Handling epsilon statements and parameters.
        Self::simplify_function_inplace_s(data);

        if data.get_id() == "-" && data.get_param_num() == 1 {
            if let Some(sc) = data.get_param(0) {
                if let SyntaxComponent::Value(val) = sc {
                    if val.is_number() {
                        let ret = ValueData::from_string_type(String::from("-") + val.get_id(), dsl::NUM_TOKEN);
                        return Some(ValueOrFunction::Value(ret));
                    }
                }
            }
        }
        else if data.get_id() == "+" && data.get_param_num() == 1 {
            if let Some(sc) = data.get_param_mut(0) {
                if let SyntaxComponent::Value(val) = sc {
                    if val.is_number() {
                        let id_moved = std::mem::take(val.get_id_mut());
                        let ret = ValueData::from_string_type(id_moved, dsl::NUM_TOKEN);
                        return Some(ValueOrFunction::Value(ret));
                    }
                }
            }
        }
        return None;
    }
    fn simplify_function_inplace_s(data: &mut FunctionData)
    {
        // When the last statement is epsilon and the only parameter is epsilon, delete this statement and parameter.
        // This ensures correct parsing of for(;;){}.
        // Currently, {} is used for non-block statement cases, so there should be no need for the last parameter to be empty
        // (allowing preceding parameters to be empty is already allowed). The side effect is that the statement list
        // also allows other statements to be empty except for the last one that is not terminated by a semicolon.
        // The higher-level application needs to handle this case when further parsing.
        if data.is_high_order() {
            if let Some(lower_order_function) = data.lower_order_function_mut() {
                Self::simplify_function_inplace_s(&mut lower_order_function.as_mut());
            }
        }
        let mut remove_last = false;
        let num = data.get_param_num();
        if data.have_statement() && num > 0 || num == 1 {
            if let Some(p) = data.get_param(num - 1) {
                if !p.is_valid() {
                    remove_last = true;
                }
            }
            else {
                remove_last = true;
            }
        }
        if remove_last {
            if let Some(ps) = data.params_mut() {
                ps.remove(num - 1);
            }
        }
    }
    fn calc_separator_s(tok: String) -> i32
    {
        if tok == "," {
            return dsl::SEPARATOR_COMMA;
        }
        else if tok == ";" {
            return dsl::SEPARATOR_SEMICOLON;
        }
        else {
            return dsl::SEPARATOR_NOTHING;
        }
    }
}
pub trait IVisitor
{
    fn visit(&self, production: &[i16], production_row: &[i16], parse: &[i16], parse_row: &[i16], start_symbol: i16, start_action: i16);
}
