#ifndef LSD_TYPE_TRAITS_IS_CHARACTER_H_
#define LSD_TYPE_TRAITS_IS_CHARACTER_H_

#include <type_traits>

namespace lsd {

template<typename T>
struct is_character : std::false_type {};

template<> struct is_character<char> : std::true_type {};
template<> struct is_character<signed char> : std::true_type {};
template<> struct is_character<unsigned char> : std::true_type {};
template<> struct is_character<wchar_t> : std::true_type {};
template<> struct is_character<char16_t> : std::true_type {};
template<> struct is_character<char32_t> : std::true_type {};

#if __cplusplus >= 202002L
template<> struct is_character<char8_t> : std::true_type {};
#endif // __cplusplus >= 202002L

} // namespace lsd

#endif // LSD_TYPE_TRAITS_IS_CHARACTER_H_
