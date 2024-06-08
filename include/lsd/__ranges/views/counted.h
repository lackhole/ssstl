//
// Created by yonggyulee on 1/27/24.
//

#ifndef LSD_RANGES_VIEWS_COUNTED_H_
#define LSD_RANGES_VIEWS_COUNTED_H_

#include <cstddef>
#include <type_traits>

#include "lsd/__concepts/convertible_to.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__iterator/contiguous_iterator.h"
#include "lsd/__iterator/counted_iterator.h"
#include "lsd/__iterator/default_sentinel_t.h"
#include "lsd/__iterator/input_or_output_iterator.h"
#include "lsd/__iterator/iter_difference_t.h"
#include "lsd/__iterator/random_access_iterator.h"
#include "lsd/__memory/to_address.h"
#include "lsd/span.h"
#include "lsd/__ranges/subrange.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/detail/return_category.h"
#include "lsd/__type_traits/detail/tag.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace ranges {
namespace views {
namespace detail {

using lsd::detail::return_category;
using lsd::detail::tag_1;
using lsd::detail::tag_2;
using lsd::detail::tag_else;

struct counted_niebloid {
 private:
  template<typename T, typename DiffType, bool = input_or_output_iterator<T>::value>
  struct check : convertible_to<DiffType, iter_difference_t<T>> {};
  template<typename T, typename DiffType>
  struct check<T, DiffType, false> : std::false_type {};

  template<typename T>
  using tag = lsd::detail::conditional_tag<
      contiguous_iterator<T>,
      random_access_iterator<T>>;

  template<typename D, typename I, typename DiffType>
  constexpr auto call(I&& it, DiffType&& count, tag_1 /* contigious_iterator */) const {
    using Address = decltype(lsd::to_address(std::forward<I>(it)));
    using T = std::remove_reference_t<iter_reference_t<Address>>;
    return span<T>(
        lsd::to_address(std::forward<I>(it)),
        static_cast<std::size_t>(static_cast<D>(std::forward<DiffType>(count))) );
  }

  template<typename D, typename I, typename DiffType>
  constexpr auto call(I&& it, DiffType&& count, tag_2 /* random_access_iterator */) const {
    return ranges::make_subrange(it, it + static_cast<D>(std::forward<DiffType>(count)));
  }

  template<typename D, typename I, typename DiffType>
  constexpr auto call(I&& it, DiffType&& count, tag_else) const {
    return ranges::make_subrange(
        counted_iterator<remove_cvref_t<I>>(
            std::forward<I>(it),
            std::forward<DiffType>(count)),
        default_sentinel
    );
  }

 public:
  template<typename I, typename DiffType, std::enable_if_t<
      check<std::decay_t<I>, DiffType&&>::value, int> = 0>
  constexpr auto operator()(I&& it, DiffType&& count) const {
    using T = std::decay_t<I>;
    using D = iter_difference_t<T>;
    return call<D>(std::forward<I>(it), std::forward<DiffType>(count), tag<T>{});
  }

};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::counted_niebloid counted{};

} // namespace views
} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_COUNTED_H_
