#include <iostream>

class Buffer {
public:
    int* buf_;
    size_t size_;
    
    Buffer() : buf_(nullptr), size_(0) {
        std::cout << "Default constructor" << std::endl;
    }
    
    Buffer(size_t size) : buf_(new int[size]), size_(size) {
        std::cout << "Constructor 1 argument" << std::endl;
    }
    
    Buffer(const Buffer& other) : buf_(new int[other.size_]), size_(other.size_) {
        std::copy(other.buf_, other.buf_ + size_, buf_);
        std::cout << "Copy costructor" << std::endl;
    }
    
    Buffer(Buffer&& other) : buf_(nullptr), size_(0) {
        swap(other);
        std::cout << "R-value costructor" << std::endl;
    }
    
    Buffer& operator=(const Buffer& other) {
        buf_ = new int[other.size_];
        size_ = (other.size_);
        std::copy(other.buf_, other.buf_ + size_, buf_);
        std::cout << "Copy operator=" << std::endl;
        return *this;
    }
    
    Buffer& operator=(Buffer&& other)  {
        std::cout << "R-value operator=" << std::endl;
        swap(other);
        return *this;
    }
    
    ~Buffer() {
        if (buf_ != nullptr) {
            delete[] buf_;
        }
    }
    
    void print() {
        for (size_t i = 0; i < size_; i++) {
            std::cout << buf_[i] << " ";
        }
        std::cout << std::endl;
    }

    private:
    void swap(Buffer& other) {
        std::swap(buf_, other.buf_);
        std::swap(size_, other.size_);
        delete[] other.buf_;
    }
};

int main() {
    Buffer buf1(5);
    Buffer buf2(5);
    
    for (size_t i = 0; i < 5; i++) {
        buf1.buf_[i] = i;
        buf2.buf_[i] = 0;
    }
    std::cout << "buf1: ";
    buf1.print();
    std::cout << "buf2: ";
    buf2.print();

    Buffer buf3 = std::move(buf1);

    std::cout << "buf1: ";
    buf1.print();
    std::cout << "buf2: ";
    buf2.print();
    std::cout << "buf3: ";
    buf3.print();
    return 0;
}