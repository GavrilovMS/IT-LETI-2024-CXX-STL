#include <iostream>

int main() {
    int a = 4;
    int& b = a; // Инициализация (связывание ссылки и переменной)

    std::cout << "a = " << a << " b = " << b << std::endl;

    b++;

    std::cout << "a = " << a << " b = " << b << std::endl;

    int c = 5;
    b = c; // Присваивание (копирование c в b)
    
    std::cout << "a = " << a << " b = " << b << std::endl;

    return 0;
}
