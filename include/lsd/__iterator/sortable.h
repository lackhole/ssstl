//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_ITERATOR_SORTABLE_H_
#define LSD_ITERATOR_SORTABLE_H_

#include <type_traits>

#include "lsd/__functional/identity.h"
#include "lsd/__functional/less.h"
#include "lsd/__iterator/indirect_strict_weak_order.h"
#include "lsd/__iterator/permutable.h"
#include "lsd/__iterator/projected.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace detail {

template<typename I, typename Comp, typename Proj,
    bool = conjunction<
        permutable<I>,
        projectable<I, Proj>
    >::value /* false */>
struct sortable_impl : std::false_type {};

template<typename I, typename Comp, typename Proj>
struct sortable_impl<I, Comp, Proj, true>
    : indirect_strict_weak_order<Comp, projected<I, Proj>> {};

} // namespace detail

template<typename I, typename Comp = ranges::less, typename Proj = identity>
struct sortable : detail::sortable_impl<I, Comp, Proj> {};

} // namespace lsd

#endif // LSD_ITERATOR_SORTABLE_H_
