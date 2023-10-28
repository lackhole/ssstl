//
// Created by cosge on 2023-10-29.
//

#ifndef SS___STDEXCEPT_RANGE_ERROR_H_
#define SS___STDEXCEPT_RANGE_ERROR_H_

#include "ss/__stdexcept/runtime_error.h"
#include "ss/string.h"

namespace ss {

class range_error : public runtime_error {
 public:
  range_error(const string& what_arg) : runtime_error(what_arg) {}
  range_error(const char* what_arg) : runtime_error(what_arg) {}
};

} // namespace ss

#endif // SS___STDEXCEPT_RANGE_ERROR_H_
