#pragma once

#include <iostream>

// class DynamicArray {
// private:
//     int* data_ = nullptr;
//     size_t size_ = 0;
// public:
//     DynamicArray() = default;
//     DynamicArray(size_t size);
//     ~DynamicArray();

//     int& operator[](size_t index);
//     size_t size();
// };

template<typename T>
class DynamicArray {
private:
    T* data_ = nullptr;
    size_t size_ = 0;
public:
    DynamicArray() = default;
    DynamicArray(size_t size);
    ~DynamicArray();

    T& operator[](size_t index);
    size_t size();
};
