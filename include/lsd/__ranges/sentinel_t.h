//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_RANGES_SENTINEL_T_H_
#define LSD_RANGES_SENTINEL_T_H_

#include <type_traits>

#include "lsd/__ranges/end.h"
#include "lsd/__ranges/range.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace ranges {

template<typename R, bool = range<R>::value, typename = void>
struct sentinel {};

template<typename R>
struct sentinel<R, true, void_t<decltype( ranges::end(std::declval<R&>()) )>> {
  using type = decltype(ranges::end(std::declval<R&>()));
};

template<typename R>
using sentinel_t = typename sentinel<R>::type;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_SENTINEL_T_H_
