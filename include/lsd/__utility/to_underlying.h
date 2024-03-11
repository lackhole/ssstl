//
// Created by yonggyulee on 2024/01/02.
//

#ifndef LSD_UTILITY_TO_UNDERLYING_HPP
#define LSD_UTILITY_TO_UNDERLYING_HPP

#include <type_traits>

namespace lsd {

template<typename Enum>
constexpr std::underlying_type_t<Enum>& to_underlying(Enum e) noexcept {
  return static_cast<std::underlying_type_t<Enum>>(e);
}

} // namespace lsd

#endif // LSD_UTILITY_TO_UNDERLYING_HPP
