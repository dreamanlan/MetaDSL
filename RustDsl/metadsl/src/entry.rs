#[cfg(not(target_arch = "wasm32"))]
mod impl_mod {

use lazy_static::lazy_static;
use std::time::Instant;
use std::fs;
use crate::dsl::common::action::{DslActionCell, GetTokenDelegationBox};
use crate::dsl::DslLogDelegationBox;
use crate::dsl::DslFile;
use crate::dsl::parser::token::DslToken;

lazy_static! {
    static ref g_time: Instant = Instant::now();
}

fn get_local_milliseconds() -> u128
{
    return g_time.elapsed().as_millis();
}

pub fn impl_main(_args: Vec<String>)
{
    println!("cur dir:{:?}", std::env::current_dir().unwrap().display());

    let log_callback: DslLogDelegationBox = Box::new(|msg| {
        println!("{:?}", msg);
    });

    let mut key_buffer: Vec<String> = Vec::new();
    let mut id_buffer: Vec<String> = Vec::new();

    let mut file = DslFile::new();
    //Modify the return statement to the 'return <-' syntax, ensuring that the return is at a shallow level
    //of semantic data for easier subsequent processing.
    let token_callback: GetTokenDelegationBox = Box::new(|_action: &DslActionCell, dsl_token: &mut DslToken, tok: &mut str, _val: &mut i16, line:&mut i32| {
        if tok == "return" {
            let old_cur_token = dsl_token.get_cur_token().clone();
            let old_last_token = dsl_token.get_last_token().clone();
            let mut index = 0;
            let nc = dsl_token.peek_next_valid_char2(0, &mut index);
            if nc == '<' && dsl_token.peek_char(index + 1) == '-' {
                return false;
            }
            dsl_token.set_cur_token(String::from("<-"));
            dsl_token.set_last_token(old_cur_token.clone());
            let cur_tok = dsl_token.get_cur_token().clone();
            dsl_token.enqueue_token(cur_tok, dsl_token.get_operator_token_value(), *line);
            dsl_token.set_cur_token(old_cur_token);
            dsl_token.set_last_token(old_last_token);
        }
        return true;
    });
    file.set_on_get_token(&token_callback);
    file.load_from_file("test.txt", &log_callback);

    let _ = file.save_to_file("copy.txt");
    let _ = file.save_binary_file("binary.txt");

    file.clear();

    if let Ok(code) = fs::read("binary.txt") {
        file.load_binary_code(&code, &mut key_buffer, &mut id_buffer);

        let _ = file.save_to_file("unbinary.txt");

        let t1 = get_local_milliseconds();
        let mut i = 0;
        while i < 1000 {
            file.load_binary_code(&code, &mut key_buffer, &mut id_buffer);
            i += 1;
        }
        let t2 = get_local_milliseconds();
        println!("time:{}", t2 - t1);
    }
}
}

pub fn main(_args: Vec<String>)
{
    #[cfg(not(target_arch = "wasm32"))]
    impl_mod::impl_main(_args);
}