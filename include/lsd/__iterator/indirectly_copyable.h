//
// Created by yonggyulee on 2024/01/08.
//

#ifndef LSD_ITERATOR_INDIRECTLY_COPYABLE_HPP
#define LSD_ITERATOR_INDIRECTLY_COPYABLE_HPP

#include <type_traits>

#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/indirectly_writable.h"
#include "lsd/__iterator/iter_reference_t.h"

namespace lsd {
namespace detail {

template<typename In, typename Out, bool = indirectly_readable<In>::value /* true */>
struct indirectly_copyable_impl
    : indirectly_writable<Out, iter_reference_t<In>> {};

template<typename In, typename Out>
struct indirectly_copyable_impl<In, Out, false> : std::false_type {};

} // namespace detail

template<typename In, typename Out>
struct indirectly_copyable : detail::indirectly_copyable_impl<In, Out> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECTLY_COPYABLE_HPP
