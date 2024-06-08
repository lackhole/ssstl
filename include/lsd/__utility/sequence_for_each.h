//
// Created by YongGyu Lee on 2024. 5. 17.
//

#ifndef LSD_UTILITY_SEQUENCE_FOR_EACH_H_
#define LSD_UTILITY_SEQUENCE_FOR_EACH_H_

#include <cstddef>
#include <type_traits>
#include <utility>

#include "lsd/__functional/identity.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/is_invocable.h"

namespace lsd {
namespace detail {

template<typename Seq, typename F>
struct sequence_for_each_invocable : std::false_type {};

template<typename T, T... v, typename F>
struct sequence_for_each_invocable<std::integer_sequence<T, v...>, F>
    : conjunction<
          is_invocable<F, std::integral_constant<T, v>>...
      > {};

} // namespace detail


// performs f(std::integral_constant<T, i>{}) for i in v...
template<typename T, T... v, typename F, std::enable_if_t<(sizeof...(v) > 1), int> = 0>
constexpr std::enable_if_t<detail::sequence_for_each_invocable<std::integer_sequence<T, v...>, F>::value>
sequence_for_each(std::integer_sequence<T, v...>, F&& f) {
  int dummy[] = {
      (lsd::invoke(f, std::integral_constant<T, v>{}), 0)...
  };
  (void)dummy;
}

// performs f(std::integral_constant<T, i>{}) for i in [0, N)
template<typename T, T N, typename F>
constexpr std::enable_if_t<detail::sequence_for_each_invocable<std::make_integer_sequence<T, N>, F>::value>
sequence_for_each(F&& f) {
  return lsd::sequence_for_each(std::make_integer_sequence<T, N>{}, std::forward<F>(f));
}

// performs f(std::integral_constant<std::size_t, i>{}) for i in [0, N)
template<std::size_t N, typename F>
constexpr std::enable_if_t<detail::sequence_for_each_invocable<std::make_index_sequence<N>, F>::value>
sequence_for_each(F&& f) {
  return lsd::sequence_for_each(std::make_index_sequence<N>{}, std::forward<F>(f));
}

} // namespace lsd

#endif // LSD_UTILITY_SEQUENCE_FOR_EACH_H_
