cmake_minimum_required(VERSION 3.15)
project(ss)
add_library(ss INTERFACE)

set(SS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ss)
set(SS_INCLUDE_DIR ${SS_DIR}/include)

target_include_directories(ss INTERFACE
        ${SS_INCLUDE_DIR})

option(SS_TEST "Run test" OFF)
option(SS_TEST_MATRIX "If running in github workflow with matrix" OFF)

if (MSVC)
    target_compile_options(ss INTERFACE "/Zc:__cplusplus")
endif()

if (SS_TEST)
    enable_testing()
    add_subdirectory(${SS_DIR}/test)
endif()
