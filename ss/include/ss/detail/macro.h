# /*
#  * Created by YongGyu Lee on 2021/06/25.
#  */
#
# ifndef SS_DETAIL_MACRO_H_
# define SS_DETAIL_MACRO_H_
#
# if __cplusplus > 202002L
#   define SS_CXX_VER 23
# elif __cplusplus > 201703L
#   define SS_CXX_VER 20
# elif __cplusplus > 201402L
#   define SS_CXX_VER 17
# elif __cplusplus > 201103L
#   define SS_CXX_VER 14
# elif __cplusplus == 201103L
#   define SS_CXX_VER 11
# else
#   error "C++11 is required at least"
# endif

# if SS_CXX_VER >= 17
#   define SS_NODISCARD [[nodiscard]]
# else
#   define SS_NODISCARD
# endif

# if SS_CXX_VER >= 17
#   define SS_INLINE_VAR inline
# else
#   define SS_INLINE_VAR
# endif



#endif // SS_DETAIL_MACRO_H_