#ifndef __INCLUDE__KDTREE_IMPL_BSR_HPP
#define __INCLUDE__KDTREE_IMPL_BSR_HPP

#include "concept.hpp"

namespace sd::kdtree::impl {

template <sd::integral T>
[[nodiscard]] constexpr inline auto 
bsr(const T n) 
noexcept -> T;

} //namespace sd::kdtree::impl

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

#include "clz.hpp"

#include <type_traits>
#include <limits>

template <sd::integral T>
[[nodiscard]] constexpr inline auto 
sd::kdtree::impl::bsr(const T n) 
noexcept -> T
{
        constexpr auto bits { 
                std::is_signed_v<T> ? std::numeric_limits<T>::digits + 1 
                                    : std::numeric_limits<T>::digits
        };
        return T{bits} - kdtree::impl::clz<T>(n) - T{1};
}

#endif // __INCLUDE__KDTREE_IMPL_BSR_HPP
