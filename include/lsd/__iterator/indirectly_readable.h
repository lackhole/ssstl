//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_ITERATOR_INDIRECTLY_READABLE_H_
#define LSD_ITERATOR_INDIRECTLY_READABLE_H_

#include <type_traits>

#include "lsd/__concepts/common_reference_with.h"
#include "lsd/__concepts/dereferenceable.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__iterator/iter_rvalue_reference_t.h"
#include "lsd/__iterator/iter_value_t.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"
#include "lsd/__type_traits/is_referenceable.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

template<typename In, bool = is_referencable<In>::value>
struct indirectly_readable_impl : std::false_type {};

template<typename In>
struct indirectly_readable_impl<In, true>
    : conjunction<
        common_reference_with<iter_reference_t<In>&&, iter_value_t<In>&>,
        common_reference_with<iter_reference_t<In>&&, iter_rvalue_reference_t<In>&&>,
        common_reference_with<iter_rvalue_reference_t<In>&&, const iter_value_t<In>&>
      >{};

template<
  typename In,
  bool = conjunction<
        dereferenceable<const In>,
        has_typename_type<iter_value<In>>,
        has_typename_type<iter_reference<In>>,
        has_typename_type<iter_rvalue_reference<In>>
      >::value
>
struct indirectly_readable_requires : std::false_type {};

template<typename In>
struct indirectly_readable_requires<In, true>
    : conjunction<
        same_as<decltype(*std::declval<const In&>()), iter_reference_t<In>>,
        same_as<decltype(ranges::iter_move(std::declval<const In&>())), iter_rvalue_reference_t<In>>,
        indirectly_readable_impl<In>
      > {};

} // namespace detail

template<typename In>
struct indirectly_readable : detail::indirectly_readable_requires<remove_cvref_t<In>> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECTLY_READABLE_H_
