#ifndef __INCLUDE__SD_TRAITS_HPP
#define __INCLUDE__SD_TRAITS_HPP

#include "policy.hpp"
#include <type_traits>
#include <concepts>
#include <thread>
#include <vector>

namespace sd {

struct f__for {};
struct f__new {};
struct f__del {};

template <typename F>
concept f__for_is_valid = std::is_base_of_v<f__for, F> &&
        requires(F f, int beg, int end, int kernel, int ctx) 
        {
                { 
                        f.template operator()<int, int>(beg, end, kernel, ctx) 
                } -> std::same_as<void>;
        };

template <typename F>
concept f__new_is_valid = std::is_base_of_v<f__new, F> &&
        requires(F f, int n, int ctx) 
        {
                { 
                        f.template operator()<int, int>(n, ctx) 
                } -> std::same_as<int*>;
        };

template <typename F>
concept f__del_is_valid = std::is_base_of_v<f__del, F> &&
        requires(F f, int* ptr, int ctx) 
        {
                {
                        f.template operator()<int, int>(ptr, ctx) 
                } -> std::same_as<void>;
        };

#ifdef _OPENMP
#include <omp.h>
#endif

struct f__for__default : f__for {
        template <typename f__kernel>
        constexpr inline void 
        operator()(sd::integral auto beg,
                   sd::integral auto end, 
                   f__kernel kernel, 
                   auto ctx) const 
        {
                (void) ctx;

                #ifdef _OPENMP
                #pragma omp parallel for
                #endif
                for (auto i = beg; i < end; ++i) {
                        kernel(i);
                }

        }
};

struct f__new__default : f__new {
        template <typename T>
        [[nodiscard]] constexpr inline T* 
        operator()(const sd::integral auto n, auto ctx) const 
        {
                (void) ctx;
                return new T[n];
        }
};

struct f__del__default : f__del {
        template <typename T>
        constexpr inline void 
        operator()(T* ptr, auto ctx) const 
        {
                (void) ctx;
                delete[] ptr;
        }
};

template <sd::policy_list pl>
consteval f__for_is_valid auto 
get_f__for(void) 
{
        return sd::policy_list_find_t<f__for, f__for__default, pl>{};
}

template <sd::policy_list pl>
consteval f__new_is_valid auto 
get_f__new(void) 
{
        return sd::policy_list_find_t<f__new, f__new__default, pl>{};
}

template <sd::policy_list pl>
consteval f__del_is_valid auto 
get_f__del(void) 
{
        return sd::policy_list_find_t<f__del, f__del__default, pl>{};
}

} // namespace sd

#endif // __INCLUDE__SD_TRAITS_HPP
