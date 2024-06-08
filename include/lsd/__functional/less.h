//
// Created by YongGyu Lee on 2024/01/03.
//

#ifndef LSD_FUNCTIONAL_LESS_H_
#define LSD_FUNCTIONAL_LESS_H_

#include <type_traits>
#include <utility>

#include "lsd/__concepts/totally_ordered.h"
#include "lsd/__utility/cxx20_rel_ops.h"

namespace lsd {
namespace ranges {

struct less {
  using is_transparent = std::true_type;

  template<typename T, typename U, std::enable_if_t<totally_ordered_with<T, U>::value, int> = 0>
  constexpr bool operator()(T&& t, U&& u) const
      noexcept(noexcept(bool(std::forward<T>(t) < std::forward<U>(u))))
  {
    using namespace lsd::rel_ops;
    return std::forward<T>(t) < std::forward<U>(u);
  }
};

} // namespace ranges
} // namespace lsd

#endif // LSD_FUNCTIONAL_LESS_H_
