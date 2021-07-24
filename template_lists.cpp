#include <cstring>
#include <iostream>
#include <utility>
#include <type_traits>

template<typename... Ts>
class Tuple {};

template<typename Head, typename... Tail>
class Tuple<Head, Tail...> {
    public:
        Tuple() {};
        Tuple(Head&& head, Tail&&... tail)
          : head(std::forward<Head>(head)),
            tail(std::forward<Tail>(tail)...)
        {}
        auto get_len() const -> std::size_t {
            return 1 + sizeof...(Tail);
        }
        auto get_head() const -> const Head& {
            return head;
        }
        auto get_tail() const -> const Tuple<Tail...>& {
            return tail;
        }

    private:
        Head head;
        Tuple<Tail...> tail;
};

template<typename... Ts>
auto make_tuple(Ts&&... args) {
    return Tuple<Ts...>(std::forward<Ts>(args)...);
}

template<size_t N>
struct TupleGet {
    template <typename Head, typename... Tail>
    static auto apply(const Tuple<Head, Tail...>& t) {
        return TupleGet<N-1>::apply(t.get_tail());
    }
};

template<>
struct TupleGet<0> {
    template <typename Head, typename... Tail>
    static auto apply(const Tuple<Head, Tail...>& t) {
        return t.get_head();
    }
};

template<size_t N, typename... Ts>
auto get(const Tuple<Ts...>& t) {
    return TupleGet<N>::apply(t);
}

// Reimplement print using fold expressions
template<size_t N>
struct TuplePrint {
    template<typename Head, typename... Tail>
    static auto print(const Tuple<Head, Tail...>& t) {
        auto h = t.get_head();
        std::cout << h << ": " << strlen(h) << "\n";

        TuplePrint<N-1>::print(t.get_tail());
    }
};

template<>
struct TuplePrint<0> {
    template<typename... Empty>
    static auto print(const Tuple<Empty...>& t) {}
};

template<typename... Ts>
void print(const Tuple<Ts...>& t) {
    TuplePrint<sizeof...(Ts)>::print(t);
}

// Implement structured bindings for Tuple

// ----------------------------------------------------
template<typename... Ts>
class List {};

template<typename T, typename... Rest>
class List<T, T, Rest...> {
    public:
        List(T&& first, T&& second, Rest&&... rest)
          : head(std::forward<T>(first)),
            tail(std::forward<T>(second), std::forward<Rest>(rest)...)
        {}
        auto get_len() const -> std::size_t {
            return 2 + sizeof...(Rest);
        }
        auto get_head() -> T& {
            return head;
        }
        auto get_tail() -> List<T, Rest...>& {
            return tail;
        }

    private:
        T head;
        List<T, Rest...> tail;
};

template<typename T>
class List<T> {
    public:
        List() {};
        List(T&& first)
          : head(std::forward<T>(first))
        {}
        auto get_len() const -> std::size_t {
            return 1;
        }
        auto get_head() -> T& {
            return head;
        }

    private:
        T head;
};

template<typename... Ts>
auto make_list(Ts&&... args) {
    return List<Ts...>(std::forward<Ts>(args)...);
}

template<size_t N>
struct ListGet {
    template<typename T, typename... Rest>
    static auto apply(List<T, T, Rest...>& l) {
        return ListGet<N-1>::apply(l.get_tail());
    }
};

template<>
struct ListGet<0> {
    template<typename T, typename... Rest>
    static auto apply(List<T, Rest...>& l) {
        return l.get_head();
    }
};

template<size_t N, typename... Ts>
auto get(List<Ts...>& l) {
    return ListGet<N>::apply(l);
}

// ----------------------------------------------------

template<typename... Ts>
class ArrayList {};

template<typename T, size_t N1, size_t N2, typename... Rest>
class ArrayList<T (&)[N1], T(&) [N2], Rest...> {
    public:
        ArrayList(const T (&first) [N1], const T (&second)[N2], Rest&&... rest)
          : head(first),
            tail(second, std::forward<Rest>(rest)...)
        {}
        auto get_len() const -> size_t {
            return 2 + sizeof...(Rest);
        }
        auto get_head() const -> Tuple<T (&)[N1], size_t> {
            return make_tuple(head, N1);
        }
        // auto&& to avoid copy, but not entirely sure if safe / best practice
        /* auto&& get_tail() const { */
        auto get_tail() const -> const ArrayList<T (&)[N2], Rest...>& {
            return tail;
        }

    private:
        const T (&head)[N1];
        const ArrayList<T (&)[N2], Rest...> tail;
};

template<typename T, size_t N>
class ArrayList<T (&)[N]> {
    public:
        ArrayList(const T (&first)[N])
          : head(first)
        {}
        auto get_len() const -> size_t {
            return 1;
        }
        auto get_head() const -> Tuple<const T (&)[N], size_t> {
            return make_tuple(head, N);
        }
    
    private:
        const T (&head)[N];
};

template<typename... Ts>
auto make_array_list(Ts&&... args) {
    return ArrayList<Ts...>(std::forward<Ts>(args)...);
}

template<size_t N>
struct ArrayListGet {
    template<typename... Ts>
    static auto apply(const ArrayList<Ts...>& al) {
        return ArrayListGet<N-1>::apply(al.get_tail());
    }
};

template<>
struct ArrayListGet<0> {
    template<typename Head, typename... Rest>
    static auto apply(const ArrayList<Head, Rest...>& al) {
        return al.get_head();
    }
};

template<size_t N, typename... Ts>
auto get(const ArrayList<Ts...>& al) {
    return ArrayListGet<N>::apply(al);
}

// To implement structured bindings
template<typename... Ts>
class std::tuple_size<ArrayList<Ts...>>
  : public std::integral_constant<std::size_t, sizeof...(Ts)> {};

// To implement structured bindings
template<std::size_t I, typename Head, typename... Tail> 
class std::tuple_element<I, ArrayList<Head, Tail...>>
  : public tuple_element<I-1, ArrayList<Tail...>> {};

// To implement structured bindings
template<typename T, std::size_t N, typename... Tail>
class std::tuple_element<0, ArrayList<T (&)[N], Tail...>> {
    public:
        using type = Tuple<T (&)[N], size_t>;
};

// ----------------------------------------------------

auto return_ref() {
    char s[] = "hi";
    return std::ref(s);
}

auto main(int argc, char* argv[]) -> int {
    auto p = make_tuple("path1", "p2", "path3_long");
    std::cout << get<2>(p) << std::endl;
    std::cout << get<0>(p) << std::endl;
    std::cout << "len: " << p.get_len() << "\n";

    std::cout << "\n--------------------\n\n";

    /* print(p); */

    /* std::cout << "\n--------------------\n\n"; */

    auto l = make_list(1.1, 2.2, 3.3);
    /* auto l = make_list("path1", "p2", "path3_long"); */
    std::cout << l.get_len() << "\n";
    std::cout << get<2>(l) << "\n";
    auto t = get<2>(l);
    t += 2;
    std::cout << get<2>(l) << "\n";

    std::cout << "\n--------------------\n\n";

    // WARNING: since ArrayList is meant for generic arrays, when used with chars the number of elements will
    // include the null terminator
    auto al = make_array_list("hi", "hello", "hey");
    std::cout << "length of list: " << al.get_len() << "\n";
    auto&& [first, second, third] = al;
    std::cout << "length of \"" << get<0>(first) << "\": " << get<1>(first) << "\n";
    std::cout << "length of \"" << get<0>(second) << "\": " << get<1>(second) << "\n";
    std::cout << "length of \"" << get<0>(third) << "\": " << get<1>(third) << "\n";

    /* std::cout << "\n--------------------\n\n"; */

    // to illustrate possibility of C++ dangling reference (solved with lifetimes in Rust)
    /* auto al = make_array_list(return_ref().get()); */
    /* auto v = get<0>(get<0>(al)); */
    /* std::cout << v << "\n"; */
}
