#include <iostream>
#include <string>
#include <utility>
#include <memory>

template<typename T>
class UniquePtr {
private:
    T* ptr_;

public:
    constexpr UniquePtr(T *p = nullptr) : ptr_(p) {}

    T* get() const { return ptr_; }
    operator bool() const {return bool(get()); }
    T* operator->() const { return get(); }
    T& operator*() const { return *get(); }

    T* release(){
        return std::exchange(ptr_, nullptr);
    }
    
    void reset(T* ptr = nullptr) {
        if (ptr_ != nullptr) {
            std::cout << "delete value" << std::endl;
            delete ptr_;
        }
        ptr_ = ptr;
    }

    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr(UniquePtr&& other) : ptr_(other.release()) {}

    UniquePtr& operator=(const UniquePtr& other) = delete;
    UniquePtr& operator=(UniquePtr&& other) {
        reset(other.release());
        return *this;
    }

    ~UniquePtr() {
        reset();
    }

};
namespace detail
{
    template<class>
    constexpr bool is_unbounded_array_v = false;
    template<class T>
    constexpr bool is_unbounded_array_v<T[]> = true;
 
    template<class>
    constexpr bool is_bounded_array_v = false;
    template<class T, std::size_t N>
    constexpr bool is_bounded_array_v<T[N]> = true;
} 

template<typename T, typename... Args>
std::enable_if_t<!std::is_array<T>::value, UniquePtr<T>>
make_unique(Args&&... args) {
    std::cout << "create value" << std::endl;
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
std::enable_if_t<detail::is_unbounded_array_v<T>, UniquePtr<T>>
make_unique(size_t size) {
    std::cout << "create array" << std::endl;
    return UniquePtr<T>(new std::remove_extent_t<T>[size]());
}

template<class T, class... Args>
std::enable_if_t<detail::is_bounded_array_v<T>> make_unique(Args&&...) = delete;

int main() {
    auto ptr1 = make_unique<int>(3);
    std::cout << "*ptr1: " << *ptr1 << std::endl;
    UniquePtr<int> ptr2(std::move(ptr1));
    // std::cout << "*ptr1: " << *ptr1 << std::endl;
    std::cout << "*ptr2: " << *ptr2 << std::endl;
    return 0;
}