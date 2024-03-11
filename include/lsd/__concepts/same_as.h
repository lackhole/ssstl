//
// Created by cosge on 2023-12-02.
//

#ifndef LSD_CONCEPTS_SAME_AS_HPP_
#define LSD_CONCEPTS_SAME_AS_HPP_

#include <type_traits>

namespace lsd {

template<typename T, typename U>
struct same_as : std::is_same<T, U> {};

} // namespace lsd

#endif // LSD_CONCEPTS_SAME_AS_HPP_
