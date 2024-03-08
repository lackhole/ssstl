#include <iostream>

#include "lsd/optional.h"


# if LSD_CXX_VER >= 17
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
    lsd::optional<foo> o;
    o.emplace();

# if LSD_CXX_VER >= 17
    std::optional<foo> op;
    op.emplace();
# endif
  }

  {
    lsd::optional<bar> o1 = 1;
    lsd::optional<bar> o3(lsd::move(o1));
//    o3 = o1;

//    std::optional<bar> o2;
//    o2.emplace();
  }

  {
    struct NoMove {
      NoMove() = default;
      NoMove(const NoMove&) {
        std::cout << "COPY SELECTED\n";
      }
      NoMove(NoMove&&) = delete;
      NoMove& operator=(const NoMove&) = default;
    };

    lsd::optional<NoMove> op1{lsd::in_place};
    lsd::optional<NoMove> op2;
    std::swap(op1, op2); // copy is selected for non-movable object
  }


  std::cout << __cplusplus << std::endl;

  return 0;
}
