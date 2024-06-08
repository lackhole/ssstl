//
// Created by YongGyu Lee on 2024/02/04.
//

#ifndef LSD_FUNCTIONAL_NOT_EQUAL_TO_H_
#define LSD_FUNCTIONAL_NOT_EQUAL_TO_H_

#include <type_traits>
#include <utility>

#include "lsd/__concepts/equality_comparable.h"
#include "lsd/__functional/equal_to.h"

namespace lsd {
namespace ranges {

struct not_equal_to {
  using is_transparent = std::true_type;

  template<typename T, typename U, std::enable_if_t<equality_comparable_with<T, U>::value, int> = 0>
  constexpr bool operator()(T&& t, U&& u) const
      noexcept(noexcept(!ranges::equal_to{}(std::forward<T>(t), std::forward<U>(u))))
  {
    return !ranges::equal_to{}(std::forward<T>(t), std::forward<U>(u));
  }
};

} // namespace ranges
} // namespace lsd

#endif // LSD_FUNCTIONAL_NOT_EQUAL_TO_H_
