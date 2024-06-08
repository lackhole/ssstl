//
// Created by yonggyulee on 2023/12/31.
//

#ifndef LSD_ITERATOR_INDIRECTLY_COPYABLE_STORABLE_H_
#define LSD_ITERATOR_INDIRECTLY_COPYABLE_STORABLE_H_

#include <type_traits>

#include "lsd/__concepts/assignable_from.h"
#include "lsd/__concepts/copyable.h"
#include "lsd/__concepts/constructible_from.h"
#include "lsd/__iterator/indirectly_copyable.h"
#include "lsd/__iterator/indirectly_writable.h"
#include "lsd/__iterator/iter_reference_t.h"
#include "lsd/__iterator/iter_value_t.h"
#include "lsd/__type_traits/conjunction.h"

namespace lsd {
namespace detail {

template<typename In, typename Out, bool = indirectly_copyable<In, Out>::value /* true */>
struct indirectly_copyable_storable_impl
    : conjunction<
          indirectly_writable<Out, iter_value_t<In>&>,
          indirectly_writable<Out, const iter_value_t<In>&>,
          indirectly_writable<Out, iter_value_t<In>&&>,
          indirectly_writable<Out, const iter_value_t<In>&&>,
          copyable<iter_value_t<In>>,
          constructible_from<iter_value_t<In>, iter_reference_t<In>>,
          assignable_from<iter_value_t<In>&, iter_reference_t<In>>
      >{};

template<typename In, typename Out>
struct indirectly_copyable_storable_impl<In, Out, false> : std::false_type {};

} // namespace detail

template<typename In, typename Out>
struct indirectly_copyable_storable : detail::indirectly_copyable_storable_impl<In, Out> {};

} // namespace lsd

#endif // LSD_ITERATOR_INDIRECTLY_COPYABLE_STORABLE_H_
