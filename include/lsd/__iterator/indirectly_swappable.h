//
// Created by yonggyulee on 2023/12/27.
//

#ifndef LSD_ITERATOR_INDIRECTLY_SWAPPABLE_H_
#define LSD_ITERATOR_INDIRECTLY_SWAPPABLE_H_

#include <type_traits>

#include "lsd/__iterator/indirectly_readable.h"
#include "lsd/__iterator/iter_swap.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace detail {

template<typename I1, typename I2, typename = void>
struct indirectly_swappable_test_iter_swap : std::false_type {};
template<typename I1, typename I2>
struct indirectly_swappable_test_iter_swap<
    I1, I2, void_t<decltype(ranges::iter_swap(std::declval<const I1&>(), std::declval<const I2&>()))>> : std::true_type {};

template<
    typename I1,
    typename I2,
    bool = conjunction< indirectly_readable<I1>, indirectly_readable<I2>>::value /* true */
>
struct indirectly_swappable_impl
    : conjunction<
          indirectly_swappable_test_iter_swap<I1, I1>,
          indirectly_swappable_test_iter_swap<I2, I2>,
          indirectly_swappable_test_iter_swap<I1, I2>,
          indirectly_swappable_test_iter_swap<I2, I1>
      >{};

template<typename I1, typename I2>
struct indirectly_swappable_impl<I1, I2, false> : std::false_type {};

} // namespace detail

template<typename I1, typename I2 = I1>
struct indirectly_swappable : detail::indirectly_swappable_impl<I1, I2> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECTLY_SWAPPABLE_H_
