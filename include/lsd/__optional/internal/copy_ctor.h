# /*
#  * Created by YongGyu Lee on 2021/05/24.
#  */
#
# ifndef LSD_OPTIONAL_INTERNAL_COPY_CTOR_H_
# define LSD_OPTIONAL_INTERNAL_COPY_CTOR_H_
#
# include <type_traits>
#
# include "lsd/__optional/internal/dtor.h"

namespace lsd {
namespace internal {
namespace optional {

template<typename T, bool v = std::is_trivially_copy_constructible<T>::value>
struct copy_ctor : dtor<T> {
  using base = dtor<T>;
  using base::base;
};

template<typename T>
struct copy_ctor<T, false> : dtor<T> {
  using base = dtor<T>;
  using base::base;

  copy_ctor() = default;
  copy_ctor(copy_ctor const& other) {
    if (other.valid) {
      this->construct(other.val);
    }
  }
  copy_ctor(copy_ctor &&) = default;
  copy_ctor& operator=(copy_ctor const&) = default;
  copy_ctor& operator=(copy_ctor &&) = default;
};

} // namespace optional
} // namespace internal
} // namespace lsd


# endif // LSD_OPTIONAL_INTERNAL_COPY_CTOR_H_