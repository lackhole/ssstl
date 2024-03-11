//
// Created by yonggyulee on 1/18/24.
//

#ifndef LSD_ALGORITHM_RANGES_FIND_IF_NOT_HPP
#define LSD_ALGORITHM_RANGES_FIND_IF_NOT_HPP

#include <functional>
#include <type_traits>

#include "lsd/__algorithm/ranges/detail/check_input.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__iterator/indirect_unary_predicate.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/borrowed_iterator_t.h"
#include "lsd/__ranges/end.h"
#include "lsd/__utility/cxx20_rel_ops.h"

namespace lsd {
namespace ranges {
namespace detail {

struct find_if_not_niebloid {
  template<typename I, typename S, typename Proj = identity, typename Pred, std::enable_if_t<
      algo_check_unary_input_iterator<indirect_unary_predicate, I, S, Proj, Pred>::value, int> = 0>
  constexpr I operator()(I first, S last, Pred pred, Proj proj = {}) const {
    using namespace lsd::rel_ops;
    for (; first != last; ++first) {
      if (!lsd::invoke(pred, lsd::invoke(proj, *first))) {
        return first;
      }
    }
    return first;
  }

  template<typename R, typename Proj = identity, typename Pred, std::enable_if_t<
      algo_check_unary_input_range<indirect_unary_predicate, R, Proj, Pred>::value, int> = 0>
  constexpr borrowed_iterator_t<R>
  operator()(R&& r, Pred pred, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), std::ref(pred), std::ref(proj));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::find_if_not_niebloid find_if_not{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_FIND_IF_NOT_HPP