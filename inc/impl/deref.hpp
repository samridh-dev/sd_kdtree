#ifndef __INCLUDE__SD_DEREF_HPP
#define __INCLUDE__SD_DEREF_HPP

#include "concept.hpp"
#include "policy.hpp"

namespace sd {

struct use_column_major_layout {};

template <sd::policy_list pl>
[[nodiscard]] constexpr inline auto
next(sd::iterator auto it, sd::integral auto i)
noexcept -> decltype(it);

template <sd::policy_list pl>
[[nodiscard]] constexpr inline auto&
deref(sd::iterator auto it, sd::integral auto i)
noexcept;

template <sd::policy_list pl>
[[nodiscard]] constexpr inline auto&
deref(sd::iterator auto it, sd::integral auto i, sd::integral auto j)
noexcept;

} // namespace sd

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

template <sd::policy_list pl>
[[nodiscard]] constexpr inline auto
sd::next(sd::iterator auto it, sd::integral auto i)
noexcept -> decltype(it)
{

        if constexpr (std::random_access_iterator<decltype(it)>) {
                using T = std::iter_difference_t<decltype(it)>;
                return (it + static_cast<T>(i));
        }

        else {
                while (i > 0) {
                        --i;
                        ++it;
                }
                return it;
        }

}

template <sd::policy_list pl>
[[nodiscard]] constexpr inline auto&
sd::deref(sd::iterator auto it, sd::integral auto i)
noexcept 
{
        return *sd::next<pl>(it, i);
}

template <sd::policy_list pl>
[[nodiscard]] constexpr inline auto&
sd::deref(sd::iterator auto it, sd::integral auto i, sd::integral auto j)
noexcept 
{

        if constexpr (
                sd::policy_list_is_defined_v<sd::use_column_major_layout, pl>
        ) {
                return sd::deref<pl>(std::begin(sd::deref<pl>(it, j)), i);
        } 
        else {
                return sd::deref<pl>(std::begin(sd::deref<pl>(it, i)), j);
        }

}

#endif // __INCLUDE__SD_DEREF_HPP
