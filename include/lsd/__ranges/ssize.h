//
// Created by yonggyulee on 2023/12/30.
//

#ifndef LSD_RANGES_SSIZE_H_
#define LSD_RANGES_SSIZE_H_

#include <type_traits>
#include <utility>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__ranges/size.h"
#include "lsd/__type_traits/void_t.h"

namespace lsd {
namespace ranges {
namespace detail {

template<typename T, bool = (sizeof(T) > sizeof(std::ptrdiff_t)) /* true */>
struct ssize_type {
  using type = T;
};
template<typename T>
struct ssize_type<T, false> {
  using type = std::ptrdiff_t;
};

template<typename T, typename = void>
struct is_ranges_size_callable : std::false_type {};
template<typename T>
struct is_ranges_size_callable<T, void_t<decltype( lsd::ranges::size(std::declval<T>()) )>> : std::true_type {};

struct ssize_niebloid {
  template<typename T, std::enable_if_t<is_ranges_size_callable<T&&>::value, int> = 0>
  constexpr auto operator()(T&& t) const {
    using size_type = decltype(ranges::size(t));
    using unsigned_type = std::make_unsigned_t<size_type>;
    using R = typename ssize_type<unsigned_type>::type;
    return static_cast<R>(ranges::size(t));
  }
};

} // namespace detail

namespace niebloid {

LSD_INLINE_OR_STATIC constexpr detail::ssize_niebloid ssize{};

} // namespace niebloid
using namespace niebloid;

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_SSIZE_H_
