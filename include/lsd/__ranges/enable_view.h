//
// Created by yonggyulee on 2023/12/30.
//

#ifndef LSD_RANGES_ENABLE_VIEW_HPP
#define LSD_RANGES_ENABLE_VIEW_HPP

#include "lsd/__concepts/derived_from.h"
#include "lsd/__concepts/derived_from_single_crtp.h"
#include "lsd/__ranges/__forward_declare.h"
#include "lsd/__ranges/view_base.h"
#include "lsd/__type_traits/disjunction.h"

namespace lsd {
namespace ranges {

template<typename T>
struct enable_view : disjunction<
          derived_from<T, view_base>,
          derived_from_single_crtp<T, view_interface>
      > {};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_ENABLE_VIEW_HPP
