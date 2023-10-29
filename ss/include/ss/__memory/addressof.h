# /*
#  * Created by YongGyu Lee on 2021/10/07.
#  */
#
# ifndef SS___MEMORY_ADDRESSOF_H_
# define SS___MEMORY_ADDRESSOF_H_

namespace ss {

template<typename T>
inline constexpr T* addressof(T& arg) noexcept {
  return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
}

template<typename T>
inline constexpr T* addressof(const T&&) = delete;

template<typename T>
const T* addressof(T&& arg) = delete;

} // namespace ss

# endif // SS___MEMORY_ADDRESSOF_H_
