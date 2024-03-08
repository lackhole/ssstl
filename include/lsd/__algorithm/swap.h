# /*
#  * Created by YongGyu Lee on 2021/07/09.
#  */
#
# ifndef LSD_DETAIL_SWAP_H_
# define LSD_DETAIL_SWAP_H_
#
# include "lsd/type_traits.h"
# include "lsd/__utility/move.h"

namespace lsd {

template<typename T>
LSD_CONSTEXPR_AFTER_14 inline
enable_if_t<is_move_constructible<T>::value && is_move_assignable<T>::value>
swap(T& a, T& b)
noexcept(is_nothrow_move_constructible<T>::value && is_nothrow_move_assignable<T>::value)
{
  T temp = lsd::move(a);
  a = lsd::move(b);
  b = lsd::move(temp);
}

template<typename ForwardIt1, typename ForwardIt2>
LSD_CONSTEXPR_AFTER_14 inline void
iter_swap(ForwardIt1 a, ForwardIt2 b) {
  using lsd::swap;
  swap(*a, *b);
}

template<typename ForwardIt1, typename ForwardIt2>
LSD_CONSTEXPR_AFTER_14 ForwardIt2
swap_ranges(ForwardIt1 first, ForwardIt1 last, ForwardIt2 first2) {
  while (first != last) {
    iter_swap(first++, first2++);
  }
  return first2;
}

// TODO
//template<typename ExecutionPolicy, typename ForwardIt1, typename ForwardIt2>
//ForwardIt2 swap_ranges(ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last, ForwardIt2 first2);}

template<typename T, size_t N>
LSD_CONSTEXPR_AFTER_14 inline
enable_if_t<is_swappable<T>::value>
swap(T(&a)[N], T(&b)[N]) noexcept(is_nothrow_swappable<T>::value) {
  swap_ranges(a, a+N, b);
}

} // namespace lsd

# endif // LSD_DETAIL_SWAP_H_
