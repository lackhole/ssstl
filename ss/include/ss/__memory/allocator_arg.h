# /*
#  * Created by YongGyu Lee on 2022/01/16.
#  */
#
# ifndef SS___MEMORY_ALLOCATOR_ARG_H_
# define SS___MEMORY_ALLOCATOR_ARG_H_
#
# include "ss/detail/macro.h"

namespace ss {

struct allocator_arg_t { explicit allocator_arg_t() = default; };

SS_INLINE_VAR constexpr allocator_arg_t allocator_arg = allocator_arg_t();

} // namespace ss

#endif // SS___MEMORY_ALLOCATOR_ARG_H_
