#ifndef __INCLUDE__KDTREE_SEARCH_IMPL_NN_HPP
#define __INCLUDE__KDTREE_SEARCH_IMPL_NN_HPP

#include "output.hpp" 
#include "signature.hpp" 

#include "../impl/concept.hpp"
#include "../impl/context.hpp"
#include "../impl/policy.hpp"
#include "../impl/deref.hpp"
#include "../impl/size.hpp"

namespace sd::kdtree {

template <sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto
nn(sd::iterator auto    it,
   sd::integral auto     n,
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

#include "../impl/dist2.hpp"

struct nn__f__process {

        template <std::integral auto k, sd::policy_list pl>
        constexpr inline auto
        operator()(sd::iterator auto     it,
                   sd::integral auto      n,
                   sd::iterator auto      q,
                   sd::iterator auto    out,
                   sd::arithmet auto& r_min,
                   sd::arithmet auto& r_max,
                   sd::integral auto   idx)
        noexcept -> void 
        {

                (void) k;
                (void) n;

                using I = std::remove_cvref_t<decltype(out->idx())>;
                using T = std::remove_cvref_t<decltype(out->dst())>;

                const I dim { // TODO : check performance
                        static_cast<I>(sd::size<pl>(it)) 
                };

                const T dst {
                        sd::kdtree::impl::euclidian::dist2<pl>(
                                q, I{0}, it, idx, dim
                        )
                };

                if ((dst > r_min) && (dst < out->dst())) {

                        out->idx(idx);
                        out->dst(dst);
                        
                        if (dst < r_max) {
                                r_max = dst;
                        }

                }
                
        }

};

#include "impl/traverse.hpp"

template <sd::policy_list pl>
constexpr inline auto
sd::kdtree::nn(sd::iterator auto    it, 
               sd::integral auto     n,
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
        sd::kdtree::impl::search::traverse
        <1, pl, nn__f__process, f__split_dim_round_robin>
        (it, n, q, out, r_min, r_max);
}

#endif // __INCLUDE__KDTREE_SEARCH_IMPL_NN_HPP
