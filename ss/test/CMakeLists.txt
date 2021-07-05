cmake_minimum_required(VERSION 3.15)
project(ss_test)

set(CMAKE_CXX_STANDARD 14)

add_executable(ss_test ss_test.cc)
target_link_libraries(ss_test PUBLIC ss)
