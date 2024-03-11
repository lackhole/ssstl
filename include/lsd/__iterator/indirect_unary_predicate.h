//
// Created by yonggyulee on 2024/01/12.
//

#ifndef LSD_ITERATOR_INDIRECT_UNARY_PREDICATE_HPP
#define LSD_ITERATOR_INDIRECT_UNARY_PREDICATE_HPP

#include <type_traits>

#include "lsd/__concepts/copy_constructible.h"
#include "lsd/__concepts/predicate.h"
#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/iter_common_reference_t.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__iterator/iter_value_t.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace detail {

template<typename F, typename I, bool = conjunction<indirectly_readable<I>, copy_constructible<F>>::value /* false */>
struct indirect_unary_predicate_impl : std::false_type {};

template<typename F, typename I>
struct indirect_unary_predicate_impl<F, I, true>
    : conjunction<
          predicate<F&, iter_value_t<I>>,
          predicate<F&, iter_reference_t<I>>,
          predicate<F&, iter_common_reference_t<I>>
      > {};

} // namespace detail

template<typename F, typename I>
struct indirect_unary_predicate : detail::indirect_unary_predicate_impl<F, I> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECT_UNARY_PREDICATE_HPP
