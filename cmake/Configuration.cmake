# CMake defined modules
include(CheckCXXSymbolExists)

# Custom modules
include(CheckTypeExists)
include(CheckCXXStandardSupport)

macro(CheckArithmeticTypeExists type)
    string(REPLACE " " "_" _name "${type}")
    string(TOUPPER ${_name} _name)
    set(_name SS_HAS_TYPE_${_name})
    CheckTypeExists(${type} "cstdint" ${_name})
    if (${_name})
        target_compile_definitions(ss INTERFACE ${_name}=1)
    else()
        target_compile_definitions(ss INTERFACE ${_name}=0)
    endif ()
endmacro()

set(_types_to_check
    "bool"
    "char"
    "signed char"
    "unsigned char"
    "wchar_t"
    "char8_t"
    "char16_t"
    "char32_t"
    "short"
    "unsigned short"
    "int"
    "unsigned int"
    "long"
    "unsigned long"
    "long long"
    "unsigned long long"
    "float"
    "double"
    "long double"
)

foreach(type ${_types_to_check})
    CheckArithmeticTypeExists(${type})
endforeach()


if ("${CMAKE_CXX_STANDARD}" STREQUAL "")
    CheckCXXStandardSupport(11 SS_COMPILER_SUPPORT_STD_11)
    CheckCXXStandardSupport(14 SS_COMPILER_SUPPORT_STD_14)
    CheckCXXStandardSupport(17 SS_COMPILER_SUPPORT_STD_17)
    CheckCXXStandardSupport(20 SS_COMPILER_SUPPORT_STD_20)
    CheckCXXStandardSupport(23 SS_COMPILER_SUPPORT_STD_23)
else()
    set(SS_COMPILER_SUPPORT_STD_11 0)
    set(SS_COMPILER_SUPPORT_STD_14 0)
    set(SS_COMPILER_SUPPORT_STD_17 0)
    set(SS_COMPILER_SUPPORT_STD_20 0)
    set(SS_COMPILER_SUPPORT_STD_23 0)
    set(SS_COMPILER_SUPPORT_STD_${CMAKE_CXX_STANDARD} 1)
endif ()

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
    message(FATAL_ERROR "Compiler must support C++11")
endif ()

check_cxx_symbol_exists(INFINITY cmath SS_DEFINED_INFINITY)
check_cxx_symbol_exists(NAN cmath SS_DEFINED_NAN)

check_cxx_symbol_exists(DECIMAL_DIG cfloat SS_DEFINED_DECIMAL_DIG)
check_cxx_symbol_exists(FLT_DECIMAL_DIG cfloat SS_DEFINED_FLT_DECIMAL_DIG)
check_cxx_symbol_exists(DBL_DECIMAL_DIG cfloat SS_DEFINED_DBL_DECIMAL_DIG)
check_cxx_symbol_exists(LDBL_DECIMAL_DIG cfloat SS_DEFINED_LDBL_DECIMAL_DIG)

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
