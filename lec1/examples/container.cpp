#include <iostream>

class Container{
public:
    Container() = default;
    virtual ~Container() {}

    virtual int& operator[](size_t index) = 0;
    virtual size_t size() = 0;
    virtual void say_hello() = 0;
};

class DynamicArray : public Container {
protected:
    int* data_ = nullptr;
    size_t size_ = 0;

public:
    DynamicArray() = default;
    DynamicArray(size_t size) : size_(size) {
        if (size_) {
            data_ = new int[size];
        }
    }
    ~DynamicArray() override {
        if (data_ == nullptr) {
            return;
        }
        delete[] data_;
    }
    size_t size() override {
        return size_;
    }
    int& operator[](size_t index) override {
        if (index < size_) {
            return data_[index];
        }
    }
    void say_hello() override {
        std::cout << "Hello from DynamicArray!" << std::endl;
    }
};

class ResizeableDynamicArray : private DynamicArray {
    void resize(size_t size) {
        if (size <= size_) {
            return;
        }
        say_hello();
        int* temp = data_;
        data_ = new int[size];
        for (size_t i = 0; i < size_; i++) {
            data_[i] = temp[i];
        }
        size_ = size;
        delete[] temp;
    }
};

class LinkedList : public Container {
private:
    struct Node{
        int* data_;
        Node* next_;
    };
    Node head_;
    size_t size_;
public:
    LinkedList() = default;
    LinkedList(size_t size) : size_(size) {
        //some code
    }
    ~LinkedList() override {
        //some code
    }
    size_t size() override {
        //some code
    }
    int& operator[](size_t index) override {
        //some code 
    }
    void say_hello() override {
        std::cout << "Hello from LinkedList!" << std::endl;
    }   
};

int main() {
    Container* arr[2];
    arr[0] = new DynamicArray(3);
    arr[1] = new LinkedList(3);
    
    arr[0]->say_hello();
    arr[1]->say_hello();
    
    DynamicArray arr1;
    DynamicArray* ptrArr = &arr1;
    arr1.say_hello();
    ptrArr->say_hello();

    ResizeableDynamicArray arr2;
    delete arr[1];
    delete arr[0];
    return 0;
}