//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_ALGORITHM_RANGES_IN_FOR_EACH_N_H_
#define LSD_ALGORITHM_RANGES_IN_FOR_EACH_N_H_

#include <functional>
#include <type_traits>
#include <utility>

#include "lsd/__core/inline_variable.h"
#include "lsd/__algorithm/ranges/in_fun_result.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__iterator/indirectly_unary_invocable.h"
#include "lsd/__iterator/input_iterator.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__iterator/projected.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {

template<typename I, typename F>
using for_each_n_result = in_fun_result<I, F>;

namespace detail {

struct for_each_n_niebloid {
 private:
  template<typename I, typename Proj, typename Fun, bool = projectable<I, Proj>::value /* false */>
  struct check : std::false_type {};
  template<typename I, typename Proj, typename Fun>
  struct check<I, Proj, Fun, true> : indirectly_unary_invocable<Fun, projected<I, Proj>> {};

 public:
  template<typename I, typename Proj = identity, typename Fun, std::enable_if_t<conjunction<
      input_iterator<I>,
      check<I, Proj, Fun>
  >::value, int> = 0>
  constexpr for_each_n_result<I, Fun>
  operator()(I first, iter_difference_t<I> n, Fun f, Proj proj = {}) const {
    for (; n-- > 0; ++first) {
      lsd::invoke(f, lsd::invoke(proj, *first));
    }
    return {std::move(first), std::move(f)};
  }
};

} // namespace detail

LSD_INLINE_VARIABLE constexpr detail::for_each_n_niebloid for_each_n{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_IN_FOR_EACH_N_H_
