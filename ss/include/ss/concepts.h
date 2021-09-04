# /*
#  * Created by YongGyu Lee on 2021/07/10.
#  */
#
# ifndef SS_CONCEPTS_H_
# define SS_CONCEPTS_H_
#
# include "ss/type_traits.h"

namespace ss {

// same_as<T, U> subsumes same_as<U, T> and vice versa.
namespace detail {
template<typename T, typename U>
concept same_as_impl = is_same_v<T, U>;
}

/**
 * same_as
 * @tparam T
 * @tparam U
 */
template<typename T, typename U>
concept same_as = detail::same_as_impl<T, U> && detail::same_as_impl<U, T>;


//template<typename T, typename U>
//concept derived_from =

}

# endif // SS_CONCEPTS_H_
