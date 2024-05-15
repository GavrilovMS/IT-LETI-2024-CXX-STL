#include <iostream>

template <typename T>
class AutoPtr {
public:
    AutoPtr() : ptr_(nullptr) {}
    explicit AutoPtr(T* ptr) : ptr_(ptr) {
        std::cout << "Pointer created" << std::endl;
    }
    ~AutoPtr() { 
        delete ptr_;
        std::cout << "Pointer deleted" << std::endl;
    }

    AutoPtr(const AutoPtr& other) : ptr_(other.ptr_) {
        other.ptr_ = nullptr;
    }

    T* operator->() const { return ptr_; }
    T& operator*() const { return *ptr_; }

    T* release() {
        T* tmp = ptr_;
        ptr_ = nullptr;
        return tmp;
    }

    void reset(T* ptr) {
        delete ptr_;
        ptr_ = ptr;
    }

private:
    T* ptr_;
};

int main() {
    AutoPtr ptr(new int);
    return 0;
}