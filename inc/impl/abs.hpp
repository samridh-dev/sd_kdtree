#ifndef __INCLUDE__SD_ABS_HPP
#define __INCLUDE__SD_ABS_HPP

namespace sd::kdtree::impl {

[[nodiscard]] constexpr inline auto
abs(sd::arithmet auto n) 
noexcept -> decltype(n)
{

        if constexpr (sd::integral<decltype(n)>) {
                return n < 0 ? -n : n;
        }

        else if constexpr (sd::floating<decltype(n)>) {
                return n < 0 ? -n : n;
        }

}

} // namespace sd::kdtree::impl

#endif // __INCLUDE__SD_ABS_HPP
