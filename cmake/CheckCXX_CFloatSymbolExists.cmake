include(CheckCXXSymbolExists)

check_cxx_symbol_exists(DECIMAL_DIG cfloat SS_DEFINED_DECIMAL_DIG)
check_cxx_symbol_exists(FLT_DECIMAL_DIG cfloat SS_DEFINED_FLT_DECIMAL_DIG)
check_cxx_symbol_exists(DBL_DECIMAL_DIG cfloat SS_DEFINED_DBL_DECIMAL_DIG)
check_cxx_symbol_exists(LDBL_DECIMAL_DIG cfloat SS_DEFINED_LDBL_DECIMAL_DIG)