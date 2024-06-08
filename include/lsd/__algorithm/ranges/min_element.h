//
// Created by YongGyu Lee on 01/08/24.
//

#ifndef LSD_ALGORITHM_RANGES_MIN_ELEMENT_H_
#define LSD_ALGORITHM_RANGES_MIN_ELEMENT_H_

#include "lsd/__algorithm/ranges/detail/check_input.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__functional/less.h"
#include "lsd/__iterator/indirect_strict_weak_order.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/borrowed_iterator_t.h"
#include "lsd/__ranges/end.h"

namespace lsd {
namespace ranges {
namespace detail {

struct min_element_niebloid {
  template<typename I, typename S, typename Proj = identity, typename Comp = ranges::less, std::enable_if_t<
      algo_check_unary_input_iterator<indirect_strict_weak_order, I, S, Proj, Comp>
  ::value, int> = 0>
  constexpr I operator()(I first, S last, Comp comp = {}, Proj proj = {}) const {
    if (first == last)
      return last;

    auto it = first;
    for (++first; first != last; ++first) {
      if (lsd::invoke(comp, lsd::invoke(proj, *first), lsd::invoke(proj, *it)))
        it = first;
    }
    return it;
  }

  template<typename R, typename Proj = identity, typename Comp = less, std::enable_if_t<
      algo_check_unary_input_range<indirect_strict_weak_order, R, Proj, Comp>
  ::value, int> = 0>
  constexpr borrowed_iterator_t<R>
  operator()(R&& r, Comp comp = {}, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), comp, proj);
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::min_element_niebloid min_element{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_MIN_ELEMENT_H_
