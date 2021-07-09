# /*
#  * Created by YongGyu Lee on 2021/07/09.
#  */
#
# ifndef SS_MEMORY_H_
# define SS_MEMORY_H_
#
# include "ss/detail/macro.h"

namespace ss {

/**
 * addressof
 * @tparam T
 * @param arg
 * @return address of arg
 */
template<typename T>
inline constexpr T* addressof(T& arg) noexcept {
  return reinterpret_cast<T*>(&const_cast<const char&>(reinterpret_cast<const volatile char&>(arg)));
}

template<typename T>
const T* addressof(T&& arg) = delete;

} // namespace ss

# endif // SS_MEMORY_H_
