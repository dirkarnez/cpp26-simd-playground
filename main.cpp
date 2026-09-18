#include <iostream>
#include <simd>
#include <string_view>

namespace simd = std::simd;

void println(std::string_view name, auto const& a)
{
    std::cout << name << ": ";
    for (std::size_t i{}; i != a.size(); ++i)
        std::cout << a[i] << ' ';
    std::cout << '\n';
}

template<class A>
constexpr simd::basic_vec<int, A> my_abs(simd::basic_vec<int, A> x)
{
    return simd::select(x < 0, -x, x);
}

int main()
{
    constexpr simd::vec<int> a = 1;
    println("a", a);

    constexpr simd::vec<int> b([](int i) { return i - 2; });
    println("b", b);

    constexpr auto c = a + b;
    println("c", c);

    constexpr auto d = my_abs(c);
    println("d", d);

    constexpr auto e = d * d;
    println("e", e);

    constexpr auto inner_product = simd::reduce(e);
    std::cout << "inner product: " << inner_product << '\n';

    constexpr simd::vec<double, 16> x([](int i) { return i; });
    println("x", x);
    // overloaded math functions are defined in <simd>
    println("cos²(x) + sin²(x)", std::pow(std::cos(x), 2) + std::pow(std::sin(x), 2));
}
