#include <iostream>
#include <utility>
#include <vector>
#include <array>

#include "ss/vector.h"

#include "ss_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif


struct incomplete;

template<>
struct ss::allocator_traits<ss::allocator<incomplete>> : public ss::allocator_traits<ss::allocator<int>> {};

int main() {
  SS_INIT_TEST("vector")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  static_assert(sizeof(int*) == 8, " ");
  
  ss::vector<int> vv;
  
  ss::allocator<int>{}.allocate_at_least(3);

  {
    SS_TESTC(!ss::detail::is_complete<incomplete>::value)
    ss::vector<incomplete> ee;
  }
  


  SS_TEST_RETURN
}
