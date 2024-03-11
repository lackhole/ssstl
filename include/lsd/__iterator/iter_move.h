//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_ITERATOR_ITER_MOVE_HPP_
#define LSD_ITERATOR_ITER_MOVE_HPP_

#include <type_traits>
#include <utility>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__concepts/dereferenceable.h"
#include "lsd/__type_traits/detail/return_category.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/disjunction.h"
#include "lsd/__type_traits/is_class_or_enum.h"

namespace lsd {
namespace ranges {
namespace detail {

using lsd::detail::return_category;

template<
    typename T,
    bool = is_class_or_enum<std::decay_t<T>>::value,
    typename = void
>
struct iter_move_check_adaptors : std::false_type {
  using category = return_category<0>;
};
template<typename T>
struct iter_move_check_adaptors<T, true, void_t<decltype(iter_move(std::declval<T>()))>> : std::true_type {
  using category = return_category<1, decltype(iter_move(std::declval<T>()))>;
};

template<typename T, bool = conjunction<std::is_lvalue_reference<T>, dereferenceable<T>>::value, typename = void>
struct iter_move_lvalue_deref_check : std::false_type {
  using category = return_category<0>;
};
template<typename T>
struct iter_move_lvalue_deref_check<T, true, void_t<decltype(std::move(*std::declval<T>()))>> : std::true_type {
  using category = return_category<2, decltype(std::move(*std::declval<T>()))>;
};

template<typename T, bool = conjunction<std::is_rvalue_reference<T>, dereferenceable<T>>::value>
struct iter_move_rvalue_deref_check : std::false_type {
  using category = return_category<0>;
};
template<typename T>
struct iter_move_rvalue_deref_check<T, true> : std::true_type {
  using category = return_category<3, decltype(std::move(*std::declval<T>()))>;
};

template<typename T>
struct iter_move_category
    : std::conditional_t<
        iter_move_check_adaptors<T>::value, typename iter_move_check_adaptors<T>::category,
      std::conditional_t<
        iter_move_lvalue_deref_check<T>::value, typename iter_move_lvalue_deref_check<T>::category,
      std::conditional_t<
        iter_move_rvalue_deref_check<T>::value, typename iter_move_rvalue_deref_check<T>::category,
        return_category<0>
      >>> {};

template<typename T, typename R>
constexpr R iter_move_impl(T&& t, return_category<1, R>) {
  return iter_move(std::forward<T>(t));
}

template<typename T, typename R>
constexpr R iter_move_impl(T&& t, return_category<2, R>) {
  return std::move(*t);
}

template<typename T, typename R>
constexpr R iter_move_impl(T&& t, return_category<3, R>) {
  return std::move(*t);
}

struct iter_move_niebloid {
  template<typename T>
  constexpr typename iter_move_category<T&&>::return_type
  operator()(T&& t) const {
    return iter_move_impl(std::forward<T>(t), detail::iter_move_category<T&&>{});
  }
};

} // namespace detail

inline namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::iter_move_niebloid iter_move{};

} // inline namespace niebloid

} // namespace ranges
} // namespace lsd

#endif // LSD_ITERATOR_ITER_MOVE_HPP_
