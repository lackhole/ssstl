#include <iostream>
#include <utility>
#include <string>

#include "lsd/utility.h"
#include "lsd/type_traits.h"

#include "lsd_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif


struct foo {
  explicit foo(int x = 0) {}
  std::string str = "hello";
};
void test(const foo&);

int main() {
  LSD_INIT_TEST("utility")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';



  LSD_TEST_RETURN
}
