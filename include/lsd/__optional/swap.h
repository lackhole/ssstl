# /*
#  * Created by YongGyu Lee on 2021/05/24.
#  */
#
# ifndef LSD_OPTIONAL_SWAP_H_
# define LSD_OPTIONAL_SWAP_H_
#
# include <algorithm>
# include <type_traits>
# include <utility>
#
# include "lsd/__optional/forward_declare.h"
# include "lsd/__type_traits/conjunction.h"
# include "lsd/__type_traits/is_swappable.h"

namespace std {

template<typename T,
  ::std::enable_if_t<
    ::std::is_move_constructible<T>::value && ::lsd::is_swappable<T>::value,
  int> = 0>
void swap(::lsd::optional<T>& lhs, ::lsd::optional<T>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}

} // namespace std

# endif // LSD_OPTIONAL_SWAP_H_
