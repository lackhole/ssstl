include(CheckCXXSourceCompiles)
include(CheckCXXStandardSupport)

function(CheckTypeExists type files variable)
    cmake_parse_arguments(ARGS
        ""
        "CXX_STANDARD"
        ""
        ${ARGN}
    )

    set(_files)
    foreach(file ${files})
        SET(_files "${_files}#include <${file}>\n")
    endforeach()

    if (DEFINED ARGS_CXX_STANDARD)
        GetCXXStandardCompilerFlag(${ARGS_CXX_STANDARD} _flag)
        if ("${_flag}")
            set(CMAKE_REQUIRED_FLAGS "${_flag}")
        endif ()
    endif ()

    set(source "
${_files}

union my_union {
  char dummy_;
  ${type} type_;
};

int main() {
  my_union my_u;
  return 0;
}")
    check_cxx_source_compiles("${source}" ${variable})
endfunction()
