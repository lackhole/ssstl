# /*
#  * Created by YongGyu Lee on 2021/08/14.
#  */
#
# ifndef SS_DETAIL_TUPLE_HELPER_H_
# define SS_DETAIL_TUPLE_HELPER_H_
#
# include <cstddef>
#
# include "ss/type_traits.h"

namespace ss {

template<typename T>
struct tuple_size;

namespace detail {
template<typename T, typename = void>
struct test_tuple_size {};

template<typename T>
struct test_tuple_size<T, void_t<decltype(tuple_size<T>::value)>>
  : integral_constant<size_t, tuple_size<T>::value> {};
} // namespace detail

template<typename T>
struct tuple_size<const T> : detail::test_tuple_size<T> {};

template<typename T>
struct tuple_size<volatile T> : detail::test_tuple_size<T> {};

template<typename T>
struct tuple_size<const volatile T> : detail::test_tuple_size<T> {};

# if SS_CXX_VER >= 14
template<typename T>
constexpr size_t tuple_size_v = tuple_size<T>::value;
# endif

template<size_t I, typename T>
struct tuple_element;

template<size_t I, typename T>
using tuple_element_t = typename tuple_element<I, T>::type;

template<size_t I, typename T>
struct tuple_element<I, const T> {
  using type = add_const_t<tuple_element_t<I, T>>;
};

template<size_t I, typename T>
struct tuple_element<I, volatile T> {
  using type = add_volatile_t<tuple_element_t<I, T>>;
};

template<size_t I, typename T>
struct tuple_element<I, const volatile T> {
  using type = add_cv_t<tuple_element_t<I, T>>;
};

namespace detail {

template<size_t I>
struct tuple_get {
  template<typename T> static constexpr       tuple_element_t<I, T>&  get(const T& t) noexcept;
  template<typename T> static constexpr const tuple_element_t<I, T>&  get(T& t) noexcept;
  template<typename T> static constexpr       tuple_element_t<I, T>&& get(T&& t) noexcept;
};

} // namespace detail

} // namespace ss

#endif // SS_DETAIL_TUPLE_HELPER_H_
