//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_ITERATOR_INDIRECT_STRICT_WEAK_ORDER_HPP
#define LSD_ITERATOR_INDIRECT_STRICT_WEAK_ORDER_HPP

#include <type_traits>

#include "lsd/__concepts/copy_constructible.h"
#include "lsd/__concepts/strict_weak_order.h"
#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/iter_common_reference_t.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__iterator/iter_value_t.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace detail {

template<
    typename F,
    typename I1,
    typename I2,
    bool = conjunction<
               indirectly_readable<I1>,
               indirectly_readable<I2>,
               copy_constructible<F>,
               has_typename_type<iter_common_reference<I1>>,
               has_typename_type<iter_common_reference<I2>>
           >::value /* false */
>
struct indirect_strict_weak_order_impl_1 : std::false_type {};


template<typename F, typename I1, typename I2>
struct indirect_strict_weak_order_impl_1<F, I1, I2, true>
    : conjunction<
          strict_weak_order<F&, iter_value_t<I1>&,           iter_value_t<I2>&>,
          strict_weak_order<F&, iter_value_t<I1>&,           iter_reference_t<I2>&>,
          strict_weak_order<F&, iter_reference_t<I1>&,       iter_value_t<I2>&>,
          strict_weak_order<F&, iter_reference_t<I1>&,       iter_reference_t<I2>&>,
          strict_weak_order<F&, iter_common_reference_t<I1>, iter_common_reference_t<I2>>
      > {};

} // namespace detail

template<typename F, typename I1, typename I2 = I1>
struct indirect_strict_weak_order : detail::indirect_strict_weak_order_impl_1<F, I1, I2> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECT_STRICT_WEAK_ORDER_HPP
