#include <iostream>

#include "ss/functional.h"

int main() {

  static_assert(__cplusplus >= 201400L, " ");
  std::cout << ss::invoke(0,0) << std::endl;
  return 0;
}
