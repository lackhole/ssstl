//
// Created by YongGyu Lee on 1/26/24.
//

#ifndef LSD_TYPE_TRAITS_MAYBE_CONST_HPP
#define LSD_TYPE_TRAITS_MAYBE_CONST_HPP

#include <type_traits>

namespace lsd {

template<bool Const, typename V>
using maybe_const = std::conditional_t<Const, const V, V>;

} // namespace lsd

#endif // LSD_TYPE_TRAITS_MAYBE_CONST_HPP
