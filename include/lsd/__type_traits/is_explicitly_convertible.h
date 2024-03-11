# /*
#  * Created by YongGyu Lee on 2024/01/10.
#  */
#
# ifndef LSD_TYPE_TRAITS_IS_EXPLICITLY_CONVERTIBLE_HPP
# define LSD_TYPE_TRAITS_IS_EXPLICITLY_CONVERTIBLE_HPP
#
# include <type_traits>
#
# include "lsd/__type_traits/void_t.h"

namespace lsd {

template<typename From, typename To, typename = void>
struct is_explicitly_convertible : std::false_type {};

template<typename From, typename To>
struct is_explicitly_convertible<From, To, void_t<decltype(static_cast<To>(std::declval<From>()))>> : std::true_type {};

} // namespace lsd

# endif // LSD_TYPE_TRAITS_IS_EXPLICITLY_CONVERTIBLE_HPP
