# /*
#  * Created by YongGyu Lee on 2021/09/03.
#  */
#
# ifndef LSD_TYPE_TRAITS_BOOL_CONSTANT_HPP
# define LSD_TYPE_TRAITS_BOOL_CONSTANT_HPP
# 
# include <type_traits>

namespace lsd {

template<bool v>
using bool_constant = std::integral_constant<bool, v>;

template<typename ...> struct always_false : std::false_type {};
template<typename ...> struct always_true : std::true_type {};

} // namespace lsd

# endif // LSD_TYPE_TRAITS_BOOL_CONSTANT_HPP
