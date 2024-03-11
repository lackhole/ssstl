//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_BIDIRECTIONAL_ITERATOR_HPP_
#define LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_BIDIRECTIONAL_ITERATOR_HPP_

#include <type_traits>

#include "lsd/__concepts/constructible_from.h"
#include "lsd/__concepts/convertible_to.h"
#include "lsd/__concepts/same_as.h"
#include "lsd/__iterator/iterator_traits/legacy_forward_iterator.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

template<typename T, typename = void>
struct is_pre_decrementable : std::false_type {};

template<typename T>
struct is_pre_decrementable<T, void_t<decltype( --std::declval<T&>() )>>
    : same_as<decltype( --std::declval<T&>() ), T&> {};

template<typename T, typename = void>
struct is_post_decrementable : std::false_type {};

template<typename T>
struct is_post_decrementable<T, void_t<decltype( std::declval<T&>()-- )>>
      : convertible_to<decltype(std::declval<T&>()--), const T&> {};

template<
    typename It,
    bool = dereferenceable<decltype(std::declval<It&>()--)>::value
>
struct LegacyBidirectionalIteratorRequireStage2 : std::false_type {};

template<typename It>
struct LegacyBidirectionalIteratorRequireStage2<It, true> // vvvvvvvvvvvvv already satisfied
    : same_as<decltype(*std::declval<It&>()--), iter_reference_t<It>> {};
// iter_reference_t<It> already satisfied in LegacyInputIterator ^^^^^^^^^

template<
    typename It,
    bool =
        conjunction<
          is_pre_decrementable<It>,
          is_post_decrementable<It>
        >::value
>
struct LegacyBidirectionalIteratorRequireStage1 : std::false_type {};

template<typename It>
struct LegacyBidirectionalIteratorRequireStage1<It, true> : LegacyBidirectionalIteratorRequireStage2<It> {};

} // namespace detail

template<typename It, bool = LegacyForwardIterator<It>::value>
struct LegacyBidirectionalIterator : std::false_type {};

template<typename It>
struct LegacyBidirectionalIterator<It, true> : detail::LegacyBidirectionalIteratorRequireStage1<It> {};

} // namespace lsd

#endif // LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_BIDIRECTIONAL_ITERATOR_HPP_
