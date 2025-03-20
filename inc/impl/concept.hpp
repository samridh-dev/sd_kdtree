#ifndef __INCLUDE__SD_CONCEPT_HPP
#define __INCLUDE__SD_CONCEPT_HPP

#include <concepts>
#include <iterator>
#include <type_traits>

namespace sd {

template <typename T>
concept iterator = std::forward_iterator<T>;

template <typename T> 
concept integral = std::integral<T>;

template <typename T> 
concept floating = std::floating_point<T>;

template <typename T> 
concept arithmet = std::integral<T> || std::floating_point<T>;

} // namespace sd

#endif // __INCLUDE__KDTREE_CONCEPT_HPP
