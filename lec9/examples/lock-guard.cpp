#include <iostream>
#include <thread>
#include <mutex>

const size_t N = 100000;
int x = 0;
std::mutex mtx;

void increment() {
    for (size_t i = 0; i < N; i++) {
        std::lock_guard<std::mutex> lk(mtx);
        x++;
    }
}

void decrement() {
    try {
        for (size_t i = 0; i < N; i++) {
            std::lock_guard<std::mutex> lk(mtx);
            x--;
            throw -1;
        }
    } 
    catch (...){
        std::cout << "Ooops" << std::endl;
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