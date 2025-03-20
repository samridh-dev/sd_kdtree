#include <create/impl/ss.hpp>
#include <impl/bsr.hpp>

#include "pch.hpp"

using sd::kdtree::impl::create::ss;
using sd::kdtree::impl::bsr;

template <std::integral T>
constexpr inline T
ss(const T s, const T n)
{
        const T L{ bsr(n) + 1 };
        return ss(s, n, L);
}

namespace ref {

template <std::integral T>
constexpr inline T
ss(const T s, const T n)
{
        if (s >= n) {
                return T{ 0 };
        }
        return T{1} + ss(T{2} * s + T{1}, n) + ss(T{2} * s + T{2}, n);
}

} // namespace ref

template <std::integral T>
static void
check(void)
{
        std::mt19937_64 rng(12345ULL);
        std::uniform_int_distribution<T> dist(0, 127);

        const T imax{
                std::numeric_limits<T>::max() < (T{ 1 } << 16) ?
                        std::numeric_limits<T>::max() :
                        (T{ 1 } << 16)
        };

        for (T i{ 0 }; i < imax; i++) {
                T s{ dist(rng) };
                T n{ dist(rng) };
                if (s >= n) {
                        std::swap(s, n);
                }
                if (s == n) {
                        if (n < std::numeric_limits<T>::max()) {
                                n++;
                        }
                        else if (s > 0) {
                                s--;
                        }
                }
                expect( ss(s, n) == ref::ss(s, n) );
        }
}

int 
main(void)
{

        "case [1] [std::uint32_t] random tests"_test = [] {
                check<std::uint32_t>();
        };

        "case [2] [std::uint64_t] random tests"_test = [] {
                check<std::uint64_t>();
        };

        "case [3]"_test = [] {
                using T = std::int32_t;
                for (T k{ 1 }; k <= T{ sizeof(T) - 2 }; ++k)
                {
                        T n{ (T{ 1 } << k) - T{ 1 } };
                        expect( ss<T>(T{ 0 }, n) == n );
                }
        };

        "case [4]"_test = [] {
                using T = std::uint64_t;
                expect( ss<T>(T{ 0 }, T{ 0}) == T{ 0 } );
                expect( ss<T>(T{ 0 }, T{ 1}) == T{ 1 } );
                expect( ss<T>(T{ 1 }, T{ 1}) == T{ 0 } );
                expect( ss<T>(T{ 1 }, T{ 0}) == T{ 0 } );
        };

        return 0;
}
