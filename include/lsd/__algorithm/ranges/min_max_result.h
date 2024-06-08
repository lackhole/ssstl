//
// Created by yonggyulee on 1/25/24.
//

#ifndef LSD_ALGORITHM_RANGES_MIN_MAX_RESULT_H_
#define LSD_ALGORITHM_RANGES_MIN_MAX_RESULT_H_

#include <type_traits>
#include <utility>

#include "lsd/__core/no_unique_address.h"
#include "lsd/__concepts/convertible_to.h"

namespace lsd {
namespace ranges {

template<typename T>
struct min_max_result {
  LSD_NO_UNIQUE_ADDRESS T min;
  LSD_NO_UNIQUE_ADDRESS T max;

  template<typename T2, std::enable_if_t<
      convertible_to<const T&, T2>::value, int> = 0>
  constexpr operator min_max_result<T2>() const & {
    return {min, max};
  }

  template<typename T2, std::enable_if_t<
      convertible_to<T, T2>::value, int> = 0>
  constexpr operator min_max_result<T2>() && {
    return {std::move(min), std::move(max)};
  }
};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_MIN_MAX_RESULT_H_
