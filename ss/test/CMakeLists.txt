cmake_minimum_required(VERSION 3.15)

set(CMAKE_CXX_STANDARD 14)

add_test(NAME ss_test COMMAND ss_test)
add_executable(ss_test ss_test.cc)
target_link_libraries(ss_test PUBLIC ss)
