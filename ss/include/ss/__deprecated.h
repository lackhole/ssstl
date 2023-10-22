//
// Created by cosge on 2023-10-19.
//

#ifndef SS___DEPRECATED_H_
#define SS___DEPRECATED_H_

#if __cplusplus >= 201402L
  #define SS_DEPRECATED(msg) [[deprecated(msg)]]
#else
  #define SS_DEPRECATED(msg)
#endif

#if __cplusplus >= 202302L
  #define SS_DEPRECATED_AFTER_CXX_14(msg) SS_DEPRECATED(msg)
  #define SS_DEPRECATED_AFTER_CXX_17(msg) SS_DEPRECATED(msg)
  #define SS_DEPRECATED_AFTER_CXX_20(msg) SS_DEPRECATED(msg)
  #define SS_DEPRECATED_AFTER_CXX_23(msg) SS_DEPRECATED(msg)
#elif __cplusplus >= 202002L
  #define SS_DEPRECATED_AFTER_CXX_14(msg) SS_DEPRECATED(msg)
  #define SS_DEPRECATED_AFTER_CXX_17(msg) SS_DEPRECATED(msg)
  #define SS_DEPRECATED_AFTER_CXX_20(msg) SS_DEPRECATED(msg)
  #define SS_DEPRECATED_AFTER_CXX_23(msg)
#elif __cplusplus >= 201703L
  #define SS_DEPRECATED_AFTER_CXX_14(msg) SS_DEPRECATED(msg)
  #define SS_DEPRECATED_AFTER_CXX_17(msg) SS_DEPRECATED(msg)
  #define SS_DEPRECATED_AFTER_CXX_20(msg)
  #define SS_DEPRECATED_AFTER_CXX_23(msg)
#elif __cplusplus >= 201402L
  #define SS_DEPRECATED_AFTER_CXX_14(msg) SS_DEPRECATED(msg)
  #define SS_DEPRECATED_AFTER_CXX_17(msg)
  #define SS_DEPRECATED_AFTER_CXX_20(msg)
  #define SS_DEPRECATED_AFTER_CXX_23(msg)
#else
  #define SS_DEPRECATED_AFTER_CXX_14(msg)
  #define SS_DEPRECATED_AFTER_CXX_17(msg)
  #define SS_DEPRECATED_AFTER_CXX_20(msg)
  #define SS_DEPRECATED_AFTER_CXX_23(msg)
#endif


#endif // SS___DEPRECATED_H_
