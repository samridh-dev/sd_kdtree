#include <create/impl/keyval.hpp>
#include <create/impl/update.hpp>
#include <sort/sort.hpp>

#include "pch.hpp"

using namespace sd::kdtree::impl::create;

using T = std::size_t;
constexpr T dim { 2 };
constexpr T n   { 10 };

using arr_t = std::array<std::array<T, dim>, n>;
using tag_t = std::array<T, n>;

namespace std {

template<typename U, std::size_t N>
std::ostream& 
operator<<(std::ostream& os, const std::array<U, N>& arr) 
{
        os << "{";
        for (std::size_t i = 0; i < N; ++i) {
                os << arr[i];
                if (i != N - 1) os << ", ";
        }
        os << "}";
        return os;
}

} // namespace std;
int 
main(void)
{

        "[step0]"_test = [] {

                constexpr T lvl   { 0 };
                constexpr T split { lvl % dim };

                arr_t arr = {{
                        {10,15}, {46,63}, {68,21}, {40,33}, {25,54},
                        {15,43}, {44,58}, {45,40}, {62,69}, {53,67}
                }};
                arr_t arr_ans = {{
                        {10,15}, {15,43}, {25,54}, {40,33}, {44,58},
                        {45,40}, {46,63}, {53,67}, {62,69}, {68,21}
                }};

                tag_t tag     = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
                tag_t tag_ans = {1, 1, 1, 1, 1, 1, 0, 2, 2, 2};

                using pl = sd::policy_list_t<>;
                using spl = sd::policy_list_t<
                        keyval__f__less<pl>,
                        keyval__f__swap<pl>,
                        keyval__f__swap_if<pl>
                        #if 0
                        , sd::use_swap_if
                        #endif
                >;
                using iter_arr = decltype(arr.begin());
                using iter_tag = decltype(tag.begin());
                keyval_t<iter_tag, iter_arr, T> kv(
                        tag.begin(), arr.begin(), split
                );

                sd::default_context ctx;

                sd::sort<spl>(kv.begin(), n, ctx);
                expect(arr == arr_ans);

                update<pl>(tag.begin(), n, lvl, ctx);
                expect(tag == tag_ans);
        };

        "[step1]"_test = [] {

                constexpr T lvl   { 1 };
                constexpr T split { lvl % dim };

                arr_t arr = {{
                        {10,15}, {15,43}, {25,54}, {40,33}, {44,58},
                        {45,40}, {46,63}, {53,67}, {62,69}, {68,21}
                }};
                arr_t arr_ans = {{
                        {46,63}, {10,15}, {40,33}, {45,40}, {15,43},
                        {25,54}, {44,58}, {68,21}, {53,67}, {62,69}
                }};

                tag_t tag     = {1, 1, 1, 1, 1, 1, 0, 2, 2, 2};
                tag_t tag_ans = {0, 3, 3, 3, 1, 4, 4, 5, 2, 6};

                using pl = sd::policy_list_t<>;
                using spl = sd::policy_list_t<
                        keyval__f__less<pl>,
                        keyval__f__swap<pl>,
                        keyval__f__swap_if<pl>
                        #if 0
                        , sd::use_swap_if
                        #endif
                >;

                using iter_arr = decltype(arr.begin());
                using iter_tag = decltype(tag.begin());
                keyval_t<iter_tag, iter_arr, T> kv(
                        tag.begin(), arr.begin(), split
                );

                sd::default_context ctx;

                sd::sort<spl>(kv.begin(), n, ctx);
                expect(arr == arr_ans);

                update<pl>(tag.begin(), n, lvl, ctx);
                expect(tag == tag_ans);

        };

        "[step2]"_test = [] {

                constexpr T lvl   { 2 };
                constexpr T split { lvl % dim };

                arr_t arr = {{
                        {46,63}, {10,15}, {40,33}, {45,40}, {15,43},
                        {25,54}, {44,58}, {68,21}, {53,67}, {62,69}
                }};
                arr_t arr_ans = {{
                        {46,63}, {15,43}, {53,67}, {10,15}, {40,33},
                        {45,40}, {25,54}, {44,58}, {68,21}, {62,69}
                }};

                tag_t tag     = {0, 3, 3, 3, 1, 4, 4, 5, 2, 6};
                tag_t tag_ans = {0, 1, 2, 7, 3, 8, 9, 4, 5, 6};

                using pl = sd::policy_list_t<>;
                using spl = sd::policy_list_t<
                        keyval__f__less<pl>,
                        keyval__f__swap<pl>,
                        keyval__f__swap_if<pl>
                        #if 0
                        , sd::use_swap_if
                        #endif
                >;

                using iter_arr = decltype(arr.begin());
                using iter_tag = decltype(tag.begin());
                keyval_t<iter_tag, iter_arr, T> kv(
                        tag.begin(), arr.begin(), split
                );

                sd::default_context ctx;

                sd::sort<spl>(kv.begin(), n, ctx);
                expect(arr == arr_ans);

                update<pl>(tag.begin(), n, lvl, ctx);
                expect(tag == tag_ans);

        };

        return 0;

}
