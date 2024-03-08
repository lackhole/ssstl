# /*
#  * Created by YongGyu Lee on 2022/01/16.
#  */
#
# ifndef LSD___MEMORY_ALLOCATOR_ARG_H_
# define LSD___MEMORY_ALLOCATOR_ARG_H_
#
# include "lsd/__core/macro.h"

namespace lsd {

struct allocator_arg_t { explicit allocator_arg_t() = default; };

LSD_INLINE_VAR constexpr allocator_arg_t allocator_arg = allocator_arg_t();

} // namespace lsd

#endif // LSD___MEMORY_ALLOCATOR_ARG_H_
