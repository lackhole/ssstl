//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_ENABLE_BORROWED_RANGE_HPP_
#define LSD_RANGES_ENABLE_BORROWED_RANGE_HPP_

#include <type_traits>

namespace lsd {
namespace ranges {

template<typename R>
struct enable_borrowed_range : std::false_type {};

} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_ENABLE_BORROWED_RANGE_HPP_
