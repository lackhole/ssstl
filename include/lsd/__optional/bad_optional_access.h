# /*
#  * Created by YongGyu Lee on 2021/05/23.
#  */
#
# ifndef LSD_OPTIONAL_BAD_OPTIONAL_ACCESS_H_
# define LSD_OPTIONAL_BAD_OPTIONAL_ACCESS_H_
#
# include <exception>

namespace lsd {

class bad_optional_access : public std::exception {
 public:
  bad_optional_access() noexcept = default;
  bad_optional_access(const bad_optional_access&) noexcept = default;
  bad_optional_access& operator=(const bad_optional_access&) noexcept = default;

  const char *what() const noexcept override {
    return "bad optional access";
  }
};

} // namespace lsd

# endif // LSD_OPTIONAL_BAD_OPTIONAL_ACCESS_H_
