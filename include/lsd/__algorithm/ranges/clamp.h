//
// Created by YongGyu Lee on 5/8/24.
//

#ifndef LSD_ALGORITHM_RANGES_CLAMP_H_
#define LSD_ALGORITHM_RANGES_CLAMP_H_

#include <utility>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__functional/less.h"
#include "lsd/__iterator/indirect_strict_weak_order.h"
#include "lsd/__iterator/projected.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

struct clamp_niebloid {
  template<typename T, typename Proj = identity, typename Comp = ranges::less, std::enable_if_t<conjunction<
      projectable<const T*, Proj>,
      indirect_strict_weak_order<Comp, projected<const T*, Proj>>
      >::value, int> = 0>
  constexpr const T& operator()(const T& v, const T& lo, const T& hi, Comp comp = {}, Proj proj = {}) const {
    auto&& pv = lsd::invoke(proj, v);

    if (lsd::invoke(comp, std::forward<decltype(pv)>(pv), lsd::invoke(proj, lo)))
      return lo;

    if (lsd::invoke(comp, lsd::invoke(proj, hi), std::forward<decltype(pv)>(pv)))
      return hi;

    return v;
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::clamp_niebloid clamp{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_CLAMP_H_
