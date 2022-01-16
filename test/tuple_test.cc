#include <iostream>
#include <utility>
#include <string>
#include <tuple>

#include "ss/tuple.h"

#include "ss_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif



int main() {
  SS_INIT_TEST("tuple")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  {
    ss::tuple<int, int, int, int> t1;
    ss::tuple<float, float, float, float> t2(t1);

    auto t3 = t1;

    static_assert(ss::is_same<int, ss::tuple_element_t<2, decltype(t1)>>::value, " ");
  }

  {
    ss::tuple<int, char> t;
    ss::pair<float, std::string> p = {1, "hello"};


    std::cout << p.second << std::endl;
    const auto c = ss::tuple_cat(t, p);

    std::cout << p.second << std::endl;
    std::cout << ss::get<std::string>(c) << std::endl;

    struct no_copy_assign {
      no_copy_assign() = default;
      no_copy_assign& operator=(const no_copy_assign&) = delete;
      no_copy_assign& operator=(no_copy_assign&&) = default;
    };

    std::pair<int, no_copy_assign> t2;
    ss::tuple<int, no_copy_assign> t3;

//    auto pp = std::move(t2);

//    static_assert(ss::is_copy_assignable_v<no_copy_assign>, " ");
//
//    t3 = ss::move(t2);

    ss::tuple<std::string> a, b;
    b = a;

    ss::tuple_cat();
  }

  SS_TEST_RETURN
}
