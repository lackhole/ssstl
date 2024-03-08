//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___STDEXCEPT_OUT_OF_RANGE_H_
#define LSD___STDEXCEPT_OUT_OF_RANGE_H_

#include "lsd/__stdexcept/logic_error.h"
#include "lsd/string.h"

namespace lsd {

class out_of_range : public logic_error {
 public:
  out_of_range(const string& what_arg) : logic_error(what_arg) {}
  out_of_range(const char* what_arg) : logic_error(what_arg) {}
};

} // namespace lsd

#endif // LSD___STDEXCEPT_OUT_OF_RANGE_H_
