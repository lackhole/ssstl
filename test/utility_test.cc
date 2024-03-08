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

  { // move
    std::string str = "hello, world!";
    std::string str2;
    str2 = lsd::move(str);

    LSD_TEST(str.empty())
    LSD_TEST(str2 == "hello, world!")
  }

  {
    constexpr lsd::pair<int, float> p1(1, 2);

    LSD_TESTC(lsd::get<0>(p1) == 1)
    LSD_TESTC(lsd::get<int>(p1) == 1)
    LSD_TESTC(lsd::get<1>(p1) == 2)
    LSD_TESTC(lsd::get<float>(p1) == 2)
  }


  LSD_TEST_RETURN
}
