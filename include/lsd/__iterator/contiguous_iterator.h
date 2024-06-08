//
// Created by cosge on 2023-12-03.
//

#ifndef LSD_ITERATOR_CONTIGUOUS_ITERATOR_H_
#define LSD_ITERATOR_CONTIGUOUS_ITERATOR_H_

#include <type_traits>

#include "lsd/__concepts/derived_from.h"
#include "lsd/__concepts/same_as.h"
#include "lsd/__iterator/detail/iter_concept.h"
#include "lsd/__iterator/iterator_traits/legacy_random_access_iterator.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__iterator/iter_value_t.h"
#include "lsd/__iterator/iterator_tag.h"
#include "lsd/__iterator/random_access_iterator.h"
#include "lsd/__memory/to_address.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"
#include "lsd/__type_traits/remove_cvref.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace detail {

template<typename I, typename = void>
struct explicit_contiguous_requires : std::false_type {};
template<typename I>
struct explicit_contiguous_requires<
        I,
        void_t<decltype( lsd::to_address( std::declval<I>() ) )>
    > : same_as<decltype( lsd::to_address( std::declval<I>() ) ), std::add_pointer_t<iter_reference_t<remove_cvref_t<I>>>> {};

template<typename I>
struct contiguous_requires : implicit_expression_check<explicit_contiguous_requires, const I&> {};

template<
    typename I,
    bool = random_access_iterator<I>::value /* false */
>
struct contiguous_iterator_impl : std::false_type {};

template<typename I>
struct contiguous_iterator_impl<I, true>
    : conjunction<
#if __cplusplus < 202002L
        disjunction<
#endif
            derived_from<ITER_CONCEPT<I>, contiguous_iterator_tag>,
#if __cplusplus < 202002L
            conjunction<
              derived_from<ITER_CONCEPT<I>, random_access_iterator_tag>,
              LegacyRandomAccessIterator<I>
            >
        >,
#endif
        std::is_lvalue_reference<iter_reference_t<I>>,
        same_as<iter_value_t<I>, remove_cvref_t<iter_reference_t<I>>>,
        contiguous_requires<I>
      > {};

} // namespace detail

template<typename I>
struct contiguous_iterator : detail::contiguous_iterator_impl<I> {};

} // namespace lsd

#endif // LSD_ITERATOR_CONTIGUOUS_ITERATOR_H_
