//
// Created by YongGyu Lee on 2021/10/05.
//

#include <functional>
#include <iostream>
#include <type_traits>

#include "ss/functional.h"

#include "ss_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif

struct A {
  A(int) {}
};

int meow(ss::reference_wrapper<int>); //#1
void meow(A); //#2

int main() {
  SS_INIT_TEST("functional")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';


  { // reference_wrapper

    // test unambiguous
    using test = decltype(meow(0));


    int x = 10;
    int y = 20;

    ss::reference_wrapper<int> a(x);
    ss::reference_wrapper<int> b(y);

    SS_TEST(a == 10)
    SS_TEST(b == 20)

    a = b;
    SS_TEST(a == 10)

    a = move(b);


  }

  return 0;
}
