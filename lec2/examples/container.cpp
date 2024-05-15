#include <iostream>

template <typename T>
class Container{
public:
    virtual ~Container() {

    }
    virtual size_t size() = 0;
    virtual T& operator[](size_t index) = 0;
};

template <typename T>
class DynamicArray : public Container<T> {
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

    ~DynamicArray() override {
        if (data_ != nullptr) {
            delete[] data_;
        }
    }

    T& operator[](size_t index) override {
        if (index < size_) {
            return data_[index];
        }
    }

    size_t size() override {
        return size_;
    }
};

template <typename T>
class LinkedList : public Container<T> {
private:
    //some code
public:
    LinkedList() = default;

    LinkedList(size_t size) : size_(size) {
        //some code
    }

    ~LinkedList() override {
        //some code
    }

    T& operator[](size_t index) override {
        //some code
    }

    size_t size() override {

    }
};

int main() {
    Container<int>* arr_of_int = new DynamicArray<int>();
    Container<float>* list_of_float = new LinkedList<float>();

    return 0;
}
