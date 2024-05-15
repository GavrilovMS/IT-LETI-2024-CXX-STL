#include <optional>
#include <iostream>

std::optional<int> divide(int a, int b) {
    if (b == 0) {
        return std::nullopt;
    } else {
        return a / b;
    }
}

int main() {
    int x = 10;
    int y = 2;

    // Пытаемся поделить
    std::optional<int> result = divide(x, y);

    // // Проверяем, есть ли значение
    // if (result.has_value()) {
    //     std::cout << "Результат деления: " << result.value() << std::endl;
    // } else {
    //     std::cout << "Деление на ноль!" << std::endl;
    // }

    // Лучше
    if (result) {
        std::cout << "Результат деления: " << *result << std::endl;
    } else {
        std::cout << "Деление на ноль!" << std::endl;
    }

    return 0;
}