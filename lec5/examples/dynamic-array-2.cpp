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
class DynamicArrayBuffer {
protected:
    T* data_;
    size_t size_;

public:
    DynamicArrayBuffer(size_t size = 0) : size_(size) {
        if (size != 0) {
            data_ = new T[size];
        }
        std::cout << "Default constructor" << std::endl;
    }

    DynamicArrayBuffer(const DynamicArrayBuffer& other) : data_(new T[other.size_]), size_(other.size_) {
        if(this != &other) {
            std::copy(other.data_, other.data_ + size_, data_);
        }
        std::cout << "Copy constructor" << std::endl;
    }

    DynamicArrayBuffer(DynamicArrayBuffer&& other) : data_(nullptr), size_(0) {
        if (this != &other) {
            swap(other);
        }
        std::cout << "Move constructor" << std::endl;
    }

    DynamicArrayBuffer& operator=(const DynamicArrayBuffer& other) {
        if (this != &other) {
            data_ = new T[other.size_];
            size_ = other.size_;
            std::copy(other.data_, other.data_ + size_, data_);
        }
        std::cout << "Copy operator=" << std::endl;
        return *this;
    }

    DynamicArrayBuffer& operator=(DynamicArrayBuffer&& other) {
        if (this != & other) {
            swap(other);
        }
        std::cout << "Move operator=" << std::endl;
        return *this;
    }

    ~DynamicArrayBuffer() {
        delete[] data_;
    }

private:
    void swap(DynamicArrayBuffer& other)t {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
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
        operator Iterator<true>() const { return Iterator<true>(ptr_); }
        
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

    DynamicArray(size_t size = 0) : DynamicArrayBuffer<T>(size) { }
    ~DynamicArray() { }

    DynamicArray(const DynamicArray& other) : DynamicArrayBuffer<T>(other), DynamicArrayInterface<T>() { }
    DynamicArray(DynamicArray&& other) : DynamicArrayBuffer<T>(std::move(other)), DynamicArrayInterface<T>() { }

    DynamicArray& operator=(const DynamicArray& other) {
        DynamicArrayBuffer<T>::operator=(other);
        return *this;
    }

    DynamicArray& operator=(DynamicArray&& other) {
        DynamicArrayBuffer<T>::operator=(std::move(other));
        return *this;
    }

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
    DynamicArray<int> arr1(10);
    std::iota(arr1.begin(), arr1.end(), 0);
    std::cout << "arr1: ";
    std::copy(arr1.begin(), arr1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;

    DynamicArray<int> arr2(std::move(arr1));
    std::cout << "arr1: ";
    std::copy(arr1.begin(), arr1.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << std::endl;
    std::cout << "arr2: ";
    std::copy(arr2.begin(), arr2.end(), std::ostream_iterator<int>(std::cout, " "));

    return 0;
}