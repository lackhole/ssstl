//
// Created by yonggyulee on 2023/09/29.
//

#ifndef LSD_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_H_
#define LSD_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_H_

#include <cstddef>
#include <type_traits>

namespace lsd {

template<class T>
struct is_unbounded_array: std::false_type {};

template<class T>
struct is_unbounded_array<T[]> : std::true_type {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_UNBOUNDED_ARRAY_H_
