#include <iostream>
#include <string>

// Program to convert BCD encoded numbers
// Basically pointless because input is given in hex
auto main(int argc, char* argv[]) -> int {
    while (true) {
        std::cout << "Enter hex value (or q to quit): \n";

        std::string input;
        std::cin >> input;

        if (input == "q") {
            break;
        }

        auto bcd = std::stoi(input, 0, 16);
        std::cout << "Raw BCD value: " << bcd << "\n";
        std::cout << "BCD value: " << ((bcd & 0xF0) >> 1) + ((bcd & 0xF0) >> 3) + (bcd & 0x0F) << "\n\n";
    }

    return 0;
}
