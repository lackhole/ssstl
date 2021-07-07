# /*
#  * Created by YongGyu Lee on 2021/06/25.
#  */
#
# ifndef SS_DETAIL_MACRO_H_
# define SS_DETAIL_MACRO_H_
#
# if __cplusplus > 202300L
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

# /** likely */
# /* Apple clang doens't supports [[likely]] and [[unlikely]]. Work needed later */

# /** nodiscard */
# if SS_CXX_VER >= 17
#   define SS_NODISCARD [[nodiscard]]
# else
#   define SS_NODISCARD
# endif

# /** inline */
# if SS_CXX_VER >= 17
#   define SS_INLINE_VAR inline
# else
#   define SS_INLINE_VAR
# endif

# /** maybe_unused */
# if SS_CXX_VER >= 17
#   define SS_MAYBE_UNUSED [[maybe_unused]]
# else
#   define SS_MAYBE_UNUSED
# endif

# if SS_CXX_VER >= 23
#   define SS_AFTER_CXX23(...) __VA_ARGS__
# else
#   define SS_AFTER_CXX23(...)
# endif

# if SS_CXX_VER >= 20
#   define SS_AFTER_CXX20(...) __VA_ARGS__
# else
#   define SS_AFTER_CXX20(...)
# endif

# if SS_CXX_VER >= 17
#   define SS_AFTER_CXX17(...) __VA_ARGS__
# else
#   define SS_AFTER_CXX17(...)
# endif

# if SS_CXX_VER >= 14
#   define SS_AFTER_CXX14(...) __VA_ARGS__
# else
#   define SS_AFTER_CXX14(...)
# endif

#endif // SS_DETAIL_MACRO_H_