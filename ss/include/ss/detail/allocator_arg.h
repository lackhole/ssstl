# /*
#  * Created by YongGyu Lee on 2022/01/16.
#  */
#
# ifndef SS_DETAIL_ALLOCATOR_ARG_H_
# define SS_DETAIL_ALLOCATOR_ARG_H_
#
# include "ss/detail/macro.h"

namespace ss {

/**
 * allocator_arg_t
 */
struct allocator_arg_t { explicit allocator_arg_t() = default; };

SS_INLINE_VAR constexpr allocator_arg_t allocator_arg = allocator_arg_t();

} // namespace ss

#endif // SS_DETAIL_ALLOCATOR_ARG_H_
