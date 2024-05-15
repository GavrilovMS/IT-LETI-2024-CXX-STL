#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl << std::endl;

    // std::remove_if(vec.begin(), vec.end(), [](int n) { return n % 2 == 0; });

    // std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    // std::cout << std::endl << std::endl;

    vec.erase(std::remove_if(vec.begin(), vec.end(), [](int n) { return n % 2 == 0; }), vec.end());
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl << std::endl;
    return 0;
}