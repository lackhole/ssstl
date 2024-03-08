//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___TYPE_TRAITS_INTEGRAL_CONSTANT_H_
#define LSD___TYPE_TRAITS_INTEGRAL_CONSTANT_H_

#include "lsd/__core/macro.h"

namespace lsd {

template<typename T, T v>
struct integral_constant {
  using value_type = T;
  using type = integral_constant;

  LSD_INLINE_VAR static constexpr value_type value = v;

  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

using true_type  = integral_constant<bool, true >;
using false_type = integral_constant<bool, false>;

template<bool B>
using bool_constant = integral_constant<bool, B>;

} // namespace lsd

#endif //LSD___TYPE_TRAITS_INTEGRAL_CONSTANT_H_
