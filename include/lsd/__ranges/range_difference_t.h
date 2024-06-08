//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_RANGE_DIFFERENCE_T_H_
#define LSD_RANGES_RANGE_DIFFERENCE_T_H_

#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename I, bool = has_typename_type<iter_difference<I>>::value /* true */>
struct range_difference_impl_2 {
  using type = iter_difference_t<I>;
};
template<typename I>
struct range_difference_impl_2<I, false> {};

template<typename R, bool = has_typename_type<iterator<R>>::value /* true */>
struct range_difference_impl_1 : range_difference_impl_2<iterator_t<R>> {};
template<typename R>
struct range_difference_impl_1<R, false> {};

} // namespace ranges

template<typename R>
struct range_difference : detail::range_difference_impl_1<R> {};

template<typename R>
using range_difference_t = typename range_difference<R>::type;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_RANGE_DIFFERENCE_T_H_
