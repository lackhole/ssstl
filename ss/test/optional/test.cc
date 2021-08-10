#include <iostream>

#include "ss/optional.h"


# if SS_CXX_VER >= 17
#include <optional>
# endif

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif

struct bar {
  bar(int) {}
//  bar(bar const&) {}
  bar(bar&&) {std::cout << "Move Ctor\n";}
  bar& operator=(bar&&) {std::cout << "Move Asgn\n"; return *this;}
//  bar& operator=(bar const&) {std::cout << "Copy Asgn\n"; return *this;}
  ~bar() noexcept {}
};

int main() {
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  {
    struct foo {};
    ss::optional<foo> o;
    o.emplace();

    std::optional<foo> op;
    op.emplace();
  }

  {
    ss::optional<bar> o1 = 1;
    ss::optional<bar> o3(ss::move(o1));
//    o3 = o1;

//    std::optional<bar> o2;
//    o2.emplace();
  }


  std::cout << __cplusplus << std::endl;

  return 0;
}
