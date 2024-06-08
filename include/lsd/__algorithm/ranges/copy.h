//
// Created by yonggyulee on 1/12/24.
//

#ifndef LSD_ALGORITHM_RANGES_COPY_H_
#define LSD_ALGORITHM_RANGES_COPY_H_

#include <type_traits>
#include <utility>

#include "lsd/__algorithm/ranges/in_out_result.h"
#include "lsd/__core/inline_or_static.h"
#include "lsd/__functional/identity.h"
#include "lsd/__iterator/indirectly_copyable.h"
#include "lsd/__iterator/input_iterator.h"
#include "lsd/__iterator/sentinel_for.h"
#include "lsd/__iterator/weakly_incrementable.h"
#include "lsd/__ranges/begin.h"
#include "lsd/__ranges/borrowed_iterator_t.h"
#include "lsd/__ranges/end.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/has_typename_type.h"

namespace lsd {
namespace ranges {

template<typename I, typename O> using copy_result = in_out_result<I, O>;
template<typename I, typename O> using copy_if_result = in_out_result<I, O>;

namespace detail {

struct copy_niebloid {
 private:
  template<typename R, typename O, bool = input_range<R>::value /* false */>
  struct check_range : std::false_type {};
  template<typename R, typename O>
  struct check_range<R, O, true>
      : conjunction<
          weakly_incrementable<O>,
          indirectly_copyable<iterator_t<R>, O>,
          has_typename_type<borrowed_iterator<R>>
        > {};

 public:
  template<typename I, typename S, typename O, std::enable_if_t<conjunction<
    input_iterator<I>,
    sentinel_for<S, I>,
    weakly_incrementable<O>,
    indirectly_copyable<I, O>
  >::value, int> = 0>
  constexpr copy_result<I, O> operator()(I first, S last, O result) const {
    for (; first != last; ++first, (void)++result)
      *result = *first;
    return {std::move(first), std::move(result)};
  }

  template<typename R, typename O, std::enable_if_t<check_range<R, O>::value, int> = 0>
  constexpr copy_result<borrowed_iterator_t<R>, O> operator()(R&& r, O result) const {
    return (*this)(ranges::begin(r), ranges::end(r), std::move(result));
  }
};

} // namespace detail

LSD_INLINE_OR_STATIC constexpr detail::copy_niebloid copy{};

} // namespace ranges
} // namespace lsd

#endif // LSD_ALGORITHM_RANGES_COPY_H_
