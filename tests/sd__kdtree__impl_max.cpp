#include <impl/max.hpp>

#include "pch.hpp"

int main(void) 
{
        using namespace boost::ut;

        "max with positive integers"_test = [] {
                expect(sd::kdtree::impl::max(3, 5) == 5_i);
                expect(sd::kdtree::impl::max(10, 2) == 10_i);
                expect(sd::kdtree::impl::max(42, 42) == 42_i);
        };

        "max with negative integers"_test = [] {
                expect(sd::kdtree::impl::max(-5, -1) == -1_i);
                expect(sd::kdtree::impl::max(-10, 2) == 2_i);
                expect(sd::kdtree::impl::max(-3, -3) == -3_i);
        };

        "max with floating points"_test = [] {
                expect(that % 2.3  == sd::kdtree::impl::max(1.2, 2.3));
                expect(that % 3.14 == sd::kdtree::impl::max(-5.7, 3.14));
                expect(that % 0.0  == sd::kdtree::impl::max(0.0, 0.0));
        };

        struct custom_type {
                int val;
                constexpr custom_type(int v) : val{v} {}
                constexpr inline bool operator>(const custom_type& rhs) const {
                        return val > rhs.val;
                }
        };

        "max with custom type"_test = [] {

                custom_type a{10};
                custom_type b{5};
                custom_type c{10};

                expect(sd::kdtree::impl::max(a, b).val == 10_i);
                expect(sd::kdtree::impl::max(b, c).val == 10_i);

        };

        return 0;
}
