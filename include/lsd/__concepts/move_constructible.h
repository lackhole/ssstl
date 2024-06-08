//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_CONCEPTS_MOVE_CONSTRUCTIBLE_H_
#define LSD_CONCEPTS_MOVE_CONSTRUCTIBLE_H_

#include "lsd/__concepts/constructible_from.h"
#include "lsd/__concepts/convertible_to.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename T>
struct move_constructible : conjunction<constructible_from<T, T>, convertible_to<T, T>> {};

} // namespace lsd

#endif // LSD_CONCEPTS_MOVE_CONSTRUCTIBLE_H_
