//
// Created by YongGyu Lee on 11/3/23.
//

#ifndef LSD_VARIANT_MONOSTATE_HPP
#define LSD_VARIANT_MONOSTATE_HPP

#include <functional>

namespace lsd {

struct monostate {};

constexpr bool operator==(monostate, monostate) noexcept { return true; }
constexpr bool operator!=(monostate, monostate) noexcept { return false; }
constexpr bool operator< (monostate, monostate) noexcept { return false; }
constexpr bool operator> (monostate, monostate) noexcept { return false; }
constexpr bool operator<=(monostate, monostate) noexcept { return true; }
constexpr bool operator>=(monostate, monostate) noexcept { return true; }


} // namespace lsd

template<>
struct std::hash<::lsd::monostate> {
  std::size_t operator()(const ::lsd::monostate&) const noexcept {
    return 1998;
  }
};

#endif // LSD_VARIANT_MONOSTATE_HPP
