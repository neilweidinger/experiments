use num_derive::FromPrimitive;
use num_traits::FromPrimitive;
use rand::Rng;
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

impl Default for Notes {
    fn default() -> Self {
        Notes::A
    }
}

fn generate_note_permutation() -> [Notes; Notes::VARIANT_COUNT] {
    let mut perm = generate_ascending_array::<{ Notes::VARIANT_COUNT }>();
    shuffle(&mut perm);

    let mut notes_perm: [Notes; Notes::VARIANT_COUNT] = Default::default();

    for (i, val) in perm.iter().enumerate() {
        notes_perm[i] = Notes::from_usize(*val).unwrap();
    }

    notes_perm
}

const fn generate_ascending_array<const N: usize>() -> [usize; N] {
    let mut a = [0; N];
    let mut i = 0;

    while i < N {
        a[i] = i;
        i += 1;
    }

    a
}

fn shuffle<T>(arr: &mut [T]) {
    let mut rng = rand::thread_rng();

    for i in (1..arr.len()).rev() {
        arr.swap(i, rng.gen_range(0..i));
    }
}

fn over_engineered_version() {
    let perm = generate_note_permutation();

    for note in perm.iter() {
        println!("{}", note);

        let mut buffer = String::new();
        stdin().read_line(&mut buffer).unwrap();
        println!("\n\n");
    }

    println!("Done!")
}

#[allow(dead_code)]
fn simple_version() {
    let mut perm: Vec<_> = (0_usize..Notes::VARIANT_COUNT).collect();
    shuffle(&mut perm);

    for i in perm {
        println!("{}", Notes::from_usize(i).unwrap());

        let mut buffer = String::new();
        stdin().read_line(&mut buffer).unwrap();
        println!("\n\n");
    }

    println!("Done!")
}

fn main() {
    over_engineered_version();
    // simple_version();
}
