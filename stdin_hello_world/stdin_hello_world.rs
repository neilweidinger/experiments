use std::io;
use std::io::Write;

fn main() {
    print!("Enter input: ");

    if let Err(e) = io::stdout().flush() {
        eprintln!("Error flushing to stdout: {:?}", e);
    }

    let mut input = String::new();

    io::stdin()
        .read_line(&mut input)
        .expect("Error reading from stdin");

    let input = input.trim_end();

    println!("Input: {}", input);

    match &input[..] {
        "hello" => println!("hi!"),
        "world" => println!("hey"),
        _ => println!("hello?"),
    }
}
