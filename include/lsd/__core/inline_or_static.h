//
// Created by yonggyulee on 2023/12/25.
//

#ifndef LSD_CORE_INLINE_OR_STATIC_H_
#define LSD_CORE_INLINE_OR_STATIC_H_

#if __cplusplus < 201703L
#define LSD_INLINE_OR_STATIC static
#else
#define LSD_INLINE_OR_STATIC inline
#endif

#endif // LSD_CORE_INLINE_OR_STATIC_H_
