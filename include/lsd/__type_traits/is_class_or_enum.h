//
// Created by yonggyulee on 2024/02/08.
//

#ifndef LSD_TYPE_TRAITS_IS_CLASS_OR_ENUM_HPP
#define LSD_TYPE_TRAITS_IS_CLASS_OR_ENUM_HPP

#include <type_traits>

#include "lsd/__type_traits/disjunction.h"

namespace lsd {

template<class T>
struct is_class_or_enum : disjunction<std::is_class<T>, std::is_enum<T>> {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_CLASS_OR_ENUM_HPP
