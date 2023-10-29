//
// Created by cosge on 2023-10-29.
//

#ifndef SS___MEMORY_DEFAULT_DELETE_H_
#define SS___MEMORY_DEFAULT_DELETE_H_

#include "ss/type_traits.h"

namespace ss {

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
    static_assert(detail::is_complete<T>::value, "ss::default_delete<T>: T must be complete type");
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
    static_assert(detail::is_complete<U>::value, "ss::default_delete<T[]>: U must be complete type");
    delete[] ptr;
  }
};

} // namespace ss

#endif // SS___MEMORY_DEFAULT_DELETE_H_
