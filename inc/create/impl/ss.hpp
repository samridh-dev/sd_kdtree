#ifndef __INCLUDE__KDTREE_CREATE_IMPL_SS_HPP
#define __INCLUDE__KDTREE_CREATE_IMPL_SS_HPP

#include "../../impl/concept.hpp"

namespace sd::kdtree::impl::create {

template <std::integral T>
constexpr inline auto 
ss(const T s, const T n, const T L)
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

#include "../../impl/lr_child.hpp"
#include "../../impl/bsr.hpp"
#include "../../impl/min.hpp"

template <std::integral T>
constexpr inline auto 
sd::kdtree::impl::create::ss(const T s, const T n, const T L) 
noexcept -> T 
{

        if (s >= n) return 0;

        const T l         { kdtree::impl::bsr(s+1)    };
        const T fllc_s    { ~((~s) << (L - l - T{1})) };

        const T nn_fllc_s {
                min((n - fllc_s) * (n > fllc_s), T{1} << (L - l - T{1}))
        };

        return (T{1} << (L - l - T{1})) - T{1} + nn_fllc_s;

}

#endif // KDTREE_CREATE_IMPL_SS_HPP
