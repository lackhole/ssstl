//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_SIZED_RANGE_HPP_
#define LSD_RANGES_SIZED_RANGE_HPP_

#include <type_traits>

#include "lsd/__ranges/range.h"
#include "lsd/__ranges/size.h"
#include "lsd/__type_traits/is_invocable.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename T, bool = range<T>::value>
struct sized_range_impl : std::false_type {};

template<typename T>
struct sized_range_impl<T, true> : is_invocable<decltype(ranges::size), T&> {};

} // namespace detail

template<typename T>
struct sized_range : detail::sized_range_impl<T> {};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_SIZED_RANGE_HPP_
