//
// Created by yonggyulee on 1/23/24.
//

#ifndef LSD_SPAN___FORWARD_DECLARE_HPP
#define LSD_SPAN___FORWARD_DECLARE_HPP

#include <cstddef>

#include "lsd/__span/dynamic_extent.h"

namespace lsd {

template<typename T, std::size_t Extent = dynamic_extent>
class span;

} // namespace lsd

#endif // LSD_SPAN___FORWARD_DECLARE_HPP
