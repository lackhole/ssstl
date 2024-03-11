//
// Created by yonggyulee on 2024/01/02.
//

#ifndef LSD_UTILITY_NONTYPE_HPP
#define LSD_UTILITY_NONTYPE_HPP

#include <type_traits>

#include "lsd/__core/inline_or_static.h"

namespace lsd {

template<typename V>
struct nontype_t {
  constexpr explicit nontype_t() = default;
};

template<typename T>
LSD_INLINE_OR_STATIC constexpr nontype_t<T> nontype{};

} // namespace lsd

#endif // LSD_UTILITY_NONTYPE_HPP
