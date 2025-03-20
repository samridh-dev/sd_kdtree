#ifndef __INCLUDE__SD_POLICY_HPP
#define __INCLUDE__SD_POLICY_HPP

#include <type_traits>

namespace sd {

template <typename... T>
struct policy_list_t {};

template <typename T>
struct is_policy_list : std::false_type {};

template <typename... T>
struct is_policy_list<policy_list_t<T...>> : std::true_type {};

template <typename T>
inline constexpr bool is_policy_list_v = is_policy_list<T>::value;

template <typename T>
concept policy_list = is_policy_list_v<T>;

template <policy_list pl>
struct policy_list_get_size;

template <typename policy, policy_list pl>
struct policy_list_append;

template <typename policy, typename default_policy, policy_list pl>
struct policy_list_find;

template <typename policy, policy_list pl>
using policy_list_append_t = typename policy_list_append<policy, pl>::type; 

template <typename policy, typename default_policy, policy_list pl>
using policy_list_find_t = typename policy_list_find<policy, default_policy,
                                                       pl>::type; 

template <typename policy, policy_list pl>
constexpr bool 
policy_list_is_defined_v = !std::is_same_v<
        policy_list_find_t<policy, void, pl>, void
>;

} // namespace sd

namespace sd {

template <typename... policies>
struct policy_list_get_size<policy_list_t<policies...>>
    : std::integral_constant<std::size_t, sizeof...(policies)> {};

template <typename policy, typename... policies>
struct policy_list_append<policy, policy_list_t<policies...>> {
    using type = policy_list_t<policies..., policy>;
};

template <typename policy, typename default_policy, typename... policies>
struct policy_list_find_impl;

template <typename policy, typename default_policy>
struct policy_list_find_impl<policy, default_policy> {
    using type = default_policy;
};

template <typename policy, typename default_policy, typename head, typename... tail>
struct policy_list_find_impl_helper {
    // Call the outer interface with the correct parameter order.
    using nested = typename policy_list_find<policy, default_policy, head>::type;
    using type = std::conditional_t<
        !std::is_same_v<nested, default_policy>,
        nested,
        typename policy_list_find_impl<policy, default_policy, tail...>::type
    >;
};

template <typename policy, typename default_policy, typename head, typename... tail>
struct policy_list_find_impl_non_list {
    using type = std::conditional_t<
        std::is_base_of_v<policy, head>,
        head,
        typename policy_list_find_impl<policy, default_policy, tail...>::type
    >;
};

template <typename policy, typename default_policy, typename head, typename... tail>
struct policy_list_find_impl<policy, default_policy, head, tail...>
    : std::conditional_t<
          is_policy_list_v<head>,
          policy_list_find_impl_helper<policy, default_policy, head, tail...>,
          policy_list_find_impl_non_list<policy, default_policy, head, tail...>
      > {};

// Outer interface for policy_list_find.
// Parameter order: <target, default_policy, policy_list>.
template <typename policy, typename default_policy, policy_list pl>
struct policy_list_find;

template <typename policy, typename default_policy, typename... policies>
struct policy_list_find<policy, default_policy, policy_list_t<policies...>>
    : policy_list_find_impl<policy, default_policy, policies...> {};

} // namespace sd

#endif // __INCLUDE__SD_POLICY_HPP
