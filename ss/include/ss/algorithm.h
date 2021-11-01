# /*
#  * Created by YongGyu Lee on 2021/07/10.
#  */
#
# ifndef SS_ALGORITHM_H_
# define SS_ALGORITHM_H_
#
# include "ss/detail/macro.h"

namespace ss {

template<typename T>
SS_CONSTEXPR_AFTER_14 const T& max(const T& a, const T& b) {
  return ((a > b)) ? a : b;
}

template<typename T, typename Compare>
SS_CONSTEXPR_AFTER_14 const T& max(const T& a, const T& b, Compare comp) {
  return (comp(a, b)) ? a : b;
}

} // namespace ss

#endif // SS_ALGORITHM_H_
