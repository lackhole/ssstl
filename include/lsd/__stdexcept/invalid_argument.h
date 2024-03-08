//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___STDEXCEPT_INVALID_ARGUMENT_H_
#define LSD___STDEXCEPT_INVALID_ARGUMENT_H_

#include "lsd/__stdexcept/logic_error.h"
#include "lsd/string.h"

namespace lsd {

class invalid_argument : public logic_error {
 public:
  invalid_argument(const string& what_arg) : logic_error(what_arg) {}
  invalid_argument(const char* what_arg) : logic_error(what_arg) {}
};

} // namespace lsd

#endif // LSD___STDEXCEPT_INVALID_ARGUMENT_H_
