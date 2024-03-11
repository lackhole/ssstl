//
// Created by YongGyu Lee on 11/13/23.
//

#ifndef LSD_TYPE_TRAITS_IS_EXPLICITLY_CONSTRUCTIBLE_HPP
#define LSD_TYPE_TRAITS_IS_EXPLICITLY_CONSTRUCTIBLE_HPP

#include <type_traits>

#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/negation.h"

namespace lsd {

template<typename T, typename... Args>
struct is_explicitly_constructible :
    conjunction<
      std::is_constructible<T, Args...>,
      negation<std::is_convertible<Args..., T>>
    > {};

template<typename T, typename... Args>
using is_explicitly_constructible_t = typename is_explicitly_constructible<T, Args...>::type;

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_EXPLICITLY_CONSTRUCTIBLE_HPP
