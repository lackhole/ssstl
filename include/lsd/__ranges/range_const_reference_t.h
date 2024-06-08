//
// Created by yonggyulee on 2024/01/27.
//

#ifndef LSD_RANGES_RANGE_CONST_REFERENCE_T_H_
#define LSD_RANGES_RANGE_CONST_REFERENCE_T_H_

#include "lsd/__iterator/iter_const_reference_t.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/range.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename I, bool = has_typename_type<iter_const_reference<I>>::value /* true */>
struct range_const_reference_impl_2 {
  using type = iter_const_reference_t<I>;
};
template<typename I>
struct range_const_reference_impl_2<I, false> {};

template<typename R, bool = range<R>::value /* true */>
struct range_const_reference_impl : range_const_reference_impl_2<iterator_t<R>> {};
template<typename R>
struct range_const_reference_impl<R, false> {};

} // namespace ranges

template<typename R>
struct range_const_reference : detail::range_const_reference_impl<R> {};

template<typename R>
using range_const_reference_t = typename range_const_reference<R>::type;

} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_RANGE_CONST_REFERENCE_T_H_
