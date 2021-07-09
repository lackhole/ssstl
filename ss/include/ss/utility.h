# /*
#  * Created by YongGyu Lee on 2021/07/06.
#  */
#
# ifndef SS_UTILITY_H_
# define SS_UTILITY_H_
#
# include "ss/type_traits.h"

namespace ss {

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
