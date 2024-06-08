//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_ITERATOR_SENTINEL_FOR_H_
#define LSD_ITERATOR_SENTINEL_FOR_H_

#include "lsd/__concepts/semiregular.h"
#include "lsd/__concepts/weakly_equality_comparable_with.h"
#include "lsd/__iterator/input_or_output_iterator.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename S, typename I>
struct sentinel_for
    : conjunction<
        semiregular<S>,
        input_or_output_iterator<I>,
        weakly_equality_comparable_with<S, I>
      > {};

} // namespace lsd

#endif // LSD_ITERATOR_SENTINEL_FOR_H_
