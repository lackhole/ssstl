//
// Created by cosge on 2023-10-29.
//

#ifndef SS___STDEXCEPT_RUNTIME_ERROR_H_
#define SS___STDEXCEPT_RUNTIME_ERROR_H_

#include "ss/exception.h"
#include "ss/string.h"

namespace ss {

class runtime_error : public exception {
 public:
  runtime_error(const string& what_arg) : exception(what_arg) {}
  runtime_error(const char* what_arg) : exception(what_arg) {}
};

} // namespace ss

#endif // SS___STDEXCEPT_RUNTIME_ERROR_H_
