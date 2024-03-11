# /*
#  * Created by YongGyu Lee on 2020/12/08.
#  */
#
# ifndef LSD_TYPE_TRAITS_IS_SPECIALIZATION_HPP
# define LSD_TYPE_TRAITS_IS_SPECIALIZATION_HPP
#
# include <type_traits>

namespace lsd {

template<typename Test, template<typename...> class Ref>
struct is_specialization : std::false_type {};

template<template<typename...> class Ref, typename... Args>
struct is_specialization<Ref<Args...>, Ref> : std::true_type {};

} // namespace lsd

# endif // LSD_TYPE_TRAITS_IS_SPECIALIZATION_HPP
