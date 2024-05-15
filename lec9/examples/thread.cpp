#include <thread>
#include <iostream>
#include <string>
#include <chrono>

const size_t N = 5;

void say_hello(std::string src) {
    for (size_t i = 0; i < N; i++) {
        std::cout << "[" << src << "]: Hello!" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
} 

int main() {
    std::thread thr(say_hello, "thr");
    say_hello("main");
    thr.join();
    return 0;
}