//
// Created by cosge on 2023-10-29.
//

#ifndef SS___TYPE_TRAITS_INTEGRAL_CONSTANT_H_
#define SS___TYPE_TRAITS_INTEGRAL_CONSTANT_H_

#include "ss/detail/macro.h"

namespace ss {

template<typename T, T v>
struct integral_constant {
  using value_type = T;
  using type = integral_constant;

  SS_INLINE_VAR static constexpr value_type value = v;

  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

using true_type  = integral_constant<bool, true >;
using false_type = integral_constant<bool, false>;

template<bool B>
using bool_constant = integral_constant<bool, B>;

} // namespace ss

#endif //SS___TYPE_TRAITS_INTEGRAL_CONSTANT_H_
