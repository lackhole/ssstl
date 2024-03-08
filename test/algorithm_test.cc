#include <iostream>
#include <algorithm>

#include "lsd/array.h"
#include "lsd/algorithm.h"
#include "lsd/initializer_list.h"

#include "lsd_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif



int main() {
  LSD_INIT_TEST("algorithm")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  { // min, max, minmax
    LSD_TESTC(lsd::min(1, 2) == 1)
    LSD_TESTC(lsd::max(1, 2) == 2)
    LSD_TESTC(lsd::minmax(1, 2).first == 1)
    LSD_TESTC(lsd::minmax(1, 2).second == 2)
    LSD_TESTC(lsd::minmax(1, 2) == lsd::minmax(2, 1))
    
    std::initializer_list<int> ilist = {2,4,1,5,3};
    
    LSD_TEST(lsd::min(ilist) == 1)
    LSD_TEST(lsd::max(ilist) == 5)
    
    auto p = lsd::minmax(ilist);
    LSD_TEST(p.first == 1)
    LSD_TEST(p.second == 5)
  }

  { // [min, max, minmax]_element
    constexpr lsd::array<int, 10> arr = {2,2,1,1,1,5,5,5,4,4};
    
    LSD_TEST(lsd::min_element(arr.begin(), arr.end()) == arr.begin() + 2)
    LSD_TEST(lsd::max_element(arr.begin(), arr.end()) == arr.begin() + 5)
    
    auto p = lsd::minmax_element(arr.begin(), arr.end());
    LSD_TEST(p.first == arr.begin() + 2)
    LSD_TEST(p.second == arr.begin() + 7)
    LSD_TEST(p.second != lsd::max_element(arr.begin(), arr.end()))
  }
  
//  std::minmax(1, 2);
  
  LSD_TEST_RETURN
}
