//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_CONCEPTS_MOVABLE_HPP_
#define LSD_CONCEPTS_MOVABLE_HPP_

#include <type_traits>

#include "lsd/__concepts/assignable_from.h"
#include "lsd/__concepts/move_constructible.h"
#include "lsd/__concepts/swappable.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_swappable.h"
#include "lsd/__type_traits/is_referenceable.h"

namespace lsd {
namespace detail {

template<typename T, bool = is_referencable<T>::value /* true */>
struct movable_impl
    : conjunction<
        std::is_object<T>,
        move_constructible<T>,
        assignable_from<T&, T>,
        swappable<T>
      > {};

template<typename T>
struct movable_impl<T, false> : std::false_type {};

} // namespace detail

template<typename T>
struct movable : detail::movable_impl<T> {};

} // namespace lsd

#endif // LSD_CONCEPTS_MOVABLE_HPP_
