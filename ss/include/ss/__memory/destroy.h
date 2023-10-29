//
// Created by cosge on 2023-10-29.
//

#ifndef SS___MEMORY_DESTROY_H_
#define SS___MEMORY_DESTROY_H_

#include "ss/iterator.h"
#include "ss/__memory/addressof.h"

namespace ss {

template<typename ForwardIt>
SS_CONSTEXPR_AFTER_14 void destroy(ForwardIt first, ForwardIt last);

/**
 * destroy_at
 * @tparam T
 * @param p
 */
template<typename T, enable_if_t<!is_array<T>::value, int> = 0>
SS_CONSTEXPR_AFTER_14 void destroy_at(T *p) {
  p->~T();
}

template<typename T, enable_if_t<is_array<T>::value, int> = 0>
SS_CONSTEXPR_AFTER_14 void destroy_at(T *p) {
  ss::destroy(ss::begin(p), ss::end(p));
}

/**
 * destroy
 * @param first
 * @param last
 */
template<typename ForwardIt>
SS_CONSTEXPR_AFTER_14 void destroy(ForwardIt first, ForwardIt last) {
  for (; first != last; ++first)
    ss::destroy_at(ss::addressof(*first));
}

template<typename ForwardIt, typename Size>
SS_CONSTEXPR_AFTER_14 ForwardIt destroy_n(ForwardIt first, Size n) {
  for (; n > 0; (void) ++first, --n) {
    ss::destroy_at(ss::addressof(first));
  }
  return first;
}

} // namespace ss

#endif // SS___MEMORY_DESTROY_H_
