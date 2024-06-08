//
// Created by YongGyu Lee on 3/14/24.
//

#ifndef LSD_EXPECTED_UNEXPECT_HPP_
#define LSD_EXPECTED_UNEXPECT_HPP_

#if __cplusplus >= 202302L

#include <expected>

#else

#include "lsd/__core/inline_or_static.h"

#endif

namespace lsd {

#if __cplusplus >= 202302L

using unexpect_t = std::unexpect_t;
inline constexpr unexpect_t unexpect{};

#else

struct unexpect_t {
  explicit unexpect_t() = default;
};

LSD_INLINE_OR_STATIC constexpr unexpect_t unexpect{};

#endif

} // namespace lsd

#endif // LSD_EXPECTED_UNEXPECT_HPP_
