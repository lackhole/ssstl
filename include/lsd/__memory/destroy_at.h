//
// Created by YongGyu Lee on 3/20/24.
//

#ifndef LSD_MEMORY_DESTROY_AT_HPP_
#define LSD_MEMORY_DESTROY_AT_HPP_

#include <type_traits>

#include "lsd/__core/constexpr.h"
#include "lsd/__memory/addressof.h"

namespace lsd {

template <typename T, std::enable_if_t<!std::is_array<T>::value, int> = 0>
LSD_CONSTEXPR_AFTER_CXX20 void destroy_at(T* p) {
  p->~T();
}

template <typename T, std::enable_if_t<std::is_array<T>::value, int> = 0>
LSD_CONSTEXPR_AFTER_CXX20 void destroy_at(T* p) {
  auto first = std::begin(*p);
  auto last = std::end(*p);

  for (; first != last; ++first) {
    lsd::destroy_at(lsd::addressof(*first));
  }
}

} // namespace lsd

#endif // LSD_MEMORY_DESTROY_AT_HPP_
