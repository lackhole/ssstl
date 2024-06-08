//
// Created by yonggyulee on 1/31/24.
//

#ifndef LSD_RANGES_VIEWS_JOIN_H_
#define LSD_RANGES_VIEWS_JOIN_H_

#include <type_traits>
#include <utility>

#include "lsd/__ranges/range.h"
#include "lsd/__ranges/range_adaptor_closure.h"
#include "lsd/__ranges/views/all.h"
#include "lsd/__ranges/views/join_view.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

class join_adaptor_object : public range_adaptor_closure<join_adaptor_object> {
 public:
  template<typename R, std::enable_if_t<range<R>::value, int> = 0>
  constexpr auto operator()(R&& r) const {
    return join_view<all_t<decltype((r))>>{std::forward<R>(r)};
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::join_adaptor_object join{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_JOIN_H_
