//
// Created by YongGyu Lee on 4/15/24.
//

#ifndef LSD_ITERATOR_MOVE_ITERATOR_HPP_
#define LSD_ITERATOR_MOVE_ITERATOR_HPP_

#include <iterator>
#include <type_traits>

#include "lsd/__core/constexpr.h"
#include "lsd/__concepts/derived_from.h"
#include "lsd/__iterator/bidirectional_iterator.h"
#include "lsd/__iterator/forward_iterator.h"
#include "lsd/__iterator/indirectly_swappable.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__iterator/iter_move.h"
#include "lsd/__iterator/iter_rvalue_reference_t.h"
#include "lsd/__iterator/iter_value_t.h"
#include "lsd/__iterator/iterator_tag.h"
#include "lsd/__iterator/iterator_traits/cxx20_iterator_traits.h"
#include "lsd/__iterator/sized_sentinel_for.h"
#include "lsd/__iterator/move_sentinel.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__iterator/random_access_iterator.h"
#include "lsd/__type_traits/negation.h"

namespace lsd {

template<typename Iterator1, typename Iterator2>
struct disable_sized_sentinel_for<std::move_iterator<Iterator1>, std::move_iterator<Iterator2>>
    : negation<sized_sentinel_for<Iterator1, Iterator2>> {};

#if __cplusplus < 202302L

namespace detail {

template<typename Iter, bool = has_typename_iterator_category<Iter>::value /* false */>
struct move_iterator_category {};

template<typename Iter>
struct move_iterator_category<Iter, true> {
  using iterator_category = std::conditional_t<
      derived_from<typename cxx20_iterator_traits<Iter>::iterator_category, random_access_iterator_tag>::value, random_access_iterator_tag,
      typename cxx20_iterator_traits<Iter>::iterator_category
  >;
};

} // namespace detail

template<typename Iter>
struct cxx20_iterator_traits<std::move_iterator<Iter>>
    : detail::move_iterator_category<Iter>
{
  using iterator_concept =
      std::conditional_t<
          random_access_iterator<Iter>::value, random_access_iterator_tag,
      std::conditional_t<
          bidirectional_iterator<Iter>::value, bidirectional_iterator_tag,
      std::conditional_t<
          forward_iterator<Iter>::value, forward_iterator_tag,
          input_iterator_tag
      >>>;
  using value_type = iter_value_t<Iter>;
  using difference_type = iter_difference_t<Iter>;
  using pointer = Iter;
  using reference = iter_rvalue_reference_t<Iter>;
};

namespace detail {

template<typename Iter>
struct is_primary_iterator_traits<std::move_iterator<Iter>> : std::true_type {};

} // namespace detail

#endif // __cplusplus < 202302L

} // namespace lsd

#if __cplusplus < 202002L

namespace std {

template<typename Iter>
constexpr lsd::iter_rvalue_reference_t<Iter> iter_move(const move_iterator<Iter>& i)
    noexcept(noexcept(lsd::ranges::iter_move(i.base())))
{
  return lsd::ranges::iter_move(i.base());
}

template<typename Iter, typename Iter2, std::enable_if_t<lsd::indirectly_swappable<Iter, Iter2>::value, int> = 0>
constexpr void iter_swap(const move_iterator<Iter>& x, const move_iterator<Iter2>& y)
    noexcept(noexcept(lsd::ranges::iter_swap(x.base(), y.base())))
{
  lsd::ranges::iter_swap(x.base(), y.base());
}

} // namespace std

#endif

#endif // LSD_ITERATOR_MOVE_ITERATOR_HPP_
