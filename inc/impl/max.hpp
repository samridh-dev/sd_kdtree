#ifndef __INCLUDE__KDTREE_IMPL_MAX_HPP
#define __INCLUDE__KDTREE_IMPL_MAX_HPP

#include "concept.hpp"

namespace sd::kdtree::impl {

template <typename T>
constexpr inline auto 
max(const T a, const T b)
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

template <typename T>
constexpr inline auto 
sd::kdtree::impl::max(const T a, const T b)
noexcept -> T 
{
        if constexpr ( 
                requires { { (a > b) * a + (!(a > b)) * b } 
                -> std::convertible_to<T>; 
        }) {
                return (a > b) * a + (!(a > b)) * b;
        } 
        else {
                return a > b ? a : b;
        }
}


#endif // __INCLUDE__KDTREE_IMPL_LR_CHILD_HPP
