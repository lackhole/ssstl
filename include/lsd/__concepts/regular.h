//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_CONCEPTS_REGULAR_HPP_
#define LSD_CONCEPTS_REGULAR_HPP_

#include "lsd/__concepts/semiregular.h"
#include "lsd/__concepts/equality_comparable.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename T>
struct regular
    : conjunction<
        semiregular<T>,
        equality_comparable<T>
      > {};

} // namespace lsd

#endif // LSD_CONCEPTS_REGULAR_HPP_
