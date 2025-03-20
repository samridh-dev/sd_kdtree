#ifndef __INCLUDE__SD_CONTEXT_HPP
#define __INCLUDE__SD_CONTEXT_HPP

#include <concepts>
#include <type_traits>

namespace sd {

struct context_t{};

template <typename T>
concept context = std::is_base_of_v<context_t, T>;

struct default_context : context_t {};

} // namespace sd

#endif // __INCLUDE__SD_CONTEXT_HPP
