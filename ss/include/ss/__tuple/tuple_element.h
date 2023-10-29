//
// Created by cosge on 2023-10-29.
//

#ifndef SS___TUPLE_TUPLE_ELEMENT_H_
#define SS___TUPLE_TUPLE_ELEMENT_H_

#include "ss/type_traits.h"

namespace ss {

template<size_t I, typename T>
struct tuple_element;

template<size_t I, typename T>
using tuple_element_t = typename tuple_element<I, T>::type;

template<size_t I, typename T>
struct tuple_element<I, const T> {
  using type = add_const_t<tuple_element_t<I, T>>;
};

template<size_t I, typename T>
struct tuple_element<I, volatile T> {
  using type = add_volatile_t<tuple_element_t<I, T>>;
};

template<size_t I, typename T>
struct tuple_element<I, const volatile T> {
  using type = add_cv_t<tuple_element_t<I, T>>;
};

} // namespace ss

#endif // SS___TUPLE_TUPLE_ELEMENT_H_
