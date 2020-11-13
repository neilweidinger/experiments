#include <iostream>
#include <string>

auto main(int argc, char* argv[]) -> int {
    std::cout << "Enter input: ";

    std::string input;
    std::cin >> input;

    std::cout << input << "\n";

    // can't do switch statements on strings in C++
    if (input == "hello") {
        std::cout << "hi!\n";
    }
    else if (input == "world") {
        std::cout << "hey\n";
    }
    else {
        std::cout << "hello?\n";
    }
}
