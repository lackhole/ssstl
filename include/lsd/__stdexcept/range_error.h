//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___STDEXCEPT_RANGE_ERROR_H_
#define LSD___STDEXCEPT_RANGE_ERROR_H_

#include "lsd/__stdexcept/runtime_error.h"
#include "lsd/string.h"

namespace lsd {

class range_error : public runtime_error {
 public:
  range_error(const string& what_arg) : runtime_error(what_arg) {}
  range_error(const char* what_arg) : runtime_error(what_arg) {}
};

} // namespace lsd

#endif // LSD___STDEXCEPT_RANGE_ERROR_H_
