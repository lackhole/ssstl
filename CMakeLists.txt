cmake_minimum_required(VERSION 3.11)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

project(lsd CXX)
include(Configuration)

set(LSD_INCLUDE_DIR "${CMAKE_CURRENT_LIST_DIR}/include")
set(LSD_BINARY_DIR "${PROJECT_BINARY_DIR}")

add_library(lsd INTERFACE)
target_include_directories(lsd INTERFACE "${LSD_INCLUDE_DIR}")

if (MSVC)
    target_compile_options(lsd INTERFACE /Zc:__cplusplus)
    target_compile_options(lsd INTERFACE /Zc:ternary)
    target_compile_options(lsd INTERFACE /permissive-)
endif ()

option(LSD_TEST "Build test" OFF)

if (LSD_TEST)
    enable_testing()
    add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/test)
endif()

option(LSD_GENERATE_DOCS "Generate status documents" OFF)

if (LSD_GENERATE_DOCS)
    add_subdirectory(tools/generate_doc)
endif()
