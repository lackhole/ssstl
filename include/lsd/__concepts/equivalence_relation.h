//
// Created by yonggyulee on 2023/12/27.
//

#ifndef LSD_CONCEPTS_EQUIVALENCE_RELATION_HPP
#define LSD_CONCEPTS_EQUIVALENCE_RELATION_HPP

#include "lsd/__concepts/relation.h"

namespace lsd {

template<typename R, typename T, typename U>
struct equivalence_relation : relation<R, T, U> {};

} // namespace lsd

#endif // LSD_CONCEPTS_EQUIVALENCE_RELATION_HPP
