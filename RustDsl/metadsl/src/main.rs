pub mod dsl;
mod entry;

use std::env;

pub fn main()
{
    let args: Vec<String> = env::args().collect();
    entry::main(args);
}