//
// Created by YongGyu Lee on 11/13/23.
//

#ifndef LSD_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_H_
#define LSD_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_H_

#include <type_traits>

#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/negation.h"

namespace lsd {

template<typename T, typename... Args>
struct is_implicitly_constructible :
    conjunction<
      std::is_constructible<T, Args...>,
      std::is_convertible<Args..., T>
    > {};

template<typename T, typename... Args>
using is_implicitly_constructible_t = typename is_implicitly_constructible<T, Args...>::type;

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_IMPLICITLY_CONSTRUCTIBLE_H_
