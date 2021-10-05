#include <iostream>
#include <utility>
#include <string>

#include "ss/utility.h"
#include "ss/type_traits.h"

#include "ss_test.h"
#include "test_utils.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif

template<typename T>
T test_forward(T&& obj) { return ss::forward<T>(obj); }

int main() {
  SS_INIT_TEST("utility")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  { // swap
    int x = 1, y = 2;
    SS_TEST(x == 1 && y == 2)
    ss::swap(x, y);
    SS_TEST(x == 2 && y == 1)

    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    ss::swap(arr1, arr2);
    SS_TEST(arr1[0] == 4 && arr1[1] == 5 && arr1[2] == 6)
    SS_TEST(arr2[0] == 1 && arr2[1] == 2 && arr2[2] == 3)

    using type = ss::with_member<std::string>;
    type a = "hello";
    type b;

    ss::swap(a, b);
    SS_TEST(a.member == "" && b.member == "hello")
  }

  { // exchange
    int x = 1;
    auto y = ss::exchange(x, 3);
    SS_TEST(y == 1 && x == 3)

    std::string str1 = "hello";
    std::string str2 = "world";

    auto str = ss::exchange(str1, str2);
    SS_TEST(str == "hello" && str1 == "world" && str2 == "world")
    ss::exchange(str1, ss::move(str2));
    SS_TEST(str1 == "world" && str2 == "")
  }

  { // forward
    std::string str = "hello";
    auto str2 = test_forward(str);
    SS_TEST(str2 == "hello" && str == "hello")

    str2 = test_forward(move(str));
    SS_TEST(str2 == "hello" && str == "")
  }

  { // move
    int x = 3;
    int y = ss::move(x);



  }

  {


    struct empty{};
//    constexpr ss::compressed_pair<int, empty> cp{};

    constexpr int x{};
  }


  SS_TEST_RETURN
}
