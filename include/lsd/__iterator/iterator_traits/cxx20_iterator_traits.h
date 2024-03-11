//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_ITERATOR_ITERATOR_TRAITS_CXX20_ITERATOR_TRAITS_HPP_
#define LSD_ITERATOR_ITERATOR_TRAITS_CXX20_ITERATOR_TRAITS_HPP_

#include <cstddef>
#include <type_traits>

#include "lsd/__iterator/iterator_tag.h"
#include "lsd/__iterator/iterator_traits/forward_declare.h"
#include "lsd/__iterator/iterator_traits/legacy_iterator.h"
#include "lsd/__iterator/iterator_traits/legacy_input_iterator.h"
#include "lsd/__iterator/iterator_traits/legacy_forward_iterator.h"
#include "lsd/__iterator/iterator_traits/legacy_bidirectional_iterator.h"
#include "lsd/__iterator/iterator_traits/legacy_random_access_iterator.h"
#include "lsd/__type_traits/has_typename_difference_type.h"
#include "lsd/__type_traits/has_typename_value_type.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace detail {

template<typename T, typename = void>
struct has_typename_pointer : std::false_type {};
template<typename T>
struct has_typename_pointer<T, void_t<typename T::pointer>> : std::true_type {};

template<typename T, typename = void>
struct has_typename_reference : std::false_type {};
template<typename T>
struct has_typename_reference<T, void_t<typename T::reference>> : std::true_type {};

template<typename T, typename = void>
struct has_typename_iterator_category : std::false_type {};
template<typename T>
struct has_typename_iterator_category<T, void_t<typename T::iterator_category>>
    : negation< std::is_same<iterator_ignore, typename T::iterator_category> > {};

template<typename T, typename = void>
struct has_typename_iterator_concept : std::false_type {};
template<typename T>
struct has_typename_iterator_concept<T, void_t<typename T::iterator_concept>> : std::true_type {};

template<typename Iter, bool = LegacyForwardIterator<Iter>::value /* false */>
struct cxx20_iterator_category_check_forward {
  using type = input_iterator_tag;
};

template<typename Iter>
struct cxx20_iterator_category_check_forward<Iter, true> {
  using type = forward_iterator_tag;
};

template<typename Iter, bool = LegacyBidirectionalIterator<Iter>::value /* false */>
struct cxx20_iterator_category_check_bidirectional
    : cxx20_iterator_category_check_forward<Iter> {};

template<typename Iter>
struct cxx20_iterator_category_check_bidirectional<Iter, true> {
  using type = bidirectional_iterator_tag;
};

template<typename Iter, bool = LegacyRandomAccessIterator<Iter>::value /* false */>
struct cxx20_iterator_category_check_random_access
    : cxx20_iterator_category_check_bidirectional<Iter> {};

template<typename Iter>
struct cxx20_iterator_category_check_random_access<Iter, true> {
  using type = random_access_iterator_tag;
};

template<typename Iter, bool = has_typename_iterator_category<Iter>::value /* false */>
struct cxx20_iterator_category : cxx20_iterator_category_check_random_access<Iter> {};

template<typename Iter>
struct cxx20_iterator_category<Iter, true> {
  using type = typename Iter::iterator_category;
};

template<typename Iter, bool = has_typename_reference<Iter>::value /* false */>
struct cxx20_iterator_traits_reference {
  using type = iter_reference_t<Iter>;
};
template<typename Iter>
struct cxx20_iterator_traits_reference<Iter, true> {
  using type = typename Iter::reference;
};

template<typename Iter, typename = void>
struct cxx20_iterator_traits_pointer_sfinae {
  using type = void;
};
template<typename Iter>
struct cxx20_iterator_traits_pointer_sfinae<Iter, void_t<decltype( std::declval<Iter&>().operator->() )>> {
  using type = decltype( std::declval<Iter&>().operator->() );
};
template<typename Iter, bool = has_typename_pointer<Iter>::value /* false */>
struct cxx20_iterator_traits_pointer : cxx20_iterator_traits_pointer_sfinae<Iter> {};
template<typename Iter>
struct cxx20_iterator_traits_pointer<Iter, true> {
  using type = typename Iter::pointer;
};

template<
    typename Iter,
    bool = has_typename_difference_type<incrementable_traits<Iter>>::value /* false */
>
struct cxx20_iterator_traits_sfinae_legacy_iterator_difference_type {
  using type = void;
};
template<typename Iter>
struct cxx20_iterator_traits_sfinae_legacy_iterator_difference_type<Iter, true> {
  using type = typename incrementable_traits<Iter>::difference_type;
};

template<
    typename Iter,
    bool = LegacyIterator<Iter>::value /* false */
>
struct cxx20_iterator_traits_sfinae_legacy_iterator {};

template<typename Iter>
struct cxx20_iterator_traits_sfinae_legacy_iterator<Iter, true> {
  using difference_type = typename cxx20_iterator_traits_sfinae_legacy_iterator_difference_type<Iter>::difference_type;
  using value_type = void;
  using pointer = void;
  using reference = void;
  using iterator_category = output_iterator_tag;
};

template<typename Iter, bool = LegacyInputIterator<Iter>::value /* false */ >
struct cxx20_iterator_traits_sfinae_legacy_input_iterator : cxx20_iterator_traits_sfinae_legacy_iterator<Iter> {};

template<typename Iter>
struct cxx20_iterator_traits_sfinae_legacy_input_iterator<Iter, true> {
  using difference_type = typename incrementable_traits<Iter>::difference_type;
  using value_type = typename indirectly_readable_traits<Iter>::value_type;
  using pointer = typename cxx20_iterator_traits_pointer<Iter>::type;
  using reference = typename cxx20_iterator_traits_reference<Iter>::type;
  using iterator_category = typename cxx20_iterator_category<Iter>::type;;
};

template<
  typename Iter,
  bool = has_typename_difference_type<Iter>::value,
  bool = has_typename_value_type<Iter>::value,
  bool = has_typename_pointer<Iter>::value,
  bool = has_typename_reference<Iter>::value,
  bool = has_typename_iterator_category<Iter>::value
>
struct cxx20_iterator_traits_sfinae : cxx20_iterator_traits_sfinae_legacy_input_iterator<Iter> {};

template<typename Iter>
struct cxx20_iterator_traits_sfinae<Iter, true, true, true, true, true> {
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = typename Iter::pointer;
  using reference = typename Iter::reference;
  using iterator_category = typename Iter::iterator_category;
};

template<typename Iter>
struct cxx20_iterator_traits_sfinae<Iter, true, true, false, true, true> {
  using difference_type = typename Iter::difference_type;
  using value_type = typename Iter::value_type;
  using pointer = void;
  using reference = typename Iter::reference;
  using iterator_category = typename Iter::iterator_category;
};

template<typename T, bool = std::is_object<T>::value /* false */>
struct cxx20_iterator_traits_object_pointer {};
template<typename T>
struct cxx20_iterator_traits_object_pointer<T, true> {
  using difference_type = std::ptrdiff_t;
  using value_type = std::remove_cv_t<T>;
  using pointer = T*;
  using reference = T&;
  using iterator_category = random_access_iterator_tag;
  using iterator_concept = contiguous_iterator_tag;
};

} // namespace detail

template<typename Iter>
struct cxx20_iterator_traits : detail::cxx20_iterator_traits_sfinae<Iter> {};

template<typename T>
struct cxx20_iterator_traits<T*> : detail::cxx20_iterator_traits_object_pointer<T> {};

} // namespace lsd

#endif // LSD_ITERATOR_ITERATOR_TRAITS_CXX20_ITERATOR_TRAITS_HPP_
