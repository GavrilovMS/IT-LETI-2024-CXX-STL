#include <iostream>
#include <string>
#include <algorithm>

int main() {

    std::string str = "abcdcba";
    std::string rev_str = str;
    std::cout << str << std::endl;

    std::reverse(rev_str.begin(), rev_str.end());

    std::cout << str << std::endl;

    return 0;
}