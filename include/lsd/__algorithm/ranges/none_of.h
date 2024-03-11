//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_ALGORITHM_RANGES_NONE_OF_HPP
#define LSD_ALGORITHM_RANGES_NONE_OF_HPP

#include <functional>
#include <type_traits>

#include "lsd/__algorithm/ranges/detail/check_input.h"
#include "lsd/__algorithm/ranges/find_if.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__functional/identity.h"
#include "lsd/__iterator/indirect_unary_predicate.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/end.h"

namespace lsd {
namespace ranges {
namespace detail {

struct none_of_niebloid {
  template<typename I, typename S, typename Proj = identity, typename Pred, std::enable_if_t<
      algo_check_unary_input_iterator<indirect_unary_predicate, I, S, Proj, Pred>
  ::value, int> = 0>
  constexpr bool operator()(I first, S last, Pred pred, Proj proj = {}) const {
    return ranges::find_if(first, last, std::ref(pred), std::ref(proj)) == last;
  }

  template<typename R, typename Proj = identity, typename Pred, std::enable_if_t<
      algo_check_unary_input_range<indirect_unary_predicate, R, Proj, Pred>
  ::value, int> = 0>
  constexpr bool operator()(R&& r, Pred pred, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), std::ref(pred), std::ref(proj));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::none_of_niebloid none_of{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_NONE_OF_HPP
