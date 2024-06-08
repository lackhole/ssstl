//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_ALGORITHM_RANGES_MISMATCH_H_
#define LSD_ALGORITHM_RANGES_MISMATCH_H_

#include <type_traits>
#include <functional>

#include "lsd/__algorithm/ranges/in_in_result.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__functional/equal_to.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__iterator/indirectly_comparable.h"
#include "lsd/__iterator/input_iterator.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/borrowed_iterator_t.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {

template<typename I1, typename I2>
using mismatch_result = in_in_result<I1, I2>;

namespace detail {

struct mismatch_niebloid {
  template<
      typename I1, typename S1,
      typename I2, typename S2,
      typename Pred = equal_to,
      typename Proj1 = identity, typename Proj2 = identity,
      std::enable_if_t<conjunction<
          input_iterator<I1>, sentinel_for<S1, I1>,
          input_iterator<I2>, sentinel_for<S2, I1>,
          indirectly_comparable<I1, I2, Pred, Proj1, Proj2>
      >::value, int> = 0
  >
  constexpr mismatch_result<I1, I2>
  operator()(I1 first1, S1 last1, I2 first2, S2 last2, Pred pred = {}, Proj1 proj1 = {}, Proj2 proj2 = {}) const {
    for (; first1 != last1 && first2 != last2; ++first1, (void)++first2) {
      if (!lsd::invoke(pred, lsd::invoke(proj1, *first1), lsd::invoke(proj2, *first2))) {
        break;
      }
    }
    return {first1, first2};
  }

  template<typename R1, typename R2, typename Pred = equal_to, typename Proj1 = identity, typename Proj2 = identity>
  constexpr mismatch_result<borrowed_iterator_t<R1>, borrowed_iterator_t<R2>>
  operator()(R1&& r1, R2&& r2, Pred pred = {}, Proj1 proj1 = {}, Proj2 proj2 = {}) const {
    return (*this)(
        ranges::begin(r1), ranges::end(r1), ranges::begin(r2), ranges::end(r2),
        std::ref(pred), std::ref(proj1), std::ref(proj2));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::mismatch_niebloid mismatch{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_MISMATCH_H_
