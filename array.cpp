#include <iostream>
#include <array>
#include <cstdio>

int main(int argc, char* argv[]) {
    constexpr size_t capacity = 5;
    std::array<char, capacity> p;

    /* for (int i = 0; i < capacity; i++) { */
    /*     p[i] = 'x';  // just so that data() always returns non null */
    /*     std::snprintf((p.data() + i), 2, "%s", "a");  // data() may return null if p is empty */
    /* } */

    p[0] = 'x';
    std::snprintf(p.data(), 10, "%s", "123456789");  // data() may return null if p is empty

    std::sprintf(p.data(), "%s", "abc");

    std::cout << "Len: " << std::strlen(p.data()) << "\n";

    for (char c : p) {
        std::cout << c << "\n";
    }

    for (int i = 0; (p.data())[i] != '\0'; i++) {
        std::cout << (p.data())[i] << "\n";
    }

    return 0;
}
