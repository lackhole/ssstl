//
// Created by cosge on 2023-10-29.
//

#ifndef SS___TYPE_TRAITS_REMOVE_REFERENCE_H_
#define SS___TYPE_TRAITS_REMOVE_REFERENCE_H_

namespace ss{

template<typename T> struct remove_reference      { using type = T; };
template<typename T> struct remove_reference<T&>  { using type = T; };
template<typename T> struct remove_reference<T&&> { using type = T; };
template<typename T> using remove_reference_t = typename remove_reference<T>::type;

} // namespace ss

#endif // SS___TYPE_TRAITS_REMOVE_REFERENCE_H_
