#ifndef __INCLUDE__KDTREE_SEARCH_SIGNATURE_HPP
#define __INCLUDE__KDTREE_SEARCH_SIGNATURE_HPP

#include <concepts>
namespace sd::kdtree {

template <typename it, typename q, typename out>
concept valid_search_parameters =
#if 0
        sd::kdtree::output< std::remove_cvref_t<decltype(*std::declval<out>())> >;
#else
        std::is_same_v<void, void>;
#endif

} // namespace sd::kdtree

#endif // __INCLUDE__KDTREE_SEARCH_SIGNATURE_HPP
