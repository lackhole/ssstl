//
// Created by yonggyulee on 2024/01/30.
//

#ifndef LSD_RANGES_VIEWS_REPEAT_HPP
#define LSD_RANGES_VIEWS_REPEAT_HPP

#include <type_traits>

#include "lsd/__concepts/constructible_from.h"
#include "lsd/__concepts/move_constructible.h"
#include "lsd/__concepts/same_as.h"
#include "lsd/__concepts/semiregular.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__ranges/views/repeat_view.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/disjunction.h"
#include "lsd/__type_traits/is_integer_like.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

struct repeat_niebloid {
  template<typename W, std::enable_if_t<conjunction<
      move_constructible< remove_cvref_t<W> >,
      std::is_object< remove_cvref_t<W> >
  >::value, int> = 0>
  constexpr auto operator()(W&& value) const {
    using RV = repeat_view<remove_cvref_t<W>>;
    return RV(std::forward<W>(value));
  }

  template<typename W, typename Bound, std::enable_if_t<conjunction<
      move_constructible< remove_cvref_t<W> >,
      std::is_object< remove_cvref_t<W> >,
      disjunction<
          is_integer_like< remove_cvref_t<Bound> >,
          same_as< remove_cvref_t<Bound>, unreachable_sentinel_t >
      >
  >::value, int> = 0>
  constexpr auto operator()(W&& value, Bound&& bound) const {
    using RV = repeat_view<remove_cvref_t<W>, remove_cvref_t<Bound>>;
    return RV(std::forward<W>(value), std::forward<Bound>(bound));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::repeat_niebloid repeat{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_REPEAT_HPP
