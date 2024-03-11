//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_CBEGIN_HPP_
#define LSD_RANGES_CBEGIN_HPP_

#include <type_traits>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/basic_const_iterator.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/constant_range.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__type_traits/detail/tag.h"
#include "lsd/__type_traits/disjunction.h"
#include "lsd/__utility/as_const.h"

namespace lsd {
namespace ranges {
namespace detail {

struct cbegin_niebloid {
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
    return ranges::begin(t);
  }
  template<typename T>
  constexpr auto call(T&& t, lsd::detail::tag_2) const {
    return ranges::begin(lsd::as_const(t));
  }
  template<typename T>
  constexpr auto call(T&& t, lsd::detail::tag_else) const {
    return make_const_iterator(ranges::begin(t));
  }
};

} // namespace detail

inline namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::cbegin_niebloid cbegin{};

} // inline namespace niebloid

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_CBEGIN_HPP_
