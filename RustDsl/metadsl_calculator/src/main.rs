pub mod dsl_expression;

use dsl_expression::dsl_calculator::DslCalculator;
use metadsl::dsl::{DslFile, DslLogDelegationBox};

fn main() {
    let log_callback: DslLogDelegationBox = Box::new(|info| {
        println!("log: {}", info);
    });
    let calculator = DslCalculator::new_cell();
    {
        calculator.borrow_mut().on_log = Some(&log_callback);
        calculator.borrow_mut().init(calculator.clone());
        let mut dsl_file = DslFile::new();
        let content = "script(main){echo(1+2*3);};";
        dsl_file.load_from_string(String::from(content), &log_callback);
        if let Some(info) = dsl_file.dsl_infos().last() {
            DslCalculator::load_dsl_info(&calculator, info);
            calculator.borrow_mut().calc_0(&"main");
        }
        println!("Hello, world!");
    }
}
