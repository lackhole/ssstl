//
// Created by cosge on 2023-10-29.
//

#ifndef SS___UTILITY_FORWARD_H_
#define SS___UTILITY_FORWARD_H_

#include "ss/__type_traits/remove_reference.h"
#include "ss/__type_traits/is_lvalue_reference.h"

namespace ss {

template<typename T> // T = U (rvalue) T = U&(lvalue) where U is no-ref
constexpr inline T&& forward(remove_reference_t<T>& t) noexcept {
return static_cast<T&&>(t);
}

template<typename T>
constexpr inline T&& forward(remove_reference_t<T>&& t) noexcept {
static_assert(!is_lvalue_reference<T>::value, "Forwarding rvalue to lvalue is prohibited");
return static_cast<T&&>(t);
}


} // namespace ss

#endif // SS___UTILITY_FORWARD_H_
