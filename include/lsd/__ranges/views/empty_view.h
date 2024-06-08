//
// Created by yonggyulee on 2024/01/02.
//

#ifndef LSD_RANGES_VIEWS_EMPTY_VIEW_H_
#define LSD_RANGES_VIEWS_EMPTY_VIEW_H_

#include <cstddef>
#include <type_traits>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__ranges/view_interface.h"

namespace lsd {
namespace ranges {

template<typename T>
class empty_view : public ranges::view_interface<empty_view<T>> {
 public:
  static_assert(std::is_object<T>::value, "Constraints not satisfied");

  static constexpr T* begin() noexcept { return nullptr; }

  static constexpr T* end() noexcept { return nullptr; }

  static constexpr T* data() noexcept { return nullptr; }

  static constexpr std::size_t size() noexcept { return 0; }

  static constexpr bool empty() noexcept { return true; }
};

template<typename T>
struct enable_borrowed_range<empty_view<T>> : std::true_type {};

namespace views {

template<typename T>
LSD_INLINE_OR_STATIC constexpr empty_view<T> empty{};

} // namespace views

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_EMPTY_VIEW_H_
