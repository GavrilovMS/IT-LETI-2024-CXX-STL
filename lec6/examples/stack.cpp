#include <iostream>
#include <stack>
#include <list>

void recursiveFunction(int n) {
    if (n > 0) {
        std::cout << n << " ";
        recursiveFunction(n-1);
        recursiveFunction(n-1);
    }
}

void iterativeFunction(int n) {
    std::stack<int, std::list<int>> stack;
    stack.push(n);
    
    while (!stack.empty()) {
        int current = stack.top();
        stack.pop();
        
        if (current > 0) {
            std::cout << current << " ";
            stack.push(current-1);
            stack.push(current-1);
        }
    }
}

int main() {
    recursiveFunction(3);
    std::cout << std::endl;
    iterativeFunction(3);
    return 0;
}