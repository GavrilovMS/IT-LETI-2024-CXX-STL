#include <iostream>

int main() {
    char a = 4;
    short b;

    char* ptrA = &a;
    short* ptrB = &b;

    char* d = "sdldslk;lsdgkl;fsg";
    std::cout << d << std::endl;
    std::cout << "a = " << a << " ptrA = " << ptrA << " *ptrA = " << *ptrA << std::endl;
    std::cout << "b = " << b << " ptrB = " << ptrB << " *ptrB = " << *ptrB << std::endl;

    std::cout << std::endl;

    *ptrB = 5;

    std::cout << "a = " << (int)a << " ptrA = " << (int*)ptrA << " *ptrA = " << (int)*ptrA << std::endl;; // Преобразование указателя к типу void* обосновано особенностями вывода в консоль типа char*
    std::cout << "b = " << b << " ptrB = " << ptrB << " *ptrB = " << *ptrB << std::endl;
    std::cout << "sizeof(a) = " << sizeof(a) << std::endl;
    std::cout << "sizeof(b) = " << sizeof(b) << std::endl;

    return 0;
}
