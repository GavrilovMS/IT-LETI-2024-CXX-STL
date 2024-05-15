#include <iostream>
#include <atomic>

int main() {
    std::atomic<int> x = 1;

    int expected, desired;
    // do {
    //     std::cout << "oops" << std::endl;
    //     expected = x.load();
    //     desired = expected * 9;
    // } while (x.compare_exchange_weak(expected, desired)); // вернуло false => другой поток изменил x
    
    int temp = x.load();
    while(x.compare_exchange_weak(temp, temp * 9)) {}

    std::cout << x << std::endl;
    return 0;
}