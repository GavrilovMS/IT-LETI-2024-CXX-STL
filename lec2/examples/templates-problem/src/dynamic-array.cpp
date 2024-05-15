#include "dynamic-array.h"
#include <iostream>

// DynamicArray::DynamicArray(size_t size) : size_(size) {
//     if (size > 0) {
//         data_ = new int[size];
//     }
// }

// DynamicArray::~DynamicArray() {
//     if (data_ != nullptr) {
//         delete[] data_;
//     }
// }

// int& DynamicArray::operator[](size_t index) {
//     if (index < size_) {
//         return data_[index];
//     }
// }


// size_t DynamicArray::size() {
//     return size_;
// }

template<typename T>
DynamicArray::DynamicArray(size_t size) : size_(size) {
    if (size > 0) {
        data_ = new T[size];
    }
}

template<typename T>
DynamicArray::~DynamicArray() {
    if (data_ != nullptr) {
        delete[] data_;
    }
}

template<typename T>
T& DynamicArray::operator[](size_t index) {
    if (index < size_) {
        return data_[index];
    }
}


template<typename T>
size_t DynamicArray::size() {
    return size_;
}


template<> class DynamicArray<int>;
template<> class DynamicArray<float>;