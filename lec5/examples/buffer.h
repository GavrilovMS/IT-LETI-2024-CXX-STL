#include <iostream>

class Buffer {
public:
    int* buf_;
    size_t size_;
    
    Buffer() : buf_(nullptr), size_(0) {
    }
    
    explicit Buffer(size_t size) : buf_(new int[size]), size_(size) {
    }
    
    Buffer(const Buffer& other) : buf_(new int[other.size_]), size_(other.size_) {
        std::copy(other.buf_, other.buf_ + size_, buf_);
    }
    
    Buffer(Buffer&& other) : buf_(nullptr), size_(0) {
        swap(other);
    }
    
    Buffer& operator=(const Buffer& other) {
        buf_ = new int[other.size_];
        size_ = (other.size_);
        std::copy(other.buf_, other.buf_ + size_, buf_);
        return *this;
    }
    
    Buffer& operator=(Buffer&& other)  {
        swap(other);
        return *this;
    }
    
    ~Buffer() {
        delete[] buf_;
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
    }
};

std::ostream& operator<<(std::ostream& out, const Buffer& buffer) {
    for (size_t i = 0; i < buffer.size_; i++) {
        out << buffer.buf_[i] << " ";
    }
    out << std::endl;
    return out;
}