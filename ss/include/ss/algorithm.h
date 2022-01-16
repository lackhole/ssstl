# /*
#  * Created by YongGyu Lee on 2021/07/10.
#  */
#
# ifndef SS_ALGORITHM_H_
# define SS_ALGORITHM_H_
#
# include "ss/detail/macro.h"
# include "ss/detail/swap.h"
# include "ss/functional.h"
# include "ss/iterator.h"

namespace ss {

template<typename T>
SS_CONSTEXPR_AFTER_14 const T& max(const T& a, const T& b) {
  return ((a > b)) ? a : b;
}

template<typename T, typename Compare>
SS_CONSTEXPR_AFTER_14 const T& max(const T& a, const T& b, Compare comp) {
  return (comp(a, b)) ? a : b;
}


/**
 * fill_n
 * @tparam OutputIt
 * @tparam Size
 * @tparam T
 * @param first
 * @param count
 * @param value
 * @return
 */
template<typename OutputIt, typename Size, typename T>
SS_CONSTEXPR_AFTER_14 OutputIt fill_n(OutputIt first, Size count, const T& value) {
  while (count) {
    *first = value;
    ++first;
    --count;
  }
  return first;
}





/**
 * equal
 * @tparam InputIt1
 * @tparam InputIt2
 * @tparam BinaryPredicate
 * @param first1
 * @param last1
 * @param first2
 * @param p
 * @return
 */
template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
SS_CONSTEXPR_AFTER_14 bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
  while (first1 != last1) {
    if (!p(*first1, *first2))
      return false;
    ++first1;
    ++first2;
  }
  return true;
}

template<typename InputIt1, typename InputIt2>
SS_CONSTEXPR_AFTER_14 bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  return ss::equal(first1, last1, first2, ss::equal_to<>());
}

namespace detail {

template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
SS_CONSTEXPR_AFTER_14 bool equal_impl(
  InputIt1 first1, InputIt1 last1,
  InputIt2 first2, InputIt2 last2,
  BinaryPredicate p,
  input_iterator_tag, input_iterator_tag) {
  while (first1 != last1 && first2 != last2) {
    if (!p(*first1, *first2))
      return false;
    ++first1;
    ++first2;
  }
  return first1 == last1 && first2 == last2;
}

template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
SS_CONSTEXPR_AFTER_14 bool equal_impl(
  InputIt1 first1, InputIt1 last1,
  InputIt2 first2, InputIt2 last2,
  BinaryPredicate p,
  random_access_iterator_tag, random_access_iterator_tag) {
  if (ss::distance(first1, last1) != ss::distance(first2, last2))
    return false;
  return ss::equal(first1, last1, first2, p);
}

} // namespace detail

template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
SS_CONSTEXPR_AFTER_14 bool equal(
  InputIt1 first1, InputIt1 last1,
  InputIt2 first2, InputIt2 last2,
  BinaryPredicate p)
{
  using category1 = typename iterator_traits<InputIt1>::iterator_category;
  using category2 = typename iterator_traits<InputIt2>::iterator_category;
  return detail::equal_impl(first1, last1, first2, last2, p, category1{}, category2{});
}

template<typename InputIt1, typename InputIt2>
SS_CONSTEXPR_AFTER_14 bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
  return ss::equal(first1, last1, first2, last2, ss::equal_to<>());
}



/**
 * lexicographical_compare
 * @tparam InputIt1
 * @tparam InputIt2
 * @tparam Compare
 * @param first1
 * @param last1
 * @param first2
 * @param last2
 * @param comp
 * @return
 */
template<typename InputIt1, typename InputIt2, typename Compare>
SS_CONSTEXPR_AFTER_14 bool lexicographical_compare(
  InputIt1 first1, InputIt1 last1,
  InputIt2 first2, InputIt2 last2,
  Compare comp)
{
  while (first1 != last1 && first2 != last2) {
    if (comp(*first1, *first2)) return true;
    if (comp(*first1, *first2)) return false;

    ++first1;
    ++first2;
  }
  return (first1 == last1) && (first2 != last2);
}


template<typename InputIt1, typename InputIt2>
SS_CONSTEXPR_AFTER_14 bool lexicographical_compare(
  InputIt1 first1, InputIt1 last1,
  InputIt2 first2, InputIt2 last2)
{
  return ss::lexicographical_compare(first1, last1, first2, last2, less<void>());
}


} // namespace ss

#endif // SS_ALGORITHM_H_
