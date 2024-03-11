#include <iostream>
#include <memory>
#include <string>

#include "lsd/memory.h"

#include "lsd_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif



int main() {
  LSD_INIT_TEST("utility")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  struct foo {
    foo() {}
    foo(const foo&) {}; // = delete;
//    foo(foo&&) = delete;
  };


  LSD_TEST_RETURN
}
