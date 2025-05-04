use std::env;

pub mod dsl;
mod entry;

pub fn main()
{
    let args: Vec<String> = env::args().collect();
    entry::main(args);
}