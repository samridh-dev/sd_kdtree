#ifndef __INCLUDE__KDTREE_IMPL_CLZ_HPP
#define __INCLUDE__KDTREE_IMPL_CLZ_HPP

#include "concept.hpp"

namespace sd::kdtree::impl {

template <sd::integral T>
[[nodiscard]] constexpr inline auto 
clz(const T n) 
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

#include <limits>
#include <bit>

template <sd::integral T>
[[nodiscard]] constexpr inline auto 
sd::kdtree::impl::clz(const T n) 
noexcept -> T
{

        return static_cast<T>(
                std::countl_zero(static_cast<std::make_unsigned_t<T>>(n))
        );

}

#endif // __INCLUDE__KDTREE_IMPL_CLZ_HPP
