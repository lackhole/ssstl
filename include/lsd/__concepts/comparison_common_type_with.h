//
// Created by yonggyulee on 2023/12/27.
//

#ifndef LSD_CONCEPTS_COMPARISON_COMMON_TYPE_WITH_HPP
#define LSD_CONCEPTS_COMPARISON_COMMON_TYPE_WITH_HPP

#include "lsd/__concepts/convertible_to.h"
#include "lsd/__concepts/same_as.h"
#include "lsd/__type_traits/common_reference.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"
#include "lsd/__type_traits/is_referenceable.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

template<typename T, typename U, typename C = common_reference_t<const T&, const U&>>
struct comparison_common_type_with_impl_3
    : conjunction<
        same_as<common_reference_t<const T&, const U&>,
                common_reference_t<const U&, const T&>>,
        disjunction<convertible_to<const T&, const C&>,
                    convertible_to<T, const C&>>,
        disjunction<convertible_to<const U&, const C&>,
                    convertible_to<U, const C&>>
      > {};

template<
    typename T,
    typename U,
    bool = conjunction<has_typename_type< common_reference<const T&, const U&> >,
                       has_typename_type< common_reference<const U&, const T&> >>::value /* true */
>
struct comparison_common_type_with_impl_2 : comparison_common_type_with_impl_3<T, U> {};

template<typename T, typename U>
struct comparison_common_type_with_impl_2<T, U, false> : std::false_type {};

template<typename T, typename U, bool = conjunction<is_referencable<T>, is_referencable<U>>::value /* true */>
struct comparison_common_type_with_impl_1 : comparison_common_type_with_impl_2<T, U> {};

template<typename T, typename U>
struct comparison_common_type_with_impl_1<T, U, false> : std::false_type {};

} // namespace detail

template<typename T, typename U>
struct comparison_common_type_with
  : detail::comparison_common_type_with_impl_1<remove_cvref_t<T>, remove_cvref_t<U>> {};

} // namespace lsd

#endif // LSD_CONCEPTS_COMPARISON_COMMON_TYPE_WITH_HPP
