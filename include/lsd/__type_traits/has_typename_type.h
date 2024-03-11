//
// Created by yonggyulee on 2023/10/27.
//

#ifndef LSD_TYPE_TRAITS_HAS_TYPENAME_TYPE_HPP_
#define LSD_TYPE_TRAITS_HAS_TYPENAME_TYPE_HPP_

#include <type_traits>

#include "lsd/__type_traits/void_t.h"

namespace lsd {

template<typename T, typename = void>
struct has_typename_type : std::false_type {};

template<typename T>
struct has_typename_type<T, void_t<typename T::type>> : std::true_type {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_HAS_TYPENAME_TYPE_HPP_
