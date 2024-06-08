//
// Created by yonggyulee on 2023/12/27.
//

#ifndef LSD_CONCEPTS_RELATION_H_
#define LSD_CONCEPTS_RELATION_H_

#include "lsd/__concepts/predicate.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename R, typename T, typename U>
struct relation
    : conjunction<
        predicate<R, T, T>,
        predicate<R, U, U>,
        predicate<R, T, U>,
        predicate<R, U, T>
      > {};

} // namespace lsd

#endif // LSD_CONCEPTS_RELATION_H_
