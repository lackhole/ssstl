#include <iostream>
#include <initializer_list>
#include <algorithm>

#include "ss/array.h"
#include "ss/algorithm.h"

#include "ss_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif



int main() {
  SS_INIT_TEST("algorithm")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  { // min, max, minmax
    SS_TESTC(ss::min(1, 2) == 1)
    SS_TESTC(ss::max(1, 2) == 2)
    SS_TESTC(ss::minmax(1, 2).first == 1)
    SS_TESTC(ss::minmax(1, 2).second == 2)
    SS_TESTC(ss::minmax(1, 2) == ss::minmax(2, 1))

    // TODO: Find out why GCC 9.3.0 fails to compile in C++11
    // https://github.com/lackhole/ssstl/runs/5006370185?check_suite_focus=true#step:4:17
# if SS_CXX_VER > 11
    auto ilist = {2,4,1,5,3};
    
    SS_TEST(ss::min(ilist) == 1)
    SS_TEST(ss::max(ilist) == 5)
    
    auto p = ss::minmax(ilist);
    SS_TEST(p.first == 1)
    SS_TEST(p.second == 5)
# endif
  }

  { // [min, max, minmax]_element
    constexpr ss::array<int, 10> arr = {2,2,1,1,1,5,5,5,4,4};
    
    SS_TEST(ss::min_element(arr.begin(), arr.end()) == arr.begin() + 2)
    SS_TEST(ss::max_element(arr.begin(), arr.end()) == arr.begin() + 5)
    
    auto p = ss::minmax_element(arr.begin(), arr.end());
    SS_TEST(p.first == arr.begin() + 2)
    SS_TEST(p.second == arr.begin() + 7)
    SS_TEST(p.second != ss::max_element(arr.begin(), arr.end()))
  }
  
//  std::minmax(1, 2);
  
  SS_TEST_RETURN
}
