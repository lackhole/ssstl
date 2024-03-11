#include <cstdint>
#include <iostream>
#include <array>
#include <functional>
#include <type_traits>
#include <memory>

#include "lsd/type_traits.h"
#include "lsd_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif

// helpers for testing
namespace Details
{

template <class T>
struct IsComplete
{
  typedef char no;
  struct yes { char dummy[2]; };

  template <class U, class = decltype(sizeof(std::declval< U >())) >
  static yes check(U*);

  template <class U>
  static no check(...);

  static const bool value = sizeof(check< T >(nullptr)) == sizeof(yes);
};

} // namespace Details

void normal_function(){}
void variadic_function(...) {}
template<typename T> void template_function() {}
template<typename ...Args> void variadic_template_function(Args&&...) {}
template<typename ...Args> void variadic_template_variadic_function(Args&&..., ...) {}

int main() {
  LSD_INIT_TEST("type_traits")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';

  // type_identity
  LSD_TESTC(std::is_same<lsd::type_identity<int>::type, lsd::type_identity_t<int>>::value)
  LSD_TESTC(std::is_same<lsd::type_identity_t<int>, int>::value)
  LSD_TESTC(std::is_same<lsd::type_identity_t<void()>, void()>::value)
  LSD_TESTC(std::is_same<lsd::type_identity_t<decltype(std::cout)>, decltype(std::cout)>::value)
  LSD_TESTC(std::is_same<lsd::type_identity_t<void()&&>, void()&&>::value)

  // void_t
  LSD_TESTC(std::is_void<lsd::void_t<>>::value)
  LSD_TESTC(std::is_void<lsd::void_t<int>>::value)
  LSD_TESTC(std::is_void<lsd::void_t<int, float, std::string>>::value)

  { // declval

  }

  { // is_swappable
    struct e { e(const e &) = delete; };
    struct e2 { e2(const e2 &) noexcept(false); };

    LSD_TESTC(lsd::is_swappable<std::unique_ptr<int>>::value)
    LSD_TESTC(lsd::is_swappable_with<int&, int&>::value)
    LSD_TESTC(lsd::is_swappable<int>::value)
    LSD_TESTC(!lsd::is_swappable<int[]>::value)
    LSD_TESTC(lsd::is_swappable<int[3]>::value)
    LSD_TESTC(!lsd::is_swappable<e>::value)
    LSD_TESTC(!lsd::is_swappable<void() &&>::value)

    LSD_TESTC(lsd::is_nothrow_swappable<int>::value)
    LSD_TESTC(!lsd::is_nothrow_swappable<e2>::value)
  }

  { // is_trivially_copyable (std)

  }

  { // is_trivial (second hand std)

  }

  { // is_standard_layout (std)

  }

  { // is_pod (second hand std)

  }

  { // has_unique_object_representation (std)
# if LSD_CXX_VER >= 17

# endif
  }



  { // remove_cvref

  }

  { // invoke_result
    using x = lsd::invoke_result<int>;
    using y = lsd::invoke_result<void()&&, std::nullptr_t, void()>;

    struct foo {};
    struct incomplete;

    LSD_TESTC(std::is_void<lsd::invoke_result_t<void()>>::value)
    LSD_TESTC(std::is_void<lsd::invoke_result_t<void(*)()>>::value)
    LSD_TESTC(std::is_void<lsd::invoke_result_t<void(foo::*)(), foo&>>::value)
    LSD_TESTC(std::is_void<lsd::invoke_result_t<void(foo::*)(), foo*>>::value)
# if LSD_CXX_VER >= 17
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<void(foo::*)(), foo>, std::invoke_result_t<void(foo::*)(), foo>>::value)
# endif


    LSD_TESTC(std::is_same<lsd::invoke_result_t<int()>, int>::value)
    LSD_TESTC(std::is_same<lsd::invoke_result_t<foo()>, foo>::value)
    LSD_TESTC(std::is_same<lsd::invoke_result_t<void(incomplete[]), incomplete[3]>, void>::value)

# if LSD_CXX_VER >= 14
    auto lambda = [](auto x) -> lsd::std::conditional_t<lsd::is_integral<decltype(x)>::value, int, float> { return 0; };
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<decltype(lambda), int>, int>::value)
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<decltype(lambda), float>, float>::value)
# endif

    struct c {
      int operator()();
      void operator()(int);
    };
    LSD_TESTC(std::is_same<lsd::invoke_result_t<c>, int>::value)
    LSD_TESTC(std::is_same<lsd::invoke_result_t<c, float>, void>::value)

    LSD_TESTC(std::is_same<void, lsd::invoke_result_t<c, int>>::value);
  }

  { // invocable
    LSD_TESTC(lsd::is_invocable<void()>::value)
    LSD_TESTC(lsd::is_invocable<void(*)()>::value)
    LSD_TESTC(lsd::is_invocable<void(&)()>::value)
    LSD_TESTC(lsd::is_invocable<void(int), float>::value)
    LSD_TESTC(lsd::is_invocable<void(bool), int>::value)
    LSD_TESTC(lsd::is_invocable<void(int), bool>::value)
    LSD_TESTC(lsd::is_invocable<void(int), lsd::bool_constant<true>>::value)

    struct a {};
    struct b : a {};

    LSD_TESTC(lsd::is_invocable<void(a&), b&>::value)
  }

  { // decay

  }

  { // common_type

  }

  { // common_reference

  }

  { // underlying_type (std)

  }


  { // make_unsigned

  }

  { // conjunction
    LSD_TESTC(lsd::conjunction<>::value == true)
    LSD_TESTC(lsd::conjunction<std::true_type, std::true_type, std::true_type>::value == true)
    LSD_TESTC(lsd::conjunction<std::false_type, std::false_type, std::false_type>::value == false)
    LSD_TESTC(lsd::conjunction<std::false_type, std::false_type, std::false_type, std::true_type>::value == false)
    LSD_TESTC(lsd::conjunction<std::false_type, void, void()&&>::value == false)
  }

  { // disjunction
    LSD_TESTC(lsd::disjunction<>::value == false)
    LSD_TESTC(lsd::disjunction<std::false_type>::value == false)
    LSD_TESTC(lsd::disjunction<std::false_type, std::false_type>::value == false)
    LSD_TESTC(lsd::disjunction<std::false_type, std::false_type, std::false_type, std::true_type>::value == true)
    LSD_TESTC(lsd::disjunction<std::true_type>::value == true)
# if LSD_CXX_VER >= 14
    LSD_TESTC(lsd::disjunction_v<> == false)
    LSD_TESTC(lsd::disjunction_v<std::false_type> == false)
    LSD_TESTC(lsd::disjunction_v<std::false_type, std::false_type> == false)
    LSD_TESTC(lsd::disjunction_v<std::false_type, std::false_type, std::true_type> == true)
    LSD_TESTC(lsd::disjunction_v<i0, i0, i1, i2> == 1)
# endif
  }

  { // negation
    LSD_TESTC(lsd::negation<std::false_type>::value == true)
    LSD_TESTC(lsd::negation<std::true_type>::value == false)
# if LSD_CXX_VER >= 14
    LSD_TESTC(lsd::negation<std::false_type>::value == lsd::negation_v<std::false_type>)
    LSD_TESTC(lsd::negation<std::true_type>::value == lsd::negation_v<std::true_type>)
# endif
  }

  { // is_constant_evaluated (std)
# if LSD_CXX_VER >= 20

# endif
  }

  LSD_TEST_RETURN
}
