//
// Created by cosge on 2023-10-29.
//

#ifndef SS___STDEXCEPT_INVALID_ARGUMENT_H_
#define SS___STDEXCEPT_INVALID_ARGUMENT_H_

#include "ss/__stdexcept/logic_error.h"
#include "ss/string.h"

namespace ss {

class invalid_argument : public logic_error {
 public:
  invalid_argument(const string& what_arg) : logic_error(what_arg) {}
  invalid_argument(const char* what_arg) : logic_error(what_arg) {}
};

} // namespace ss

#endif // SS___STDEXCEPT_INVALID_ARGUMENT_H_
