struct C {
    data: String,
}

impl C {
    fn print_data(&self) {
        println!("{}", self.data)
    }
}

fn safe_borrow(object: &C) {
    let borrowed = object;
    borrowed.print_data();
}

fn move_object(object: C) {
    let moved = object;
    moved.print_data();
}

fn main() {
    {
        let a = C {
            data: "hello world".to_string(),
        };

        a.print_data();

        safe_borrow(&a);

        a.print_data();
    }

    println!("----------------------------");

    {
        let a = C {
            data: "hello world".to_string(),
        };

        a.print_data();

        move_object(a);

        // a.print_data(); // will not compile as it is not safe to use moved from object
    }
}
