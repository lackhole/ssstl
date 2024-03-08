# /*
#  * Created by YongGyu Lee on 2022/01/21.
#  */
#
# ifndef LSD_DETAIL_ASSERT_H_
# define LSD_DETAIL_ASSERT_H_
# 
# include <cassert>
# 
# define LSD_DEBUG_ASSERT(expr, msg) assert(((void)(msg), (expr)));
# 
# endif // LSD_DETAIL_ASSERT_H_
