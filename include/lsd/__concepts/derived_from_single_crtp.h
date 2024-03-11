//
// Created by yonggyulee on 2024/01/01.
//

#ifndef LSD_TYPE_TRAITS_IS_DERIVED_FROM_SINGLE_CRTP_HPP
#define LSD_TYPE_TRAITS_IS_DERIVED_FROM_SINGLE_CRTP_HPP

#include "lsd/__concepts/same_as.h"
#include "lsd/__type_traits/is_invocable.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace detail {

template<typename T, typename = void>

struct has_typename_vccc_derived : std::false_type {};
template<typename T>
struct has_typename_vccc_derived<T, void_t<typename T::_$vccc_derived>> : std::true_type {};

template<template<typename> class Base>
struct derived_from_single_crtp_tester {
  template<typename T, typename U>
  auto operator()(const T&, const Base<U>&) const -> same_as<T, Base<U>>;
};

template<
    typename Derived,
    template<typename> class Base,
    bool = is_referencable<Derived>::value /* true */
>
struct derived_from_single_crtp_impl
#if defined(_MSC_VER) && _MSC_VER < 1930 // Ambigious casting is allowed until Visutal Studio 2022
    : has_typename_vccc_derived<Derived> {};
#else
    : is_invocable_r<
          std::false_type, derived_from_single_crtp_tester<Base>, Derived&, Derived&>{};
#endif

template<typename Derived, template<typename> class Base>
struct derived_from_single_crtp_impl<Derived, Base, false> : std::false_type {};

} // namespace detail

template<typename Derived, template<typename> class Base>
struct derived_from_single_crtp : detail::derived_from_single_crtp_impl<Derived, Base> {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_DERIVED_FROM_SINGLE_CRTP_HPP
