//
// Created by yonggyulee on 2024/01/02.
//

#ifndef LSD_RANGES_OWINING_VIEW_HPP
#define LSD_RANGES_OWINING_VIEW_HPP

#include <utility>

#include "lsd/__concepts/movable.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/contiguous_range.h"
#include "lsd/__ranges/data.h"
#include "lsd/__ranges/empty.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/range.h"
#include "lsd/__ranges/size.h"
#include "lsd/__ranges/sized_range.h"
#include "lsd/__ranges/view_interface.h"
#include "lsd/__type_traits/is_initializer_list.h"
#include "lsd/__type_traits/is_invocable.h"

namespace lsd {
namespace ranges {

template<typename R>
class owning_view : public view_interface<owning_view<R>> {
 public:
  static_assert(range<R>::value, "Constraints not satisfied");
  static_assert(movable<R>::value, "Constraints not satisfied");
  static_assert(is_initializer_list<R>::value == false, "Constraints not satisfied");

  constexpr owning_view() = default;
  constexpr owning_view(owning_view&&) = default;
  constexpr owning_view(const owning_view&) = delete;
  constexpr owning_view(R&& t) noexcept(std::is_nothrow_move_constructible<R>::value)
      : r_(std::move(t)) {}


  owning_view& operator=(owning_view&&) = default;
  owning_view& operator=(const owning_view&) = delete;


  constexpr R& base() & noexcept { return r_; }
  constexpr const R& base() const & noexcept { return r_; }
  constexpr R&& base() && noexcept { return std::move(r_); }
  constexpr const R&& base() const && noexcept { return std::move(r_); }


  template<typename T = R>
  constexpr iterator_t<T> begin() {
    return ranges::begin(r_);
  }
  template<typename T = R, std::enable_if_t<range<const T>::value, int> = 0>
  constexpr auto begin() const {
    return ranges::begin(r_);
  }


  template<typename T = R>
  constexpr sentinel_t<T> end() {
    return ranges::end(r_);
  }
  template<typename T = R, std::enable_if_t<range<const T>::value, int> = 0>
  constexpr auto end() const {
    return ranges::end(r_);
  }


  template<typename T = R, std::enable_if_t<is_invocable<decltype(ranges::end), T&>::value, int> = 0>
  constexpr bool empty() {
    return ranges::empty(r_);
  }

  template<typename T = R, std::enable_if_t<is_invocable<decltype(ranges::end), const T&>::value, int> = 0>
  constexpr bool empty() const {
    return ranges::empty(r_);
  }


  template<typename T = R, std::enable_if_t<sized_range<T>::value, int> = 0>
  constexpr auto size() {
    return ranges::size(r_);
  }

  template<typename T = R, std::enable_if_t<sized_range<const T>::value, int> = 0>
  constexpr auto size() const {
    return ranges::size(r_);
  }


  template<typename T = R, std::enable_if_t<contiguous_range<T>::value, int> = 0>
  constexpr auto data() {
    return ranges::data(r_);
  }

  template<typename T = R, std::enable_if_t<contiguous_range<const T>::value, int> = 0>
  constexpr auto data() const {
    return ranges::data(r_);
  }

 private:
  R r_;
};

#if __cplusplus >= 201703L

template<typename R>
owning_view(R&&) -> owning_view<R>;

#endif

template<typename T>
struct enable_borrowed_range<owning_view<T>> : enable_borrowed_range<T> {};

} // namespace ranges
} // namespace namespace lsd

#endif // LSD_RANGES_OWINING_VIEW_HPP
