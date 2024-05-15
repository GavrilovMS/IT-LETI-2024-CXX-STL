#include <iostream>

class DynamicArray{
private:
    int* data_ = nullptr;
    size_t size_ = 0;

public:
    DynamicArray() = default;
    DynamicArray(size_t size) : size_(size) {
        if (size_) {
            data_ = new int[size];
        }
    }
    ~DynamicArray() {
        if (data_ == nullptr) {
            return;
        }
        delete[] data_;
    }
    size_t size() {
        return size_;
    }
    int& operator[](size_t index) {
        if (index < size_) {
            return data_[index];
        }
    }
};

int main() { 
    DynamicArray arr(10);
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = i;
    } 
    arr[4] = 10;
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    } 
    return 0;
}