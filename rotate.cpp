#include <iostream>
#include <algorithm>
#include <vector>

template<typename T>
void printVector(std::vector<T> const& v) {
    for (auto const& i : v) {
        std::cout << i << " ";
    }

    std::cout << "\n";
}

auto main(int argc, char* argv[]) -> int {
    std::vector<float> v = {1.2f, 2.f, 3.5f};
    std::cout << "Original: \t";
    printVector(v);

    std::rotate(v.begin(), v.begin() + 1, v.end());
    std::cout << "Rotate Left: \t";
    printVector(v);

    std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
    std::cout << "Rotate Right: \t";
    printVector(v);

    return 0;
}
