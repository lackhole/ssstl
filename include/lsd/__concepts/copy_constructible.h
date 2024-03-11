//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_CONCEPTS_COPY_CONSTRUCTIBLE_HPP_
#define LSD_CONCEPTS_COPY_CONSTRUCTIBLE_HPP_

#include "lsd/__concepts/move_constructible.h"
#include "lsd/__concepts/constructible_from.h"
#include "lsd/__concepts/convertible_to.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_referenceable.h"

namespace lsd {
namespace detail {

template<typename T, bool = is_referencable<T>::value>
struct copy_constructible_impl
    : conjunction<
        move_constructible<T>,
        constructible_from<T, T&>, convertible_to<T&, T>,
        constructible_from<T, const T&>, convertible_to<const T&, T>,
        constructible_from<T, const T>, convertible_to<const T, T>
      > {};

template<typename T>
struct copy_constructible_impl<T, false> : std::false_type {};

} // namespace detail

template<typename T>
struct copy_constructible : detail::copy_constructible_impl<T> {};

} // namespace lsd

#endif // LSD_CONCEPTS_COPY_CONSTRUCTIBLE_HPP_
