#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>

#include "buffer.h"

int main() {
    std::vector<Buffer> vec;
    vec.reserve(10);
    std::cout << "size: " << vec.size() << std::endl;
    std::cout << "capacity: " << vec.capacity() << std::endl;
    std::cout << std::endl;

    vec.push_back(Buffer(2));
    vec.emplace_back(Buffer(2));
    std::cout << "size: " << vec.size() << std::endl;
    std::cout << "capacity: " << vec.capacity() << std::endl;
    std::cout << std::endl;

    std::copy(vec.begin(), vec.end(), std::ostream_iterator<Buffer>(std::cout, " "));
    std::cout << std::endl;
    
    vec.erase(vec.begin(), vec.end()-1);
    std::cout << "size: " << vec.size() << std::endl;
    std::cout << "capacity: " << vec.capacity() << std::endl;
    std::cout << std::endl;

    return 0;
}