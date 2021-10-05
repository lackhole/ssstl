# /*
#  * Created by YongGyu Lee on 2021/07/06.
#  */
#
# ifndef SS_UTILITY_H_
# define SS_UTILITY_H_
#
# include <initializer_list>
#
# include "ss/type_traits.h"
# include "ss/detail/swap.h"
# include "ss/detail/tuple_helper.h"
#
# if SS_CXX_VER >= 20
#   include "ss/compare.h"
# endif

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

/**
 * enchange
 */
template<typename T, typename U = T>
SS_CONSTEXPR_AFTER_14
T exchange(T& obj, U&& new_obj)
{
  static_assert(is_move_constructible<T>::value, "ss::exchange : T must be move constructible");
  static_assert(is_assignable<T&, U&&>::value,    "ss::exchange : U must be possible to move assigned to T");

  T temp = ss::move(obj);
  obj = ss::forward<U>(new_obj);
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
  return ss::move(x);
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
                "ss::cmp_equal : only integral types can be compared");
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
 * piecewise_construct_t
 */
struct piecewise_construct_t { explicit piecewise_construct_t() = default; };
SS_INLINE_VAR constexpr piecewise_construct_t piecewise_construct{};


/**
 * tuple forward-declare
 */
template<typename ...Ts>
struct tuple;


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
    : first(ss::forward<U1>(x)), second(ss::forward<U2>(y)) {}

  template<typename U1 = T1, typename U2 = T2,
    enable_if_t<
      both_constructible<U1&&, U2&&>::value &&
      check_constructible<U1&&, first_type, U2&&, second_type>::explicit_,
    int> = 0>
  constexpr explicit pair(U1&& x, U2&& y) noexcept(both_nothrow_constructible<U1&&, U2&&>::value)
    : first(ss::forward<U1>(x)), second(ss::forward<U2>(y)) {}

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
    : first(ss::forward<U1>(p.first)), second(ss::forward<U2>(p.second)) {}

  template<typename U1, typename U2,
    enable_if_t<
      both_constructible<U1&&, U2&&>::value &&
      check_constructible<U1&&, first_type, U2&&, second_type>::explicit_,
    int> = 0>
  constexpr explicit pair(pair<U1, U2>&& p)  noexcept(both_nothrow_constructible<U1&&, U2&&>::value)
    : first(ss::forward<U1>(p.first)), second(ss::forward<U2>(p.second)) {}

    // TODO
//  template<typename ...Args1, typename ...Args2>
//  constexpr pair(piecewise_construct_t, tuple<Args1...> first_args, tuple<Args2...> second_args)

  constexpr pair(const pair&) = default;
  constexpr pair(pair&&) = default;


  template<typename Dummy = void,
    enable_if_t<
      is_same<Dummy, void>::value &&
      both<is_copy_assignable>::value,
    int> = 0>
  SS_CONSTEXPR_AFTER_14 pair& operator=(const pair& other) {
    first = other.first;
    second = other.second;
    return *this;
  }

  template<typename U1, typename U2,
    enable_if_t<
      is_assignable<first_type& , const U1&>::value &&
      is_assignable<second_type&, const U2&>::value,
    int> = 0>
  SS_CONSTEXPR_AFTER_14 pair& operator=(const pair<U1, U2>& other) {
    first = other.first;
    second = other.second;
    return *this;
  }

  template<typename Dummy = void,
    enable_if_t<
      is_same<Dummy, void>::value &&
      both<is_move_assignable>::value,
    int> = 0>
  SS_CONSTEXPR_AFTER_14 pair& operator=(pair&& other) {
    first = ss::move(other.first);
    second = ss::move(other.second);
    return *this;
  }

  template<typename U1, typename U2,
    enable_if_t<
      is_assignable<first_type& , U1>::value &&
      is_assignable<second_type&, U2>::value,
    int> = 0>
  SS_CONSTEXPR_AFTER_14 pair& operator=(pair<U1, U2>&& other)
    noexcept(is_nothrow_move_assignable<first_type>::value && is_nothrow_move_assignable<second_type>::value)
  {
    first = ss::forward<U1>(other.first);
    second = ss::forward<U2>(other.second);
    return *this;
  }

  SS_CONSTEXPR_AFTER_14 void swap(pair& other)
    noexcept(is_nothrow_swappable<first_type >::value && is_nothrow_swappable<second_type>::value)
  {
    using ss::swap;
    swap(first, other.first);
    swap(second, other.second);
  }

  first_type first;
  second_type second;
};

# if SS_CXX_VER >= 17
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
struct make_pair_type_impl<std::reference_wrapper<T>> {
  using type = T&;
};

template<typename T>
using make_pair_type = typename make_pair_type_impl<decay_t<T>>::type;
}

template<typename T1, typename T2>
constexpr inline pair<detail::make_pair_type<T1>, detail::make_pair_type<T2>>
make_pair(T1&& t1, T2&& t2) {
  return pair<detail::make_pair_type<T1>, detail::make_pair_type<T2>>(ss::forward<T1>(t1), ss::forward<T2>(t2));
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
SS_CONSTEXPR_AFTER_14 inline enable_if_t<is_swappable<T1>::value && is_swappable<T2>::value>
swap(pair<T1, T2>& p1, pair<T1, T2>& p2) noexcept(noexcept(p1.swap(p2))) {
  p1.swap(p2);
}


template<typename T1, typename T2>
struct tuple_size<pair<T1, T2>> : integral_constant<size_t, 2> {};

template<size_t I, typename T1, typename T2>
struct tuple_element<I, pair<T1, T2>> {
  static_assert(I < 2, "ss::tuple_element : I must be 0 or 1");
};

template<typename T1, typename T2> struct tuple_element<0, pair<T1, T2>> { using type = T1; };
template<typename T1, typename T2> struct tuple_element<1, pair<T1, T2>> { using type = T2; };

namespace detail {
template<>
struct tuple_get<0> {
  template<typename T> static constexpr tuple_element_t<0, T> get(const T& p) noexcept { return p.first; }
  template<typename T> static constexpr tuple_element_t<0, T> get(T& p) noexcept  { return p.first; };
  template<typename T> static constexpr tuple_element_t<0, T> get(T&& p) noexcept { return ss::move(p.first); };
};

template<>
struct tuple_get<1> {
  template<typename T> static constexpr tuple_element_t<1, T> get(const T& p) noexcept { return p.second; }
  template<typename T> static constexpr tuple_element_t<1, T> get(T& p) noexcept  { return p.second; };
  template<typename T> static constexpr tuple_element_t<1, T> get(T&& p) noexcept { return ss::move(p.second); };
};
}

template<size_t I, typename T1, typename T2>
constexpr inline tuple_element_t<I, pair<T1, T2>>
get(pair<T1, T2>& p) noexcept {
  return detail::tuple_get<I>(p);
}

template<size_t I, typename T1, typename T2>
constexpr inline tuple_element_t<I, pair<T1, T2>>
get(const pair<T1, T2>& p) noexcept {
  return detail::tuple_get<I>(p);
}

template<size_t I, typename T1, typename T2>
constexpr inline tuple_element_t<I, pair<T1, T2>>
get(pair<T1, T2>&& p) noexcept {
  return detail::tuple_get<I>(p);
}

template<typename T, typename U>
constexpr inline T&
get(pair<T, U>& p) noexcept { return p.first; }

template<typename T, typename U>
constexpr inline const T&
get(const pair<T, U>& p) noexcept { return p.first; }

template<typename T, typename U>
constexpr inline T&&
get(pair<T, U>&& p) noexcept { return ss::move(p.first); }

template<typename T, typename U>
constexpr inline const T&&
get(const pair<T, U>&& p) noexcept { return ss::move(p.first); }

template<typename T, typename U>
constexpr inline T&
get(pair<U, T>& p) noexcept { return p.second; }

template<typename T, typename U>
constexpr inline const T&
get(const pair<U, T>& p) noexcept { return p.second; }

template<typename T, typename U>
constexpr inline T&&
get(pair<U, T>&& p) noexcept { return ss::move(p.second); }

template<typename T, typename U>
constexpr inline const T&&
get(const pair<U, T>&& p) noexcept { return ss::move(p.second); }

template<typename T> T& get(pair<T, T>& p) = delete;
template<typename T> const T& get(const pair<T, T>& p) = delete;
template<typename T> T&& get(pair<T, T>&& p) = delete;
template<typename T> const T&& get(const pair<T, T>&& p) = delete;


/**
 * compressed_pair
 */

namespace detail {

template<typename T, bool v = is_class<T>::value>
struct compressed_pair_base : public T {
  using type = T;
};

template<typename T>
struct compressed_pair_base<T, false> {
  using type = T;
  type value;
};

}

template<typename T, bool v = is_class<T>::value>
struct A1 : public T {
//  using compressed_
};


template<typename T1, typename T2>
class compressed_pair :
  public detail::compressed_pair_base<T1>,
  public detail::compressed_pair_base<T2>
{
 public:
  static_assert(is_empty<T1>::value + is_empty<T2>::value == 1,
    "ss::compressed_pair : One type must be empty");

  using first_type = T1;
  using second_type = T2;

 private:
  using compressed_base = ss::conditional_t<is_empty<first_type>::value,
                                             detail::compressed_pair_base<first_type>,
                                             detail::compressed_pair_base<second_type>>;

  using uncompressed_base = ss::conditional_t<is_empty<first_type>::value,
                                               detail::compressed_pair_base<second_type>,
                                               detail::compressed_pair_base<first_type>>;
  using uncompressed_base::uncompressed_base;

 public:
  using compressed_type = typename compressed_base::type;
  using uncompressed_type = typename uncompressed_base::type;
  using value_type = uncompressed_type;

  template<typename Dummy = void,
    enable_if_t<
      is_same<Dummy, void>::value &&
      detail::is_implicitly_default_constructible<value_type>::value,
    int> = 0>
  constexpr compressed_pair() noexcept(is_nothrow_default_constructible<value_type>::value)
  : uncompressed_base::value() {}

  template<typename Dummy = void,
    enable_if_t<
      is_same<Dummy, void>::value &&
      !detail::is_implicitly_default_constructible<value_type>::value,
    int> = 0>
  constexpr explicit compressed_pair() noexcept(is_nothrow_default_constructible<value_type>::value)
    : uncompressed_base::value() {}

  template<typename Dummy = void,
    enable_if_t<
      is_same<Dummy, void>::value &&
      is_copy_constructible<value_type>::value &&
      is_convertible<const value_type&, value_type>::value,
    int> = 0>
  constexpr compressed_pair(const value_type& x) noexcept(is_nothrow_copy_constructible<value_type>::value)
    : uncompressed_base::value(x) {}

};

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
