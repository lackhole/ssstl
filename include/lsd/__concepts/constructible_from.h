//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_CONCEPTS_CONSTRUCTIBLE_FROM_H_
#define LSD_CONCEPTS_CONSTRUCTIBLE_FROM_H_

#include "lsd/__concepts/destructible.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename T, typename... Args>
struct constructible_from : conjunction<
    destructible<T>,
    std::is_constructible<T, Args...>> {};

} // namespace lsd

#endif // LSD_CONCEPTS_CONSTRUCTIBLE_FROM_H_
