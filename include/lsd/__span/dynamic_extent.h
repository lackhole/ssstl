//
// Created by yonggyulee on 2023/12/30.
//

#ifndef LSD_SPAN_DYNAMIC_EXTENT_HPP
#define LSD_SPAN_DYNAMIC_EXTENT_HPP

#include <cstddef>
#include <limits>

#include "lsd/__core/inline_or_static.h"

namespace lsd {

LSD_INLINE_OR_STATIC constexpr std::size_t dynamic_extent = (std::numeric_limits<std::size_t>::max)();

} // namespace lsd

#endif // LSD_SPAN_DYNAMIC_EXTENT_HPP
