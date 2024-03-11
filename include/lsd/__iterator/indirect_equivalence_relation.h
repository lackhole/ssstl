//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_ITERATOR_INDIRECT_EQUIVALENCE_RELATION_HPP
#define LSD_ITERATOR_INDIRECT_EQUIVALENCE_RELATION_HPP

#include <type_traits>

#include "lsd/__concepts/copy_constructible.h"
#include "lsd/__concepts/equivalence_relation.h"
#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/iter_common_reference_t.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__iterator/iter_value_t.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace detail {

template<typename F, typename I1, typename I2>
struct indirect_equivalence_relation_impl_2
    : conjunction<
          equivalence_relation<F&, iter_value_t<I1>&, iter_value_t<I2>&>,
          equivalence_relation<F&, iter_value_t<I1>&, iter_reference_t<I2>>,
          equivalence_relation<F&, iter_reference_t<I1>, iter_value_t<I2>&>,
          equivalence_relation<F&, iter_reference_t<I1>, iter_reference_t<I2>>,
          equivalence_relation<F&, iter_common_reference_t<I1>, iter_common_reference_t<I2>>
      > {};

template<typename F, typename I1, typename I2, bool = conjunction<
    indirectly_readable<I1>,
    indirectly_readable<I2>,
    copy_constructible<F>
>::value /* true */>
struct indirect_equivalence_relation_impl_1 : indirect_equivalence_relation_impl_2<F, I1, I2> {};
template<typename F, typename I1, typename I2>
struct indirect_equivalence_relation_impl_1<F, I1, I2, false> : std::false_type {};

} // namespace detail

template<typename F, typename I1, typename I2 = I1>
struct indirect_equivalence_relation : detail::indirect_equivalence_relation_impl_1<F, I1, I2> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECT_EQUIVALENCE_RELATION_HPP
