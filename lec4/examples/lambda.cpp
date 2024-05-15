#include <iostream>

int main() {
    int x = 10;

    // Пример лямбда-функции с захватом переменной и параметром
    auto increase_x = [x](int a) -> int {
        return x + a;
    };

    // Пример лямбда-функции без захвата переменных и без параметров
    auto say_hello = []() {
        std::cout << "Hello, lambda!" << std::endl;
    };

    // Пример лямбда-функции без указания типа возвращаемого значения
    auto sum = [](int a, int b) {
        return a * b;
    };

    return 0;
}