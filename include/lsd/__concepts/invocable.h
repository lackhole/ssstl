//
// Created by cosge on 2023-12-27.
//

#ifndef LSD_CONCEPTS_INVOCABLE_H_
#define LSD_CONCEPTS_INVOCABLE_H_

#include <cstddef>
#include <type_traits>

#include "lsd/__functional/invoke.h"
#include "lsd/__type_traits/void_t.h"
#include "lsd/__utility/type_sequence.h"

namespace lsd {
namespace detail {

template<typename F, typename Seq, typename = void>
struct explicit_invocable : std::false_type {};

template<typename F, typename... Args>
struct explicit_invocable<
      F, type_sequence<Args...>,
      void_t<decltype(
          lsd::invoke(
              std::declval<decltype( std::forward<F>   (std::declval<F&&>   ()) )>(),
              std::declval<decltype( std::forward<Args>(std::declval<Args&&>()) )>()...
          )
      )>
    > : std::true_type {};

template<typename F, typename Seq>
struct invocable_impl : std::false_type {};

template<typename F, typename... Args>
struct invocable_impl<F, type_sequence<Args...>> : explicit_invocable<F, type_sequence<Args...>> {};

} // namespace detail

template<typename F, typename... Args>
struct invocable : detail::invocable_impl<F, type_sequence<Args...>> {};

template<typename F, typename... Args >
struct regular_invocable : invocable<F, Args...> {};

} // namespace lsd

#endif // LSD_CONCEPTS_INVOCABLE_H_
