//
// Created by YongGyu Lee on 4/15/24.
//

#ifndef LSD_ALGORITHM_RANGES_CONTAINS_H_
#define LSD_ALGORITHM_RANGES_CONTAINS_H_

#include <type_traits>
#include <utility>

#include "lsd/__algorithm/ranges/find.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__functional/equal_to.h"
#include "lsd/__functional/identity.h"
#include "lsd/__iterator/forward_iterator.h"
#include "lsd/__iterator/indirectly_comparable.h"
#include "lsd/__iterator/indirect_binary_predicate.h"
#include "lsd/__iterator/input_iterator.h"
#include "lsd/__iterator/projected.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/forward_range.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {

namespace detail {

struct contains_niebloid {
  template<typename I, typename S, typename T, typename Proj = identity, std::enable_if_t<conjunction<
      input_iterator<I>,
      sentinel_for<S, I>,
      projectable<I, Proj>,
      indirect_binary_predicate<ranges::equal_to, projected<I, Proj>, const T*>
  >::value, int> = 0>
  constexpr bool operator()(I first, S last, const T& value, Proj proj = {}) const {
    return ranges::find(std::move(first), last, value, proj) != last;
  }

  template<typename R, typename T, typename Proj = identity, std::enable_if_t<conjunction<
      input_range<R>,
      projectable<iterator_t<R>, Proj>,
      indirect_binary_predicate<ranges::equal_to, projected<iterator_t<R>, Proj>, const T*>
  >::value, int> = 0>
  constexpr bool operator()(R&& r, const T& value, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), std::move(value), proj);
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::contains_niebloid contains{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_CONTAINS_H_
