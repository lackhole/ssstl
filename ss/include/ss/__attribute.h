//
// Created by cosge on 2023-10-19.
//

#ifndef SS___ATTRIBUTE_H_
#define SS___ATTRIBUTE_H_

#if defined(__has_attribute)
  #define SS_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
  #define SS_HAS_ATTRIBUTE(x) 0
#endif


#endif // SS___ATTRIBUTE_H_
