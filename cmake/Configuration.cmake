# CMake defined modules
include(CheckCXXSymbolExists)

# Custom modules
include(CheckTypeExists)
include(CheckCXXStandardSupport)
include(CheckCXX_TypeExists)
include(CheckCXX_InitializerListExists)

CheckCXXStandardSupport(11 SS_COMPILER_SUPPORT_STD_11)
CheckCXXStandardSupport(14 SS_COMPILER_SUPPORT_STD_14)
CheckCXXStandardSupport(17 SS_COMPILER_SUPPORT_STD_17)
CheckCXXStandardSupport(20 SS_COMPILER_SUPPORT_STD_20)
CheckCXXStandardSupport(23 SS_COMPILER_SUPPORT_STD_23)

if(SS_COMPILER_SUPPORT_STD_23)
    set(SS_COMPILER_SUPPORT_STD 23)
elseif(SS_COMPILER_SUPPORT_STD_20)
    set(SS_COMPILER_SUPPORT_STD 20)
elseif(SS_COMPILER_SUPPORT_STD_17)
    set(SS_COMPILER_SUPPORT_STD 17)
elseif(SS_COMPILER_SUPPORT_STD_14)
    set(SS_COMPILER_SUPPORT_STD 14)
elseif(SS_COMPILER_SUPPORT_STD_11)
    set(SS_COMPILER_SUPPORT_STD 11)
else()
    message(FATAL_ERROR "Compiler must support C++11 at least")
endif ()

# Generate config header
set(SS_GENERATED_DIR "${SS_BINARY_DIR}/generated")
set(SS_GENERATED_INCLUDE_DIR "${SS_GENERATED_DIR}/include")

if (NOT EXISTS "${SS_GENERATED_INCLUDE_DIR}/ss")
    file(MAKE_DIRECTORY "${SS_GENERATED_INCLUDE_DIR}/ss")
endif ()

configure_file(
    "${SS_INCLUDE_DIR}/ss/__config.cmake.in"
    "${SS_GENERATED_INCLUDE_DIR}/ss/__config.h"
)

target_include_directories(ss INTERFACE "${SS_GENERATED_INCLUDE_DIR}")
