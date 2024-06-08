#ifndef LSD_CORE_STD_VERSION_H_
#define LSD_CORE_STD_VERSION_H_

#ifndef __cplusplus
#error "__cplusplus is not defined"
#endif

#ifndef LSD_CXX_VERSION
#  if __cplusplus >= 202302L
#    define LSD_CXX_VERSION 23
#  elif __cplusplus >= 202002L
#    define LSD_CXX_VERSION 20
#  elif __cplusplus >= 201703L
#    define LSD_CXX_VERSION 17
#  elif __cplusplus >= 201402L
#    define LSD_CXX_VERSION 14
#  else
#    error "C++14 is required"
#  endif
#endif

#endif // LSD_CORE_STD_VERSION_H_
