//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_INPUT_ITERATOR_H_
#define LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_INPUT_ITERATOR_H_

#include <type_traits>

#include "lsd/__concepts/equality_comparable.h"
#include "lsd/__concepts/signed_integral.h"
#include "lsd/__iterator/iterator_traits/legacy_iterator.h"
#include "lsd/__iterator/incrementable_traits.h"
#include "lsd/__iterator/indirectly_readable_traits.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__type_traits/common_reference.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_value_type.h"
#include "lsd/__type_traits/has_typename_difference_type.h"

namespace lsd {
namespace detail {

template<
    typename I,
    bool = conjunction<
             LegacyIterator<I>,
             equality_comparable<I>,
             has_typename_difference_type<incrementable_traits<I>>,
             has_typename_value_type<indirectly_readable_traits<I>>,
             has_typename_type<iter_reference<I>>
           >::value
>
struct LegacyInputIteratorRequiresStage1 : std::false_type {};

template<typename I>
struct LegacyInputIteratorRequiresStage1<I, true>
    : conjunction<
        has_typename_type<common_reference<iter_reference_t<I>&&,
                                           typename indirectly_readable_traits<I>::value_type&>>,
        has_typename_type<common_reference<decltype(*std::declval<I&>()++)&&, // *i++ satisfied in LegacyIterator<I>
                                           typename indirectly_readable_traits<I>::value_type&>>,
        signed_integral<typename incrementable_traits<I>::difference_type>
      > {};

} // namespace detail

template<typename I, bool = is_referencable<I>::value>
struct LegacyInputIterator : std::false_type {};

template<typename I>
struct LegacyInputIterator<I, true> : detail::LegacyInputIteratorRequiresStage1<I> {};

} // namespace lsd

#endif // LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_INPUT_ITERATOR_H_
