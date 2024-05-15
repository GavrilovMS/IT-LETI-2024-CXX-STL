#include <condition_variable>
#include <mutex>
#include <thread>
#include <iostream>

std::mutex mtx;
std::condition_variable cv;
bool data_ready = false;

int x = 0;
size_t N = 10;

void consumer_thread() {
    std::unique_lock<std::mutex> lock(mtx);
    std::cout << "waiting" << std::endl;
    cv.wait(lock, []{ return data_ready; }); // Ожидаем, пока data_ready станет true
    std::cout << x << std::endl;
}

void producer_thread() {
    std::this_thread::sleep_for(std::chrono::seconds(1));
    x = 10;
    {
        std::lock_guard<std::mutex> lock(mtx);
        data_ready = true;
    }
    cv.notify_all(); // Оповещаем ожидающий поток
}

int main() {
    {
        std::jthread worker(consumer_thread);
        std::jthread producer(producer_thread);
    }
    return 0;
}