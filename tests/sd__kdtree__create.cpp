#include <create/create.hpp>
                      
#include "pch.hpp"

template<template<class...> class OUTER,
         template<class...> class INNER,
         typename Tv,
         typename Ts
         >
static bool 
test_(Ts n) 
{
        OUTER<INNER<Tv>> vec = {
                { { 10, 15 } }, { { 46, 63 } },
                { { 68, 21 } }, { { 40, 33 } },
                { { 25, 54 } }, { { 15, 43 } },
                { { 44, 58 } }, { { 45, 40 } },
                { { 62, 69 } }, { { 53, 67 } }
        };

        OUTER<INNER<Tv>> ans = {
                { { 46, 63 } }, { { 15, 43 } },
                { { 53, 67 } }, { { 40, 33 } },
                { { 44, 58 } }, { { 68, 21 } },
                { { 62, 69 } }, { { 10, 15 } },
                { { 45, 40 } }, { { 25, 54 } }
        };

        sd::kdtree::create(vec.begin(), n);
        return vec == ans;
}

template <typename Ts, typename Tv>
void 
test_kdtree_create(void) 
{
        constexpr Ts n = 10;

        "std::list< std::vector >"_test = [n]() {
                expect( test_<std::list, std::vector, Tv>(n) );
        };
        "std::deque< std::vector >"_test = [n]() {
                expect( test_<std::deque, std::vector, Tv>(n) );
        };
        "std::forward_list< std::vector >"_test = [n]() {
                expect( test_<std::forward_list, std::vector, Tv>(n) );
        };
        "std::vector< std::vector >"_test = [n]() {
                expect( test_<std::vector, std::vector, Tv>(n) );
        };

        "std::list< std::list >"_test = [n]() {
                expect( test_<std::list, std::list, Tv>(n) );
        };
        "std::deque< std::list >"_test = [n]() {
                expect( test_<std::deque, std::list, Tv>(n) );
        };
        "std::forward_list< std::list >"_test = [n]() {
                expect( test_<std::forward_list, std::list, Tv>(n) );
        };
        "std::vector< std::list >"_test = [n]() {
                expect( test_<std::vector, std::list, Tv>(n) );
        };

        "std::list< std::deque >"_test = [n]() {
                expect( test_<std::list, std::deque, Tv>(n) );
        };
        "std::deque< std::deque >"_test = [n]() {
                expect( test_<std::deque, std::deque, Tv>(n) );
        };
        "std::forward_list< std::deque >"_test = [n]() {
                expect( test_<std::forward_list, std::deque, Tv>(n) );
        };
        "std::vector< std::deque >"_test = [n]() {
                expect( test_<std::vector, std::deque, Tv>(n) );
        };

        "std::list< std::forward_list >"_test = [n]() {
                expect( test_<std::list, std::forward_list, Tv>(n) );
        };
        "std::deque< std::forward_list >"_test = [n]() {
                expect( test_<std::deque, std::forward_list, Tv>(n) );
        };
        "std::forward_list< std::forward_list >"_test = [n]() {
                expect( test_<std::forward_list, std::forward_list, Tv>(n) );
        };
        "std::vector< std::forward_list >"_test = [n]() {
                expect( test_<std::vector, std::forward_list, Tv>(n) );
        };
}

int 
main(void) 
{

        "kdtree::create basic [std::int32_t][std::int32_t]"_test = [] {
                test_kdtree_create<std::int32_t, std::int32_t>();
        };
        "kdtree::create basic [std::int32_t][std::int64_t]"_test = [] {
                test_kdtree_create<std::int32_t, std::int64_t>();
        };
        "kdtree::create basic [std::int32_t][std::uint32_t]"_test = [] {
                test_kdtree_create<std::int32_t, std::uint32_t>();
        };
        "kdtree::create basic [std::int32_t][std::uint64_t]"_test = [] {
                test_kdtree_create<std::int32_t, std::uint64_t>();
        };

        return 0;
}
