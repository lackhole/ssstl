//
// Created by YongGyu Lee on 1/18/24.
//

#ifndef LSD_CONCEPTS_DIFFERENT_FROM_HPP
#define LSD_CONCEPTS_DIFFERENT_FROM_HPP

#include "lsd/__concepts/same_as.h"
#include "lsd/__type_traits/negation.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {

template<typename Test, typename From>
struct different_from : negation< same_as<remove_cvref_t<Test>, remove_cvref_t<From>> > {};

template<typename Test, typename...>
struct different_from_variadic : std::true_type {};

template<typename Test, typename T>
struct different_from_variadic<Test, T> : different_from<Test, T> {};

} // namespace lsd

#endif // LSD_CONCEPTS_DIFFERENT_FROM_HPP
