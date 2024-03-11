//
// Created by cosge on 2023-12-29.
//

#ifndef LSD_ITERATOR_PROJECTED_HPP
#define LSD_ITERATOR_PROJECTED_HPP

#include "lsd/__iterator/indirect_result_t.h"
#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/indirectly_regular_unary_invocable.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__iterator/weakly_incrementable.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace detail {

template<typename I, bool = weakly_incrementable<I>::value /* true */>
struct projected_impl_difference_type {
  using difference_type = iter_difference_t<I>;
};
template<typename I>
struct projected_impl_difference_type<I, false> {};

template<
    typename I,
    typename Proj,
    bool = conjunction<
               indirectly_readable<I>,
               indirectly_regular_unary_invocable<Proj, I>
           >::value /* true */
>
struct projected_impl {
  struct type : projected_impl_difference_type<I> {
    using value_type = remove_cvref_t<indirect_result_t<Proj, I>>;

    indirect_result_t<Proj&, I> operator*() const;
  };
};

template<typename I, typename Proj>
struct projected_impl<I, Proj, false> {};

} // namespace detail

template<typename I, typename Proj>
using projected = typename detail::projected_impl<I, Proj>::type;

// Test if expression `lsd::projected<I, Proj>` is valid in an unqualified context (required until C++20)
template<typename I, typename Proj>
using projectable = has_typename_type<detail::projected_impl<I, Proj>>;

} // namespace lsd

#endif // LSD_ITERATOR_PROJECTED_HPP
