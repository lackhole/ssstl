//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_CONCEPTS_DERIVED_FROM_H_
#define LSD_CONCEPTS_DERIVED_FROM_H_

#include <type_traits>

#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename Derived, typename Base>
struct derived_from
    : conjunction<
        std::is_base_of<Base, Derived>,
        std::is_convertible<const volatile Derived*, const volatile Base*>
      > {};

} // namespace lsd

#endif // LSD_CONCEPTS_DERIVED_FROM_H_
