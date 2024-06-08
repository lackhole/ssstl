//
// Created by yonggyulee on 1/24/24.
//

#ifndef LSD_RANGES_VIEWS_FILTER_HPP
#define LSD_RANGES_VIEWS_FILTER_HPP

#include <type_traits>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__ranges/range_adaptor.h"
#include "lsd/__ranges/range_adaptor_closure.h"
#include "lsd/__ranges/views/filter_view.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

struct filter_niebloid {
  template<typename R, typename Pred, std::enable_if_t<viewable_range<R>::value, int> = 0>
  constexpr auto operator()(R&& r, Pred&& pred) const {
    return filter_view<all_t<R>, remove_cvref_t<Pred>>(std::forward<R>(r), std::forward<Pred>(pred));
  }

  template<typename Pred>
  constexpr auto operator()(Pred&& pred) const {
    return range_adaptor<filter_niebloid, std::decay_t<Pred>>{std::forward<Pred>(pred)};
  }

};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::filter_niebloid filter{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_FILTER_HPP
