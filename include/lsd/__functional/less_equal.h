//
// Created by YongGyu Lee on 2024/02/04.
//

#ifndef LSD_FUNCTIONAL_LESS_EQUAL_HPP
#define LSD_FUNCTIONAL_LESS_EQUAL_HPP

#include <type_traits>
#include <utility>

#include "lsd/__concepts/totally_ordered.h"
#include "lsd/__functional/less.h"

namespace lsd {
namespace ranges {

struct less_equal {
  using is_transparent = std::true_type;

  template<typename T, typename U, std::enable_if_t<totally_ordered_with<T, U>::value, int> = 0>
  constexpr bool operator()(T&& t, U&& u) const
      noexcept(noexcept(!ranges::less{}(std::forward<U>(u), std::forward<T>(t))))
  {
    return !ranges::less{}(std::forward<U>(u), std::forward<T>(t));
  }
};

} // namespace ranges
} // namespace lsd

#endif // LSD_FUNCTIONAL_LESS_EQUAL_HPP
