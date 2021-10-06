# /*
#  * Created by YongGyu Lee on 2021/07/06.
#  */
#
# ifndef SS_FUNCTIONAL_H_
# define SS_FUNCTIONAL_H_

# include "ss/memory.h"
# include "ss/type_traits.h"
# include "ss/utility.h"

namespace ss {

template<typename Key>
struct hash;

//template<typename Func, typename ...Args>
//constexpr inline decltype(auto) invoke(Func&&, Args&&... args) {
//  return 0;
//}

template<typename T>
class reference_wrapper {
 private:
  T* val;

  static void FUN(T&) noexcept;
  static void FUN(T&&) = delete;

  template<typename U, typename = void>
  struct test_fun : false_type {};

  template<typename U>
  struct test_fun<U, void_t<decltype(FUN(declval<U>()))>> : true_type {};

 public:
  using type = T;

  // https://cplusplus.github.io/LWG/issue2993
  // Not declare reference_wrapper(T&&) = delete

  template<typename U, typename Dummy = decltype(FUN(std::declval<U>())),
    enable_if_t<
      !is_same<ss::remove_cvref_t<U>, reference_wrapper>::value,
    int> = 0>
  constexpr reference_wrapper(U&& x) noexcept(noexcept(FUN(declval<U>())))
    : val(ss::addressof(ss::forward<U>(x))) {}

  constexpr reference_wrapper(const reference_wrapper&) = default;
  SS_CONSTEXPR_AFTER_14 reference_wrapper& operator=(const reference_wrapper& other) noexcept = default;

  constexpr operator T&() const noexcept {
    return static_cast<T&>(*val);
  }

  constexpr T& get() const noexcept {
    return static_cast<T&>(*val);
  }

  // TODO
//  template<typename ...Args>
//  operator()(Args&&... args))

};

}

# endif // SS_FUNCTIONAL_H_
