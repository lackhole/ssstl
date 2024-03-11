# /*
#  * Created by YongGyu Lee on 2020/12/08.
#  */
#
# ifndef LSD_TYPE_TRAITS_CVREF_HPP
# define LSD_TYPE_TRAITS_CVREF_HPP
#
# include <type_traits>

namespace lsd {

template<typename T>
struct remove_cvref {
  using type = std::remove_cv_t<std::remove_reference_t<T>>;
};

template<typename T>
using remove_cvref_t = typename remove_cvref<T>::type;

} // namespace lsd

# endif // LSD_TYPE_TRAITS_CVREF_HPP
