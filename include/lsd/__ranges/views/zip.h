//
// Created by YongGyu Lee on 4/9/24.
//

#ifndef LSD_RANGES_VIEWS_ZIP_H_
#define LSD_RANGES_VIEWS_ZIP_H_

#include <tuple>
#include <type_traits>

#include "lsd/__core/decay_copy.h"
#include "lsd/__core/inline_variable.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__ranges/views/all.h"
#include "lsd/__ranges/views/empty_view.h"
#include "lsd/__ranges/views/zip_view.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

struct zip_niebloid {
  constexpr auto operator()() const {
    return vccc_decay_copy(views::empty<std::tuple<>>);
  }

  template<typename... Rs, std::enable_if_t<conjunction<
      viewable_range<Rs>...
  >::value, int> = 0>
  constexpr auto operator()(Rs&&... rs) const {
    return ranges::zip_view<views::all_t<decltype((rs))>...>(rs...);
  }
};

} // namespace detail

LSD_INLINE_VARIABLE constexpr detail::zip_niebloid zip{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_ZIP_H_
