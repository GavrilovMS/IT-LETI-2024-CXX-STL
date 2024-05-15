#include <any>
#include <iostream>
#include <string>

int main() {
    std::any value;
    
    value = 10;
    std::cout << "Stored int: " << std::any_cast<int>(value) << std::endl;
    
    value = 3.14;
    std::cout << "Stored double: " << std::any_cast<double>(value) << std::endl;
    
    value = std::string("Hello, std::any!");
    std::cout << "Stored string: " << std::any_cast<std::string>(value) << std::endl;

    return 0;
}