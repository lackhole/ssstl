//
// Created by yonggyulee on 2024/01/08.
//

#ifndef LSD_RANGES_BORROWED_ITERATOR_T_H_
#define LSD_RANGES_BORROWED_ITERATOR_T_H_

#include <type_traits>

#include "lsd/__ranges/borrowed_range.h"
#include "lsd/__ranges/dangling.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/range.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename R, bool v = range<R>::value /* true */>
struct borrowed_iterator_impl {
  using type = std::conditional_t<borrowed_range<R>::value, iterator_t<R>, dangling>;
};

template<typename R>
struct borrowed_iterator_impl<R, false> {};

} // namespace detail

template<typename R>
struct borrowed_iterator : detail::borrowed_iterator_impl<R> {};

template<typename R>
using borrowed_iterator_t = typename borrowed_iterator<R>::type;

} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_BORROWED_ITERATOR_T_H_
