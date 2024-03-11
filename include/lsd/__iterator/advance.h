//
// Created by cosge on 2023-12-25.
//

#ifndef LSD_ITERATOR_ADVANCE_HPP_
#define LSD_ITERATOR_ADVANCE_HPP_

#include <type_traits>

#include "lsd/core.h"
#include "lsd/__concepts/assignable_from.h"
#include "lsd/__iterator/bidirectional_iterator.h"
#include "lsd/__iterator/input_or_output_iterator.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__iterator/random_access_iterator.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__iterator/sized_sentinel_for.h"
#include "lsd/__type_traits/detail/tag.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/negation.h"

namespace lsd {
namespace ranges {
namespace detail {

struct advance_niebloid;
using lsd::detail::conditional_tag;
using lsd::detail::tag_1;
using lsd::detail::tag_2;
using lsd::detail::tag_3;
using lsd::detail::tag_else;

template<typename I>
using advance_n_tag = conditional_tag<random_access_iterator<I>, bidirectional_iterator<I>>;

template<typename I>
constexpr void advance_n(I& i, iter_difference_t<I> n, tag_1 /* random_access_iterator */) {
  i += n;
}

template<typename I>
constexpr void advance_n(I& i, iter_difference_t<I> n, tag_2 /* bidirectional_iterator */) {
  while (n > 0) {
    --n;
    ++i;
  }

  while (n < 0) {
    ++n;
    --i;
  }
}

template<typename I>
constexpr void advance_n(I& i, iter_difference_t<I> n, tag_else) {
  while (n > 0) {
    --n;
    ++i;
  }
}

template<typename I, typename S>
struct advance_bound_check_impl : conjunction<input_or_output_iterator<I>, sentinel_for<S, I>> {};

template<typename I, typename S, bool = has_typename_type<iter_difference<I>>::value /* true */>
struct advance_bound_check : conjunction< negation<std::is_same<iter_difference_t<I>, S>>,
                                          advance_bound_check_impl<I, S>                  > {};
template<typename I, typename S>
struct advance_bound_check<I, S, false> : advance_bound_check_impl<I, S> {};

template<typename I, typename S>
using advance_bound_tag = conditional_tag<assignable_from<I&, S>, sized_sentinel_for<S, I>>;

template<typename I, typename S>
constexpr void advance_bound(I& i, S bound, tag_1 /* assignable_from */) {
  i = std::move(bound);
}

template<typename I, typename S>
constexpr void advance_bound(I& i, S bound, tag_2 /* sized_sentinel_for */);

template<typename I, typename S>
constexpr void advance_bound(I& i, S bound, tag_else) {
  while (i != bound)
    ++i;
}


template<typename I, typename S>
using advance_mixed_tag = conditional_tag<sized_sentinel_for<S, I>, bidirectional_iterator<I>>;

template<typename I, typename S>
constexpr iter_difference_t<I>
advance_mixed(I& i, iter_difference_t<I> n, S bound, tag_1 /* sized_sentinel_for */);

template<typename I, typename S>
constexpr iter_difference_t<I>
advance_mixed(I& i, iter_difference_t<I> n, S bound, tag_2 /* bidirectional_iterator */) {
  while (n > 0 && i != bound) {
    --n;
    ++i;
  }

  while (n < 0 && i != bound) {
    ++n;
    --i;
  }

  return n;
}

template<typename I, typename S>
constexpr iter_difference_t<I>
advance_mixed(I& i, iter_difference_t<I> n, S bound, tag_else) {
  while (n > 0 && i != bound) {
    --n;
    ++i;
  }

  return n;
}

struct advance_niebloid {
  template<typename I>
  constexpr std::enable_if_t<input_or_output_iterator<I>::value>
  operator()(I& i, iter_difference_t<I> n) const {
    advance_n(i, n, advance_n_tag<I>{});
  }


  // Subsumes above
  template<typename I, typename S>
  constexpr std::enable_if_t<advance_bound_check<I, S>::value>
  operator()(I& i, S bound) const {
    advance_bound(i, bound, advance_bound_tag<I, S>{});
  }


  template<typename I, typename S, std::enable_if_t<conjunction<
      input_or_output_iterator<I>,
      sentinel_for<S, I>
  >::value, int> = 0>
  constexpr iter_difference_t<I>
  operator()(I& i, iter_difference_t<I> n, S bound) const {
    return advance_mixed(i, n, bound, advance_mixed_tag<I, S>{});
  }
};
} // namespace detail

inline namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::advance_niebloid advance{};

} // inline namespace niebloid

namespace detail {

template<typename I, typename S>
constexpr void advance_bound(I& i, S bound, tag_2 /* sized_sentinel_for */) {
  ranges::advance(i, bound - i);
}

template<typename I, typename S>
constexpr iter_difference_t<I>
advance_mixed(I& i, iter_difference_t<I> n, S bound, tag_1 /* sized_sentinel_for */) {
  const iter_difference_t<I> d = bound - i;
  if ((n < 0 && n <= d) || (n > 0 && n >= d)) {
    ranges::advance(i, d);
    return n - d;
  }

  ranges::advance(i, n);
  return 0;
}

} // namespace detail
} // namespace ranges
} // namespace lsd

#endif // LSD_ITERATOR_ADVANCE_HPP_
