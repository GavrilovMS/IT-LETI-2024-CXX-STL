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
    int& operator[](size_t index) {
        return data_[index];
    }
};

int foo() {
    int* arr = new int[10];
    for (size_t i = 0; i < 10; i++) {
        if (arr[i] % 2) {
            break;
        } else {
            delete[] arr;
            arr = new int[10];
            if (arr[i] % 2) {
                continue;
            }
        }
        if (arr[i] % 3) {
            int res = arr[i];
            delete[] arr;
            return res;
        }
    }
    delete[] arr;
    return 0;
}

int bar() {
    Array arr(10);
    for (size_t i = 0; i < 10; i++) {
        if (arr[i] % 2) {
            break;
        } else {
            arr = Array(10);
            if (arr[i] % 2) {
                continue;
            }
        }
        if (arr[i] % 3) {
            return arr[i];
        }
    }
    return 0;
}