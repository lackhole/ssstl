//
// Created by cosge on 2023-10-29.
//

#ifndef SS___TYPE_TRAITS_ADD_RVALUE_REFERENCE_H_
#define SS___TYPE_TRAITS_ADD_RVALUE_REFERENCE_H_

#include "ss/__type_traits/integral_constant.h"
#include "ss/__type_traits/void_t.h"

namespace ss {

namespace detail {

template<typename T, typename = void>
struct is_rvalue_referencable : false_type {};

template<typename T>
struct is_rvalue_referencable<T, void_t<T&&>> : true_type {};

template<typename T, bool v = is_rvalue_referencable<T>::value>
struct add_rvalue_reference_impl { using type = T&&; };

template<typename T>
struct add_rvalue_reference_impl<T, false> { using type = T; };

}

/**
 * add_rvalue_reference
 * @tparam T
 */
template<typename T>
struct add_rvalue_reference : detail::add_rvalue_reference_impl<T> {};
template<typename T> using add_rvalue_reference_t = typename add_rvalue_reference<T>::type;

}

#endif //SS___TYPE_TRAITS_ADD_RVALUE_REFERENCE_H_
