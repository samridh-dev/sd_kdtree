#include "pch.hpp"

#include <impl/clz.hpp>

int 
main(void) {

        "clz returns correct count for zero"_test = [] {
                unsigned u { 0 };
                expect(sd::kdtree::impl::clz(u) == std::countl_zero(u));
        };

        "clz returns correct count for a power of two"_test = [] {
                unsigned u { 1 << 5 };
                expect(sd::kdtree::impl::clz(u) == std::countl_zero(u));
        };

        "clz returns correct count for various unsigned values"_test = [] {
                for (unsigned u{0}; u < 256; ++u) {
                        expect(sd::kdtree::impl::clz(u) == std::countl_zero(u));
                }
        };

        "clz works correctly with fixed-width types (uint32_t)"_test = [] {
                uint32_t x { 0xF0F0F0F0 };
                expect(sd::kdtree::impl::clz(x) == std::countl_zero(x));
        };

        "clz works correctly with fixed-width types (uint64_t)"_test = [] {
                uint64_t x { 0x0F0F0F0F0F0F0F0F };
                expect(sd::kdtree::impl::clz(x) == std::countl_zero(x));
        };

        return 0;
}
