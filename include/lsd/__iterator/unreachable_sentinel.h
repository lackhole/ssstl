//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_ITERATOR_UNREACHABLE_SENTINEL_H_
#define LSD_ITERATOR_UNREACHABLE_SENTINEL_H_

#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/weakly_incrementable.h"

namespace lsd {

struct unreachable_sentinel_t {
  template<typename I>
  friend constexpr std::enable_if_t<weakly_incrementable<I>::value, bool>
  operator==(unreachable_sentinel_t, const I&) noexcept {
    return false;
  }
};

LSD_INLINE_OR_STATIC constexpr unreachable_sentinel_t unreachable_sentinel{};

} // namespace lsd

#endif // LSD_ITERATOR_UNREACHABLE_SENTINEL_H_
