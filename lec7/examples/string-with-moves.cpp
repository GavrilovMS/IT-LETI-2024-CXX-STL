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
    StringBuffer(size_t size = 0) : size_(size), str_(new char[size]) {
        Allocation();
    }

    StringBuffer(const char* str) {
        size_ = std::strlen(str);
        Allocation();
        str_ = new char[size_];
        Copy();
        strcpy(str_, str);
    }

    StringBuffer(const StringBuffer& other) : size_(other.size_) {
        if (this != &other) {
            str_ = new char[size_];
            Allocation();
            Copy();
            strcpy(str_, other.str_);
        }
    }

    StringBuffer(StringBuffer&& other) noexcept  {
        if (this != &other) {
            swap(other);
        }
    }

    StringBuffer& operator=(const StringBuffer& other) {
        if (this != &other) {
            delete[] str_;
            size_ = other.size_;
            str_ = new char[size_];
            Allocation();
            Copy();
            strcpy(str_, other.str_);
        }
        return *this;
    }

    StringBuffer& operator=(StringBuffer&& other) noexcept {
        if (this != &other) {
            swap(other);
        }
        return *this;
    }

    ~StringBuffer() {
        delete[] str_;
    }
private:
    void swap(StringBuffer& other) {
        std::swap(str_, other.str_);
        std::swap(str_, other.str_);
        std::swap(str_, other.str_);
    }
};


class String : protected StringBuffer{
public:
    String(size_t size = 0) : StringBuffer(size) { }
    String(const char* str) : StringBuffer(str){ }

    ~String() { }

    String(const String& other) : StringBuffer(other) { }

    String(String&& other) noexcept : StringBuffer(std::move(other)) {}

    String& operator=(const String& other) {
        StringBuffer::operator=(other);
        return *this;
    }

    String& operator=(String&& other) noexcept {
        StringBuffer::operator=(std::move(other));
        return *this;
    }

    char& operator[](size_t index) {
        if (index < StringBuffer::size_) {
            return StringBuffer::str_[index];
        } else {
            throw std::runtime_error("Out of array boundaries");
        }
    }

    const char& operator[](size_t index) const {
        if (index < StringBuffer::size_) {
            return StringBuffer::str_[index];
        } else {
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
    String str1 = "12345";
    String str2 = std::move(str1);
    // std::cout << str2 << std::endl;
    return 0;
}