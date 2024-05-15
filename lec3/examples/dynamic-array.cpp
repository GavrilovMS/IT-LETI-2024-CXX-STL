#include <iostream>

class DynamicArray{
private:
    int* data_;
    size_t size_;
public:
    DynamicArray() {}
    ~DynamicArray() {}
    int& operator[](size_t index) {
        return data_[index];
    }
    size_t size() {}
};