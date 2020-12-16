#include <iostream>
#include <string>
#include <unordered_map>

// expects a valid numeral (does not accept empty strings)
int romanNumeralValue(const std::string& numeral) {
    // static lifetime to only initialize once in program
    static std::unordered_map<char, int> roman_map = {
        {'I', 1},
        {'V', 5},
        {'X', 10},
        {'L', 50},
    };
    
    int value = 0;
    
    for (int i = 0; i < numeral.size() - 1; i++) {
        auto current = roman_map.at(numeral.at(i));
        auto next = roman_map.at(numeral.at(i + 1));
        
        if (current < next) {
            value -= current;
        }
        else {
            value += current;
        }
    }

    // add value of final character, input string needs to be non-empty
    value += roman_map.at(numeral.at(numeral.size() - 1));
    
    return value;
}

// returns true if numeral a is less than b, false otherwise
bool compareRomanNumerals(const std::string& a, const std::string& b) {
    return romanNumeralValue(a) < romanNumeralValue(b);
}

auto main() -> int {
    std::cout << romanNumeralValue("IV") << "\n";
    std::cout << romanNumeralValue("IX") << "\n";

    return 0;
}
