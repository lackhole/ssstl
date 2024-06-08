//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_CONCEPTS_DESTRUCTIBLE_H_
#define LSD_CONCEPTS_DESTRUCTIBLE_H_

#include <type_traits>

namespace lsd {

template<typename T>
struct destructible : std::is_nothrow_destructible<T> {};

} // namespace lsd

#endif // LSD_CONCEPTS_DESTRUCTIBLE_H_
