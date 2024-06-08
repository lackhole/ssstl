//
// Created by cosge on 2024-01-27.
//

#ifndef LSD_RANGES_CONST_ITERATOR_T_H_
#define LSD_RANGES_CONST_ITERATOR_T_H_

#include <type_traits>

#include "lsd/__ranges/cbegin.h"
#include "lsd/__ranges/range.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename T, bool = range<T>::value, typename = void>
struct const_iterator_impl {};

template<typename T>
struct const_iterator_impl<T, true, void_t<decltype( ranges::cbegin(std::declval<T&>()) )>> {
  using type = decltype(ranges::cbegin(std::declval<T&>()));
};

} // namespace detail

template<typename T>
struct const_iterator : detail::const_iterator_impl<T> {};

template<typename T>
using const_iterator_t = typename const_iterator<T>::type;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_CONST_ITERATOR_T_H_
