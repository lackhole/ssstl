//
// Created by YongGyu Lee on 4/15/24.
//

#ifndef LSD_ALGORITHM_RANGES_SORT_HEAP_HPP_
#define LSD_ALGORITHM_RANGES_SORT_HEAP_HPP_

#include <algorithm>
#include <type_traits>
#include <utility>

#include "lsd/__algorithm/ranges/pop_heap.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__functional/less.h"
#include "lsd/__iterator/next.h"
#include "lsd/__iterator/random_access_iterator.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__iterator/sortable.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/borrowed_iterator_t.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/random_access_range.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

struct sort_heap_niebloid {
  template<typename I, typename S, typename Comp = ranges::less, typename Proj = identity, std::enable_if_t<conjunction<
      random_access_iterator<I>,
      sentinel_for<S, I>,
      sortable<I, Comp, Proj>
  >::value, int> = 0>
  constexpr I operator()(I first, S last, Comp comp = {}, Proj proj = {}) const {
    auto last_iter = ranges::next(first, last);
    for (; !(first == last); --last)
      ranges::pop_heap(first, last, comp, proj);
    return last_iter;
  }

  template<typename R, typename Comp = ranges::less, typename Proj = identity, std::enable_if_t<conjunction<
      random_access_range<R>,
      sortable<iterator_t<R>, Comp, Proj>
  >::value, int> = 0>
  constexpr borrowed_iterator_t<R> operator()(R&& r, Comp comp = {}, Proj proj = {}) const {
    return (*this)(ranges::begin(r), ranges::end(r), std::move(comp), std::move(proj));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::sort_heap_niebloid sort_heap{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_SORT_HEAP_HPP_
