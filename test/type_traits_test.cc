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


template <class T>
struct IsComplete : std::integral_constant< bool, Details::IsComplete< T >::value >
{};

template<typename T, lsd::enable_if_t<std::is_integral<T>::value, int> = 0>
int test_enable_if();

template<typename T, lsd::enable_if_t<std::is_floating_point<T>::value, int> = 0>
double test_enable_if();

void normal_function(){}
void variadic_function(...) {}
template<typename T> void template_function() {}
template<typename ...Args> void variadic_template_function(Args&&...) {}
template<typename ...Args> void variadic_template_variadic_function(Args&&..., ...) {}


template<typename T, typename = void>
struct has_typename_type : lsd::false_type {};

template<typename T>
struct has_typename_type<T, lsd::void_t<typename T::type>> : lsd::true_type {};

template<typename T>
using has_typename_type_t = typename has_typename_type<T>::type;

template<typename T> using is_false_t = lsd::is_same<T, lsd::false_type>;
template<typename T> using is_true_t = lsd::is_same<T, lsd::true_type>;

using false_t = lsd::false_type;
using true_t = lsd::true_type;
using i0 = lsd::integral_constant<int, 0>;
using i1 = lsd::integral_constant<int, 1>;
using i2 = lsd::integral_constant<int, 2>;
using i3 = lsd::integral_constant<int, 3>;
using i4 = lsd::integral_constant<int, 4>;
using i5 = lsd::integral_constant<int, 5>;
using i6 = lsd::integral_constant<int, 6>;
using i7 = lsd::integral_constant<int, 7>;
using i8 = lsd::integral_constant<int, 8>;
using i9 = lsd::integral_constant<int, 9>;

int main() {
  LSD_INIT_TEST("type_traits")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';


  // integral_constant
  LSD_TESTC(std::is_same<lsd::integral_constant<int, 3>::value_type, int>::value)
  LSD_TESTC(std::integral_constant<int, 3>::value == lsd::integral_constant<int, 3>::value)
  LSD_TESTC(std::integral_constant<bool, true>::value == lsd::bool_constant<true>::value)
  LSD_TESTC(std::is_same<lsd::integral_constant<bool, true>, lsd::bool_constant<true>>::value)

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

  // enable_if
  LSD_TESTC(std::is_same<decltype(test_enable_if<int>()), int>::value)
  LSD_TESTC(std::is_same<decltype(test_enable_if<char>()), int>::value)
  LSD_TESTC(std::is_same<decltype(test_enable_if<float>()), double>::value)
  LSD_TESTC(std::is_same<decltype(test_enable_if<double>()), double>::value)

  // conditional
  LSD_TESTC(std::is_same<lsd::conditional<true, int, float>::type, lsd::conditional_t<true, int, float>>::value)
  LSD_TESTC(std::is_same<lsd::conditional<true, int, float>::type, int>::value)
  LSD_TESTC(std::is_same<lsd::conditional<false, int, float>::type, float>::value)
  LSD_TESTC(std::is_same<lsd::conditional<false, int, void()&&>::type, void()&&>::value)

  // is_same
  LSD_TESTC(lsd::is_same<int, int>::value)
  LSD_TESTC(lsd::is_same<int, int>::value)
  LSD_TESTC(lsd::is_same<void()&, void()&>::value)
  LSD_TESTC(!lsd::is_same<void()&, void()&&>::value)
  LSD_TESTC(!lsd::is_same<int, int&>::value)
  LSD_TESTC(!lsd::is_same<int, volatile int>::value)
  LSD_TESTC(!lsd::is_same<int, const int>::value)

  // is_not_same
  LSD_TESTC(!lsd::is_not_same<int, int>::value)
  LSD_TESTC(!lsd::is_not_same<int, int>::value)
  LSD_TESTC(!lsd::is_not_same<void()&, void()&>::value)
  LSD_TESTC(lsd::is_not_same<void()&, void()&&>::value)
  LSD_TESTC(lsd::is_not_same<int, int&>::value)
  LSD_TESTC(lsd::is_not_same<int, volatile int>::value)
  LSD_TESTC(lsd::is_not_same<int, const int>::value)

  // is_const
  LSD_TESTC(!lsd::is_const<int>::value)
  LSD_TESTC(lsd::is_const<int const>::value)
  LSD_TESTC(!lsd::is_const<const int*>::value)
  LSD_TESTC(lsd::is_const<int* const>::value)
  LSD_TESTC(!lsd::is_const<void(int)const>::value)

  // is_volatile
  LSD_TESTC(!lsd::is_volatile<int>::value)
  LSD_TESTC(lsd::is_volatile<int volatile>::value)
  LSD_TESTC(!lsd::is_volatile<volatile int*>::value)
  LSD_TESTC(lsd::is_volatile<int* volatile>::value)
  LSD_TESTC(!lsd::is_volatile<void(int)volatile>::value)

  // remove_const
  LSD_TESTC(lsd::is_same<int, lsd::remove_const_t<int>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_const_t<int const>>::value)
  LSD_TESTC(lsd::is_same<volatile int, lsd::remove_const_t<volatile int const>>::value)
  LSD_TESTC(lsd::is_same<int*, lsd::remove_const_t<int* const>>::value)

  // remove_volatile
  LSD_TESTC(lsd::is_same<int, lsd::remove_volatile_t<int>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_volatile_t<int volatile>>::value)
  LSD_TESTC(lsd::is_same<const int, lsd::remove_volatile_t<volatile int const>>::value)
  LSD_TESTC(lsd::is_same<int*, lsd::remove_volatile_t<int* volatile>>::value)

  // remove_cv
  LSD_TESTC(lsd::is_same<int, lsd::remove_cv_t<int>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_cv_t<int volatile>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_cv_t<int const>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_cv_t<volatile int const>>::value)
  LSD_TESTC(lsd::is_same<int*, lsd::remove_cv_t<int* volatile const>>::value)

  // add_const
  LSD_TESTC(lsd::is_same<const int, lsd::add_const_t<int>>::value)
  LSD_TESTC(lsd::is_same<const int, lsd::add_const_t<int const>>::value)
  LSD_TESTC(lsd::is_same<const volatile int, lsd::add_const_t<volatile int>>::value)
  LSD_TESTC(lsd::is_same<int* const, lsd::add_const_t<int*>>::value)
  LSD_TESTC(lsd::is_same<void(), lsd::add_const_t<void()>>::value)

  // add_volatile
  LSD_TESTC(lsd::is_same<volatile int, lsd::add_volatile_t<int>>::value)
  LSD_TESTC(lsd::is_same<volatile int, lsd::add_volatile_t<int volatile>>::value)
  LSD_TESTC(lsd::is_same<volatile const int, lsd::add_volatile_t<int const>>::value)
  LSD_TESTC(lsd::is_same<int* volatile, lsd::add_volatile_t<int*>>::value)
  LSD_TESTC(lsd::is_same<void(), lsd::add_volatile_t<void()>>::value)

  // add_cv
  LSD_TESTC(lsd::is_same<volatile const int, lsd::add_cv_t<int>>::value)
  LSD_TESTC(lsd::is_same<volatile const int, lsd::add_cv_t<int volatile>>::value)
  LSD_TESTC(lsd::is_same<volatile const int, lsd::add_cv_t<int const>>::value)
  LSD_TESTC(lsd::is_same<volatile const int, lsd::add_cv_t<volatile int const>>::value)
  LSD_TESTC(lsd::is_same<int* volatile const , lsd::add_cv_t<int* >>::value)
  LSD_TESTC(lsd::is_same<void(), lsd::add_cv_t<void()>>::value)

  // remove_reference
  LSD_TESTC(lsd::is_same<int, lsd::remove_reference_t<int>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_reference_t<int&>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_reference_t<int&&>>::value)
  LSD_TESTC(lsd::is_same<int*, lsd::remove_reference_t<int*>>::value)
  LSD_TESTC(lsd::is_same<int*, lsd::remove_reference_t<int*&>>::value)
  LSD_TESTC(lsd::is_same<int*, lsd::remove_reference_t<int*&&>>::value)
  LSD_TESTC(!lsd::is_same<void(), lsd::remove_reference_t<void()&>>::value)

  // add_lvalue_reference
  LSD_TESTC(lsd::is_same<int&, lsd::add_lvalue_reference_t<int>>::value)
  LSD_TESTC(lsd::is_same<int&, lsd::add_lvalue_reference_t<int&>>::value)
  LSD_TESTC(lsd::is_same<int&, lsd::add_lvalue_reference_t<int&&>>::value)
  LSD_TESTC(lsd::is_same<void(&)(), lsd::add_lvalue_reference_t<void()>>::value)
  LSD_TESTC(lsd::is_same<void, lsd::add_lvalue_reference_t<void>>::value)

  // add_rvalue_reference
  LSD_TESTC(lsd::is_same<int&&, lsd::add_rvalue_reference_t<int>>::value)
  LSD_TESTC(lsd::is_same<int&, lsd::add_rvalue_reference_t<int&>>::value)
  LSD_TESTC(lsd::is_same<int&&, lsd::add_rvalue_reference_t<int&&>>::value)
  LSD_TESTC(lsd::is_same<void(&&)(), lsd::add_rvalue_reference_t<void()>>::value)
  LSD_TESTC(lsd::is_same<void()const, lsd::add_rvalue_reference_t<void()const>>::value)
  LSD_TESTC(lsd::is_same<void, lsd::add_rvalue_reference_t<void>>::value)

  { // declval

  }

  // remove_pointer
  LSD_TESTC(lsd::is_same<int, lsd::remove_pointer_t<int>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_pointer_t<int*>>::value)
  LSD_TESTC(lsd::is_same<int*, lsd::remove_pointer_t<int**>>::value)
  LSD_TESTC(lsd::is_same<void, lsd::remove_pointer_t<void*>>::value)
  LSD_TESTC(lsd::is_same<void, lsd::remove_pointer_t<void>>::value)
  LSD_TESTC(lsd::is_same<void(), lsd::remove_pointer_t<void(*)()>>::value)
  LSD_TESTC(lsd::is_same<void()const, lsd::remove_pointer_t<void()const>>::value)

  // add_pointer
  LSD_TESTC(lsd::is_same<int*, lsd::add_pointer_t<int>>::value)
  LSD_TESTC(lsd::is_same<int**, lsd::add_pointer_t<int*>>::value)
  LSD_TESTC(lsd::is_same<int***, lsd::add_pointer_t<int**>>::value)
  LSD_TESTC(lsd::is_same<void**, lsd::add_pointer_t<void*>>::value)
  LSD_TESTC(lsd::is_same<void*, lsd::add_pointer_t<void>>::value)
  LSD_TESTC(lsd::is_same<void(**)(), lsd::add_pointer_t<void(*)()>>::value)
  LSD_TESTC(lsd::is_same<void()const, lsd::add_pointer_t<void()const>>::value)
  LSD_TESTC(lsd::is_same<void()const, lsd::add_pointer<void()const>::type>::value)

  // remove_extent
  LSD_TESTC(lsd::is_same<int, lsd::remove_extent_t<int>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_extent_t<int[]>>::value)
  LSD_TESTC(lsd::is_same<int[2], lsd::remove_extent_t<int[1][2]>>::value)

  // remove_all_extents
  LSD_TESTC(lsd::is_same<int, lsd::remove_all_extents_t<int>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_all_extents_t<int[]>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_all_extents_t<int[1][2]>>::value)
  LSD_TESTC(lsd::is_same<int, lsd::remove_all_extents_t<int[1][2][3]>>::value)

  // is_void
  LSD_TESTC(lsd::is_void<void>::value)
  LSD_TESTC(lsd::is_void<volatile void>::value)
  LSD_TESTC(lsd::is_void<const void>::value)
  LSD_TESTC(!lsd::is_void<void()&&>::value)
  LSD_TESTC(!lsd::is_void<int>::value)

  // is_null_pointer
  LSD_TESTC(lsd::is_null_pointer<std::nullptr_t>::value)
  LSD_TESTC(lsd::is_null_pointer<decltype(nullptr)>::value)
  LSD_TESTC(lsd::is_null_pointer<volatile std::nullptr_t>::value)
  LSD_TESTC(!lsd::is_null_pointer<void()&&>::value)
  LSD_TESTC(!lsd::is_null_pointer<void>::value)

  { // is_integral
    enum e{};
    LSD_TESTC(lsd::is_integral<bool>::value)
    LSD_TESTC(lsd::is_integral<char>::value)
    LSD_TESTC(lsd::is_integral<signed char>::value)
    LSD_TESTC(lsd::is_integral<volatile unsigned char>::value)
    LSD_TESTC(lsd::is_integral<char16_t>::value)
    LSD_TESTC(lsd::is_integral<char32_t>::value)
    LSD_TESTC(lsd::is_integral<wchar_t>::value)
    LSD_TESTC(lsd::is_integral<short>::value)
    LSD_TESTC(lsd::is_integral<int>::value)
    LSD_TESTC(lsd::is_integral<long>::value)
    LSD_TESTC(lsd::is_integral<long long>::value)
    LSD_TESTC(!lsd::is_integral<e>::value)
    LSD_TESTC(!lsd::is_integral<float>::value)
    LSD_TESTC(!lsd::is_integral<int*>::value)
    LSD_TESTC(!lsd::is_integral<int()&&>::value)
  }

  // is_floating_point
  LSD_TESTC(lsd::is_floating_point<float>::value)
  LSD_TESTC(lsd::is_floating_point<double>::value)
  LSD_TESTC(lsd::is_floating_point<long double>::value)
  LSD_TESTC(lsd::is_floating_point<volatile float>::value)
  LSD_TESTC(lsd::is_floating_point<const float>::value)
  LSD_TESTC(lsd::is_floating_point<const volatile float>::value)
  LSD_TESTC(!lsd::is_floating_point<float*>::value)
  LSD_TESTC(!lsd::is_floating_point<int>::value)
  LSD_TESTC(!lsd::is_floating_point<float()>::value)

  // is_array
  LSD_TESTC(lsd::is_array<int[]>::value)
  LSD_TESTC(lsd::is_array<int[][3]>::value)
  LSD_TESTC(lsd::is_array<int[][3][4][5][6]>::value)
  LSD_TESTC(!lsd::is_array<int*>::value)
  LSD_TESTC(!lsd::is_array<std::array<int, 3>>::value)

  { // is_bounded_array
    LSD_TESTC(!lsd::is_bounded_array<int>::value)
    LSD_TESTC(!lsd::is_bounded_array<void()>::value)
    LSD_TESTC(!lsd::is_bounded_array<void()&&>::value)
    LSD_TESTC(!lsd::is_bounded_array<int[]>::value)
    LSD_TESTC(!lsd::is_bounded_array<int*>::value)
    LSD_TESTC(!lsd::is_bounded_array<int(&)[3]>::value)
    LSD_TESTC(lsd::is_bounded_array<int[3]>::value)
    LSD_TESTC(!lsd::is_bounded_array<int[][3]>::value)
    LSD_TESTC(lsd::is_bounded_array<int[2][3]>::value)
  }

  { // is_unbounded_array
    LSD_TESTC(!lsd::is_unbounded_array<int>::value)
    LSD_TESTC(!lsd::is_unbounded_array<void()>::value)
    LSD_TESTC(!lsd::is_unbounded_array<void()&&>::value)
    LSD_TESTC(!lsd::is_unbounded_array<int*>::value)
    LSD_TESTC(!lsd::is_unbounded_array<int(&)[]>::value)
    LSD_TESTC(lsd::is_unbounded_array<int[]>::value)
    LSD_TESTC(!lsd::is_unbounded_array<int[3]>::value)
    LSD_TESTC(lsd::is_unbounded_array<int[][3]>::value)
    LSD_TESTC(!lsd::is_unbounded_array<int[2][3]>::value)
  }

  { // is_enum
    enum e{};
    LSD_TESTC(lsd::is_enum<e>::value)
    LSD_TESTC(lsd::is_enum<volatile e>::value)
    LSD_TESTC(lsd::is_enum<const e>::value)
    LSD_TESTC(lsd::is_enum<const volatile e>::value)
    LSD_TESTC(!lsd::is_enum<e*>::value)
    LSD_TESTC(!lsd::is_enum<int>::value)
  }

  { // is_union
    union e{};
    LSD_TESTC(lsd::is_union<e>::value)
    LSD_TESTC(lsd::is_union<volatile e>::value)
    LSD_TESTC(lsd::is_union<const e>::value)
    LSD_TESTC(lsd::is_union<const volatile e>::value)
    LSD_TESTC(!lsd::is_union<e*>::value)
    LSD_TESTC(!lsd::is_union<int>::value)
  }

  { // is_class
    class c{}; struct s{};
    auto lambda = []()->void{};
    LSD_TESTC(lsd::is_class<c>::value)
    LSD_TESTC(lsd::is_class<s>::value)
    LSD_TESTC(lsd::is_class<decltype(lambda)>::value)
    LSD_TESTC(lsd::is_class<volatile c>::value)
    LSD_TESTC(lsd::is_class<const c>::value)
    LSD_TESTC(lsd::is_class<const volatile c>::value)
    LSD_TESTC(!lsd::is_class<c*>::value)
    LSD_TESTC(!lsd::is_class<int>::value)
    LSD_TESTC(!lsd::is_class<int()&&>::value)
  }

  { // is_pointer
    LSD_TESTC(lsd::is_pointer<void *>::value)
    LSD_TESTC(lsd::is_pointer<void ******>::value)
    LSD_TESTC(lsd::is_pointer<volatile void *>::value)
    LSD_TESTC(lsd::is_pointer<const void *>::value)
    LSD_TESTC(lsd::is_pointer<const volatile void *>::value)
    LSD_TESTC(lsd::is_pointer<void(*)()>::value)
    LSD_TESTC(!lsd::is_pointer<int>::value)
    LSD_TESTC(!lsd::is_pointer<int()&&>::value)
    LSD_TESTC(!lsd::is_pointer<int(&)()>::value)
    LSD_TESTC(!lsd::is_pointer<int()>::value)
  }

  { // is_lvalue_reference
    auto lambda = [](){};
    auto& lambda_ref = lambda;
    LSD_TESTC(lsd::is_lvalue_reference<int&>::value)
    LSD_TESTC(lsd::is_lvalue_reference<int(&)()>::value)
    LSD_TESTC(lsd::is_lvalue_reference<decltype(lambda_ref)>::value)
    LSD_TESTC(lsd::is_lvalue_reference<float &>::value)
    LSD_TESTC(!lsd::is_lvalue_reference<int>::value)
    LSD_TESTC(!lsd::is_lvalue_reference<int*>::value)
    LSD_TESTC(!lsd::is_lvalue_reference<int&&>::value)
    LSD_TESTC(!lsd::is_lvalue_reference<int(&&)()>::value)
    LSD_TESTC(!lsd::is_lvalue_reference<int()&&>::value)
  }

  { // is_rvalue_reference
    auto lambda = [](){};
    auto&& lambda_ref = std::move(lambda);
    LSD_TESTC(lsd::is_rvalue_reference<int&&>::value)
    LSD_TESTC(lsd::is_rvalue_reference<int(&&)()>::value)
    LSD_TESTC(lsd::is_rvalue_reference<decltype(lambda_ref)>::value)
    LSD_TESTC(lsd::is_rvalue_reference<float &&>::value)
    LSD_TESTC(!lsd::is_rvalue_reference<int>::value)
    LSD_TESTC(!lsd::is_rvalue_reference<int*>::value)
    LSD_TESTC(!lsd::is_rvalue_reference<int&>::value)
    LSD_TESTC(!lsd::is_rvalue_reference<int(&)()>::value)
    LSD_TESTC(!lsd::is_rvalue_reference<int()&&>::value)
  }

  { // is_reference
    auto lambda = [](){};
    auto&& lambda_ref = std::move(lambda);
    LSD_TESTC(lsd::is_reference<int&>::value)
    LSD_TESTC(lsd::is_reference<int&&>::value)
    LSD_TESTC(lsd::is_reference<int(&&)()>::value)
    LSD_TESTC(lsd::is_reference<int(&)()>::value)
    LSD_TESTC(lsd::is_reference<decltype(lambda_ref)>::value)
    LSD_TESTC(lsd::is_reference<float &&>::value)
    LSD_TESTC(!lsd::is_reference<int>::value)
    LSD_TESTC(!lsd::is_reference<int*>::value)
    LSD_TESTC(!lsd::is_reference<int()&&>::value)
  }

  {
    // is_function
    auto lambda = [](){};
    LSD_TESTC(lsd::is_function<decltype(normal_function)>::value)
    LSD_TESTC(lsd::is_function<decltype(template_function<void>)>::value)
    LSD_TESTC(lsd::is_function<decltype(variadic_function)>::value)
    LSD_TESTC(lsd::is_function<decltype(variadic_template_function<>)>::value)
    LSD_TESTC(lsd::is_function<decltype(variadic_template_variadic_function<>)>::value)
    LSD_TESTC(lsd::is_function<void()>::value)
    LSD_TESTC(!lsd::is_function<void(&)()>::value)
    LSD_TESTC(!lsd::is_function<void(*)()>::value)
    LSD_TESTC(!lsd::is_function<std::function<void()>>::value)
    LSD_TESTC(!lsd::is_function<decltype(lambda)>::value)
  }

  { // is_member_pointer
    struct s {
      int x;
      void mf() {}
      void cmf() const {}
      void rmf() && {}
    };

    LSD_TESTC(lsd::is_member_pointer<decltype(&s::x)>::value)
    LSD_TESTC(lsd::is_member_pointer<decltype(&s::mf)>::value)
    LSD_TESTC(lsd::is_member_pointer<decltype(&s::cmf)>::value)
    LSD_TESTC(lsd::is_member_pointer<decltype(&s::rmf)>::value)
    LSD_TESTC(lsd::is_member_pointer<decltype(&s::rmf)>::value)
    LSD_TESTC(lsd::is_member_pointer<int s::*>::value)
    LSD_TESTC(!lsd::is_member_pointer<int s::**>::value)
    LSD_TESTC(lsd::is_member_pointer<int(s::*)(void)>::value)
    LSD_TESTC(!lsd::is_member_pointer<int(s::**)(void)>::value)
    LSD_TESTC(lsd::is_member_pointer<int(s::*)(void)&>::value)
    LSD_TESTC(lsd::is_member_pointer<void(s::*)(void)volatile const&>::value)
    LSD_TESTC(!lsd::is_member_pointer<void*>::value)
    LSD_TESTC(!lsd::is_member_pointer<void(*)(int)>::value)
    LSD_TESTC(!lsd::is_member_pointer<void(&)(int)>::value)
    LSD_TESTC(!lsd::is_member_pointer<void(int)&&>::value)

    LSD_TESTC(lsd::is_member_function_pointer<int(s::*)(int)>::value)
    LSD_TESTC(!lsd::is_member_function_pointer<int(s::**)(int)>::value)
    LSD_TESTC(!lsd::is_member_function_pointer<int(s::*)>::value)

    LSD_TESTC(!lsd::is_member_object_pointer<int(s::*)(int)>::value)
    LSD_TESTC(!lsd::is_member_object_pointer<int(s::**)(int)>::value)
    LSD_TESTC(lsd::is_member_object_pointer<int(s::*)>::value)
  }

  { // is_arithmetic
    enum e {};
    LSD_TESTC(lsd::is_arithmetic<int>::value)
    LSD_TESTC(lsd::is_arithmetic<signed char>::value)
    LSD_TESTC(lsd::is_arithmetic<long double>::value)
    LSD_TESTC(lsd::is_arithmetic<const volatile int>::value)
    LSD_TESTC(lsd::is_arithmetic<std::size_t>::value)
    LSD_TESTC(lsd::is_arithmetic<std::ptrdiff_t>::value)
    LSD_TESTC(!lsd::is_arithmetic<void>::value)
    LSD_TESTC(!lsd::is_arithmetic<lsd::nullptr_t>::value)
    LSD_TESTC(!lsd::is_arithmetic<std::nullptr_t>::value)
    LSD_TESTC(!lsd::is_arithmetic<decltype(nullptr)>::value)
    LSD_TESTC(!lsd::is_arithmetic<void*>::value)
    LSD_TESTC(!lsd::is_arithmetic<e>::value)
    LSD_TESTC(!lsd::is_arithmetic<std::vector<int>>::value)
  }

  { // is_fundamental
    enum e {};
    struct s {};
    LSD_TESTC(lsd::is_fundamental<int>::value)
    LSD_TESTC(lsd::is_fundamental<signed char>::value)
    LSD_TESTC(lsd::is_fundamental<long double>::value)
    LSD_TESTC(lsd::is_fundamental<const volatile int>::value)
    LSD_TESTC(lsd::is_fundamental<std::size_t>::value)
    LSD_TESTC(lsd::is_fundamental<std::ptrdiff_t>::value)
    LSD_TESTC(lsd::is_fundamental<void>::value)
    LSD_TESTC(!lsd::is_fundamental<int&>::value)
    LSD_TESTC(lsd::is_fundamental<lsd::nullptr_t>::value)
    LSD_TESTC(lsd::is_fundamental<std::nullptr_t>::value)
    LSD_TESTC(lsd::is_fundamental<decltype(nullptr)>::value)
    LSD_TESTC(!lsd::is_fundamental<void*>::value)
    LSD_TESTC(!lsd::is_fundamental<e>::value)
    LSD_TESTC(!lsd::is_fundamental<s>::value)
    LSD_TESTC(!lsd::is_fundamental<std::vector<int>>::value)
  }

  { // is_scalar
    enum e {};
    struct s {};
    LSD_TESTC(lsd::is_scalar<int>::value)
    LSD_TESTC(lsd::is_scalar<signed char>::value)
    LSD_TESTC(lsd::is_scalar<long double>::value)
    LSD_TESTC(lsd::is_scalar<const volatile int>::value)
    LSD_TESTC(lsd::is_scalar<std::size_t>::value)
    LSD_TESTC(lsd::is_scalar<std::ptrdiff_t>::value)
    LSD_TESTC(!lsd::is_scalar<void>::value)
    LSD_TESTC(!lsd::is_scalar<void()>::value)
    LSD_TESTC(!lsd::is_scalar<void()&&>::value)
    LSD_TESTC(!lsd::is_scalar<int&>::value)
    LSD_TESTC(lsd::is_scalar<lsd::nullptr_t>::value)
    LSD_TESTC(lsd::is_scalar<std::nullptr_t>::value)
    LSD_TESTC(lsd::is_scalar<decltype(nullptr)>::value)
    LSD_TESTC(lsd::is_scalar<void*>::value)
    LSD_TESTC(lsd::is_scalar<void*****>::value)
    LSD_TESTC(lsd::is_scalar<int s::*>::value)
    LSD_TESTC(lsd::is_scalar<void* s::*>::value)
    LSD_TESTC(lsd::is_scalar<void* (s::*)()>::value)
    LSD_TESTC(lsd::is_scalar<e>::value)
    LSD_TESTC(!lsd::is_scalar<s>::value)
    LSD_TESTC(!lsd::is_scalar<std::vector<int>>::value)
  }

  { // is_object
    enum e {};
    struct s {};
    LSD_TESTC(lsd::is_object<int>::value)
    LSD_TESTC(lsd::is_object<signed char>::value)
    LSD_TESTC(lsd::is_object<long double>::value)
    LSD_TESTC(lsd::is_object<const volatile int>::value)
    LSD_TESTC(lsd::is_object<std::size_t>::value)
    LSD_TESTC(lsd::is_object<std::ptrdiff_t>::value)
    LSD_TESTC(!lsd::is_object<void>::value)
    LSD_TESTC(!lsd::is_object<int&>::value)
    LSD_TESTC(!lsd::is_object<void()>::value)
    LSD_TESTC(!lsd::is_object<void()&&>::value)
    LSD_TESTC(lsd::is_object<lsd::nullptr_t>::value)
    LSD_TESTC(lsd::is_object<std::nullptr_t>::value)
    LSD_TESTC(lsd::is_object<decltype(nullptr)>::value)
    LSD_TESTC(lsd::is_object<void*>::value)
    LSD_TESTC(lsd::is_object<void*****>::value)
    LSD_TESTC(lsd::is_object<int s::*>::value)
    LSD_TESTC(lsd::is_object<void* s::*>::value)
    LSD_TESTC(lsd::is_object<void* (s::*)()>::value)
    LSD_TESTC(lsd::is_object<e>::value)
    LSD_TESTC(lsd::is_object<s>::value)
    LSD_TESTC(lsd::is_object<std::vector<int>>::value)
  }

  { // is_compound
    enum e {};
    struct s {};
    LSD_TESTC(!lsd::is_compound<int>::value)
    LSD_TESTC(!lsd::is_compound<signed char>::value)
    LSD_TESTC(!lsd::is_compound<long double>::value)
    LSD_TESTC(!lsd::is_compound<const volatile int>::value)
    LSD_TESTC(!lsd::is_compound<std::size_t>::value)
    LSD_TESTC(!lsd::is_compound<std::ptrdiff_t>::value)
    LSD_TESTC(!lsd::is_compound<void>::value)
    LSD_TESTC(lsd::is_compound<int&>::value)
    LSD_TESTC(lsd::is_compound<void()>::value)
    LSD_TESTC(lsd::is_compound<void()&&>::value)
    LSD_TESTC(!lsd::is_compound<lsd::nullptr_t>::value)
    LSD_TESTC(!lsd::is_compound<std::nullptr_t>::value)
    LSD_TESTC(!lsd::is_compound<decltype(nullptr)>::value)
    LSD_TESTC(lsd::is_compound<void*>::value)
    LSD_TESTC(lsd::is_compound<void*****>::value)
    LSD_TESTC(lsd::is_compound<int s::*>::value)
    LSD_TESTC(lsd::is_compound<void* s::*>::value)
    LSD_TESTC(lsd::is_compound<void* (s::*)()>::value)
    LSD_TESTC(lsd::is_compound<e>::value)
    LSD_TESTC(lsd::is_compound<s>::value)
    LSD_TESTC(lsd::is_compound<std::vector<int>>::value)
  }

  { // is_constructible
    struct a {};
    struct b { b(int){}};
    struct c { c(a) {}; c() noexcept(false) {}};

    // non user-defined types
    // default
    LSD_TESTC(std::is_constructible<int>::value)
    LSD_TESTC(!lsd::is_constructible<int&>::value)
    LSD_TESTC(!lsd::is_constructible<int&&>::value)
    LSD_TESTC(lsd::is_constructible<int[3]>::value)
    LSD_TESTC(!lsd::is_constructible<int[]>::value)
    LSD_TESTC(!lsd::is_constructible<void>::value)
    LSD_TESTC(lsd::is_constructible<void*>::value)
    LSD_TESTC(!lsd::is_constructible<void()>::value)
    LSD_TESTC(lsd::is_constructible<void(*)()>::value)
    LSD_TESTC(!lsd::is_constructible<void(&)()>::value)
    LSD_TESTC(!lsd::is_constructible<void()&&>::value)
    LSD_TESTC(lsd::is_constructible<std::nullptr_t>::value)

    // unary
    LSD_TESTC(!lsd::is_constructible<int&, int>::value)
    LSD_TESTC(lsd::is_constructible<int&, int&>::value)
    LSD_TESTC(lsd::is_constructible<const int&, int>::value)
    LSD_TESTC(lsd::is_constructible<const int&, int&>::value)
    LSD_TESTC(lsd::is_constructible<const int&, int&&>::value)
    LSD_TESTC(lsd::is_constructible<int, double>::value)
    LSD_TESTC(lsd::is_constructible<const int&, double>::value)
    LSD_TESTC(lsd::is_constructible<int&&, double>::value)
    LSD_TESTC(!lsd::is_constructible<int[3], int[3]>::value)
    LSD_TESTC(!lsd::is_constructible<int[3], int[]>::value)
    LSD_TESTC(!lsd::is_constructible<int[], int[3]>::value)
    LSD_TESTC(lsd::is_constructible<void(&)(), void(&)()>::value)
    LSD_TESTC(lsd::is_constructible<void(*)(), void(*)()>::value)
    LSD_TESTC(lsd::is_constructible<void(&)(), void()>::value)
    LSD_TESTC(lsd::is_constructible<void(*)(), void()>::value)
    LSD_TESTC(!lsd::is_constructible<void(*)(), void()&>::value)
    LSD_TESTC(!lsd::is_constructible<void(*)(), void()const>::value)
    LSD_TESTC(!lsd::is_constructible<void(), void()>::value)
    LSD_TESTC(!lsd::is_constructible<void(), void()&>::value)
    LSD_TESTC(!lsd::is_constructible<void()&, void()>::value)


    // user-defined types
    LSD_TESTC(lsd::is_constructible<a>::value)
    LSD_TESTC(!lsd::is_constructible<b>::value)
    LSD_TESTC(lsd::is_constructible<b, int>::value)
    LSD_TESTC(lsd::is_constructible<b, int&&>::value)
    LSD_TESTC(lsd::is_constructible<b, float>::value)
    LSD_TESTC(lsd::is_constructible<b, size_t>::value)
    LSD_TESTC(lsd::is_constructible<b, b>::value)
    LSD_TESTC(lsd::is_constructible<b, b&>::value)
    LSD_TESTC(lsd::is_constructible<c, a>::value)


    // is_trivially_constructible
    LSD_TESTC(lsd::is_trivially_constructible<int>::value)
    LSD_TESTC(lsd::is_trivially_constructible<a>::value)
    LSD_TESTC(lsd::is_trivially_constructible<int*>::value)
    LSD_TESTC(lsd::is_trivially_constructible<std::nullptr_t>::value)
    LSD_TESTC(lsd::is_trivially_constructible<int[3]>::value)
    LSD_TESTC(!lsd::is_trivially_constructible<int[]>::value)
    LSD_TESTC(!lsd::is_trivially_constructible<b>::value)
    LSD_TESTC(!lsd::is_trivially_constructible<int&>::value)
    LSD_TESTC(!lsd::is_trivially_constructible<void>::value)
    LSD_TESTC(!lsd::is_trivially_constructible<void()&&>::value)

    // is_nothrow_constructible
    // default
    LSD_TESTC(std::is_nothrow_constructible<int>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<int&>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<int&&>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<int[3]>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<int[]>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<void>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<void*>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<void()>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<void(*)()>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<void(&)()>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<void()&&>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<std::nullptr_t>::value)

    // unary
    LSD_TESTC(!lsd::is_nothrow_constructible<int&, int>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<int&, int&>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<const int&, int>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<const int&, int&>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<const int&, int&&>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<int, double>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<const int&, double>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<int&&, double>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<int[3], int[3]>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<int[3], int[]>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<int[], int[3]>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<void(&)(), void(&)()>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<void(*)(), void(*)()>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<void(&)(), void()>::value)
    LSD_TESTC(lsd::is_nothrow_constructible<void(*)(), void()>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<void(*)(), void()&>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<void(*)(), void()const>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<void(), void()>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<void(), void()&>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<void()&, void()>::value)

    // user-defined types
    LSD_TESTC(lsd::is_nothrow_constructible<a>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<b>::value)
    LSD_TESTC(!lsd::is_nothrow_constructible<b, float>::value)
  }

  { // default_constructible
    struct a { a(int){}};
    struct b {};
    auto lambda = [](){};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

    LSD_TESTC(lsd::is_default_constructible<int>::value)
    LSD_TESTC(lsd::is_default_constructible<const int>::value)
    LSD_TESTC(!lsd::is_default_constructible<int&>::value)
    LSD_TESTC(!lsd::is_default_constructible<int&&>::value)
    LSD_TESTC(lsd::is_default_constructible<std::nullptr_t>::value)
    LSD_TESTC(lsd::is_default_constructible<int[3]>::value)
    LSD_TESTC(lsd::is_default_constructible<const int[3]>::value)
    LSD_TESTC(!lsd::is_default_constructible<int[]>::value)
    LSD_TESTC(!lsd::is_default_constructible<void>::value)
    LSD_TESTC(!lsd::is_default_constructible<void()>::value)
    LSD_TESTC(!lsd::is_default_constructible<void()&&>::value)

    // TODO: define feature macros. __cplusplus is too rough to check each feature support
//# if LSD_CXX_VER < 20
//    LSD_TESTC(!lsd::is_default_constructible<decltype(lambda)>::value)
//# else
//    LSD_TESTC(lsd::is_default_constructible<decltype(lambda)>::value)
//# endif
    LSD_TESTC(!lsd::is_default_constructible<decltype(lambda_capture)>::value)
    // MSVC Bug: https://stackoverflow.com/questions/68363717/msvc-behaves-different-about-default-constructor-of-closure-type-in-c20
//    LSD_TESTC(!lsd::is_default_constructible<decltype(lambda_capture_default)>::value)

    LSD_TESTC(!lsd::is_default_constructible<a>::value)
    LSD_TESTC(lsd::is_default_constructible<b>::value)
  }

  { // copy_constructible
    struct a { a(const a&) = delete; };
    struct b {};
    struct c : a {};
    struct d { d(const d&) noexcept(false) {}};
    auto lambda = []{};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

    LSD_TESTC(lsd::is_copy_constructible<int>::value)
    LSD_TESTC(lsd::is_copy_constructible<const int>::value)
    LSD_TESTC(lsd::is_copy_constructible<int&>::value)
    LSD_TESTC(lsd::is_copy_constructible<const int&>::value)
    LSD_TESTC(!lsd::is_copy_constructible<int&&>::value)
    LSD_TESTC(!lsd::is_copy_constructible<const int&&>::value)
    LSD_TESTC(!lsd::is_copy_constructible<void>::value)
    LSD_TESTC(!lsd::is_copy_constructible<void()>::value)
    LSD_TESTC(!lsd::is_copy_constructible<void()&>::value)
    LSD_TESTC(!lsd::is_copy_constructible<void()const>::value)
    LSD_TESTC(lsd::is_copy_constructible<lsd::nullptr_t>::value)
    LSD_TESTC(lsd::is_copy_constructible<decltype(lambda)>::value)
    LSD_TESTC(lsd::is_copy_constructible<decltype(lambda_capture)>::value)
    LSD_TESTC(lsd::is_copy_constructible<decltype(lambda_capture_default)>::value)
    LSD_TESTC(lsd::is_copy_constructible<void(*)()>::value)
    LSD_TESTC(lsd::is_copy_constructible<void(&)()>::value)
    LSD_TESTC(!lsd::is_copy_constructible<int[]>::value)
    LSD_TESTC(!lsd::is_copy_constructible<int[3]>::value)

    LSD_TESTC(!lsd::is_copy_constructible<a>::value)
    LSD_TESTC(!lsd::is_copy_constructible<a>::value)
    LSD_TESTC(!lsd::is_copy_constructible<a>::value)

    LSD_TESTC(lsd::is_copy_constructible<b>::value)
    LSD_TESTC(lsd::is_copy_constructible<b>::value)
    LSD_TESTC(lsd::is_copy_constructible<b>::value)

    LSD_TESTC(!lsd::is_copy_constructible<c>::value)
    LSD_TESTC(!lsd::is_copy_constructible<c>::value)
    LSD_TESTC(!lsd::is_copy_constructible<c>::value)

    LSD_TESTC(lsd::is_copy_constructible<d>::value)
    LSD_TESTC(!lsd::is_trivially_copy_constructible<d>::value)
    LSD_TESTC(!lsd::is_nothrow_copy_constructible<d>::value)
  }

  { // move_constructible
    struct a { a(a&&) = delete; };
    struct b {};
    struct c : a {};
    struct d { d(const d&) {}};
    struct e { e(e&&) noexcept(false) {}};

    auto lambda = []{};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

    LSD_TESTC(lsd::is_move_constructible<int>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<int>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<int>::value)

    LSD_TESTC(!lsd::is_move_constructible<int[]>::value)
    LSD_TESTC(!lsd::is_move_constructible<int[3]>::value)

    LSD_TESTC(lsd::is_move_constructible<const int>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<const int>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<const int>::value)

    LSD_TESTC(lsd::is_move_constructible<int&>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<int&>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<int&>::value)

    LSD_TESTC(lsd::is_move_constructible<const int&>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<const int&>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<const int&>::value)

    LSD_TESTC(lsd::is_move_constructible<int&&>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<int&&>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<int&&>::value)

    LSD_TESTC(lsd::is_move_constructible<const int&&>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<const int&&>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<const int&&>::value)

    LSD_TESTC(!lsd::is_move_constructible<void>::value)
    LSD_TESTC(!lsd::is_trivially_move_constructible<void>::value)
    LSD_TESTC(!lsd::is_nothrow_move_constructible<void>::value)

    LSD_TESTC(!lsd::is_move_constructible<void()>::value)
    LSD_TESTC(!lsd::is_trivially_move_constructible<void()>::value)
    LSD_TESTC(!lsd::is_nothrow_move_constructible<void()>::value)

    LSD_TESTC(!lsd::is_move_constructible<void()&>::value)
    LSD_TESTC(!lsd::is_trivially_move_constructible<void()&>::value)
    LSD_TESTC(!lsd::is_nothrow_move_constructible<void()&>::value)

    LSD_TESTC(!lsd::is_move_constructible<void()const>::value)
    LSD_TESTC(!lsd::is_trivially_move_constructible<void()const>::value)
    LSD_TESTC(!lsd::is_nothrow_move_constructible<void()const>::value)

    LSD_TESTC(lsd::is_move_constructible<lsd::nullptr_t>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<lsd::nullptr_t>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<lsd::nullptr_t>::value)

    LSD_TESTC(lsd::is_move_constructible<decltype(lambda)>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<decltype(lambda)>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<decltype(lambda)>::value)

    LSD_TESTC(lsd::is_move_constructible<decltype(lambda_capture)>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<decltype(lambda_capture)>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<decltype(lambda_capture)>::value)

    LSD_TESTC(lsd::is_move_constructible<decltype(lambda_capture_default)>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<decltype(lambda_capture_default)>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<decltype(lambda_capture_default)>::value)

    LSD_TESTC(lsd::is_move_constructible<void(*)()>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<void(*)()>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<void(*)()>::value)

    LSD_TESTC(lsd::is_move_constructible<void(&)()>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<void(&)()>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<void(&)()>::value)

    LSD_TESTC(!lsd::is_move_constructible<a>::value)
    LSD_TESTC(!lsd::is_trivially_move_constructible<a>::value)
    LSD_TESTC(!lsd::is_nothrow_move_constructible<a>::value)

    LSD_TESTC(lsd::is_move_constructible<b>::value)
    LSD_TESTC(lsd::is_trivially_move_constructible<b>::value)
    LSD_TESTC(lsd::is_nothrow_move_constructible<b>::value)

    LSD_TESTC(!lsd::is_move_constructible<c>::value)

    LSD_TESTC(lsd::is_move_constructible<d>::value)
    LSD_TESTC(!lsd::is_trivially_move_constructible<d>::value)
    LSD_TESTC(!lsd::is_nothrow_move_constructible<d>::value)

    LSD_TESTC(lsd::is_move_constructible<e>::value)
    LSD_TESTC(!lsd::is_trivially_move_constructible<e>::value)
    LSD_TESTC(!lsd::is_nothrow_move_constructible<e>::value)
  }

  { // assignable
    LSD_TESTC(!lsd::is_assignable<int, int>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<int, int>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<int, int>::value)

    LSD_TESTC(!lsd::is_assignable<int[], int[]>::value)
    LSD_TESTC(!lsd::is_assignable<int[], int[3]>::value)
    LSD_TESTC(!lsd::is_assignable<int[3], int[3]>::value)

    LSD_TESTC(!lsd::is_assignable<const int, int>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<const int, int>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<const int, int>::value)

    LSD_TESTC(!lsd::is_assignable<int, int&>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<int, int&>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<int, int&>::value)

    LSD_TESTC(lsd::is_assignable<int&, int>::value)
    LSD_TESTC(lsd::is_trivially_assignable<int&, int>::value)
    LSD_TESTC(lsd::is_nothrow_assignable<int&, int>::value)

    LSD_TESTC(lsd::is_assignable<int&, double>::value)
    LSD_TESTC(lsd::is_trivially_assignable<int&, double>::value)
    LSD_TESTC(lsd::is_nothrow_assignable<int&, double>::value)

    LSD_TESTC(lsd::is_assignable<int&, char>::value)
    LSD_TESTC(lsd::is_trivially_assignable<int&, char>::value)
    LSD_TESTC(lsd::is_nothrow_assignable<int&, char>::value)

    LSD_TESTC(lsd::is_assignable<int&, int&>::value)
    LSD_TESTC(lsd::is_trivially_assignable<int&, int&>::value)
    LSD_TESTC(lsd::is_nothrow_assignable<int&, int&>::value)

    LSD_TESTC(!lsd::is_assignable<const int&, int>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<const int&, int>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<const int&, int>::value)

    LSD_TESTC(!std::is_assignable<const int&, int&&>::value)
    LSD_TESTC(!std::is_trivially_assignable<const int&, int&&>::value)
    LSD_TESTC(!std::is_nothrow_assignable<const int&, int&&>::value)

    LSD_TESTC(!lsd::is_assignable<int&&, int>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<int&&, int>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<int&&, int>::value)

    LSD_TESTC(!lsd::is_assignable<int&&, int&>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<int&&, int&>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<int&&, int&>::value)

    LSD_TESTC(!lsd::is_assignable<int&&, int&&>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<int&&, int&&>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<int&&, int&&>::value)


    LSD_TESTC(!lsd::is_assignable<void, void>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void, void>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void, void>::value)

    LSD_TESTC(!lsd::is_assignable<void, int>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void, int>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void, int>::value)

    LSD_TESTC(!lsd::is_assignable<void*(&), int>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void*(&), int>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void*(&), int>::value)

    LSD_TESTC(!lsd::is_assignable<void*, std::nullptr_t>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void*, std::nullptr_t>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void*, std::nullptr_t>::value)

    LSD_TESTC(!lsd::is_assignable<void*(&&), std::nullptr_t>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void*(&&), std::nullptr_t>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void*(&&), std::nullptr_t>::value)

    LSD_TESTC(!lsd::is_assignable<std::nullptr_t, std::nullptr_t>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<std::nullptr_t, std::nullptr_t>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<std::nullptr_t, std::nullptr_t>::value)

    LSD_TESTC(lsd::is_assignable<std::nullptr_t&, std::nullptr_t>::value)
    LSD_TESTC(lsd::is_trivially_assignable<std::nullptr_t&, std::nullptr_t>::value)
    LSD_TESTC(lsd::is_nothrow_assignable<std::nullptr_t&, std::nullptr_t>::value)


    LSD_TESTC(!lsd::is_assignable<void(), void()>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void(), void()>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void(), void()>::value)

    LSD_TESTC(!lsd::is_assignable<void()&&, void()>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void()&&, void()>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void()&&, void()>::value)

    LSD_TESTC(!lsd::is_assignable<void()&&, void()volatile>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void()&&, void()volatile>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void()&&, void()volatile>::value)

    LSD_TESTC(!lsd::is_assignable<void(&)(), void()>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void(&)(), void()>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void(&)(), void()>::value)

    LSD_TESTC(!lsd::is_assignable<void(&&)(), void()>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void(&&)(), void()>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void(&&)(), void()>::value)

    LSD_TESTC(!lsd::is_assignable<void(*)(), void()>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<void(*)(), void()>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<void(*)(), void()>::value)

    LSD_TESTC(lsd::is_assignable<void(*&)(), void()>::value)
    LSD_TESTC(lsd::is_trivially_assignable<void(*&)(), void()>::value)
    LSD_TESTC(lsd::is_nothrow_assignable<void(*&)(), void()>::value)

    LSD_TESTC(lsd::is_assignable<void(*&)(), void(*)()>::value)
    LSD_TESTC(lsd::is_trivially_assignable<void(*&)(), void(*)()>::value)
    LSD_TESTC(lsd::is_nothrow_assignable<void(*&)(), void(*)()>::value)

    auto lambda = []{};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

//# if LSD_CXX_VER < 20
//    LSD_TESTC(!lsd::is_assignable<decltype(lambda), decltype(lambda)>::value)
//    LSD_TESTC(!lsd::is_trivially_assignable<decltype(lambda), decltype(lambda)>::value)
//    LSD_TESTC(!lsd::is_nothrow_assignable<decltype(lambda), decltype(lambda)>::value)
//# else
//    LSD_TESTC(lsd::is_assignable<decltype(lambda), decltype(lambda)>::value)
//    LSD_TESTC(lsd::is_trivially_assignable<decltype(lambda), decltype(lambda)>::value)
//    LSD_TESTC(lsd::is_nothrow_assignable<decltype(lambda), decltype(lambda)>::value)
//# endif

    LSD_TESTC(!lsd::is_assignable<decltype(lambda_capture), decltype(lambda_capture)>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<decltype(lambda_capture), decltype(lambda_capture)>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<decltype(lambda_capture), decltype(lambda_capture)>::value)

    // MSVC bug
//    LSD_TESTC(!lsd::is_assignable<decltype(lambda_capture_default), decltype(lambda_capture_default)>::value)
//    LSD_TESTC(!lsd::is_trivially_assignable<decltype(lambda_capture_default), decltype(lambda_capture_default)>::value)
//    LSD_TESTC(!lsd::is_nothrow_assignable<decltype(lambda_capture_default), decltype(lambda_capture_default)>::value)

    struct a { a& operator=(const a&) = delete; };
    struct b {};
    struct c : a {};
    struct d { d& operator=(const d&) noexcept(true) {return *this;}};
    struct e { e& operator=(const e&) noexcept(false) {return *this;}};

    LSD_TESTC(!lsd::is_assignable<a, a>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<a, a>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<a, a>::value)

    LSD_TESTC(lsd::is_assignable<b, b>::value)
    LSD_TESTC(lsd::is_trivially_assignable<b, b>::value)
    LSD_TESTC(lsd::is_nothrow_assignable<b, b>::value)

    LSD_TESTC(!lsd::is_assignable<c, c>::value)
    LSD_TESTC(!lsd::is_trivially_assignable<c, c>::value)
    LSD_TESTC(!lsd::is_nothrow_assignable<c,c >::value)

    LSD_TESTC(std::is_assignable<d, d>::value)
    LSD_TESTC(!std::is_trivially_assignable<d, d>::value)
    LSD_TESTC(std::is_nothrow_assignable<d, d>::value)

    LSD_TESTC(std::is_assignable<e, e>::value)
    LSD_TESTC(!std::is_trivially_assignable<e, e>::value)
    LSD_TESTC(!std::is_nothrow_assignable<e, e>::value)
  }

  { // copy_assignable
    LSD_TESTC(lsd::is_copy_assignable<int>::value)
    LSD_TESTC(lsd::is_copy_assignable<int&>::value)
    LSD_TESTC(lsd::is_copy_assignable<int&&>::value)
    LSD_TESTC(!lsd::is_copy_assignable<const int>::value)
    LSD_TESTC(!lsd::is_copy_assignable<const int&>::value)
    LSD_TESTC(!lsd::is_copy_assignable<const int&&>::value)
    LSD_TESTC(!lsd::is_copy_assignable<int[]>::value)
    LSD_TESTC(!lsd::is_copy_assignable<int[3]>::value)



    LSD_TESTC(!lsd::is_copy_assignable<void>::value)
    LSD_TESTC(!lsd::is_copy_assignable<void()>::value)
    LSD_TESTC(!lsd::is_copy_assignable<void()&>::value)
    LSD_TESTC(!lsd::is_copy_assignable<void()volatile&>::value)
    LSD_TESTC(lsd::is_copy_assignable<void(*)()>::value)
    LSD_TESTC(!lsd::is_copy_assignable<void(&)()>::value)
    LSD_TESTC(lsd::is_copy_assignable<lsd::nullptr_t>::value)

    auto lambda = []{};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

//# if LSD_CXX_VER < 20
//    LSD_TESTC(!std::is_copy_assignable<decltype(lambda)>::value)
//    LSD_TESTC(!lsd::is_copy_assignable<decltype(lambda_capture)>::value)
//    LSD_TESTC(!lsd::is_copy_assignable<decltype(lambda_capture_default)>::value)
//# else
//    LSD_TESTC(std::is_copy_assignable<decltype(lambda)>::value)
//# endif


    struct a { a& operator=(const a&) = delete; };
    struct b {};
    struct c : a {};
    struct d { d& operator=(const d&) noexcept(true) {return *this;}};
    struct e { e& operator=(const e&) noexcept(false) {return *this;}};

    LSD_TESTC(!lsd::is_copy_assignable<a>::value)
    LSD_TESTC(!lsd::is_trivially_copy_assignable<a>::value)
    LSD_TESTC(!lsd::is_nothrow_copy_assignable<a>::value)

    LSD_TESTC(lsd::is_copy_assignable<b>::value)
    LSD_TESTC(lsd::is_trivially_copy_assignable<b>::value)
    LSD_TESTC(lsd::is_nothrow_copy_assignable<b>::value)

    LSD_TESTC(!lsd::is_copy_assignable<c>::value)
    LSD_TESTC(!lsd::is_trivially_copy_assignable<c>::value)
    LSD_TESTC(!lsd::is_nothrow_copy_assignable<c>::value)

    LSD_TESTC(lsd::is_copy_assignable<d>::value)
    LSD_TESTC(!lsd::is_trivially_copy_assignable<d>::value)
    LSD_TESTC(lsd::is_nothrow_copy_assignable<d>::value)

    LSD_TESTC(lsd::is_copy_assignable<e>::value)
    LSD_TESTC(!lsd::is_trivially_copy_assignable<e>::value)
    LSD_TESTC(!lsd::is_nothrow_copy_assignable<e>::value)
  }

  { // move_assignable
    LSD_TESTC(lsd::is_move_assignable<int>::value)
    LSD_TESTC(lsd::is_move_assignable<int&>::value)
    LSD_TESTC(lsd::is_move_assignable<int&&>::value)
    LSD_TESTC(!lsd::is_move_assignable<const int>::value)
    LSD_TESTC(!lsd::is_move_assignable<const int&>::value)
    LSD_TESTC(!lsd::is_move_assignable<const int&&>::value)
    LSD_TESTC(!lsd::is_move_assignable<int[]>::value)
    LSD_TESTC(!lsd::is_move_assignable<int[3]>::value)


    LSD_TESTC(!lsd::is_move_assignable<void>::value)
    LSD_TESTC(!lsd::is_move_assignable<void()>::value)
    LSD_TESTC(!lsd::is_move_assignable<void()&>::value)
    LSD_TESTC(!lsd::is_move_assignable<void()volatile&>::value)
    LSD_TESTC(lsd::is_move_assignable<void(*)()>::value)
    LSD_TESTC(!lsd::is_move_assignable<void(&)()>::value)
    LSD_TESTC(lsd::is_move_assignable<lsd::nullptr_t>::value)

    auto lambda = []{};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

//# if LSD_CXX_VER < 20
//    LSD_TESTC(!std::is_move_assignable<decltype(lambda)>::value)
//    LSD_TESTC(!lsd::is_move_assignable<decltype(lambda_capture)>::value)
//    LSD_TESTC(!lsd::is_move_assignable<decltype(lambda_capture_default)>::value)
//# else
//    LSD_TESTC(std::is_move_assignable<decltype(lambda)>::value)
//# endif


    struct a { a& operator=(const a&) = delete; };
    struct b {};
    struct c : a {};
    struct d { d& operator=(const d&) noexcept(true) {return *this;}};
    struct e { e& operator=(const e&) noexcept(false) {return *this;}};

    LSD_TESTC(!lsd::is_move_assignable<a>::value)
    LSD_TESTC(!lsd::is_trivially_move_assignable<a>::value)
    LSD_TESTC(!lsd::is_nothrow_move_assignable<a>::value)

    LSD_TESTC(lsd::is_move_assignable<b>::value)
    LSD_TESTC(lsd::is_trivially_move_assignable<b>::value)
    LSD_TESTC(lsd::is_nothrow_move_assignable<b>::value)

    LSD_TESTC(!lsd::is_move_assignable<c>::value)
    LSD_TESTC(!lsd::is_trivially_move_assignable<c>::value)
    LSD_TESTC(!lsd::is_nothrow_move_assignable<c>::value)

    LSD_TESTC(lsd::is_move_assignable<d>::value)
    LSD_TESTC(!lsd::is_trivially_move_assignable<d>::value)
    LSD_TESTC(lsd::is_nothrow_move_assignable<d>::value)

    LSD_TESTC(lsd::is_move_assignable<e>::value)
    LSD_TESTC(!lsd::is_trivially_move_assignable<e>::value)
    LSD_TESTC(!lsd::is_nothrow_move_assignable<e>::value)

  }

  { // destructible

  }

  { // has_virtual_destructor
    struct a {};
    struct b {virtual void foo() {}};
    struct c {virtual ~c() = default; };

    LSD_TESTC(!lsd::has_virtual_destructor<void>::value)
    LSD_TESTC(!lsd::has_virtual_destructor<void()>::value)
    LSD_TESTC(!lsd::has_virtual_destructor<void()const &>::value)
    LSD_TESTC(!lsd::has_virtual_destructor<void(&)()>::value)
    LSD_TESTC(lsd::has_virtual_destructor<std::iostream>::value)
    LSD_TESTC(!lsd::has_virtual_destructor<a>::value)
    LSD_TESTC(!lsd::has_virtual_destructor<b>::value)
    LSD_TESTC(lsd::has_virtual_destructor<c>::value)
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


  {
    struct s1 {};
    struct s2 : s1 {};
    struct s3 { virtual ~s3() {} };
    struct s4 { virtual void foo() {}};
    struct s5 { int x : 3; };
    struct s6 { s1 s1_;};

    LSD_TESTC(lsd::is_empty<s1>::value)
    LSD_TESTC(lsd::is_empty<s2>::value)
    LSD_TESTC(!lsd::is_empty<s3>::value)
    LSD_TESTC(!lsd::is_empty<s4>::value)
    LSD_TESTC(!lsd::is_empty<s5>::value)
    LSD_TESTC(!lsd::is_empty<s6>::value)

    LSD_TESTC(!lsd::is_polymorphic<s1>::value)
    LSD_TESTC(!lsd::is_polymorphic<s2>::value)
    LSD_TESTC(lsd::is_polymorphic<s3>::value)
    LSD_TESTC(lsd::is_polymorphic<s4>::value)
    LSD_TESTC(!lsd::is_polymorphic<s5>::value)
    LSD_TESTC(!lsd::is_polymorphic<s6>::value)
  }

  { // is_abstract
    LSD_TESTC(!lsd::is_abstract<int>::value)
    LSD_TESTC(!lsd::is_abstract<void>::value)
    LSD_TESTC(!lsd::is_abstract<void()>::value)
    LSD_TESTC(!lsd::is_abstract<void()&&>::value)
    LSD_TESTC(!lsd::is_abstract<void()&&>::value)
    LSD_TESTC(!lsd::is_abstract<int[]>::value)
    LSD_TESTC(!lsd::is_abstract<int[3]>::value)

    auto lambda = [](){};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};
    LSD_TESTC(!lsd::is_abstract<decltype(lambda)>::value)
    LSD_TESTC(!lsd::is_abstract<decltype(lambda_capture)>::value)
    LSD_TESTC(!lsd::is_abstract<decltype(lambda_capture_default)>::value)

    struct a {};
    struct b { virtual void foo() = 0; };
    LSD_TESTC(!lsd::is_abstract<a>::value)
    LSD_TESTC(lsd::is_abstract<b>::value)
  }

  { // is_final (std)
# if LSD_CXX_VER >= 14

# endif
  }

  { // is_aggregate (std)
# if LSD_CXX_VER >= 17

# endif
  }

  { // is_signed
    LSD_TESTC(lsd::is_signed<char>::value)
    LSD_TESTC(lsd::is_signed<signed char>::value)
    LSD_TESTC(lsd::is_signed<short>::value)
    LSD_TESTC(lsd::is_signed<int>::value)
    LSD_TESTC(lsd::is_signed<long>::value)
    LSD_TESTC(lsd::is_signed<long long>::value)
    LSD_TESTC(lsd::is_signed<float>::value)
    LSD_TESTC(lsd::is_signed<double>::value)
    LSD_TESTC(lsd::is_signed<long double>::value)
//    LSD_TESTC(lsd::is_signed<wchar_t>::value) unknown?

//    LSD_TESTC(lsd::is_signed<std::int8_t>::value)   optional
//    LSD_TESTC(lsd::is_signed<std::int16_t>::value)
//    LSD_TESTC(lsd::is_signed<std::int32_t>::value)
//    LSD_TESTC(lsd::is_signed<std::int64_t>::value)
    LSD_TESTC(lsd::is_signed<std::int_fast8_t>::value)
    LSD_TESTC(lsd::is_signed<std::int_fast16_t>::value)
    LSD_TESTC(lsd::is_signed<std::int_fast32_t>::value)
    LSD_TESTC(lsd::is_signed<std::int_fast64_t>::value)
    LSD_TESTC(lsd::is_signed<std::int_least8_t>::value)
    LSD_TESTC(lsd::is_signed<std::int_least16_t>::value)
    LSD_TESTC(lsd::is_signed<std::int_least32_t>::value)
    LSD_TESTC(lsd::is_signed<std::int_least64_t>::value)
    LSD_TESTC(lsd::is_signed<std::intmax_t>::value)
//    LSD_TESTC(lsd::is_signed<std::intptr_t>::value)  optional


    LSD_TESTC(!lsd::is_signed<void>::value)
    LSD_TESTC(!lsd::is_signed<void*>::value)
    LSD_TESTC(!lsd::is_signed<int*>::value)
    LSD_TESTC(!lsd::is_signed<int[]>::value)
    LSD_TESTC(!lsd::is_signed<int[3]>::value)
    LSD_TESTC(!lsd::is_signed<void()>::value)
    LSD_TESTC(!lsd::is_signed<void()&&>::value)
    LSD_TESTC(!lsd::is_signed<void(*)()>::value)
    LSD_TESTC(!lsd::is_signed<lsd::nullptr_t>::value)
# if LSD_CXX_VER >= 20
    LSD_TESTC(!lsd::is_signed<char8_t>::value)
# endif
    LSD_TESTC(!lsd::is_signed<char16_t>::value)
    LSD_TESTC(!lsd::is_signed<char32_t>::value)
    LSD_TESTC(!lsd::is_signed<unsigned char>::value)
    LSD_TESTC(!lsd::is_signed<unsigned short>::value)
    LSD_TESTC(!lsd::is_signed<unsigned int>::value)
    LSD_TESTC(!lsd::is_signed<unsigned long>::value)
    LSD_TESTC(!lsd::is_signed<unsigned long long>::value)
    LSD_TESTC(!lsd::is_signed<std::uint_fast8_t>::value)
    LSD_TESTC(!lsd::is_signed<std::uint_fast16_t>::value)
    LSD_TESTC(!lsd::is_signed<std::uint_fast32_t>::value)
    LSD_TESTC(!lsd::is_signed<std::uint_fast64_t>::value)
    LSD_TESTC(!lsd::is_signed<std::uint_least8_t>::value)
    LSD_TESTC(!lsd::is_signed<std::uint_least16_t>::value)
    LSD_TESTC(!lsd::is_signed<std::uint_least32_t>::value)
    LSD_TESTC(!lsd::is_signed<std::uint_least64_t>::value)
    LSD_TESTC(!lsd::is_signed<std::uintmax_t>::value)

    struct a {};
    struct b { operator int() { return 0; }};
    enum e {};
    enum class f {};

    LSD_TESTC(!lsd::is_signed<a>::value)
    LSD_TESTC(!lsd::is_signed<b>::value)
    LSD_TESTC(!lsd::is_signed<e>::value)
    LSD_TESTC(!lsd::is_signed<f>::value)
  }

  { // is_unsigned

# if LSD_CXX_VER >= 20
    LSD_TESTC(lsd::is_unsigned<char8_t>::value)
# endif
    LSD_TESTC(lsd::is_unsigned<char16_t>::value)
    LSD_TESTC(lsd::is_unsigned<char32_t>::value)
    LSD_TESTC(lsd::is_unsigned<unsigned char>::value)
    LSD_TESTC(lsd::is_unsigned<unsigned short>::value)
    LSD_TESTC(lsd::is_unsigned<unsigned int>::value)
    LSD_TESTC(lsd::is_unsigned<unsigned long>::value)
    LSD_TESTC(lsd::is_unsigned<unsigned long long>::value)
    LSD_TESTC(lsd::is_unsigned<std::uint_fast8_t>::value)
    LSD_TESTC(lsd::is_unsigned<std::uint_fast16_t>::value)
    LSD_TESTC(lsd::is_unsigned<std::uint_fast32_t>::value)
    LSD_TESTC(lsd::is_unsigned<std::uint_fast64_t>::value)
    LSD_TESTC(lsd::is_unsigned<std::uint_least8_t>::value)
    LSD_TESTC(lsd::is_unsigned<std::uint_least16_t>::value)
    LSD_TESTC(lsd::is_unsigned<std::uint_least32_t>::value)
    LSD_TESTC(lsd::is_unsigned<std::uint_least64_t>::value)
    LSD_TESTC(lsd::is_unsigned<std::uintmax_t>::value)

    LSD_TESTC(!lsd::is_unsigned<char>::value)
    LSD_TESTC(!lsd::is_unsigned<signed char>::value)
    LSD_TESTC(!lsd::is_unsigned<short>::value)
    LSD_TESTC(!lsd::is_unsigned<int>::value)
    LSD_TESTC(!lsd::is_unsigned<long>::value)
    LSD_TESTC(!lsd::is_unsigned<long long>::value)
    LSD_TESTC(!lsd::is_unsigned<float>::value)
    LSD_TESTC(!lsd::is_unsigned<double>::value)
    LSD_TESTC(!lsd::is_unsigned<long double>::value)

    LSD_TESTC(!lsd::is_unsigned<std::int_fast8_t>::value)
    LSD_TESTC(!lsd::is_unsigned<std::int_fast16_t>::value)
    LSD_TESTC(!lsd::is_unsigned<std::int_fast32_t>::value)
    LSD_TESTC(!lsd::is_unsigned<std::int_fast64_t>::value)
    LSD_TESTC(!lsd::is_unsigned<std::int_least8_t>::value)
    LSD_TESTC(!lsd::is_unsigned<std::int_least16_t>::value)
    LSD_TESTC(!lsd::is_unsigned<std::int_least32_t>::value)
    LSD_TESTC(!lsd::is_unsigned<std::int_least64_t>::value)
    LSD_TESTC(!lsd::is_unsigned<std::intmax_t>::value)


    LSD_TESTC(!lsd::is_unsigned<void>::value)
    LSD_TESTC(!lsd::is_unsigned<void*>::value)
    LSD_TESTC(!lsd::is_unsigned<int*>::value)
    LSD_TESTC(!lsd::is_unsigned<int[]>::value)
    LSD_TESTC(!lsd::is_unsigned<int[3]>::value)
    LSD_TESTC(!lsd::is_unsigned<void()>::value)
    LSD_TESTC(!lsd::is_unsigned<void()&&>::value)
    LSD_TESTC(!lsd::is_unsigned<void(*)()>::value)
    LSD_TESTC(!lsd::is_unsigned<lsd::nullptr_t>::value)

    struct a {};
    struct b { operator int() { return 0; }};
    enum e {};
    enum class f {};

    LSD_TESTC(!lsd::is_unsigned<a>::value)
    LSD_TESTC(!lsd::is_unsigned<b>::value)
    LSD_TESTC(!lsd::is_unsigned<e>::value)
    LSD_TESTC(!lsd::is_unsigned<f>::value)
  }

  { // is_scoped_enum
    enum a {};
    enum b : char {};
    enum c : int {};
    enum d : long long {};
    enum e : std::size_t {};
    enum class f {};
    enum class g : char {};
    enum class h : int {};
    enum class i : long long {};
    enum class j : std::size_t {};

    LSD_TESTC(!lsd::is_scoped_enum<a>::value)
    LSD_TESTC(!lsd::is_scoped_enum<b>::value)
    LSD_TESTC(!lsd::is_scoped_enum<c>::value)
    LSD_TESTC(!lsd::is_scoped_enum<d>::value)
    LSD_TESTC(!lsd::is_scoped_enum<e>::value)
    LSD_TESTC(lsd::is_scoped_enum<f>::value)
    LSD_TESTC(lsd::is_scoped_enum<g>::value)
    LSD_TESTC(lsd::is_scoped_enum<h>::value)
    LSD_TESTC(lsd::is_scoped_enum<i>::value)
    LSD_TESTC(lsd::is_scoped_enum<j>::value)

    LSD_TESTC(!lsd::is_scoped_enum<void>::value)
    LSD_TESTC(!lsd::is_scoped_enum<lsd::nullptr_t>::value)
    LSD_TESTC(!lsd::is_scoped_enum<void()>::value)
    LSD_TESTC(!lsd::is_scoped_enum<void()&&>::value)
    LSD_TESTC(!lsd::is_scoped_enum<void(*)()>::value)
    LSD_TESTC(!lsd::is_scoped_enum<int[]>::value)
    LSD_TESTC(!lsd::is_scoped_enum<int[3]>::value)
  }

  { // alignment_of

  }

  { // rank
    struct s {};
    auto lambda = [](){};

    LSD_TESTC(lsd::rank<int>::value == 0)
    LSD_TESTC(lsd::rank<void>::value == 0)
    LSD_TESTC(lsd::rank<lsd::nullptr_t>::value == 0)
    LSD_TESTC(lsd::rank<s>::value == 0)
    LSD_TESTC(lsd::rank<decltype(lambda)>::value == 0)
    LSD_TESTC(lsd::rank<void()>::value == 0)
    LSD_TESTC(lsd::rank<void()&&>::value == 0)

    LSD_TESTC(lsd::rank<int(*)[1]>::value == 0)
    LSD_TESTC(lsd::rank<int(&)[1]>::value == 0)
    LSD_TESTC(lsd::rank<int[]>::value == 1)
    LSD_TESTC(lsd::rank<int[][1]>::value == 2)
    LSD_TESTC(lsd::rank<int[][1][2][3][4]>::value == 5)
    LSD_TESTC(lsd::rank<int[][1][2][3][4]>::value == 5)
  }

  { // extent

  }

  { // is_base_of
    struct A {};
    struct B1 : public A {};
    struct B2 : protected A {};
    struct B3 : private A {};
    struct C {};

    LSD_TESTC(lsd::is_base_of<A, A>::value)
    LSD_TESTC(lsd::is_base_of<A, B1>::value)
    LSD_TESTC(lsd::is_base_of<A, B2>::value)
    LSD_TESTC(lsd::is_base_of<A, B3>::value)
    LSD_TESTC(!lsd::is_base_of<A, C>::value)

    LSD_TESTC(!lsd::is_base_of<B1, A>::value)
    LSD_TESTC(!lsd::is_base_of<B2, A>::value)
    LSD_TESTC(!lsd::is_base_of<B3, A>::value)

    LSD_TESTC(!lsd::is_base_of<A, void>::value)
    LSD_TESTC(!lsd::is_base_of<void, void>::value)
    LSD_TESTC(!lsd::is_base_of<void, void*>::value)
    LSD_TESTC(!lsd::is_base_of<void*, void*>::value)
    LSD_TESTC(!lsd::is_base_of<void()&&, int*>::value)

    LSD_TESTC(lsd::is_public_base_of<A, A>::value)
    LSD_TESTC(lsd::is_public_base_of<A, B1>::value)
    LSD_TESTC(!lsd::is_public_base_of<A, B2>::value)
    LSD_TESTC(!lsd::is_public_base_of<A, B3>::value)
    LSD_TESTC(!lsd::is_public_base_of<A, C>::value)

    LSD_TESTC(!lsd::is_public_base_of<B1, A>::value)
    LSD_TESTC(!lsd::is_public_base_of<B2, A>::value)
    LSD_TESTC(!lsd::is_public_base_of<B3, A>::value)

    LSD_TESTC(!lsd::is_public_base_of<A, void>::value)
    LSD_TESTC(!lsd::is_public_base_of<void, void>::value)
    LSD_TESTC(!lsd::is_public_base_of<void, void*>::value)
    LSD_TESTC(!lsd::is_public_base_of<void*, void*>::value)
    LSD_TESTC(!lsd::is_public_base_of<void()&&, int*>::value)
  }

  { // convertible

  }

  { // aligned_storage (std)

  }

  { // aligned_union

  }

  { // remove_cvref

  }

  { // invoke_result
    using x = lsd::invoke_result<int>;
    using y = lsd::invoke_result<void()&&, lsd::nullptr_t, void()>;

    struct foo {};
    struct incomplete;

    LSD_TESTC(lsd::is_void<lsd::invoke_result_t<void()>>::value)
    LSD_TESTC(lsd::is_void<lsd::invoke_result_t<void(*)()>>::value)
    LSD_TESTC(lsd::is_void<lsd::invoke_result_t<void(foo::*)(), foo&>>::value)
    LSD_TESTC(lsd::is_void<lsd::invoke_result_t<void(foo::*)(), foo*>>::value)
# if LSD_CXX_VER >= 17
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<void(foo::*)(), foo>, std::invoke_result_t<void(foo::*)(), foo>>::value)
# endif


    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<int()>, int>::value)
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<foo()>, foo>::value)
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<void(incomplete[]), incomplete[3]>, void>::value)

# if LSD_CXX_VER >= 14
    auto lambda = [](auto x) -> lsd::conditional_t<lsd::is_integral<decltype(x)>::value, int, float> { return 0; };
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<decltype(lambda), int>, int>::value)
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<decltype(lambda), float>, float>::value)
# endif

    struct c {
      int operator()();
      void operator()(int);
    };
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<c>, int>::value)
    LSD_TESTC(lsd::is_same<lsd::invoke_result_t<c, float>, void>::value)

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

  { // make_signed
    enum e1 : char {};
    enum e2 : int {};
    enum e3 : long long {};
    LSD_TESTC(lsd::is_same<int, lsd::make_signed_t<int>>::value)
    LSD_TESTC(lsd::is_same<signed int, lsd::make_signed_t<int>>::value)
    LSD_TESTC(lsd::is_same<int, lsd::make_signed_t<unsigned int>>::value)
    LSD_TESTC(lsd::is_same<signed char, lsd::make_signed_t<e1>>::value)
    LSD_TESTC(sizeof(lsd::make_signed_t<wchar_t>) == sizeof(wchar_t) &&
             lsd::is_not_same<lsd::make_signed_t<wchar_t>, wchar_t>::value)
    LSD_TESTC(sizeof(lsd::make_signed_t<unsigned long long>) == sizeof(unsigned long long) &&
             lsd::is_not_same<lsd::make_signed_t<unsigned long long>, unsigned long long>::value)
  }

  { // make_unsigned

  }

  { // conjunction
    LSD_TESTC(lsd::conjunction<>::value == true)
    LSD_TESTC(is_true_t<typename lsd::conjunction<>::type>::value == true)
    LSD_TESTC(lsd::conjunction<true_t, true_t, true_t>::value == true)
    LSD_TESTC(lsd::conjunction<false_t, false_t, false_t>::value == false)
    LSD_TESTC(lsd::conjunction<false_t, false_t, false_t, true_t>::value == false)
    LSD_TESTC(lsd::conjunction<false_t, void, void()&&>::value == false)
  }

  { // disjunction
    LSD_TESTC(lsd::disjunction<>::value == false)
    LSD_TESTC(is_false_t<typename lsd::disjunction<>::type>::value == true)
    LSD_TESTC(lsd::disjunction<false_t>::value == false)
    LSD_TESTC(lsd::disjunction<false_t, false_t>::value == false)
    LSD_TESTC(lsd::disjunction<false_t, false_t, false_t, true_t>::value == true)
    LSD_TESTC(lsd::disjunction<true_t>::value == true)
    LSD_TESTC(lsd::disjunction<i0, i0, i1, i2>::value == 1)
# if LSD_CXX_VER >= 14
    LSD_TESTC(lsd::disjunction_v<> == false)
    LSD_TESTC(lsd::disjunction_v<false_t> == false)
    LSD_TESTC(lsd::disjunction_v<false_t, false_t> == false)
    LSD_TESTC(lsd::disjunction_v<false_t, false_t, true_t> == true)
    LSD_TESTC(lsd::disjunction_v<i0, i0, i1, i2> == 1)
# endif
  }

  { // negation
    LSD_TESTC(lsd::negation<false_t>::value == true)
    LSD_TESTC(lsd::negation<true_t>::value == false)
# if LSD_CXX_VER >= 14
    LSD_TESTC(lsd::negation<false_t>::value == lsd::negation_v<false_t>)
    LSD_TESTC(lsd::negation<true_t>::value == lsd::negation_v<true_t>)
# endif
  }

  { // is_constant_evaluated (std)
# if LSD_CXX_VER >= 20

# endif
  }

  { // test 'test helpers'
    struct foo { using type = void; };
    struct bar {};

    LSD_TESTC(has_typename_type_t<foo>::value == true)
    LSD_TESTC(has_typename_type_t<bar>::value == false)
    LSD_TESTC(is_true_t<lsd::true_type>::value == true)
    LSD_TESTC(is_true_t<lsd::false_type>::value == false)
    LSD_TESTC(is_false_t<lsd::true_type>::value == false)
    LSD_TESTC(is_false_t<lsd::false_type>::value == true)
  }

  LSD_TEST_RETURN
}
