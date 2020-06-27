#include <iostream>
#include <algorithm>

auto main(int argc, char* argv[]) -> int {
    int x = 1;
    int y = 2;

    // template parameter deduction, works because both parameters are of same type (int)
    std::cout << "Max of " << x << " and " << y << ": " << std::max(x, y) << std::endl;

    int a = 2;
    double b = 2.1;

    // technically works, but only because we explicitly say that the parameters are of type int.
    // rememeber that std::max only takes ONE template paramter.
    // logically does NOT work, since b is cast into an int which means we are essentially
    // comparing 2 and 2 now, resulting in std::max(2, 2.1) = 2
    std::cout << "Max of " << a << " and " << b << ": " << std::max<int>(a, b) << std::endl;

    return 0;
}
