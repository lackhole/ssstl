# /*
#  * Created by YongGyu Lee on 2021/07/06.
#  */
#
# ifndef LSD_UTILITY_H_
# define LSD_UTILITY_H_
#
# include "lsd/limits.h"
# include "lsd/type_traits.h"
# include "lsd/__algorithm/swap.h"
# include "lsd/__tuple/forward_declare.h"
# include "lsd/__tuple/tuple_size.h"
# include "lsd/__tuple/tuple_element.h"
# include "lsd/__utility/declval.h"
# include "lsd/__utility/forward.h"
# include "lsd/__utility/move.h"
# include "lsd/type_traits.h"
#
# if LSD_CXX_VER >= 20
#   include "lsd/compare.h"
# endif

namespace lsd {

namespace rel_ops {

template<typename T> constexpr inline bool operator!=(const T& lhs, const T& rhs) { return !(lhs == rhs);  }
template<typename T> constexpr inline bool operator> (const T& lhs, const T& rhs) { return rhs < lhs;      }
template<typename T> constexpr inline bool operator<=(const T& lhs, const T& rhs) { return !(rhs < lhs);   }
template<typename T> constexpr inline bool operator>=(const T& lhs, const T& rhs) { return !(lhs < rhs);   }

} // namespace rel_ops

/**
 * enchange
 */
template<typename T, typename U = T>
LSD_CONSTEXPR_AFTER_14
T exchange(T& obj, U&& new_obj)
{
  static_assert(is_move_constructible<T>::value, "lsd::exchange : T must be move constructible");
  static_assert(is_assignable<T&, U&&>::value,    "lsd::exchange : U must be possible to move assigned to T");

  T temp = lsd::move(obj);
  obj = lsd::forward<U>(new_obj);
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
  return lsd::move(x);
}


/**
 * as_const
 */
template<typename T>
constexpr inline add_const_t<T>& as_const(T& t) noexcept { return t; }

template<typename T> void as_const(T&& t) = delete;


/**
 * cmp_xxx
 */
namespace detail {
template<bool v1, bool v2>
struct cmp_impl {
  template<typename T, typename U> static constexpr bool equal(T t, U u) noexcept { return t == u; }
  template<typename T, typename U> static constexpr bool less(T t, U u)  noexcept { return t < u;  }
};

template<>
struct cmp_impl<true, false> {
  template<typename T, typename U>
  static constexpr bool equal(T t, U u) noexcept { return t < 0 ? false : make_unsigned_t<T>(t) == u; }
  template<typename T, typename U>
  static constexpr bool less(T t, U u)  noexcept { return t < 0 ? true  : make_unsigned_t<T>(t) < u;  }
};

template<>
struct cmp_impl<false, true> {
  template<typename T, typename U>
  static constexpr bool equal(T t, U u) noexcept { return u < 0 ? false : t == make_unsigned_t<U>(u); }
  template<typename T, typename U>
  static constexpr bool less(T t, U u)  noexcept { return u < 0 ? false : t < make_unsigned_t<U>(u);  }
};

template<typename T, typename U>
struct cmp : cmp_impl<is_signed<T>::value, is_signed<U>::value> {
  static_assert(is_integral<T>::value && is_integral<T>::value,
                "lsd::cmp_equal : only integral types can be compared");
};
} // namespace detail

template<typename T, typename U>
constexpr inline bool cmp_equal(T t, U u) noexcept {
  return detail::cmp<T, U>::equal(t, u);
}

template<typename T, typename U>
constexpr inline bool cmp_not_equal(T t, U u) noexcept {
  return !detail::cmp<T, U>::equal(t, u);
}

template<typename T, typename U>
constexpr inline bool cmp_less(T t, U u) noexcept {
  return detail::cmp<T, U>::less(t, u);
}

template<typename T, typename U>
constexpr inline bool cmp_greater(T t, U u) noexcept {
  return detail::cmp<U, T>::less(u, t);
}

template<typename T, typename U>
constexpr inline bool cmp_less_equal(T t, U u) noexcept {
  return !detail::cmp<U, T>::less(u, t);
}

template<typename T, typename U>
constexpr inline bool cmp_greater_equal(T t, U u) noexcept {
  return !detail::cmp<T, U>::less(t, u);
}



/**
 * integer_sequence
 */

template<typename T, T... Ints>
struct integer_sequence {
  static_assert(is_integral<T>::value, "lsd::integer_sequence : T must be integral");
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

// TODO: Optimize speed of sizeof... operator in clang
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
  static_assert(is_integral<T>::value, "lsd::make_integer_sequence : T must be integral");
  static_assert(N >= 0, "lsd::make_integer_sequence : N must be greater or equal to zero");
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
 * piecewise_construct_t
 */
struct piecewise_construct_t { explicit piecewise_construct_t() = default; };
LSD_INLINE_VAR constexpr piecewise_construct_t piecewise_construct{};


/**
 * pair
 */
template<typename T1, typename T2>
struct pair {
  using first_type = T1;
  using second_type = T2;

 private:
  template<template<typename...> class Cond>
    using both = conjunction<Cond<first_type>, Cond<second_type>>;

  template<template<typename...> class Cond>
    using either = disjunction<Cond<first_type>, Cond<second_type>>;

  template<template<typename...> class Cond>
    using neither = conjunction<negation<Cond<first_type>>, negation<Cond<second_type>>>;

  template<typename U1, typename U2>
    using both_constructible = conjunction<is_constructible<first_type, U1>, is_constructible<second_type, U2>>;

  template<typename U1, typename U2>
    using both_nothrow_constructible = conjunction<is_nothrow_constructible<first_type, U1>,
                                                   is_nothrow_constructible<second_type, U2>>;

  template<typename A1, typename B1, typename A2, typename B2>
  struct check_constructible {
    static constexpr bool implicit_ = is_convertible<A1, B1>::value && is_convertible<A2, B2>::value;
    static constexpr bool explicit_ = !is_convertible<A1, B1>::value || !is_convertible<A2, B2>::value;
  };

 public:
  template<typename Dummy = void,
    enable_if_t<
      is_same<Dummy, void>::value &&
      both<detail::is_implicitly_default_constructible_t>::value,
    int> = 0>
  constexpr pair() noexcept(both<is_nothrow_default_constructible>::value)
    : first(), second() {}

  template<typename Dummy = void,
    enable_if_t<
      is_same<Dummy, void>::value &&
      (detail::is_implicitly_default_constructible<first_type >::value == false ||
       detail::is_implicitly_default_constructible<second_type>::value == false),
    int> = 0>
  constexpr explicit pair() noexcept(both<is_nothrow_default_constructible>::value)
    : first(), second() {}

  template<typename Dummy = void,
    enable_if_t<
      is_same<Dummy, void>::value &&
      both<is_copy_constructible>::value &&
      check_constructible<const first_type&, first_type, const second_type&, second_type>::implicit_,
    int> = 0>
  constexpr pair(const first_type& x, const second_type& y) noexcept(both<is_nothrow_copy_constructible>::value)
    : first(x), second(y) {}

  template<typename Dummy = void,
    enable_if_t<
      is_same<Dummy, void>::value &&
      both<is_copy_constructible>::value &&
      check_constructible<const first_type&, first_type, const second_type&, second_type>::explicit_,
    int> = 0>
  constexpr explicit pair(const first_type& x, const second_type& y)
    noexcept(both<is_nothrow_copy_constructible>::value)
    : first(x), second(y) {}

  template<typename U1 = T1, typename U2 = T2,
    enable_if_t<
      both_constructible<U1&&, U2&&>::value &&
      check_constructible<U1&&, first_type, U2&&, second_type>::implicit_,
    int> = 0>
  constexpr pair(U1&& x, U2&& y) noexcept(both_nothrow_constructible<U1&&, U2&&>::value)
    : first(lsd::forward<U1>(x)), second(lsd::forward<U2>(y)) {}

  template<typename U1 = T1, typename U2 = T2,
    enable_if_t<
      both_constructible<U1&&, U2&&>::value &&
      check_constructible<U1&&, first_type, U2&&, second_type>::explicit_,
    int> = 0>
  constexpr explicit pair(U1&& x, U2&& y) noexcept(both_nothrow_constructible<U1&&, U2&&>::value)
    : first(lsd::forward<U1>(x)), second(lsd::forward<U2>(y)) {}

  template<typename U1, typename U2,
    enable_if_t<
      both_constructible<const U1&, const U2&>::value &&
      check_constructible<const U1&, first_type, const U2&, second_type>::implicit_,
    int> = 0>
  constexpr pair(const pair<U1, U2>& p) noexcept(both_nothrow_constructible<const U1&, const U2&>::value)
    : first(p.first), second(p.second) {}

  template<typename U1, typename U2,
    enable_if_t<
      both_constructible<const U1&, const U2&>::value &&
      check_constructible<const U1&, first_type, const U2&, second_type>::explicit_,
    int> = 0>
  constexpr explicit pair(const pair<U1, U2>& p) noexcept(both_nothrow_constructible<const U1&, const U2&>::value)
    : first(p.first), second(p.second) {}

  template<typename U1, typename U2,
    enable_if_t<
      both_constructible<U1&&, U2&&>::value &&
      check_constructible<U1&&, first_type, U2&&, second_type>::implicit_,
    int> = 0>
  constexpr pair(pair<U1, U2>&& p) noexcept(both_nothrow_constructible<U1&&, U2&&>::value)
    : first(lsd::forward<U1>(p.first)), second(lsd::forward<U2>(p.second)) {}

  template<typename U1, typename U2,
    enable_if_t<
      both_constructible<U1&&, U2&&>::value &&
      check_constructible<U1&&, first_type, U2&&, second_type>::explicit_,
    int> = 0>
  constexpr explicit pair(pair<U1, U2>&& p)  noexcept(both_nothrow_constructible<U1&&, U2&&>::value)
    : first(lsd::forward<U1>(p.first)), second(lsd::forward<U2>(p.second)) {}

  template<typename ...Args1, typename ...Args2>
  constexpr pair(piecewise_construct_t, tuple<Args1...> first_args, tuple<Args2...> second_args)
  noexcept(conjunction<is_nothrow_constructible<first_type, Args1...>,
                       is_nothrow_constructible<second_type, Args2...>>::value)
    : pair(piecewise_construct_t{}, lsd::move(first_args), lsd::move(second_args),
           make_index_sequence<tuple_size<tuple<Args1...>>::value>{},
           make_index_sequence<tuple_size<tuple<Args2...>>::value>{}) {}

  constexpr pair(const pair&) = default;
  constexpr pair(pair&&) = default;


  LSD_CONSTEXPR_AFTER_14 pair& operator=(conditional_t<both<is_copy_assignable>::value, const pair&, detail::unused> other)
    noexcept(both<is_nothrow_copy_assignable>::value)
  {
    first = other.first;
    second = other.second;
    return *this;
  }
  
  template<typename Dummy = void, 
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        both<is_copy_assignable>
      >::value,
    int> = 0>
  LSD_CONSTEXPR_AFTER_14 const pair& operator=(type_identity_t<const pair&> other)
    noexcept(both<is_nothrow_copy_assignable>::value)
  {
    first = other.first;
    second = other.second;
    return *this;
  }

  template<typename U1, typename U2,
    enable_if_t<
      is_assignable<first_type& , const U1&>::value &&
      is_assignable<second_type&, const U2&>::value,
    int> = 0>
  LSD_CONSTEXPR_AFTER_14 pair& operator=(const pair<U1, U2>& other)
    noexcept(conjunction<is_nothrow_assignable<first_type&, const U1&>,
                         is_nothrow_assignable<second_type&, const U2&>>::value)
  {
    first = other.first;
    second = other.second;
    return *this;
  }

  template<typename U1, typename U2,
    enable_if_t<
      conjunction<
        is_assignable<const first_type& , const U1&>,
        is_assignable<const second_type&, const U2&>
      >::value,
    int> = 0>
  LSD_CONSTEXPR_AFTER_14 const pair& operator=(const pair<U1, U2>& other)
  noexcept(conjunction<is_nothrow_assignable<const first_type&, const U1&>,
                       is_nothrow_assignable<const second_type&, const U2&>>::value)
  {
    first = other.first;
    second = other.second;
    return *this;
  }

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        both<is_move_assignable>
      >::value,
    int> = 0>
  LSD_CONSTEXPR_AFTER_14 pair& operator=(pair&& other)
    noexcept(both<is_nothrow_move_assignable>::value)
  {
    first = lsd::move(other.first);
    second = lsd::move(other.second);
    return *this;
  }

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        is_assignable<const first_type&, first_type>,
        is_assignable<const second_type&, second_type>
      >::value,
      int> = 0>
  LSD_CONSTEXPR_AFTER_14 const pair& operator=(pair&& other)
    noexcept(conjunction<is_nothrow_assignable<const first_type&, first_type>,
                         is_nothrow_assignable<const second_type&, second_type>>::value)
  {
    first = lsd::move(other.first);
    second = lsd::move(other.second);
    return *this;
  }

  template<typename U1, typename U2,
    enable_if_t<
      is_assignable<first_type& , U1>::value &&
      is_assignable<second_type&, U2>::value,
    int> = 0>
  LSD_CONSTEXPR_AFTER_14 pair& operator=(pair<U1, U2>&& other)
    noexcept(conjunction<is_nothrow_assignable<first_type&, U1>, is_nothrow_assignable<second_type&, U2>>::value)
  {
    first = lsd::forward<U1>(other.first);
    second = lsd::forward<U2>(other.second);
    return *this;
  }

  template<typename U1, typename U2,
    enable_if_t<
      conjunction<
        is_assignable<const first_type& , U1>,
        is_assignable<const second_type&, U2>
      >::value,
    int> = 0>
  LSD_CONSTEXPR_AFTER_14 const pair& operator=(pair<U1, U2>&& other)
    noexcept(conjunction<is_nothrow_assignable<const first_type&, U1>,
                         is_nothrow_assignable<const second_type&, U2>>::value)
  {
    first = lsd::forward<U1>(other.first);
    second = lsd::forward<U2>(other.second);
    return *this;
  }

  LSD_CONSTEXPR_AFTER_14 void swap(pair& other)
    noexcept(is_nothrow_swappable<first_type >::value && is_nothrow_swappable<second_type>::value)
  {
    using lsd::swap;
    swap(first, other.first);
    swap(second, other.second);
  }

  first_type first;
  second_type second;
  
 private:
  template<typename... Args1, typename... Args2, size_t... I1, size_t... I2>
  constexpr pair(piecewise_construct_t,
                 tuple<Args1...> first_args, tuple<Args2...> second_args,
                 index_sequence<I1...>, index_sequence<I2...>);
};

# if LSD_CXX_VER >= 17
template<typename T1, typename T2> pair(T1, T2) -> pair<T1, T2>;
# endif

/**
 * make_pair
 */
namespace detail {
template<typename T>
struct make_pair_type_impl {
  using type = T;
};

template<typename T>
struct make_pair_type_impl<reference_wrapper<T>> {
  using type = T&;
};

template<typename T>
using make_pair_type = typename make_pair_type_impl<decay_t<T>>::type;
}

template<typename T1, typename T2>
constexpr inline pair<detail::make_pair_type<T1>, detail::make_pair_type<T2>>
make_pair(T1&& t1, T2&& t2) {
  return pair<detail::make_pair_type<T1>, detail::make_pair_type<T2>>(lsd::forward<T1>(t1), lsd::forward<T2>(t2));
}

/**
 * compares
 */
template<typename T1, typename T2>
constexpr inline bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first == rhs.first && lhs.second == rhs.second;
}

template<typename T1, typename T2>
constexpr inline bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first != rhs.first || lhs.second != rhs.second;
}

template<typename T1, typename T2>
constexpr inline bool operator<(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
}

template<typename T1, typename T2>
constexpr inline bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  using namespace rel_ops;
  return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second <= rhs.second);
}

template<typename T1, typename T2>
constexpr inline bool operator>(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  using namespace rel_ops;
  return lhs.first > rhs.first || (lhs.first == rhs.first && lhs.second > rhs.second);
}

template<typename T1, typename T2>
constexpr inline bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
  using namespace rel_ops;
  return lhs.first > rhs.first || (lhs.first == rhs.first && lhs.second >= rhs.second);
}

/**
 * swap
 */
template<typename T1, typename T2>
LSD_CONSTEXPR_AFTER_14 inline enable_if_t<is_swappable<T1>::value && is_swappable<T2>::value>
swap(pair<T1, T2>& p1, pair<T1, T2>& p2) noexcept(noexcept(p1.swap(p2))) {
  p1.swap(p2);
}


template<typename T1, typename T2>
struct tuple_size<pair<T1, T2>> : integral_constant<size_t, 2> {};

template<size_t I, typename T1, typename T2>
struct tuple_element<I, pair<T1, T2>> {
  static_assert(I < 2, "lsd::tuple_element<I, pair<T1, T2>> : I must be 0 or 1");
};

template<typename T1, typename T2> struct tuple_element<0, pair<T1, T2>> { using type = T1; };
template<typename T1, typename T2> struct tuple_element<1, pair<T1, T2>> { using type = T2; };

namespace detail {

template<size_t>
struct get_pair;

template<>
struct get_pair<0> {
  template<typename T1, typename T2> static constexpr       T1&  get(      pair<T1, T2>&  p) noexcept { return p.first;           }
  template<typename T1, typename T2> static constexpr const T1&  get(const pair<T1, T2>&  p) noexcept { return p.first;           }
  template<typename T1, typename T2> static constexpr       T1&& get(      pair<T1, T2>&& p) noexcept { return lsd::move(p.first); }
  template<typename T1, typename T2> static constexpr const T1&& get(const pair<T1, T2>&& p) noexcept { return lsd::move(p.first); }
};

template<>
struct get_pair<1> {
  template<typename T1, typename T2> static constexpr       T2&  get(      pair<T1, T2>&  p) noexcept { return p.second;           }
  template<typename T1, typename T2> static constexpr const T2&  get(const pair<T1, T2>&  p) noexcept { return p.second;           }
  template<typename T1, typename T2> static constexpr       T2&& get(      pair<T1, T2>&& p) noexcept { return lsd::move(p.second); }
  template<typename T1, typename T2> static constexpr const T2&& get(const pair<T1, T2>&& p) noexcept { return lsd::move(p.second); }
};

} // namespace detail

template<size_t I, typename T1, typename T2>
constexpr inline tuple_element_t<I, pair<T1, T2>>&
get(pair<T1, T2>& p) noexcept {
  return detail::get_pair<I>::get(p);
}

template<size_t I, typename T1, typename T2>
constexpr inline const tuple_element_t<I, pair<T1, T2>>&
get(const pair<T1, T2>& p) noexcept {
  return detail::get_pair<I>::get(p);
}

template<size_t I, typename T1, typename T2>
constexpr inline tuple_element_t<I, pair<T1, T2>>&&
get(pair<T1, T2>&& p) noexcept {
  return detail::get_pair<I>::get(lsd::move(p));
}

template<size_t I, typename T1, typename T2>
constexpr inline const tuple_element_t<I, pair<T1, T2>>&&
get(const pair<T1, T2>&& p) noexcept {
  return detail::get_pair<I>::get(lsd::move(p));
}

template<typename T, typename U>
constexpr inline T&
get(pair<T, U>& p) noexcept { return p.first; }

template<typename T, typename U>
constexpr inline const T&
get(const pair<T, U>& p) noexcept { return p.first; }

template<typename T, typename U>
constexpr inline T&&
get(pair<T, U>&& p) noexcept { return lsd::move(p.first); }

template<typename T, typename U>
constexpr inline const T&&
get(const pair<T, U>&& p) noexcept { return lsd::move(p.first); }

template<typename T, typename U>
constexpr inline T&
get(pair<U, T>& p) noexcept { return p.second; }

template<typename T, typename U>
constexpr inline const T&
get(const pair<U, T>& p) noexcept { return p.second; }

template<typename T, typename U>
constexpr inline T&&
get(pair<U, T>&& p) noexcept { return lsd::move(p.second); }

template<typename T, typename U>
constexpr inline const T&&
get(const pair<U, T>&& p) noexcept { return lsd::move(p.second); }

template<typename T> T& get(pair<T, T>& p) = delete;
template<typename T> const T& get(const pair<T, T>& p) = delete;
template<typename T> T&& get(pair<T, T>&& p) = delete;
template<typename T> const T&& get(const pair<T, T>&& p) = delete;

template<typename T1, typename T2>
template<typename... Args1, typename... Args2, size_t... I1, size_t... I2>
constexpr pair<T1, T2>::pair(piecewise_construct_t,
               tuple<Args1...> first_args, tuple<Args2...> second_args,
               index_sequence<I1...>, index_sequence<I2...>)
  : first(lsd::forward<Args1>(lsd::get<I1>(first_args))...),
    second(lsd::forward<Args2>(lsd::get<I2>(second_args))...) {}


/**
 * in_place_t
 */
struct in_place_t { constexpr explicit in_place_t() = default; };
LSD_INLINE_VAR constexpr in_place_t in_place{};

template<typename T> struct in_place_type_t { constexpr explicit in_place_type_t() = default; };
# if LSD_CXX_VER >= 14
template<typename T> LSD_INLINE_VAR constexpr in_place_type_t<T> in_place_type{};
# endif

/**
 * is_place_index_t
 * @tparam I
 */
template<size_t I> struct in_place_index_t { explicit in_place_index_t() = default; };
# if LSD_CXX_VER >= 14
template<size_t I> LSD_INLINE_VAR constexpr in_place_index_t<I> in_place_index{};
# endif

/**
 * in_range
 * @tparam R
 * @tparam T
 * @param t
 * @return
 */
template<typename R, typename T>
constexpr bool in_range(T t) noexcept {
  return cmp_greater_equal(t, numeric_limits<R>::min()) && cmp_less_equal(t, numeric_limits<R>::max());
}

} // namespace lsd

#endif // LSD_UTILITY_H_
