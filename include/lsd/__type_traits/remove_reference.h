//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___TYPE_TRAITS_REMOVE_REFERENCE_H_
#define LSD___TYPE_TRAITS_REMOVE_REFERENCE_H_

namespace lsd{

template<typename T> struct remove_reference      { using type = T; };
template<typename T> struct remove_reference<T&>  { using type = T; };
template<typename T> struct remove_reference<T&&> { using type = T; };
template<typename T> using remove_reference_t = typename remove_reference<T>::type;

} // namespace lsd

#endif // LSD___TYPE_TRAITS_REMOVE_REFERENCE_H_
