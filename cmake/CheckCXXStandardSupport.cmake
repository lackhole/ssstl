include(CheckCXXSourceCompiles)
include(CheckCXXCompilerFlag)

function(GetCXXStandardCompilerFlag version out_var)
    if(MSVC)
        set(_flag_prefix "/std:c++")
    else()
        set(_flag_prefix "-std=c++")
    endif()

    set(_flag "${_flag_prefix}${version}")

    check_cxx_compiler_flag(${_flag} __${out_var}_FLAG)
    if ("${__${out_var}_FLAG}")
        set(${out_var} ${_flag} PARENT_SCOPE)
        return()
    endif ()

    if (MSVC AND version EQUAL 11)
        CheckCXXStandardSupport(14 __${out_var}_FLAG_STD_MSCV_OVERRIDE_14)
        if (${__${out_var}_FLAG_STD_MSCV_OVERRIDE_14})
            set(${out_var} ${__${out_var}_FLAG_STD_MSCV_OVERRIDE_14} PARENT_SCOPE)
            return()
        endif ()
    endif()

    message(FATAL_ERROR "Cannot find a compiler flag for C++ ${version}")
endfunction(GetCXXStandardCompilerFlag)

# TODO: Integrate
function(CheckCXXStandardSupport version variable)
    if(MSVC)
        set(CMAKE_REQUIRED_FLAGS "/Zc:__cplusplus")
        set(_std_version_flag "/std:c++${version}")
    else()
        set(_std_version_flag "-std=c++${version}")
    endif()

    check_cxx_compiler_flag(${_std_version_flag} __${variable}_FLAG)
    if (NOT "${__${variable}_FLAG}")
        if (MSVC AND version EQUAL 11)
            CheckCXXStandardSupport(14 __${variable}_FLAG_STD_MSCV_OVERRIDE_14)
            if (${__${variable}_FLAG_STD_MSCV_OVERRIDE_14})
                set(${variable} 1 PARENT_SCOPE)
                return()
            endif ()
        endif()
        set(${variable} 0 PARENT_SCOPE)
        return()
    endif()

    set(_cplusplus_11 "201103L")
    set(_cplusplus_14 "201402L")
    set(_cplusplus_17 "201703L")
    set(_cplusplus_20 "202002L")
    set(_cplusplus_23 "202302L")

    if (NOT "${version}" MATCHES "^(11|14|17|20|23)$")
        message(FATAL_ERROR "Undetermined C++ standard: ${version}")
    endif()

    set(CMAKE_REQUIRED_FLAGS "${_std_version_flag}")
    if (MSVC)
        set(CMAKE_REQUIRED_FLAGS "${CMAKE_REQUIRED_FLAGS} /Zc:__cplusplus")
    endif()
    set(_source "
#if __cplusplus < ${_cplusplus_${version}}
#error 1
#endif
int main() { return 0; }")
    check_cxx_source_compiles("${_source}" ${variable})
endfunction()



