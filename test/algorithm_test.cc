#include <array>
#include <iostream>
#include <algorithm>

#include "lsd/algorithm.h"

#include "lsd_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif



int main() {
  LSD_INIT_TEST("algorithm")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  
//  std::minmax(1, 2);
  
  LSD_TEST_RETURN
}
