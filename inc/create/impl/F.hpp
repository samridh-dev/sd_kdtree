#ifndef __INCLUDE__KDTREE_CREATE_IMPL_F_HPP
#define __INCLUDE__KDTREE_CREATE_IMPL_F_HPP

#include "../../impl/concept.hpp"

namespace sd::kdtree::impl::create {

template <sd::integral T>
constexpr inline auto 
F(const T n) 
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

template <sd::integral T>
constexpr inline auto 
sd::kdtree::impl::create::F(const T n)
noexcept -> T
{
        return (T{1} << n) - T{1};
}

#endif // __INCLUDE__KDTREE_CREATE_IMPL_F_HPP
