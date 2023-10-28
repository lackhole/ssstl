include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)

function(_GetCXXStandardCompilerFlagPrefix out_var)
    if(MSVC)
        set(${out_var} "/std:c++" PARENT_SCOPE)
    else()
        set(${out_var} "-std=c++" PARENT_SCOPE)
    endif()
endfunction()

_GetCXXStandardCompilerFlagPrefix(_flag_prefix)
set(__SS_STD_CXX_COMPILER_FLAG_PREFIX "${_flag_prefix}" CACHE STRING "Prefix compiler flag for C++ standard")

check_cxx_compiler_flag("${__SS_STD_CXX_COMPILER_FLAG_PREFIX}11" __SS_COMPILE_TEST_STD_CXX_11)
check_cxx_compiler_flag("${__SS_STD_CXX_COMPILER_FLAG_PREFIX}14" __SS_COMPILE_TEST_STD_CXX_14)
check_cxx_compiler_flag("${__SS_STD_CXX_COMPILER_FLAG_PREFIX}17" __SS_COMPILE_TEST_STD_CXX_17)
check_cxx_compiler_flag("${__SS_STD_CXX_COMPILER_FLAG_PREFIX}20" __SS_COMPILE_TEST_STD_CXX_20)
check_cxx_compiler_flag("${__SS_STD_CXX_COMPILER_FLAG_PREFIX}23" __SS_COMPILE_TEST_STD_CXX_23)
check_cxx_compiler_flag("${__SS_STD_CXX_COMPILER_FLAG_PREFIX}26" __SS_COMPILE_TEST_STD_CXX_26)

function(GetCXXStandardCompilerFlag version out_var)
    if ("${__SS_COMPILE_TEST_STD_CXX_${version}}")
        set(${out_var} "${__SS_STD_CXX_COMPILER_FLAG_PREFIX}${version}" PARENT_SCOPE)
        return()
    endif ()

    # Override to 14
    if (MSVC AND version EQUAL 11)
        GetCXXStandardCompilerFlag(14 ${out_var})
        return()
    endif()

    set(${out_var} PARENT_SCOPE)
endfunction(GetCXXStandardCompilerFlag)

# TODO: Integrate
function(CheckCXXStandardSupport version variable)
    if (NOT "${version}" MATCHES "^(11|14|17|20|23)$")
        message(FATAL_ERROR "Undetermined C++ standard: ${version}")
    endif()

    GetCXXStandardCompilerFlag(${version} _flag)
    if (${_flag})
        set(${variable} 1 PARENT_SCOPE)
        return()
    endif()

    set(_cplusplus_11 "201103L")
    set(_cplusplus_14 "201402L")
    set(_cplusplus_17 "201703L")
    set(_cplusplus_20 "202002L")
    set(_cplusplus_23 "202302L")

    if (MSVC)
        set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} /Zc:__cplusplus")
    endif()
    set(_source "
#if __cplusplus < ${_cplusplus_${version}}
#error 1
#endif
int main() { return 0; }")
    check_cxx_source_compiles("${_source}" __SS_COMPILE_TEST_CPLUSPLUS_${version})
    set(${variable} ${__SS_COMPILE_TEST_CPLUSPLUS_${version}} PARENT_SCOPE)
endfunction()



