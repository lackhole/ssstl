//
// Created by YongGyu Lee on 12/28/23.
//

#ifndef LSD_FUNCTIONAL_IDENTITY_HPP
#define LSD_FUNCTIONAL_IDENTITY_HPP

#include <type_traits>
#include <utility>

namespace lsd {

struct identity {
  template<typename T>
  constexpr T&& operator()(T&& t) const noexcept {
    return std::forward<T>(t);
  }

  using is_transparent = std::true_type;
};

} // namespace lsd

#endif // LSD_FUNCTIONAL_IDENTITY_HPP
