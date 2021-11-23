#include <iostream>
#include <memory>
#include <string>

#include "ss/memory.h"

#include "ss_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif



int main() {
  SS_INIT_TEST("utility")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  struct foo {
    foo() {}
    foo(const foo&) {}; // = delete;
//    foo(foo&&) = delete;
  };

  static_assert(ss::is_constructible<foo, foo&&>::value, " ");

  auto p1 = ss::make_unique<int>(3);
  auto p2 = ss::make_unique<int[]>(3);
//  auto p3 = ss::make_unique<int[4]>(3);

  *p1 = 99;
  p2[1] = 99;

  SS_TEST_RETURN
}
