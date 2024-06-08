//
// Created by yonggyulee on 1/12/24.
//

#ifndef LSD_ALGORITHM_RANGES_IN_OUT_RESULT_H_
#define LSD_ALGORITHM_RANGES_IN_OUT_RESULT_H_

#include <type_traits>
#include <utility>

#include "lsd/__core/no_unique_address.h"
#include "lsd/__concepts/convertible_to.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {

template<typename I, typename O>
struct in_out_result {
  LSD_NO_UNIQUE_ADDRESS I in;
  LSD_NO_UNIQUE_ADDRESS O out;

  template<typename I2, typename O2, std::enable_if_t<conjunction<
      convertible_to<const I&, I2>,
      convertible_to<const O&, O2>
  >::value, int> = 0>
  constexpr operator in_out_result<I2, O2>() const & {
    return {in, out};
  }

  template<typename I2, typename O2, std::enable_if_t<conjunction<
      convertible_to<I, I2>,
      convertible_to<O, O2>
  >::value, int> = 0>
  constexpr operator in_out_result<I2, O2>() && {
    return {std::move(in), std::move(out)};
  }
};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_IN_OUT_RESULT_H_
