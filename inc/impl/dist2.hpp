#ifndef __INCLUDE__SD_DIST2_HPP
#define __INCLUDE__SD_DIST2_HPP

#include "concept.hpp"
#include "policy.hpp"

namespace sd::kdtree::impl::euclidian {
  
template <sd::policy_list pl>
constexpr inline auto
dist2(sd::iterator auto x, sd::integral auto xi,
      sd::iterator auto y, sd::integral auto yi,
      sd::integral auto n) 
{
        using I = std::remove_cvref_t<decltype(n)>;

        constexpr bool x_1d { 
                sd::arithmet<std::iter_value_t<decltype(x)>>
        };

        constexpr bool y_1d { 
                sd::arithmet<std::iter_value_t<decltype(y)>>
        };

        if constexpr (x_1d && y_1d) {

                std::remove_cvref_t<
                        decltype((*x) - (*y))
                > v{0};

                for (I i{0}; i < n; ++i) {
                        v += (sd::deref<pl>(x, i) - sd::deref<pl>(y, i))
                           * (sd::deref<pl>(x, i) - sd::deref<pl>(y, i));
                }

                return v;

        }

        if constexpr (!x_1d && y_1d) {

                std::remove_cvref_t<
                        decltype(*std::begin(*x) - (*y))
                > v{0};

                for (I i{0}; i < n; ++i) {
                        v += (sd::deref<pl>(x, xi, i) - sd::deref<pl>(y, i))
                           * (sd::deref<pl>(x, xi, i) - sd::deref<pl>(y, i));
                }

                return v;

        }

        if constexpr (x_1d && !y_1d) {

                std::remove_cvref_t<
                        decltype((*x) - *std::begin(*y))
                > v{0};

                for (I i{0}; i < n; ++i) {
                        v += (sd::deref<pl>(x, i) - sd::deref<pl>(y, yi, i))
                           * (sd::deref<pl>(x, i) - sd::deref<pl>(y, yi, i));
                }

                return v;

        }

        if constexpr (!x_1d && !y_1d) {

                std::remove_cvref_t<
                        decltype(*std::begin(*x) - *std::begin(*y))
                > v{0};

                for (I i{0}; i < n; ++i) {
                        v += (sd::deref<pl>(x, xi, i) 
                           -  sd::deref<pl>(y, yi, i))
                           * (sd::deref<pl>(x, xi, i) 
                           -  sd::deref<pl>(y, yi, i));
                }

                return v;
        }
}

template <sd::policy_list pl>
constexpr inline auto
dist2(sd::iterator auto x, sd::iterator auto y, sd::integral auto n)
{
        return dist2<pl>(x, decltype(n){0}, y, decltype(n){0}, n);
}

} // namespace sd::kdtree::impl::euclidian


#endif // __INCLUDE__SD_DIST2_HPP
