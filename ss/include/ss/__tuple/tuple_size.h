//
// Created by cosge on 2023-10-29.
//

#ifndef SS___TUPLE_TUPLE_SIZE_H_
#define SS___TUPLE_TUPLE_SIZE_H_

#include "ss/__size_t.h"
#include "ss/__type_traits/integral_constant.h"

namespace ss {

template<typename T>
struct tuple_size;

template<typename T>
struct tuple_size<const T> : integral_constant<size_t, tuple_size<T>::value> {};

# if SS_CXX_VER >= 14
template<typename T>
constexpr size_t tuple_size_v = tuple_size<T>::value;
# endif

} // namespace ss

#endif // SS___TUPLE_TUPLE_SIZE_H_
