#include <iostream>

struct MyData {
    char a;
    char b;
    char c;
    int32_t i;
    char d; // try removing and adding this back in to see change in size of struct
        
    friend auto operator<<(std::ostream& os, MyData const& obj) -> std::ostream&;
};

auto operator<<(std::ostream& os, MyData const& obj) -> std::ostream& {
    os << obj.a << ' ' << obj.i;

    return os;
}

// http://www.catb.org/esr/structure-packing/
auto main(int argc, char* argv[]) -> int {
    MyData t = {'a', 'b', 'c', 1234};

    std::cout << t << '\n';
    std::cout << sizeof(t) << '\n';
}
