//
// Created by yonggyulee on 2024/01/08.
//

#ifndef LSD_RANGES_BORROWED_SUBRANGE_T_H_
#define LSD_RANGES_BORROWED_SUBRANGE_T_H_

#include <type_traits>

#include "lsd/__ranges/borrowed_range.h"
#include "lsd/__ranges/dangling.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/range.h"
#include "lsd/__ranges/subrange.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename R, bool v = range<R>::value /* true */>
struct borrowed_subrange_impl {
  using type = std::conditional_t<borrowed_range<R>::value, subrange<iterator_t<R>>, dangling>;
};

template<typename R>
struct borrowed_subrange_impl<R, false> {};

} // namespace detail

template<typename R>
struct borrowed_subrange : detail::borrowed_subrange_impl<R> {};

template<typename R>
using borrowed_subrange_t = typename borrowed_subrange<R>::type;

} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_BORROWED_SUBRANGE_T_H_
