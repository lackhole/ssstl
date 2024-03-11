//
// Created by YongGyu Lee on 2021/10/05.
//

#include <functional>
#include <iostream>
#include <type_traits>

#include "lsd/functional.h"

#include "lsd_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif

struct A {
  A(int) {}
};


int main() {
  LSD_INIT_TEST("functional")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';



  LSD_TEST_RETURN
}
