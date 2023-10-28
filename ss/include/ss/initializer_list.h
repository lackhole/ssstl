# /*
#  * Created by YongGyu Lee on 2022/01/21.
#  */
#
# ifndef SS_INITIALIZER_LIST_H_
# define SS_INITIALIZER_LIST_H_
# 
# include <cstddef>
#
# include "ss/__config.h"
# include "ss/detail/macro.h"
# include "ss/iterator.h"
#
# if SS_HAS_INITIALIZER_LIST

#include <initializer_list>

namespace ss {

template<typename T>
using initializer_list = std::initializer_list<T>;

} // namespace ss

# else

namespace ss {

template<class T>
class initializer_list {
 public:
  using value_type      = T;
  using reference       = const T&;
  using const_reference = const T&;
  using size_type       = std::size_t;
  using iterator        = const T*;
  using const_iterator  = const T*;

 public:
  constexpr initializer_list() noexcept : ptr_(nullptr), size_(0) { }

#if defined(_MSC_VER)
  // See: https://docs.microsoft.com/en-us/cpp/standard-library/initializer-list-class#initializer_list
  constexpr initializer_list(const_iterator first, const_iterator last) noexcept
      : ptr_(first), size_(last - first) {}
#endif

  constexpr size_type size()  const noexcept { return size_; }
  constexpr const T* begin() const noexcept { return ptr_; }
  constexpr const T* end()   const noexcept { return ptr_ + size_; }

 private:
  constexpr initializer_list(const_iterator ptr, size_type size) noexcept
      : ptr_(ptr), size_(size) {}

  iterator  ptr_;
  size_type size_;
};

} // namespace ss

# endif

namespace ss {

template<typename T>
constexpr const T* begin(ss::initializer_list<T> il) noexcept {
  return il.begin();
}

template<typename T>
constexpr const T* end(ss::initializer_list<T> il) noexcept {
  return il.end();
}

template<typename T>
SS_NODISCARD
constexpr bool empty(ss::initializer_list<T> il) noexcept {
  return il.size() == 0;
}

template<typename T>
constexpr const T* data(ss::initializer_list<T> il) noexcept {
  return il.begin();
}

} // namespace ss

#endif // SS_INITIALIZER_LIST_H_
