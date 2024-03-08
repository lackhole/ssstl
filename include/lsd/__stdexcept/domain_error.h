//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___STDEXCEPT_DOMAIN_ERROR_H_
#define LSD___STDEXCEPT_DOMAIN_ERROR_H_

#include "lsd/__stdexcept/logic_error.h"
#include "lsd/string.h"

namespace lsd {

class domain_error : public logic_error {
 public:
  domain_error(const string& what_arg) : logic_error(what_arg) {}
  domain_error(const char* what_arg) : logic_error(what_arg) {}
};

} // namespace lsd

#endif // LSD___STDEXCEPT_DOMAIN_ERROR_H_
