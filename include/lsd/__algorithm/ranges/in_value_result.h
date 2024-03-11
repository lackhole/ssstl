//
// Created by yonggyulee on 1/25/24.
//

#ifndef LSD_ALGORITHM_RANGES_IN_VALUE_RESULT_HPP
#define LSD_ALGORITHM_RANGES_IN_VALUE_RESULT_HPP

#include <type_traits>
#include <utility>

#include "lsd/__core/no_unique_address.h"
#include "lsd/__concepts/convertible_to.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {

template<typename I, typename T>
struct in_value_result {
  LSD_NO_UNIQUE_ADDRESS I in;
  LSD_NO_UNIQUE_ADDRESS T value;

  template<typename I2, typename T2, std::enable_if_t<conjunction<
      convertible_to<const I&, I2>,
      convertible_to<const T&, T2>
  >::value, int> = 0>
  constexpr operator in_value_result<I2, T2>() const & {
    return {in, value};
  }

  template<typename I2, typename T2, std::enable_if_t<conjunction<
      convertible_to<I, I2>,
      convertible_to<T, T2>
  >::value, int> = 0>
  constexpr operator in_value_result<I2, T2>() && {
    return {std::move(in), std::move(value)};
  }
};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_IN_VALUE_RESULT_HPP
