//
// Created by YongGyu Lee on 3/27/24.
//

#ifndef LSD_RANGES_CDATA_HPP_
#define LSD_RANGES_CDATA_HPP_

#include <type_traits>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/basic_const_iterator.h"
#include "lsd/__ranges/as_const_pointer.h"
#include "lsd/__ranges/data.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__ranges/possibly_const_range.h"
#include "lsd/__ranges/range_const_reference_t.h"
#include "lsd/__type_traits/disjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

struct cdata_niebloid {
  template<typename T, std::enable_if_t<disjunction<
      std::is_lvalue_reference<T>,
      enable_borrowed_range<std::remove_cv_t<T>>
  >::value, int> = 0>
  constexpr std::remove_reference_t<range_const_reference_t<T>>* operator()(T&& t) const {
    return lsd::ranges::as_const_pointer(ranges::data(possibly_const_range(t)));
  }
};

} // namespace detail

namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::cdata_niebloid cdata{};

} // namespace niebloid
using namespace niebloid;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_CDATA_HPP_
