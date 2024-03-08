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

int meow(lsd::reference_wrapper<int>); //#1
void meow(A); //#2

int main() {
  LSD_INIT_TEST("functional")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';


  { // reference_wrapper

    // test unambiguous
    using test = decltype(meow(0));


    int x = 10;
    int y = 20;

    lsd::reference_wrapper<int> a(x);
    lsd::reference_wrapper<int> b(y);

    LSD_TEST(a == 10)
    LSD_TEST(b == 20)

    a = b;
    LSD_TEST(a == 20)

    a = move(b);


  }

  LSD_TEST_RETURN
}
