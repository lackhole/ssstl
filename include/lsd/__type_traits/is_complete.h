//
// Created by cosge on 2023-12-03.
//

#ifndef LSD_TYPE_TRAITS_IS_COMPLETE_HPP_
#define LSD_TYPE_TRAITS_IS_COMPLETE_HPP_

#include <cstddef>
#include <type_traits>

namespace lsd {
namespace detail {
template <class T, std::size_t = sizeof(T)>
std::true_type is_complete_impl(T *);

std::false_type is_complete_impl(...);
} // namespace detail

template <class T>
using is_complete = decltype(detail::is_complete_impl(std::declval<T*>()));

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_COMPLETE_HPP_
