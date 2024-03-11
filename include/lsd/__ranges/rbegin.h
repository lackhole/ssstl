//
// Created by yonggyulee on 2024/02/08.
//

#ifndef LSD_RANGES_RBEGIN_HPP_
#define LSD_RANGES_RBEGIN_HPP_

#include <iterator>
#include <type_traits>

#include "lsd/__core/decay_copy.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/input_or_output_iterator.h"
#include "lsd/__iterator/forward_iterator.h"
#include "lsd/__ranges/common_range.h"
#include "lsd/__ranges/detail/not_incomplete_array.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__ranges/end.h"
#include "lsd/__type_traits/bool_constant.h"
#include "lsd/__type_traits/detail/tag.h"
#include "lsd/__type_traits/disjunction.h"
#include "lsd/__type_traits/is_class_or_enum.h"
#include "lsd/__type_traits/remove_cvref.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace ranges {
namespace detail {

using lsd::detail::tag_1;
using lsd::detail::tag_2;
using lsd::detail::tag_3;

struct rbegin_niebloid {
 private:

  template<typename T, typename = void>
  struct rbegin_member_check : std::false_type {};
  template<typename T>
  struct rbegin_member_check<T, void_t<decltype(vccc_decay_copy( std::declval<T>().rbegin() )) >>
            : input_or_output_iterator<decltype(vccc_decay_copy( std::declval<T>().rbegin() )) > {};

  template<typename T, bool = is_class_or_enum<remove_cvref_t<T>>::value, typename = void>
  struct rbegin_global_check : std::false_type {};
  template<typename T>
  struct rbegin_global_check<T, true, void_t<decltype(vccc_decay_copy( rbegin(std::declval<T>()) ))>>
            : input_or_output_iterator<decltype(vccc_decay_copy( rbegin(std::declval<T>()) ))> {};

  template<typename T, bool = common_range<T>::value>
  struct common_bidi_check : std::false_type {};
  template<typename T>
  struct common_bidi_check<T, true> : bidirectional_iterator<decltype( ranges::begin(std::declval<T>()) )> {};

  template<typename T>
  using rbegin_tag = conditional_tag<rbegin_member_check<T>, rbegin_global_check<T>, common_bidi_check<T>>;

  template<typename T>
  constexpr auto run(T&& t, tag_1) const {
    return vccc_decay_copy(t.rbegin());
  }

  template<typename T>
  constexpr auto run(T&& t, tag_2) const {
    return vccc_decay_copy(rbegin(t));
  }

  template<typename T>
  constexpr auto run(T&& t, tag_3) const {
    return std::make_reverse_iterator(ranges::end(t));
  }

 public:
  template<typename T, std::enable_if_t<conjunction<
      lsd::detail::not_incomplete_array<T>,
      disjunction<
        std::is_lvalue_reference<std::remove_cv_t<T>>,
        enable_borrowed_range<std::remove_cv_t<T>>
      >,
      bool_constant<(rbegin_tag<T>::value > 0)>
  >::value, int> = 0>
  constexpr auto operator()(T&& t) const {
    return run(std::forward<T>(t), rbegin_tag<T>{});
  }
};

} // namespace detail

inline namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::rbegin_niebloid rbegin{};

} // inline namespace niebloid

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_RBEGIN_HPP_
