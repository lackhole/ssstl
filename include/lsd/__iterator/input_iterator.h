//
// Created by cosge on 2023-12-03.
//

#ifndef LSD_ITERATOR_INPUT_ITERATOR_H_
#define LSD_ITERATOR_INPUT_ITERATOR_H_

#include <type_traits>

#include "lsd/__concepts/derived_from.h"
#include "lsd/__iterator/detail/iter_concept.h"
#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/input_or_output_iterator.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace detail {

template<
    typename I,
    bool = conjunction<
             input_or_output_iterator<I>,
             indirectly_readable<I>,
             has_typename_type<ITER_CONCEPT_T<I>>
           >::value
>
struct input_iterator_impl : std::false_type {};

template<typename I>
struct input_iterator_impl<I, true>
    : derived_from<ITER_CONCEPT<I>, input_iterator_tag> {};

} // namespace detail

template<typename I>
struct input_iterator : detail::input_iterator_impl<I> {};

} // namespace lsd

#endif // LSD_ITERATOR_INPUT_ITERATOR_H_
