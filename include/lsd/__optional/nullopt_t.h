# /*
#  * Created by YongGyu Lee on 2021/05/23.
#  */
#
# ifndef LSD_OPTIONAL_NULLOPT_T_H_
# define LSD_OPTIONAL_NULLOPT_T_H_

namespace lsd {

struct nullopt_t {
  constexpr explicit nullopt_t(int) {}
};

constexpr nullopt_t nullopt{0};

} // namespace lsd

# endif // LSD_OPTIONAL_NULLOPT_T_H_
