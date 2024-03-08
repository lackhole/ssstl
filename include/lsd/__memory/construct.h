//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___MEMORY_CONSTRUCT_AT_H_
#define LSD___MEMORY_CONSTRUCT_AT_H_

#include "lsd/type_traits.h"
#include "lsd/utility.h"

namespace lsd {

namespace detail {

template<typename T, typename ...Args>
auto in_place_new_test(int) -> decltype(::new(::lsd::declval<void *>()) T(lsd::declval<Args>()...));

template<typename...>
auto in_place_new_test(...) -> unused;

template<typename T, typename ...Args>
struct in_place_new_allocatable : is_not_same<unused, decltype(in_place_new_test<T, Args...>(0))> {};

} // namespace detail

/**
 * construct_at
 * @param p
 * @param args
 * @return
 */
template<typename T, typename ...Args>
constexpr enable_if_t<detail::in_place_new_allocatable<T, Args...>::value, T *>
construct_at(T *p, Args&& ... args) {
  return ::new(const_cast<void *>(static_cast<const volatile void *>(p))) T(lsd::forward<Args>(args)...);
}

} // namespace lsd

#endif // LSD___MEMORY_CONSTRUCT_AT_H_
