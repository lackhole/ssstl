//
// Created by yonggyulee on 2024/01/06.
//

#ifndef LSD_RANGES_RANGE_SIZE_T_HPP
#define LSD_RANGES_RANGE_SIZE_T_HPP

#include <type_traits>

#include "lsd/__ranges/size.h"
#include "lsd/__ranges/sized_range.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename R, bool = sized_range<R>::value /* true */>
struct range_size_impl {
  using type = decltype(ranges::size(std::declval<R&>()));
};

template<typename R>
struct range_size_impl<R, false> {};

} // namespace detail

template<typename R>
struct range_size : detail::range_size_impl<R> {};

template<typename R>
using range_size_t = typename range_size<R>::type;

} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_RANGE_SIZE_T_HPP
