# /*
#  * Created by YongGyu Lee on 2021/08/14.
#  */
#
# ifndef LSD_TEST_TEST_UTILS_H_
# define LSD_TEST_TEST_UTILS_H_
#
# include "lsd/type_traits.h"

namespace ss {

template<bool> struct default_constructible_t {};
template<bool> struct copy_constructible_t    {};
template<bool> struct copy_assignable_t       {};
template<bool> struct move_constructible_t    {};
template<bool> struct move_assignable_t       {};

template<> struct default_constructible_t<false> {
  default_constructible_t() = delete;
  default_constructible_t(default_constructible_t const&) = default;
  default_constructible_t(default_constructible_t &&) = default;
  default_constructible_t& operator=(default_constructible_t const&) = default;
  default_constructible_t& operator=(default_constructible_t &&) = default;
};
template<> struct copy_constructible_t<false> {
  copy_constructible_t() = default;
  copy_constructible_t(copy_constructible_t const&) = delete;
  copy_constructible_t(copy_constructible_t &&) = default;
  copy_constructible_t& operator=(copy_constructible_t const&) = default;
  copy_constructible_t& operator=(copy_constructible_t &&) = default;
};
template<> struct copy_assignable_t<false> {
  copy_assignable_t() = default;
  copy_assignable_t(copy_assignable_t const&) = default;
  copy_assignable_t(copy_assignable_t &&) = default;
  copy_assignable_t& operator=(copy_assignable_t const&) = delete;
  copy_assignable_t& operator=(copy_assignable_t &&) = default;
};
template<> struct move_constructible_t<false> {
  move_constructible_t() = default;
  move_constructible_t(move_constructible_t const&) = default;
  move_constructible_t(move_constructible_t &&) = delete;
  move_constructible_t& operator=(move_constructible_t const&) = default;
  move_constructible_t& operator=(move_constructible_t &&) = default;
};
template<> struct move_assignable_t<false> {
  move_assignable_t() = default;
  move_assignable_t(move_assignable_t const&) = default;
  move_assignable_t(move_assignable_t &&) = default;
  move_assignable_t& operator=(move_assignable_t const&) = default;
  move_assignable_t& operator=(move_assignable_t &&) = delete;
};

template<typename Member>
struct with_member {

  template<typename Dummy = void,
    enable_if_t<
      is_default_constructible<Member>::value,
    int> = 0>
  with_member() : member() {};

  template<typename Arg,
    enable_if_t<
      is_constructible<Member, Arg&&>::value,
    int> = 0>
  constexpr explicit with_member(Arg&& arg)
    : member(forward<Arg>(arg)) {}

  template<typename Arg, typename ...Args,
    enable_if_t<
      is_constructible<Member, Arg&&, Args&&...>::value,
    int> = 0>
  constexpr with_member(Arg&& arg, Args&&... args)
    : member(forward<Arg>(arg), forward<Args>(args)...) {}

  Member member;
};

} // namespace ss

# endif // LSD_TEST_TEST_UTILS_H_
