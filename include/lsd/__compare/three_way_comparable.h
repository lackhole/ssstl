//
// Created by YongGyu Lee on 4/11/24.
//

#ifndef LSD_COMPARE_THREE_WAY_COMPARABLE_H_
#define LSD_COMPARE_THREE_WAY_COMPARABLE_H_

#include "lsd/__concepts/partially_ordered_with.h"
#include "lsd/__concepts/weakly_equality_comparable_with.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename T>
struct unstable_three_way_comparable
    : conjunction<
        weakly_equality_comparable_with<T, T>,
        partially_ordered_with<T, T>
    > {};

} // namespace lsd

#endif // LSD_COMPARE_THREE_WAY_COMPARABLE_H_
