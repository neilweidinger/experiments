#include <iostream>

struct Data {
    char buf1[5];
    char buf2[5];
};

void cpy(const char* src, char* dst) {
    if (src == nullptr) return;

    while (*src) {
        *dst = *src;
        src++;
        dst++;
    }

    *dst = '\0';
}

/*
 * Run in lldb. Struct buffer fields should be right after each other with no padding.
 * Read memory of t.buf1: `memory read --size 1 --format Y --count 10 &t.buf1`
 * Read memory of t.buf2: `memory read --size 1 --format Y --count 10 &t.buf2`
 *
 * `fr v -L` to show addresses of variables
 * `help format` to show formatting options
 */
auto main(int argc, char* argv[]) -> int {
    Data t;

    cpy(argv[1], t.buf1);  // possible buffer overflow!

    std::cout << t.buf1 << "\n";
    std::cout << t.buf2 << "\n";

    return 0;
}
