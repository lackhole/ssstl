//
// Created by YongGyu Lee on 5/8/24.
//

#ifndef LSD_UTILITY_IN_RANGE_HPP_
#define LSD_UTILITY_IN_RANGE_HPP_

#include <limits>

#include "lsd/__utility/cmp.h"

namespace lsd {

template<typename R, typename T>
constexpr bool in_range(T t) noexcept {
  return lsd::cmp_greater_equal(t, (std::numeric_limits<R>::min)()) &&
         lsd::cmp_less_equal(t, (std::numeric_limits<R>::max)());
}

} // namespace lsd

#endif // LSD_UTILITY_IN_RANGE_HPP_
