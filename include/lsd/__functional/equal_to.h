//
// Created by YongGyu Lee on 2024/01/12.
//

#ifndef LSD_FUNCTIONAL_EQUAL_TO_HPP
#define LSD_FUNCTIONAL_EQUAL_TO_HPP

#include <type_traits>
#include <utility>

#include "lsd/__concepts/equality_comparable.h"
#include "lsd/__utility/cxx20_rel_ops.h"

namespace lsd {
namespace ranges {

struct equal_to {
  using is_transparent = std::true_type;

  template<typename T, typename U, std::enable_if_t<equality_comparable_with<T, U>::value, int> = 0>
  constexpr bool operator()(T&& t, U&& u) const
      noexcept(noexcept(bool(std::forward<T>(t) == std::forward<U>(u))))
  {
    return std::forward<T>(t) == std::forward<U>(u);
  }
};

} // namespace ranges
} // namespace lsd

#endif // LSD_FUNCTIONAL_EQUAL_TO_HPP
