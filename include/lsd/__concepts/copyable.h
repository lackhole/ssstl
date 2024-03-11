//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_CONCEPTS_COPYABLE_HPP_
#define LSD_CONCEPTS_COPYABLE_HPP_

#include <type_traits>

#include "lsd/__concepts/assignable_from.h"
#include "lsd/__concepts/copy_constructible.h"
#include "lsd/__concepts/movable.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_referenceable.h"

namespace lsd {
namespace detail {

template<typename T, bool = is_referencable<T>::value>
struct copyable_impl
    : conjunction<
        copy_constructible<T>,
        movable<T>,
        assignable_from<T&, T&>,
        assignable_from<T&, const T&>,
        assignable_from<T&, const T>
      > {};

template<typename T>
struct copyable_impl<T, false> : std::false_type {};

} // namespace detail

template<typename T>
struct copyable : detail::copyable_impl<T> {};

} // namespace lsd

#endif // LSD_CONCEPTS_COPYABLE_HPP_
