# /*
#  * Created by YongGyu Lee on 2021/06/25.
#  */
#
# ifndef LSD_DETAIL_MACRO_H_
# define LSD_DETAIL_MACRO_H_
#
# if __cplusplus >= 202300L
#   define LSD_CXX_VER 23
# elif __cplusplus >= 202002L
#   define LSD_CXX_VER 20
# elif __cplusplus >= 201703L
#   define LSD_CXX_VER 17
# elif __cplusplus >= 201402L
#   define LSD_CXX_VER 14
# elif __cplusplus == 201103L
#   define LSD_CXX_VER 11
# else
#   error "C++11 is required at least"
# endif

# /** likely */
# /* Apple clang doens't supports [[likely]] and [[unlikely]]. Work needed later */

# /** nodiscard */
# if LSD_CXX_VER >= 17
#   define LSD_NODISCARD [[nodiscard]]
# else
#   define LSD_NODISCARD
# endif

# /** inline */
# if LSD_CXX_VER >= 17
#   define LSD_INLINE_VAR inline
# else
#   define LSD_INLINE_VAR
# endif

# /** maybe_unused */
# if LSD_CXX_VER >= 17
#   define LSD_MAYBE_UNUSED [[maybe_unused]]
# else
#   define LSD_MAYBE_UNUSED
# endif

# if LSD_CXX_VER >= 14
#   define LSD_CONSTEXPR_AFTER_14 constexpr
# else
#   define LSD_CONSTEXPR_AFTER_14
# endif

# if LSD_CXX_VER >= 23
#   define LSD_AFTER_CXX23(...) __VA_ARGS__
# else
#   define LSD_AFTER_CXX23(...)
# endif

# if LSD_CXX_VER >= 20
#   define LSD_AFTER_CXX20(...) __VA_ARGS__
# else
#   define LSD_AFTER_CXX20(...)
# endif

# if LSD_CXX_VER >= 17
#   define LSD_AFTER_CXX17(...) __VA_ARGS__
# else
#   define LSD_AFTER_CXX17(...)
# endif

# if LSD_CXX_VER >= 14
#   define LSD_AFTER_CXX14(...) __VA_ARGS__
# else
#   define LSD_AFTER_CXX14(...)
# endif

#endif // LSD_DETAIL_MACRO_H_
