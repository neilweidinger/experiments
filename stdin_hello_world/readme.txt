To run dynamically linked rust binary:

$ LD_LIBRARY_PATH=$(rustc --print sysroot)/lib/rustlib/x86_64-apple-darwin/lib ./rust_binary_dynamically_linked
