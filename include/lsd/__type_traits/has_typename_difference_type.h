//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_TYPE_TRAITS_HAS_TYPENAME_DIFFERENCE_TYPE_H_
#define LSD_TYPE_TRAITS_HAS_TYPENAME_DIFFERENCE_TYPE_H_

#include <type_traits>

#include "lsd/__type_traits/void_t.h"

namespace lsd {

template<typename T, typename = void>
struct has_typename_difference_type : std::false_type {};

template<typename T>
struct has_typename_difference_type<T, void_t<typename T::difference_type>> : std::true_type {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_HAS_TYPENAME_DIFFERENCE_TYPE_H_
