//
// Created by cosge on 2023-10-29.
//

#ifndef SS___NEW_ALIGN_VAL_T_H_
#define SS___NEW_ALIGN_VAL_T_H_

#include <new>

namespace ss {

#if __cplusplus >= 201703L

using align_val_t = std::align_val_t;

#endif

} // namespace ss

#endif // SS___NEW_ALIGN_VAL_T_H_
