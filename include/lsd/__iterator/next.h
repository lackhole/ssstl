//
// Created by cosge on 2024-01-13.
//

#ifndef LSD_ITERATOR_NEXT_H_
#define LSD_ITERATOR_NEXT_H_

#include <type_traits>

#include "lsd/__core/inline_variable.h"
#include "lsd/__iterator/advance.h"
#include "lsd/__iterator/input_or_output_iterator.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__iterator/sentinel_for.h"

namespace lsd {
namespace ranges {
namespace detail {

struct next_niebloid {
  template<typename I>
  constexpr std::enable_if_t<input_or_output_iterator<I>::value, I>
  operator()(I i) const {
    ++i;
    return i;
  }

  template<typename I, std::enable_if_t<input_or_output_iterator<I>::value, int> = 0>
  constexpr I operator()(I i, iter_difference_t<I> n) const {
    ranges::advance(i, n);
    return i;
  }

  template<typename I, typename S, std::enable_if_t<conjunction<
      input_or_output_iterator<I>,
      sentinel_for<S, I>
  >::value, int> = 0>
  constexpr I operator()(I i, S bound) const {
    ranges::advance(i, bound);
    return i;
  }

  template<typename I, typename S, std::enable_if_t<conjunction<
      input_or_output_iterator<I>,
      sentinel_for<S, I>
  >::value, int> = 0>
  constexpr I operator()(I i, iter_difference_t<I> n, S bound) const {
    ranges::advance(i, n, bound);
    return i;
  }
};

} // namespace detail

namespace niebloid {

LSD_INLINE_VARIABLE constexpr detail::next_niebloid next{};

} // namespace niebloid
using namespace niebloid;

} // namespace ranges
} // namespace lsd

#endif // LSD_ITERATOR_NEXT_H_
