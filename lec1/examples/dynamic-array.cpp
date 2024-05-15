#include <iostream>

class DynamicArray{
public:
    int* data_ = nullptr;
    size_t size_ = 0;
    DynamicArray() = default;
    DynamicArray(size_t size) : size_(size) {
        if (size_) {
            data_ = new int[size];
        }
        std::cout << "Created dynamic array of size " << size_ << std::endl;
    }
    ~DynamicArray() {
        std::cout << "Deleted dynamic array of size " << size_ << std::endl;
        if (data_ == nullptr) {
            return;
        }
        delete[] data_;
    }
};

int main() {
    DynamicArray arr1;
    
    DynamicArray arr2(3);

    DynamicArray* ptr1 = new DynamicArray;
    DynamicArray* ptr2 = new DynamicArray(3);

    delete ptr1;
    delete ptr2;

    return 0;
}