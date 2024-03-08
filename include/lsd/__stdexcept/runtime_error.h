//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___STDEXCEPT_RUNTIME_ERROR_H_
#define LSD___STDEXCEPT_RUNTIME_ERROR_H_

#include "lsd/exception.h"
#include "lsd/string.h"

namespace lsd {

class runtime_error : public exception {
 public:
  runtime_error(const string& what_arg) : exception(what_arg) {}
  runtime_error(const char* what_arg) : exception(what_arg) {}
};

} // namespace lsd

#endif // LSD___STDEXCEPT_RUNTIME_ERROR_H_
