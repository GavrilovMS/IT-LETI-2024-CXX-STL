#include <mutex>
#include <thread>
#include <iostream>

std::mutex mtx;
bool data_ready = false;

int x = 0;

void consumer_thread() {
    for (;;) {
        std::cout << "waiting" << std::endl;
        std::lock_guard<std::mutex> lock(mtx);
        if (data_ready) {
            std::cout << x << std::endl;
            return;
        } 
    }
}

void producer_thread() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    x = 10;
    {
        std::lock_guard<std::mutex> lock(mtx);
        data_ready = true;
    }
}

int main() {
    {
        std::jthread worker(consumer_thread);
        std::jthread producer(producer_thread);
    }
    return 0;
}