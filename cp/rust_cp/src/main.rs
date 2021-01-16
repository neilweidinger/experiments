use anyhow::{bail, Context, Result};
use nix::fcntl::{self, OFlag};
use nix::sys::stat::Mode;
use nix::unistd;

fn main() -> Result<()> {
    let args: Vec<_> = std::env::args().collect();

    if args.len() != 3 {
        bail!("Usage: cp source_file target_file");
    }

    let source_name = &args[1];
    let dest_name = &args[2];

    let source = fcntl::open(source_name.as_str(), OFlag::O_RDONLY, Mode::empty())
        .with_context(|| format!("Failed to open {}", source_name))?;

    let dest = fcntl::open(
        dest_name.as_str(),
        OFlag::O_CREAT | OFlag::O_WRONLY | OFlag::O_TRUNC,
        Mode::from_bits_truncate(0o644),
    )
    .with_context(|| format!("Failed to open {}", source_name))?;

    loop {
        let mut buffer = [0_u8; 4096];
        let bytes_read = unistd::read(source, &mut buffer)
            .with_context(|| format!("Failed to read from {}", source_name))?;

        if bytes_read == 0 {
            break;
        }

        unistd::write(dest, &buffer[..bytes_read])
            .with_context(|| format!("Failed to write to {}", dest_name))?;
    }

    unistd::close(source).with_context(|| format!("Failed to close {}", source_name))?;
    unistd::close(dest).with_context(|| format!("Failed to close {}", dest_name))?;

    Ok(())
}
