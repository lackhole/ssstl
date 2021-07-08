cmake_minimum_required(VERSION 3.10)

# C++11
add_test(NAME type_traits_test_cxx11 COMMAND type_traits_test_cxx11)
add_executable(type_traits_test_cxx11 test.cc)
#set_property(TARGET type_traits_test_cxx11 PROPERTY CXX_STANDARD 11)
target_link_libraries(type_traits_test_cxx11 PUBLIC ss)


## C++14
#add_test(NAME type_traits_test_cxx14 COMMAND type_traits_test_cxx14)
#add_executable(type_traits_test_cxx14 test.cc)
#set_property(TARGET type_traits_test_cxx14 PROPERTY CXX_STANDARD 14)
#target_link_libraries(type_traits_test_cxx14 PUBLIC ss)
#
#
## C++17
#add_test(NAME type_traits_test_cxx17 COMMAND type_traits_test_cxx17)
#add_executable(type_traits_test_cxx17 test.cc)
#set_property(TARGET type_traits_test_cxx17 PROPERTY CXX_STANDARD 17)
#target_link_libraries(type_traits_test_cxx17 PUBLIC ss)
#
#
## C++20
#add_test(NAME type_traits_test_cxx20 COMMAND type_traits_test_cxx20)
#add_executable(type_traits_test_cxx20 test.cc)
#set_property(TARGET type_traits_test_cxx20 PROPERTY CXX_STANDARD 20)
#target_link_libraries(type_traits_test_cxx20 PUBLIC ss)
