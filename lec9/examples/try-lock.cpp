#include <iostream>
#include <thread>
#include <mutex>

const size_t MAX_WAIT = 1000;
const size_t N = 100000;
int x = 0;
std::mutex mtx;

void increment() {
    size_t i = 0, wait = 0;
    while (i < N && wait < MAX_WAIT) {
        if (mtx.try_lock()) {
            x++; 
            i++;
            wait = 0;
            mtx.unlock();
        }
        else {
            wait++;
        }
    }
}

void decrement() {
    try {
        for (size_t i = 0; i < N; i++) {
            mtx.lock();
            x--;
            throw -1;
            mtx.unlock();
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