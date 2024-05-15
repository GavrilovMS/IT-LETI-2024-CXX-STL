#include <iostream>

class A {
    // Some code
};

class owning_A {
    A a;
};

class non_owning_A {
    A& a;
};
