# /*
#  * Created by YongGyu Lee on 2021/05/24.
#  */
#
# ifndef LSD_OPTIONAL_INTERNAL_COPY_ASSIGNMENT_H_
# define LSD_OPTIONAL_INTERNAL_COPY_ASSIGNMENT_H_
#
# include <type_traits>
#
# include "lsd/__optional/internal/move_ctor.h"

namespace lsd {
namespace internal {
namespace optional {

template<typename T, bool v =
  std::is_trivially_copy_constructible<T>::value &&
  std::is_trivially_copy_assignable<T>::value &&
  std::is_trivially_destructible<T>::value>
struct copy_assign : move_ctor<T> {
  using base = move_ctor<T>;
  using base::base;
};

template<typename T>
struct copy_assign<T, false> : move_ctor<T> {
  using base = move_ctor<T>;
  using base::base;

  copy_assign() = default;
  copy_assign(copy_assign const&) = default;
  copy_assign(copy_assign &&) = default;
  copy_assign& operator=(copy_assign const& other) {
    if (!other.valid) {
      this->reset();
    } else {
      if (this->valid)
        this->val = other.val;
      else
        this->construct(other.val);
    }
    return *this;
  }
  copy_assign& operator=(copy_assign &&) = default;
};

} // namespace optional
} // namespace internal
} // namespace lsd

# endif // LSD_OPTIONAL_INTERNAL_COPY_ASSIGNMENT_H_
