//
// Created by cosge on 2023-12-03.
//

#ifndef LSD_ITERATOR_BIDIRECTIONAL_ITERATOR_H_
#define LSD_ITERATOR_BIDIRECTIONAL_ITERATOR_H_

#include <type_traits>

#include "lsd/__concepts/derived_from.h"
#include "lsd/__concepts/same_as.h"
#include "lsd/__iterator/iterator_traits/legacy_bidirectional_iterator.h"
#include "lsd/__iterator/forward_iterator.h"
#include "lsd/__iterator/iterator_tag.h"

namespace lsd {
namespace detail {

template<typename T, typename = void>
struct is_post_decrementable_bidi_iter : std::false_type {};

template<typename T>
struct is_post_decrementable_bidi_iter<T, void_t<decltype( std::declval<T&>()-- )>>
    : same_as<decltype( std::declval<T&>()-- ), T> {};

template<typename I, bool = forward_iterator<I>::value>
struct bidirectional_iterator_impl : std::false_type {};

template<typename I>
struct bidirectional_iterator_impl<I, true>
    : conjunction<
        derived_from<ITER_CONCEPT<I>, bidirectional_iterator_tag>,
        is_pre_decrementable<I>,
        is_post_decrementable_bidi_iter<I>
      > {};

} // namespace detail

template<typename I>
struct bidirectional_iterator : detail::bidirectional_iterator_impl<I> {};

} // namespace lsd

#endif // LSD_ITERATOR_BIDIRECTIONAL_ITERATOR_H_
