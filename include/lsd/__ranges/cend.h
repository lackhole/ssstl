//
// Created by yonggyulee on 2024/01/16.
//

#ifndef LSD_RANGES_CEND_HPP_
#define LSD_RANGES_CEND_HPP_

#include <type_traits>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/basic_const_iterator.h"
#include "lsd/__ranges/constant_range.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__ranges/end.h"
#include "lsd/__type_traits/detail/tag.h"
#include "lsd/__type_traits/disjunction.h"
#include "lsd/__utility/as_const.h"

namespace lsd {
namespace ranges {
namespace detail {

struct cend_niebloid {
  template<typename T, std::enable_if_t<disjunction<
      std::is_lvalue_reference<T>,
      enable_borrowed_range<std::remove_cv_t<T>>
  >::value, int> = 0>
  constexpr auto operator()(T&& t) const {
    using tag = conditional_tag<constant_range<T>, constant_range<const T>>;
    return this->call(std::forward<T>(t), tag{});
  }

 private:
  template<typename T>
  constexpr auto call(T&& t, lsd::detail::tag_1) const {
    return ranges::end(t);
  }
  template<typename T>
  constexpr auto call(T&& t, lsd::detail::tag_2) const {
    return ranges::end(lsd::as_const(t));
  }
  template<typename T>
  constexpr auto call(T&& t, lsd::detail::tag_else) const {
    return make_const_sentinel(ranges::end(t));
  }
};

} // namespace detail

inline namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::cend_niebloid cend{};

} // inline namespace niebloid

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_CEND_HPP_
