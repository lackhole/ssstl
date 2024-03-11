//
// Created by yonggyulee on 2023/12/26.
//

#ifndef LSD_RANGES_RANDOM_ACCESS_RANGE_HPP_
#define LSD_RANGES_RANDOM_ACCESS_RANGE_HPP_

#include <type_traits>

#include "lsd/__iterator/random_access_iterator.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/bidirectional_range.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace ranges {
namespace detail {

template<
    typename T,
    bool =
        conjunction<
          bidirectional_range<T>,
          has_typename_type<iterator<T>>
        >::value
>
struct random_access_range_impl : std::false_type {};

template<typename T>
struct random_access_range_impl<T, true> : random_access_iterator<iterator_t<T>> {};

} // namespace ranges

template<typename T>
struct random_access_range : detail::random_access_range_impl<T> {};

} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_RANDOM_ACCESS_RANGE_HPP_
