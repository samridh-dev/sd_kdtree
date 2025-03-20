#ifndef __INCLUDE__KDTREE_SEARCH_IMPL_KNN_HPP
#define __INCLUDE__KDTREE_SEARCH_IMPL_KNN_HPP

#include "output.hpp" 
#include "signature.hpp" 

#include "../impl/concept.hpp"
#include "../impl/context.hpp"
#include "../impl/policy.hpp"
#include "../impl/deref.hpp"
#include "../impl/size.hpp"
namespace sd::kdtree {

template <sd::integral auto k, sd::policy_list pl = sd::policy_list_t<>>
constexpr inline auto
knn(sd::iterator auto    it,
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
#include "../sort/network.hpp"
#include "../sort/traits.hpp"

template <sd::policy_list pl>
struct knn__f__less : sd::f__less {

        template <sd::iterator iter>
        constexpr inline auto
        operator()(iter i, iter j)
        const -> bool
        {
                return (*i).dst() < (*j).dst();
        }

};

template <sd::policy_list pl>
struct knn__f__swap : sd::f__swap {

        template <sd::iterator iter>
        constexpr inline auto
        operator()(iter i, iter j)
        const -> void
        {
                const auto tmp { *i };
                *i = *j;
                *j = tmp;
        }

};

template <sd::policy_list pl>
struct knn__f__swap_if : sd::f__swap_if {

        template <sd::iterator iter>
        constexpr inline auto
        operator()(const bool do_swap, iter i, iter j)
        const -> void
        {

                const auto tmp_ { (*i) };
                (*i) = (do_swap) * (*j) + (!do_swap) * (*i);
                (*j) = (do_swap) * tmp_ + (!do_swap) * (*j);

        }

};


struct knn__f__process {

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

                (void) n;

                using I = std::remove_cvref_t<decltype(out->idx())>;
                using T = std::remove_cvref_t<decltype(out->dst())>;

                const I dim {
                        static_cast<I>(sd::size<pl>(it)) 
                };

                const T dst {
                        sd::kdtree::impl::euclidian::dist2<pl>(
                                q, I{0}, it, idx, dim
                        )
                };

                auto worst {
                        sd::next<pl>(out, k-1) 
                };

                if ((dst > r_min) && (dst < (*worst).dst())) {

                        (*worst).idx(idx);
                        (*worst).dst(dst);

                        for (auto i{out}; i < sd::next<pl>(out, k); ++i) {

                                const bool less {
                                        knn__f__less<pl>{}(worst, i)
                                };

                                knn__f__swap_if<pl>{}(less, worst, i);

                        }

                        r_max = (*worst).dst();

                }
                
        }

};

#include "impl/traverse.hpp"

template <sd::integral auto k, sd::policy_list pl>
constexpr inline auto
sd::kdtree::knn(sd::iterator auto    it, 
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
        <k, pl, knn__f__process, f__split_dim_round_robin>
        (it, n, q, out, r_min, r_max);
}

#endif // __INCLUDE__KDTREE_SEARCH_IMPL_KNN_HPP
