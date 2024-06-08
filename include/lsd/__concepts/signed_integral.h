//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_CONCEPTS_SIGNED_INTEGRAL_H_
#define LSD_CONCEPTS_SIGNED_INTEGRAL_H_

#include <type_traits>

#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename T>
struct signed_integral : conjunction<std::is_integral<T>, std::is_signed<T>> {};

} // namespace lsd

#endif // LSD_CONCEPTS_SIGNED_INTEGRAL_H_
