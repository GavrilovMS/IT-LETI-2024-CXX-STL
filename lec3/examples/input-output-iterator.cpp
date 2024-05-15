#include <iostream>
#include <vector>
#include <iterator>

int main() {
    std::vector<int> arr;
    
    std::istream_iterator<int> in_it(std::cin);
    std::istream_iterator<int> eof; // По умолчанию указывает на конец потока
    
    std::copy(in_it, eof, std::back_inserter(arr)); // Ctrl + Z to finish

    std::ostream_iterator<int> out_it(std::cout, " ");

    std::copy(arr.begin(), arr.end(), out_it);
    return 0;
}