#include <iostream>
#include <thread>
#include <mutex>

const size_t N = 100000;
int x = 0;
std::mutex mtx;

void increment() {
    for (size_t i = 0; i < N; i++) {
        mtx.lock(); // блокирующая операция
        x++; // критическая секция
        mtx.unlock();
    }
}

void decrement() {
    for (size_t i = 0; i < N; i++) {
        mtx.lock(); // блокирующаая операция
        x--; // критическая секция
        mtx.unlock();
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