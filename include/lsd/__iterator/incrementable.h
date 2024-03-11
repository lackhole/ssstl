//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_ITERATOR_INCREMENTABLE_HPP_
#define LSD_ITERATOR_INCREMENTABLE_HPP_

#include "lsd/__concepts/regular.h"
#include "lsd/__iterator/weakly_incrementable.h"

namespace lsd {

template<typename T>
struct incrementable
    : conjunction<
        regular<T>,
        weakly_incrementable<T>
      > {};

} // namespace lsd

#endif // LSD_ITERATOR_INCREMENTABLE_HPP_
