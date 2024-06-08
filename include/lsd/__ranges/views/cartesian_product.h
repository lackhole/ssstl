//
// Created by yonggyulee on 2024/01/27.
//

#ifndef LSD_RANGES_VIEWS_CARTESIAN_PRODUCT_H_
#define LSD_RANGES_VIEWS_CARTESIAN_PRODUCT_H_

#include <tuple>
#include <type_traits>

#include "lsd/__core/inline_variable.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__ranges/views/all.h"
#include "lsd/__ranges/views/cartesian_product_view.h"
#include "lsd/__ranges/views/single.h"

#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

struct cartesian_product_niebloid {
  constexpr auto operator()() const {
    return views::single(std::tuple<>());
  }

  template<typename... Rs, std::enable_if_t<conjunction<
      viewable_range<Rs>...
  >::value, int> = 0>
  constexpr auto operator()(Rs&&... rs) const {
    return ranges::cartesian_product_view<all_t<Rs&&>...>(std::forward<Rs>(rs)...);
  }
};

} // namespace detail

LSD_INLINE_VARIABLE constexpr detail::cartesian_product_niebloid cartesian_product{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_CARTESIAN_PRODUCT_H_
