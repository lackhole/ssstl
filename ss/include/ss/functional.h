# /*
#  * Created by YongGyu Lee on 2021/07/06.
#  */
#
# ifndef SS_FUNCTIONAL_H_
# define SS_FUNCTIONAL_H_

# include "ss/type_traits.h"
# include "ss/utility.h"

namespace ss {

template<typename Key>
struct hash;

//template<typename Func, typename ...Args>
//constexpr inline decltype(auto) invoke(Func&&, Args&&... args) {
//  return 0;
//}

/**
 * plus
 * @tparam T
 */
template<typename T = void>
struct plus {
  constexpr T operator()(const T& lhs, const T& rhs) const {
    return lhs + rhs;
  }
};

template<>
struct plus<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) + ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) + ss::forward<U>(rhs);
  }
};



/**
 * minus
 * @tparam T
 */
template<typename T = void>
struct minus {
  constexpr T operator()(const T& lhs, const T& rhs) const {
    return lhs - rhs;
  }
};

template<>
struct minus<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) - ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) - ss::forward<U>(rhs);
  }
};



/**
 * multiplies
 * @tparam T
 */
template<typename T = void>
struct multiplies {
  constexpr T operator()(const T& lhs, const T& rhs) const {
    return lhs * rhs;
  }
};

template<>
struct multiplies<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) * ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) * ss::forward<U>(rhs);
  }
};



/**
 * divides
 * @tparam T
 */
template<typename T = void>
struct divides {
  constexpr T operator()(const T& lhs, const T& rhs) const {
    return lhs / rhs;
  }
};

template<>
struct divides<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) / ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) / ss::forward<U>(rhs);
  }
};



/**
 * modulus
 * @tparam T
 */
template<typename T = void>
struct modulus {
  constexpr T operator()(const T& lhs, const T& rhs) const {
    return lhs % rhs;
  }
};

template<>
struct modulus<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) % ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) % ss::forward<U>(rhs);
  }
};



/**
 * negate
 * @tparam T
 */
template<typename T = void>
struct negate {
  constexpr T operator()(const T& x) const {
    return -x;
  }
};

template<>
struct negate<void> {
  using is_transparent = true_type;

  template<typename T>
  constexpr auto operator()(T&& x) const -> decltype(-ss::forward<T>(x)) {
    return -ss::forward<T>(x);
  }
};



/**
 * equal_to
 * @tparam T
 */
template<typename T = void>
struct equal_to {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs == rhs;
  }
};

template<>
struct equal_to<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) == ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) == ss::forward<U>(rhs);
  }
};



/**
 * not_equal_to
 * @tparam T
 */
template<typename T = void>
struct not_equal_to {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs != rhs;
  }
};

template<>
struct not_equal_to<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) != ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) != ss::forward<U>(rhs);
  }
};



/**
 * greater
 * @tparam T
 */
template<typename T = void>
struct greater {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs > rhs;
  }
};

template<>
struct greater<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) > ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) > ss::forward<U>(rhs);
  }
};



/**
 * less
 * @tparam T
 */
template<typename T = void>
struct less {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs < rhs;
  }
};

template<>
struct less<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) < ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) < ss::forward<U>(rhs);
  }
};



/**
 * greater
 * @tparam T
 */
template<typename T = void>
struct greater_equal {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs >= rhs;
  }
};

template<>
struct greater_equal<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) >= ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) >= ss::forward<U>(rhs);
  }
};



/**
 * less_equal
 * @tparam T
 */
template<typename T = void>
struct less_equal {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs <= rhs;
  }
};

template<>
struct less_equal<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) <= ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) <= ss::forward<U>(rhs);
  }
};



/**
 * logical_and
 * @tparam T
 */
template<typename T = void>
struct logical_and {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs && rhs;
  }
};

template<>
struct logical_and<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) && ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) && ss::forward<U>(rhs);
  }
};



/**
 * logical_or
 * @tparam T
 */
template<typename T = void>
struct logical_or {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs || rhs;
  }
};

template<>
struct logical_or<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) || ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) || ss::forward<U>(rhs);
  }
};



/**
 * logical_not
 * @tparam T
 */
template<typename T = void>
struct logical_not {
  constexpr bool operator()(const T& x) const {
    return !x;
  }
};

template<>
struct logical_not<void> {
  using is_transparent = true_type;

  template<typename T>
  constexpr auto operator()(T&& x) const -> decltype(!ss::forward<T>(x)) {
    return !ss::forward<T>(x);
  }
};



/**
 * bit_and
 * @tparam T
 */
template<typename T = void>
struct bit_and {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs & rhs;
  }
};

template<>
struct bit_and<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) & ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) & ss::forward<U>(rhs);
  }
};



/**
 * bit_or
 * @tparam T
 */
template<typename T = void>
struct bit_or {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs | rhs;
  }
};

template<>
struct bit_or<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) | ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) | ss::forward<U>(rhs);
  }
};



/**
 * bit_xor
 * @tparam T
 */
template<typename T = void>
struct bit_xor {
  constexpr bool operator()(const T& lhs, const T& rhs) const {
    return lhs ^ rhs;
  }
};

template<>
struct bit_xor<void> {
  using is_transparent = true_type;

  template<typename T, typename U>
  constexpr auto operator()(T&& lhs, U&& rhs) const -> decltype(ss::forward<T>(lhs) ^ ss::forward<U>(rhs)) {
    return ss::forward<T>(lhs) ^ ss::forward<U>(rhs);
  }
};



/**
 * bit_not
 * @tparam T
 */
template<typename T = void>
struct bit_not {
  constexpr bool operator()(const T& x) const {
    return ~x;
  }
};

template<>
struct bit_not<void> {
  using is_transparent = true_type;

  template<typename T>
  constexpr auto operator()(T&& x) const -> decltype(~ss::forward<T>(x)) {
    return ~ss::forward<T>(x);
  }
};

}

# endif // SS_FUNCTIONAL_H_
