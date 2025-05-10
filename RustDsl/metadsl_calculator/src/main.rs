pub mod dsl_expression;

use dsl_expression::dsl_calculator::DslCalculator;
use metadsl::dsl::{DslFile, DslLogDelegationBox};

#[cfg(not(target_arch = "wasm32"))]
mod impl_mod {
use std::io::Write;
use std::rc::Rc;
use rustyline::{error::ReadlineError, history::FileHistory};
use rustyline::Editor;

use crate::dsl_expression::dsl_calculator::{DslCalculator, DslCalculatorCell};
use metadsl::dsl::{DslFile, DslLogDelegationBox};

pub fn interactive_execution(calculator: &Rc<DslCalculatorCell>, log_callback: &DslLogDelegationBox) {
    if let Result::Ok(mut rl) = Editor::<(), FileHistory>::new() {
        let mut dsl_file = DslFile::new();

        loop {
            let readline = rl.readline(">> ");
            match readline {
                Ok(line) => {
                    let command = line.trim();
                    match command {
                        "q" | "quit" | "exit" => {
                            println!("bye!");
                            break;
                        }
                        s => {
                            dsl_file.clear();
                            let content = format!("script(main){{{}}};", s);
                            dsl_file.load_from_string(String::from(content), &log_callback);
                            if let Some(info) = dsl_file.dsl_infos().last() {
                                calculator.borrow_mut().clear();
                                DslCalculator::load_dsl_info(&calculator, info);
                                let ret = DslCalculator::calc_0(&calculator, &"main");
                                println!("result:{}", ret.to_string());
                                let _ = std::io::stdout().flush();
                            }
                        }
                    }
                    if let Result::Err(err) = rl.add_history_entry(command) {
                        println!("add history error: {}", err);
                    }
                },
                Err(ReadlineError::Interrupted) | Err(ReadlineError::Eof) => {
                    println!("exit.");
                    break;
                },
                Err(err) => {
                    println!("error: {:?}", err);
                    break;
                }
            }
        }
    }
}
}

fn main() {
    let log_callback: DslLogDelegationBox = Box::new(|info| {
        println!("log: {}", info);
    });
    let calculator = DslCalculator::new_cell();
    {
        calculator.borrow_mut().on_log = Some(&log_callback);
        calculator.borrow_mut().init();
        let mut dsl_file = DslFile::new();
        let content = "script(main){echo('1+2*3=',1+2*3,'\n');};";
        dsl_file.load_from_string(String::from(content), &log_callback);
        if let Some(info) = dsl_file.dsl_infos().last() {
            DslCalculator::load_dsl_info(&calculator, info);
            DslCalculator::calc_0(&calculator, &"main");
        }
        println!("begin interactive execution...");
        #[cfg(not(target_arch = "wasm32"))]
        impl_mod::interactive_execution(&calculator, &log_callback);
    }
}
