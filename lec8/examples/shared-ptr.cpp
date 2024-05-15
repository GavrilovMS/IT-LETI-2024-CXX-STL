#include <iostream>
#include <utility>
#include <memory>

class ControlBlock 
{
public:
    ControlBlock() : use_(0) {}
    ControlBlock(const ControlBlock&) = delete;
    ControlBlock& operator=(const ControlBlock&) = delete;

    size_t use_;
};

template <typename T>
class SharedPtr 
{
private:
    ControlBlock* ctrl_;
    T* ptr_;

public:
    explicit SharedPtr(T* p = nullptr) : ptr_(p), ctrl_(new ControlBlock) {
        ctrl_->use_++;
    }

    SharedPtr(const SharedPtr<T>& other) : ptr_(other.ptr_), ctrl_(other.ctrl_)
    {
        ctrl_->use_++;
    }
    
    SharedPtr(SharedPtr<T> && other) : ptr_(std::exchange(other.ptr_, nullptr)), ctrl_(std::exchange(other.ctrl_, nullptr)) {
    }

    SharedPtr<T>& operator=(const SharedPtr<T>& other) {
        ptr_ = other.ptr_;
        ctrl_ = other.ctrl_;
        ctrl_->use_++;
        return *this;
    }

    SharedPtr<T>& operator=(SharedPtr&& other) {
        ptr_ = std::exchange(other.ptr_, nullptr);
        ctrl_ = std::exchange(other.ctrl_, nullptr);
    }

    T* get() { return ptr_; } 
    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_;}

    ~SharedPtr()
    {
        ctrl_->use_--;
        if (ctrl_->use_ == 0) 
        {
            std::cout << "deleted" << std::endl;
            delete ctrl_;
            delete ptr_;
        }
    }

};

template<typename T, typename... Args>
std::enable_if_t<!std::is_array<T>::value, SharedPtr<T>>
make_shared(Args&&... args) {
    std::cout << "created" << std::endl;
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}

class Example{
    int a_;
    float b_;
    Example(int a, float b) : a_(a), b_(b) {

    }
};
int main() {
    auto ptr = make_shared<Example>(1, 2.5);
    return 0;
}

// int main() {
//     auto ptr1 = make_shared<int>(3);
//     auto ptr2 = ptr1;
//     std::cout << "*ptr1: " << *ptr1 << std::endl;
//     std::cout << "*ptr2: " << *ptr2 << std::endl;
//     return 0;
// }
