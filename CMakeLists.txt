cmake_minimum_required(VERSION 3.15)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(ss CXX)
add_library(ss INTERFACE)

set(SS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/ss)
set(SS_INCLUDE_DIR ${SS_DIR}/include)
set(SS_BINARY_DIR "${PROJECT_BINARY_DIR}")

include(Configuration)

target_include_directories(ss INTERFACE ${SS_INCLUDE_DIR})

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(ss INTERFACE -fconcepts)
elseif (MSVC)
    target_compile_options(ss INTERFACE /Zc:__cplusplus)
    target_compile_options(ss INTERFACE /Zc:ternary)
    target_compile_options(ss INTERFACE /permissive-)
endif ()

option(SS_TEST "Run test" OFF)
option(SS_TEST_MATRIX "If running in github workflow with matrix" OFF)

if (SS_TEST)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/test)
endif()

option(SS_GENERATE_DOCS "Generate status documents" OFF)

if (SS_GENERATE_DOCS)
    add_subdirectory(tools/generate_doc)
endif()
