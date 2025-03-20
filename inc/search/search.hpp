#ifndef __INCLUDE__KDTREE_SEARCH_HPP
#define __INCLUDE__KDTREE_SEARCH_HPP

#include "output.hpp"
#include "signature.hpp" 

#include "../impl/concept.hpp"
#include "../impl/context.hpp"
#include "../impl/policy.hpp"

namespace sd::kdtree {

template <sd::integral auto k, sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto
search(sd::iterator auto it, sd::iterator auto q, sd::iterator auto out,
       sd::arithmet auto r_min, sd::arithmet auto r_max)
-> void
requires
(
        sd::kdtree::valid_search_parameters<
                decltype( it),
                decltype(  q),
                decltype(out)
        >
);

} // namespace sd::kdtree

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

template <sd::integral auto k, sd::policy_list pl>
constexpr inline auto
sd::kdtree::search(sd::iterator auto    it,
                   sd::iterator auto     q,
                   sd::iterator auto   out,
                   sd::arithmet auto r_min,
                   sd::arithmet auto r_max)
-> void
requires
(
        sd::kdtree::valid_search_parameters<
                decltype( it),
                decltype(  q),
                decltype(out)
        >
)
{

        if constexpr (k == 0) {
                return;
        }
        if constexpr (k == 1) {

        }

}

#endif // __INCLUDE__KDTREE_SEARCH_HPP
