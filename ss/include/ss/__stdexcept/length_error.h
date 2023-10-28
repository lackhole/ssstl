//
// Created by cosge on 2023-10-29.
//

#ifndef SS___STDEXCEPT_LENGTH_ERROR_H_
#define SS___STDEXCEPT_LENGTH_ERROR_H_

#include "ss/__stdexcept/logic_error.h"
#include "ss/string.h"

namespace ss {

class length_error : public logic_error {
 public:
  length_error(const string& what_arg) : logic_error(what_arg) {}
  length_error(const char* what_arg) : logic_error(what_arg) {}
};

} // namespace ss

#endif // SS___STDEXCEPT_LENGTH_ERROR_H_
