#include <iostream>
#include <string>
#include <algorithm>

auto main(int argc, char* argv[]) -> int {
    if (argc != 3) {
        std::cerr << "Usage: ./a.out <maintenance calories> <body_weight_kg>\n";
        return 1;
    }

    /* auto maintenance_cals = std::stoi(argv[1]); */
    std::string maintenance_cals_str(argv[1]);
    maintenance_cals_str.erase(std::remove(std::begin(maintenance_cals_str),
                           std::end(maintenance_cals_str), ','),
                           std::end(maintenance_cals_str));

    auto maintenance_cals = std::stoi(maintenance_cals_str);
    auto bulk_surplus_cals = 500;
    auto total_cals = maintenance_cals + bulk_surplus_cals;

    auto body_weight = std::stod(argv[2]) * 2.2;
    auto protein_g = body_weight * 1.1; // 1.1 g protein per lb bw
    auto fat_g = total_cals * 0.25 / 9; // 25% of calories from fat
    auto carbs_g = (total_cals - ((protein_g * 4) + (fat_g * 9))) / 4; // rest from carbs

    std::cout << "Maintenance calories: " << maintenance_cals << '\n';
    std::cout << "Total calories: " << maintenance_cals + bulk_surplus_cals << '\n';
    std::cout << "Protein: " << protein_g << " grams\n";
    std::cout << "Fats: " << fat_g << " grams\n";
    std::cout << "Carbs: " << carbs_g << " grams\n";

    return 0;
}
