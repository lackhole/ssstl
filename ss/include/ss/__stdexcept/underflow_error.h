//
// Created by cosge on 2023-10-29.
//

#ifndef SS___STDEXCEPT_UNDERFLOW_ERROR_H_
#define SS___STDEXCEPT_UNDERFLOW_ERROR_H_

#include "ss/__stdexcept/runtime_error.h"
#include "ss/string.h"

namespace ss {

class underflow_error : public runtime_error {
 public:
  underflow_error(const string& what_arg) : runtime_error(what_arg) {}
  underflow_error(const char* what_arg) : runtime_error(what_arg) {}
};

} // namespace ss

#endif // SS___STDEXCEPT_UNDERFLOW_ERROR_H_
