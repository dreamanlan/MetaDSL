pub mod dsl_expression;
use dsl_expression::dsl_calculator::create_class_factory;
use metadsl::dsl::{
    DslFile,
    DslLogDelegationBox,
};
use crate::dsl_expression::dsl_calculator::{
    DslCalculator,
};

#[cfg(not(target_arch = "wasm32"))]
mod impl_mod {
use std::io::Write;
use std::rc::Rc;
use std::u32;
use rustyline::{error::ReadlineError, history::FileHistory};
use rustyline::Editor;

use crate::dsl_expression::dsl_calculator::{
    DslCalculator,
    DslCalculatorCell,
    DslCalculatorValue,
    IObjectDispatch,
};
use metadsl::dsl::{
    DslFile,
    DslLogDelegationBox,
};
use metadsl_macros::{
    add_object_dispatch_fields,
    impl_object_dispatch,
};
#[add_object_dispatch_fields]
struct ObjectTest
{
    m_test: Option<String>,
}
impl Default for ObjectTest
{
    fn default() -> Self
    {
        ObjectTest {
            m_test: None,

            m_obj_id: u32::MAX,
        }
    }
}
impl IObjectDispatch<'_> for ObjectTest
{
    fn get_class_name(&self) -> &str
    {
        "ObjectTest"
    }
    fn get_dispatch_id(&self, name: &str) -> u32
    {
        if name == "test" {
            return 1;
        }
        else if name == "test_call" {
            return 2;
        }
        return u32::MAX;
    }
    fn get_property(&self, disp_id: u32) -> Option<DslCalculatorValue>
    {
        match disp_id {
            1 => {
                if let Some(test) = &self.m_test {
                    return Some(DslCalculatorValue::String(test.clone()));
                }
            }
            _ => {
            }
        }
        return None;
    }
    fn set_property(&mut self, disp_id: u32, val: &DslCalculatorValue)
    {
        match disp_id {
            1 => {
                self.m_test = Some(val.to_string());
            }
            _ => {
            }
        }
    }
    fn invoke_method(&mut self, disp_id: u32, args: &Vec<&DslCalculatorValue>) -> Option<DslCalculatorValue>
    {
        match disp_id {
            2 => {
                if let Some(test) = &self.m_test {
                    return Some(DslCalculatorValue::String(args[0].to_string() + ":" + test));
                }
            }
            _ => {
            }
        }
        return None;
    }

    impl_object_dispatch!();
}

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
        calculator.borrow_mut().register_class("ObjectTest", "test object api", create_class_factory::<impl_mod::ObjectTest>());
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

                $a = [13,2,4,5].orderbydesc($$);
                echo($a[0],",",$a[1],",",$a[2],",",$a[3],'\n');

                $obj = objectnew(ObjectTest);
                $obj.test = "test";
                echo("call:",$obj.test_call("some info")," get:",$obj.test,'\n');
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
