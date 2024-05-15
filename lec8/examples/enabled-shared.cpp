#include <memory>


class BadExample  {
    void foo() {
        bar(std::make_shared<BadExample>(this));
    }
};

class Example : public std::enable_shared_from_this<Example> {
    void foo() {
        bar(this->shared_from_this());
    }
};

void bar(std::shared_ptr<Example> ptr) {}
void bar(std::shared_ptr<BadExample> ptr) {}

int main() {
    return 0;
}