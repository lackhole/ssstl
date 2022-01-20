# /*
#  * Created by YongGyu Lee on 2022/01/21.
#  */
#
# ifndef SS_DETAIL_ASSERT_H_
# define SS_DETAIL_ASSERT_H_
# 
# include <cassert>
# 
# define SS_DEBUG_ASSERT(expr, msg) assert(((void)(msg), (expr)));
# 
# endif // SS_DETAIL_ASSERT_H_
