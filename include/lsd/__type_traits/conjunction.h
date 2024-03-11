//
// Created by cosge on 2023-10-14.
//

#ifndef LSD_TYPE_TRAITS_CONJUNCTION_HPP
#define LSD_TYPE_TRAITS_CONJUNCTION_HPP

#include <type_traits>

namespace lsd {

template<typename ...B>
struct conjunction;

template<>
struct conjunction<> : std::true_type {};

template<typename B1>
struct conjunction<B1> : B1 {};

template<typename B1, typename ...BN>
struct conjunction<B1, BN...> : std::conditional_t<bool(B1::value), conjunction<BN...>, B1> {};

} // namespace lsd

#endif // LSD_TYPE_TRAITS_CONJUNCTION_HPP
