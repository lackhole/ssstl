//
// Created by cosge on 2023-12-31.
//

#ifndef LSD_ITERATOR_OUTPUT_ITERATOR_HPP
#define LSD_ITERATOR_OUTPUT_ITERATOR_HPP

#include <type_traits>

#include "lsd/__iterator/indirectly_writable.h"
#include "lsd/__iterator/input_or_output_iterator.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace detail {

template<
    typename I,
    typename T,
    bool = conjunction<
               input_or_output_iterator<I>,
               indirectly_writable<I, T>
           >::value
>
struct output_iterator_impl
    : std::is_assignable<
          decltype(*std::declval<I&>()++),
          decltype(std::forward<T>(std::declval<T&&>()))
      > {};

template<typename I, typename T>
struct output_iterator_impl<I, T, false> : std::false_type {};

} // namespace detail

template<typename I, typename T>
struct output_iterator : detail::output_iterator_impl<I, T> {};

} // namespace lsd

#endif // LSD_ITERATOR_OUTPUT_ITERATOR_HPP
