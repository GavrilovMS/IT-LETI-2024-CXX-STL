#include <iostream>

int main() {
    int* a = new int;
    int* b = new int[10];

    *a = 5;
    
    for (size_t i = 0; i < 10; i++) {
        b[i] = i;
    }

    std::cout << "*a = " << *a << std::endl;
    std::cout << "*b = " << *b << std::endl;
    std::cout << std::endl;

    for (size_t i = 0; i < 10; i++) {
        std::cout << "b[" << i << "] = " << b[i] << std::endl;
    }

    delete a;
    delete[] b;

    return 0;
}