//
// Created by yonggyulee on 1/24/24.
//

#ifndef LSD_TYPE_TRAITS_HAS_OPERATOR_ARROW_HPP
#define LSD_TYPE_TRAITS_HAS_OPERATOR_ARROW_HPP

#include <type_traits>

#include "lsd/__type_traits/void_t.h"

namespace lsd {

template<typename T, typename = void>
struct has_operator_arrow : std::false_type {};

template<typename T>
struct has_operator_arrow<T, void_t<decltype(std::declval<T>().operator->())>> : std::true_type {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_HAS_OPERATOR_ARROW_HPP
