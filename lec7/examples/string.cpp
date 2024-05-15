#include <iostream>
#include <algorithm>
#include <cstring>

void Allocation() {
    std::cout << "Allocation!" << std::endl;
}

void Copy() {
    std::cout << "Copy!" << std::endl;
}

class StringBuffer {
protected:
    char* str_;
    size_t size_;

public:
    StringBuffer(size_t size = 0) : size_(size) {
        if (size != 0) {
            Allocation();
            str_ = new char[size];
        }
    }

    StringBuffer(const char* str) {
        size_ = std::strlen(str);
        if (size_ != 0) {
            Allocation();
            str_ = new char[size_];
            Copy();
            strcpy(str_, str);
        }
    }

    StringBuffer(const StringBuffer& other) : size_(other.size_) {
        if(this != &other && size_) {
            Allocation();
            str_ = new char[other.size_];
            Copy();
            strcpy(str_, other.str_);
        }
    }

    StringBuffer& operator=(const StringBuffer& other) {
        if (this != &other) {
            Allocation();
            str_ = new char[other.size_];
            size_ = other.size_;
            Copy();
            strcpy(str_, other.str_);
        }
        return *this;
    }

    ~StringBuffer() {
        if (str_ != nullptr) {
            delete[] str_;
        }
    }
};

class String : protected StringBuffer{
public:
    String(size_t size = 0) : StringBuffer(size) { }
    String(const char* str) : StringBuffer(str){ }

    ~String() { }

    String(const String& other) : StringBuffer(other) { }

    String& operator=(const String& other) {
        StringBuffer::operator=(other);
        return *this;
    }

    char& operator[](size_t index) {
        if (index < StringBuffer::size_) {
            return StringBuffer::str_[index];
        } 
        else {
            throw std::runtime_error("Out of array boundaries");
        }
    }

    const char& operator[](size_t index) const {
        if (index < StringBuffer::size_) {
            return StringBuffer::str_[index];
        } 
        else {
            throw std::runtime_error("Out of array boundaries");
        }
    }

    size_t size() const {
        return StringBuffer::size_;
    }

    friend std::ostream& operator<<(std::ostream& os, const String& str) {
        for (size_t i = 0; i < str.size(); ++i) {
            os << str[i];
        }
        return os;
    }
};

int main() {
    String str1 = "12345"; // +  Allocation
    String str2 = str1;
    std::cout << str1 << std::endl;
    return 0;
}