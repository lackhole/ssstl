# /*
#  * Created by YongGyu Lee on 2021/07/06.
#  */
#
# ifndef SS_UTILITY_H_
# define SS_UTILITY_H_
#
# include "ss/type_traits.h"

namespace ss {

namespace rel_ops {

template<typename T> inline bool operator!=(const T& lhs, const T& rhs) { return !(lhs == rhs); }
template<typename T> inline bool operator> (const T& lhs, const T& rhs) { return rhs < lhs; }
template<typename T> inline bool operator<=(const T& lhs, const T& rhs) { return !(rhs < lhs); }
template<typename T> inline bool operator>=(const T& lhs, const T& rhs) { return !(lhs < rhs); }

}

template<typename ForwardIt1, typename ForwardIt2>
SS_CONSTEXPR_AFTER_14 inline void iter_swap(ForwardIt1 a, ForwardIt2 b) {
  using ss::swap;
  swap(*a, *b);
}

template<typename ForwardIt1, typename ForwardIt2>
SS_CONSTEXPR_AFTER_14 ForwardIt2 swap_ranges(ForwardIt1 first, ForwardIt1 last, ForwardIt2 first2) {
  while (first != last) {
    iter_swap(first++, first2++);
  }
  return first2;
}

// TODO
//template<typename ExecutionPolicy, typename ForwardIt1, typename ForwardIt2>
//ForwardIt2 swap_ranges(ExecutionPolicy&& policy, ForwardIt1 first, ForwardIt1 last, ForwardIt2 first2);}

template<typename T>
SS_CONSTEXPR_AFTER_14 inline enable_if_t<is_move_constructible<T>::value && is_move_assignable<T>::value> swap(T& a, T& b)
noexcept(is_nothrow_move_constructible<T>::value && is_nothrow_move_assignable<T>::value)
{
  T temp = move(a);
  a = move(b);
  b = move(temp);
}

template<typename T, size_t N>
SS_CONSTEXPR_AFTER_14 inline enable_if_t<is_swappable<T>::value> swap(T(&a)[N], T(&b)[N]) noexcept(is_nothrow_swappable<T>::value) {
  swap_ranges(a, a+N, b);
}

template<typename T> // T = U (rvalue) T = U&(lvalue) where U is no-ref
constexpr inline T&& forward(remove_reference_t<T>& t) noexcept {
  return static_cast<T&&>(t);
}

template<typename T>
constexpr inline T&& forward(remove_reference_t<T>&& t) noexcept {
  static_assert(!is_lvalue_reference<T>::value, "Forwarding rvalue to lvalue is prohibited");
  return static_cast<T&&>(t);
}

template<typename T>
constexpr inline remove_reference_t<T>&& move(T&& t) noexcept {
  return static_cast<remove_reference_t<T>&&>(t);
}

/**
 * in_place_t
 */
struct in_place_t { constexpr explicit in_place_t() = default; };
SS_INLINE_VAR constexpr in_place_t in_place{};

template<typename T> struct in_place_type_t { constexpr explicit in_place_type_t() = default; };
# if SS_CXX_VER >= 14
template<typename T> SS_INLINE_VAR constexpr in_place_type_t<T> in_place_type{};
# endif

/**
 * is_place_index_t
 * @tparam I
 */
template<size_t I> struct in_place_index_t { explicit in_place_index_t() = default; };
# if SS_CXX_VER >= 14
template<size_t I> SS_INLINE_VAR constexpr in_place_index_t<I> in_place_index{};
# endif

} // namespace ss

#endif // SS_UTILITY_H_
