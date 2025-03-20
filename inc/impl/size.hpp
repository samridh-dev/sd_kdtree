#ifndef __INCLUDE__SD_SIZE_HPP
#define __INCLUDE__SD_SIZE_HPP

#include <iterator>
#include <type_traits>
#include <utility>
#include <cstddef>
#include <cstdlib>

#include "concept.hpp"
#include "policy.hpp"

namespace sd {

namespace impl {

template <typename T>
concept size__has_subsize = requires (const T& x) {
        { std::size(x) } -> std::unsigned_integral;
};

} // namespace impl

template <sd::policy_list pl>
[[nodiscard]] constexpr inline auto
size(sd::iterator auto it) noexcept {
        if constexpr (impl::size__has_subsize<decltype(*it)>) {
                return std::size(*it);
        } else {
                const auto n = std::distance(std::begin(*it), std::end(*it));
                return static_cast<std::make_unsigned_t<decltype(n)>>(n);
        }
}

} // namespace sd 

#endif // __INCLUDE__SD_SIZE_HPP
