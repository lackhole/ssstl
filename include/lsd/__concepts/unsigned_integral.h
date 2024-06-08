//
// Created by yonggyulee on 2023/12/27.
//

#ifndef LSD_CONCEPTS_UNSIGNED_INTEGRAL_H_
#define LSD_CONCEPTS_UNSIGNED_INTEGRAL_H_

#include <type_traits>

#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/negation.h"

namespace lsd {

template<typename T>
struct unsigned_integral : conjunction<std::is_integral<T>, negation<std::is_signed<T>>> {};

} // namespace lsd

#endif // LSD_CONCEPTS_UNSIGNED_INTEGRAL_H_
