#include <iostream>
#include <utility>
#include <string>

#include "ss/utility.h"
#include "ss/type_traits.h"

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
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';



  return 0;
}
