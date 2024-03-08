//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___UTILITY_DECLVAL_H_
#define LSD___UTILITY_DECLVAL_H_

namespace lsd {

/**
 * declval
 * It have to be declared here to avoid mutal header inclusion error
 * @tparam T
 */
template<typename T>
inline add_rvalue_reference_t<T> declval() noexcept;

} // namespace lsd

#endif //LSD___UTILITY_DECLVAL_H_
