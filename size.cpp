#include <iostream>
#include <cstddef>

int main(int argc, char* argv[]) {
    std::size_t a = 10;
    std::size_t b = 20;

    std::cout << "a: \t\t" << a << "\n" << "b: \t\t" << b << "\n\n";

    std::cout << "(b - a): \t" << (b - a) << "\n";
    std::cout << "(a - b): \t" << (a - b) << "\n";

    return 0;
}
