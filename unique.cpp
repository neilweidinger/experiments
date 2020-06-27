#include <iostream>
#include <memory>
#include <cstdio>

int main(int argc, char* argv[]) {
    size_t capacity = 10;

    std::unique_ptr<char[]> p(new char[capacity]);

    for (int i = 0; i < capacity; i++) {
        /* std::snprintf(&p[i], 2, "%s", "z"); */
        std::snprintf((p.get() + i), 2, "%s", "a");
    }

    for (int i = 0; i < capacity; i++) {
        std::cout << p[i] << "\n";
    }

    return 0;
}
