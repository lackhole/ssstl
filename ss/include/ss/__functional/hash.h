//
// Created by cosge on 2023-10-29.
//

#ifndef SS___FUNCTIONAL_HASH_H_
#define SS___FUNCTIONAL_HASH_H_

#include <cstddef>
#include <cstdint>

#include "ss/__config.h"
#include "ss/__size_t.h"
#include "ss/__nullptr_t.h"
#include "ss/limits.h"
#include "ss/type_traits.h"

namespace ss {

template<typename Key>
struct hash;

namespace detail {

// Fowler-Noll-Vo hash function
// https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function

template<size_t Bytes = sizeof(size_t) * CHAR_BIT> struct FNV_offset_basis;
template<size_t Bytes = sizeof(size_t) * CHAR_BIT> struct FNV_prime;

template<> struct FNV_prime<32> : integral_constant<size_t, 16777619U> {};
template<> struct FNV_offset_basis<32> : integral_constant<size_t, 2166136261U> {};

template<> struct FNV_prime<64> : integral_constant<size_t, 1099511628211U> {};
template<> struct FNV_offset_basis<64> : integral_constant<size_t, 14695981039346656037U> {};

//template<> struct FNV_prime<128> : integral_constant<size_t, 309485009821345068724781371U> {};
//template<> struct FNV_offset_basis<128> : integral_constant<size_t, 144066263297769815596495629667062367629U> {};

template<typename T>
inline size_t FNV_1a(size_t value, const T& byte) {
  value = value ^ static_cast<size_t>(byte);
  value = value * FNV_prime<>::value;
  return value;
}

size_t FNV_1a(size_t value, const unsigned char* const bytes, size_t size) {
  for (size_t i = 0; i < size; ++i) {
    value = FNV_1a(value, bytes[i]);
  }
  return value;
}

template<typename T>
size_t hash_value(const T& byte) {
  static_assert(is_integral<T>::value, "Invalid type");
  return FNV_1a(FNV_offset_basis<>::value, byte);
}

template<typename T>
size_t hash_array(const T* bytes, size_t size) {
  static_assert(is_arithmetic<T>::value, "Invalid type");
  return FNV_1a(FNV_offset_basis<>::value, reinterpret_cast<const unsigned char* const>(bytes), sizeof(T) * size);
}


template<typename T, size_t N>
size_t hash_array(const T(&bytes)[N]) {
  return hash_array(bytes, N);
}

template<typename Key, bool UseArray = (sizeof(Key) > sizeof(size_t)) || is_floating_point<Key>::value>
struct numeric_hash;

template<typename Key>
struct numeric_hash<Key, false> {
  size_t operator()(const Key& key) const noexcept {
    return hash_value(key);
  }
};

template<typename Key>
struct numeric_hash<Key, true> {
  size_t operator()(const Key& key) const noexcept {
    return hash_array(&key, 1);
  }
};

} // namespace detail

template<> struct hash<bool> : public detail::numeric_hash<bool> {};
template<> struct hash<char> : public detail::numeric_hash<char> {};
template<> struct hash<signed char> : public detail::numeric_hash<signed char> {};
template<> struct hash<unsigned char> : public detail::numeric_hash<unsigned char> {};
#if SS_HAS_TYPE_CHAR8_T_CXX20
template<> struct hash<char8_t> : public detail::numeric_hash<char8_t> {};
#endif
template<> struct hash<char16_t> : public detail::numeric_hash<char16_t> {};
template<> struct hash<char32_t> : public detail::numeric_hash<char32_t> {};
template<> struct hash<wchar_t> : public detail::numeric_hash<wchar_t> {};
template<> struct hash<short> : public detail::numeric_hash<short> {};
template<> struct hash<unsigned short> : public detail::numeric_hash<unsigned short> {};
template<> struct hash<int> : public detail::numeric_hash<int> {};
template<> struct hash<unsigned int> : public detail::numeric_hash<unsigned int> {};
template<> struct hash<long> : public detail::numeric_hash<long> {};
template<> struct hash<long long> : public detail::numeric_hash<long long> {};
template<> struct hash<unsigned long> : public detail::numeric_hash<unsigned long> {};
template<> struct hash<unsigned long long> : public detail::numeric_hash<unsigned long long> {};
template<> struct hash<float> : public detail::numeric_hash<float> {};
template<> struct hash<double> : public detail::numeric_hash<double> {};
template<> struct hash<long double> : public detail::numeric_hash<long double> {};

template<> struct hash<nullptr_t> : public detail::numeric_hash<uintptr_t> {};
template< class T > struct hash<T*> : public detail::numeric_hash<uintptr_t> {};

} // namespace ss

#endif // SS___FUNCTIONAL_HASH_H_
