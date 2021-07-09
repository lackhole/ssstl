#include <iostream>

#include "ss/type_traits.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif

// helpers for testing

#define sa(...) static_assert(__VA_ARGS__, " ");

template<typename T, typename = void>
struct has_typename_type : ss::false_type {};

template<typename T>
struct has_typename_type<T, ss::void_t<typename T::type>> : ss::true_type {};

template<typename T>
using has_typename_type_t = typename has_typename_type<T>::type;

template<typename T> using is_false_t = ss::is_same<T, ss::false_type>;
template<typename T> using is_true_t = ss::is_same<T, ss::true_type>;

using false_t = ss::false_type;
using true_t = ss::true_type;
using i0 = ss::integral_constant<int, 0>;
using i1 = ss::integral_constant<int, 1>;
using i2 = ss::integral_constant<int, 2>;
using i3 = ss::integral_constant<int, 3>;
using i4 = ss::integral_constant<int, 4>;
using i5 = ss::integral_constant<int, 5>;
using i6 = ss::integral_constant<int, 6>;
using i7 = ss::integral_constant<int, 7>;
using i8 = ss::integral_constant<int, 8>;
using i9 = ss::integral_constant<int, 9>;

int main() {
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  { // test 'test helpers'
    struct foo { using type = void; };
    struct bar {};
    sa(has_typename_type_t<foo>::value == true)
    sa(has_typename_type_t<bar>::value == false)
    sa(is_true_t<ss::true_type>::value == true)
    sa(is_true_t<ss::false_type>::value == false)
    sa(is_false_t<ss::true_type>::value == false)
    sa(is_false_t<ss::false_type>::value == true)
  }


  // conjunction
  sa(ss::conjunction<>::value == true)
  sa(is_true_t<typename ss::conjunction<>::type>::value == true)
  sa(ss::conjunction<true_t, true_t, true_t>::value == true)
  sa(ss::conjunction<false_t, false_t, false_t>::value == false)
  sa(ss::conjunction<false_t, false_t, false_t, true_t>::value == false)
  sa(ss::conjunction<false_t, void, void()&&>::value == false)

  // disjunction
  sa(ss::disjunction<>::value == false)
  sa(is_false_t<typename ss::disjunction<>::type>::value == true)
  sa(ss::disjunction<false_t>::value == false)
  sa(ss::disjunction<false_t, false_t>::value == false)
  sa(ss::disjunction<false_t, false_t, false_t, true_t>::value == true)
  sa(ss::disjunction<true_t>::value == true)
  sa(ss::disjunction<i0, i0, i1, i2>::value == 1)

# if SS_CXX_VER >= 14
  sa(ss::disjunction_v<> == false)
  sa(ss::disjunction_v<false_t> == false)
  sa(ss::disjunction_v<false_t, false_t> == false)
  sa(ss::disjunction_v<false_t, false_t, true_t> == true)
  sa(ss::disjunction_v<i0, i0, i1, i2> == 1)
# endif

  // negation
  static_assert(ss::negation<false_t>::value == true, " ");
  static_assert(ss::negation<true_t>::value == false, " ");
# if SS_CXX_VER >= 14
  static_assert(ss::negation<false_t>::value == ss::negation_v<false_t>, " ");
  static_assert(ss::negation<true_t>::value == ss::negation_v<true_t>, " ");
# endif

  return 0;
}
