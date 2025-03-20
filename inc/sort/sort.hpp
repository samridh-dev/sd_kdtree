#ifndef __INCLUDE__KDTREE_SORT_HPP
#define __INCLUDE__KDTREE_SORT_HPP

#include "../impl/concept.hpp"
#include "../impl/context.hpp"
#include "../impl/policy.hpp"

namespace sd {

template <std::integral auto n, sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto 
sort(sd::iterator auto it) 
-> void;

template <sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto 
sort(sd::iterator auto it, const sd::integral auto n) 
-> void;

template <sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto 
sort(sd::iterator auto it, const sd::integral auto n, sd::context auto ctx) 
-> void;

} // namespace sd

///////////////////////////////////////////////////////////////////////////////
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                             IMPLEMENTATION                              ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///                                                                         ///
///////////////////////////////////////////////////////////////////////////////


template <sd::policy_list pl>
constexpr inline auto 
sd::sort(sd::iterator auto it, const sd::integral auto n) 
-> void 
{
        sd::default_context ctx;
        return sd::sort<pl>(it, n, ctx);
}

#include "../impl/traits.hpp"

#include "traits.hpp"

template <sd::policy_list pl>
constexpr inline auto 
sd::sort(sd::iterator auto it, const sd::integral auto n, sd::context auto ctx) 
-> void 
{

        using I = std::remove_cvref_t<decltype(n)>;

        constexpr auto f__for     { sd::get_f__for<pl>()     };
        constexpr auto f__less    { sd::get_f__less<pl>()    };
        constexpr auto f__swap    { sd::get_f__swap<pl>()    };
        constexpr auto f__swap_if { sd::get_f__swap_if<pl>() };

        if ((n & (n - 1)) == 0) {
                for (I k{2}; k <= n; k *= 2) {
                for (I j{k / 2}; j > 0; j /= 2) {
                f__for(I{0}, n, [=](I i) {
                        const I ij { i ^ j };
                        if (ij > i) {
                                const bool ascending { ((i & k) == 0) };
                                if (ascending) {
                                if (!f__less.template 
                                    operator()<decltype(it)>(
                                    sd::next<pl>(it, i),
                                    sd::next<pl>(it, ij))
                                    ) {
                                        f__swap.template 
                                        operator()<decltype(it)>(
                                                sd::next<pl>(it, i),
                                                sd::next<pl>(it, ij)
                                        );
                                }
                                } else {
                                if (f__less.template 
                                    operator()<decltype(it)>(
                                    sd::next<pl>(it, i),
                                    sd::next<pl>(it, ij))
                                ) {
                                        f__swap.template 
                                        operator()<decltype(it)>(
                                                sd::next<pl>(it, i),
                                                sd::next<pl>(it, ij)
                                        );
                               }
                               }
                        }
                }, ctx);
                }}
        } 
        else {
                for (I i{0}; i < n; ++i) {
                for (I j{0}; j < n - i - I{1}; ++j) {

                        if constexpr (
                                sd::policy_list_is_defined_v
                                <sd::use_swap_if, pl>
                        ) {

                                const bool do_swap { 
                                        !f__less.template 
                                        operator()<decltype(it)>(
                                        sd::next<pl>(it, j),
                                        sd::next<pl>(it, j + 1)
                                )};

                                f__swap_if.template 
                                operator()<decltype(it)>(
                                        do_swap,
                                        sd::next<pl>(it, j),
                                        sd::next<pl>(it, j + 1)
                                );

                        } 
                        else {
                                if (!f__less.template 
                                    operator()<decltype(it)>(
                                    sd::next<pl>(it, j),
                                    sd::next<pl>(it, j + 1)
                                )) {
                                        f__swap.template 
                                        operator()<decltype(it)>(
                                                sd::next<pl>(it, j),
                                                sd::next<pl>(it, j + 1)
                                        );
                                }
                        }

                }}
        }

}


#endif // __INCLUDE__KDTREE_SORT_HPP

