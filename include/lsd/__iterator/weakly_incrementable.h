//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_ITERATOR_WEAKLY_INCREMENTABLE_HPP_
#define LSD_ITERATOR_WEAKLY_INCREMENTABLE_HPP_

#include <type_traits>

#include "lsd/__concepts/same_as.h"
#include "lsd/__concepts/movable.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"
#include "lsd/__type_traits/is_integer_like.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace detail {

template<typename T, bool = has_typename_type<iter_difference<T>>::value>
struct is_signed_integer_like_iter_difference : std::false_type {};

template<typename T>
struct is_signed_integer_like_iter_difference<T, true>
    : is_signed_integer_like<iter_difference_t<T>> {};

template<typename T, typename = void>
struct is_pre_incrementable : std::false_type {};

template<typename T>
struct is_pre_incrementable<T, void_t<decltype( ++std::declval<T&>() )>> : same_as<decltype( ++std::declval<T&>() ), T&> {};

template<typename T, typename = void>
struct is_post_incrementable : std::false_type {};

template<typename T>
struct is_post_incrementable<T, void_t<decltype( std::declval<T&>()++ )>> : std::true_type {};

} // namespace detail

template<typename I>
struct weakly_incrementable
    : conjunction<
        movable<I>,
        detail::is_signed_integer_like_iter_difference<I>,
        detail::is_pre_incrementable<I>,
        detail::is_post_incrementable<I>
      > {};

} // namespace lsd

#endif // LSD_ITERATOR_WEAKLY_INCREMENTABLE_HPP_
