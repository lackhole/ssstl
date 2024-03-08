# /*
#  * Created by YongGyu Lee on 2021/10/07.
#  */
#
# ifndef LSD___MEMORY_ADDRESSOF_H_
# define LSD___MEMORY_ADDRESSOF_H_

namespace lsd {

template<typename T>
inline constexpr T* addressof(T& arg) noexcept {
  return reinterpret_cast<T*>(&const_cast<char&>(reinterpret_cast<const volatile char&>(arg)));
}

template<typename T>
inline constexpr T* addressof(const T&&) = delete;

template<typename T>
const T* addressof(T&& arg) = delete;

} // namespace lsd

# endif // LSD___MEMORY_ADDRESSOF_H_
