//
// Created by yonggyulee on 2023/12/27.
//

#ifndef LSD_CONCEPTS_FLOATING_POINT_HPP
#define LSD_CONCEPTS_FLOATING_POINT_HPP

#include <type_traits>

namespace lsd {

template<typename T>
struct floating_point : std::is_floating_point<T> {};

} // namespace lsd

#endif // LSD_CONCEPTS_FLOATING_POINT_HPP
