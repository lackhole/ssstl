//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___TUPLE_TUPLE_SIZE_H_
#define LSD___TUPLE_TUPLE_SIZE_H_

#include "lsd/__size_t.h"
#include "lsd/__type_traits/integral_constant.h"

namespace lsd {

template<typename T>
struct tuple_size;

template<typename T>
struct tuple_size<const T> : integral_constant<size_t, tuple_size<T>::value> {};

# if LSD_CXX_VER >= 14
template<typename T>
constexpr size_t tuple_size_v = tuple_size<T>::value;
# endif

} // namespace lsd

#endif // LSD___TUPLE_TUPLE_SIZE_H_
