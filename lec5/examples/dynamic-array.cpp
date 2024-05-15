#include <iostream>
#include <algorithm>
#include <numeric>
#include <iterator>

// Зона ответственности - определение интерфейса
template<typename T>
class DynamicArrayInterface {
public:
    DynamicArrayInterface() = default;
    virtual ~DynamicArrayInterface() {}
    virtual T& operator[](size_t index) = 0;
    virtual size_t size() const = 0;
};

// Зона ответственности - владение ресурсом
template <typename T>
class DynamicArrayBuffer{
protected:
    T* data_;
    size_t size_;
    DynamicArrayBuffer(size_t size = 0) : size_(size) {
        if (size != 0) {
            data_ = new T[size];
        }
    }
    ~DynamicArrayBuffer() {
        delete[] data_;
    }
};

// Зона ответственности - реализация
template <typename T>
class DynamicArray : public DynamicArrayInterface<T>, protected DynamicArrayBuffer<T>{
public:

    template<bool Const>
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::conditional_t<Const, const T, T>;
        using difference_type = std::ptrdiff_t;
        using pointer = std::conditional_t<Const, const T*, T*>;
        using reference = std::conditional_t<Const, const T&, T&>;

        reference operator*() const { return *ptr_; }
        pointer operator->() { return ptr_; }
        Iterator& operator++() { ++ptr_; return *this; }
        Iterator operator++(int) { Iterator temp = *this; ++ptr_; return temp; }
        bool operator==(const Iterator& other) const { return ptr_ == other.ptr_; }
        bool operator!=(const Iterator& other) const { return ptr_ != other.ptr_; }

    private:
        pointer ptr_;

        friend class Iterator<!Const>;
        friend class DynamicArray;
        explicit Iterator(pointer ptr) : ptr_(ptr) {}
    };

    using const_iterator = Iterator<true>;
    using iterator = Iterator<false>;

    iterator begin() { return iterator(DynamicArrayBuffer<T>::data_); }
    iterator end() { return iterator(DynamicArrayBuffer<T>::data_ + DynamicArrayBuffer<T>::size_); }

    const_iterator begin() const { return const_iterator(DynamicArrayBuffer<T>::data_); }
    const_iterator end() const { return const_iterator(DynamicArrayBuffer<T>::data_ + DynamicArrayBuffer<T>::size_); }

    DynamicArray(size_t size = 0) : DynamicArrayBuffer<T>(size) {}
    ~DynamicArray() {}

    T& operator[](size_t index) override {
        if (index < DynamicArrayBuffer<T>::size_) {
            return DynamicArrayBuffer<T>::data_[index];
        } else {
            throw std::runtime_error("Out of array boundaries");
        }
    }

    size_t size() const override {
        return DynamicArrayBuffer<T>::size_;
    }
};

int main() {
    DynamicArrayInterface<int>* arr = new DynamicArray<int>(10);
    (*arr)[5] = 5;
    std::cout << (*arr)[5] << std::endl;
    delete arr; // нарушение RAII?

    DynamicArray<int> arr1(10);
    std::iota(arr1.begin(), arr1.end(), 0);
    std::copy(arr1.begin(), arr1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    return 0;
}