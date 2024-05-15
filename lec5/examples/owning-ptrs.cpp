#include <iostream>

class A {
    // Some code
};

class owning_A {
    A* a;
    owning_A() : a(new A) {}  
    ~owning_A() {
        delete a;
    }  
};

class non_owning_A {
    A* a;
};