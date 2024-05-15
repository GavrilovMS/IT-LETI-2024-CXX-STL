#include <iostream>

class Array{
private:
    int* data_;
public:
    Array(size_t size = 0) : data_(new int[size]) {
        std::cout << "data_ created" << std::endl;
    }
    ~Array() {
        std::cout << "data_ destroyed" << std::endl;
        delete[] data_;
    }
};

int main() {

    try {
        Array arr1(10);
        int* arr2 = new int[10];
        std::cout << "arr2 created" << std::endl;

        throw -1;
        
        delete[] arr2;
        std::cout << "arr2 destroyed" << std::endl;
    } catch (...) {

    }

    return 0;
}