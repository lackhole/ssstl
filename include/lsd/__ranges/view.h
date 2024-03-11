//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_VIEW_HPP_
#define LSD_RANGES_VIEW_HPP_

#include "lsd/__concepts/movable.h"
#include "lsd/__ranges/enable_view.h"
#include "lsd/__ranges/range.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {

template<typename T>
struct view
    : conjunction<
          range<T>,
          movable<T>,
          enable_view<T>
      > {};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEW_HPP_
