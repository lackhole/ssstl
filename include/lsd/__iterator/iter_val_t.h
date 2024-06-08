//
// Created by cosge on 2024-01-13.
//

#ifndef LSD_ITERATOR_ITER_VAL_T_H_
#define LSD_ITERATOR_ITER_VAL_T_H_

#include "lsd/__iterator/iterator_traits/cxx20_iterator_traits.h"
#include "lsd/__type_traits/has_typename_value_type.h"

namespace lsd {
namespace detail {

template<typename I, bool = has_typename_value_type< cxx20_iterator_traits<I> >::value /* true */>
struct iter_val_impl {
  using type = typename cxx20_iterator_traits<I>::value_type;
};
template<typename I>
struct iter_val_impl<I, false> {};

} // namespace detail

template<typename T>
struct iter_val : detail::iter_val_impl<T> {};

template<typename T>
using iter_val_t = typename iter_val<T>::type;

} // namespace lsd

#endif // LSD_ITERATOR_ITER_VAL_T_H_
