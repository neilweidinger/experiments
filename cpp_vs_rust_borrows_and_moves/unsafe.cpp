#include <iostream>
#include <string>

class C {
    public:
        explicit C(std::string s = "hello world")
          : data{s}
        {
            std::cout << "Called constructor\n";
        }

        C(C const& other) = delete;
        auto operator=(C const& other) -> C& = delete;
        
        C(C&& other) noexcept
          : data{std::move(other.data)}
        {
            std::cout << "Called move constructor\n";
            other.data = "error! object has been moved from!";
        }

        auto operator=(C&& other) noexcept -> C&
        {
            std::cout << "Called move assignment operator\n";

            data = std::move(other.data);
            other.data = "error! object has been moved from!";

            return *this;
        }

        void print_data() const
        {
            std::cout << data << "\n";
        }

    private:
        std::string data;
};

// We try and "borrow" by using a reference, but this function actually "steals" under the
// surface using std::move, leaving object in a moved from state.
// Cannot accept C const& as then we could not use move constructor, since move constructor
// (and move assignment operator) expects non const object (since they want to "steal"
// internals, does not make sense for object to be const, would imply moving is as efficient
// as just copying since if object was const it would stay intact but we now have a copy).
void unsafe_borrow(C& object) {
    auto stolen = std::move(object);
    stolen.print_data();
}

// Legal in the sense that this function accepts an r-value ref, meaning if you std::move an
// object into this function it's your fault if you continue to use it after.
void legal_move(C&& object) {
    // not "stolen" anymore, as function takes r-value ref implying moving is fair game
    auto moved = std::move(object); 
    moved.print_data();
}

auto main(int argc, char* argv[]) -> int {
    {
        C a;
        a.print_data();

        // would not work if a was declared const, as unsafe_borrow doesn't accept const
        // l-value reference, since it uses the move constructor and the move constructor
        // only accepts non-const r-value refs (const r-value ref wouldn't make sense, as
        // the whole point of r-value ref is to steal internals)
        unsafe_borrow(a); 

        // using moved from object, arguably an error
        a.print_data();
    }

    std::cout << "----------------------------\n";

    {
        C a;
        a.print_data();

        // would not work if a was declared const, as legal_move doesn't accept const
        // r-value ref, nor would it make sense to (the whole point of r-value ref is to
        // steal internals)
        legal_move(std::move(a)); 

        // using moved from object, arguably an error
        a.print_data();
    }

    return 0;
}
