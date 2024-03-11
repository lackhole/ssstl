//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_TYPE_TRAITS_CORE_SIZE_HPP_
#define LSD_TYPE_TRAITS_CORE_SIZE_HPP_

#include <cstddef>
#include <type_traits>

#include "lsd/__type_traits/common_type.h"

namespace lsd {

template<typename C>
constexpr inline auto size(const C& c) -> decltype(c.size())
{
  return c.size();
}

template<typename T, std::size_t N>
constexpr inline std::size_t size(const T (&array)[N]) noexcept
{
  return N;
}

template<typename C>
constexpr inline auto ssize(const C& c)
    -> common_type_t<std::ptrdiff_t, std::make_signed_t<decltype(c.size())>>
{
  using R = common_type_t<std::ptrdiff_t, std::make_signed_t<decltype(c.size())>>;
  return static_cast<R>(c.size());
}

template<typename T, std::size_t N>
constexpr inline std::ptrdiff_t ssize(const T (&array)[N]) noexcept
{
  return static_cast<std::ptrdiff_t>(N);
}

} // namespace lsd

#endif // LSD_TYPE_TRAITS_CORE_SIZE_HPP_
