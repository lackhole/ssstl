//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___MEMORY_DESTROY_H_
#define LSD___MEMORY_DESTROY_H_

#include "lsd/iterator.h"
#include "lsd/__memory/addressof.h"

namespace lsd {

template<typename ForwardIt>
LSD_CONSTEXPR_AFTER_14 void destroy(ForwardIt first, ForwardIt last);

/**
 * destroy_at
 * @tparam T
 * @param p
 */
template<typename T, enable_if_t<!is_array<T>::value, int> = 0>
LSD_CONSTEXPR_AFTER_14 void destroy_at(T *p) {
  p->~T();
}

template<typename T, enable_if_t<is_array<T>::value, int> = 0>
LSD_CONSTEXPR_AFTER_14 void destroy_at(T *p) {
  lsd::destroy(lsd::begin(p), lsd::end(p));
}

/**
 * destroy
 * @param first
 * @param last
 */
template<typename ForwardIt>
LSD_CONSTEXPR_AFTER_14 void destroy(ForwardIt first, ForwardIt last) {
  for (; first != last; ++first)
    lsd::destroy_at(lsd::addressof(*first));
}

template<typename ForwardIt, typename Size>
LSD_CONSTEXPR_AFTER_14 ForwardIt destroy_n(ForwardIt first, Size n) {
  for (; n > 0; (void) ++first, --n) {
    lsd::destroy_at(lsd::addressof(first));
  }
  return first;
}

} // namespace lsd

#endif // LSD___MEMORY_DESTROY_H_
