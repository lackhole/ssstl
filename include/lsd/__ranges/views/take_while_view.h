//
// Created by YongGyu Lee on 3/27/24.
//

#ifndef LSD_RANGES_VIEWS_TAKE_WHILE_VIEW_H_
#define LSD_RANGES_VIEWS_TAKE_WHILE_VIEW_H_

#include <memory>
#include <type_traits>
#include <utility>

#include "lsd/__core/constexpr.h"
#include "lsd/__concepts/convertible_to.h"
#include "lsd/__concepts/copy_constructible.h"
#include "lsd/__functional/invoke.h"
#include "lsd/__iterator/indirect_unary_predicate.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/movable_box.h"
#include "lsd/__ranges/range.h"
#include "lsd/__ranges/sentinel_t.h"
#include "lsd/__ranges/simple_view.h"
#include "lsd/__ranges/view.h"
#include "lsd/__ranges/viewable_range.h"
#include "lsd/__ranges/view_interface.h"
#include "lsd/__ranges/views/all.h"
#include "lsd/__type_traits/bool_constant.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/maybe_const.h"
#include "lsd/__type_traits/negation.h"
#include "lsd/__utility/cxx20_rel_ops.h"

namespace lsd {
namespace ranges {

template<typename V, typename Pred>
class take_while_view {
 public:
  static_assert(ranges::view<V>::value, "Constraints not satisfied");
  static_assert(ranges::input_range<V>::value, "Constraints not satisfied");
  static_assert(std::is_object<Pred>::value, "Constraints not satisfied");
  static_assert(indirect_unary_predicate<const Pred, iterator_t<V>>::value, "Constraints not satisfied");

  template<bool Const>
  class sentinel {
    using Base = maybe_const<Const, V>;
    friend class sentinel<!Const>;

   public:
    sentinel() = default;

    constexpr explicit sentinel(sentinel_t<Base> end, const Pred* pred)
        : end_(std::move(end)), pred_(pred) {}

    template<bool AntiConst, std::enable_if_t<conjunction<
        bool_constant<((Const != AntiConst) && Const)>,
        convertible_to<sentinel_t<V>, sentinel_t<Base>>
    >::value, int> = 0>
    constexpr sentinel(sentinel<AntiConst> that)
        : end_(std::move(that.end_)), pred_(that.pred_) {}

    constexpr sentinel_t<Base> base() const {
      return end_;
    }

    friend constexpr bool operator==(const iterator_t<Base>& x, const sentinel& y) {
      using namespace lsd::rel_ops;
      return x == y.end_ || !lsd::invoke(*y.pred_, *x);
    }

    friend constexpr bool operator!=(const iterator_t<Base>& x, const sentinel& y) {
      return !(x == y);
    }

    friend constexpr bool operator==(const sentinel& y, const iterator_t<Base>& x) {
      return x == y;
    }

    friend constexpr bool operator!=(const sentinel& y, const iterator_t<Base>& x) {
      return !(x == y);
    }

   private:
    sentinel_t<Base> end_;
    const Pred* pred_;
  };

  take_while_view() = default;

  constexpr explicit take_while_view(V base, Pred pred)
      : base_(std::move(base)), pred_(std::move(pred)) {}

  template<typename Dummy = void, std::enable_if_t<lsd::conjunction<std::is_void<Dummy>,
      copy_constructible<V>
  >::value, int> = 0>
  constexpr V base() const& {
    return base_;
  }

  constexpr V base() && {
    return std::move(base_);
  }

  constexpr const Pred& pred() const {
    return *pred_;
  }

  template<typename Dummy = void, std::enable_if_t<lsd::conjunction<std::is_void<Dummy>,
      negation<simple_view<V>>
  >::value, int> = 0>
  constexpr auto begin() {
    return ranges::begin(base_);
  }

  template<typename Dummy = void, std::enable_if_t<lsd::conjunction<std::is_void<Dummy>,
      range<const V>,
      indirect_unary_predicate<const Pred, iterator_t<const V>>
  >::value, int> = 0>
  constexpr auto begin() const {
    return ranges::begin(base_);
  }

  template<typename Dummy = void, std::enable_if_t<lsd::conjunction<std::is_void<Dummy>,
      negation<simple_view<V>>
  >::value, int> = 0>
  LSD_CONSTEXPR_AFTER_CXX17 auto end() {
    return sentinel<false>{ranges::end(base_), pred_.operator->()};
  }

  template<typename Dummy = void, std::enable_if_t<lsd::conjunction<std::is_void<Dummy>,
      range<const V>,
      indirect_unary_predicate<const Pred, iterator_t<const V>>
  >::value, int> = 0>
  LSD_CONSTEXPR_AFTER_CXX17 auto end() const {
    return sentinel<true>{ranges::end(base_), pred_.operator->()};
  }

 private:
  V base_{};
  movable_box<Pred> pred_{};
};

#if __cplusplus >= 201703L

template<typename R, typename Pred>
take_while_view(R&&, Pred) -> take_while_view<views::all_t<R>, Pred>;

#endif

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_TAKE_WHILE_VIEW_H_
