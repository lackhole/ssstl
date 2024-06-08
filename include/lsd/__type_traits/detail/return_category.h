//
// Created by yonggyulee on 2023/12/24.
//

#ifndef LSD_TYPE_TRAITS_DETAIL_RETURN_CATEGORY_H_
#define LSD_TYPE_TRAITS_DETAIL_RETURN_CATEGORY_H_

#include <type_traits>

namespace lsd {
namespace detail {

template<int v, typename...>
struct return_category : std::integral_constant<int, v> {};

template<int v, typename R>
struct return_category<v, R> : std::integral_constant<int, v> {
  using return_type = R;
};


} // namespace lsd
} // namespace detail

#endif // LSD_TYPE_TRAITS_DETAIL_RETURN_CATEGORY_H_
