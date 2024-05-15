#include <tuple>
#include <iostream>

int main() {
    std::tuple<int, double, std::string> myTuple(10, 3.14, "hello");
    
    std::cout << std::get<0>(myTuple) << std::endl;
    std::cout << std::get<1>(myTuple) << std::endl;
    std::cout << std::get<2>(myTuple) << std::endl;

    return 0;
}