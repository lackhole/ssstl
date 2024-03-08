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

  {
    lsd::tuple<int, int, int, int> t1;
    lsd::tuple<float, float, float, float> t2(t1);

    auto t3 = t1;

    static_assert(lsd::is_same<int, lsd::tuple_element_t<2, decltype(t1)>>::value, " ");
  }

  {
    lsd::tuple<int, char> t;
    lsd::pair<float, std::string> p = {1, "hello"};


    std::cout << p.second << std::endl;
    const auto c = lsd::tuple_cat(t, p);

    std::cout << p.second << std::endl;
    std::cout << lsd::get<std::string>(c) << std::endl;

    struct no_copy_assign {
      no_copy_assign() = default;
      no_copy_assign& operator=(const no_copy_assign&) = delete;
      no_copy_assign& operator=(no_copy_assign&&) = default;
    };

    std::pair<int, no_copy_assign> t2;
    lsd::tuple<int, no_copy_assign> t3;

//    auto pp = std::move(t2);

//    static_assert(lsd::is_copy_assignable_v<no_copy_assign>, " ");
//
//    t3 = lsd::move(t2);

    lsd::tuple<std::string> a, b;
    b = a;

    lsd::tuple_cat();
  }

  LSD_TEST_RETURN
}
