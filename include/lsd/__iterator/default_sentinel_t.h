//
// Created by cosge on 2024-01-03.
//

#ifndef LSD_ITERATOR_DEFAULT_SENTINEL_T_H_
#define LSD_ITERATOR_DEFAULT_SENTINEL_T_H_

#include <type_traits>

#include "lsd/__core/inline_or_static.h"

namespace lsd {

struct default_sentinel_t {};

LSD_INLINE_OR_STATIC constexpr default_sentinel_t default_sentinel{};

} // namespace lsd

#endif // LSD_ITERATOR_DEFAULT_SENTINEL_T_H_
