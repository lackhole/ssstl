//
// Created by yonggyulee on 2023/12/29.
//

#ifndef LSD_ITERATOR_INDIRECT_UNARY_INVOCABLE_H_
#define LSD_ITERATOR_INDIRECT_UNARY_INVOCABLE_H_

#include <type_traits>

#include "lsd/__concepts/common_reference_with.h"
#include "lsd/__concepts/copy_constructible.h"
#include "lsd/__concepts/invocable.h"
#include "lsd/__functional/invoke.h"
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
    typename I,
    bool v = conjunction<
                 invocable<F&, iter_value_t<I>&>,
                 invocable<F&, iter_reference_t<I>>,
                 invocable<F&, iter_common_reference_t<I>>
             >::value /* true */
>
struct indirectly_unary_invocable_impl_2
    : common_reference_with<
          invoke_result_t<F&, iter_value_t<I>&>,
          invoke_result_t<F&, iter_reference_t<I>>
      > {};

template<typename F, typename I>
struct indirectly_unary_invocable_impl_2<F, I, false> : std::false_type {};

template<
    typename F,
    typename I,
    bool v = conjunction<
                 indirectly_readable<I>,
                 copy_constructible<F>,
                 has_typename_type< iter_common_reference<I> >
             >::value /* true */
>
struct indirectly_unary_invocable_impl_1 : indirectly_unary_invocable_impl_2<F, I> {};

template<typename F, typename I>
struct indirectly_unary_invocable_impl_1<F, I, false> : std::false_type {};

} // namespace detail

template<typename F, typename I>
struct indirectly_unary_invocable : detail::indirectly_unary_invocable_impl_1<F, I> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECT_UNARY_INVOCABLE_H_
