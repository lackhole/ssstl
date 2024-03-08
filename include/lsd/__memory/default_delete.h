//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___MEMORY_DEFAULT_DELETE_H_
#define LSD___MEMORY_DEFAULT_DELETE_H_

#include "lsd/type_traits.h"

namespace lsd {

/**
 * default_delete<T>
 * @tparam T
 */
template<typename T>
struct default_delete {
  constexpr default_delete() = default;

  template<typename U, enable_if_t<is_convertible<U *, T *>::value, int> = 0>
  default_delete(const default_delete<U>&) noexcept {}

  void operator()(T *ptr) const {
    static_assert(detail::is_complete<T>::value, "lsd::default_delete<T>: T must be complete type");
    delete ptr;
  }
};

/**
 * default_delete<T[]>
 * @tparam T
 */
template<typename T>
struct default_delete<T[]> {
  constexpr default_delete() = default;

  template<typename U, enable_if_t<is_convertible<U(*)[], T(*)[]>::value, int> = 0>
  default_delete(const default_delete<U[]>&) noexcept {}

  template<typename U, enable_if_t<is_convertible<U(*)[], T(*)[]>::value, int> = 0>
  void operator()(U *ptr) const {
    static_assert(detail::is_complete<U>::value, "lsd::default_delete<T[]>: U must be complete type");
    delete[] ptr;
  }
};

} // namespace lsd

#endif // LSD___MEMORY_DEFAULT_DELETE_H_
