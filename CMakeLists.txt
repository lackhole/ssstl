cmake_minimum_required(VERSION 3.15)
project(ss)
add_library(ss INTERFACE)

set(SS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ss)
set(SS_INCLUDE_DIR ${SS_DIR}/include)

target_include_directories(ss INTERFACE
        ${SS_INCLUDE_DIR})

option(SS_TEST "Run test" ON)

if (MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus")
endif()

if (SS_TEST)
    enable_testing()
    add_subdirectory(${SS_DIR}/test)
endif()
