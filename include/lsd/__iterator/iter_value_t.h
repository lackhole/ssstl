//
// Created by cosge on 2023-12-24.
//

#ifndef LSD_ITERATOR_ITER_VALUE_T_HPP_
#define LSD_ITERATOR_ITER_VALUE_T_HPP_

#include "lsd/__iterator/iterator_traits/cxx20_iterator_traits.h"
#include "lsd/__iterator/indirectly_readable_traits.h"
#include "lsd/__type_traits/has_typename_value_type.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

template<
    typename T,
    bool = is_primary_iterator_traits< cxx20_iterator_traits< remove_cvref_t<T> > >::value,
    bool = has_typename_value_type<indirectly_readable_traits<remove_cvref_t<T>>>::value
>
struct iter_value_impl {};

template<typename T, bool v>
struct iter_value_impl<T, false, v> {
  using type = typename cxx20_iterator_traits<remove_cvref_t<T>>::value_type;
};

template<typename T>
struct iter_value_impl<T, true, true> {
  using type = typename indirectly_readable_traits<remove_cvref_t<T>>::value_type;
};

} // namespace detail

template<typename T>
struct iter_value : detail::iter_value_impl<T> {};

template<typename T>
using iter_value_t = typename iter_value<T>::type;

} // namespace lsd

#endif // LSD_ITERATOR_ITER_VALUE_T_HPP_
