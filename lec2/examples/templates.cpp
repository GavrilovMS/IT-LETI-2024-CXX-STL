#include <iostream>

template <typename T>
class DynamicArray{
private:
    T* data_ = nullptr;
    size_t size_ = 0;
public:
    DynamicArray() = default;

    DynamicArray(size_t size) : size_(size) {
        if (size > 0) {
            data_ = new T[size];
        }
    }

    ~DynamicArray() {
        if (data_ != nullptr) {
            delete[] data_;
        }
    }

    T& operator[](size_t index) {
        if (index < size_) {
            return data_[index];
        }
    }

    size_t size() {
        return size_;
    }
};

int main() {
    DynamicArray<int> arr_of_ints(2);
    DynamicArray<float> arr_of_floats(2);

    for (size_t i = 0; i < 2; i++) {
        arr_of_ints[i] = i + 0.9;
        arr_of_floats[i] = i + 0.9;
    }

    std::cout << "Ints: " << arr_of_ints[0] << " " << arr_of_ints[1] << std::endl;
    std::cout << "Floats: " << arr_of_floats[0] << " " << arr_of_floats[1] << std::endl;
    return 0;
}
