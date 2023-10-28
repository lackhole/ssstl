include(CheckTypeExists)

CheckTypeExists("bool"              "cstdint" SS_HAS_TYPE_BOOL)
CheckTypeExists("char"              "cstdint" SS_HAS_TYPE_CHAR)
CheckTypeExists("signed char"       "cstdint" SS_HAS_TYPE_SIGNED_CHAR)
CheckTypeExists("unsigned char"     "cstdint" SS_HAS_TYPE_UNSIGNED_CHAR)
CheckTypeExists("wchar_t"           "cstdint" SS_HAS_TYPE_WCHAR_T)
CheckTypeExists("char8_t"           "cstdint" SS_HAS_TYPE_CHAR8_T_CXX20 CXX_STANDARD 20)
CheckTypeExists("char16_t"          "cstdint" SS_HAS_TYPE_CHAR16_T)
CheckTypeExists("char32_t"          "cstdint" SS_HAS_TYPE_CHAR32_T)
CheckTypeExists("short"             "cstdint" SS_HAS_TYPE_SHORT)
CheckTypeExists("unsigned short"    "cstdint" SS_HAS_TYPE_UNSIGNED_SHORT)
CheckTypeExists("int"               "cstdint" SS_HAS_TYPE_INT)
CheckTypeExists("unsigned int"      "cstdint" SS_HAS_TYPE_UNSIGNED_INT)
CheckTypeExists("long"              "cstdint" SS_HAS_TYPE_LONG)
CheckTypeExists("unsigned long"     "cstdint" SS_HAS_TYPE_UNSIGNED_LONG)
CheckTypeExists("long long"         "cstdint" SS_HAS_TYPE_LONG_LONG)
CheckTypeExists("unsigned long long" "cstdint" SS_HAS_TYPE_UNSIGNED_LONG_LONG)
CheckTypeExists("float"             "cstdint" SS_HAS_TYPE_FLOAT)
CheckTypeExists("double"            "cstdint" SS_HAS_TYPE_DOUBLE)
CheckTypeExists("long double"       "cstdint" SS_HAS_TYPE_LONG_DOUBLE)
