# /*
#  * Created by YongGyu Lee on 2021/05/25.
#  */
#
# ifndef LSD_OPTIONAL_INTERNAL_HASH_H_
# define LSD_OPTIONAL_INTERNAL_HASH_H_
#
# include <functional>
# include <type_traits>

namespace lsd {
namespace internal {
namespace optional {

struct not_constructible {
  not_constructible() = delete;
};

struct constructible {};

template<typename T>
using hash_constructible =
std::conditional_t<
  std::is_default_constructible<std::hash<T>>::value,
  constructible,
  not_constructible>;

} // namespace optional
} // namespace internal
} // namespace lsd

# endif // LSD_OPTIONAL_INTERNAL_HASH_H_
