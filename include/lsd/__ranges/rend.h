//
// Created by yonggyulee on 2024/02/08.
//

#ifndef LSD_RANGES_REND_HPP_
#define LSD_RANGES_REND_HPP_

#include <iterator>
#include <type_traits>

#include "lsd/__core/decay_copy.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/bidirectional_iterator.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__ranges/common_range.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__ranges/detail/not_incomplete_array.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/rbegin.h"
#include "lsd/__type_traits/disjunction.h"
#include "lsd/__type_traits/is_invocable.h"
#include "lsd/__type_traits/remove_cvref.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace ranges {
namespace detail {

using lsd::detail::tag_1;
using lsd::detail::tag_2;
using lsd::detail::tag_3;

struct rend_niebloid {
 private:

  template<typename T, bool = is_invocable<rbegin_niebloid, T&&>::value, typename = void>
  struct rend_member_check : std::false_type {};
  template<typename T>
  struct rend_member_check<T,
        true, void_t<decltype(vccc_decay_copy( std::declval<T>().rend() ))>>
      : sentinel_for<decltype(vccc_decay_copy( std::declval<T>().rend() )),
                     decltype( ranges::rbegin(std::declval<T>()) )> {};

  template<typename T, bool = conjunction<
      is_invocable<rbegin_niebloid, T&&>,
      is_class_or_enum<remove_cvref_t<T>>>::value, typename = void>
  struct rend_global_check : std::false_type {};
  template<typename T>
  struct rend_global_check<T,
        true, void_t<decltype(vccc_decay_copy( rend(std::declval<T>()) ))>>
      : sentinel_for<decltype(vccc_decay_copy( rend(std::declval<T>()) )),
                     decltype( ranges::rbegin(std::declval<T>()) )> {};

  template<typename T, bool = common_range<T>::value>
  struct common_bidi_check : std::false_type {};
  template<typename T>
  struct common_bidi_check<T, true> : bidirectional_iterator<decltype( ranges::begin(std::declval<T>()) )> {};

  template<typename T>
  using rend_tag = conditional_tag<rend_member_check<T>, rend_global_check<T>, common_bidi_check<T>>;

  template<typename T>
  constexpr auto run(T&& t, tag_1) const {
    return vccc_decay_copy(t.rend());
  }

  template<typename T>
  constexpr auto run(T&& t, tag_2) const {
    return vccc_decay_copy(rend(t));
  }

  template<typename T>
  constexpr auto run(T&& t, tag_3) const {
    return std::make_reverse_iterator(ranges::begin(t));
  }

 public:
  template<typename T, std::enable_if_t<conjunction<
      lsd::detail::not_incomplete_array<T>,
      disjunction<
        std::is_lvalue_reference<std::remove_cv_t<T>>,
        enable_borrowed_range<std::remove_cv_t<T>>
      >,
      bool_constant<(rend_tag<T>::value > 0)>
  >::value, int> = 0>
  constexpr auto operator()(T&& t) const {
    return run(std::forward<T>(t), rend_tag<T>{});
  }
};

} // namespace detail

inline namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::rend_niebloid rend{};

} // inline namespace niebloid

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_REND_HPP_
