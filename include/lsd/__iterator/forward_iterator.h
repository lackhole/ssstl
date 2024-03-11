//
// Created by cosge on 2023-12-03.
//

#ifndef LSD_ITERATOR_FORWARD_ITERATOR_HPP_
#define LSD_ITERATOR_FORWARD_ITERATOR_HPP_

#include <type_traits>

#include "lsd/__concepts/derived_from.h"
#include "lsd/__iterator/detail/iter_concept.h"
#include "lsd/__iterator/incrementable.h"
#include "lsd/__iterator/input_iterator.h"
#include "lsd/__iterator/iterator_tag.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace detail {

template<typename I, bool = input_iterator<I>::value>
struct forward_iterator_impl : std::false_type {};

template<typename I>
struct forward_iterator_impl<I, true>
    : conjunction<
        derived_from<ITER_CONCEPT<I>, forward_iterator_tag>,
        incrementable<I>,
        sentinel_for<I, I>
      > {};

} // namespace detail

template<typename I>
struct forward_iterator : detail::forward_iterator_impl<I> {};

} // namespace lsd

#endif // LSD_ITERATOR_FORWARD_ITERATOR_HPP_
