use std::vec::Vec;
use std::collections::VecDeque;
use std::cell::RefCell;
use std::char;
use crate::dsl::common::action;
use crate::dsl::common::action::{DslActionCell, GetTokenDelegationBox, TokenCanEatCharDelegationBox};
use crate::dsl::common::log::DslLogCell;
use crate::dsl::parser::constants;

macro_rules! white_spaces {
    () => {
        " \t\r\n"
    };
}

macro_rules! delimiters {
    () => {
        ",;"
    };
}

macro_rules! begin_parentheses {
    () => {
        "{(["
    };
}

macro_rules! end_parentheses {
    () => {
        "})]"
    };
}

macro_rules! operators {
    () => {
        "~`!%^&*-+=|:<>?/"
    };
}

macro_rules! quotes {
    () => {
        "'\""
    };
}

const WHITE_SPACES: &str = white_spaces!();
const DELIMITERS: &str = delimiters!();
const BEGIN_PARENTHESES: &str = begin_parentheses!();
const END_PARENTHESES: &str = end_parentheses!();
const OPERATORS: &str = operators!();
const QUOTES: &str = quotes!();
const SPECIAL_CHARS: &str = concat!(
    white_spaces!(),
    delimiters!(),
    begin_parentheses!(),
    end_parentheses!(),
    operators!(),
    quotes!()
);

pub type DslTokenCell<'a> = RefCell<DslToken<'a>>;

pub struct DslToken<'a>
{
    m_action: &'a DslActionCell<'a>,
    m_log: &'a DslLogCell<'a>,
    m_input: Vec<char>,
    m_char_byte_index: Vec<usize>,
    m_byte_char_index: Vec<usize>,
    m_input_str: String,
    m_iterator: usize,
    m_cur_token: String,
    m_last_token: String,

    m_line_number: i32,
    m_last_line_number: i32,

    m_comment_builder: String,
    m_comments: Vec<String>,
    m_comment_on_new_line: bool,

    m_token_builder: String,
    m_token_queue: VecDeque<TokenInfo>,

    m_nullable_syntax_enabled: bool,
    m_string_begin_delimiter: String,
    m_string_end_delimiter: String,
    m_script_begin_delimiter: String,
    m_script_end_delimiter: String,
    m_on_get_token: Option<&'a GetTokenDelegationBox<'a>>,
    m_on_token_can_eat_char: Option<&'a TokenCanEatCharDelegationBox<'a>>,
}

struct TokenInfo
{
    m_token: String,
    m_token_value: i16,
    m_line_number: i32,
}

impl<'a> DslToken<'a>
{
    pub fn new(action: &'a DslActionCell<'a>, log: &'a DslLogCell<'a>, input: String, nullable_syntax_enabled: bool) -> Self
    {
        Self {
            m_action: action,
            m_log: log,
            m_input: input.chars().collect(),
            m_char_byte_index: Self::build_char_byte_index(&input),
            m_byte_char_index: Self::build_byte_char_index(&input),
            m_input_str: input,
            m_iterator: 0,

            m_line_number: 1,
            m_last_line_number: 1,

            m_cur_token: String::new(),
            m_last_token: String::new(),

            m_comment_builder: String::new(),
            m_comments: Vec::new(),
            m_comment_on_new_line: false,

            m_token_builder: String::new(),
            m_token_queue: VecDeque::new(),

            m_nullable_syntax_enabled: nullable_syntax_enabled,
            m_string_begin_delimiter: String::new(),
            m_string_end_delimiter: String::new(),
            m_script_begin_delimiter: String::new(),
            m_script_end_delimiter: String::new(),
            m_on_get_token: None,
            m_on_token_can_eat_char: None,
        }
    }
    fn build_char_byte_index(input: &str) -> Vec<usize>
    {
        let char_to_byte: Vec<usize> = input.char_indices().map(|(b, _)| b).collect();
        return char_to_byte;
    }
    fn build_byte_char_index(input: &str) -> Vec<usize>
    {
        let mut byte_to_char = vec![0; input.len()];
        for (char_idx, (byte_idx, _)) in input.char_indices().enumerate() {
            byte_to_char[byte_idx] = char_idx;
        }

        let mut last = 0;
        for i in 0..byte_to_char.len() {
            if byte_to_char[i] != 0 || i == 0 {
                last = byte_to_char[i];
            } else {
                byte_to_char[i] = last;
            }
        }

        return byte_to_char;
    }

    pub fn get(&mut self) -> i16
    {
        let mut tok: i16 = self.get_impl();
        if let Some(on_get_token) = self.m_on_get_token {
            let mut cur_tok = self.m_cur_token.clone();
            let mut line = self.m_line_number;
            on_get_token(self.m_action, self, &mut cur_tok, &mut tok, &mut line);
            self.m_cur_token = cur_tok;
        }
        return tok;
    }
    fn get_impl(&mut self) -> i16
    {
        self.m_last_token = std::mem::take(&mut self.m_cur_token);
        self.m_last_line_number = self.m_line_number;
        if !self.m_token_queue.is_empty() {
            let token = self.m_token_queue.pop_front();
            if let Some(tk) = token {
                self.m_cur_token = tk.m_token;
                self.m_line_number = tk.m_line_number;
                return tk.m_token_value;
            }
            assert!(false);
        }
        let mut is_skip = true;
        //skip comments and white spaces
        while is_skip && self.cur_char() != '\0' {
            is_skip = false;
            while WHITE_SPACES.find(self.cur_char()) != None {
                if self.cur_char() == '\n' {
                    self.m_line_number += 1;
                    if self.m_comments.len() <= 0 {
                        self.m_comment_on_new_line = true;
                    }
                }
                is_skip = true;
                self.m_iterator += 1;
            }
            //#Leading single-line or block comment
            if self.cur_char() == '#' || self.cur_char() == '/' && self.next_char() == '/' {
                self.m_comment_builder.clear();
                while self.cur_char() != '\0' && self.cur_char() != '\n' {
                    if self.cur_char() != '\r' {
                        self.m_comment_builder.push(self.cur_char());
                    }
                    self.m_iterator += 1;
                }
                //mLineNumber += 1;
                is_skip = true;
                self.m_comments.push(std::mem::take(&mut self.m_comment_builder));
            }
            //C++ style multi-line comments
            if self.cur_char() == '/' && self.next_char() == '*' {
                self.m_comment_builder.clear();
                self.m_comment_builder.push(self.cur_char());
                self.m_comment_builder.push(self.next_char());
                self.m_iterator += 1;
                self.m_iterator += 1;
                while self.cur_char() != '\0' {
                    if self.cur_char() == '\n' {
                        self.m_comment_builder.push('\n');
                        self.m_line_number += 1;
                    }
                    else if self.cur_char() == '*' && self.next_char() == '/' {
                        self.m_comment_builder.push(self.cur_char());
                        self.m_comment_builder.push(self.next_char());
                        self.m_iterator += 1;
                        self.m_iterator += 1;
                        break;
                    }
                    else if self.cur_char() != '\r' {
                        self.m_comment_builder.push(self.cur_char());
                    }
                    self.m_iterator += 1;
                }
                is_skip = true;
                self.m_comments.push(std::mem::take(&mut self.m_comment_builder));
            }
        }
        self.m_token_builder.clear();
        if self.cur_char() == '\0' {//end of input
            self.m_cur_token = String::from("<<eof>>");
            return constants::END_OF_SLK_INPUT_;
        }
        else if !self.string_begin_delimiter().is_empty() && !self.string_end_delimiter().is_empty() && self.is_begin(self.string_begin_delimiter()) {
            self.m_iterator += self.string_begin_delimiter().chars().count();
            let mut iter: usize = 0;
            let mut line: i32 = 0;
            self.m_cur_token = self.get_block_string(self.string_end_delimiter(), &mut iter, &mut line);
            self.m_iterator = iter;
            self.m_line_number = line;
            return constants::STRING_;
        }
        else if !self.script_begin_delimiter().is_empty() && !self.script_end_delimiter().is_empty() && self.is_begin(self.script_begin_delimiter()) {
            self.m_iterator += self.script_begin_delimiter().chars().count();
            let mut iter: usize = 0;
            let mut line: i32 = 0;
            self.m_cur_token = self.get_block_string(self.script_end_delimiter(), &mut iter, &mut line);
            self.m_iterator = iter;
            self.m_line_number = line;
            return constants::SCRIPT_CONTENT_;
        }
        else if self.cur_char() == '{' && self.next_char() == ':' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            let line = self.m_line_number;
            //find the end of script ':}'
            while self.cur_char() != '\0' {
                while self.cur_char() != '\0' && self.cur_char() != ':' {
                    if self.cur_char() == '\n' {
                        self.m_line_number += 1;
                    }

                    self.m_token_builder.push(self.cur_char());
                    self.m_iterator += 1;
                }
                if self.cur_char() == '\0' {
                    break;
                }
                if self.next_char() == '}' {
                    self.m_iterator += 1;
                    self.m_iterator += 1;
                    break;
                }
                else {
                    self.m_token_builder.push(self.cur_char());
                    self.m_iterator += 1;
                }
            }
            if self.cur_char() == '\0' {
                self.m_log.borrow().info(&format!("[error][line {}]: ExternScript can't finish! \n", line));
            }
            let str = std::mem::take(&mut self.m_token_builder);
            self.m_cur_token = self.remove_first_and_last_empty_line(&str);
            return constants::SCRIPT_CONTENT_;
        }
        else if self.cur_char() == '[' && self.next_char() == ':' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("[:");
            return constants::BRACKET_COLON_BEGIN_;
        }
        else if self.cur_char() == ':' && self.next_char() == ']' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from(":]");
            return constants::BRACKET_COLON_END_;
        }
        else if self.cur_char() == '(' && self.next_char() == ':' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("(:");
            return constants::PARENTHESES_COLON_BEGIN_;
        }
        else if self.cur_char() == ':' && self.next_char() == ')' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from(":)");
            return constants::PARENTHESES_COLON_END_;
        }
        else if self.cur_char() == '<' && self.next_char() == ':' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            if self.cur_char() == ':' {
                if self.next_char() == '>' {
                    self.m_cur_token = String::from("<:");
                    return constants::ANGLE_BRACKET_COLON_BEGIN_;
                }
                else {
                    self.m_iterator += 1;
                    self.m_token_queue.push_back(TokenInfo { m_token: String::from("::"), m_token_value: constants::COLON_COLON_, m_line_number: self.m_line_number });
                    self.m_cur_token = String::from("<");
                    return self.get_operator_token_value();
                }
            }
            else {
                self.m_cur_token = String::from("<:");
                return constants::ANGLE_BRACKET_COLON_BEGIN_;
            }
        }
        else if self.cur_char() == ':' && self.next_char() == '>' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from(":>");
            return constants::ANGLE_BRACKET_COLON_END_;
        }
        else if self.cur_char() == '{' && self.next_char() == '%' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("{%");
            return constants::BRACE_PERCENT_BEGIN_;
        }
        else if self.cur_char() == '%' && self.next_char() == '}' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("%}");
            return constants::BRACE_PERCENT_END_;
        }
        else if self.cur_char() == '[' && self.next_char() == '%' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("[%");
            return constants::BRACKET_PERCENT_BEGIN_;
        }
        else if self.cur_char() == '%' && self.next_char() == ']' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("%]");
            return constants::BRACKET_PERCENT_END_;
        }
        else if self.cur_char() == '(' && self.next_char() == '%' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("(%");
            return constants::PARENTHESES_PERCENT_BEGIN_;
        }
        else if self.cur_char() == '%' && self.next_char() == ')' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("%)");
            return constants::PARENTHESES_PERCENT_END_;
        }
        else if self.cur_char() == '<' && self.next_char() == '%' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("<%");
            return constants::ANGLE_BRACKET_PERCENT_BEGIN_;
        }
        else if self.cur_char() == '%' && self.next_char() == '>' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("%>");
            return constants::ANGLE_BRACKET_PERCENT_END_;
        }
        else if self.cur_char() == ':' && self.next_char() == ':' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from("::");

            let (ct, last_char, last_char2) = Self::get_last_2_chars_s(&self.m_last_token);
            if ct > 0 && self.is_not_identifier_and_number_and_end_parentheses(last_char) && last_char != '?' && last_char != '!' &&
                (ct != 2 || (!(last_char2 == ':' && last_char == '>') && !(last_char2 == '%' && last_char == '>'))) {
                return self.get_operator_token_value();
            }
            let next_char = self.peek_next_valid_char(0);
            let next_char2 = self.peek_next_valid_char(1);
            let next_char3 = self.peek_next_valid_char(2);
            if self.is_not_identifier_and_begin_parentheses(next_char) && !(next_char == '<' && next_char2 == ':' && self.is_white_space(next_char3)) && !(next_char == '<' && next_char2 == '%' && self.is_white_space(next_char3)) {
                return self.get_operator_token_value();
            }
            return constants::COLON_COLON_;
        }
        else if self.cur_char() == '?' || self.cur_char() == '!' {
            let (ct, last_char, last_char2) = Self::get_last_2_chars_s(&self.m_last_token);
            if ct > 0 && self.is_not_identifier_and_number_and_end_parentheses(last_char) && last_char != '?' && last_char != '!' &&
                (ct != 2 || (!(last_char2 == ':' && last_char == '>') && !(last_char2 == '%' && last_char == '>'))) {
                self.get_operator_token();
                return self.get_operator_token_value();
            }
            else if self.m_nullable_syntax_enabled {
                let tok = if self.cur_char() == '?' { "?" }else{ "!"};
                if self.next_char() == '.' {
                    self.m_iterator += 1;
                    self.m_cur_token = String::from(tok);
                    return constants::OP_TOKEN_NULLABLE_;
                }
                else if self.next_char() == '-' && self.peek_char(2) == '>' {
                    self.m_iterator += 1;
                    self.m_cur_token = String::from(tok);
                    return constants::OP_TOKEN_NULLABLE_;
                }
                else if self.next_char() == '(' {
                    self.m_iterator += 1;
                    self.m_cur_token = String::from(tok);
                    return constants::OP_TOKEN_NULLABLE_;
                }
                else if self.next_char() == '[' {
                    self.m_iterator += 1;
                    self.m_cur_token = String::from(tok);
                    return constants::OP_TOKEN_NULLABLE_;
                }
                else if self.next_char() == '{' {
                    self.m_iterator += 1;
                    self.m_cur_token = String::from(tok);
                    return constants::OP_TOKEN_NULLABLE_;
                }
                else if self.next_char() == '<' && (self.peek_char(2) == ':' || self.peek_char(2) == '%') {
                    self.m_iterator += 1;
                    self.m_cur_token = String::from(tok);
                    return constants::OP_TOKEN_NULLABLE_;
                }
                else {
                    self.get_operator_token();
                    return self.get_operator_token_value();
                }
            }
            else {
                self.get_operator_token();
                return self.get_operator_token_value();
            }
        }
        else if self.cur_char() == '-' {
            if self.next_char() == '>' {
                self.m_iterator += 1;
                self.m_iterator += 1;
                if self.cur_char() == '*' {
                    self.m_iterator += 1;
                    self.m_cur_token = String::from("->*");

                    let (ct, last_char, last_char2) = Self::get_last_2_chars_s(&self.m_last_token);
                    if ct > 0 && self.is_not_identifier_and_number_and_end_parentheses(last_char) && last_char != '?' && last_char != '!' &&
                        (ct != 2 || (!(last_char2 == ':' && last_char == '>') && !(last_char2 == '%' && last_char == '>'))) {
                        return self.get_operator_token_value();
                    }
                    let next_char = self.peek_next_valid_char(0);
                    let next_char2 = self.peek_next_valid_char(1);
                    let next_char3 = self.peek_next_valid_char(2);
                    if self.is_not_identifier_and_begin_parentheses(next_char) && !(next_char == '<' && next_char2 == ':' && self.is_white_space(next_char3)) && !(next_char == '<' && next_char2 == '%' && self.is_white_space(next_char3)) {
                        return self.get_operator_token_value();
                    }
                    return constants::POINTER_STAR_;
                }
                else {
                    self.m_cur_token = String::from("->");

                    let (ct, last_char, last_char2) = Self::get_last_2_chars_s(&self.m_last_token);
                    if ct > 0 && self.is_not_identifier_and_number_and_end_parentheses(last_char) && last_char != '?' && last_char != '!' &&
                        (ct != 2 || (!(last_char2 == ':' && last_char == '>') && !(last_char2 == '%' && last_char == '>'))) {
                        return self.get_operator_token_value();
                    }
                    let next_char = self.peek_next_valid_char(0);
                    let next_char2 = self.peek_next_valid_char(1);
                    let next_char3 = self.peek_next_valid_char(2);
                    if self.is_not_identifier_and_begin_parentheses(next_char) && !(next_char == '<' && next_char2 == ':' && self.is_white_space(next_char3)) && !(next_char == '<' && next_char2 == '%' && self.is_white_space(next_char3)) {
                        return self.get_operator_token_value();
                    }
                    return constants::POINTER_;
                }
            }
            else {
                self.get_operator_token();
                return self.get_operator_token_value();
            }
        }
        else if self.cur_char() == '.' && self.next_char() == '*' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            self.m_cur_token = String::from(".*");

            let (ct, last_char, last_char2) = Self::get_last_2_chars_s(&self.m_last_token);
            if ct > 0 && self.is_not_identifier_and_number_and_end_parentheses(last_char) && last_char != '?' && last_char != '!' &&
                (ct != 2 || (!(last_char2 == ':' && last_char == '>') && !(last_char2 == '%' && last_char == '>'))) {
                return self.get_operator_token_value();
            }
            let next_char = self.peek_next_valid_char(0);
            let next_char2 = self.peek_next_valid_char(1);
            let next_char3 = self.peek_next_valid_char(2);
            if self.is_not_identifier_and_begin_parentheses(next_char) && !(next_char == '<' && next_char2 == ':' && self.is_white_space(next_char3)) && !(next_char == '<' && next_char2 == '%' && self.is_white_space(next_char3)) {
                return self.get_operator_token_value();
            }
            return constants::PERIOD_STAR_;
        }
        else if self.cur_char() == '.' && self.next_char() == '.' {
            self.m_iterator += 1;
            self.m_iterator += 1;
            if self.cur_char() == '.' {
                self.m_iterator += 1;
                self.m_cur_token = String::from("...");
                return constants::IDENTIFIER_;
            }
            else {
                self.m_cur_token = String::from("..");
                return self.get_operator_token_value();
            }
        }
        else if OPERATORS.find(self.cur_char()) != None {
            self.get_operator_token();
            return self.get_operator_token_value();
        }
        else if self.cur_char() == '.' && !Self::is_digit_s(self.next_char(), false) {
            let c = self.cur_char();
            self.m_iterator += 1;

            self.m_token_builder.push(c);
            self.m_cur_token = std::mem::take(&mut self.m_token_builder);

            let (ct, last_char, last_char2) = Self::get_last_2_chars_s(&self.m_last_token);
            if ct > 0 && self.is_not_identifier_and_number_and_end_parentheses(last_char) && last_char != '?' && last_char != '!' &&
                (ct != 2 || (!(last_char2 == ':' && last_char == '>') && !(last_char2 == '%' && last_char == '>'))) {
                return self.get_operator_token_value();
            }
            let next_char = self.peek_next_valid_char(0);
            let next_char2 = self.peek_next_valid_char(1);
            let next_char3 = self.peek_next_valid_char(2);
            if self.is_not_identifier_and_begin_parentheses(next_char) && !(next_char == '<' && next_char2 == ':' && self.is_white_space(next_char3)) && !(next_char == '<' && next_char2 == '%' && self.is_white_space(next_char3)) {
                return self.get_operator_token_value();
            }
            return constants::DOT_;
        }
        else if self.cur_char() == '{' {
            self.m_iterator += 1;
            self.m_cur_token = String::from("{");
            return constants::LBRACE_;
        }
        else if self.cur_char() == '}' {
            self.m_iterator += 1;
            self.m_cur_token = String::from("}");
            return constants::RBRACE_;
        }
        else if self.cur_char() == '[' {
            self.m_iterator += 1;
            self.m_cur_token = String::from("[");
            return constants::LBRACK_;
        }
        else if self.cur_char() == ']' {
            self.m_iterator += 1;
            self.m_cur_token = String::from("]");
            return constants::RBRACK_;
        }
        else if self.cur_char() == '(' {
            self.m_iterator += 1;
            self.m_cur_token = String::from("(");
            return constants::LPAREN_;
        }
        else if self.cur_char() == ')' {
            self.m_iterator += 1;
            self.m_cur_token = String::from(")");
            return constants::RPAREN_;
        }
        else if self.cur_char() == ',' {
            self.m_iterator += 1;
            self.m_cur_token = String::from(",");
            return constants::COMMA_;
        }
        else if self.cur_char() == ';' {
            self.m_iterator += 1;
            self.m_cur_token = String::from(";");
            return constants::SEMI_;
        }
        else if (self.cur_char() == '@' && (self.next_char() == '"' || self.next_char() == '\'')) ||
            (self.cur_char() == '@' && self.next_char() == '$' && (self.peek_char(2) == '"' || self.peek_char(2) == '\'')) ||
            (self.cur_char() == '$' && self.next_char() == '@' && (self.peek_char(2) == '"' || self.peek_char(2) == '\'')) {
            let mut is_dollar = false;
            if (self.cur_char() == '@' && self.next_char() == '$') || (self.cur_char() == '$' && self.next_char() == '@') {
                self.m_iterator += 1;
                self.m_iterator += 1;
                is_dollar = true;
            }
            else {
                self.m_iterator += 1;
            }
            let line = self.m_line_number;
            let c = self.cur_char();
            self.m_iterator += 1;
            while self.cur_char() != '\0' {
                if self.cur_char() == '\n' { self.m_line_number += 1;}
                if self.cur_char() == c {
                    if self.next_char() == c {
                        self.m_token_builder.push(self.cur_char());
                        self.m_iterator += 1;
                    }
                    else {
                        break;
                    }
                }
                else {
                    self.m_token_builder.push(self.cur_char());
                }
                self.m_iterator += 1;
            }
            if self.cur_char() != '\0' {
                self.m_iterator += 1;
            }
            else {
                self.m_log.borrow().info(&format!("[error][line {}]: String cannot be ended !\n", line));
            }
            self.m_cur_token = std::mem::take(&mut self.m_token_builder);
            /*Ordinary strings keep the appearance of the source code without removing the leading and trailing blank lines.
            if (mCurToken.IndexOf('\n') >= 0) {
                mCurToken = removeFirstAndLastEmptyLine(mCurToken);
            }
            */
            if is_dollar {
                return constants::DOLLAR_STRING_;
            }
            else {
                return constants::STRING_;
            }
        }
        else {//keyword,identifier or constant
            if self.cur_char() == '"' || self.cur_char() == '\'' || self.cur_char()=='$' && (self.next_char() == '"' || self.next_char() == '\'') {//Quoted name or keyword
                let mut is_dollar = false;
                if self.cur_char() == '$' {
                    self.m_iterator += 1;
                    is_dollar = true;
                }
                let line = self.m_line_number;
                let c = self.cur_char();
                self.m_iterator += 1;
                while self.cur_char() != '\0' {
                    if self.cur_char() == '\n' { self.m_line_number += 1; }
                    if self.cur_char() == '\\' {
                        self.m_iterator += 1;
                        if self.cur_char() == 'n' {
                            self.m_token_builder.push('\n');
                        }
                        else if self.cur_char() == 'r' {
                            self.m_token_builder.push('\r');
                        }
                        else if self.cur_char() == 't' {
                            self.m_token_builder.push('\t');
                        }
                        else if self.cur_char() == 'v' {
                            self.m_token_builder.push('\x0B');
                        }
                        else if self.cur_char() == 'a' {
                            self.m_token_builder.push('\x07');
                        }
                        else if self.cur_char() == 'b' {
                            self.m_token_builder.push('\x08');
                        }
                        else if self.cur_char() == 'f' {
                            self.m_token_builder.push('\x0C');
                        }
                        else if self.cur_char() == 'u' && Self::is_digit_s(self.next_char(), true) && Self::is_digit_s(self.peek_char(2), true) && Self::is_digit_s(self.peek_char(3), true) {
                            self.m_iterator += 1;
                            //4 digits HEX
                            let h1 = self.cur_char();
                            self.m_iterator += 1;
                            let h2 = self.cur_char();
                            self.m_iterator += 1;
                            let h3 = self.cur_char();
                            self.m_iterator += 1;
                            let h4 = self.cur_char();
                            if let Some(c) = char::from_u32(((Self::char_2_int_s(h1) << 12) + (Self::char_2_int_s(h2) << 8) + (Self::char_2_int_s(h3) << 4) + Self::char_2_int_s(h4)) as u32) {
                                self.m_token_builder.push(c);
                            }
                            else {
                                //error
                            }
                        }
                        else if self.cur_char() == 'U' && Self::is_digit_s(self.next_char(), true) && Self::is_digit_s(self.peek_char(2), true) && Self::is_digit_s(self.peek_char(3), true)
                            && Self::is_digit_s(self.peek_char(4), true) && Self::is_digit_s(self.peek_char(5), true) && Self::is_digit_s(self.peek_char(6), true) && Self::is_digit_s(self.peek_char(7), true) {
                            self.m_iterator += 1;
                            //8 digits HEX
                            let h1 = self.cur_char();
                            self.m_iterator += 1;
                            let h2 = self.cur_char();
                            self.m_iterator += 1;
                            let h3 = self.cur_char();
                            self.m_iterator += 1;
                            let h4 = self.cur_char();
                            self.m_iterator += 1;
                            let h5 = self.cur_char();
                            self.m_iterator += 1;
                            let h6 = self.cur_char();
                            self.m_iterator += 1;
                            let h7 = self.cur_char();
                            self.m_iterator += 1;
                            let h8 = self.cur_char();
                            if let Some(c1) = char::from_u32(((Self::char_2_int_s(h5) << 12) + (Self::char_2_int_s(h6) << 8) + (Self::char_2_int_s(h7) << 4) + Self::char_2_int_s(h8)) as u32) {
                                if let Some(c2) = char::from_u32(((Self::char_2_int_s(h1) << 12) + (Self::char_2_int_s(h2) << 8) + (Self::char_2_int_s(h3) << 4) + Self::char_2_int_s(h4)) as u32) {
                                    self.m_token_builder.push(c1);
                                    self.m_token_builder.push(c2);
                                }
                                else{
                                    //error
                                }
                            }
                            else{
                                //error
                            }
                        }
                        else if self.cur_char() == 'x' && Self::is_digit_s(self.next_char(), true) {
                            self.m_iterator += 1;
                            //1~2 digits HEX
                            let h1 = self.cur_char();
                            if Self::is_digit_s(self.next_char(), true) {
                                self.m_iterator += 1;
                                let h2 = self.cur_char();
                                if let Some(nc) = char::from_u32(((Self::char_2_int_s(h1) << 4) + Self::char_2_int_s(h2)) as u32) {
                                    self.m_token_builder.push(nc);
                                }
                                else {
                                    //error
                                }
                            }
                            else {
                                if let Some(nc) = char::from_u32(Self::char_2_int_s(h1) as u32) {
                                    self.m_token_builder.push(nc);
                                }
                                else {
                                    //error
                                }
                            }
                        }
                        else if Self::is_digit_s(self.cur_char(), false) {
                            //1~3 digits OCT
                            let o1 = self.cur_char();
                            if Self::is_digit_s(self.next_char(), false) {
                                self.m_iterator += 1;
                                let o2 = self.cur_char();
                                if Self::is_digit_s(self.next_char(), false) {
                                    self.m_iterator += 1;
                                    let o3 = self.cur_char();
                                    if let Some(nc) = char::from_u32(((Self::char_2_int_s(o1) << 6) + (Self::char_2_int_s(o2) * 3) + Self::char_2_int_s(o3)) as u32) {
                                        self.m_token_builder.push(nc);
                                    }
                                    else {
                                        //error
                                    }
                                }
                                else {
                                    if let Some(nc) = char::from_u32(((Self::char_2_int_s(o1) << 3) + Self::char_2_int_s(o2)) as u32) {
                                        self.m_token_builder.push(nc);
                                    }
                                    else {
                                        //error
                                    }
                                }
                            }
                            else {
                                if let Some(nc) = char::from_u32(Self::char_2_int_s(o1) as u32) {
                                    self.m_token_builder.push(nc);
                                }
                                else {
                                    //error
                                }
                            }
                        }
                        else {
                            self.m_token_builder.push(self.cur_char());
                        }
                    }
                    else if self.cur_char() == c {
                        if self.next_char() == c {
                            self.m_token_builder.push(self.cur_char());
                            self.m_iterator += 1;
                        }
                        else {
                            break;
                        }
                    }
                    else {
                        self.m_token_builder.push(self.cur_char());
                    }
                    self.m_iterator += 1;
                }
                if self.cur_char() != '\0' {
                    self.m_iterator += 1;
                }
                else {
                    self.m_log.borrow().info(&format!("[error][line {}]: string can't end !\n", line));
                }
                self.m_cur_token = std::mem::take(&mut self.m_token_builder);
                /*Ordinary strings should maintain their appearance in the source code, without removing leading or trailing blank lines.
                if (mCurToken.IndexOf('\n') >= 0) {
                    mCurToken = removeFirstAndLastEmptyLine(mCurToken);
                }
                */
                if is_dollar {
                    return constants::DOLLAR_STRING_;
                }
                else {
                    return constants::STRING_;
                }
            }
            else {
                let mut is_num = true;
                let mut is_hex = false;
                let mut include_epart = false;
                let mut include_add_sub = false;
                let mut wait_finish = false;
                let mut dot_ct = 0;
                if self.cur_char() == '0' && self.next_char() == 'x' {
                    is_hex = true;
                    self.m_token_builder.push(self.cur_char());
                    self.m_iterator += 1;
                    self.m_token_builder.push(self.cur_char());
                    self.m_iterator += 1;
                }
                let mut char_ct = 0;
                while self.cur_char() == '?' || self.cur_char() == '\'' || is_num && Self::is_digit2_s(self.cur_char(), is_hex, include_epart, include_add_sub) || !self.is_special_char(self.cur_char()) {
                    if self.cur_char() == '#' {
                        break;
                    }
                    else if self.cur_char() == '?' {
                        //In the case of a nullable type (with a question mark following the type name), only one question mark is allowed.
                        if let Some(on_token_can_eat_char) = self.m_on_token_can_eat_char {
                            let c = self.cur_char();
                            if on_token_can_eat_char(&mut self.m_token_builder, c) {
                                self.m_token_builder.push(self.cur_char());
                                self.m_iterator += 1;
                                //char_ct += 1;
                            }
                        }
                        break;
                    }
                    else if self.cur_char() == '\'' {
                        if !is_num {
                            break;
                        }
                        else {
                            if self.next_char() != '\0' && !Self::is_digit2_s(self.next_char(), is_hex, include_epart, include_add_sub) {
                                break;
                            }
                            self.m_iterator += 1;
                            char_ct += 1;
                        }
                    }
                    else if self.cur_char() == '.' {
                        if !is_num || is_hex {
                            break;
                        }
                        else {
                            if self.next_char() == 'b' || self.next_char() == 'B' || self.next_char() == 'f' || self.next_char() == 'F' || self.next_char() == 'l' || self.next_char() == 'L' {
                            }
                            else if self.next_char() != '\0' && !Self::is_digit2_s(self.next_char(), is_hex, include_epart, include_add_sub) {
                                let c = self.peek_next_valid_char(1);
                                if !self.is_special_char(c) {
                                    break;
                                }
                            }
                        }
                        dot_ct += 1;
                        if dot_ct > 1 {
                            break;
                        }
                    }
                    else if is_num {
                        if dot_ct > 0 && (self.cur_char() == 'b' || self.cur_char() == 'B' || self.cur_char() == 'f' || self.cur_char() == 'F' || self.cur_char() == 'l' || self.cur_char() == 'L') {
                        }
                        else if dot_ct == 0 && char_ct > 0 && (self.cur_char() == 'l' || self.cur_char() == 'L' || self.cur_char() == 'u' || self.cur_char() == 'U' || self.cur_char() == 'z' || self.cur_char() == 'Z') {
                        }
                        else if !Self::is_digit2_s(self.cur_char(), is_hex, include_epart, include_add_sub) {
                            is_num = false;
                        }
                    }
                    if is_num && !wait_finish {
                        if include_epart && (!is_hex && (self.cur_char() == 'e' || self.cur_char() == 'E')) || (is_hex && (self.cur_char() == 'p' || self.cur_char() == 'P')) {
                            include_epart = false;
                            include_add_sub = true;
                        }
                        else if include_add_sub {
                            include_add_sub = false;
                            wait_finish = true;
                        }
                        else {
                            include_epart = true;
                        }
                    }
                    self.m_token_builder.push(self.cur_char());
                    self.m_iterator += 1;
                    char_ct += 1;
                }
                self.m_cur_token = std::mem::take(&mut self.m_token_builder);
                if is_num {
                    return constants::NUMBER_;
                }
                else {
                    return constants::IDENTIFIER_;
                }
            }
        }
    }
    pub fn peek(&self, _level: i32) -> i16// scan next token without consuming it
    {
        let token = 0;
        self.m_log.borrow().info("[info] peek_token is not called in an LL(1) grammar\n");
        return token;
    }

    pub fn set_cur_token(&mut self, tok: String)
    {
        self.m_cur_token = tok;
    }
    pub fn set_last_token(&mut self, tok: String)
    {
        self.m_last_token = tok;
    }
    pub fn enqueue_token(&mut self, tok: String, val: i16, line: i32) -> bool
    {
        self.m_token_queue.push_back(TokenInfo { m_token: tok, m_token_value: val, m_line_number: line });
        return true;
    }

    pub fn get_cur_token(&self) -> &String
    {
        return &self.m_cur_token;
    }
    pub fn get_last_token(&self) -> &String
    {
        return &self.m_last_token;
    }
    pub fn get_line_number(&self) -> i32
    {
        return self.m_line_number;
    }
    pub fn get_last_line_number(&self) -> i32
    {
        return self.m_last_line_number;
    }
    pub fn is_comment_on_new_line(&self) -> bool
    {
        return self.m_comment_on_new_line;
    }
    pub fn get_comments(&self) -> &Vec<String>
    {
        return &self.m_comments;
    }
    pub fn get_comments_mut(&mut self) -> &mut Vec<String>
    {
        return &mut self.m_comments;
    }
    pub fn reset_comments(&mut self)
    {
        self.m_comment_on_new_line = false;
        self.m_comments.clear();
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
    pub fn script_end_delimiter(&self) -> &String
    {
        return &self.m_script_end_delimiter;
    }
    pub fn string_begin_delimiter_mut(&mut self) -> &mut String
    {
        return &mut self.m_string_begin_delimiter;
    }
    pub fn string_end_delimiter_mut(&mut self) -> &mut String
    {
        return &mut self.m_string_end_delimiter;
    }
    pub fn script_begin_delimiter_mut(&mut self) -> &mut String
    {
        return &mut self.m_script_begin_delimiter;
    }
    pub fn script_end_delimiter_mut(&mut self) -> &mut String
    {
        return &mut self.m_script_end_delimiter;
    }
    pub fn on_get_token(&self) -> Option<&'a GetTokenDelegationBox>
    {
        return self.m_on_get_token;
    }
    pub fn set_on_get_token(&mut self, value: &'a GetTokenDelegationBox)
    {
        self.m_on_get_token = Some(value);
    }
    pub fn on_token_can_eat_char(&self) -> Option<&'a TokenCanEatCharDelegationBox>
    {
        return self.m_on_token_can_eat_char;
    }
    pub fn set_on_token_can_eat_char(&mut self, value: &'a TokenCanEatCharDelegationBox)
    {
        self.m_on_token_can_eat_char = Some(value);
    }

    fn is_begin(&self, delimiter: &str) -> bool
    {
        let mut ret = false;
        if !delimiter.is_empty() {
            let mut iter = delimiter.chars();
            let mut pos = self.m_iterator as usize;
            while pos < self.m_input.len() {
                if let Some(c) = iter.next() {
                    let c2 = self.m_input[pos];
                    pos += 1;
                    if c != c2 {
                        break;
                    }
                }
                else {
                    ret = true;
                    break;
                }
            }
        }
        return ret;
    }
    fn get_block_string(&self, delimiter: &str, iter: &mut usize, line: &mut i32) -> String
    {
        *line = self.m_line_number;
        if let Some(start) = self.char_to_byte_index(self.m_iterator) {
            if let Some(len) = self.m_input_str[start..].find(delimiter) {
                let end = start + len;
                let mut char_end = 0;
                if let Some(char_ix) = self.byte_to_char_index(end) {
                    char_end = char_ix;
                    *iter = char_ix + delimiter.chars().count();
                }
                else {
                    assert!(false);
                }
                let mut pos = start;
                loop {
                    if let Some(line_end) = Self::vec_char_find2_s(&self.m_input, '\n', pos, char_end - pos) {
                        pos = line_end + 1;
                        *line += 1;
                    }
                    else {
                        break;
                    }
                }
                return self.remove_first_and_last_empty_line(&self.m_input_str[start..end]);
            }
            else {
                self.m_log.borrow().info(&format!("[error][line {:?}]: block can't finish, delimiter: {:?}！\n", self.m_line_number, delimiter));
                return String::new();
            }
        }
        return String::new();
    }
    fn remove_first_and_last_empty_line(&self, str: &str) -> String
    {
        let mut start = 0;
        let ct = str.chars().count();
        let mut iter = str.chars();
        if let Some(mut c) = iter.next() {
            while start < ct && self.is_white_space(c) && c != '\n' {
                start += 1;
                if let Some(nc) = iter.next() {
                    c = nc;
                }
                else {
                    break;
                }
            }
        }
        if start < ct && iter.next() == Some('\n') {
            start += 1;
        }
        else {
            //If there is no newline at the beginning of the line, preserve the white space.
            start = 0;
        }
        let mut end = ct - 1;
        let mut riter = str.chars().rev();
        if let Some(mut c) = riter.next() {
            while end > 0 && self.is_white_space(c) && c != '\n' {
                end -= 1;
                if let Some(nc) = riter.next() {
                    c = nc;
                }
                else {
                    break;
                }
            }
        }
        if end > 0 && riter.next() != Some('\n') {
            //If there is no newline at the end of the line, preserve the white space; otherwise, remove the white space but keep the newline.
            end = ct - 1;
        }
        if start > 0 || end < ct - 1 {
            return str[start..=end].chars().collect();
        }
        else {
            return String::from(str);
        }
    }

    pub fn get_operator_token(&mut self)
    {
        let st = self.m_iterator;
        match self.cur_char() {
            '+' => {
                    self.m_iterator += 1;
                    if self.cur_char() == '+' || self.cur_char() == '=' {
                        self.m_iterator += 1;
                    }
                }
            '-' => {
                    self.m_iterator += 1;
                    if self.cur_char() == '-' || self.cur_char() == '=' || self.cur_char() == '>' {
                        self.m_iterator += 1;
                    }
                }
            '>' => {
                    self.m_iterator += 1;
                    if self.cur_char() == '=' {
                        self.m_iterator += 1;
                    }
                    else if self.cur_char() == '>' {
                        self.m_iterator += 1;
                        if self.cur_char() == '>' {
                            self.m_iterator += 1;
                        }
                        if self.cur_char() == '=' {
                            self.m_iterator += 1;
                        }
                    }
                }
            '<' => {
                    self.m_iterator += 1;
                    if self.cur_char() == '=' {
                        self.m_iterator += 1;
                        if self.cur_char() == '>' {
                            self.m_iterator += 1;
                        }
                    }
                    else if self.cur_char() == '-' {
                        self.m_iterator += 1;
                    }
                    else if self.cur_char() == '<' {
                        self.m_iterator += 1;
                        if self.cur_char() == '=' {
                            self.m_iterator += 1;
                        }
                    }
                }
            '&' => {
                    self.m_iterator += 1;
                    if self.cur_char() == '=' {
                        self.m_iterator += 1;
                    }
                    else if self.cur_char() == '&' {
                        self.m_iterator += 1;
                        if self.cur_char() == '=' {
                            self.m_iterator += 1;
                        }
                    }
                }
            '|' => {
                    self.m_iterator += 1;
                    if self.cur_char() == '=' {
                        self.m_iterator += 1;
                    }
                    else if self.cur_char() == '|' {
                        self.m_iterator += 1;
                        if self.cur_char() == '=' {
                            self.m_iterator += 1;
                        }
                    }
                }
            '=' => {
                    self.m_iterator += 1;
                    if self.cur_char() == '=' || self.cur_char() == '>' {
                        self.m_iterator += 1;
                    }
                }
            '!' | '^' | '*' | '/' | '%' => {
                    self.m_iterator += 1;
                    if self.cur_char() == '=' {
                        self.m_iterator += 1;
                    }
                }
            '?' => {
                    self.m_iterator += 1;
                    if self.cur_char() == '?' {
                        self.m_iterator += 1;
                        if self.cur_char() == '=' {
                            self.m_iterator += 1;
                        }
                    }
                }
            '`' => {
                    self.m_iterator += 1;
                    let mut is_op = false;
                    while self.is_operator(self.cur_char()) {
                        self.m_iterator += 1;
                        is_op = true;
                    }
                    if !is_op {
                        while self.cur_char() != '\0' && !self.is_special_char(self.cur_char()) {
                            if self.cur_char() == '#' {
                                break;
                            }
                            else if self.cur_char() == '.' {
                                break;
                            }
                            self.m_iterator += 1;
                        }
                    }
                }
            _ => {
                    self.m_iterator += 1;
                }
        }
        let ed = self.m_iterator;
        self.m_cur_token = self.m_input_str[st..ed].chars().collect();
    }
    pub fn get_operator_token_value(&self) -> i16
    {
        let cur_operator = &self.m_cur_token;
        let last_token = &self.m_last_token;
        let mut last_is_operator = true;
        if last_token.len() > 0 {
            let mut last_char = '\0';
            if let Some(c) = last_token.chars().next() {
                last_char = c;
            }
            if self.is_delimiter(last_char) {
                last_is_operator = true;
            }
            else if self.is_begin_parentheses(last_char) {
                last_is_operator = true;
            }
            else {
                last_is_operator = self.is_operator(last_char);
            }
        }
        let mut val = constants::OP_TOKEN_2_;
        if cur_operator.len() > 0 {
            let mut iter = cur_operator.chars();
            let c0 = iter.next();
            let mut c1 = None as Option<char>;
            let mut c2 = None as Option<char>;
            let mut c3 = None as Option<char>;
            let mut c4 = None as Option<char>;
            if cur_operator.len() > 1 {
                c1 = iter.next();
            }
            if cur_operator.len() > 2 {
                c2 = iter.next();
            }
            if cur_operator.len() > 3 {
                c3 = iter.next();
            }
            if cur_operator.len() > 4 {
                c4 = iter.next();
            }
            if c0 == Some('=') && c1 == None {
                val = constants::OP_TOKEN_1_;
            }
            else if c0 != Some('=') && c0 != Some('!') && c0 != Some('>') && c0 != Some('<') && c1 == Some('=') && c2 == None {
                val = constants::OP_TOKEN_1_;
            }
            else if c2 == Some('=') && c3 == None {
                val = constants::OP_TOKEN_1_;
            }
            else if c3 == Some('=') && c4 == None {
                val = constants::OP_TOKEN_1_;
            }
            else if c0 == Some('=') && c1 == Some('>') && c2 == None || c0 == Some('<') && c1 == Some('-') && c2 == None {
                val = constants::OP_TOKEN_2_;
            }
            else if c0 == Some(':') && c1 == None {
                if self.m_action.borrow().peek_pair_type_stack() == action::PAIR_TYPE_QUESTION_COLON {
                    val = constants::OP_TOKEN_QUESTION_COLON_;
                }
                else {
                    val = constants::OP_TOKEN_COLON_;
                }
            }
            else if c0 == Some('?') && c1 == None {
                val = constants::OP_TOKEN_QUESTION_;
            }
            else if c0 == Some('|') && c1 == Some('|') && c2 == None || c0 == Some('?') && c1 == Some('?') && c2 == None {
                val = constants::OP_TOKEN_4_;
            }
            else if c0 == Some('&') && c1 == Some('&') && c2 == None {
                val = constants::OP_TOKEN_5_;
            }
            else if c0 == Some('|') && c1 == None {
                val = constants::OP_TOKEN_6_;
            }
            else if c0 == Some('^') && c1 == None {
                val = constants::OP_TOKEN_7_;
            }
            else if c0 == Some('&') && c1 == None {
                if last_is_operator {
                    val = constants::OP_TOKEN_14_;
                }
                else {
                    val = constants::OP_TOKEN_8_;
                }
            }
            else if (c0 == Some('=') || c0 == Some('!')) && c1 == Some('=') && c2 == None || c0 == Some('<') && c1 == Some('=') && c2 == Some('>') && c3 == None {
                val = constants::OP_TOKEN_9_;
            }
            else if (c0 == Some('<') || c0 == Some('>')) && (c1 == Some('=') && c2 == None || c1 == None) {
                val = constants::OP_TOKEN_10_;
            }
            else if (c0 == Some('<') && c1 == Some('<') && c2 == None) || (c0 == Some('>') && c1 == Some('>') && c2 == None) || (c0 == Some('>') && c1 == Some('>') && c2 == Some('>') && c3 == None) {
                val = constants::OP_TOKEN_11_;
            }
            else if (c0 == Some('+') || c0 == Some('-')) && c1 == None {
                if last_is_operator {
                    val = constants::OP_TOKEN_14_;
                }
                else {
                    val = constants::OP_TOKEN_12_;
                }
            }
            else if (c0 == Some('*') || c0 == Some('/') || c0 == Some('%')) && c1 == None || c0 == Some('.') && c1 == Some('.') && c2 == None {
                if c0 == Some('*') && last_is_operator {
                    val = constants::OP_TOKEN_14_;
                }
                else {
                    val = constants::OP_TOKEN_13_;
                }
            }
            else if (c0 == Some('+') && c1 == Some('+') && c2 == None) || (c0 == Some('-') && c1 == Some('-') && c2 == None) || (c0 == Some('~') && c1 == None) || (c0 == Some('!') && c1 == None) {
                val = constants::OP_TOKEN_14_;
            }
            else if c0 == Some('`') && c1 == None {
                val = constants::OP_TOKEN_0_;
            }
            else if c0 == Some('`') && c1 != None {
                val = constants::OP_TOKEN_3_;
            }
            else if c0 == Some('-') && c1 == Some('>') && (c2 == None || c2 == Some('*') && c3 == None) ||
                c0 == Some('.') && (c1 == None || c1 == Some('*') && c2 == None) ||
                (c0 == Some(':') && c1 == Some(':') && c2 == None) {
                self.m_log.borrow().info(&format!("[warning][line {}]: Member access operation '{}' should not appear in operators", self.m_line_number, self.m_cur_token));
                val = constants::OP_TOKEN_15_;
            }
            else {
                val = constants::OP_TOKEN_3_;
            }
        }
        return val;
    }
    pub fn is_not_identifier(&self, c: char) -> bool
    {
        if '\0' == c {
           return false;
        }
        else {
            return !Self::is_letter_s(c) && c != '_' && c != '@' && c != '$';
        }
    }
    pub fn is_not_identifier_and_begin_parentheses(&self, c: char) -> bool
    {
        if '\0' == c {
           return false;
        }
        else {
            return BEGIN_PARENTHESES.find(c) == None && !Self::is_letter_s(c) && c != '_' && c != '@' && c != '$';
        }
    }
    pub fn is_not_identifier_and_number_and_end_parentheses(&self, c: char) -> bool
    {
        if '\0' == c {
            return false;
        }
        else {
            return END_PARENTHESES.find(c) == None && !Self::is_letter_or_digit_s(c) && c != '_' && c != '@' && c != '$';
        }
    }
    pub fn is_white_space(&self, c: char) -> bool
    {
        if '\0' == c {
            return false;
        }
        else {
            return WHITE_SPACES.find(c) != None;
        }
    }
    pub fn is_delimiter(&self, c: char) -> bool
    {
        if '\0' == c {
            return false;
        }
        else {
            return DELIMITERS.find(c) != None;
        }
    }
    pub fn is_begin_parentheses(&self, c: char) -> bool
    {
        if '\0' == c {
            return false;
        }
        else {
            return BEGIN_PARENTHESES.find(c) != None;
        }
    }
    pub fn is_end_parentheses(&self, c: char) -> bool
    {
        if '\0' == c {
            return false;
        }
        else {
            return END_PARENTHESES.find(c) != None;
        }
    }
    pub fn is_operator(&self, c: char) -> bool
    {
        if '\0' == c {
            return false;
        }
        else {
            return OPERATORS.find(c) != None;
        }
    }
    pub fn is_quote(&self, c: char) -> bool
    {
        if '\0' == c {
            return false;
        }
        else {
            return QUOTES.find(c) != None;
        }
    }
    pub fn is_special_char(&self, c: char) -> bool
    {
        if '\0' == c {
            return true;
        }
        else {
            return SPECIAL_CHARS.find(c) != None;
        }
    }

    pub fn cur_char(&self) -> char
    {
        return self.peek_char(0);
    }
    pub fn next_char(&self) -> char
    {
        return self.peek_char(1);
    }
    pub fn peek_char(&self, ix: usize) -> char
    {
        let mut c = 0 as char;
        if self.m_iterator + ix < self.m_input.len() {
            c = self.m_input[self.m_iterator + ix];
        }
        return c;
    }
    pub fn peek_next_valid_char(&self, begin_index: usize) -> char
    {
        let mut v = 0;
        return self.peek_next_valid_char2(begin_index, &mut v);
    }
    pub fn peek_next_valid_char2(&self, begin_index: usize, index: &mut usize) -> char
    {
        let mut next_char = '\0';
        *index = 0;
        let mut start = self.m_iterator + begin_index;
        while start < self.m_input.len() {
            if WHITE_SPACES.find(self.m_input[start]) != None {
                start += 1;
                continue;
            }
            else {
                next_char = self.m_input[start];
                *index = start - self.m_iterator;
                break;
            }
        }
        return next_char;
    }
    pub fn char_to_byte_index(&self, char_index: usize) -> Option<usize>
    {
        if char_index >= self.m_char_byte_index.len() {
            return None;
        }
        else{
            return Some(self.m_char_byte_index[char_index]);
        }
    }
    pub fn byte_to_char_index(&self, byte_index: usize) -> Option<usize>
    {
        if byte_index >= self.m_byte_char_index.len() {
            return None;
        }
        else{
            return Some(self.m_byte_char_index[byte_index]);
        }
    }

    pub fn char_to_byte_index_s(s: &str, char_index: usize) -> Option<usize>
    {
        if let Some((ix, _c)) = s.char_indices().nth(char_index) {
            return Some(ix);
        }
        else {
            return None;
        }
    }
    pub fn byte_to_char_index_s(s: &str, byte_index: usize) -> Option<usize>
    {
        if byte_index > s.len() {
            return None;
        }

        let mut char_index = 0;
        let mut current_byte_index = 0;

        for (i, _c) in s.char_indices() {
            if i == byte_index {
                return Some(char_index);
            }
            current_byte_index = i;
            char_index += 1;
        }

        if current_byte_index + s[current_byte_index..].len() == byte_index {
            return Some(char_index);
        }

        None
    }
    pub fn vec_char_find_s(vec: &Vec<char>, c: char, start: usize) -> Option<usize>
    {
        for (i, v) in vec.iter().skip(start).enumerate() {
            if c == *v {
                return Option::Some(start + i);
            }
        }
        return None;
    }
    pub fn vec_char_find2_s(vec: &Vec<char>, c: char, start: usize, len: usize) -> Option<usize>
    {
        for (i, v) in vec.iter().skip(start).enumerate() {
            if i >= len {
                break;
            }
            else if c == *v {
                return Option::Some(start + i);
            }
        }
        return None;
    }
    pub fn get_last_char_s(str: &str) -> (usize, char)
    {
        let ct = str.chars().count();
        let mut rchars = str.chars().rev();
        if let Some(last_char) = rchars.next() {
            return (ct, last_char);
        }
        else {
            return (ct, '\0');
        }
    }
    pub fn get_last_2_chars_s(str: &str) -> (usize, char, char)
    {
        let ct = str.chars().count();
        let mut rchars = str.chars().rev();
        if let Some(last_char) = rchars.next() {
            if let Some(last_char2) = rchars.next() {
                return (ct, last_char, last_char2);
            }
            else {
                return (ct, last_char, '\0');
            }
        }
        else {
            return (ct, '\0', '\0');
        }
    }
    pub fn is_digit_s(c: char, is_hex: bool) -> bool
    {
        return Self::is_digit2_s(c, is_hex, false, false);
    }
    pub fn is_digit2_s(c: char, is_hex: bool, include_epart: bool, include_add_sub: bool) -> bool
    {
        let ret;
        if is_hex {
            if include_epart && (c == 'P' || c == 'p') {
                ret = true;
            }
            else if include_add_sub && (c == '+' || c == '-') {
                ret = true;
            }
            else if (c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F') {
                ret = true;
            }
            else {
                ret = false;
            }
        }
        else {
            if include_epart && (c == 'E' || c == 'e') {
                ret = true;
            }
            else if include_add_sub && (c == '+' || c == '-') {
                ret = true;
            }
            else if c >= '0' && c <= '9' {
                ret = true;
            }
            else {
                ret = false;
            }
        }
        return ret;
    }
    pub fn char_2_int_s(c: char) -> u32
    {
        if c >= '0' && c <= '9' {
            return c as u32 - '0' as u32;
        }
        else if c >= 'a' && c <= 'f' {
            return 10 + c as u32 - 'a' as u32;
        }
        else if c >= 'A' && c <= 'F' {
            return 10 + c as u32 - 'A' as u32;
        }
        else {
            return 0;
        }
    }
    pub fn is_white_space_s(c: char) -> bool
    {
        match c {
            ' ' | '\t' | '\r' | '\n' => true,
            _ => false,
        }
    }
    pub fn is_letter_s(c : char) -> bool
    {
        match c {
            'a'..='z' | 'A'..='Z' => true,
            _ => false,
        }
    }
    pub fn is_letter_or_digit_s(c : char) -> bool
    {
        match c {
            'a'..='z' | 'A'..='Z' | '0'..='9' => true,
            _ => false,
        }
    }
}
