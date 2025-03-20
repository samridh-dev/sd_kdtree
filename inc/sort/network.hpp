#ifndef __INCLUDE__KDTREE_SORT_NETWORK_HPP
#define __INCLUDE__KDTREE_SORT_NETWORK_HPP

#include "../impl/concept.hpp"
#include "../impl/context.hpp"
#include "../impl/policy.hpp"

namespace sd {

template <std::integral auto n, sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto 
sort__network(sd::iterator auto it) 
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

#include "traits.hpp"

template <std::integral auto n, sd::policy_list pl>
constexpr inline auto 
sd::sort__network(sd::iterator auto it) 
-> void
{

        constexpr auto f__less    { sd::get_f__less<pl>()    };
        constexpr auto f__swap    { sd::get_f__swap<pl>()    };
        constexpr auto f__swap_if { sd::get_f__swap_if<pl>() };

        auto op { [&](sd::integral auto i, sd::integral auto j)
        {

                if constexpr (
                        sd::policy_list_is_defined_v<sd::use_swap_if, pl>
                ) {
                        const bool do_swap { 
                                !f__less.template operator()<decltype(it)>(
                                        std::next(it, i),
                                        std::next(it, j)
                                )
                        };

                        f__swap_if.template operator()<decltype(it)>( 
                                do_swap,
                                std::next(it, i),
                                std::next(it, j)
                        );

                } 
                else {

                        if (
                                !f__less.template operator()<decltype(it)>(
                                        std::next(it, i),
                                        std::next(it, j)
                                )
                        ) {
                                 f__swap.template operator()<decltype(it)>(
                                         std::next(it, i),
                                         std::next(it, j)
                                 );
                        }

                }

        }};

        if constexpr (n == 0) {
                return;
        }

        if constexpr (n == 1) {
                return;
        }

        if constexpr (n == 2) {
                op( 0, 1);
                return;
        }

        if constexpr (n == 3) {
                op( 0, 2);
                op( 0, 1);
                op( 1, 2);
                return;
        }

        if constexpr (n == 4) {
                op( 0, 3);
                op( 1, 2);
                op( 0, 1);
                op( 2, 3);
                op( 1, 2);
                return;
        }

        if constexpr (n == 5) {
                op( 0, 4);
                op( 0, 2);
                op( 1, 4);
                op( 1, 3);
                op( 2, 4);
                op( 0, 1);
                op( 2, 3);
                op( 1, 2);
                op( 3, 4);
                return;
        }

        if constexpr (n == 6) {
                op( 0, 3);
                op( 1, 4);
                op( 2, 5);
                op( 0, 2);
                op( 3, 5);
                op( 1, 3);
                op( 2, 4);
                op( 0, 1);
                op( 2, 3);
                op( 4, 5);
                op( 1, 2);
                op( 3, 4);
                return;
        }

        if constexpr (n == 7) {
                op( 0, 6);
                op( 1, 5);
                op( 2, 3);
                op( 0, 2);
                op( 1, 4);
                op( 3, 6);
                op( 0, 1);
                op( 3, 5);
                op( 4, 6);
                op( 1, 3);
                op( 2, 4);
                op( 5, 6);
                op( 2, 3);
                op( 4, 5);
                op( 1, 2);
                op( 3, 4);
                return;
        }

        if constexpr (n == 8) {
                op( 0, 5);
                op( 1, 3);
                op( 2, 7);
                op( 4, 6);
                op( 0, 2);
                op( 1, 4);
                op( 3, 6);
                op( 5, 7);
                op( 0, 1);
                op( 2, 4);
                op( 3, 5);
                op( 6, 7);
                op( 1, 3);
                op( 4, 6);
                op( 2, 3);
                op( 4, 5);
                op( 1, 2);
                op( 3, 4);
                op( 5, 6);
                return;
        }

        if constexpr (n == 9) {
                op( 0, 8);
                op( 1, 6);
                op( 2, 5);
                op( 4, 7);
                op( 0, 4);
                op( 2, 6);
                op( 3, 7);
                op( 5, 8);
                op( 0, 2);
                op( 1, 5);
                op( 3, 4);
                op( 6, 8);
                op( 1, 3);
                op( 4, 6);
                op( 5, 7);
                op( 0, 1);
                op( 2, 4);
                op( 3, 5);
                op( 7, 8);
                op( 2, 3);
                op( 4, 5);
                op( 6, 7);
                op( 1, 2);
                op( 3, 4);
                op( 5, 6);
                return;
        }

        if constexpr (n == 10) {
                op( 0, 7);
                op( 1, 6);
                op( 2, 9);
                op( 3, 8);
                op( 4, 5);
                op( 0, 3);
                op( 1, 4);
                op( 5, 8);
                op( 6, 9);
                op( 0, 2);
                op( 3, 6);
                op( 7, 9);
                op( 0, 1);
                op( 2, 4);
                op( 5, 7);
                op( 8, 9);
                op( 1, 3);
                op( 2, 5);
                op( 4, 7);
                op( 6, 8);
                op( 1, 2);
                op( 3, 5);
                op( 4, 6);
                op( 7, 8);
                op( 2, 3);
                op( 4, 5);
                op( 6, 7);
                op( 3, 4);
                op( 5, 6);
                return;
        }

        if constexpr (n == 11) {
                op( 0,10);
                op( 1, 7);
                op( 2, 9);
                op( 3, 8);
                op( 0, 3);
                op( 2, 6);
                op( 4, 9);
                op( 5, 7);
                op( 8,10);
                op( 0, 2);
                op( 1, 5);
                op( 4, 8);
                op( 6, 9);
                op( 7,10);
                op( 1, 4);
                op( 2, 7);
                op( 3, 6);
                op( 5, 8);
                op( 9,10);
                op( 0, 1);
                op( 2, 4);
                op( 3, 5);
                op( 6, 8);
                op( 7, 9);
                op( 1, 3);
                op( 4, 6);
                op( 5, 7);
                op( 8, 9);
                op( 2, 3);
                op( 4, 5);
                op( 6, 7);
                op( 1, 2);
                op( 3, 4);
                op( 5, 6);
                op( 7, 8);
                return;
        }

        if constexpr (n == 12) {
                op( 0,11);
                op( 1,10);
                op( 2, 9);
                op( 3, 8);
                op( 4, 7);
                op( 5, 6);
                op( 0, 5);
                op( 1, 3);
                op( 6,11);
                op( 8,10);
                op( 0, 2);
                op( 3, 7);
                op( 4, 8);
                op( 9,11);
                op( 1, 4);
                op( 2, 5);
                op( 6, 9);
                op( 7,10);
                op( 0, 1);
                op( 2, 4);
                op( 3, 6);
                op( 5, 8);
                op( 7, 9);
                op(10,11);
                op( 1, 3);
                op( 4, 7);
                op( 5, 6);
                op( 8,10);
                op( 1, 2);
                op( 3, 5);
                op( 6, 8);
                op( 9,10);
                op( 2, 3);
                op( 4, 5);
                op( 6, 7);
                op( 8, 9);
                op( 3, 4);
                op( 5, 6);
                op( 7, 8);
                return;
        }

        if constexpr (n == 13) {
                op( 0, 8);
                op( 1, 7);
                op( 2, 9);
                op( 3,10);
                op( 4,12);
                op( 5,11);
                op( 0, 2);
                op( 3, 4);
                op( 6,11);
                op( 8, 9);
                op(10,12);
                op( 0, 3);
                op( 1, 6);
                op( 2,10);
                op( 4, 8);
                op( 7,11);
                op( 9,12);
                op( 5, 8);
                op( 6, 9);
                op( 7,10);
                op(11,12);
                op( 1, 5);
                op( 3, 6);
                op( 4, 7);
                op( 8,10);
                op( 9,11);
                op( 0, 1);
                op( 2, 5);
                op( 8, 9);
                op(10,11);
                op( 1, 3);
                op( 2, 4);
                op( 5, 7);
                op( 6, 8);
                op( 9,10);
                op( 1, 2);
                op( 3, 4);
                op( 5, 6);
                op( 7, 8);
                op( 2, 3);
                op( 4, 5);
                op( 6, 7);
                op( 8, 9);
                op( 3, 4);
                op( 5, 6);
                return;
        }

        if constexpr (n == 14) {
                op( 0,13);
                op( 1,12);
                op( 2,11);
                op( 3,10);
                op( 4, 9);
                op( 5, 8);
                op( 6, 7);
                op( 0, 6);
                op( 1, 5);
                op( 2, 4);
                op( 7,13);
                op( 8,12);
                op( 9,11);
                op( 0, 2);
                op( 3, 9);
                op( 4,10);
                op(11,13);
                op( 1, 3);
                op( 2, 5);
                op( 4, 7);
                op( 6, 9);
                op( 8,11);
                op(10,12);
                op( 0, 1);
                op( 3, 6);
                op( 4, 8);
                op( 5, 9);
                op( 7,10);
                op(12,13);
                op( 1, 3);
                op( 2, 4);
                op( 5, 8);
                op( 9,11);
                op(10,12);
                op( 1, 2);
                op( 3, 4);
                op( 5, 7);
                op( 6, 8);
                op( 9,10);
                op(11,12);
                op( 2, 3);
                op( 4, 6);
                op( 7, 9);
                op(10,11);
                op( 4, 5);
                op( 6, 7);
                op( 8, 9);
                op( 3, 4);
                op( 5, 6);
                op( 7, 8);
                op( 9,10);
                return;
        }

        if constexpr (n == 15) {
                op( 0,14);
                op( 1,13);
                op( 2,12);
                op( 3,11);
                op( 5, 8);
                op( 6,10);
                op( 7, 9);
                op( 0, 5);
                op( 1, 7);
                op( 2, 6);
                op( 4,11);
                op( 8,14);
                op( 9,13);
                op(10,12);
                op( 0, 2);
                op( 3, 9);
                op( 4, 7);
                op( 5,10);
                op( 6, 8);
                op(11,13);
                op(12,14);
                op( 1, 5);
                op( 2, 4);
                op( 3, 6);
                op( 7,10);
                op( 8,11);
                op( 9,12);
                op(13,14);
                op( 0, 2);
                op( 1, 3);
                op( 4, 9);
                op( 5, 8);
                op( 6, 7);
                op(10,12);
                op(11,13);
                op( 0, 1);
                op( 2, 3);
                op( 4, 6);
                op( 7, 9);
                op(10,11);
                op(12,13);
                op( 1, 2);
                op( 3, 5);
                op( 8,10);
                op(11,12);
                op( 3, 4);
                op( 5, 6);
                op( 7, 8);
                op( 9,10);
                op( 2, 3);
                op( 4, 5);
                op( 6, 7);
                op( 8, 9);
                op(10,11);
                op( 5, 6);
                op( 7, 8);
                return;
        }

        if constexpr (n == 16) {
                op( 0,15);
                op( 1,14);
                op( 2,13);
                op( 3,12);
                op( 4,11);
                op( 5,10);
                op( 6, 9);
                op( 7, 8);
                op( 0, 4);
                op( 1, 6);
                op( 2, 7);
                op( 3, 5);
                op( 8,13);
                op( 9,14);
                op(10,12);
                op(11,15);
                op( 0, 3);
                op( 1, 2);
                op( 4,10);
                op( 5,11);
                op( 6, 8);
                op( 7, 9);
                op(12,15);
                op(13,14);
                op( 0, 1);
                op( 2, 5);
                op( 3, 6);
                op( 4, 7);
                op( 8,11);
                op( 9,12);
                op(10,13);
                op(14,15);
                op( 1, 3);
                op( 2, 4);
                op( 5,10);
                op( 6, 9);
                op( 7, 8);
                op(11,13);
                op(12,14);
                op( 1, 2);
                op( 3, 4);
                op( 5, 7);
                op( 8,10);
                op(11,12);
                op(13,14);
                op( 2, 3);
                op( 4, 6);
                op( 9,11);
                op(12,13);
                op( 4, 5);
                op( 6, 7);
                op( 8, 9);
                op(10,11);
                op( 3, 4);
                op( 5, 6);
                op( 7, 8);
                op( 9,10);
                op(11,12);
                op( 6, 7);
                op( 8, 9);
                return;
        }
        else {
        }

}


#endif // __INCLUDE__KDTREE_SORT_NETWORK_HPP
