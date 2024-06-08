# /*
#  * Created by YongGyu Lee on 2020/12/08.
#  */
#
# ifndef LSD_TYPE_TRAITS_VOID_T_H_
# define LSD_TYPE_TRAITS_VOID_T_H_
#
# include <type_traits>

namespace lsd {

template<typename ...>
using void_t = void;

} // namespace lsd

# endif // LSD_TYPE_TRAITS_VOID_T_H_
