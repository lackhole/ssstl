//
// Created by cosge on 2023-12-03.
//

#ifndef LSD_ITERATOR_ITER_DIFFERENCE_T_HPP_
#define LSD_ITERATOR_ITER_DIFFERENCE_T_HPP_

#include "lsd/__iterator/incrementable_traits.h"
#include "lsd/__iterator/iterator_traits/forward_declare.h"
#include "lsd/__type_traits/has_typename_difference_type.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

template<
    typename T,
    bool = is_primary_iterator_traits< cxx20_iterator_traits< remove_cvref_t<T> > >::value,
    bool = has_typename_difference_type<incrementable_traits<remove_cvref_t<T>>>::value
>
struct iter_difference_impl {};

template<typename T, bool v>
struct iter_difference_impl<T, false, v> {
  using type = typename cxx20_iterator_traits<remove_cvref_t<T>>::difference_type;
};

template<typename T>
struct iter_difference_impl<T, true, true> {
  using type = typename incrementable_traits<remove_cvref_t<T>>::difference_type;
};

} // namespace detail

template<typename T>
struct iter_difference : detail::iter_difference_impl<T> {};

template<typename T>
using iter_difference_t = typename iter_difference<T>::type;

} // namespace lsd

#endif // LSD_ITERATOR_ITER_DIFFERENCE_T_HPP_
