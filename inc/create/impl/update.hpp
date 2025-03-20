#ifndef __INCLUDE__KDTREE_CREATE_IMPL_UPDATE_HPP
#define __INCLUDE__KDTREE_CREATE_IMPL_UPDATE_HPP

#include "../../impl/concept.hpp"
#include "../../impl/context.hpp"
#include "../../impl/policy.hpp"

namespace sd::kdtree::impl::create {

template <sd::policy_list pl>
constexpr inline auto
update(sd::iterator auto tag, const sd::integral auto n,
       const sd::integral auto d, sd::context auto ctx) 
-> void;

} // namespace sd::kdtree::impl::create


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

#include "../../impl/traits.hpp"
#include "../../impl/bsr.hpp"
#include "../../impl/lr_child.hpp"

#include "ss.hpp"
#include "sb.hpp"
#include "F.hpp"

template <sd::policy_list pl>
constexpr inline auto
sd::kdtree::impl::create::update(
        sd::iterator auto tag, const sd::integral auto n,
        const sd::integral auto d, sd::context auto ctx
) 
-> void
{

        constexpr auto f__for { sd::get_f__for<pl>() };

        const auto L { sd::kdtree::impl::bsr(n) + 1 };

        f__for(decltype(n){F(d)}, n, [=](decltype(n) i) {

                auto& s { sd::deref<pl>(tag, i) };

                const auto p { 
                        sd::kdtree::impl::create::sb(s, n, L) +
                        sd::kdtree::impl::create::ss(impl::l_child(s), n, L) 
                };
              
#if 0
                if (i < p) {
                        s = impl::l_child(s);
                } 
                else if (i > p)  {
                        s = impl::r_child(s);
                }
                else {
                }
#else
                #if 0
                        const decltype(n) b = ((i == p) << 1) | (i > p);
                        s += !(b >> 1) * ( (2 * s + 1 + b) - (s) );
                #else
                        const bool b1 { i != p };
                        const bool b2 { i  > p };
                        s += b1 * ( kdtree::impl::l_child(s) + b2 - s );
                #endif
#endif

        }, ctx);

}

#endif // KDTREE_CREATE_IMPL_UPDATE_HPP
