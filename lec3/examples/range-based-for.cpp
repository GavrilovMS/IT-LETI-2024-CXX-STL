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

    template<bool Const> 
    class Iterator {
    private:
        Node* ptr_;
        explicit Iterator(Node* ptr = nullptr) : ptr_(ptr) {}

        friend class LinkedList;
        friend class Iterator<!Const>;

        using NodePtr = std::conditional_t<Const, const Node*, Node*>;
        using Reference = std::conditional_t<Const, const T&, T&>;
    public:
    
        Reference operator*() const {
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

        template<bool R>
        bool operator==(const Iterator<R>& rhs) const {
            return ptr_ == rhs.ptr_;
        }
        
        template<bool R>
        bool operator!=(const Iterator<R>& rhs) const {
            return ptr_ != rhs.ptr_;
        }

        operator Iterator<true>() const {
            return Iterator<true>(ptr_);
        }
    };

    using const_iterator = Iterator<true>;
    using iterator = Iterator<false>;

    iterator begin()  {
        return iterator(head_);
    }

    iterator end() {
        return iterator(nullptr);
    }

    const_iterator begin() const{
        return const_iterator(head_);
    }

    const_iterator end() const{
        return const_iterator(nullptr);
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

template<typename Iterator>
void printContainer(Iterator begin, Iterator end) {
    for (auto it = begin; it != end; it++) {
        std::cout << *it << std::endl;
    }
}

int main() {
    LinkedList<int> list(5);
    for (auto & element : list) {
        element = rand();
    }
    printContainer(list.begin(), list.end());
    return 0;
}