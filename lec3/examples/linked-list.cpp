#include <iostream>

class LinkedList{
private:
    struct Node{
        int data_;
        Node* next_;
    };

    Node* head_ = nullptr;
    size_t size_;
public:

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

template<typename Container>
void printContainer(Container& arr){
    for (size_t i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << std::endl;
    }
}

int main() {
    LinkedList list;
    printContainer(list);
    return 0;
}