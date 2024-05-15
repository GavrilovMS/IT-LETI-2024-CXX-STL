#include <iostream>

class LinkedList{
public:
    struct Node{
        int data_;
        Node* next_;
    };
    Node* head_ = nullptr;
    size_t size_;
    // ...
    LinkedList() {}
    ~LinkedList() {}

    int& operator[](size_t index) {
        if (index >= size_) {
            return;
        }

        Node* res = head_;
        for (size_t i = 0; i < index; i++) {
            res = res->next_;
        } 
        return res->data_;
    }
};

void printLinkedList(LinkedList& arr){
    for (LinkedList::Node* node = arr.head_; node != nullptr; node = node->next_) {
            std::cout << node->data_ << std::endl;
    } 
}

int main() {
    LinkedList list;
    printLinkedList(list);
    return 0;
}