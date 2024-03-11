//
// Created by yonggyulee on 2024/01/03.
//

#ifndef LSD_RANGES_DETAIL_SIMPLE_VIEW_HPP
#define LSD_RANGES_DETAIL_SIMPLE_VIEW_HPP

#include <type_traits>

#include "lsd/__concepts/same_as.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/sentinel_t.h"
#include "lsd/__ranges/range.h"
#include "lsd/__ranges/view.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename R, bool = conjunction<view<R>, range<const R>>::value /* true */>
struct simple_view
    : conjunction<
          same_as<iterator_t<R>, iterator_t<const R>>,
          same_as<sentinel_t<R>, sentinel_t<const R>>
      > {};

template<typename R>
struct simple_view<R, false> : std::false_type {};

} // namespace detail
} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_DETAIL_SIMPLE_VIEW_HPP
