#include <iostream>
#include <utility>
#include <memory>

class ControlBlock 
{
public:
    ControlBlock() : use_(0), weak_(0) {}
    ControlBlock(const ControlBlock&) = delete;
    ControlBlock& operator=(const ControlBlock&) = delete;

    size_t weak_;
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
            delete ptr_;
            if (ctrl_->weak_ == 0) {
                delete ctrl_;
            }
        }
    }

    friend class WeakPtr;
};

template <typename T>
class WeakPtr 
{
private:
    ControlBlock* ctrl_;
    T* ptr_;

public:
    explicit WeakPtr(const SharedPtr& p) : ptr_(p.get()), ctrl_(p->ctrl_) {
        ctrl_->weak_++;
    }

    WeakPtr(const WeakPtr<T>& other) : ptr_(other.ptr_), ctrl_(other.ctrl_)
    {
    }
    
    WeakPtr(WeakPtr<T> && other) : ptr_(std::exchange(other.ptr_, nullptr)), ctrl_(std::exchange(other.ctrl_, nullptr)) {
    }

    WeakPtr<T>& operator=(const WeakPtr<T>& other) {
        ptr_ = other.ptr_;
        ctrl_ = other.ctrl_;
        return *this;
    }

    WeakPtr<T>& operator=(WeakPtr&& other) {
        ptr_ = std::exchange(other.ptr_, nullptr);
        ctrl_ = std::exchange(other.ctrl_, nullptr);
    }

    T* get() { return ptr_; } 
    T& operator*() { return *ptr_; }
    T* operator->() { return ptr_;}

    ~WeakPtr()
    {
        ctrl_->weak_--;
        if (ctrl->use_ == 0 && ctrl_->weak_ == 0) {
            delete ctrl_;
        }
    }

};

template<typename T, typename... Args>
std::enable_if_t<!std::is_array<T>::value, SharedPtr<T>>
make_shared(Args&&... args) {
    std::cout << "created" << std::endl;
    return SharedPtr<T>(new T(std::forward<Args>(args)...));
}


int main() {
    auto ptr1 = make_shared<int>(3);
    auto ptr2 = ptr1;
    std::cout << "*ptr1: " << *ptr1 << std::endl;
    std::cout << "*ptr2: " << *ptr2 << std::endl;
    return 0;
}
