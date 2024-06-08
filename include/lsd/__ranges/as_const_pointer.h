//
// Created by YongGyu Lee on 3/27/24.
//

#ifndef LSD_RANGES_AS_CONST_POINTER_HPP_
#define LSD_RANGES_AS_CONST_POINTER_HPP_

namespace lsd {
namespace ranges {

template<typename T>
constexpr auto as_const_pointer(const T* p) noexcept {
  return p;
}

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_AS_CONST_POINTER_HPP_
