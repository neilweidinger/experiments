#include <iostream>

struct C {
    C() { std::cout << "Constructor called\n"; }
    C(C const& other) { std::cout << "Copy constructor called\n"; }
    C& operator=(C const& rhs) { std::cout << "Copy assignment operator called\n"; return *this; }
    C(C&& other) noexcept { std::cout << "Move constructor called\n"; }
    C& operator=(C&& other) noexcept { std::cout << "Move assignment operator called\n"; return *this; }

    void do_something() {
        std::cout << "doing something\n";
    }
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
    return a; // no need to use std::move here, as returning local variable will (hopefully) trigger
              // NRVO (Item 25 page 174 Effective Modern C++)
}

// can disable NVRO using -fno-elide-constructors
int main() {
    {
        C obj = f();
        obj.do_something();
        std::cout << "\n";
    }

    {
        C obj = g();
        obj.do_something();
        std::cout << "\n";
    }

    {
        C obj = h();
        obj.do_something();
        std::cout << "\n";
    }

    {
        C obj = z();
        obj.do_something();
        std::cout << "\n";
    }
}
