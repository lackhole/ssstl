//
// Created by YongGyu Lee on 4/12/24.
//

#ifndef LSD_ALGORITHM_RANGES_FIND_FIRST_OF_H_
#define LSD_ALGORITHM_RANGES_FIND_FIRST_OF_H_

#include <type_traits>
#include <utility>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/indirectly_comparable.h"
#include "lsd/__iterator/input_iterator.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__functional/equal_to.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/borrowed_iterator_t.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/forward_range.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

struct find_first_of_niebloid {
  template<typename I1, typename S1,
           typename I2, typename S2,
           typename Pred = ranges::equal_to,
           typename Proj1 = identity,
           typename Proj2 = identity,
           std::enable_if_t<conjunction<
               input_iterator<I1>, sentinel_for<S1, I1>,
               forward_iterator<I2>, sentinel_for<S2, I2>,
               indirectly_comparable<I1, I2, Pred, Proj1, Proj2>
           >::value, int> = 0>
  constexpr I1 operator()(I1 first1, S1 last1, I2 first2, S2 last2, Pred pred = {}, Proj1 proj1 = {}, Proj2 proj2 = {}) const {
    for (; first1 != last1; ++first1) {
      for (auto it = first2; it != last2; ++it) {
        if (lsd::invoke(pred, lsd::invoke(proj1, *first1), lsd::invoke(proj2, *it))) {
          return first1;
        }
      }
    }

    return first1;
  }

  template<typename R1, typename R2,
           typename Pred = ranges::equal_to, typename Proj1 = identity, typename Proj2 = identity,
           std::enable_if_t<conjunction<
               input_range<R1>, forward_range<R2>,
               indirectly_comparable<iterator_t<R1>, iterator_t<R2>, Pred, Proj1, Proj2>
           >::value, int> = 0>
  constexpr borrowed_iterator_t<R1> operator()(R1&& r1, R2&& r2, Pred pred = {}, Proj1 proj1 = {}, Proj2 proj2 = {}) const {
    return (*this)(ranges::begin(r1), ranges::end(r1), ranges::begin(r2), ranges::end(r2), std::move(pred), std::move(proj1), std::move(proj2));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::find_first_of_niebloid find_first_of{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_FIND_FIRST_OF_H_
