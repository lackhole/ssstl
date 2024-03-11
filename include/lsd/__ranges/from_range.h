//
// Created by yonggyulee on 2024/01/06.
//

#ifndef LSD_RANGES_FROM_RANGE_HPP_
#define LSD_RANGES_FROM_RANGE_HPP_

#if __cplusplus >= 202302L
#include <ranges>
#endif

#include "lsd/__core/inline_or_static.h"


namespace lsd {
namespace ranges {

#if __cplusplus >= 202302L
using from_range_t = std::ranges::from_range_t;
#else
struct from_range_t {
  explicit from_range_t() = default;
};
#endif

LSD_INLINE_OR_STATIC constexpr from_range_t from_range{};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_FROM_RANGE_HPP_
