#include "stdafx.h"

// https://oleksandrkvl.github.io/2021/04/02/cpp-20-overview.html

template<typename T>
concept is_sortable = true;

auto l = [](auto x) {};
void f1(auto x) {}               // unconstrained template
void f2(is_sortable auto x) {}   // constrained template

template<is_sortable auto NonTypeParameter, is_sortable TypeParameter>
is_sortable auto f3(is_sortable auto x, auto y)
{
    // notice that nothing is allowed between constraint name and `auto`
    is_sortable auto z = 0;
    return 0;
}

template<is_sortable auto... NonTypePack, is_sortable... TypePack>
void f4(TypePack... args) {}

int f() { return 0; };

// takes two parameters
template<typename T1, typename T2>
concept C = true;
// binds second parameter
C<double> auto v = f(); // means C<int, double>

struct X {
    operator is_sortable auto() {
        return 0;
    }
};

auto f5() -> is_sortable decltype(auto){
    f4<1, 2, 3>(1, 2, 3);
    return new is_sortable auto(1);
}

void HandleString(const char*) {}
// distinct function name is required to handle UTF-8 in C++17
void HandleStringUTF8(const char*) {}
// now it can be done using convenient overload
void HandleString(const char8_t*) {}

void Cpp20() {
    HandleString("abc");    // char
    HandleString(u8"abc");  // char8_t
}

struct duration {
    constexpr duration() {}
    constexpr operator int() const { return 0; }
};

// duration d = duration(); // #1
int n = sizeof(int{ duration(duration()) });    // always OK since C++20

int f_() {
    using T = int;
    T n{ 1 };
    n.~T();     // no effect in C++17, ends n's lifetime in C++20
    return n;   // OK in C++17, UB in C++20, n is dead now
}


