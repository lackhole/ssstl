# /*
#  * Created by YongGyu Lee on 2021/09/03.
#  */
#
# ifndef LSD_TYPE_TRAITS_NEGATION_H_
# define LSD_TYPE_TRAITS_NEGATION_H_
#
# include <type_traits>
# 
# include "lsd/__type_traits/bool_constant.h"

namespace lsd {

template<typename B> struct negation : bool_constant<!bool(B::value)> {};

} // namespace lsd

# endif // LSD_TYPE_TRAITS_NEGATION_H_
