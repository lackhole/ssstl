//
// Created by YongGyu Lee on 3/20/24.
//

#ifndef LSD_MEMORY_DESTROY_H_
#define LSD_MEMORY_DESTROY_H_

#include "lsd/__core/constexpr.h"
#include "lsd/__memory/addressof.h"
#include "lsd/__memory/destroy_at.h"

namespace lsd {

template<typename ForwardIt>
LSD_CONSTEXPR_AFTER_CXX20 void destroy(ForwardIt first, ForwardIt last) {
  for (; first != last; ++first) {
    lsd::destroy_at(lsd::addressof(*first));
  }
}

} // namespace lsd

#endif // LSD_MEMORY_DESTROY_H_
