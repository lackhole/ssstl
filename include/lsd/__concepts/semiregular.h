//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_CONCEPTS_SEMIREGULAR_HPP_
#define LSD_CONCEPTS_SEMIREGULAR_HPP_

#include "lsd/__concepts/copyable.h"
#include "lsd/__concepts/default_initializable.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename T>
struct semiregular
    : conjunction<
        copyable<T>,
        default_initializable<T>
      > {};

} // namespace lsd

#endif // LSD_CONCEPTS_SEMIREGULAR_HPP_
