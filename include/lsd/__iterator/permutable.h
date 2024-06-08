//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_ITERATOR_PERMUTABLE_H_
#define LSD_ITERATOR_PERMUTABLE_H_

#include "lsd/__iterator/forward_iterator.h"
#include "lsd/__iterator/indirectly_movable_storable.h"
#include "lsd/__iterator/indirectly_swappable.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename I>
struct permutable
    : conjunction<
          forward_iterator<I>,
          indirectly_movable_storable<I, I>,
          indirectly_swappable<I, I>
      > {};

} // namespace lsd

#endif // LSD_ITERATOR_PERMUTABLE_H_
