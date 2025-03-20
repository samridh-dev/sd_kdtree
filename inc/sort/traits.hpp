#ifndef __INCLUDE__KDTREE_SORT_TRAITS_HPP
#define __INCLUDE__KDTREE_SORT_TRAITS_HPP

#include "../impl/concept.hpp"
#include "../impl/policy.hpp"
#include "../impl/deref.hpp"

namespace sd {

struct f__less {};
struct f__swap {};

struct use_swap_if {};
struct f__swap_if  {};

template <sd::policy_list pl>
struct f__less__default : f__less {

        template <sd::iterator iter>
        constexpr inline auto 
        operator()(iter i, iter j)
        const -> bool
        {
                return *i < *j;
        }

};

template <sd::policy_list pl>
struct f__swap__default : f__swap {

        template <sd::iterator iter>
        constexpr inline auto 
        operator()(iter i, iter j)
        const -> void
        {
                const auto tmp { *i };
                *i = *j;
                *j = tmp;
        }

};

template <sd::policy_list pl>
struct f__swap_if__default : f__swap_if {

        template <sd::iterator iter>
        constexpr inline auto 
        operator()(const bool do_swap, iter i, iter j)
        const -> void
        {
                if (do_swap) {
                        const auto tmp { *i };
                        *i = *j;
                        *j = tmp;
                }
        }

};

template <typename F>
concept 
f__less_is_valid = std::is_base_of_v<f__less, F> &&
        requires(F f, int* a, int* b) 
        {
                { 
                        f.template operator()<int*>(a, b) 
                } -> std::convertible_to<bool>;
        };

template <typename F>
concept 
f__swap_is_valid = std::is_base_of_v<f__swap, F> &&
        requires(F f, int* a, int* b) 
        {
                { 
                        f.template operator()<int*>(a, b) 
                } -> std::same_as<void>;
        };

template <typename F>
concept 
f__swap_if_is_valid = std::is_base_of_v<f__swap_if, F> &&
        requires(F f, int* a, int* b) 
        {
                { 
                        f.template operator()<int*>(true, a, b) 
                } -> std::same_as<void>;
        };

template <sd::policy_list pl>
consteval auto 
get_f__less(void)
-> policy_list_find_t<f__less, f__less__default<pl>, pl>
{
        return policy_list_find_t<f__less, f__less__default<pl>, pl>{};
}

template <sd::policy_list pl>
consteval auto 
get_f__swap(void)
-> policy_list_find_t<f__swap, f__swap__default<pl>, pl>
{
        return policy_list_find_t<f__swap, f__swap__default<pl>, pl>{};
}

template <sd::policy_list pl>
consteval auto 
get_f__swap_if(void)
-> policy_list_find_t<f__swap_if, f__swap_if__default<pl>, pl> 
{
        return policy_list_find_t<f__swap_if, f__swap_if__default<pl>, pl>{};
}

} // namespace sd

#endif // __INCLUDE__KDTREE_SORT_TRAITS_HPP
