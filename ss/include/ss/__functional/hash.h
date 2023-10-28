//
// Created by cosge on 2023-10-29.
//

#ifndef SS___FUNCTIONAL_HASH_H_
#define SS___FUNCTIONAL_HASH_H_

#include <cstddef>
#include <cstdint>

#include "ss/__config.h"
#include "ss/__nullptr_t.h"
#include "ss/limits.h"
#include "ss/type_traits.h"

namespace ss {

template<typename Key>
struct hash;

namespace detail {

template<typename Key, int Size = (sizeof(Key) == sizeof(std::size_t) ? 0 : sizeof(Key) < sizeof(std::size_t) ? 1 : 2)>
struct integer_hash;

template<typename Key>
struct integer_hash<Key, 0> { // Same size
  std::size_t operator()(const Key& key) const noexcept {
    return key;
  }
};

template<typename Key>
struct integer_hash<Key, 1> { // Smaller size
  std::size_t operator()(const Key& key) const noexcept {
    return key;
  }
};

template<typename Key>
struct integer_hash<Key, 2> { // Bigger size
  std::size_t operator()(const Key& key) const noexcept {
    return key % numeric_limits<std::size_t>::max();
  }
};

template<typename Key, std::size_t Len = ((sizeof(Key) < sizeof(std::size_t)) + (sizeof(Key) / sizeof(std::size_t)))>
struct floating_point_hash {
 private:
  union u {
    Key f;
    std::size_t i[Len];
  };
 public:
  std::size_t operator()(const Key& key) const noexcept {
    u x{key};
    std::size_t v = x.i[0];
    for (int i = 1; i < Len; ++i) {
      v = v ^ x.i[i];
    }
    return v;
  }
};
} // namespace detail

template<> struct hash<bool> : public detail::integer_hash<bool> {};
template<> struct hash<char> : public detail::integer_hash<char> {};
template<> struct hash<signed char> : public detail::integer_hash<signed char> {};
template<> struct hash<unsigned char> : public detail::integer_hash<unsigned char> {};
#if SS_HAS_TYPE_CHAR8_T_CXX20
template<> struct hash<char8_t> : public detail::integer_hash<char8_t> {};
#endif
template<> struct hash<char16_t> : public detail::integer_hash<char16_t> {};
template<> struct hash<char32_t> : public detail::integer_hash<char32_t> {};
template<> struct hash<wchar_t> : public detail::integer_hash<wchar_t> {};
template<> struct hash<short> : public detail::integer_hash<short> {};
template<> struct hash<unsigned short> : public detail::integer_hash<unsigned short> {};
template<> struct hash<int> : public detail::integer_hash<int> {};
template<> struct hash<unsigned int> : public detail::integer_hash<unsigned int> {};
template<> struct hash<long> : public detail::integer_hash<long> {};
template<> struct hash<long long> : public detail::integer_hash<long long> {};
template<> struct hash<unsigned long> : public detail::integer_hash<unsigned long> {};
template<> struct hash<unsigned long long> : public detail::integer_hash<unsigned long long> {};
template<> struct hash<float> : public detail::floating_point_hash<float> {};
template<> struct hash<double> : public detail::floating_point_hash<double> {};
template<> struct hash<long double> : public detail::floating_point_hash<long double> {};

template<> struct hash<nullptr_t> : public detail::integer_hash<uintptr_t> {};
template< class T > struct hash<T*> : public detail::integer_hash<uintptr_t> {};

} // namespace ss

#endif // SS___FUNCTIONAL_HASH_H_
