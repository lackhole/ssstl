//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___MEMORY_POINTER_TRAITS_H_
#define LSD___MEMORY_POINTER_TRAITS_H_

#include <utility>

namespace lsd {

namespace detail {

template<typename T, typename = void>
struct has_const_pointer : false_type {};
template<typename T>
struct has_const_pointer<T, void_t<typename T::const_pointer>> : true_type {};

template<typename T, typename = void>
struct has_void_pointer : false_type {};
template<typename T>
struct has_void_pointer<T, void_t<typename T::void_pointer>> : true_type {};

template<typename T, typename = void>
struct has_const_void_pointer : false_type {};
template<typename T>
struct has_const_void_pointer<T, void_t<typename T::const_void_pointer>> : true_type {};

template<typename T, typename = void>
struct has_size_type : false_type {};
template<typename T>
struct has_size_type<T, void_t<typename T::size_type>> : true_type {};

template<typename T, typename = void>
struct has_propagate_on_container_copy_assignment : false_type {};
template<typename T>
struct has_propagate_on_container_copy_assignment<T, void_t<typename T::propagate_on_container_copy_assignment>> : true_type {};

template<typename T, typename = void>
struct has_propagate_on_container_move_assignment : false_type {};
template<typename T>
struct has_propagate_on_container_move_assignment<T, void_t<typename T::propagate_on_container_move_assignment>> : true_type {};

template<typename T, typename = void>
struct has_propagate_on_container_swap : false_type {};
template<typename T>
struct has_propagate_on_container_swap<T, void_t<typename T::propagate_on_container_swap>> : true_type {};

template<typename T, typename = void>
struct has_is_always_equal : false_type {};
template<typename T>
struct has_is_always_equal<T, void_t<typename T::is_always_equal>> : true_type {};

template<typename T, typename U, typename = void>
struct has_rebind : false_type {};
template<typename T, typename U>
struct has_rebind<T, U, void_t<typename T::template rebind<U>>> : true_type {};

//template<typename T, typename = void> struct has_element_type : false_type {};
//template<typename T> struct has_element_type<T, void_t<typename T::element_type>> : true_type {};

template<typename T>
struct template_type;

template<template<typename, typename...> class Template, typename T, typename ...Args>
struct template_type<Template<T, Args...>> {
  using first_type = T;
  template<typename U>
  using rebind_first = Template<U, Args...>;
};

template<typename Ptr, typename = void>
struct pointer_traits_element_type {
  using type = typename template_type<Ptr>::first_type;
};

template<typename Ptr>
struct pointer_traits_element_type<Ptr, void_t<typename Ptr::element_type>> {
using type = typename Ptr::element_type;
};

template<typename Ptr, bool v = has_difference_type<Ptr>::value>
struct pointer_traits_difference_type {
  using type = typename Ptr::difference_type;
};
template<typename Ptr>
struct pointer_traits_difference_type<Ptr, false> {
  using type = ptrdiff_t;
};

template<typename Ptr, typename U, bool v = /* true */ has_rebind<Ptr, U>::value>
struct pointer_traits_rebind {
  using type = typename Ptr::template rebind<U>;
};

template<typename Ptr, typename U>
struct pointer_traits_rebind<Ptr, U, false> {
  using type = typename template_type<Ptr>::template rebind_first<U>;
};

} // namespace detail

/**
 * pointer_traits
 * @tparam Ptr
 */
template<typename Ptr>
struct pointer_traits {
  using pointer = Ptr;
  using element_type = typename detail::pointer_traits_element_type<Ptr>::type;
  using difference_type = typename detail::pointer_traits_difference_type<Ptr>::type;

  template<typename U>
  using rebind = typename detail::pointer_traits_rebind<Ptr, U>::type;

  static pointer pointer_to(conditional_t<is_void<element_type>::value, void, element_type>& r) {
    return Ptr::pointer_to(r);
  }
};

template<typename T>
struct pointer_traits<T*> {
  using pointer = T*;
  using element_type = T;
  using difference_type = ptrdiff_t;

  template<typename U> using rebind = U *;

  static constexpr pointer pointer_to(conditional_t<is_void<element_type>::value, void, element_type>& r) noexcept {
    return lsd::addressof(r);
  }
};

} // namespace lsd

#endif // LSD___MEMORY_POINTER_TRAITS_H_
