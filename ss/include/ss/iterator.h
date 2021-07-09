# /*
#  * Created by YongGyu Lee on 2021/07/10.
#  */
#
# ifndef SS_ITERATOR_H_
# define SS_ITERATOR_H_
#
# include "ss/type_traits.h"

namespace ss {

struct input_iterator_tag {};
struct output_iterator_tag {};
struct forward_iterator_tag : public input_iterator_tag {};
struct bidirectional_iterator_tag : public forward_iterator_tag {};
struct random_access_iterator_tag : public bidirectional_iterator_tag {};
struct contiguous_iterator_tag : public random_access_iterator_tag {};

template<typename Iter>
struct iterator_traits;

template<typename T>
struct iterator_traits<T*> {
  static_assert(is_object<T>::value, "Type must be pointer to object");

  using difference_type = std::ptrdiff_t;
  using value_type = remove_cv_t<T>;
  using pointer = T*;
  using reference = T&;
  using iterator_category = random_access_iterator_tag;
  using iterator_concept = contiguous_iterator_tag
};


} // namespace ss

# endif // SS_ITERATOR_H_
