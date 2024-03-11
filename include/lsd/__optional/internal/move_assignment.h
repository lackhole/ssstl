# /*
#  * Created by YongGyu Lee on 2021/05/24.
#  */
#
#ifndef LSD_OPTIONAL_INTERNAL_MOVE_ASSIGNMENT_H_
#define LSD_OPTIONAL_INTERNAL_MOVE_ASSIGNMENT_H_
#
# include <type_traits>
#
# include "lsd/__optional/internal/copy_assignment.h"

namespace lsd {
namespace internal {
namespace optional {

template<typename T, bool v =
  std::is_trivially_move_constructible<T>::value &&
  std::is_trivially_move_assignable<T>::value &&
  std::is_trivially_destructible<T>::value>
struct move_assign : copy_assign<T> {
  using base = copy_assign<T>;
  using base::base;
};

template<typename T>
struct move_assign<T, false> : copy_assign<T> {
  using base = copy_assign<T>;
  using base::base;

  move_assign() = default;
  move_assign(move_assign const&) = default;
  move_assign(move_assign &&) = default;
  move_assign& operator=(move_assign const&) = default;
  move_assign& operator=(move_assign && other)
    noexcept(std::is_nothrow_move_assignable<T>::value && std::is_nothrow_move_constructible<T>::value)
  {
    if (!other.valid) {
      this->reset();
    } else {
      if (this->valid)
        this->val = std::move(other.val);
      else
        this->construct(std::move(other.val));
    }
    return *this;
  }
};

} // namespace optional
} // namespace internal
} // namespace lsd

# endif // LSD_OPTIONAL_INTERNAL_MOVE_ASSIGNMENT_H_
