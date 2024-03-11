# /*
#  * Created by YongGyu Lee on 2021/09/03.
#  */
#
# ifndef LSD_TYPE_TRAITS_DISJUNCTION_HPP
# define LSD_TYPE_TRAITS_DISJUNCTION_HPP
#
# include <type_traits>

namespace lsd {

template<typename ...B>
struct disjunction;

template<>
struct disjunction<> : std::false_type {};

template<typename B1>
struct disjunction<B1> : B1 {};

template<typename B1, typename ...BN>
struct disjunction<B1, BN...> : std::conditional_t<bool(B1::value), B1, disjunction<BN...>> {};

} // namespace lsd

# endif // LSD_TYPE_TRAITS_DISJUNCTION_HPP
