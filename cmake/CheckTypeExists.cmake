include(CheckCXXSourceCompiles)

function(CheckTypeExists type files variable)
    set(_files)
    foreach(file ${files})
        SET(_files "${_files}#include <${file}>\n")
    endforeach()

    set(source "
${_files}
int main() {
  static ${type} tmp;
  if (sizeof(tmp))
    return 0;
  return 0;
}")
    check_cxx_source_compiles("${source}" ${variable})
endfunction()
