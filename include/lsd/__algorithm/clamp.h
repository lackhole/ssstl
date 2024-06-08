//
// Created by YongGyu Lee on 1/26/24.
//

#ifndef LSD_ALGORITHM_CLAMP_H_
#define LSD_ALGORITHM_CLAMP_H_

#include <functional>

namespace lsd {

template<typename T, typename Compare>
constexpr const T& clamp(const T& v, const T& lo, const T& hi, Compare comp) {
  return comp(v, lo) ? lo : comp(hi, v) ? hi : v;
}

template<typename T>
constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
  return lsd::clamp(v, lo, hi, std::less<>{});
}

} // namespace lsd

#endif // LSD_ALGORITHM_CLAMP_H_
