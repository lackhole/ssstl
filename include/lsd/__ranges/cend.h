//
// Created by yonggyulee on 2024/01/16.
//

#ifndef LSD_RANGES_CEND_H_
#define LSD_RANGES_CEND_H_

#include <type_traits>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/basic_const_iterator.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/possibly_const_range.h"
#include "lsd/__type_traits/disjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

struct cend_niebloid {
  template<typename T, std::enable_if_t<disjunction<
      std::is_lvalue_reference<T>,
      enable_borrowed_range<std::remove_cv_t<T>>
  >::value, int> = 0>
  constexpr auto operator()(T&& t) const {
    return lsd::const_sentinel<decltype(ranges::end(possibly_const_range(t)))>(ranges::end(possibly_const_range(t)));
  }
};

} // namespace detail

namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::cend_niebloid cend{};

} // namespace niebloid
using namespace niebloid;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_CEND_H_
