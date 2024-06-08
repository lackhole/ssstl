//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_RANGES_VIEWS_VALUES_VIEW_H_
#define LSD_RANGES_VIEWS_VALUES_VIEW_H_

#include "lsd/__ranges/views/elements.h"
#include "lsd/__ranges/views/elements_view.h"

namespace lsd {
namespace ranges {

template<typename R>
using values_view = elements_view<R, 1>;

namespace views {

LSD_INLINE_VARIABLE constexpr detail::elements_adaptor_object<1> values{};

} // namespace views

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_VALUES_VIEW_H_
