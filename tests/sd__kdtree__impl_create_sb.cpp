#include <create/impl/sb.hpp>
#include <create/impl/ss.hpp>
#include <create/impl/F.hpp>
#include <impl/bsr.hpp>

#include "pch.hpp"

using sd::kdtree::impl::create::ss;
using sd::kdtree::impl::create::sb;
using sd::kdtree::impl::create::F;
using sd::kdtree::impl::bsr;

template <std::integral T>
constexpr inline T
sb(const T s, const T n)
{
        const T L{ bsr(n) + 1 };
        return sb(s, n, L);
}

namespace ref {

template <std::integral T>
constexpr inline T
ss(T s, T n)
{
        T ss_s{ 0 };
        T w{ 1 };
        while (s < n)
        {
                T beg{s};
                ss_s += (w < (n - beg)) ? w : (n - beg);
                s = T{ 2 } * s + T{ 1 };
                w += w;
        }
        return ss_s;
}

template <std::integral T>
constexpr inline T
sb(const T s, const T n)
{
        const T l{ bsr(s + 1) };
        T sb_s_l{ F(l) };
        for (T i{ sb_s_l }; i < s; ++i)
        {
                sb_s_l += ss(i, n);
        }
        return sb_s_l;
}

} // namespace ref

int main(void)
{
        using namespace boost::ut;

        "case [1]"_test = [] {
                using namespace std;
                expect( sb<int32_t>(1, 2) == ref::sb<int32_t>(1, 2) );
                expect( sb<int32_t>(1, 3) == ref::sb<int32_t>(1, 3) );
                expect( sb<int32_t>(2, 3) == ref::sb<int32_t>(2, 3) );

                expect( sb<int32_t>(3, 4) == ref::sb<int32_t>(3, 4) );
                expect( sb<int32_t>(4, 5) == ref::sb<int32_t>(4, 5) );
                expect( sb<int32_t>(7, 8) == ref::sb<int32_t>(7, 8) );
                expect( sb<int32_t>(8, 9) == ref::sb<int32_t>(8, 9) );

                expect( sb<int32_t>(15, 16) == ref::sb<int32_t>(15, 16) );
                expect( sb<int32_t>(16, 17) == ref::sb<int32_t>(16, 17) );
                expect( sb<int32_t>(31, 32) == ref::sb<int32_t>(31, 32) );
                expect( sb<int32_t>(32, 33) == ref::sb<int32_t>(32, 33) );

                expect( sb<int64_t>(63, 64) == ref::sb<int64_t>(63, 64) );
                expect( sb<int64_t>(64, 65) == ref::sb<int64_t>(64, 65) );
                expect( sb<int64_t>(127, 128) == ref::sb<int64_t>(127, 128) );
                expect( sb<int64_t>(128, 129) == ref::sb<int64_t>(128, 129) );
        };

        return 0;
}
