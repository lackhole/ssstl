//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___NEW_ALIGN_VAL_T_H_
#define LSD___NEW_ALIGN_VAL_T_H_

#include <new>

namespace lsd {

#if __cplusplus >= 201703L

using align_val_t = std::align_val_t;

#endif

} // namespace lsd

#endif // LSD___NEW_ALIGN_VAL_T_H_
