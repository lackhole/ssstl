//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___TYPE_TRAITS_IS_LVALUE_REFERENCE_H_
#define LSD___TYPE_TRAITS_IS_LVALUE_REFERENCE_H_

#include "lsd/__type_traits/integral_constant.h"

namespace lsd {

template<typename T> struct is_lvalue_reference : false_type {};
template<typename T> struct is_lvalue_reference<T&> : true_type {};
# if LSD_CXX_VER >= 14
template<typename T> LSD_INLINE_VAR constexpr bool is_lvalue_reference_v = is_lvalue_reference<T>::value;
# endif

} // namespace lsd

#endif // LSD___TYPE_TRAITS_IS_LVALUE_REFERENCE_H_
