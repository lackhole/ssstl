//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_FORWARD_RANGE_HPP_
#define LSD_RANGES_FORWARD_RANGE_HPP_

#include <type_traits>

#include "lsd/__iterator/forward_iterator.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename T, bool = has_typename_type<iterator<T>>::value>
struct forward_range_impl : std::false_type {};

template<typename T>
struct forward_range_impl<T, true>
    : conjunction<
        input_range<T>,
        forward_iterator<iterator_t<T>>
      > {};

} // namespace detail

template<typename T>
struct forward_range : detail::forward_range_impl<T> {};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_FORWARD_RANGE_HPP_
