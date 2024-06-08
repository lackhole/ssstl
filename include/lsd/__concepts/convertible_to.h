//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_CONCEPTS_CONVERTIBLE_TO_H_
#define LSD_CONCEPTS_CONVERTIBLE_TO_H_

#include <type_traits>

#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_explicitly_convertible.h"

namespace lsd {

template<typename From, typename To>
struct convertible_to :
    conjunction<
      std::is_convertible<From, To>,
      is_explicitly_convertible<From, To>
    > {};

} // namespace lsd

#endif // LSD_CONCEPTS_CONVERTIBLE_TO_H_
