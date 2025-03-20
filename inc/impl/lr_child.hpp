#ifndef __INCLUDE__KDTREE_IMPL_LR_CHILD_HPP
#define __INCLUDE__KDTREE_IMPL_LR_CHILD_HPP

#include "concept.hpp"

namespace sd::kdtree::impl {

template <sd::integral T>
constexpr inline auto 
l_child(const T n)
noexcept -> T;

template <sd::integral T>
constexpr inline auto 
r_child(const T n)
noexcept -> T;

} // namespace sd::kdtree::impl
  
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

template <sd::integral T>
constexpr inline auto 
sd::kdtree::impl::l_child(const T n) 
noexcept -> T
{
        return T{2} * n + T{1};
}

template <sd::integral T>
constexpr inline auto 
sd::kdtree::impl::r_child(const T n) 
noexcept -> T
{
        return T{2} * n + T{2};
}

#endif // __INCLUDE__KDTREE_IMPL_LR_CHILD_HPP
