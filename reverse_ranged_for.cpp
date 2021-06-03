#include <iostream>
#include <vector>

template <typename T>
struct reverse_wrapper {
    T& iterable;
};

template <typename T>
auto begin(reverse_wrapper<T> rw) {
    return std::rbegin(rw.iterable);
}

template <typename T>
auto end(reverse_wrapper<T> rw) {
    return std::rend(rw.iterable);
}

template <typename T>
auto reverse(T&& iterable) -> reverse_wrapper<T> {
    return { iterable };
}

auto main(int argc, char* argv[]) -> int {
    std::vector v = {1, 2, 3};

    for (auto i : v) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    for (auto i : reverse(v)) {
        std::cout << i << ' ';
    }
    std::cout << '\n';

    return 0;
}
