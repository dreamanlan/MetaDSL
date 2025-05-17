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
                                calculator.borrow_mut().clear_stacks();
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
        let content = r#"
            script(main){
                @a=456;
                $b=789;
                echo('1+2*3=',1+2*3,' a:',@a,' b:',$b,'\n');
                loop(5){
                    echo("loop:",$$+1,'\n');
                };
                looplist([1,2,3,4,5]){
                    echo("looplist:",$$,'\n');
                };
                foreach(1,2,3,4,5){
                    echo("foreach:",$$,'\n');
                };
                $ct=5;
                $ix=0;
                while($ix<$ct){
                    echo("while:",$ix,"<",$ct,'\n');
                    $ix = $ix + 1;
                };
                $a=$ix;
                $b=$ct;
                if($a<$b){
                    echo($a,"<",$b,"=>yes",'\n');
                }elif($a==$b){
                    echo($a,"==",$b,"=>yes",'\n');
                }else{
                    echo($a,"<=",$b,"=>no",'\n');
                };

                ($v1,$v2,$v3,$v4,$v5,$v6,$v7,$v8,$v9,$v10)=(1,2,3,4,5,6,7,8,9,10);
                echo($v1,$v2,$v3,$v4,$v5,$v6,$v7,$v8,$v9,$v10,'\n');

                if( ($a1,($b1),($c1))=(3,(5),(4)) ){
                    echo($a1,$b1,$c1,'\n');
                };

                if( ($a2,($b2,$c2))=(3,(5,4)) ){
                    echo($a2,$b2,$c2,'\n');
                };

                ($a,$b)=sincos(1.57);
                echo($a,",",$b,'\n');

                echo(format("{} {}\n", 1231, 456));
            };
        "#;
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
