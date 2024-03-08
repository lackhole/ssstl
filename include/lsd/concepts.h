# /*
#  * Created by YongGyu Lee on 2021/07/10.
#  */
#
# ifndef LSD_CONCEPTS_H_
# define LSD_CONCEPTS_H_
#
# include "lsd/__core/macro.h"
# include "lsd/type_traits.h"

# if LSD_CXX_VER >= 20

namespace lsd {

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



/**
 * derived_from
 * @tparam Derived
 * @tparam Base
 */
template<typename Derived, typename Base>
concept derived_from = is_public_base_of_v<Base, Derived>;



//template<typename From, typename To>
//concept convertible_to = is_convertible_v<From, To>;


}

# endif

# endif // LSD_CONCEPTS_H_
