#include <iostream>
#include <string>

class Pet{
public:
    std::string name;
    unsigned int age;
    void run() {
        //some code
    }
    virtual void talk() = 0;
};

class Cat : public Pet {
public:
    std::string breed;
    void talk() override {
        //
    }
};

class Dog : public Pet {
public:
    std::string breed;
    void talk() override {
        //
    }
};

int main() {
    Cat cat;
    cat.name = "Barsik";
    cat.age = 2;
    cat.breed = "Siamese";
    cat.talk();
    cat.run();

    Dog dog;
    dog.name = "Rex";
    dog.age = 3;
    dog.breed = "Sheepdog";
    dog.talk();
    dog.run();

    return 0;
}