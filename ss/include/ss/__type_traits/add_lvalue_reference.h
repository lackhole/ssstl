//
// Created by cosge on 2023-10-29.
//

#ifndef SS___TYPE_TRAITS_ADD_LVALUE_REFERENCE_H_
#define SS___TYPE_TRAITS_ADD_LVALUE_REFERENCE_H_

#include "ss/__type_traits/integral_constant.h"
#include "ss/__type_traits/void_t.h"

namespace ss {

namespace detail {

template<typename T, typename = void>
struct is_lvalue_referencable : false_type {};

template<typename T>
struct is_lvalue_referencable<T, void_t<T&>> : true_type {};

template<typename T, bool v = is_lvalue_referencable<T>::value>
struct add_lvalue_reference_impl { using type = T&; };

template<typename T>
struct add_lvalue_reference_impl<T, false> { using type = T; };

} // namespace detail

template<typename T>
struct add_lvalue_reference : detail::add_lvalue_reference_impl<T> {};
template<typename T> using add_lvalue_reference_t = typename add_lvalue_reference<T>::type;

} // namespace ss

#endif //SS___TYPE_TRAITS_ADD_LVALUE_REFERENCE_H_
