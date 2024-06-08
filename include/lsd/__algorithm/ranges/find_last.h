//
// Created by YongGyu Lee on 4/11/24.
//

#ifndef LSD_ALGORITHM_RANGES_FIND_LAST_H_
#define LSD_ALGORITHM_RANGES_FIND_LAST_H_

#include <functional>
#include <type_traits>

#include "lsd/__algorithm/ranges/detail/check_input.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/forward_iterator.h"
#include "lsd/__iterator/indirect_binary_predicate.h"
#include "lsd/__iterator/indirect_unary_predicate.h"
#include "lsd/__iterator/next.h"
#include "lsd/__iterator/projected.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__functional/equal_to.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/borrowed_subrange_t.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/forward_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/subrange.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

struct find_last_niebloid {
  template<typename I, typename S, typename T, typename Proj = identity, std::enable_if_t<conjunction<
      input_iterator<I>,
      sentinel_for<S, I>,
      projectable<I, Proj>,
      indirect_binary_predicate<equal_to, projected<I, Proj>, const T*>
  >::value, int> = 0>
  constexpr subrange<I> operator()(I first, S last, const T& value, Proj proj = {}) const {
    I found{};

    for (; first != last; ++first) {
      if (lsd::invoke(proj, *first) == value)
        found = first;
    }

    if (found == I {})
      return {first, first};

    return {found, ranges::next(found, last)};
  }

  template<typename R, typename T, typename Proj = identity, std::enable_if_t<conjunction<
      input_range<R>,
      projectable<iterator_t<R>, Proj>,
      indirect_binary_predicate<equal_to, projected<iterator_t<R>, Proj>, const T*>
  >::value, int> = 0>
  constexpr borrowed_subrange_t<R> operator()(R&& r, const T& value, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), value, std::ref(proj));
  }
};

struct find_last_if_niebloid {
  template<typename I, typename S, typename Proj = identity, typename Pred, std::enable_if_t<conjunction<
      forward_iterator<I>,
      sentinel_for<S, I>,
      projectable<I, Proj>,
      indirect_unary_predicate<Pred, projected<I, Proj>>
  >::value, int> = 0>
  constexpr subrange<I> operator()(I first, S last, Pred pred, Proj proj = {}) const {
    I found{};
    for (; first != last; ++first) {
      if (lsd::invoke(pred, lsd::invoke(proj, *first))) {
        found = first;
      }
    }

    if (found == I {})
      return {first, first};

    return {found, ranges::next(found, last)};
  }

  template<typename R, typename Proj = identity, typename Pred, std::enable_if_t<conjunction<
      forward_range<R>,
      projectable<iterator_t<R>, Proj>,
      indirect_unary_predicate<Pred, projected<iterator_t<R>, Proj>>
  >::value, int> = 0>
  constexpr borrowed_subrange_t<R> operator()(R&& r, Pred pred, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), std::ref(pred), std::ref(proj));
  }
};

struct find_last_if_not_niebloid {
  template<typename I, typename S, typename Proj = identity, typename Pred, std::enable_if_t<conjunction<
      forward_iterator<I>,
      sentinel_for<S, I>,
      projectable<I, Proj>,
      indirect_unary_predicate<Pred, projected<I, Proj>>
  >::value, int> = 0>
  constexpr subrange<I> operator()(I first, S last, Pred pred, Proj proj = {}) const {
    I found{};
    for (; first != last; ++first) {
      if (!lsd::invoke(pred, lsd::invoke(proj, *first))) {
        found = first;
      }
    }

    if (found == I {})
      return {first, first};

    return {found, ranges::next(found, last)};
  }

  template<typename R, typename Proj = identity, typename Pred, std::enable_if_t<conjunction<
      forward_range<R>,
      projectable<iterator_t<R>, Proj>,
      indirect_unary_predicate<Pred, projected<iterator_t<R>, Proj>>
  >::value, int> = 0>
  constexpr borrowed_subrange_t<R> operator()(R&& r, Pred pred, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), std::ref(pred), std::ref(proj));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::find_last_niebloid find_last{};
LSD_INLINE_OR_STATIC constexpr detail::find_last_if_niebloid find_last_if{};
LSD_INLINE_OR_STATIC constexpr detail::find_last_if_not_niebloid find_last_if_not{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_FIND_LAST_H_
