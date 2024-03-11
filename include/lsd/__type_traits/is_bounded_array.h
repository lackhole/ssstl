//
// Created by yonggyulee on 2023/09/29.
//

#ifndef LSD_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
#define LSD_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP

#include <cstddef>
#include <type_traits>

namespace lsd {

template<class T>
struct is_bounded_array : std::false_type {};

template<class T, std::size_t N>
struct is_bounded_array<T[N]> : std::true_type {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_BOUNDED_ARRAY_HPP
