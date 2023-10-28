//
// Created by cosge on 2023-10-29.
//

#ifndef SS___STDEXCEPT_OUT_OF_RANGE_H_
#define SS___STDEXCEPT_OUT_OF_RANGE_H_

#include "ss/__stdexcept/logic_error.h"
#include "ss/string.h"

namespace ss {

class out_of_range : public logic_error {
 public:
  out_of_range(const string& what_arg) : logic_error(what_arg) {}
  out_of_range(const char* what_arg) : logic_error(what_arg) {}
};

} // namespace ss

#endif // SS___STDEXCEPT_OUT_OF_RANGE_H_
