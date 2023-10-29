//
// Created by cosge on 2023-10-29.
//

#ifndef SS___TYPE_TRAITS_IS_LVALUE_REFERENCE_H_
#define SS___TYPE_TRAITS_IS_LVALUE_REFERENCE_H_

#include "ss/__type_traits/integral_constant.h"

namespace ss {

template<typename T> struct is_lvalue_reference : false_type {};
template<typename T> struct is_lvalue_reference<T&> : true_type {};
# if SS_CXX_VER >= 14
template<typename T> SS_INLINE_VAR constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
# endif

} // namespace ss

#endif // SS___TYPE_TRAITS_IS_LVALUE_REFERENCE_H_
