//
// Created by yonggyulee on 2024/01/13.
//

#ifndef LSD_RANGES_RANGE_KEY_T_HPP
#define LSD_RANGES_RANGE_KEY_T_HPP

#include <tuple>
#include <type_traits>

#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/range_value_t.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename T, typename = void>
struct has_first_type : std::false_type {};
template<typename T>
struct has_first_type<T, void_t<typename T::first_type>> : std::true_type {};

template<typename T, typename = void>
struct has_first_tuple_element : std::false_type {};
template<typename T>
struct has_first_tuple_element<T, void_t<std::tuple_element_t<0, T>>> : std::true_type {};

template<typename RV, bool = has_first_type<RV>::value, bool = has_first_tuple_element<RV>::value>
struct guide_key {};
template<typename RV, bool v>
struct guide_key<RV, true, v> {
  using type = std::remove_const_t< typename RV::first_type >;
};
template<typename RV>
struct guide_key<RV, false, true> {
  using type = std::remove_const_t< std::tuple_element_t<0, RV> >;
};

template<typename R, bool = input_range<R>::value /* false */>
struct range_key_impl {};
template<typename R>
struct range_key_impl<R, true> : guide_key<range_value_t<R>> {};

} // namespace ranges

template<typename R>
struct range_key : detail::range_key_impl<R> {};

template<typename R>
using range_key_t = typename range_key<R>::type;

} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_RANGE_KEY_T_HPP
