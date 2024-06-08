//
// Created by yonggyulee on 2023/12/29.
//

#ifndef LSD_ITERATOR_INDIRECTLY_COMPARABLE_H_
#define LSD_ITERATOR_INDIRECTLY_COMPARABLE_H_

#include <type_traits>

#include "lsd/__functional/identity.h"
#include "lsd/__iterator/indirect_binary_predicate.h"
#include "lsd/__iterator/projected.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace detail {

template<
    typename I1,
    typename I2,
    typename Comp,
    typename Proj1,
    typename Proj2,
    bool = conjunction<projectable<I1, Proj1>, projectable<I2, Proj2>>::value /* true */
>
struct indirectly_comparable_impl
    : indirect_binary_predicate<Comp, projected<I1, Proj1>, projected<I2, Proj2>> {};

template<typename I1, typename I2, typename Comp, typename Proj1, typename Proj2>
struct indirectly_comparable_impl<I1, I2, Comp, Proj1, Proj2, false> : std::false_type {};

} // namespace detail

template<typename I1, typename I2, typename Comp,
         typename Proj1 = identity, typename Proj2 = identity>
struct indirectly_comparable : detail::indirectly_comparable_impl<I1, I2, Comp, Proj1, Proj2> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECTLY_COMPARABLE_H_
