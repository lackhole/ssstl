#include <iostream>
#include <utility>
#include <vector>
#include <array>

#include "lsd/vector.h"

#include "lsd_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif


struct incomplete;

template<>
struct lsd::allocator_traits<lsd::allocator<incomplete>> : public lsd::allocator_traits<lsd::allocator<int>> {};

int main() {
  LSD_INIT_TEST("vector")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  
  lsd::vector<int> vv;

  {
    LSD_TESTC(!lsd::detail::is_complete<incomplete>::value)
    lsd::vector<incomplete> ee;
  }
  


  LSD_TEST_RETURN
}
