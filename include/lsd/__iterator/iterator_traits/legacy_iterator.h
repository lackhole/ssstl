//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_ITERATOR_HPP_
#define LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_ITERATOR_HPP_

#include <type_traits>

#include "lsd/__concepts/copyable.h"
#include "lsd/__concepts/dereferenceable.h"
#include "lsd/__iterator/weakly_incrementable.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_referenceable.h"

namespace lsd {
namespace detail {

template<typename I, bool = dereferenceable<decltype(std::declval<I&>()++)>::value>
struct LegacyIteratorCheckPostIncrement_2 : std::false_type {};
template<typename I>
struct LegacyIteratorCheckPostIncrement_2<I, true> : is_referencable<decltype(*std::declval<I&>()++)> {};

template<typename I, bool = lsd::detail::is_post_incrementable<I>::value>
struct LegacyIteratorCheckPostIncrement : std::false_type {};
template<typename I>
struct LegacyIteratorCheckPostIncrement<I, true> : LegacyIteratorCheckPostIncrement_2<I> {};

} // namespace detail

template<typename I, bool = dereferenceable<I>::value>
struct LegacyIterator : std::false_type {};

template<typename I>
struct LegacyIterator<I, true>
    : conjunction<
        is_referencable<decltype(*std::declval<I&>())>,
        detail::is_pre_incrementable<I>,
        detail::LegacyIteratorCheckPostIncrement<I>,
        copyable<I>
> {};

} // namespace lsd

#endif // LSD_ITERATOR_ITERATOR_TRAITS_LEGACY_ITERATOR_HPP_
