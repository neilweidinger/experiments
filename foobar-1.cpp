#include <iostream>
#include <vector>
#include <string>

template <typename T>
constexpr void printVector(std::vector<T> const& v) {
    for (auto const& e : v) {
        std::cout << e << " ";
    }

    std::cout << "\n";
}

auto shortestRepeatingSubstringLength(std::string const& in) -> int {
    if (in.length() == 0) {
        return 0;
    }

    std::vector<int> next(in.length(), 0);

    for (int i = 1; i < in.length(); i++) {
        int k = next.at(i - 1);

        while (true) {
            if (in.at(i) == next.at(k)) {
                next.at(i) = k + 1;
                break;
            }
            else if (k == 0) {
                next.at(i) = 0;
                break;
            }
            else {
                k = next.at(k - 1);
            }
        }
    }

    printVector(next);
    int substringLen = in.length() - next.at(in.length() - 1);

    return (in.length() / substringLen);
}

auto main(int argc, char* argv[]) -> int {
    std::string const s{"abcabcabc"};

    std::cout << shortestRepeatingSubstringLength(s) << std::endl;

    return 0;
}
