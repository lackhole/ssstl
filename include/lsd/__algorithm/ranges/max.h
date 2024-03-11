//
// Created by YongGyu Lee on 01/27/24.
//

#ifndef LSD_ALGORITHM_RANGES_MAX_HPP
#define LSD_ALGORITHM_RANGES_MAX_HPP

#include <functional>
#include <initializer_list>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__algorithm/ranges/max_element.h"
#include "lsd/__concepts/copyable.h"
#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__functional/less.h"
#include "lsd/__iterator/indirect_strict_weak_order.h"
#include "lsd/__iterator/indirectly_copyable_storable.h"
#include "lsd/__iterator/projected.h"
#include "lsd/__ranges/forward_range.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/range_value_t.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

struct max_niebloid {
 private:
  template<typename R, typename Proj, typename Comp, bool = projectable<iterator_t<R>, Proj>::value /* false */>
  struct check_range_2 : std::false_type {};
  template<typename R, typename Proj, typename Comp>
  struct check_range_2<R, Proj, Comp, true>
      : conjunction<
            indirect_strict_weak_order<Comp, projected<iterator_t<R>, Proj>>,
            indirectly_copyable_storable<iterator_t<R>, range_value_t<R>*>
        > {};

  template<typename R, typename Proj, typename Comp, bool = input_range<R>::value /* false */>
  struct check_range : std::false_type {};
  template<typename R, typename Proj, typename Comp>
  struct check_range<R, Proj, Comp, true> : check_range_2<R, Proj, Comp> {};

  template<typename R, typename Proj, typename Comp>
  constexpr range_value_t<R>
  max_range(R&& r, Comp comp, Proj proj, std::true_type /* forward_range */) const {
    return static_cast<range_value_t<R>>(*ranges::max_element(r, std::ref(comp), std::ref(proj)));
  }

  template<typename R, typename Proj, typename Comp>
  constexpr range_value_t<R>
  max_range(R&& r, Comp comp, Proj proj, std::false_type /* forward_range */) const {
    auto i = ranges::begin(r);
    auto s = ranges::end(r);
    range_value_t<R> m(*i);
    while (++i != s) {
      if (!lsd::invoke(comp, lsd::invoke(proj, m), lsd::invoke(proj, *i)))
        m = *i;
    }
    return m;
  }

 public:
  template<typename T, typename Proj = identity, typename Comp = less, std::enable_if_t<
      indirect_strict_weak_order<Comp, projected<const T*, Proj>>::value, int> = 0>
  constexpr const T&
  operator()(const T& a, const T& b, Comp comp = {}, Proj proj = {}) const {
    return lsd::invoke(comp, lsd::invoke(proj, a), lsd::invoke(proj, b)) ? b : a;
  }

  template<typename T, typename Proj = identity, typename Comp = less,
      std::enable_if_t<conjunction<
          copyable<T>,
          indirect_strict_weak_order<Comp, projected<const T*, Proj>>
      >::value, int> = 0>
  constexpr T
  operator()(std::initializer_list<T> r, Comp comp = {}, Proj proj = {}) const {
    return *ranges::max_element(r, std::ref(comp), std::ref(proj));
  }

  template<typename R, typename Proj = identity, typename Comp = less,
      std::enable_if_t<check_range<R, Proj, Comp>::value, int> = 0>
  constexpr range_value_t<R>
  operator()(R&& r, Comp comp = {}, Proj proj = {}) const {
    return this->max_range(std::forward<R>(r), std::ref(comp), std::ref(proj), forward_range<R>{});
  }
};
} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::max_niebloid max{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_MAX_HPP
