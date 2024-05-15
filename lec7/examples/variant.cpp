#include <variant>
#include <iostream>

int main() {
    std::variant<int, double, std::string> myVariant;
    
    myVariant = 10;
    if (std::holds_alternative<int>(myVariant)) {
        std::cout << std::get<int>(myVariant) << std::endl;
    }

    myVariant = 3.14;
    if (std::holds_alternative<double>(myVariant)) {
        std::cout << std::get<double>(myVariant) << std::endl;
    }

    myVariant = "hello";
    if (std::holds_alternative<std::string>(myVariant)) {
        std::cout << std::get<std::string>(myVariant) << std::endl;
    }

    return 0;
}