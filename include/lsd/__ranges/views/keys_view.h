//
// Created by yonggyulee on 1/26/24.
//

#ifndef LSD_RANGES_VIEWS_KEYS_VIEW_H_
#define LSD_RANGES_VIEWS_KEYS_VIEW_H_

#include "lsd/__ranges/views/elements.h"
#include "lsd/__ranges/views/elements_view.h"

namespace lsd {
namespace ranges {

template<typename R>
using keys_view = elements_view<R, 0>;

namespace views {

LSD_INLINE_OR_STATIC constexpr detail::elements_adaptor_object<0> keys{};

} // namespace views

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_VIEWS_KEYS_VIEW_H_
