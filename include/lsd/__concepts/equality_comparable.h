//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_CONCEPTS_EQUALITY_COMPARABLE_HPP_
#define LSD_CONCEPTS_EQUALITY_COMPARABLE_HPP_

#include "lsd/__concepts/comparison_common_type_with.h"
#include "lsd/__concepts/equality_comparable.h"
#include "lsd/__concepts/weakly_equality_comparable_with.h"
#include "lsd/__type_traits/common_reference.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {

template<typename T>
struct equality_comparable : weakly_equality_comparable_with<T, T> {};


namespace detail {

template<
    typename T,
    typename U,
    bool = has_typename_type<
             common_reference< const std::remove_reference_t<T>&,
                               const std::remove_reference_t<U>& >
           >::value /* true */
>
struct equality_comparable_with_impl_2
    : conjunction<
        equality_comparable<
            common_reference_t< const std::remove_reference_t<T>&,
                                const std::remove_reference_t<U>&> >,
        weakly_equality_comparable_with<T, U>
      >{};

template<typename T, typename U>
struct equality_comparable_with_impl_2<T, U, false> : std::false_type {};

template<
    typename T,
    typename U,
    bool = conjunction<
               equality_comparable<T>,
               equality_comparable<U>,
               comparison_common_type_with<T, U>
           >::value /* true */
>
struct equality_comparable_with_impl_1 : equality_comparable_with_impl_2<T, U> {};
template<typename T, typename U>
struct equality_comparable_with_impl_1<T, U, false> : std::false_type {};

} // namespace detail

template<typename T, typename U>
struct equality_comparable_with : detail::equality_comparable_with_impl_1<T, U> {};

} // namespace lsd

#endif // LSD_CONCEPTS_EQUALITY_COMPARABLE_HPP_
