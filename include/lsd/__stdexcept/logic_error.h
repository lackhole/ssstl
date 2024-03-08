//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___STDEXCEPT_LOGIC_ERROR_H_
#define LSD___STDEXCEPT_LOGIC_ERROR_H_

#include "lsd/exception.h"
#include "lsd/string.h"

namespace lsd {

class logic_error : public exception {
 public:
  logic_error(const string& what_arg) : exception(what_arg) {}
  logic_error(const char* what_arg) : exception(what_arg) {}
};

} // namespace lsd

#endif // LSD___STDEXCEPT_LOGIC_ERROR_H_
