# /*
#  * Created by YongGyu Lee on 2022/01/21.
#  */
#
# ifndef LSD_INITIALIZER_LIST_H_
# define LSD_INITIALIZER_LIST_H_
# 
# include <cstddef>
#
# include "lsd/__core/macro.h"
# include "lsd/iterator.h"

#include <initializer_list>

namespace lsd {

template<typename T>
using initializer_list = std::initializer_list<T>;

template<typename T>
constexpr const T* begin(initializer_list<T> il) noexcept {
  return il.begin();
}

template<typename T>
constexpr const T* end(initializer_list<T> il) noexcept {
  return il.end();
}

template<typename T>
LSD_NODISCARD
constexpr bool empty(initializer_list<T> il) noexcept {
  return il.size() == 0;
}

template<typename T>
constexpr const T* data(initializer_list<T> il) noexcept {
  return il.begin();
}

} // namespace lsd

#endif // LSD_INITIALIZER_LIST_H_
