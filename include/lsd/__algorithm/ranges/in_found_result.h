//
// Created by yonggyulee on 1/25/24.
//

#ifndef LSD_ALGORITHM_RANGES_IN_FOUND_RESULT_H_
#define LSD_ALGORITHM_RANGES_IN_FOUND_RESULT_H_

#include <type_traits>
#include <utility>

#include "lsd/__core/no_unique_address.h"
#include "lsd/__concepts/convertible_to.h"

namespace lsd {
namespace ranges {

template<typename I>
struct in_found_result {
  LSD_NO_UNIQUE_ADDRESS I in;
  LSD_NO_UNIQUE_ADDRESS bool found;

  template<typename I2, std::enable_if_t<
      convertible_to<const I&, I2>::value, int> = 0>
  constexpr operator in_found_result<I2>() const & {
    return {in, found};
  }

  template<typename I2, std::enable_if_t<
      convertible_to<I, I2>::value, int> = 0>
  constexpr operator in_found_result<I2>() && {
    return {std::move(in), found};
  }
};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_IN_FOUND_RESULT_H_
