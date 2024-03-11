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

} // namespace lsd

#endif // LSD_CONCEPTS_DIFFERENT_FROM_HPP
