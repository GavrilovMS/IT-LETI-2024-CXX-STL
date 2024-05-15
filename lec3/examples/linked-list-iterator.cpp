#include <iostream>

template<typename T>
class LinkedList{
private:
    struct Node{
        T data_;
        Node* next_ = nullptr;
    };

    Node* head_ = nullptr;
    size_t size_;
public:
    LinkedList(size_t size = 0) : size_(size) {
        if (size_ == 0) {
            return;
        }
        head_ = new Node;
        Node* node = head_;
        for (size_t i = 1; i < size_; i++) {
            node->next_ = new Node;
            node = node->next_;
        }
    } 
    ~LinkedList() {
        for (Node* node = head_; node != nullptr;) {
            head_ = node->next_;
            delete node;
            node = head_;
        }
    }

    friend class Iterator;

    class Iterator {
    private:
        Node* ptr_;
        explicit Iterator(Node* ptr = nullptr) : ptr_(ptr) {}
        friend class LinkedList;
    public:
    
        T& operator*() const {
            return ptr_->data_;
        }

        Iterator& operator++() {
            ptr_ = ptr_->next_;
            return *this;
        }

        Iterator operator++(int){
            auto res = *this;
            ++*this;
            return res;
        }

        bool operator==(const Iterator& rhs) const {
            return ptr_ == rhs.ptr_;
        }

        bool operator!=(const Iterator& rhs) const {
            return ptr_ != rhs.ptr_;
        }
    };

    Iterator begin()  {
        return Iterator(head_);
    }

    Iterator end() {
        return Iterator(nullptr);
    }

    T& operator[](size_t index) {
        Node* res = head_;
        for (size_t i = 0; i < index; i++) {
            res = res->next_;
        } 
        return res->data_;
    }

    size_t size() {
        return size_;
    }
};

template<typename Container>
void printContainer(Container& arr) {
    for (auto it = arr.begin(); it != arr.end(); it++) {
        std::cout << *it << std::endl;
    }
}

int main() {
    LinkedList<int> list_of_ints(10);
    for (size_t i = 0; i < 10; i++) {
        list_of_ints[i] = i;
    }

    printContainer(list_of_ints);
    return 0;
}