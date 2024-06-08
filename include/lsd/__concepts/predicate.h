//
// Created by yonggyulee on 2023/12/27.
//

#ifndef LSD_CONCEPTS_PREDICATE_H_
#define LSD_CONCEPTS_PREDICATE_H_

#include "lsd/__concepts/boolean_testable.h"
#include "lsd/__concepts/invocable.h"
#include "lsd/__functional/invoke.h"

namespace lsd {
namespace detail {

template<bool v /* false */, typename F, typename... Args>
struct predicate_impl : std::false_type {};

template<typename F, typename... Args>
struct predicate_impl<true, F, Args...> : boolean_testable<invoke_result_t<F, Args...>> {};

} // namespace detail

template<typename F, typename... Args>
struct predicate : detail::predicate_impl<regular_invocable<F, Args...>::value, F, Args...> {};

} // namespace lsd

#endif // LSD_CONCEPTS_PREDICATE_H_
