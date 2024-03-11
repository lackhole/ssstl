//
// Created by cosge on 2023-12-29.
//

#ifndef LSD_TYPE_TRAITS_IS_INITIALIZER_LIST_HPP
#define LSD_TYPE_TRAITS_IS_INITIALIZER_LIST_HPP

#include <initializer_list>
#include <type_traits>

#include "lsd/__type_traits/is_specialization.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {

template <class T>
struct is_initializer_list : is_specialization<remove_cvref_t<T>, std::initializer_list> {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_INITIALIZER_LIST_HPP
