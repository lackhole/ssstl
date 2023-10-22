include(CheckCXXStandardSupport)

GetCXXStandardCompilerFlag(11 SS_CPP_11_FLAG)
set(CMAKE_REQUIRED_FLAGS "${SS_CPP_11_FLAG}")
check_cxx_source_compiles("
#include <initializer_list>

int main() {
  std::initializer_list<int> il = {1, 2, 3};

  return 0;
}
" SS_HAS_INITIALIZER_LIST)
