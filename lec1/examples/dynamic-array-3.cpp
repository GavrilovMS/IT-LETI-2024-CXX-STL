#include <iostream>

class DynamicArray{
protected:
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

class ResizeableDynamicArray : public DynamicArray {
    void resize(size_t size) {
        if (size <= size_) {
            return;
        }
        int* temp = data_;
        data_ = new int[size];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = temp[i];
        }
        size_ = size;
        delete[] temp;
    }
};

int main() { 
    DynamicArray arr(10);
    for (size_t i = 0; i < arr.size(); i++) {
        arr[i] = i;
    } 
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << "arr[" << i << "] = " << arr[i] << std::endl;
    } 
    return 0;
}