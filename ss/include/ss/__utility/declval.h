//
// Created by cosge on 2023-10-29.
//

#ifndef SS___UTILITY_DECLVAL_H_
#define SS___UTILITY_DECLVAL_H_

namespace ss {

/**
 * declval
 * It have to be declared here to avoid mutal header inclusion error
 * @tparam T
 */
template<typename T>
inline add_rvalue_reference_t<T> declval() noexcept;

} // namespace ss

#endif //SS___UTILITY_DECLVAL_H_
