//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_ITERATOR_INPUT_OR_OUTPUT_ITERATOR_HPP_
#define LSD_ITERATOR_INPUT_OR_OUTPUT_ITERATOR_HPP_

#include "lsd/__concepts/dereferenceable.h"
#include "lsd/__iterator/weakly_incrementable.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {

template<typename I>
struct input_or_output_iterator
    : conjunction<
        dereferenceable<I>,
        weakly_incrementable<I>
      > {};

} // namespace lsd

#endif // LSD_ITERATOR_INPUT_OR_OUTPUT_ITERATOR_HPP_
