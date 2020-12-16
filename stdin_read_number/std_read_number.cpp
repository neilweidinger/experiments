#include <iostream>
#include <string>
#include <algorithm>

auto user_number_input() -> int;
auto read_input() -> std::string;
auto play_again() -> bool;

auto main(int argc, char* argv[]) -> int {
    while (true) {
        auto i = user_number_input();

        if (i <= -1) {
            std::cout << "negative\n";
        }
        else if (i <= 5) {
            std::cout << "smol\n";
        }
        else if (i <= 11) {
            std::cout << "bigger\n";
        }
        else {
            std::cout << "biggest\n";
        }

        if (!play_again()) {
            return 0;
        }
    }
}

auto user_number_input() -> int {
    while (true) {
        std::cout << "Enter a number: " << std::flush;

        try {
            return std::stoi(read_input());
        }
        catch (std::invalid_argument const& e) {
            std::cerr << "Could not parse as signed integer, please try again\n";
        }
    }
}

auto play_again() -> bool {
    std::cout << "Play again?: [y/n] " << std::flush;

    while (true) {
        auto s = read_input();

        std::transform(std::begin(s), std::end(s), std::begin(s),
                [](unsigned char c) { return std::tolower(c); });

        if (s == "y" || s == "yes") {
            return true;
        }
        else if (s == "n" || s == "no") {
            return false;
        }
        else {
            std::cerr << "Could not parse, please enter again: [y/n] " << std::flush;
        }
    }
}

auto read_input() -> std::string {
    std::string buffer;
    std::cin >> buffer;

    return buffer;
}
