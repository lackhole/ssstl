//
// Created by yonggyulee on 2023/01/12.
//

#ifndef LSD_RANGES_VIEWS_TRANSFORM_HPP
#define LSD_RANGES_VIEWS_TRANSFORM_HPP

#include <type_traits>
#include <utility>

#include "lsd/__core/inline_or_static.h"
#include "lsd/__concepts/copy_constructible.h"
#include "lsd/__concepts/invocable.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/movable_box.h"
#include "lsd/__ranges/range_adaptor_closure.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__ranges/views/all.h"
#include "lsd/__ranges/views/transform_view.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

template<typename F>
class transform_adaptor_closure : public range_adaptor_closure<transform_adaptor_closure<F>> {
 public:
  explicit transform_adaptor_closure(F func) : func_(func) {}

  template<typename R, std::enable_if_t<ranges::range<R>::value, int> = 0>
  constexpr transform_view<views::all_t<R>, F>
  operator()(R&& r) const {
    return transform_view<views::all_t<R>, F>(std::forward<R>(r), *func_);
  }

 private:
  movable_box<F> func_;
};

struct transform_niebloid {
 private:
  template<typename R, typename F, bool = conjunction<input_range<R>, copy_constructible<F>>::value /* false */>
  struct check_range : std::false_type {};
  template<typename R, typename F>
  struct check_range<R, F, true>
      : conjunction<
            view<R>,
            std::is_object<F>,
            regular_invocable<F&, range_reference_t<R>>
        >{};

 public:
  template<typename R, typename F, std::enable_if_t<conjunction<
      viewable_range<R>,
      check_range<all_t<R>, std::decay_t<F>>
  >::value, int> = 0>
  constexpr auto operator()(R&& r, F&& fun) const {
    return transform_view<all_t<R>, std::decay_t<F>>(std::forward<R>(r), std::forward<F>(fun));
  }

  template<typename F, std::enable_if_t<conjunction<
      copy_constructible<std::decay_t<F>>,
      std::is_object<std::decay_t<F>>
  >::value, int> = 0>
  constexpr transform_adaptor_closure<std::decay_t<F>>
  operator()(F&& fun) const {
    return transform_adaptor_closure<std::decay_t<F>>(std::forward<F>(fun));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::transform_niebloid transform{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_TRANSFORM_HPP
