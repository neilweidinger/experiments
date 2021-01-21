#include <iostream>

struct C {
    C() { std::cout << "Constructor called\n"; }
    C(C const& other) { std::cout << "Copy constructor called\n"; }
    C& operator=(C const& rhs) { std::cout << "Copy assignment operator called\n"; return *this; }
    C(C&& other) noexcept { std::cout << "Move constructor called\n"; }
    C& operator=(C&& other) noexcept { std::cout << "Move assignment operator called\n"; return *this; }
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

C h() {
    std::cout << "Called h()\n";
    auto a = C();
    auto r = std::move(a);
    return r;
}

C z() {
    std::cout << "Called z()\n";
    auto a = C();
    return a; // no need to use std::move here, as returning local variable will trigger RVO (Item 25 page 174 Effective Modern C++)
}

int main() {
    C obj1 = f();
    std::cout << "\n";

    C obj2 = g();
    std::cout << "\n";

    C obj3 = h();
    std::cout << "\n";

    C obj4 = z();
}
