//
// Created by yonggyulee on 2023/12/21.
//

#ifndef LSD_CONCEPTS_SUBTRACTABLE_HPP_
#define LSD_CONCEPTS_SUBTRACTABLE_HPP_

#include <type_traits>

#include "lsd/__concepts/implicit_expression_check.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_referenceable.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {

template<typename T, typename U, typename = void>
struct is_explicitly_subtractable : std::false_type {};

template<typename T, typename U>
struct is_explicitly_subtractable<T, U, void_t<decltype(std::declval<T>() - std::declval<U>())>> : std::true_type {};

template<typename T, bool = is_referencable<T>::value>
struct is_subtractable_impl : std::false_type {};

template<typename T>
struct is_subtractable_impl<T, true> : implicit_expression_check<is_explicitly_subtractable, const T&, const T&> {};

template<typename T>
struct subtractable : is_subtractable_impl<T> {};

} // namespace lsd

#endif // LSD_CONCEPTS_SUBTRACTABLE_HPP_
