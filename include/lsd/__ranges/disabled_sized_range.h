//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_DISABLED_SIZED_RANGE_HPP_
#define LSD_RANGES_DISABLED_SIZED_RANGE_HPP_

#include <type_traits>

namespace lsd {
namespace ranges {

template<typename T>
struct disabled_sized_range : std::false_type {};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_DISABLED_SIZED_RANGE_HPP_
