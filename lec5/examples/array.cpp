#include <array>
#include <iostream>
#include <numeric>
#include <iterator>
#include <vector>

int main(){
    std::array<int, 10> arr;
    std::iota(arr.begin(), arr.end(), 0);
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    return 0;
}