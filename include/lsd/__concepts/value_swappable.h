//
// Created by yonggyulee on 1/25/24.
//

#ifndef LSD_CONCEPTS_VALUE_SWAPPABLE_HPP
#define LSD_CONCEPTS_VALUE_SWAPPABLE_HPP

#include <type_traits>

#include "lsd/__concepts/dereferenceable.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_swappable.h"

namespace lsd {
namespace detail {

template<typename I1, typename I2, bool = conjunction<dereferenceable<I1>, dereferenceable<I2>>::value>
struct ValueSwappableImpl : std::false_type {};
template<typename I1, typename I2>
struct ValueSwappableImpl<I1, I2, true>
    : is_swappable<decltype(*std::declval<I1&>(), *std::declval<I2&>())> {};

} // namespace detail

template<typename I1, typename I2>
struct ValueSwappable : detail::ValueSwappableImpl<I1, I2> {};

} // namespace lsd

#endif // LSD_CONCEPTS_VALUE_SWAPPABLE_HPP
