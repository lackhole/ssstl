//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___STDEXCEPT_LENGTH_ERROR_H_
#define LSD___STDEXCEPT_LENGTH_ERROR_H_

#include "lsd/__stdexcept/logic_error.h"
#include "lsd/string.h"

namespace lsd {

class length_error : public logic_error {
 public:
  length_error(const string& what_arg) : logic_error(what_arg) {}
  length_error(const char* what_arg) : logic_error(what_arg) {}
};

} // namespace lsd

#endif // LSD___STDEXCEPT_LENGTH_ERROR_H_
