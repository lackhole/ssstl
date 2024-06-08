//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_ALGORITHM_RANGES_COUNT_H_
#define LSD_ALGORITHM_RANGES_COUNT_H_

#include <functional>
#include <type_traits>

#include "lsd/__algorithm/ranges/detail/check_input.h"
#include "lsd/__core/inline_variable.h"
#include "lsd/__functional/equal_to.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__iterator/indirect_binary_predicate.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/range_difference_t.h"
#include "lsd/__utility/cxx20_rel_ops.h"

namespace lsd {
namespace ranges {
namespace detail {

struct count_niebloid {
  template<typename I, typename S, typename T, typename Proj = identity, std::enable_if_t<
      algo_check_binary_input_iterator<indirect_binary_predicate, I, S, const T*, Proj, ranges::equal_to>
  ::value, int> = 0>
  constexpr iter_difference_t<I> operator()(I first, S last, const T& value, Proj proj = {}) const {
    using namespace lsd::rel_ops;

    iter_difference_t<I> counter = 0;

    for (; first != last; ++first) {
      if (lsd::invoke(proj, *first) == value) {
        ++counter;
      }
    }

    return counter;
  }

  template<typename R, typename T, typename Proj = identity, std::enable_if_t<
      algo_check_binary_input_range<indirect_binary_predicate, R, const T*, Proj, ranges::equal_to>::value, int> = 0>
  constexpr range_difference_t<R>
  operator()(R&& r, const T& value, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), value, std::ref(proj));
  }
};

} // namespace detail

LSD_INLINE_VARIABLE constexpr detail::count_niebloid count{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_COUNT_H_
