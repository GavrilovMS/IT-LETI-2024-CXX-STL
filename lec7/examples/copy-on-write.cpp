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
public:
    char* str_;
    size_t size_;
    int* ref_count_; // указатель на счетчик ссылок

    StringBuffer(size_t size = 0) : size_(size), ref_count_(new int(1)) {
        if (size_) {
            Allocation();
            str_ = new char[size_];
        }
    }

    StringBuffer(const char* str) {
        size_ = std::strlen(str);
        ref_count_ = new int(1);
        if (size_) {
            Allocation();
            str_ = new char[size_];
            Copy();
            std::copy(str, str + size_ + 1, str_);
        }
    }

    StringBuffer(const StringBuffer& other) : size_(other.size_), ref_count_(other.ref_count_) {
        ++(*ref_count_); 
        if (size_) {
            str_ = other.str_;
        }
    }

    StringBuffer& operator=(const StringBuffer& other) {
        if (this != &other) {
            --(*ref_count_); 
            if (!*ref_count_) {
                delete[] str_;
                delete ref_count_;
            }
            str_ = other.str_;
            size_ = other.size_;
            ref_count_ = other.ref_count_;
            ++(*ref_count_); // Увеличиваем новый счетчик ссылок
        }
        return *this;
    }

    ~StringBuffer() {
        --(*ref_count_); // Уменьшаем счетчик ссылок
        if (!*ref_count_) {
            delete[] str_;
            delete ref_count_;
        }
    }
};

class String : public StringBuffer{ // По-хорошему protected
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
        if (*ref_count_ != 1) {
            *this = str_;
        }
        if (index < size_) {
            return str_[index];
        } else {
            throw std::runtime_error("Out of array boundaries");
        }
    }

    const char& operator[](size_t index) const {
        if (index < size_) {
            return str_[index];
        } else {
            throw std::runtime_error("Out of array boundaries");
        }
    }

    size_t size() const {
        return size_;
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
    String str2 = str1;

    std::cout << (void*)str1.str_ << std::endl;
    std::cout << (void*)str2.str_ << std::endl;

    str1[1] = 'm';

    std::cout << (void*)str1.str_ << std::endl;
    std::cout << (void*)str2.str_ << std::endl;
    return 0;
}