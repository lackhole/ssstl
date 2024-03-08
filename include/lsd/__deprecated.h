//
// Created by cosge on 2023-10-19.
//

#ifndef LSD___DEPRECATED_H_
#define LSD___DEPRECATED_H_

#if __cplusplus >= 201402L
  #define LSD_DEPRECATED(msg) [[deprecated(msg)]]
#else
  #define LSD_DEPRECATED(msg)
#endif

#if __cplusplus >= 202302L
  #define LSD_DEPRECATED_AFTER_CXX_14(msg) LSD_DEPRECATED(msg)
  #define LSD_DEPRECATED_AFTER_CXX_17(msg) LSD_DEPRECATED(msg)
  #define LSD_DEPRECATED_AFTER_CXX_20(msg) LSD_DEPRECATED(msg)
  #define LSD_DEPRECATED_AFTER_CXX_23(msg) LSD_DEPRECATED(msg)
#elif __cplusplus >= 202002L
  #define LSD_DEPRECATED_AFTER_CXX_14(msg) LSD_DEPRECATED(msg)
  #define LSD_DEPRECATED_AFTER_CXX_17(msg) LSD_DEPRECATED(msg)
  #define LSD_DEPRECATED_AFTER_CXX_20(msg) LSD_DEPRECATED(msg)
  #define LSD_DEPRECATED_AFTER_CXX_23(msg)
#elif __cplusplus >= 201703L
  #define LSD_DEPRECATED_AFTER_CXX_14(msg) LSD_DEPRECATED(msg)
  #define LSD_DEPRECATED_AFTER_CXX_17(msg) LSD_DEPRECATED(msg)
  #define LSD_DEPRECATED_AFTER_CXX_20(msg)
  #define LSD_DEPRECATED_AFTER_CXX_23(msg)
#elif __cplusplus >= 201402L
  #define LSD_DEPRECATED_AFTER_CXX_14(msg) LSD_DEPRECATED(msg)
  #define LSD_DEPRECATED_AFTER_CXX_17(msg)
  #define LSD_DEPRECATED_AFTER_CXX_20(msg)
  #define LSD_DEPRECATED_AFTER_CXX_23(msg)
#else
  #define LSD_DEPRECATED_AFTER_CXX_14(msg)
  #define LSD_DEPRECATED_AFTER_CXX_17(msg)
  #define LSD_DEPRECATED_AFTER_CXX_20(msg)
  #define LSD_DEPRECATED_AFTER_CXX_23(msg)
#endif


#endif // LSD___DEPRECATED_H_
