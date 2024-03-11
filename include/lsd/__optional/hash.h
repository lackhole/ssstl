# /*
#  * Created by YongGyu Lee on 2021/05/24.
#  */
#
# ifndef LSD_OPTIONAL_HASH_H_
# define LSD_OPTIONAL_HASH_H_
#
# include <cstddef>
#
# include <functional>
# include <type_traits>
#
# include "lsd/__optional/internal/hash.h"
# include "lsd/__optional/optional.h"

namespace std {

template<typename T>
struct hash<lsd::optional<T>> : lsd::internal::optional::hash_constructible<std::remove_const_t<T>> {
  using argument_type = lsd::optional<T>;
  using result_type = std::size_t;

  result_type operator()(const argument_type& key) const {
    return key.has_value() ? ::std::hash<std::remove_const_t<T>>()(*key) : 0;
  }
};

} // namespace std

# endif // LSD_OPTIONAL_HASH_H_
