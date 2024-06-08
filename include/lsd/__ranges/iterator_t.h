//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_RANGES_ITERATOR_T_H_
#define LSD_RANGES_ITERATOR_T_H_

#include <type_traits>

#include "lsd/__ranges/begin.h"
#include "lsd/__type_traits/is_referenceable.h"

namespace lsd {
namespace ranges {

template<typename T, bool = is_referencable<T>::value, typename = void>
struct iterator {};

template<typename T>
struct iterator<T, true, void_t<decltype( ranges::begin(std::declval<T&>()) )>> {
  using type = decltype(ranges::begin(std::declval<T&>()));
};

template<typename T>
using iterator_t = typename ranges::iterator<T>::type;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_ITERATOR_T_H_
