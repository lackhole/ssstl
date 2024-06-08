//
// Created by YongGyu Lee on 3/27/24.
//

#ifndef LSD_RANGES_CRBEGIN_HPP_
#define LSD_RANGES_CRBEGIN_HPP_

#include <type_traits>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/basic_const_iterator.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__ranges/possibly_const_range.h"
#include "lsd/__ranges/rbegin.h"
#include "lsd/__type_traits/disjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

struct crbegin_niebloid {
  template<typename T, std::enable_if_t<disjunction<
      std::is_lvalue_reference<T>,
      enable_borrowed_range<std::remove_cv_t<T>>
  >::value, int> = 0>
  constexpr auto operator()(T&& t) const {
    return lsd::const_iterator<decltype(ranges::rbegin(possibly_const_range(t)))>(ranges::rbegin(possibly_const_range(t)));
  }
};

} // namespace detail

namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::crbegin_niebloid crbegin{};

} // namespace niebloid
using namespace niebloid;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_CRBEGIN_HPP_
