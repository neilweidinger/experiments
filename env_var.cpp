#include <iostream>
#include <cstdlib>

auto main(int argc, char* argv[]) -> int {
    if (char const* env_path = std::getenv("PATH")) {
        std::cout << "Your PATH is: " << env_path << "\n";
    }

    return 0;
}
