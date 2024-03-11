//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_ITERATOR_DETAIL_ITER_CONCEPT_HPP_
#define LSD_ITERATOR_DETAIL_ITER_CONCEPT_HPP_

#include "lsd/__iterator/iterator_traits/cxx20_iterator_traits.h"
#include "lsd/__iterator/iterator_tag.h"

namespace lsd {
namespace detail {

template<typename I>
struct ITER_TRAITS_T {
  using type = std::conditional_t<
      is_primary_iterator_traits< cxx20_iterator_traits<I> >::value,
      I,
      cxx20_iterator_traits<I>>;
};

template<typename I>
using ITER_TRAITS = typename ITER_TRAITS_T<I>::type;


template<typename I, bool = is_primary_iterator_traits< cxx20_iterator_traits<I> >::value /* false */>
struct ITER_CONCEPT_IMPL_3 {};
template<typename I>
struct ITER_CONCEPT_IMPL_3<I, true> {
  using type = random_access_iterator_tag;
};

template<typename I, bool = has_typename_iterator_category<ITER_TRAITS<I>>::value /* false */>
struct ITER_CONCEPT_IMPL_2 : ITER_CONCEPT_IMPL_3<I> {};
template<typename I>
struct ITER_CONCEPT_IMPL_2<I, true> {
  using type = typename ITER_TRAITS<I>::iterator_category;
};

template<typename I, bool = has_typename_iterator_concept<ITER_TRAITS<I>>::value /* false */>
struct ITER_CONCEPT_IMPL_1 : ITER_CONCEPT_IMPL_2<I> {};
template<typename I>
struct ITER_CONCEPT_IMPL_1<I, true> {
  using type = typename ITER_TRAITS<I>::iterator_concept;
};

template<typename I>
struct ITER_CONCEPT_T : ITER_CONCEPT_IMPL_1<I> {};

template<typename I>
using ITER_CONCEPT = typename ITER_CONCEPT_T<I>::type;

} // namespace detail
} // namespace lsd

#endif // LSD_ITERATOR_DETAIL_ITER_CONCEPT_HPP_
