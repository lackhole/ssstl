//
// Created by YongGyu Lee on 2/22/24.
//

#ifndef LSD_UTILITY_KEY_VALUE_HPP
#define LSD_UTILITY_KEY_VALUE_HPP

#include <cstddef>
#include <tuple>
#include <utility>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__tuple/tuple_like.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

template<std::size_t I>
struct element_niebloid {
  template<typename T, std::enable_if_t<conjunction<
      tuple_like<T>,
      internal::tuple_size_greater_than<remove_cvref_t<T>, I>
  >::value, int> = 0>
  constexpr decltype(auto) operator()(T&& t) const noexcept {
    return std::get<I>(std::forward<T>(t));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::element_niebloid<0> key;
LSD_INLINE_OR_STATIC constexpr detail::element_niebloid<0> first;
LSD_INLINE_OR_STATIC constexpr detail::element_niebloid<1> value;
LSD_INLINE_OR_STATIC constexpr detail::element_niebloid<1> second;

template<std::size_t I>
LSD_INLINE_OR_STATIC constexpr detail::element_niebloid<I> element;

} // namespace lsd


#endif // LSD_UTILITY_KEY_VALUE_HPP
