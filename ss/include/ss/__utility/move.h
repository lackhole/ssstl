//
// Created by cosge on 2023-10-29.
//

#ifndef SS___UTILITY_MOVE_H_
#define SS___UTILITY_MOVE_H_

#include "ss/__type_traits/remove_reference.h"

namespace ss {

template<typename T>
constexpr inline remove_reference_t<T>&& move(T&& t) noexcept {
  return static_cast<remove_reference_t<T>&&>(t);
}

} // namespace ss

#endif // SS___UTILITY_MOVE_H_
