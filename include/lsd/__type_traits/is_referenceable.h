//
// Created by yonggyulee on 2023/10/27.
//

#ifndef LSD_TYPE_TRAITS_IS_REFERENCEABLE_H_
#define LSD_TYPE_TRAITS_IS_REFERENCEABLE_H_

#include <type_traits>

#include "lsd/__type_traits/void_t.h"

namespace lsd {

template<typename T, typename = void>
struct is_referencable : std::false_type {};

template<typename T>
struct is_referencable<T, void_t<T&>> : std::true_type {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_REFERENCEABLE_H_
