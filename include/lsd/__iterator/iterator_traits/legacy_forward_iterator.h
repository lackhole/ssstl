//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_FORWARD_ITERATOR_HPP_
#define LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_FORWARD_ITERATOR_HPP_

#include <type_traits>

#include "lsd/__concepts/constructible_from.h"
#include "lsd/__concepts/convertible_to.h"
#include "lsd/__iterator/iterator_traits/legacy_input_iterator.h"
#include "lsd/__iterator/indirectly_readable_traits.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

template<
    typename It,
    bool =
        conjunction<
          constructible_from<It>,
          std::is_reference<iter_reference_t<It>>, // iter_reference_t<It> satisfied in LegacyInputIterator,
          same_as<
              remove_cvref_t<iter_reference_t<It>>,
              typename indirectly_readable_traits<It>::value_type>, // indirectly_readable_traits<It>::value already satisfied
          convertible_to<decltype(std::declval<It&>()++),  const It&>,
          same_as<decltype(*std::declval<It&>()++), iter_reference_t<It>>
        >::value
>
struct LegacyForwardIteratorRequire : std::false_type {};

template<typename It>
struct LegacyForwardIteratorRequire<It, true> : std::true_type {};

} // namespace detail

template<typename It, bool = LegacyInputIterator<It>::value>
struct LegacyForwardIterator : std::false_type {};

template<typename It>
struct LegacyForwardIterator<It, true> : detail::LegacyForwardIteratorRequire<It> {};

} // namespace lsd

#endif // LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_FORWARD_ITERATOR_HPP_
