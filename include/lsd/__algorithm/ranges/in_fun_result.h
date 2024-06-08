//
// Created by yonggyulee on 1/10/24.
//

#ifndef LSD_ALGORITHM_RANGES_IN_FUN_RESULT_H_
#define LSD_ALGORITHM_RANGES_IN_FUN_RESULT_H_

#include <type_traits>
#include <utility>

#include "lsd/__core/no_unique_address.h"
#include "lsd/__concepts/convertible_to.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {

template<typename I, typename F>
struct in_fun_result {
  LSD_NO_UNIQUE_ADDRESS I in;
  LSD_NO_UNIQUE_ADDRESS F fun;

  template<typename I2, typename F2, std::enable_if_t<conjunction<
      convertible_to<const I&, I2>,
      convertible_to<const F&, F2>
  >::value, int> = 0>
  constexpr operator in_fun_result<I2, F2>() const & {
    return {in, fun};
  }

  template<typename I2, typename F2, std::enable_if_t<conjunction<
      convertible_to<const I&, I2>,
      convertible_to<const F&, F2>
  >::value, int> = 0>
  constexpr operator in_fun_result<I2, F2>() && {
    return {std::move(in), std::move(fun)};
  }
};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_IN_FUN_RESULT_H_
