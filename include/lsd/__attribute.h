//
// Created by cosge on 2023-10-19.
//

#ifndef LSD___ATTRIBUTE_H_
#define LSD___ATTRIBUTE_H_

#if defined(__has_attribute)
  #define LSD_HAS_ATTRIBUTE(x) __has_attribute(x)
#else
  #define LSD_HAS_ATTRIBUTE(x) 0
#endif


#endif // LSD___ATTRIBUTE_H_
