//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_CBEGIN_H_
#define LSD_RANGES_CBEGIN_H_

#include <type_traits>

#include "lsd/__core/inline_variable.h"
#include "lsd/__iterator/basic_const_iterator.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__ranges/possibly_const_range.h"
#include "lsd/__type_traits/disjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

struct cbegin_niebloid {
  template<typename T, std::enable_if_t<disjunction<
      std::is_lvalue_reference<T>,
      enable_borrowed_range<std::remove_cv_t<T>>
  >::value, int> = 0>
  constexpr auto operator()(T&& t) const {
    return const_iterator<decltype(ranges::begin(lsd::ranges::possibly_const_range(t)))>(
                                   ranges::begin(lsd::ranges::possibly_const_range(t)));
  }
};

} // namespace detail

namespace niebloid {

LSD_INLINE_VARIABLE constexpr detail::cbegin_niebloid cbegin{};

} // namespace niebloid
using namespace niebloid;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_CBEGIN_H_
