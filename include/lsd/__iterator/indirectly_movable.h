//
// Created by yonggyulee on 2024/01/10.
//

#ifndef LSD_ITERATOR_INDIRECTLY_MOVABLE_HPP
#define LSD_ITERATOR_INDIRECTLY_MOVABLE_HPP

#include <type_traits>

#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/indirectly_writable.h"
#include "lsd/__iterator/iter_rvalue_reference_t.h"

namespace lsd {
namespace detail {

template<typename In, typename Out, bool = indirectly_readable<In>::value /* true */>
struct indirectly_movable_impl
    : indirectly_writable<Out, iter_rvalue_reference_t<In>> {};

template<typename In, typename Out>
struct indirectly_movable_impl<In, Out, false> : std::false_type {};

} // namespace detail

template<typename In, typename Out>
struct indirectly_movable : detail::indirectly_movable_impl<In, Out> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECTLY_MOVABLE_HPP
