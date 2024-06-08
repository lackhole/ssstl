//
// Created by yonggyulee on 2024/01/03.
//

#ifndef LSD_CORE_CONSTEXPR_H_
#define LSD_CORE_CONSTEXPR_H_

// TODO: Use CheckCXXSybolExists
#define LSD_CONSTEXPR constexpr

#if __cplusplus >= 201402L
#define LSD_CONSTEXPR_AFTER_CXX14 constexpr
#else
#define LSD_CONSTEXPR_AFTER_CXX14
#endif

#if __cplusplus >= 201703L
#define LSD_CONSTEXPR_AFTER_CXX17 constexpr
#else
#define LSD_CONSTEXPR_AFTER_CXX17
#endif

#if __cplusplus >= 202002L
#define LSD_CONSTEXPR_AFTER_CXX20 constexpr
#else
#define LSD_CONSTEXPR_AFTER_CXX20
#endif

#if __cplusplus >= 202302L
#define LSD_CONSTEXPR_AFTER_CXX23 constexpr
#else
#define LSD_CONSTEXPR_AFTER_CXX23
#endif

#endif // LSD_CORE_CONSTEXPR_H_
