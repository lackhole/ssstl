# /*
#  * Created by YongGyu Lee on 2022/01/16.
#  */
#
# ifndef LSD_DETAIL_USES_ALLOCATOR_H_
# define LSD_DETAIL_USES_ALLOCATOR_H_
#
# include "lsd/__core/macro.h"
# include "lsd/experimental/utility.h"
# include "lsd/type_traits.h"

namespace lsd {
namespace detail {

template<typename T, typename = void>
struct has_allocator_type : false_type {};

template<typename T>
struct has_allocator_type<T, void_t<typename T::allocator_type>> : true_type {};

template<typename T, typename Alloc, bool v = has_allocator_type<T>::value>
struct uses_allocator_impl : false_type {};

template<typename T, typename Alloc>
struct uses_allocator_impl<T, Alloc, true> : is_convertible<Alloc, typename T::allocator_type> {};

template<typename Alloc>
struct uses_allocator_impl<lsd::experimental::erased_type, Alloc, true> : true_type {};

} // namespace detail

/**
 * uses_allocator
 */
template<typename T, typename Alloc>
struct uses_allocator : detail::uses_allocator_impl<T, Alloc> {};

# if LSD_CXX_VER >= 14
template<typename T, typename Alloc> LSD_INLINE_VAR constexpr bool uses_allocator_v = uses_allocator<T, Alloc>::value;
# endif

} // namespace lsd

# endif // LSD_DETAIL_USES_ALLOCATOR_H_
