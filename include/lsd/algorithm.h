# /*
#  * Created by YongGyu Lee on 2021/07/10.
#  */
#
# ifndef LSD_ALGORITHM_H_
# define LSD_ALGORITHM_H_
#
# include "lsd/__core/macro.h"
# include "lsd/__algorithm/swap.h"
# include "lsd/functional.h"
# include "lsd/initializer_list.h"
# include "lsd/iterator.h"
# include "lsd/utility.h"

namespace lsd {

template<typename ForwardIt, typename Compare>
LSD_CONSTEXPR_AFTER_14 ForwardIt min_element(ForwardIt first, ForwardIt last, Compare comp) {
  if (first == last)
    return last;

  ForwardIt min_ = first;
  ++first;

  while(first != last) {
    if (comp(*first, *min_))
      min_ = first;
    ++first;
  }
  return min_;
}

template<typename ForwardIt>
LSD_CONSTEXPR_AFTER_14 ForwardIt min_element(ForwardIt first, ForwardIt last) {
  return min_element(first, last, less<>{});
}

template<typename ForwardIt, typename Compare>
LSD_CONSTEXPR_AFTER_14 ForwardIt max_element(ForwardIt first, ForwardIt last, Compare comp) {
  if (first == last)
    return last;

  ForwardIt max_ = first;
  ++first;

  while(first != last) {
    if (comp(*max_, *first))
      max_ = first;
    ++first;
  }
  return max_;
}

template<typename ForwardIt>
LSD_CONSTEXPR_AFTER_14 ForwardIt max_element(ForwardIt first, ForwardIt last) {
  return max_element(first, last, less<>{});
}

template<typename ForwardIt, typename Compare>
LSD_CONSTEXPR_AFTER_14 pair<ForwardIt, ForwardIt>
minmax_element(ForwardIt first, ForwardIt last, Compare comp) {
  pair<ForwardIt, ForwardIt> result(first, first);
  
  // Input is empty
  if (first == last)
    return result;
  
  while (++first != last) {
    ForwardIt next = first;
    if (++first == last) { // compare one (next)
      if (comp(*next, *result.first)) {
        result.first = next;
      } else if (!comp(*next, *result.second)) {
        result.second = next;
      }
      break;
    } else { // compare ahead pair (next, first)
      if (comp(*next, *first)) { // next < first
        if (comp(*next, *result.first)) {
          result.first = next;
        }
        if (!comp(*first, *result.second)) {
          result.second = first;
        }
      } else { // first <= next
        if (comp(*first, *result.first)) {
          result.first = first;
        }
        if (!comp(*next, *result.second)) {
          result.second = next;
        }
      }
    }
  }
  
  return result;
}

template<typename ForwardIt>
LSD_CONSTEXPR_AFTER_14 pair<ForwardIt, ForwardIt>
minmax_element(ForwardIt first, ForwardIt last) {
  return lsd::minmax_element(first, last, less<>{});
}


template<typename T>
constexpr const T& min(const T& a, const T& b) {
  return (a < b) ? a : b;
}

template<typename T, typename Compare>
constexpr const T& min(const T& a, const T& b, Compare comp) {
  return (comp(a < b)) ? a : b;
}

template<typename T>
constexpr T min(initializer_list<T> ilist) {
  return *lsd::min_element(ilist.begin(), ilist.end(), less<T>{});
}

template<typename T, typename Compare>
constexpr T min(initializer_list<T> ilist, Compare comp) {
  return *lsd::min_element(ilist.begin(), ilist.end(), comp);
}

template<typename T, typename Compare>
constexpr const T& max(const T& a, const T& b, Compare comp) {
  return (comp(a, b)) ? b : a;
}

template<typename T>
constexpr const T& max(const T& a, const T& b) {
  return lsd::max(a, b, less<T>{});
}

template<typename T>
constexpr T max(initializer_list<T> ilist) {
  return *lsd::max_element(ilist.begin(), ilist.end());
}

template<typename T, typename Compare>
constexpr T max(initializer_list<T> ilist, Compare comp) {
  return *lsd::max_element(ilist.begin(), ilist.end(), comp);
}

template<typename T, typename Compare>
constexpr pair<const T&, const T&> minmax(const T& a, const T& b, Compare comp) {
  return comp(a, b) ? pair<const T&, const T&>(a, b) : pair<const T&, const T&>(b, a);
}

template<typename T>
constexpr pair<const T&, const T&> minmax(const T& a, const T& b) {
  return lsd::minmax(a, b, less<T>{});
}

template<typename T>
LSD_CONSTEXPR_AFTER_14 pair<T, T> minmax(initializer_list<T> ilist) {
  auto res = lsd::minmax_element(ilist.begin(), ilist.end());
  return pair<T, T>(*res.first, *res.second);
}

template<typename T, typename Compare>
LSD_CONSTEXPR_AFTER_14 pair<T, T> minmax(initializer_list<T> ilist, Compare comp) {
  auto res = lsd::minmax_element(ilist.begin(), ilist.end(), comp);
  return pair<T, T>(*res.first, *res.second);
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
LSD_CONSTEXPR_AFTER_14 OutputIt fill_n(OutputIt first, Size count, const T& value) {
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
LSD_CONSTEXPR_AFTER_14 bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p) {
  while (first1 != last1) {
    if (!p(*first1, *first2))
      return false;
    ++first1;
    ++first2;
  }
  return true;
}

template<typename InputIt1, typename InputIt2>
LSD_CONSTEXPR_AFTER_14 bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
  return lsd::equal(first1, last1, first2, lsd::equal_to<>());
}

namespace detail {

template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
LSD_CONSTEXPR_AFTER_14 bool equal_impl(
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
LSD_CONSTEXPR_AFTER_14 bool equal_impl(
  InputIt1 first1, InputIt1 last1,
  InputIt2 first2, InputIt2 last2,
  BinaryPredicate p,
  random_access_iterator_tag, random_access_iterator_tag) {
  if (lsd::distance(first1, last1) != lsd::distance(first2, last2))
    return false;
  return lsd::equal(first1, last1, first2, p);
}

} // namespace detail

template<typename InputIt1, typename InputIt2, typename BinaryPredicate>
LSD_CONSTEXPR_AFTER_14 bool equal(
  InputIt1 first1, InputIt1 last1,
  InputIt2 first2, InputIt2 last2,
  BinaryPredicate p)
{
  using category1 = typename iterator_traits<InputIt1>::iterator_category;
  using category2 = typename iterator_traits<InputIt2>::iterator_category;
  return detail::equal_impl(first1, last1, first2, last2, p, category1{}, category2{});
}

template<typename InputIt1, typename InputIt2>
LSD_CONSTEXPR_AFTER_14 bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2) {
  return lsd::equal(first1, last1, first2, last2, lsd::equal_to<>());
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
LSD_CONSTEXPR_AFTER_14 bool lexicographical_compare(
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
LSD_CONSTEXPR_AFTER_14 bool lexicographical_compare(
  InputIt1 first1, InputIt1 last1,
  InputIt2 first2, InputIt2 last2)
{
  return lsd::lexicographical_compare(first1, last1, first2, last2, less<void>());
}


} // namespace lsd

#endif // LSD_ALGORITHM_H_
