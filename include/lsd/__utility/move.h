//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___UTILITY_MOVE_H_
#define LSD___UTILITY_MOVE_H_

#include "lsd/__type_traits/remove_reference.h"

namespace lsd {

template<typename T>
constexpr inline remove_reference_t<T>&& move(T&& t) noexcept {
  return static_cast<remove_reference_t<T>&&>(t);
}

} // namespace lsd

#endif // LSD___UTILITY_MOVE_H_
