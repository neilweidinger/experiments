use std::io;
use std::io::Write;

fn main() {
    loop {
        match user_number_input() {
            i32::MIN..=-1 => println!("negative"),
            0..=5 => println!("smol"),
            6..=11 => println!("bigger"),
            12..=i32::MAX => println!("biggest"),
        }

        if !play_again() {
            return ();
        }
    }
}

fn user_number_input() -> i32 {
    loop {
        print!("Enter a number: ");
        io::stdout().flush().unwrap();

        match read_input().trim().parse::<i32>() {
            Ok(num) => return num,
            Err(_) => eprintln!("Could not parse as signed integer, please try again"),
        }
    }
}

fn play_again() -> bool {
    print!("Play again?: [y/n] ");
    io::stdout().flush().unwrap();

    loop {
        match read_input().trim().to_lowercase().as_str() {
            "y" | "yes" => return true,
            "n" | "no" => return false,
            _ => {
                print!("Could not parse, please enter again: [y/n] ");
                io::stdout().flush().unwrap();
            }
        };
    }
}

fn read_input() -> String {
    let mut buffer = String::new();

    io::stdin()
        .read_line(&mut buffer)
        .expect("Failed to read line from input");

    buffer
}
