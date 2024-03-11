//
// Created by YongGyu Lee on 2/8/24.
//

#ifndef LSD_RANGES_VIEWS_COMMON_HPP
#define LSD_RANGES_VIEWS_COMMON_HPP

#include <type_traits>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__ranges/common_range.h"
#include "lsd/__ranges/range_adaptor_closure.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__ranges/views/all.h"
#include "lsd/__ranges/views/common_view.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_invocable.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

struct common_adaptor_object : range_adaptor_closure<common_adaptor_object> {
 private:
  template<typename R>
  constexpr auto call(R&& r, std::true_type /* all and common */) const {
    return views::all(std::forward<R>(r));
  }
  template<typename R>
  constexpr auto call(R&& r, std::false_type /* all and common */) const {
    return common_view<all_t<R>>(std::forward<R>(r));
  }

 public:
  template<typename R, std::enable_if_t<viewable_range<R>::value, int> = 0>
  constexpr auto operator()(R&& r) const {
    return call(std::forward<R>(r), conjunction<is_invocable<all_adaptor_closure, R&&>, common_range<decltype((r))>>{});
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::common_adaptor_object common{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_COMMON_HPP
