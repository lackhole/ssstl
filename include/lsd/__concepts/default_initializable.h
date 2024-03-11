//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_CONCEPTS_DEFAULT_INITIALIZABLE_HPP_
#define LSD_CONCEPTS_DEFAULT_INITIALIZABLE_HPP_

#include "lsd/__concepts/constructible_from.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace detail {

template<typename T, typename = void>
struct is_direct_list_initializable : std::false_type {};
template<typename T>
struct is_direct_list_initializable<T, void_t<decltype(T{})>> : std::true_type {};

template<typename T, typename = void>
struct is_default_initializable : std::false_type {};
template<typename T>
struct is_default_initializable<T, void_t<decltype(::new T)>> : std::true_type {};

} // namespace detail

template<typename T>
struct default_initializable
    : conjunction<
        constructible_from<T>,
        detail::is_direct_list_initializable<T>,
        detail::is_default_initializable<T>
      > {};

} // namespace lsd

#endif // LSD_CONCEPTS_DEFAULT_INITIALIZABLE_HPP_