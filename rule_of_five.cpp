#include <iostream>
#include <type_traits>
#include <utility>
#include <cstring>

// Extremely useful CppCon talk on move semantics: https://youtu.be/St0MNEU5b0o
// Slides: https://github.com/CppCon/CppCon2019/blob/master/Presentations/back_to_basics_move_semantics_part_1/back_to_basics_move_semantics_part_1__klaus_iglberger__cppcon_2019.pdf
// There's also a part 2 talk.
class MyClass {
    public:
        explicit MyClass(char const* s = "abc")
          : cstring(nullptr)
        {
            std::cout << this << " Called constructor\n";

            if (s) {
                std::size_t n = std::strlen(s) + 1;
                cstring = new char[n];
                std::memcpy(cstring, s, n);
            }
        }

        ~MyClass() noexcept
        {
            std::cout << this << " Called destructor\n";

            delete[] cstring;
        }

        MyClass(MyClass const& other)
          /* could use delegating constuctor, but we copy in body to make demonstration explicit */
          /* : MyClass(other.cstring) */
        {
            std::cout << this << " Called copy constructor\n";

            if (other.cstring) {
                std::size_t n = std::strlen(other.cstring) + 1;
                cstring = new char[n];
                std::memcpy(cstring, other.cstring, n);
            }
        }

        auto operator=(MyClass const& other) -> MyClass&
        {
            std::cout << this << " Called copy assignment operator\n";

            std::size_t n = std::strlen(other.cstring) + 1;

            if (n == std::strlen(cstring) + 1) {
                std::memcpy(cstring, other.cstring, n);
            }
            else {
                delete[] cstring;
                cstring = new char[n];
                std::memcpy(cstring, other.cstring, n);
            }

            return *this;
        }

        MyClass(MyClass&& other) noexcept
          : cstring(std::exchange(other.cstring, nullptr))
        {
            std::cout << this << " Called move constructor\n";
        }

        auto operator=(MyClass&& other) noexcept -> MyClass&
        {
            std::cout << this << " Called move assignment operator\n";

            delete[] cstring;
            cstring = std::exchange(other.cstring, nullptr);

            return *this;
        }

        // Uses C++14 deduced return types (notice there's no -> in the function declarator),
        // can of course just return -> T
        template <typename T, uint32_t N>
        constexpr auto pow(T const& v)
        {
            static_assert(std::is_integral<T>::value || std::is_floating_point<T>::value,
                          "Base of power must be integral or floating point type");

            auto product = T{1};

            for (int i = 0; i < N; i++) {
                product *= v;
            }

            return product;
        }

        // Only works in C++17 and above
        // This version of pow() differs from the one above because you can just call pow<base, exponent>()
        // Uses non-type template parameters, and C++17 allowing placeholder types (i.e. auto) as non-type template parameters
        // Base can ONLY be an integral type, floating point types as non-type template parameters not supported (should be introduced in C++20)
        // Also uses C++14 deduced return types, can also just return -> decltype(base)
        template <auto base, uint32_t exponent>
        constexpr auto pow()
        {
            using Base_type = decltype(base);
            static_assert(std::is_integral<Base_type>::value, "Base of power must be integral");

            auto product = Base_type{1};

            for (int i = 0; i < exponent; i++) {
                product *= base;
            }

            return product;
        }

        void print_cstring()
        {
            std::cout << "Called print_cstring\n";
            std::cout << "cstring = " << this->cstring << "\n";
        }

    private:
        char *cstring;
};

auto doSomething(MyClass c) -> std::uint32_t
{
    std::cout << "Called doSomething\n";

    // u is integer literal suffix
    // std::integral_constant to force evaluation of power at compile time
    return std::integral_constant<std::uint32_t, c.pow<2u, 31>()>::value;
}

auto main(int argc, char* argv[]) -> int
{
    {
        std::cout << "**************************** \n";
        std::cout << "DEMO: Pass rvalue (std::move'd object) as argument\n\n";

        MyClass object{};
        std::cout << doSomething(std::move(object)) << "\n";
    }

    {
        std::cout << "\n **************************** \n";
        std::cout << "DEMO: Pass lvalue as argument\n\n";

        MyClass object{};
        std::cout << doSomething(object) << "\n";
    }

    {
        std::cout << "\n **************************** \n";
        std::cout << "DEMO: Pass rvalue (object construction) as argument\n\n";

        std::cout << doSomething(MyClass()) << "\n";
    }

    {
        std::cout << "\n **************************** \n";
        std::cout << "DEMO: Copy constructor\n\n";

        MyClass object1{};
        MyClass object2{object1};
    }

    {
        std::cout << "\n **************************** \n";
        std::cout << "DEMO: Copy constructor 2\n\n";

        MyClass object1{"test"};
        MyClass object2 = object1;
    }

    {
        std::cout << "\n **************************** \n";
        std::cout << "DEMO: Copy assignment\n\n";

        MyClass object1{};
        MyClass object2{"abcd"};  // purposely create object2 with cstring of different length to object1 so that original object2 cstring gets deleted
        object2 = object1;
    }

    {
        std::cout << "\n **************************** \n";
        std::cout << "DEMO: Move constructor\n\n";

        MyClass object1{};
        MyClass object2{std::move(object1)};
    }

    {
        std::cout << "\n **************************** \n";
        std::cout << "DEMO: Move assignment\n\n";

        MyClass object1{};
        MyClass object2{};
        object2 = std::move(object1);
    }

    return 0;
}
