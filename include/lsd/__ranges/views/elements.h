//
// Created by yonggyulee on 2024/01/22.
//

#ifndef LSD_RANGES_VIEWS_ELEMENTS_HPP
#define LSD_RANGES_VIEWS_ELEMENTS_HPP

#include <type_traits>
#include <utility>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__ranges/range_adaptor_closure.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__ranges/views/all.h"
#include "lsd/__ranges/views/elements_view.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

template<std::size_t N>
class elements_adaptor_object : public range_adaptor_closure<elements_adaptor_object<N>> {
 public:
  constexpr elements_adaptor_object() = default;

  template<typename R, std::enable_if_t<viewable_range<R>::value, int> = 0>
  constexpr auto operator()(R&& r) const {
    return elements_view<all_t<R>, N>(std::forward<R>(r));
  }
};

} // namespace detail

template<std::size_t N>
LSD_INLINE_OR_STATIC constexpr detail::elements_adaptor_object<N> elements{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_ELEMENTS_HPP
