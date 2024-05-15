#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <numeric>

int main() {

    std::vector<int> arr(10);
    std::iota(arr.begin(), arr.end(), 0);
    std::copy(arr.begin(), arr.end(), std::ostream_iterator<int>(std::cout, " "));

    std::cout << std::endl;
    std::cout << "distance: " << std::distance(arr.begin(), arr.end()) << std::endl;
    std::cout << "count: " << std::count(arr.begin(), arr.end(), 5) << std::endl;
    std::cout << "count_if: " << std::count_if(arr.begin(), arr.end(), [](int x) {return x % 2;}) << std::endl;

    return 0;
}