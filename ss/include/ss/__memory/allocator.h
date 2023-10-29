//
// Created by cosge on 2023-10-29.
//

#ifndef SS___MEMORY_ALLOCATOR_H_
#define SS___MEMORY_ALLOCATOR_H_

#include <cstdint>

#include "ss/limits.h"
#include "ss/__new/align_val_t.h"
#include "ss/__new/bad_array_new_length.h"
#include "ss/type_traits.h"

namespace ss {

template<typename Pointer>
struct allocation_result {
  Pointer ptr;
  size_t count;
};

template<typename T>
struct allocator {
  using value_type = T;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using propagate_on_container_move_assignment = true_type;

  constexpr allocator() noexcept = default;
  constexpr allocator(const allocator&) noexcept = default;

  template<typename U>
  constexpr allocator(const allocator<U>&) noexcept {}

  SS_AFTER_CXX20(constexpr)
  ~allocator() = default;

  // TODO: Check operator new(size_t, align_val_t), operator delete(void*, align_val_t) is available

  SS_NODISCARD SS_CONSTEXPR_AFTER_14 T* allocate(size_t n) {
    if (numeric_limits<size_t>::max() / sizeof(T) < n)
      throw bad_array_new_length();
# if SS_CXX_VER < 17
    return static_cast<T*>(::operator new(n * sizeof(T)));
# else
    return static_cast<T*>(::operator new(n * sizeof(T), static_cast<align_val_t>(alignof(T))));
# endif
  }

  SS_NODISCARD SS_CONSTEXPR_AFTER_14 allocation_result<T*> allocate_at_least(size_t n) {
    // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p0401r6.html#motivation
    if ((numeric_limits<size_t>::max() / sizeof(T)) < n)
      throw bad_array_new_length();
    return {
# if SS_CXX_VER < 17
        static_cast<T*>(::operator new(n * sizeof(T))),
# else
        static_cast<T*>(::operator new(n * sizeof(T), static_cast<align_val_t>(sizeof(T)))),
# endif
        n
    };
  }

  SS_CONSTEXPR_AFTER_14 void deallocate(T* p, size_t n) {
# if SS_CXX_VER < 17
    ::operator delete(p);
# else
    ::operator delete(p, static_cast<align_val_t>(alignof(T)));
# endif
  }
};

template<typename T1, typename T2>
constexpr bool operator==(const allocator<T1>& lhs, const allocator<T2>& rhs) noexcept {
  return true;
}
# if SS_CXX_VER < 20
template<typename T1, typename T2>
constexpr bool operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs) noexcept {
  return false;
}
# endif

} // namespace ss

#endif // SS___MEMORY_ALLOCATOR_H_
