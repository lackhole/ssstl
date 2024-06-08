//
// Created by yonggyulee on 1/10/24.
//

#ifndef LSD_ALGORITHM_RANGES_IN_FOR_EACH_H_
#define LSD_ALGORITHM_RANGES_IN_FOR_EACH_H_

#include <functional>
#include <type_traits>
#include <utility>

#include "lsd/__algorithm/ranges/detail/check_input.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__algorithm/ranges/in_fun_result.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__iterator/indirectly_unary_invocable.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/borrowed_iterator_t.h"
#include "lsd/__ranges/end.h"

namespace lsd {
namespace ranges {

template<typename I, typename F>
using for_each_result = in_fun_result<I, F>;

namespace detail {

struct for_each_niebloid {
  template<typename I, typename S, typename Proj = identity, typename Fun, std::enable_if_t<
      algo_check_unary_input_iterator<indirectly_unary_invocable, I, S, Proj, Fun>::value, int> = 0>
  constexpr for_each_result<I, Fun>
  operator()(I first, S last, Fun f, Proj proj = {}) const {
    for (; first != last; ++first) {
      lsd::invoke(f, lsd::invoke(proj, *first));
    }
    return {std::move(first), std::move(f)};
  }

  template<typename R, typename Proj = identity, typename Fun, std::enable_if_t<
      algo_check_unary_input_range<indirectly_unary_invocable, R, Proj, Fun>::value, int> = 0>
  constexpr for_each_result<borrowed_iterator_t<R>, Fun>
  operator()(R&& r, Fun f, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), std::move(f), std::ref(proj));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::for_each_niebloid for_each{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_IN_FOR_EACH_H_
