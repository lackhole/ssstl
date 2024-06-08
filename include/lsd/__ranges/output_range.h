//
// Created by YongGyu Lee on 3/27/24.
//

#ifndef LSD_RANGES_OUTPUT_RANGE_H_
#define LSD_RANGES_OUTPUT_RANGE_H_

#include "lsd/__ranges/iterator_t.h"
#include "lsd/__iterator/output_iterator.h"
#include "lsd/__ranges/range.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename R, typename T, bool = range<R>::value /* true */>
struct output_range_impl : std::false_type {};

template<typename R, typename T>
struct output_range_impl<R, T, true> : output_iterator<iterator_t<R>, T> {};

} // namespace detail

template<typename R, typename T>
struct output_range : detail::output_range_impl<R, T> {};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_OUTPUT_RANGE_H_
