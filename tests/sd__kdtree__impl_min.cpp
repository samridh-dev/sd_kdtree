#include <impl/min.hpp>

#include "pch.hpp"

int
main(void) 
{

        using namespace boost::ut;

        "min with positive integers"_test = [] {
                expect(sd::kdtree::impl::min(3, 5) == 3_i);
                expect(sd::kdtree::impl::min(10, 2) == 2_i);
                expect(sd::kdtree::impl::min(42, 42) == 42_i);
        };

        "min with negative integers"_test = [] {
                expect(sd::kdtree::impl::min(-5, -1) == -5_i);
                expect(sd::kdtree::impl::min(-10, 2) == -10_i);
                expect(sd::kdtree::impl::min(-3, -3) == -3_i);
        };

        "min with floating points"_test = [] {
                expect(that % 1.2  == sd::kdtree::impl::min(1.2, 2.3));
                expect(that % -5.7 == sd::kdtree::impl::min(-5.7, 3.14));
                expect(that % 0.0  == sd::kdtree::impl::min(0.0, 0.0));
        };

        struct custom_type {
                int val;
                constexpr custom_type(int v) : val{v} {}
                constexpr inline bool 
                operator<(const custom_type& rhs) const 
                {
                        return val < rhs.val;
                }
        };

        "min with custom type"_test = [] {

                custom_type a{10};
                custom_type b{5};
                custom_type c{5};

                expect(sd::kdtree::impl::min(a, b).val == 5_i);
                expect(sd::kdtree::impl::min(b, c).val == 5_i);

        };

        return 0;

}
