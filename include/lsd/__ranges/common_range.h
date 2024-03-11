//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_COMMON_RANGE_HPP_
#define LSD_RANGES_COMMON_RANGE_HPP_

#include <type_traits>

#include "lsd/__concepts/same_as.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/sentinel_t.h"
#include "lsd/__ranges/range.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace ranges {
namespace detail {

template<
    typename T,
    bool =
        conjunction<
          range<T>,
          has_typename_type<iterator<T>>,
          has_typename_type<sentinel<T>>
        >::value
>
struct common_range_impl : std::false_type {};

template<typename T>
struct common_range_impl<T, true> : same_as<iterator_t<T>, sentinel_t<T>> {};

} // namespace ranges

template<typename T>
struct common_range : detail::common_range_impl<T> {};

} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_COMMON_RANGE_HPP_
