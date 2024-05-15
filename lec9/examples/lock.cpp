#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <string>
#include <windows.h>

const size_t N = 5;
std::mutex talking_mtx;
std::vector<std::mutex> forks(N);

void talk(std::string str) {
    std::lock_guard<std::mutex> lk(talking_mtx);
    std::cout << str << std::endl;
}

void philosopher(size_t l_fork, size_t r_fork){
    talk("thinking");
    std::lock(forks[l_fork], forks[r_fork]);
    talk("eating");
}

int main() {
    {
        std::vector<std::jthread> philosophers;
        for (size_t i = 0; i < N; i++) {
            philosophers.emplace_back(philosopher, i, (i+1) % N);
        }
    }
    std::cout << "All philosophers are fed" << std::endl;
    return 0;
}