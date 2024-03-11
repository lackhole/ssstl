//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_RANGES_BORROWED_RANGE_HPP_
#define LSD_RANGES_BORROWED_RANGE_HPP_

#include <type_traits>

#include "lsd/__ranges/__forward_declare.h"
#include "lsd/__ranges/enable_borrowed_range.h"
#include "lsd/__type_traits/conjunction.h"
#include "lsd/__type_traits/disjunction.h"
#include "lsd/__type_traits/remove_cvref.h"

namespace lsd {
namespace ranges {

template<typename R>
struct borrowed_range
    : conjunction<
        range<R>,
        disjunction<
          std::is_lvalue_reference<R>,
          enable_borrowed_range<remove_cvref_t<R>>
        >
      > {};

} // namespace lsd
} // namespace ranges

#endif // LSD_RANGES_BORROWED_RANGE_HPP_
