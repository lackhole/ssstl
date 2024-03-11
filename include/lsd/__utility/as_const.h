//
// Created by yonggyulee on 2024/01/02.
//

#ifndef LSD_UTILITY_AS_CONST_HPP
#define LSD_UTILITY_AS_CONST_HPP

#include <type_traits>

namespace lsd {

template<typename T>
constexpr std::add_const_t<T>& as_const(T& t) noexcept {
  return t;
}

template<typename T>
void as_const(T&&) = delete;

} // namespace lsd

#endif // LSD_UTILITY_AS_CONST_HPP
