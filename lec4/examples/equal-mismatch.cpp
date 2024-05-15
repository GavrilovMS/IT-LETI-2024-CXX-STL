#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>

int main() {

    std::vector<int> arr1(10), arr2(10);
    int x1 = 0, x2 = 0;
    std::iota(arr1.begin(), arr1.end(), 0);
    std::iota(arr2.begin(), arr2.end(), 0);

    std::cout << "equal: " << std::equal(arr1.begin(), arr1.end(), arr2.begin(), arr2.end()) << std::endl;
    
    auto pair = std::mismatch(arr1.begin(), arr1.end(), arr2.begin(), arr2.end());
    std::cout << "mismatch: " << *pair.first << " " << *pair.second << std::endl;

    return 0;
}