#include <iostream>
#include <utility>
#include <string>

#include "ss/utility.h"
#include "ss/type_traits.h"

#include "ss_test.h"

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
  SS_INIT_TEST("utility")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  { // move
    std::string str = "hello, world!";
    std::string str2;
    str2 = ss::move(str);

    SS_TEST(str.empty())
    SS_TEST(str2 == "hello, world!")
  }

  {
    constexpr ss::pair<int, float> p1(1, 2);

    SS_TESTC(ss::get<0>(p1) == 1)
    SS_TESTC(ss::get<int>(p1) == 1)
    SS_TESTC(ss::get<1>(p1) == 2)
    SS_TESTC(ss::get<float>(p1) == 2)
  }


  return 0;
}
