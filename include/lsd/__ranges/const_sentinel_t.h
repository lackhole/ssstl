//
// Created by cosge on 2024-01-27.
//

#ifndef LSD_RANGES_CONST_SENTINEL_T_H_
#define LSD_RANGES_CONST_SENTINEL_T_H_

#include <type_traits>

#include "lsd/__ranges/cend.h"
#include "lsd/__ranges/range.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename R, bool = range<R>::value, typename = void>
struct const_sentinel_impl {};

template<typename R>
struct const_sentinel_impl<R, true, void_t<decltype( ranges::cend(std::declval<R&>()) )>> {
  using type = decltype(ranges::cend(std::declval<R&>()));
};

} // namespace detail

template<typename R>
struct const_sentinel : detail::const_sentinel_impl<R> {};

template<typename R>
using const_sentinel_t = typename const_sentinel<R>::type;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_CONST_SENTINEL_T_H_
