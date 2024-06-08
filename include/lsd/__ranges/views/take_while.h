//
// Created by YongGyu Lee on 3/27/24.
//

#ifndef LSD_RANGES_VIEWS_TAKE_WHILE_H_
#define LSD_RANGES_VIEWS_TAKE_WHILE_H_

#include <type_traits>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/indirect_unary_predicate.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/range_adaptor.h"
#include "lsd/__ranges/view.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__ranges/views/all.h"
#include "lsd/__ranges/views/take_while_view.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

struct take_while_niebloid {
  template<typename R, typename Pred, std::enable_if_t<conjunction<
      has_typename_type<detail::all_t_impl<R>>,
      view<all_t<R>>,
      input_range<all_t<R>>,
      std::is_object<remove_cvref_t<Pred>>,
      indirect_unary_predicate<const remove_cvref_t<Pred>, iterator_t<all_t<R>>>
  >::value, int> = 0>
  constexpr auto operator()(R&& r, Pred&& pred) const {
    return take_while_view<all_t<R>, std::decay_t<Pred>>(std::forward<R>(r), std::forward<Pred>(pred));
  }

  template<typename Pred>
  constexpr auto operator()(Pred&& pred) const {
    return range_adaptor<take_while_niebloid, std::decay_t<Pred>>(std::forward<Pred>(pred));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::take_while_niebloid take_while{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_TAKE_WHILE_H_
