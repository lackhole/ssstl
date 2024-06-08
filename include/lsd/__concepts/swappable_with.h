//
// Created by cosge on 2023-12-03.
//

#ifndef LSD_CONCEPTS_SWAPPABLE_WITH_H_
#define LSD_CONCEPTS_SWAPPABLE_WITH_H_

#include <type_traits>

#include "lsd/__concepts/common_reference_with.h"
#include "lsd/__concepts/swap.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace detail {

template<typename T, typename U, typename = void>
struct swap_uref_test : std::false_type {};

template<typename T, typename U>
struct swap_uref_test<T, U, void_t<decltype( ranges::swap(std::declval<T>(), std::declval<U>()) )>> : std::true_type {};

template<typename T, typename U, bool = common_reference_with<T, U>::value /* false */>
struct swappable_with_impl : std::false_type {};

template<typename T, typename U>
struct swappable_with_impl<T, U, true>
    : conjunction<
          swap_uref_test<T, T>,
          swap_uref_test<U, U>,
          swap_uref_test<T, U>,
          swap_uref_test<U, T>
      > {};

} // namespace detail

template<typename T, typename U>
struct swappable_with : detail::swappable_with_impl<T, U> {};

} // namespace lsd

#endif // LSD_CONCEPTS_SWAPPABLE_WITH_H_
