//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_ITERATOR_DETAIL_ITER_MOVE_STD_HPP_
#define LSD_ITERATOR_DETAIL_ITER_MOVE_STD_HPP_

#if __cplusplus < 202002L

#include <iterator>
#include <type_traits>

#include "lsd/__iterator/iter_move.h"
#include "lsd/__iterator/iter_rvalue_reference_t.h"

namespace std {

template<typename Iter>
constexpr lsd::iter_rvalue_reference_t<Iter>
iter_move(const reverse_iterator<Iter>& i)
    noexcept(
      is_nothrow_copy_constructible<Iter>::value &&
      noexcept(lsd::ranges::iter_move(--declval<Iter&>()))
    )
{
  auto tmp = i.base();
  return lsd::ranges::iter_move(--tmp);
}

template<typename Iter>
constexpr lsd::iter_rvalue_reference_t<Iter>
iter_move(const move_iterator<Iter>& i)
    noexcept(noexcept(lsd::ranges::iter_move(--declval<Iter&>())))
{
  return lsd::ranges::iter_move(i.base());
}

} // namespace std

#endif

#endif // LSD_ITERATOR_DETAIL_ITER_MOVE_STD_HPP_
