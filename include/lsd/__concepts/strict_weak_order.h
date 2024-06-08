//
// Created by yonggyulee on 2023/12/27.
//

#ifndef LSD_CONCEPTS_STRICT_WEAK_ORDER_H_
#define LSD_CONCEPTS_STRICT_WEAK_ORDER_H_

#include "lsd/__concepts/relation.h"

namespace lsd {

template<typename R, typename T, typename U>
struct strict_weak_order : relation<R, T, U> {};

} // namespace lsd

#endif // LSD_CONCEPTS_STRICT_WEAK_ORDER_H_
