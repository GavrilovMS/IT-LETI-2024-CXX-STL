#include <iostream>


int main() {

    uint64_t n;
    std::cin >> n;
    int arr[n];
    for (size_t i = 0; i < n; i++) {\
        arr[i] = i;
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    }

    std::cout << "&n = " << &n << std::endl; 
    std::cout << "&arr = " << &arr << std::endl;

    return 0;
}