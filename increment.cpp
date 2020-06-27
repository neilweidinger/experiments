#include <iostream>

template<typename T>
auto increment(T const& val) -> T {
    return val + 1;
}

auto main(int argc, char* argv[]) -> int {
    auto x = 2.1f;

    std::cout << "Original: \t" << x << " \n";
    std::cout << "Incremented: \t" << increment(x) << std::endl;

    return 0;
}
