#include <iostream>
#include <utility>
#include <string>
#include <tuple>

#include "lsd/tuple.h"

#include "lsd_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif



int main() {
  LSD_INIT_TEST("tuple")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';


  LSD_TEST_RETURN
}
