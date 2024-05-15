#include <iostream>

template<typename L, typename R, typename Res = L>
Res Sum(L left, R right) {
    return left + right;
}

int main() {
    int a = 1;
    float b = 1.5;

    std::cout << Sum(a, b) << std::endl;
    std::cout << Sum<float>(a, b) << std::endl;

    return 0;
}