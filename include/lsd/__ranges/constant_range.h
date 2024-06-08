//
// Created by yonggyulee on 2023/12/30.
//

#ifndef LSD_RANGES_CONSTANT_RANGE_H_
#define LSD_RANGES_CONSTANT_RANGE_H_

#include <type_traits>

#include "lsd/__concepts/same_as.h"
#include "lsd/__iterator/input_iterator.h"
#include "lsd/__iterator/iter_const_reference_t.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__ranges/input_range.h"
#include "lsd/__ranges/iterator_t.h"
#include "lsd/__ranges/view.h"

namespace lsd {
namespace ranges {
namespace detail {

template<
    typename T,
    bool = conjunction<
               input_iterator<T>,
               has_typename_type<iter_const_reference<T>>
           >::value /* true */
>
struct constant_range_constant_iterator : same_as<iter_const_reference_t<T>, iter_reference_t<T>> {};
template<typename T>
struct constant_range_constant_iterator<T, false> : std::false_type {};

template<typename T, bool = input_range<T>::value /* true */>
struct constant_range_impl : constant_range_constant_iterator<iterator_t<T>> {};
template<typename T>
struct constant_range_impl<T, false> : std::false_type {};

} // namespace detail

template<typename T>
struct constant_range : detail::constant_range_impl<T> {};

} // namespace ranges
} // namespace lsd

#endif // LSD_RANGES_CONSTANT_RANGE_H_
