//
// Created by yonggyulee on 2024/01/04.
//

#ifndef LSD_CORE_NODISCARD_HPP
#define LSD_CORE_NODISCARD_HPP

#if __cplusplus < 201703L
#  if defined(__GNUC__) && (__GNUC__ >= 4)
#    define LSD_NODISCARD __attribute__ ((warn_unused_result))
#  elif defined(_MSC_VER) && (_MSC_VER >= 1700)
#    define LSD_NODISCARD _Check_return_
#  else
#    define LSD_NODISCARD
#  endif
#else
#  define LSD_NODISCARD [[nodiscard]]
#endif

#endif // LSD_CORE_CONSTEXPR_HPP
