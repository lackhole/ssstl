//
// Created by YongGyu Lee on 02/01/24.
//

#ifndef LSD_VARIANT_VARIANT_SIZE_H_
#define LSD_VARIANT_VARIANT_SIZE_H_

#include <type_traits>

#include "lsd/__core/inline_or_static.h"

namespace lsd {

template<typename... T>
class variant;

template<typename T>
struct variant_size;

template<typename... Ts>
struct variant_size<variant<Ts...>> : std::integral_constant<std::size_t, sizeof...(Ts)> {};

template<typename T>
struct variant_size<const T> : std::integral_constant<std::size_t, variant_size<T>::value> {};

template<typename T>
LSD_INLINE_OR_STATIC constexpr std::size_t variant_size_v = variant_size<T>::value;

} // namespace lsd

#endif // LSD_VARIANT_VARIANT_SIZE_H_
