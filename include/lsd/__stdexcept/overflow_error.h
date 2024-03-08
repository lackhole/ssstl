//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___STDEXCEPT_OVERFLOW_ERROR_H_
#define LSD___STDEXCEPT_OVERFLOW_ERROR_H_

#include "lsd/__stdexcept/runtime_error.h"
#include "lsd/string.h"

namespace lsd {

class overflow_error : public runtime_error {
 public:
  overflow_error(const string& what_arg) : runtime_error(what_arg) {}
  overflow_error(const char* what_arg) : runtime_error(what_arg) {}
};

} // namespace lsd

#endif // LSD___STDEXCEPT_OVERFLOW_ERROR_H_
