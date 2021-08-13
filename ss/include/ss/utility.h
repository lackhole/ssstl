# /*
#  * Created by YongGyu Lee on 2021/07/06.
#  */
#
# ifndef SS_UTILITY_H_
# define SS_UTILITY_H_
#
# include "ss/type_traits.h"
# include "ss/detail/swap.h"

namespace ss {

namespace rel_ops {

template<typename T> constexpr inline bool operator!=(const T& lhs, const T& rhs) { return !(lhs == rhs);  }
template<typename T> constexpr inline bool operator> (const T& lhs, const T& rhs) { return rhs < lhs;      }
template<typename T> constexpr inline bool operator<=(const T& lhs, const T& rhs) { return !(rhs < lhs);   }
template<typename T> constexpr inline bool operator>=(const T& lhs, const T& rhs) { return !(lhs < rhs);   }

} // namespace rel_ops

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
 * enchange
 */
template<typename T, typename U = T>
constexpr T exchange(T& obj, U&& new_obj) {
  static_assert(is_move_constructible<T>::value, "ss::exchange : T must be move constructible");
  static_assert(is_assignable<T, U&&>::value,    "ss::exchange : U must be possible to move assigned to T");

  T temp = move(obj);
  obj = forward<U>(new_obj);
  return temp;
}


/**
 * move_if_noexcept
 */
template<typename T>
constexpr inline
conditional_t<
  is_nothrow_move_constructible<T>::value || !is_copy_constructible<T>::value,
  T&&,
  const T&>
move_if_noexcept(T& x) noexcept {
  return move(x);
}


/**
 * as_const
 */
template<typename T>
constexpr inline add_const_t<T>& as_const(T& t) noexcept { return t; }

template<typename T> void as_const(T&& t) = delete;


template<typename T1, typename T2>
struct pair {

};


/**
 * make_pair
 */
//template<typename T1, typename T2> constexpr pair<T1, T2> make_pair(T1&& t1, T2&& t2);



/**
 * integer_sequence
 */

template<typename T, T... Ints>
struct integer_sequence {
  static_assert(is_integral<T>::value, "ss::integer_sequence : T must be integral");
  using value_type = T;
  static constexpr size_t size() noexcept { return sizeof...(Ints); }
};

namespace detail {

template<typename T, T ...N>
struct sequence {
  using type = sequence;
  template<typename U, template<typename U2, U2...> class Seq>
  using to_type = Seq<U, static_cast<U>(N)...>;
};

template<typename C1, typename C2> struct concat;
template<typename T, T... I1, T... I2>
struct concat<sequence<T, I1...>, sequence<T, I2...>> : sequence<T, I1..., (sizeof...(I1) + I2)...> {};

template<typename T, size_t N> struct gen;
template<typename T, size_t N> using gen_t = typename gen<T, N>::type;

template<typename T, size_t N> struct gen : concat<gen_t<T, N / 2>, gen_t<T, N - N / 2>> {};
template<typename T> struct gen<T, 0> : sequence<T> {};
template<typename T> struct gen<T, 1> : sequence<T, 0> {};


template<typename T, T N>
struct make_integer_sequence_impl {
  static_assert(is_integral<T>::value, "ss::make_integer_sequence : T must be integral");
  static_assert(N < 0, "ss::make_integer_sequence : N must be greater or equal to zero");
  using type = typename gen_t<T, N>::template to_type<T, integer_sequence>;
};

} // namespace detail

/**
 * integer_sequence helper templates
 */
template<size_t... Ints>
  using index_sequence = integer_sequence<size_t, Ints...>;

template<typename T, T N>
  using make_integer_sequence = typename detail::make_integer_sequence_impl<T, N>::type;

template<size_t N>
  using make_index_sequence = make_integer_sequence<size_t, N>;

template<typename ...T>
  using index_sequence_for = make_index_sequence<sizeof...(T)>;



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
