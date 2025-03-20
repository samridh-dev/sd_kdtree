#include <search/nn.hpp>
#include "pch.hpp"

using T = int;
constexpr T dim { 2 };
constexpr T n   { 10 };

using pos_t = std::array<T, dim>;
using arr_t = std::array<pos_t, n>;

namespace std {

        template<typename U, std::integral auto N>
        std::ostream& 
        operator<<(std::ostream &os, const std::array<U, N> &arr) 
        {
                os << "{";
                for (std::size_t i = 0; i < N; ++i) {
                        os << arr[i];
                        if (i != N - 1)
                                os << ", ";
                }
                os << "}";
                return os;
        }

}

arr_t 
make_test_data(void) 
{
        return {{
                {46, 63}, {15, 43}, {53, 67}, {40, 33}, {44, 58},
                {68, 21}, {62, 69}, {10, 15}, {45, 40}, {25, 54}
        }};
}

#define RUN_NN_TESTS_FOR(I_TYPE)                                               \
        "[basic_test:1 (" #I_TYPE ")]"_test = [] {                             \
            arr_t vec = make_test_data();                                      \
            pos_t q {50, 50};                                                  \
            sd::kdtree::output_t<I_TYPE, T> out;                               \
            T r_min {0};                                                       \
            T r_max {100};                                                     \
            sd::kdtree::nn(vec.begin(), n, q.begin(), out.begin(),             \
                           r_min, r_max);                                      \
                                                                               \
            constexpr I_TYPE ans__idx = 4;                                     \
            constexpr I_TYPE ans__dst = 100;                                   \
            const pos_t ans__pos = {{44, 58}};                                 \
                                                                               \
            expect(out.dst() == ans__dst);                                     \
            expect(out.idx() == ans__idx);                                     \
            expect(vec[static_cast<std::size_t>(out.idx())] == ans__pos);      \
        };                                                                     \
                                                                               \
        "[basic_test:2 (" #I_TYPE ")]"_test = [] {                             \
            arr_t vec = make_test_data();                                      \
            pos_t q {46, 63};                                                  \
            sd::kdtree::output_t<I_TYPE, T> out;                               \
            T r_min {0};                                                       \
            T r_max {100};                                                     \
            sd::kdtree::nn(vec.begin(), n, q.begin(), out.begin(),             \
                            r_min, r_max);                                     \
                                                                               \
            constexpr I_TYPE ans__idx = 4;                                     \
            const pos_t ans__pos = {{44, 58}};                                 \
                                                                               \
            expect(out.idx() == ans__idx);                                     \
            expect(vec[static_cast<std::size_t>(out.idx())] == ans__pos);      \
        };                                                                     \
                                                                               \
        "[basic_test:3 (" #I_TYPE ")]"_test = [] {                             \
            arr_t vec = make_test_data();                                      \
            pos_t q {100, 100};                                                \
            sd::kdtree::output_t<I_TYPE, T> out;                               \
            T r_min {0};                                                       \
            T r_max {3000};                                                    \
            sd::kdtree::nn(vec.begin(), n, q.begin(), out.begin(),             \
                            r_min, r_max);                                     \
                                                                               \
            constexpr I_TYPE ans__idx = 6;                                     \
            const pos_t ans__pos = {{62, 69}};                                 \
                                                                               \
            expect(out.idx() == ans__idx);                                     \
            expect(vec[static_cast<std::size_t>(out.idx())] == ans__pos);      \
        };                                                                     \
                                                                               \
        "[basic_test:4 (" #I_TYPE ")]"_test = [] {                             \
                  arr_t vec = make_test_data();                                \
                  pos_t q {46, 63};                                            \
                  sd::kdtree::output_t<I_TYPE, T> out;                         \
                  T r_min {1};                                                 \
                  T r_max {100};                                               \
                  sd::kdtree::nn(vec.begin(), n, q.begin(), out.begin(),       \
                                 r_min, r_max);                                \
                                                                               \
                  constexpr I_TYPE ans__idx = 4;                               \
                  constexpr I_TYPE ans__dst = 29;                              \
                  const pos_t ans__pos = {{44, 58}};                           \
                                                                               \
                  expect(out.idx() == ans__idx);                               \
                  expect(vec[static_cast<std::size_t>(out.idx())] == ans__pos);\
        };

int 
main(void)
{
        
        RUN_NN_TESTS_FOR(std::uint64_t)
        RUN_NN_TESTS_FOR(std::int32_t)

        return 0;

}

