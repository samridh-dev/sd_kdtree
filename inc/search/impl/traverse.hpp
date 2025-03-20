#ifndef __INCLUDE__KDTREE_SEARCH_IMPL_TRAVERSE_HPP
#define __INCLUDE__KDTREE_SEARCH_IMPL_TRAVERSE_HPP

namespace sd::kdtree::impl::search {

template <sd::integral auto k, sd::policy_list pl, 
          typename f__process, typename f__split_dim
          >
constexpr inline auto
traverse(sd::iterator auto   it, 
         sd::integral auto    n,
         sd::iterator auto    q,
         sd::iterator auto   out,
         sd::arithmet auto r_min,
         sd::arithmet auto r_max)
noexcept -> void;

} // namespace sd::kdtree::impl::search

///////////////////////////////////////////////////////////////////////////////
///                             IMPLEMENTATION                              ///
///////////////////////////////////////////////////////////////////////////////

struct f__split_dim {};

#include "../../impl/bsr.hpp" 
struct f__split_dim_round_robin : f__split_dim 
{
        constexpr inline auto
        operator()(sd::iterator auto  it,
                   sd::integral auto   n,
                   sd::integral auto dim,
                   sd::integral auto   s) 
        noexcept -> decltype(s)
        {
                (void) it;
                (void) n;
                const decltype(s) l { sd::kdtree::impl::bsr(s + 1) };
                const decltype(s) d { l % dim };
                return d;
        }
};

#include "../../impl/lr_child.hpp" 
#include "../../impl/size.hpp" 
#include "../../impl/abs.hpp" 

template <sd::integral auto k, sd::policy_list pl, 
          typename f__process, typename f__split_dim
          >
constexpr inline auto
sd::kdtree::impl::search::traverse(sd::iterator auto     it,
                                   sd::integral auto      n,
                                   sd::iterator auto      q,
                                   sd::iterator auto    out,
                                   sd::arithmet auto  r_min,
                                   sd::arithmet auto  r_max)
noexcept -> void
{

        using I = std::remove_cvref_t<decltype(out->idx())>;
        using T = std::remove_cvref_t<decltype(out->dst())>;

        using sd::kdtree::impl::l_child;
        using sd::kdtree::impl::r_child;
        using sd::kdtree::impl::abs;

        const I dim {
                static_cast<I>(sd::size<pl>(it)) 
        };

        I prev { static_cast<I>(-1) };
        I curr { 0 };

        while (true) {

                const I parent { (curr + 1) / I{2} - I{1} };
                const bool from_parent { (prev + 1) <= curr };

                if (curr >= n) {
                        prev = curr;
                        curr = parent;
                        continue;
                }

                if (from_parent) {
                        f__process{}.template operator()<k, pl>
                        (it, n, q, out, r_min, r_max, curr);
                }

                const I  s_dim        { f__split_dim{}(it, n, dim, curr)     };
                const T  s_pos        { sd::deref<pl>(it, curr, s_dim)       };
                const T& q_pos        { sd::deref<pl>(q, s_dim)              };
                const T  sign_dist    { q_pos - s_pos                        };
                const I  close_side   { sign_dist > T{0}                     };
                const I  close_child  { l_child(curr) + close_side           };
                const I  far_child    { r_child(curr) - close_side           }; 
                const I  far_in_range { sign_dist * sign_dist <= (r_max)     };  // TODO : add the approximation stuff

                I next;
                {

                        const auto b1 { from_parent         };
                        const auto b2 { prev == close_child };
                        const auto b3 { far_in_range        };

                        next  = parent;
                        next +=      b1 * (close_child - next);
                        next += b2 * b3 * (far_child   - next);

                }

                if (next == static_cast<I>(-1)) {
                        return;
                }

                prev = curr;
                curr = next;

        }

}

#endif // __INCLUDE__KDTREE_SEARCH_IMPL_TRAVERSE_HPP
