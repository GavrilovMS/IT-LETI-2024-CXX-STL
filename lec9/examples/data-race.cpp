#include <iostream>
#include <thread>

const size_t N = 1000000;
int x = 0;

void increment() {
    for (size_t i = 0; i < N; i++) {
        x++;
    }
}

void decrement() {
    for (size_t i = 0; i < N; i++) {
        x--;
    }
}

int main() {
    {
        std::jthread thr1(increment);
        std::jthread thr2(decrement);
    }
    std::cout << x << std::endl;
    return 0;
}