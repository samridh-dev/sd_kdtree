#ifndef __INCLUDE__KDTREE_CREATE_IMPL_SB_HPP
#define __INCLUDE__KDTREE_CREATE_IMPL_SB_HPP

#include "../../impl/concept.hpp"

namespace sd::kdtree::impl::create {

template <sd::integral T>
constexpr inline auto 
sb(const T s, const T n, const T L)
noexcept -> T;

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

#include "../../impl/bsr.hpp"
#include "../../impl/min.hpp"

#include "ss.hpp"
#include "F.hpp"

template <sd::integral T>
constexpr inline auto 
sd::kdtree::impl::create::sb(const T s, const T n, const T L) 
noexcept -> T
{

        const T l       { kdtree::impl::bsr(s+1)   };
        const T nls_s   { s - ((T{1} << l) - T{1}) };

        const T sb_s_l  { 
                (T{1} << l) - T{1}
                + nls_s * ((T{1} << (L - l - T{1})) - T{1})
                + min(nls_s * (T{1} << (L - l - T{1})),
                      n - ((T{1} << (L - T{1})) - T{1}))
        };

        return sb_s_l;

}

#endif // KDTREE_CREATE_IMPL_SB_HPP
