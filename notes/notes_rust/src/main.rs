use num_derive::FromPrimitive;
use num_traits::FromPrimitive;
use rand::distributions::{Distribution, Uniform};
use std::collections::HashSet;
use std::fmt;
use std::io::stdin;
use variant_count::VariantCount;

#[derive(FromPrimitive, VariantCount, Debug, PartialEq, Eq, Hash)]
enum Notes {
    A,
    ASharp,
    B,
    C,
    CSharp,
    D,
    DSharp,
    E,
    F,
    FSharp,
    G,
    GSharp,
}

impl fmt::Display for Notes {
    fn fmt(&self, f: &mut fmt::Formatter) -> fmt::Result {
        match self {
            Notes::A => write!(f, "A"),
            Notes::ASharp => write!(f, "A♯/B♭"),
            Notes::B => write!(f, "B"),
            Notes::C => write!(f, "C"),
            Notes::CSharp => write!(f, "C♯/D♭"),
            Notes::D => write!(f, "D"),
            Notes::DSharp => write!(f, "D♯/E♭"),
            Notes::E => write!(f, "E"),
            Notes::F => write!(f, "F"),
            Notes::FSharp => write!(f, "F♯/G♭"),
            Notes::G => write!(f, "G"),
            Notes::GSharp => write!(f, "G♯/A♭"),
        }
    }
}

fn main() {
    let rng = rand::thread_rng();
    let dist = Uniform::new(0, Notes::VARIANT_COUNT);
    let mut get_note = dist.sample_iter(rng);

    let mut seen_notes = HashSet::new();

    while seen_notes.len() < Notes::VARIANT_COUNT {
        let num = get_note.next().unwrap();
        let note = Notes::from_usize(num).unwrap();

        if !seen_notes.contains(&note) {
            println!("{}", note);
            seen_notes.insert(note);

            let mut buffer = String::new();
            stdin().read_line(&mut buffer).unwrap();
            println!("\n\n");
        }
    }

    println!("Done!")
}
