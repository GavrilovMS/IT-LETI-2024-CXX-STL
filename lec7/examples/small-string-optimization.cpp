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
    const static constexpr size_t SMALL_BUFFER_SIZE = sizeof(char*) + sizeof(size_t);
    union {
        struct {
            char* str_;
            size_t capacity_;
        };
        char buf_[SMALL_BUFFER_SIZE];
    };
    size_t size_;

    StringBuffer(size_t size = 0) : size_(size) {
        if (size_ > SMALL_BUFFER_SIZE) {
            str_ = new char[size_];
            Allocation();
            capacity_ = size_;
        }
    }

    StringBuffer(const char* str) {
        size_ = std::strlen(str);

        if (size_ > SMALL_BUFFER_SIZE) {
            capacity_ = size_;
            str_ = new char[size_];
            Allocation();
            strcpy(str_, str);
            Copy();
        } else {
            strcpy(buf_, str);
            Copy();
        }
    }

    StringBuffer(const StringBuffer& other) {
        if (this != &other) {
            size_ = other.size_;
            if (size_ > SMALL_BUFFER_SIZE) {
                capacity_ = other.capacity_;
                str_ = new char[size_];
                Allocation();
                strcpy(str_, other.str_);
                Copy();
            } else {
                strcpy(buf_, other.buf_);
                Copy();
            }
        }
    }

    StringBuffer(StringBuffer&& other) noexcept {
        if (this != &other) {
            swap(other);
        }
    }

    StringBuffer& operator=(const StringBuffer& other) {
        if (this != &other) {
            delete[] str_;
            size_ = other.size_;
            capacity_ = other.capacity_;
            str_ = new char[size_];
            strcpy(str_, other.str_);
            Copy();
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
        if (size_ > SMALL_BUFFER_SIZE && str_ != nullptr) {
            delete[] str_;
        }
    }

private:
    void swap(StringBuffer& other) {
        std::swap(str_, other.str_);
        std::swap(str_, other.str_);
        std::swap(str_, other.str_);
    }
};


class String : protected StringBuffer{
private:
public:
    String(size_t size = 0) : StringBuffer(size) { }
    String(const char* str) : StringBuffer(str) { }

    ~String() { }

    String(const String& other) : StringBuffer(other){ }

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
        if (index < size_) {
            if (size_ < SMALL_BUFFER_SIZE) {
                return buf_[index];
            }
            else {
                return str_[index];
            }
        } else {
            throw std::runtime_error("Out of array boundaries");
        }
    }

    const char& operator[](size_t index) const {
        if (index < size_) {
            if (size_ < SMALL_BUFFER_SIZE) {
                return buf_[index];
            }
            else {
                return str_[index];
            }
        } else {
            throw std::runtime_error("Out of array boundaries");
        }
    }

    size_t size() const {
        return size_;
    }

    void resize(size_t new_size) {
        if (new_size <= capacity_) {
            size_ = new_size;
        } 
        else {
            capacity_ *= 2;
            StringBuffer new_buf(capacity_);
            strcpy(new_buf.str_, str_);
            StringBuffer::operator=(std::move(new_buf));
        }
    }

    void push_back(char c) {
        if (size_ < capacity_) {
            str_[size_] = c;
            size_++;
        } else {
            capacity_ *= 2;
            StringBuffer new_buf(capacity_);
            new_buf.size_ = size_;

            if (capacity_ > SMALL_BUFFER_SIZE) {
                if (size_ > SMALL_BUFFER_SIZE) {
                    strcpy(new_buf.str_, str_);
                }
                else {
                    strcpy(new_buf.str_, buf_);
                }
                new_buf.str_[new_buf.size_++] = c;
            } 
            else {
                strcpy(new_buf.buf_, buf_);
                new_buf.buf_[new_buf.size_++] = c;
            }

            StringBuffer::operator=(std::move(new_buf));
        }
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
    std::cout << str1;
    return 0;
}