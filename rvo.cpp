#include <iostream>

struct C {
    C() = default;
    C(const C&) { std::cout << "A copy was made.\n"; }
};

C f() {
    std::cout << "Called f()\n";
    return C();
}

C g() {
    std::cout << "Called g()\n";
    auto a = C();
    auto r = a;
    return r;
}

int main() {
    C obj1 = f();
    C obj2 = g();
}
