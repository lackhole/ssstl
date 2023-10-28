#include <cstdint>
#include <iostream>
#include <array>
#include <functional>
#include <type_traits>
#include <memory>

#include "ss/type_traits.h"
#include "ss_test.h"

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

template<typename T, ss::enable_if_t<std::is_integral<T>::value, int> = 0>
int test_enable_if();

template<typename T, ss::enable_if_t<std::is_floating_point<T>::value, int> = 0>
double test_enable_if();

void normal_function(){}
void variadic_function(...) {}
template<typename T> void template_function() {}
template<typename ...Args> void variadic_template_function(Args&&...) {}
template<typename ...Args> void variadic_template_variadic_function(Args&&..., ...) {}


template<typename T, typename = void>
struct has_typename_type : ss::false_type {};

template<typename T>
struct has_typename_type<T, ss::void_t<typename T::type>> : ss::true_type {};

template<typename T>
using has_typename_type_t = typename has_typename_type<T>::type;

template<typename T> using is_false_t = ss::is_same<T, ss::false_type>;
template<typename T> using is_true_t = ss::is_same<T, ss::true_type>;

using false_t = ss::false_type;
using true_t = ss::true_type;
using i0 = ss::integral_constant<int, 0>;
using i1 = ss::integral_constant<int, 1>;
using i2 = ss::integral_constant<int, 2>;
using i3 = ss::integral_constant<int, 3>;
using i4 = ss::integral_constant<int, 4>;
using i5 = ss::integral_constant<int, 5>;
using i6 = ss::integral_constant<int, 6>;
using i7 = ss::integral_constant<int, 7>;
using i8 = ss::integral_constant<int, 8>;
using i9 = ss::integral_constant<int, 9>;

int main() {
  SS_INIT_TEST("type_traits")
  std::cerr << "__cplusplus: " << __cplusplus << '\n';
  std::cerr << "NDEBUG: " << NDEBUG_DEFINED << '\n';


  // integral_constant
  SS_TESTC(std::is_same<ss::integral_constant<int, 3>::value_type, int>::value)
  SS_TESTC(std::integral_constant<int, 3>::value == ss::integral_constant<int, 3>::value)
  SS_TESTC(std::integral_constant<bool, true>::value == ss::bool_constant<true>::value)
  SS_TESTC(std::is_same<ss::integral_constant<bool, true>, ss::bool_constant<true>>::value)

  // type_identity
  SS_TESTC(std::is_same<ss::type_identity<int>::type, ss::type_identity_t<int>>::value)
  SS_TESTC(std::is_same<ss::type_identity_t<int>, int>::value)
  SS_TESTC(std::is_same<ss::type_identity_t<void()>, void()>::value)
  SS_TESTC(std::is_same<ss::type_identity_t<decltype(std::cout)>, decltype(std::cout)>::value)
  SS_TESTC(std::is_same<ss::type_identity_t<void()&&>, void()&&>::value)

  // void_t
  SS_TESTC(std::is_void<ss::void_t<>>::value)
  SS_TESTC(std::is_void<ss::void_t<int>>::value)
  SS_TESTC(std::is_void<ss::void_t<int, float, std::string>>::value)

  // enable_if
  SS_TESTC(std::is_same<decltype(test_enable_if<int>()), int>::value)
  SS_TESTC(std::is_same<decltype(test_enable_if<char>()), int>::value)
  SS_TESTC(std::is_same<decltype(test_enable_if<float>()), double>::value)
  SS_TESTC(std::is_same<decltype(test_enable_if<double>()), double>::value)

  // conditional
  SS_TESTC(std::is_same<ss::conditional<true, int, float>::type, ss::conditional_t<true, int, float>>::value)
  SS_TESTC(std::is_same<ss::conditional<true, int, float>::type, int>::value)
  SS_TESTC(std::is_same<ss::conditional<false, int, float>::type, float>::value)
  SS_TESTC(std::is_same<ss::conditional<false, int, void()&&>::type, void()&&>::value)

  // is_same
  SS_TESTC(ss::is_same<int, int>::value)
  SS_TESTC(ss::is_same<int, int>::value)
  SS_TESTC(ss::is_same<void()&, void()&>::value)
  SS_TESTC(!ss::is_same<void()&, void()&&>::value)
  SS_TESTC(!ss::is_same<int, int&>::value)
  SS_TESTC(!ss::is_same<int, volatile int>::value)
  SS_TESTC(!ss::is_same<int, const int>::value)

  // is_not_same
  SS_TESTC(!ss::is_not_same<int, int>::value)
  SS_TESTC(!ss::is_not_same<int, int>::value)
  SS_TESTC(!ss::is_not_same<void()&, void()&>::value)
  SS_TESTC(ss::is_not_same<void()&, void()&&>::value)
  SS_TESTC(ss::is_not_same<int, int&>::value)
  SS_TESTC(ss::is_not_same<int, volatile int>::value)
  SS_TESTC(ss::is_not_same<int, const int>::value)

  // is_const
  SS_TESTC(!ss::is_const<int>::value)
  SS_TESTC(ss::is_const<int const>::value)
  SS_TESTC(!ss::is_const<const int*>::value)
  SS_TESTC(ss::is_const<int* const>::value)
  SS_TESTC(!ss::is_const<void(int)const>::value)

  // is_volatile
  SS_TESTC(!ss::is_volatile<int>::value)
  SS_TESTC(ss::is_volatile<int volatile>::value)
  SS_TESTC(!ss::is_volatile<volatile int*>::value)
  SS_TESTC(ss::is_volatile<int* volatile>::value)
  SS_TESTC(!ss::is_volatile<void(int)volatile>::value)

  // remove_const
  SS_TESTC(ss::is_same<int, ss::remove_const_t<int>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_const_t<int const>>::value)
  SS_TESTC(ss::is_same<volatile int, ss::remove_const_t<volatile int const>>::value)
  SS_TESTC(ss::is_same<int*, ss::remove_const_t<int* const>>::value)

  // remove_volatile
  SS_TESTC(ss::is_same<int, ss::remove_volatile_t<int>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_volatile_t<int volatile>>::value)
  SS_TESTC(ss::is_same<const int, ss::remove_volatile_t<volatile int const>>::value)
  SS_TESTC(ss::is_same<int*, ss::remove_volatile_t<int* volatile>>::value)

  // remove_cv
  SS_TESTC(ss::is_same<int, ss::remove_cv_t<int>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_cv_t<int volatile>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_cv_t<int const>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_cv_t<volatile int const>>::value)
  SS_TESTC(ss::is_same<int*, ss::remove_cv_t<int* volatile const>>::value)

  // add_const
  SS_TESTC(ss::is_same<const int, ss::add_const_t<int>>::value)
  SS_TESTC(ss::is_same<const int, ss::add_const_t<int const>>::value)
  SS_TESTC(ss::is_same<const volatile int, ss::add_const_t<volatile int>>::value)
  SS_TESTC(ss::is_same<int* const, ss::add_const_t<int*>>::value)
  SS_TESTC(ss::is_same<void(), ss::add_const_t<void()>>::value)

  // add_volatile
  SS_TESTC(ss::is_same<volatile int, ss::add_volatile_t<int>>::value)
  SS_TESTC(ss::is_same<volatile int, ss::add_volatile_t<int volatile>>::value)
  SS_TESTC(ss::is_same<volatile const int, ss::add_volatile_t<int const>>::value)
  SS_TESTC(ss::is_same<int* volatile, ss::add_volatile_t<int*>>::value)
  SS_TESTC(ss::is_same<void(), ss::add_volatile_t<void()>>::value)

  // add_cv
  SS_TESTC(ss::is_same<volatile const int, ss::add_cv_t<int>>::value)
  SS_TESTC(ss::is_same<volatile const int, ss::add_cv_t<int volatile>>::value)
  SS_TESTC(ss::is_same<volatile const int, ss::add_cv_t<int const>>::value)
  SS_TESTC(ss::is_same<volatile const int, ss::add_cv_t<volatile int const>>::value)
  SS_TESTC(ss::is_same<int* volatile const , ss::add_cv_t<int* >>::value)
  SS_TESTC(ss::is_same<void(), ss::add_cv_t<void()>>::value)

  // remove_reference
  SS_TESTC(ss::is_same<int, ss::remove_reference_t<int>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_reference_t<int&>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_reference_t<int&&>>::value)
  SS_TESTC(ss::is_same<int*, ss::remove_reference_t<int*>>::value)
  SS_TESTC(ss::is_same<int*, ss::remove_reference_t<int*&>>::value)
  SS_TESTC(ss::is_same<int*, ss::remove_reference_t<int*&&>>::value)
  SS_TESTC(!ss::is_same<void(), ss::remove_reference_t<void()&>>::value)

  // add_lvalue_reference
  SS_TESTC(ss::is_same<int&, ss::add_lvalue_reference_t<int>>::value)
  SS_TESTC(ss::is_same<int&, ss::add_lvalue_reference_t<int&>>::value)
  SS_TESTC(ss::is_same<int&, ss::add_lvalue_reference_t<int&&>>::value)
  SS_TESTC(ss::is_same<void(&)(), ss::add_lvalue_reference_t<void()>>::value)
  SS_TESTC(ss::is_same<void, ss::add_lvalue_reference_t<void>>::value)

  // add_rvalue_reference
  SS_TESTC(ss::is_same<int&&, ss::add_rvalue_reference_t<int>>::value)
  SS_TESTC(ss::is_same<int&, ss::add_rvalue_reference_t<int&>>::value)
  SS_TESTC(ss::is_same<int&&, ss::add_rvalue_reference_t<int&&>>::value)
  SS_TESTC(ss::is_same<void(&&)(), ss::add_rvalue_reference_t<void()>>::value)
  SS_TESTC(ss::is_same<void()const, ss::add_rvalue_reference_t<void()const>>::value)
  SS_TESTC(ss::is_same<void, ss::add_rvalue_reference_t<void>>::value)

  { // declval

  }

  // remove_pointer
  SS_TESTC(ss::is_same<int, ss::remove_pointer_t<int>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_pointer_t<int*>>::value)
  SS_TESTC(ss::is_same<int*, ss::remove_pointer_t<int**>>::value)
  SS_TESTC(ss::is_same<void, ss::remove_pointer_t<void*>>::value)
  SS_TESTC(ss::is_same<void, ss::remove_pointer_t<void>>::value)
  SS_TESTC(ss::is_same<void(), ss::remove_pointer_t<void(*)()>>::value)
  SS_TESTC(ss::is_same<void()const, ss::remove_pointer_t<void()const>>::value)

  // add_pointer
  SS_TESTC(ss::is_same<int*, ss::add_pointer_t<int>>::value)
  SS_TESTC(ss::is_same<int**, ss::add_pointer_t<int*>>::value)
  SS_TESTC(ss::is_same<int***, ss::add_pointer_t<int**>>::value)
  SS_TESTC(ss::is_same<void**, ss::add_pointer_t<void*>>::value)
  SS_TESTC(ss::is_same<void*, ss::add_pointer_t<void>>::value)
  SS_TESTC(ss::is_same<void(**)(), ss::add_pointer_t<void(*)()>>::value)
  SS_TESTC(ss::is_same<void()const, ss::add_pointer_t<void()const>>::value)
  SS_TESTC(ss::is_same<void()const, ss::add_pointer<void()const>::type>::value)

  // remove_extent
  SS_TESTC(ss::is_same<int, ss::remove_extent_t<int>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_extent_t<int[]>>::value)
  SS_TESTC(ss::is_same<int[2], ss::remove_extent_t<int[1][2]>>::value)

  // remove_all_extents
  SS_TESTC(ss::is_same<int, ss::remove_all_extents_t<int>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_all_extents_t<int[]>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_all_extents_t<int[1][2]>>::value)
  SS_TESTC(ss::is_same<int, ss::remove_all_extents_t<int[1][2][3]>>::value)

  // is_void
  SS_TESTC(ss::is_void<void>::value)
  SS_TESTC(ss::is_void<volatile void>::value)
  SS_TESTC(ss::is_void<const void>::value)
  SS_TESTC(!ss::is_void<void()&&>::value)
  SS_TESTC(!ss::is_void<int>::value)

  // is_null_pointer
  SS_TESTC(ss::is_null_pointer<std::nullptr_t>::value)
  SS_TESTC(ss::is_null_pointer<decltype(nullptr)>::value)
  SS_TESTC(ss::is_null_pointer<volatile std::nullptr_t>::value)
  SS_TESTC(!ss::is_null_pointer<void()&&>::value)
  SS_TESTC(!ss::is_null_pointer<void>::value)

  { // is_integral
    enum e{};
    SS_TESTC(ss::is_integral<bool>::value)
    SS_TESTC(ss::is_integral<char>::value)
    SS_TESTC(ss::is_integral<signed char>::value)
    SS_TESTC(ss::is_integral<volatile unsigned char>::value)
    SS_TESTC(ss::is_integral<char16_t>::value)
    SS_TESTC(ss::is_integral<char32_t>::value)
    SS_TESTC(ss::is_integral<wchar_t>::value)
    SS_TESTC(ss::is_integral<short>::value)
    SS_TESTC(ss::is_integral<int>::value)
    SS_TESTC(ss::is_integral<long>::value)
    SS_TESTC(ss::is_integral<long long>::value)
    SS_TESTC(!ss::is_integral<e>::value)
    SS_TESTC(!ss::is_integral<float>::value)
    SS_TESTC(!ss::is_integral<int*>::value)
    SS_TESTC(!ss::is_integral<int()&&>::value)
  }

  // is_floating_point
  SS_TESTC(ss::is_floating_point<float>::value)
  SS_TESTC(ss::is_floating_point<double>::value)
  SS_TESTC(ss::is_floating_point<long double>::value)
  SS_TESTC(ss::is_floating_point<volatile float>::value)
  SS_TESTC(ss::is_floating_point<const float>::value)
  SS_TESTC(ss::is_floating_point<const volatile float>::value)
  SS_TESTC(!ss::is_floating_point<float*>::value)
  SS_TESTC(!ss::is_floating_point<int>::value)
  SS_TESTC(!ss::is_floating_point<float()>::value)

  // is_array
  SS_TESTC(ss::is_array<int[]>::value)
  SS_TESTC(ss::is_array<int[][3]>::value)
  SS_TESTC(ss::is_array<int[][3][4][5][6]>::value)
  SS_TESTC(!ss::is_array<int*>::value)
  SS_TESTC(!ss::is_array<std::array<int, 3>>::value)

  { // is_bounded_array
    SS_TESTC(!ss::is_bounded_array<int>::value)
    SS_TESTC(!ss::is_bounded_array<void()>::value)
    SS_TESTC(!ss::is_bounded_array<void()&&>::value)
    SS_TESTC(!ss::is_bounded_array<int[]>::value)
    SS_TESTC(!ss::is_bounded_array<int*>::value)
    SS_TESTC(!ss::is_bounded_array<int(&)[3]>::value)
    SS_TESTC(ss::is_bounded_array<int[3]>::value)
    SS_TESTC(!ss::is_bounded_array<int[][3]>::value)
    SS_TESTC(ss::is_bounded_array<int[2][3]>::value)
  }

  { // is_unbounded_array
    SS_TESTC(!ss::is_unbounded_array<int>::value)
    SS_TESTC(!ss::is_unbounded_array<void()>::value)
    SS_TESTC(!ss::is_unbounded_array<void()&&>::value)
    SS_TESTC(!ss::is_unbounded_array<int*>::value)
    SS_TESTC(!ss::is_unbounded_array<int(&)[]>::value)
    SS_TESTC(ss::is_unbounded_array<int[]>::value)
    SS_TESTC(!ss::is_unbounded_array<int[3]>::value)
    SS_TESTC(ss::is_unbounded_array<int[][3]>::value)
    SS_TESTC(!ss::is_unbounded_array<int[2][3]>::value)
  }

  { // is_enum
    enum e{};
    SS_TESTC(ss::is_enum<e>::value)
    SS_TESTC(ss::is_enum<volatile e>::value)
    SS_TESTC(ss::is_enum<const e>::value)
    SS_TESTC(ss::is_enum<const volatile e>::value)
    SS_TESTC(!ss::is_enum<e*>::value)
    SS_TESTC(!ss::is_enum<int>::value)
  }

  { // is_union
    union e{};
    SS_TESTC(ss::is_union<e>::value)
    SS_TESTC(ss::is_union<volatile e>::value)
    SS_TESTC(ss::is_union<const e>::value)
    SS_TESTC(ss::is_union<const volatile e>::value)
    SS_TESTC(!ss::is_union<e*>::value)
    SS_TESTC(!ss::is_union<int>::value)
  }

  { // is_class
    class c{}; struct s{};
    auto lambda = []()->void{};
    SS_TESTC(ss::is_class<c>::value)
    SS_TESTC(ss::is_class<s>::value)
    SS_TESTC(ss::is_class<decltype(lambda)>::value)
    SS_TESTC(ss::is_class<volatile c>::value)
    SS_TESTC(ss::is_class<const c>::value)
    SS_TESTC(ss::is_class<const volatile c>::value)
    SS_TESTC(!ss::is_class<c*>::value)
    SS_TESTC(!ss::is_class<int>::value)
    SS_TESTC(!ss::is_class<int()&&>::value)
  }

  { // is_pointer
    SS_TESTC(ss::is_pointer<void *>::value)
    SS_TESTC(ss::is_pointer<void ******>::value)
    SS_TESTC(ss::is_pointer<volatile void *>::value)
    SS_TESTC(ss::is_pointer<const void *>::value)
    SS_TESTC(ss::is_pointer<const volatile void *>::value)
    SS_TESTC(ss::is_pointer<void(*)()>::value)
    SS_TESTC(!ss::is_pointer<int>::value)
    SS_TESTC(!ss::is_pointer<int()&&>::value)
    SS_TESTC(!ss::is_pointer<int(&)()>::value)
    SS_TESTC(!ss::is_pointer<int()>::value)
  }

  { // is_lvalue_reference
    auto lambda = [](){};
    auto& lambda_ref = lambda;
    SS_TESTC(ss::is_lvalue_reference<int&>::value)
    SS_TESTC(ss::is_lvalue_reference<int(&)()>::value)
    SS_TESTC(ss::is_lvalue_reference<decltype(lambda_ref)>::value)
    SS_TESTC(ss::is_lvalue_reference<float &>::value)
    SS_TESTC(!ss::is_lvalue_reference<int>::value)
    SS_TESTC(!ss::is_lvalue_reference<int*>::value)
    SS_TESTC(!ss::is_lvalue_reference<int&&>::value)
    SS_TESTC(!ss::is_lvalue_reference<int(&&)()>::value)
    SS_TESTC(!ss::is_lvalue_reference<int()&&>::value)
  }

  { // is_rvalue_reference
    auto lambda = [](){};
    auto&& lambda_ref = std::move(lambda);
    SS_TESTC(ss::is_rvalue_reference<int&&>::value)
    SS_TESTC(ss::is_rvalue_reference<int(&&)()>::value)
    SS_TESTC(ss::is_rvalue_reference<decltype(lambda_ref)>::value)
    SS_TESTC(ss::is_rvalue_reference<float &&>::value)
    SS_TESTC(!ss::is_rvalue_reference<int>::value)
    SS_TESTC(!ss::is_rvalue_reference<int*>::value)
    SS_TESTC(!ss::is_rvalue_reference<int&>::value)
    SS_TESTC(!ss::is_rvalue_reference<int(&)()>::value)
    SS_TESTC(!ss::is_rvalue_reference<int()&&>::value)
  }

  { // is_reference
    auto lambda = [](){};
    auto&& lambda_ref = std::move(lambda);
    SS_TESTC(ss::is_reference<int&>::value)
    SS_TESTC(ss::is_reference<int&&>::value)
    SS_TESTC(ss::is_reference<int(&&)()>::value)
    SS_TESTC(ss::is_reference<int(&)()>::value)
    SS_TESTC(ss::is_reference<decltype(lambda_ref)>::value)
    SS_TESTC(ss::is_reference<float &&>::value)
    SS_TESTC(!ss::is_reference<int>::value)
    SS_TESTC(!ss::is_reference<int*>::value)
    SS_TESTC(!ss::is_reference<int()&&>::value)
  }

  {
    // is_function
    auto lambda = [](){};
    SS_TESTC(ss::is_function<decltype(normal_function)>::value)
    SS_TESTC(ss::is_function<decltype(template_function<void>)>::value)
    SS_TESTC(ss::is_function<decltype(variadic_function)>::value)
    SS_TESTC(ss::is_function<decltype(variadic_template_function<>)>::value)
    SS_TESTC(ss::is_function<decltype(variadic_template_variadic_function<>)>::value)
    SS_TESTC(ss::is_function<void()>::value)
    SS_TESTC(!ss::is_function<void(&)()>::value)
    SS_TESTC(!ss::is_function<void(*)()>::value)
    SS_TESTC(!ss::is_function<std::function<void()>>::value)
    SS_TESTC(!ss::is_function<decltype(lambda)>::value)
  }

  { // is_member_pointer
    struct s {
      int x;
      void mf() {}
      void cmf() const {}
      void rmf() && {}
    };

    SS_TESTC(ss::is_member_pointer<decltype(&s::x)>::value)
    SS_TESTC(ss::is_member_pointer<decltype(&s::mf)>::value)
    SS_TESTC(ss::is_member_pointer<decltype(&s::cmf)>::value)
    SS_TESTC(ss::is_member_pointer<decltype(&s::rmf)>::value)
    SS_TESTC(ss::is_member_pointer<decltype(&s::rmf)>::value)
    SS_TESTC(ss::is_member_pointer<int s::*>::value)
    SS_TESTC(!ss::is_member_pointer<int s::**>::value)
    SS_TESTC(ss::is_member_pointer<int(s::*)(void)>::value)
    SS_TESTC(!ss::is_member_pointer<int(s::**)(void)>::value)
    SS_TESTC(ss::is_member_pointer<int(s::*)(void)&>::value)
    SS_TESTC(ss::is_member_pointer<void(s::*)(void)volatile const&>::value)
    SS_TESTC(!ss::is_member_pointer<void*>::value)
    SS_TESTC(!ss::is_member_pointer<void(*)(int)>::value)
    SS_TESTC(!ss::is_member_pointer<void(&)(int)>::value)
    SS_TESTC(!ss::is_member_pointer<void(int)&&>::value)

    SS_TESTC(ss::is_member_function_pointer<int(s::*)(int)>::value)
    SS_TESTC(!ss::is_member_function_pointer<int(s::**)(int)>::value)
    SS_TESTC(!ss::is_member_function_pointer<int(s::*)>::value)

    SS_TESTC(!ss::is_member_object_pointer<int(s::*)(int)>::value)
    SS_TESTC(!ss::is_member_object_pointer<int(s::**)(int)>::value)
    SS_TESTC(ss::is_member_object_pointer<int(s::*)>::value)
  }

  { // is_arithmetic
    enum e {};
    SS_TESTC(ss::is_arithmetic<int>::value)
    SS_TESTC(ss::is_arithmetic<signed char>::value)
    SS_TESTC(ss::is_arithmetic<long double>::value)
    SS_TESTC(ss::is_arithmetic<const volatile int>::value)
    SS_TESTC(ss::is_arithmetic<std::size_t>::value)
    SS_TESTC(ss::is_arithmetic<std::ptrdiff_t>::value)
    SS_TESTC(!ss::is_arithmetic<void>::value)
    SS_TESTC(!ss::is_arithmetic<ss::nullptr_t>::value)
    SS_TESTC(!ss::is_arithmetic<std::nullptr_t>::value)
    SS_TESTC(!ss::is_arithmetic<decltype(nullptr)>::value)
    SS_TESTC(!ss::is_arithmetic<void*>::value)
    SS_TESTC(!ss::is_arithmetic<e>::value)
    SS_TESTC(!ss::is_arithmetic<std::vector<int>>::value)
  }

  { // is_fundamental
    enum e {};
    struct s {};
    SS_TESTC(ss::is_fundamental<int>::value)
    SS_TESTC(ss::is_fundamental<signed char>::value)
    SS_TESTC(ss::is_fundamental<long double>::value)
    SS_TESTC(ss::is_fundamental<const volatile int>::value)
    SS_TESTC(ss::is_fundamental<std::size_t>::value)
    SS_TESTC(ss::is_fundamental<std::ptrdiff_t>::value)
    SS_TESTC(ss::is_fundamental<void>::value)
    SS_TESTC(!ss::is_fundamental<int&>::value)
    SS_TESTC(ss::is_fundamental<ss::nullptr_t>::value)
    SS_TESTC(ss::is_fundamental<std::nullptr_t>::value)
    SS_TESTC(ss::is_fundamental<decltype(nullptr)>::value)
    SS_TESTC(!ss::is_fundamental<void*>::value)
    SS_TESTC(!ss::is_fundamental<e>::value)
    SS_TESTC(!ss::is_fundamental<s>::value)
    SS_TESTC(!ss::is_fundamental<std::vector<int>>::value)
  }

  { // is_scalar
    enum e {};
    struct s {};
    SS_TESTC(ss::is_scalar<int>::value)
    SS_TESTC(ss::is_scalar<signed char>::value)
    SS_TESTC(ss::is_scalar<long double>::value)
    SS_TESTC(ss::is_scalar<const volatile int>::value)
    SS_TESTC(ss::is_scalar<std::size_t>::value)
    SS_TESTC(ss::is_scalar<std::ptrdiff_t>::value)
    SS_TESTC(!ss::is_scalar<void>::value)
    SS_TESTC(!ss::is_scalar<void()>::value)
    SS_TESTC(!ss::is_scalar<void()&&>::value)
    SS_TESTC(!ss::is_scalar<int&>::value)
    SS_TESTC(ss::is_scalar<ss::nullptr_t>::value)
    SS_TESTC(ss::is_scalar<std::nullptr_t>::value)
    SS_TESTC(ss::is_scalar<decltype(nullptr)>::value)
    SS_TESTC(ss::is_scalar<void*>::value)
    SS_TESTC(ss::is_scalar<void*****>::value)
    SS_TESTC(ss::is_scalar<int s::*>::value)
    SS_TESTC(ss::is_scalar<void* s::*>::value)
    SS_TESTC(ss::is_scalar<void* (s::*)()>::value)
    SS_TESTC(ss::is_scalar<e>::value)
    SS_TESTC(!ss::is_scalar<s>::value)
    SS_TESTC(!ss::is_scalar<std::vector<int>>::value)
  }

  { // is_object
    enum e {};
    struct s {};
    SS_TESTC(ss::is_object<int>::value)
    SS_TESTC(ss::is_object<signed char>::value)
    SS_TESTC(ss::is_object<long double>::value)
    SS_TESTC(ss::is_object<const volatile int>::value)
    SS_TESTC(ss::is_object<std::size_t>::value)
    SS_TESTC(ss::is_object<std::ptrdiff_t>::value)
    SS_TESTC(!ss::is_object<void>::value)
    SS_TESTC(!ss::is_object<int&>::value)
    SS_TESTC(!ss::is_object<void()>::value)
    SS_TESTC(!ss::is_object<void()&&>::value)
    SS_TESTC(ss::is_object<ss::nullptr_t>::value)
    SS_TESTC(ss::is_object<std::nullptr_t>::value)
    SS_TESTC(ss::is_object<decltype(nullptr)>::value)
    SS_TESTC(ss::is_object<void*>::value)
    SS_TESTC(ss::is_object<void*****>::value)
    SS_TESTC(ss::is_object<int s::*>::value)
    SS_TESTC(ss::is_object<void* s::*>::value)
    SS_TESTC(ss::is_object<void* (s::*)()>::value)
    SS_TESTC(ss::is_object<e>::value)
    SS_TESTC(ss::is_object<s>::value)
    SS_TESTC(ss::is_object<std::vector<int>>::value)
  }

  { // is_compound
    enum e {};
    struct s {};
    SS_TESTC(!ss::is_compound<int>::value)
    SS_TESTC(!ss::is_compound<signed char>::value)
    SS_TESTC(!ss::is_compound<long double>::value)
    SS_TESTC(!ss::is_compound<const volatile int>::value)
    SS_TESTC(!ss::is_compound<std::size_t>::value)
    SS_TESTC(!ss::is_compound<std::ptrdiff_t>::value)
    SS_TESTC(!ss::is_compound<void>::value)
    SS_TESTC(ss::is_compound<int&>::value)
    SS_TESTC(ss::is_compound<void()>::value)
    SS_TESTC(ss::is_compound<void()&&>::value)
    SS_TESTC(!ss::is_compound<ss::nullptr_t>::value)
    SS_TESTC(!ss::is_compound<std::nullptr_t>::value)
    SS_TESTC(!ss::is_compound<decltype(nullptr)>::value)
    SS_TESTC(ss::is_compound<void*>::value)
    SS_TESTC(ss::is_compound<void*****>::value)
    SS_TESTC(ss::is_compound<int s::*>::value)
    SS_TESTC(ss::is_compound<void* s::*>::value)
    SS_TESTC(ss::is_compound<void* (s::*)()>::value)
    SS_TESTC(ss::is_compound<e>::value)
    SS_TESTC(ss::is_compound<s>::value)
    SS_TESTC(ss::is_compound<std::vector<int>>::value)
  }

  { // is_constructible
    struct a {};
    struct b { b(int){}};
    struct c { c(a) {}; c() noexcept(false) {}};

    // non user-defined types
    // default
    SS_TESTC(std::is_constructible<int>::value)
    SS_TESTC(!ss::is_constructible<int&>::value)
    SS_TESTC(!ss::is_constructible<int&&>::value)
    SS_TESTC(ss::is_constructible<int[3]>::value)
    SS_TESTC(!ss::is_constructible<int[]>::value)
    SS_TESTC(!ss::is_constructible<void>::value)
    SS_TESTC(ss::is_constructible<void*>::value)
    SS_TESTC(!ss::is_constructible<void()>::value)
    SS_TESTC(ss::is_constructible<void(*)()>::value)
    SS_TESTC(!ss::is_constructible<void(&)()>::value)
    SS_TESTC(!ss::is_constructible<void()&&>::value)
    SS_TESTC(ss::is_constructible<std::nullptr_t>::value)

    // unary
    SS_TESTC(!ss::is_constructible<int&, int>::value)
    SS_TESTC(ss::is_constructible<int&, int&>::value)
    SS_TESTC(ss::is_constructible<const int&, int>::value)
    SS_TESTC(ss::is_constructible<const int&, int&>::value)
    SS_TESTC(ss::is_constructible<const int&, int&&>::value)
    SS_TESTC(ss::is_constructible<int, double>::value)
    SS_TESTC(ss::is_constructible<const int&, double>::value)
    SS_TESTC(ss::is_constructible<int&&, double>::value)
    SS_TESTC(!ss::is_constructible<int[3], int[3]>::value)
    SS_TESTC(!ss::is_constructible<int[3], int[]>::value)
    SS_TESTC(!ss::is_constructible<int[], int[3]>::value)
    SS_TESTC(ss::is_constructible<void(&)(), void(&)()>::value)
    SS_TESTC(ss::is_constructible<void(*)(), void(*)()>::value)
    SS_TESTC(ss::is_constructible<void(&)(), void()>::value)
    SS_TESTC(ss::is_constructible<void(*)(), void()>::value)
    SS_TESTC(!ss::is_constructible<void(*)(), void()&>::value)
    SS_TESTC(!ss::is_constructible<void(*)(), void()const>::value)
    SS_TESTC(!ss::is_constructible<void(), void()>::value)
    SS_TESTC(!ss::is_constructible<void(), void()&>::value)
    SS_TESTC(!ss::is_constructible<void()&, void()>::value)


    // user-defined types
    SS_TESTC(ss::is_constructible<a>::value)
    SS_TESTC(!ss::is_constructible<b>::value)
    SS_TESTC(ss::is_constructible<b, int>::value)
    SS_TESTC(ss::is_constructible<b, int&&>::value)
    SS_TESTC(ss::is_constructible<b, float>::value)
    SS_TESTC(ss::is_constructible<b, size_t>::value)
    SS_TESTC(ss::is_constructible<b, b>::value)
    SS_TESTC(ss::is_constructible<b, b&>::value)
    SS_TESTC(ss::is_constructible<c, a>::value)


    // is_trivially_constructible
    SS_TESTC(ss::is_trivially_constructible<int>::value)
    SS_TESTC(ss::is_trivially_constructible<a>::value)
    SS_TESTC(ss::is_trivially_constructible<int*>::value)
    SS_TESTC(ss::is_trivially_constructible<std::nullptr_t>::value)
    SS_TESTC(ss::is_trivially_constructible<int[3]>::value)
    SS_TESTC(!ss::is_trivially_constructible<int[]>::value)
    SS_TESTC(!ss::is_trivially_constructible<b>::value)
    SS_TESTC(!ss::is_trivially_constructible<int&>::value)
    SS_TESTC(!ss::is_trivially_constructible<void>::value)
    SS_TESTC(!ss::is_trivially_constructible<void()&&>::value)

    // is_nothrow_constructible
    // default
    SS_TESTC(std::is_nothrow_constructible<int>::value)
    SS_TESTC(!ss::is_nothrow_constructible<int&>::value)
    SS_TESTC(!ss::is_nothrow_constructible<int&&>::value)
    SS_TESTC(ss::is_nothrow_constructible<int[3]>::value)
    SS_TESTC(!ss::is_nothrow_constructible<int[]>::value)
    SS_TESTC(!ss::is_nothrow_constructible<void>::value)
    SS_TESTC(ss::is_nothrow_constructible<void*>::value)
    SS_TESTC(!ss::is_nothrow_constructible<void()>::value)
    SS_TESTC(ss::is_nothrow_constructible<void(*)()>::value)
    SS_TESTC(!ss::is_nothrow_constructible<void(&)()>::value)
    SS_TESTC(!ss::is_nothrow_constructible<void()&&>::value)
    SS_TESTC(ss::is_nothrow_constructible<std::nullptr_t>::value)

    // unary
    SS_TESTC(!ss::is_nothrow_constructible<int&, int>::value)
    SS_TESTC(ss::is_nothrow_constructible<int&, int&>::value)
    SS_TESTC(ss::is_nothrow_constructible<const int&, int>::value)
    SS_TESTC(ss::is_nothrow_constructible<const int&, int&>::value)
    SS_TESTC(ss::is_nothrow_constructible<const int&, int&&>::value)
    SS_TESTC(ss::is_nothrow_constructible<int, double>::value)
    SS_TESTC(ss::is_nothrow_constructible<const int&, double>::value)
    SS_TESTC(ss::is_nothrow_constructible<int&&, double>::value)
    SS_TESTC(!ss::is_nothrow_constructible<int[3], int[3]>::value)
    SS_TESTC(!ss::is_nothrow_constructible<int[3], int[]>::value)
    SS_TESTC(!ss::is_nothrow_constructible<int[], int[3]>::value)
    SS_TESTC(ss::is_nothrow_constructible<void(&)(), void(&)()>::value)
    SS_TESTC(ss::is_nothrow_constructible<void(*)(), void(*)()>::value)
    SS_TESTC(ss::is_nothrow_constructible<void(&)(), void()>::value)
    SS_TESTC(ss::is_nothrow_constructible<void(*)(), void()>::value)
    SS_TESTC(!ss::is_nothrow_constructible<void(*)(), void()&>::value)
    SS_TESTC(!ss::is_nothrow_constructible<void(*)(), void()const>::value)
    SS_TESTC(!ss::is_nothrow_constructible<void(), void()>::value)
    SS_TESTC(!ss::is_nothrow_constructible<void(), void()&>::value)
    SS_TESTC(!ss::is_nothrow_constructible<void()&, void()>::value)

    // user-defined types
    SS_TESTC(ss::is_nothrow_constructible<a>::value)
    SS_TESTC(!ss::is_nothrow_constructible<b>::value)
    SS_TESTC(!ss::is_nothrow_constructible<b, float>::value)
  }

  { // default_constructible
    struct a { a(int){}};
    struct b {};
    auto lambda = [](){};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

    SS_TESTC(ss::is_default_constructible<int>::value)
    SS_TESTC(ss::is_default_constructible<const int>::value)
    SS_TESTC(!ss::is_default_constructible<int&>::value)
    SS_TESTC(!ss::is_default_constructible<int&&>::value)
    SS_TESTC(ss::is_default_constructible<std::nullptr_t>::value)
    SS_TESTC(ss::is_default_constructible<int[3]>::value)
    SS_TESTC(ss::is_default_constructible<const int[3]>::value)
    SS_TESTC(!ss::is_default_constructible<int[]>::value)
    SS_TESTC(!ss::is_default_constructible<void>::value)
    SS_TESTC(!ss::is_default_constructible<void()>::value)
    SS_TESTC(!ss::is_default_constructible<void()&&>::value)

    // TODO: define feature macros. __cplusplus is too rough to check each feature support
//# if SS_CXX_VER < 20
//    SS_TESTC(!ss::is_default_constructible<decltype(lambda)>::value)
//# else
//    SS_TESTC(ss::is_default_constructible<decltype(lambda)>::value)
//# endif
    SS_TESTC(!ss::is_default_constructible<decltype(lambda_capture)>::value)
    // MSVC Bug: https://stackoverflow.com/questions/68363717/msvc-behaves-different-about-default-constructor-of-closure-type-in-c20
//    SS_TESTC(!ss::is_default_constructible<decltype(lambda_capture_default)>::value)

    SS_TESTC(!ss::is_default_constructible<a>::value)
    SS_TESTC(ss::is_default_constructible<b>::value)
  }

  { // copy_constructible
    struct a { a(const a&) = delete; };
    struct b {};
    struct c : a {};
    struct d { d(const d&) noexcept(false) {}};
    auto lambda = []{};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

    SS_TESTC(ss::is_copy_constructible<int>::value)
    SS_TESTC(ss::is_copy_constructible<const int>::value)
    SS_TESTC(ss::is_copy_constructible<int&>::value)
    SS_TESTC(ss::is_copy_constructible<const int&>::value)
    SS_TESTC(!ss::is_copy_constructible<int&&>::value)
    SS_TESTC(!ss::is_copy_constructible<const int&&>::value)
    SS_TESTC(!ss::is_copy_constructible<void>::value)
    SS_TESTC(!ss::is_copy_constructible<void()>::value)
    SS_TESTC(!ss::is_copy_constructible<void()&>::value)
    SS_TESTC(!ss::is_copy_constructible<void()const>::value)
    SS_TESTC(ss::is_copy_constructible<ss::nullptr_t>::value)
    SS_TESTC(ss::is_copy_constructible<decltype(lambda)>::value)
    SS_TESTC(ss::is_copy_constructible<decltype(lambda_capture)>::value)
    SS_TESTC(ss::is_copy_constructible<decltype(lambda_capture_default)>::value)
    SS_TESTC(ss::is_copy_constructible<void(*)()>::value)
    SS_TESTC(ss::is_copy_constructible<void(&)()>::value)
    SS_TESTC(!ss::is_copy_constructible<int[]>::value)
    SS_TESTC(!ss::is_copy_constructible<int[3]>::value)

    SS_TESTC(!ss::is_copy_constructible<a>::value)
    SS_TESTC(!ss::is_copy_constructible<a>::value)
    SS_TESTC(!ss::is_copy_constructible<a>::value)

    SS_TESTC(ss::is_copy_constructible<b>::value)
    SS_TESTC(ss::is_copy_constructible<b>::value)
    SS_TESTC(ss::is_copy_constructible<b>::value)

    SS_TESTC(!ss::is_copy_constructible<c>::value)
    SS_TESTC(!ss::is_copy_constructible<c>::value)
    SS_TESTC(!ss::is_copy_constructible<c>::value)

    SS_TESTC(ss::is_copy_constructible<d>::value)
    SS_TESTC(!ss::is_trivially_copy_constructible<d>::value)
    SS_TESTC(!ss::is_nothrow_copy_constructible<d>::value)
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

    SS_TESTC(ss::is_move_constructible<int>::value)
    SS_TESTC(ss::is_trivially_move_constructible<int>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<int>::value)

    SS_TESTC(!ss::is_move_constructible<int[]>::value)
    SS_TESTC(!ss::is_move_constructible<int[3]>::value)

    SS_TESTC(ss::is_move_constructible<const int>::value)
    SS_TESTC(ss::is_trivially_move_constructible<const int>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<const int>::value)

    SS_TESTC(ss::is_move_constructible<int&>::value)
    SS_TESTC(ss::is_trivially_move_constructible<int&>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<int&>::value)

    SS_TESTC(ss::is_move_constructible<const int&>::value)
    SS_TESTC(ss::is_trivially_move_constructible<const int&>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<const int&>::value)

    SS_TESTC(ss::is_move_constructible<int&&>::value)
    SS_TESTC(ss::is_trivially_move_constructible<int&&>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<int&&>::value)

    SS_TESTC(ss::is_move_constructible<const int&&>::value)
    SS_TESTC(ss::is_trivially_move_constructible<const int&&>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<const int&&>::value)

    SS_TESTC(!ss::is_move_constructible<void>::value)
    SS_TESTC(!ss::is_trivially_move_constructible<void>::value)
    SS_TESTC(!ss::is_nothrow_move_constructible<void>::value)

    SS_TESTC(!ss::is_move_constructible<void()>::value)
    SS_TESTC(!ss::is_trivially_move_constructible<void()>::value)
    SS_TESTC(!ss::is_nothrow_move_constructible<void()>::value)

    SS_TESTC(!ss::is_move_constructible<void()&>::value)
    SS_TESTC(!ss::is_trivially_move_constructible<void()&>::value)
    SS_TESTC(!ss::is_nothrow_move_constructible<void()&>::value)

    SS_TESTC(!ss::is_move_constructible<void()const>::value)
    SS_TESTC(!ss::is_trivially_move_constructible<void()const>::value)
    SS_TESTC(!ss::is_nothrow_move_constructible<void()const>::value)

    SS_TESTC(ss::is_move_constructible<ss::nullptr_t>::value)
    SS_TESTC(ss::is_trivially_move_constructible<ss::nullptr_t>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<ss::nullptr_t>::value)

    SS_TESTC(ss::is_move_constructible<decltype(lambda)>::value)
    SS_TESTC(ss::is_trivially_move_constructible<decltype(lambda)>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<decltype(lambda)>::value)

    SS_TESTC(ss::is_move_constructible<decltype(lambda_capture)>::value)
    SS_TESTC(ss::is_trivially_move_constructible<decltype(lambda_capture)>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<decltype(lambda_capture)>::value)

    SS_TESTC(ss::is_move_constructible<decltype(lambda_capture_default)>::value)
    SS_TESTC(ss::is_trivially_move_constructible<decltype(lambda_capture_default)>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<decltype(lambda_capture_default)>::value)

    SS_TESTC(ss::is_move_constructible<void(*)()>::value)
    SS_TESTC(ss::is_trivially_move_constructible<void(*)()>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<void(*)()>::value)

    SS_TESTC(ss::is_move_constructible<void(&)()>::value)
    SS_TESTC(ss::is_trivially_move_constructible<void(&)()>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<void(&)()>::value)

    SS_TESTC(!ss::is_move_constructible<a>::value)
    SS_TESTC(!ss::is_trivially_move_constructible<a>::value)
    SS_TESTC(!ss::is_nothrow_move_constructible<a>::value)

    SS_TESTC(ss::is_move_constructible<b>::value)
    SS_TESTC(ss::is_trivially_move_constructible<b>::value)
    SS_TESTC(ss::is_nothrow_move_constructible<b>::value)

    SS_TESTC(!ss::is_move_constructible<c>::value)

    SS_TESTC(ss::is_move_constructible<d>::value)
    SS_TESTC(!ss::is_trivially_move_constructible<d>::value)
    SS_TESTC(!ss::is_nothrow_move_constructible<d>::value)

    SS_TESTC(ss::is_move_constructible<e>::value)
    SS_TESTC(!ss::is_trivially_move_constructible<e>::value)
    SS_TESTC(!ss::is_nothrow_move_constructible<e>::value)
  }

  { // assignable
    SS_TESTC(!ss::is_assignable<int, int>::value)
    SS_TESTC(!ss::is_trivially_assignable<int, int>::value)
    SS_TESTC(!ss::is_nothrow_assignable<int, int>::value)

    SS_TESTC(!ss::is_assignable<int[], int[]>::value)
    SS_TESTC(!ss::is_assignable<int[], int[3]>::value)
    SS_TESTC(!ss::is_assignable<int[3], int[3]>::value)

    SS_TESTC(!ss::is_assignable<const int, int>::value)
    SS_TESTC(!ss::is_trivially_assignable<const int, int>::value)
    SS_TESTC(!ss::is_nothrow_assignable<const int, int>::value)

    SS_TESTC(!ss::is_assignable<int, int&>::value)
    SS_TESTC(!ss::is_trivially_assignable<int, int&>::value)
    SS_TESTC(!ss::is_nothrow_assignable<int, int&>::value)

    SS_TESTC(ss::is_assignable<int&, int>::value)
    SS_TESTC(ss::is_trivially_assignable<int&, int>::value)
    SS_TESTC(ss::is_nothrow_assignable<int&, int>::value)

    SS_TESTC(ss::is_assignable<int&, double>::value)
    SS_TESTC(ss::is_trivially_assignable<int&, double>::value)
    SS_TESTC(ss::is_nothrow_assignable<int&, double>::value)

    SS_TESTC(ss::is_assignable<int&, char>::value)
    SS_TESTC(ss::is_trivially_assignable<int&, char>::value)
    SS_TESTC(ss::is_nothrow_assignable<int&, char>::value)

    SS_TESTC(ss::is_assignable<int&, int&>::value)
    SS_TESTC(ss::is_trivially_assignable<int&, int&>::value)
    SS_TESTC(ss::is_nothrow_assignable<int&, int&>::value)

    SS_TESTC(!ss::is_assignable<const int&, int>::value)
    SS_TESTC(!ss::is_trivially_assignable<const int&, int>::value)
    SS_TESTC(!ss::is_nothrow_assignable<const int&, int>::value)

    SS_TESTC(!std::is_assignable<const int&, int&&>::value)
    SS_TESTC(!std::is_trivially_assignable<const int&, int&&>::value)
    SS_TESTC(!std::is_nothrow_assignable<const int&, int&&>::value)

    SS_TESTC(!ss::is_assignable<int&&, int>::value)
    SS_TESTC(!ss::is_trivially_assignable<int&&, int>::value)
    SS_TESTC(!ss::is_nothrow_assignable<int&&, int>::value)

    SS_TESTC(!ss::is_assignable<int&&, int&>::value)
    SS_TESTC(!ss::is_trivially_assignable<int&&, int&>::value)
    SS_TESTC(!ss::is_nothrow_assignable<int&&, int&>::value)

    SS_TESTC(!ss::is_assignable<int&&, int&&>::value)
    SS_TESTC(!ss::is_trivially_assignable<int&&, int&&>::value)
    SS_TESTC(!ss::is_nothrow_assignable<int&&, int&&>::value)


    SS_TESTC(!ss::is_assignable<void, void>::value)
    SS_TESTC(!ss::is_trivially_assignable<void, void>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void, void>::value)

    SS_TESTC(!ss::is_assignable<void, int>::value)
    SS_TESTC(!ss::is_trivially_assignable<void, int>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void, int>::value)

    SS_TESTC(!ss::is_assignable<void*(&), int>::value)
    SS_TESTC(!ss::is_trivially_assignable<void*(&), int>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void*(&), int>::value)

    SS_TESTC(!ss::is_assignable<void*, std::nullptr_t>::value)
    SS_TESTC(!ss::is_trivially_assignable<void*, std::nullptr_t>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void*, std::nullptr_t>::value)

    SS_TESTC(!ss::is_assignable<void*(&&), std::nullptr_t>::value)
    SS_TESTC(!ss::is_trivially_assignable<void*(&&), std::nullptr_t>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void*(&&), std::nullptr_t>::value)

    SS_TESTC(!ss::is_assignable<std::nullptr_t, std::nullptr_t>::value)
    SS_TESTC(!ss::is_trivially_assignable<std::nullptr_t, std::nullptr_t>::value)
    SS_TESTC(!ss::is_nothrow_assignable<std::nullptr_t, std::nullptr_t>::value)

    SS_TESTC(ss::is_assignable<std::nullptr_t&, std::nullptr_t>::value)
    SS_TESTC(ss::is_trivially_assignable<std::nullptr_t&, std::nullptr_t>::value)
    SS_TESTC(ss::is_nothrow_assignable<std::nullptr_t&, std::nullptr_t>::value)


    SS_TESTC(!ss::is_assignable<void(), void()>::value)
    SS_TESTC(!ss::is_trivially_assignable<void(), void()>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void(), void()>::value)

    SS_TESTC(!ss::is_assignable<void()&&, void()>::value)
    SS_TESTC(!ss::is_trivially_assignable<void()&&, void()>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void()&&, void()>::value)

    SS_TESTC(!ss::is_assignable<void()&&, void()volatile>::value)
    SS_TESTC(!ss::is_trivially_assignable<void()&&, void()volatile>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void()&&, void()volatile>::value)

    SS_TESTC(!ss::is_assignable<void(&)(), void()>::value)
    SS_TESTC(!ss::is_trivially_assignable<void(&)(), void()>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void(&)(), void()>::value)

    SS_TESTC(!ss::is_assignable<void(&&)(), void()>::value)
    SS_TESTC(!ss::is_trivially_assignable<void(&&)(), void()>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void(&&)(), void()>::value)

    SS_TESTC(!ss::is_assignable<void(*)(), void()>::value)
    SS_TESTC(!ss::is_trivially_assignable<void(*)(), void()>::value)
    SS_TESTC(!ss::is_nothrow_assignable<void(*)(), void()>::value)

    SS_TESTC(ss::is_assignable<void(*&)(), void()>::value)
    SS_TESTC(ss::is_trivially_assignable<void(*&)(), void()>::value)
    SS_TESTC(ss::is_nothrow_assignable<void(*&)(), void()>::value)

    SS_TESTC(ss::is_assignable<void(*&)(), void(*)()>::value)
    SS_TESTC(ss::is_trivially_assignable<void(*&)(), void(*)()>::value)
    SS_TESTC(ss::is_nothrow_assignable<void(*&)(), void(*)()>::value)

    auto lambda = []{};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

//# if SS_CXX_VER < 20
//    SS_TESTC(!ss::is_assignable<decltype(lambda), decltype(lambda)>::value)
//    SS_TESTC(!ss::is_trivially_assignable<decltype(lambda), decltype(lambda)>::value)
//    SS_TESTC(!ss::is_nothrow_assignable<decltype(lambda), decltype(lambda)>::value)
//# else
//    SS_TESTC(ss::is_assignable<decltype(lambda), decltype(lambda)>::value)
//    SS_TESTC(ss::is_trivially_assignable<decltype(lambda), decltype(lambda)>::value)
//    SS_TESTC(ss::is_nothrow_assignable<decltype(lambda), decltype(lambda)>::value)
//# endif

    SS_TESTC(!ss::is_assignable<decltype(lambda_capture), decltype(lambda_capture)>::value)
    SS_TESTC(!ss::is_trivially_assignable<decltype(lambda_capture), decltype(lambda_capture)>::value)
    SS_TESTC(!ss::is_nothrow_assignable<decltype(lambda_capture), decltype(lambda_capture)>::value)

    // MSVC bug
//    SS_TESTC(!ss::is_assignable<decltype(lambda_capture_default), decltype(lambda_capture_default)>::value)
//    SS_TESTC(!ss::is_trivially_assignable<decltype(lambda_capture_default), decltype(lambda_capture_default)>::value)
//    SS_TESTC(!ss::is_nothrow_assignable<decltype(lambda_capture_default), decltype(lambda_capture_default)>::value)

    struct a { a& operator=(const a&) = delete; };
    struct b {};
    struct c : a {};
    struct d { d& operator=(const d&) noexcept(true) {return *this;}};
    struct e { e& operator=(const e&) noexcept(false) {return *this;}};

    SS_TESTC(!ss::is_assignable<a, a>::value)
    SS_TESTC(!ss::is_trivially_assignable<a, a>::value)
    SS_TESTC(!ss::is_nothrow_assignable<a, a>::value)

    SS_TESTC(ss::is_assignable<b, b>::value)
    SS_TESTC(ss::is_trivially_assignable<b, b>::value)
    SS_TESTC(ss::is_nothrow_assignable<b, b>::value)

    SS_TESTC(!ss::is_assignable<c, c>::value)
    SS_TESTC(!ss::is_trivially_assignable<c, c>::value)
    SS_TESTC(!ss::is_nothrow_assignable<c,c >::value)

    SS_TESTC(std::is_assignable<d, d>::value)
    SS_TESTC(!std::is_trivially_assignable<d, d>::value)
    SS_TESTC(std::is_nothrow_assignable<d, d>::value)

    SS_TESTC(std::is_assignable<e, e>::value)
    SS_TESTC(!std::is_trivially_assignable<e, e>::value)
    SS_TESTC(!std::is_nothrow_assignable<e, e>::value)
  }

  { // copy_assignable
    SS_TESTC(ss::is_copy_assignable<int>::value)
    SS_TESTC(ss::is_copy_assignable<int&>::value)
    SS_TESTC(ss::is_copy_assignable<int&&>::value)
    SS_TESTC(!ss::is_copy_assignable<const int>::value)
    SS_TESTC(!ss::is_copy_assignable<const int&>::value)
    SS_TESTC(!ss::is_copy_assignable<const int&&>::value)
    SS_TESTC(!ss::is_copy_assignable<int[]>::value)
    SS_TESTC(!ss::is_copy_assignable<int[3]>::value)



    SS_TESTC(!ss::is_copy_assignable<void>::value)
    SS_TESTC(!ss::is_copy_assignable<void()>::value)
    SS_TESTC(!ss::is_copy_assignable<void()&>::value)
    SS_TESTC(!ss::is_copy_assignable<void()volatile&>::value)
    SS_TESTC(ss::is_copy_assignable<void(*)()>::value)
    SS_TESTC(!ss::is_copy_assignable<void(&)()>::value)
    SS_TESTC(ss::is_copy_assignable<ss::nullptr_t>::value)

    auto lambda = []{};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

//# if SS_CXX_VER < 20
//    SS_TESTC(!std::is_copy_assignable<decltype(lambda)>::value)
//    SS_TESTC(!ss::is_copy_assignable<decltype(lambda_capture)>::value)
//    SS_TESTC(!ss::is_copy_assignable<decltype(lambda_capture_default)>::value)
//# else
//    SS_TESTC(std::is_copy_assignable<decltype(lambda)>::value)
//# endif


    struct a { a& operator=(const a&) = delete; };
    struct b {};
    struct c : a {};
    struct d { d& operator=(const d&) noexcept(true) {return *this;}};
    struct e { e& operator=(const e&) noexcept(false) {return *this;}};

    SS_TESTC(!ss::is_copy_assignable<a>::value)
    SS_TESTC(!ss::is_trivially_copy_assignable<a>::value)
    SS_TESTC(!ss::is_nothrow_copy_assignable<a>::value)

    SS_TESTC(ss::is_copy_assignable<b>::value)
    SS_TESTC(ss::is_trivially_copy_assignable<b>::value)
    SS_TESTC(ss::is_nothrow_copy_assignable<b>::value)

    SS_TESTC(!ss::is_copy_assignable<c>::value)
    SS_TESTC(!ss::is_trivially_copy_assignable<c>::value)
    SS_TESTC(!ss::is_nothrow_copy_assignable<c>::value)

    SS_TESTC(ss::is_copy_assignable<d>::value)
    SS_TESTC(!ss::is_trivially_copy_assignable<d>::value)
    SS_TESTC(ss::is_nothrow_copy_assignable<d>::value)

    SS_TESTC(ss::is_copy_assignable<e>::value)
    SS_TESTC(!ss::is_trivially_copy_assignable<e>::value)
    SS_TESTC(!ss::is_nothrow_copy_assignable<e>::value)
  }

  { // move_assignable
    SS_TESTC(ss::is_move_assignable<int>::value)
    SS_TESTC(ss::is_move_assignable<int&>::value)
    SS_TESTC(ss::is_move_assignable<int&&>::value)
    SS_TESTC(!ss::is_move_assignable<const int>::value)
    SS_TESTC(!ss::is_move_assignable<const int&>::value)
    SS_TESTC(!ss::is_move_assignable<const int&&>::value)
    SS_TESTC(!ss::is_move_assignable<int[]>::value)
    SS_TESTC(!ss::is_move_assignable<int[3]>::value)


    SS_TESTC(!ss::is_move_assignable<void>::value)
    SS_TESTC(!ss::is_move_assignable<void()>::value)
    SS_TESTC(!ss::is_move_assignable<void()&>::value)
    SS_TESTC(!ss::is_move_assignable<void()volatile&>::value)
    SS_TESTC(ss::is_move_assignable<void(*)()>::value)
    SS_TESTC(!ss::is_move_assignable<void(&)()>::value)
    SS_TESTC(ss::is_move_assignable<ss::nullptr_t>::value)

    auto lambda = []{};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};

//# if SS_CXX_VER < 20
//    SS_TESTC(!std::is_move_assignable<decltype(lambda)>::value)
//    SS_TESTC(!ss::is_move_assignable<decltype(lambda_capture)>::value)
//    SS_TESTC(!ss::is_move_assignable<decltype(lambda_capture_default)>::value)
//# else
//    SS_TESTC(std::is_move_assignable<decltype(lambda)>::value)
//# endif


    struct a { a& operator=(const a&) = delete; };
    struct b {};
    struct c : a {};
    struct d { d& operator=(const d&) noexcept(true) {return *this;}};
    struct e { e& operator=(const e&) noexcept(false) {return *this;}};

    SS_TESTC(!ss::is_move_assignable<a>::value)
    SS_TESTC(!ss::is_trivially_move_assignable<a>::value)
    SS_TESTC(!ss::is_nothrow_move_assignable<a>::value)

    SS_TESTC(ss::is_move_assignable<b>::value)
    SS_TESTC(ss::is_trivially_move_assignable<b>::value)
    SS_TESTC(ss::is_nothrow_move_assignable<b>::value)

    SS_TESTC(!ss::is_move_assignable<c>::value)
    SS_TESTC(!ss::is_trivially_move_assignable<c>::value)
    SS_TESTC(!ss::is_nothrow_move_assignable<c>::value)

    SS_TESTC(ss::is_move_assignable<d>::value)
    SS_TESTC(!ss::is_trivially_move_assignable<d>::value)
    SS_TESTC(ss::is_nothrow_move_assignable<d>::value)

    SS_TESTC(ss::is_move_assignable<e>::value)
    SS_TESTC(!ss::is_trivially_move_assignable<e>::value)
    SS_TESTC(!ss::is_nothrow_move_assignable<e>::value)

  }

  { // destructible

  }

  { // has_virtual_destructor
    struct a {};
    struct b {virtual void foo() {}};
    struct c {virtual ~c() = default; };

    SS_TESTC(!ss::has_virtual_destructor<void>::value)
    SS_TESTC(!ss::has_virtual_destructor<void()>::value)
    SS_TESTC(!ss::has_virtual_destructor<void()const &>::value)
    SS_TESTC(!ss::has_virtual_destructor<void(&)()>::value)
    SS_TESTC(ss::has_virtual_destructor<std::iostream>::value)
    SS_TESTC(!ss::has_virtual_destructor<a>::value)
    SS_TESTC(!ss::has_virtual_destructor<b>::value)
    SS_TESTC(ss::has_virtual_destructor<c>::value)
  }

  { // is_swappable
    struct e { e(const e &) = delete; };
    struct e2 { e2(const e2 &) noexcept(false); };

    SS_TESTC(ss::is_swappable<std::unique_ptr<int>>::value)
    SS_TESTC(ss::is_swappable_with<int&, int&>::value)
    SS_TESTC(ss::is_swappable<int>::value)
    SS_TESTC(!ss::is_swappable<int[]>::value)
    SS_TESTC(ss::is_swappable<int[3]>::value)
    SS_TESTC(!ss::is_swappable<e>::value)
    SS_TESTC(!ss::is_swappable<void() &&>::value)

    SS_TESTC(ss::is_nothrow_swappable<int>::value)
    SS_TESTC(!ss::is_nothrow_swappable<e2>::value)
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
# if SS_CXX_VER >= 17

# endif
  }


  {
    struct s1 {};
    struct s2 : s1 {};
    struct s3 { virtual ~s3() {} };
    struct s4 { virtual void foo() {}};
    struct s5 { int x : 3; };
    struct s6 { s1 s1_;};

    SS_TESTC(ss::is_empty<s1>::value)
    SS_TESTC(ss::is_empty<s2>::value)
    SS_TESTC(!ss::is_empty<s3>::value)
    SS_TESTC(!ss::is_empty<s4>::value)
    SS_TESTC(!ss::is_empty<s5>::value)
    SS_TESTC(!ss::is_empty<s6>::value)

    SS_TESTC(!ss::is_polymorphic<s1>::value)
    SS_TESTC(!ss::is_polymorphic<s2>::value)
    SS_TESTC(ss::is_polymorphic<s3>::value)
    SS_TESTC(ss::is_polymorphic<s4>::value)
    SS_TESTC(!ss::is_polymorphic<s5>::value)
    SS_TESTC(!ss::is_polymorphic<s6>::value)
  }

  { // is_abstract
    SS_TESTC(!ss::is_abstract<int>::value)
    SS_TESTC(!ss::is_abstract<void>::value)
    SS_TESTC(!ss::is_abstract<void()>::value)
    SS_TESTC(!ss::is_abstract<void()&&>::value)
    SS_TESTC(!ss::is_abstract<void()&&>::value)
    SS_TESTC(!ss::is_abstract<int[]>::value)
    SS_TESTC(!ss::is_abstract<int[3]>::value)

    auto lambda = [](){};
    auto lambda_capture = [&lambda](){};
    auto lambda_capture_default = [&](){};
    SS_TESTC(!ss::is_abstract<decltype(lambda)>::value)
    SS_TESTC(!ss::is_abstract<decltype(lambda_capture)>::value)
    SS_TESTC(!ss::is_abstract<decltype(lambda_capture_default)>::value)

    struct a {};
    struct b { virtual void foo() = 0; };
    SS_TESTC(!ss::is_abstract<a>::value)
    SS_TESTC(ss::is_abstract<b>::value)
  }

  { // is_final (std)
# if SS_CXX_VER >= 14

# endif
  }

  { // is_aggregate (std)
# if SS_CXX_VER >= 17

# endif
  }

  { // is_signed
    SS_TESTC(ss::is_signed<char>::value)
    SS_TESTC(ss::is_signed<signed char>::value)
    SS_TESTC(ss::is_signed<short>::value)
    SS_TESTC(ss::is_signed<int>::value)
    SS_TESTC(ss::is_signed<long>::value)
    SS_TESTC(ss::is_signed<long long>::value)
    SS_TESTC(ss::is_signed<float>::value)
    SS_TESTC(ss::is_signed<double>::value)
    SS_TESTC(ss::is_signed<long double>::value)
//    SS_TESTC(ss::is_signed<wchar_t>::value) unknown?

//    SS_TESTC(ss::is_signed<std::int8_t>::value)   optional
//    SS_TESTC(ss::is_signed<std::int16_t>::value)
//    SS_TESTC(ss::is_signed<std::int32_t>::value)
//    SS_TESTC(ss::is_signed<std::int64_t>::value)
    SS_TESTC(ss::is_signed<std::int_fast8_t>::value)
    SS_TESTC(ss::is_signed<std::int_fast16_t>::value)
    SS_TESTC(ss::is_signed<std::int_fast32_t>::value)
    SS_TESTC(ss::is_signed<std::int_fast64_t>::value)
    SS_TESTC(ss::is_signed<std::int_least8_t>::value)
    SS_TESTC(ss::is_signed<std::int_least16_t>::value)
    SS_TESTC(ss::is_signed<std::int_least32_t>::value)
    SS_TESTC(ss::is_signed<std::int_least64_t>::value)
    SS_TESTC(ss::is_signed<std::intmax_t>::value)
//    SS_TESTC(ss::is_signed<std::intptr_t>::value)  optional


    SS_TESTC(!ss::is_signed<void>::value)
    SS_TESTC(!ss::is_signed<void*>::value)
    SS_TESTC(!ss::is_signed<int*>::value)
    SS_TESTC(!ss::is_signed<int[]>::value)
    SS_TESTC(!ss::is_signed<int[3]>::value)
    SS_TESTC(!ss::is_signed<void()>::value)
    SS_TESTC(!ss::is_signed<void()&&>::value)
    SS_TESTC(!ss::is_signed<void(*)()>::value)
    SS_TESTC(!ss::is_signed<ss::nullptr_t>::value)
# if SS_CXX_VER >= 20
    SS_TESTC(!ss::is_signed<char8_t>::value)
# endif
    SS_TESTC(!ss::is_signed<char16_t>::value)
    SS_TESTC(!ss::is_signed<char32_t>::value)
    SS_TESTC(!ss::is_signed<unsigned char>::value)
    SS_TESTC(!ss::is_signed<unsigned short>::value)
    SS_TESTC(!ss::is_signed<unsigned int>::value)
    SS_TESTC(!ss::is_signed<unsigned long>::value)
    SS_TESTC(!ss::is_signed<unsigned long long>::value)
    SS_TESTC(!ss::is_signed<std::uint_fast8_t>::value)
    SS_TESTC(!ss::is_signed<std::uint_fast16_t>::value)
    SS_TESTC(!ss::is_signed<std::uint_fast32_t>::value)
    SS_TESTC(!ss::is_signed<std::uint_fast64_t>::value)
    SS_TESTC(!ss::is_signed<std::uint_least8_t>::value)
    SS_TESTC(!ss::is_signed<std::uint_least16_t>::value)
    SS_TESTC(!ss::is_signed<std::uint_least32_t>::value)
    SS_TESTC(!ss::is_signed<std::uint_least64_t>::value)
    SS_TESTC(!ss::is_signed<std::uintmax_t>::value)

    struct a {};
    struct b { operator int() { return 0; }};
    enum e {};
    enum class f {};

    SS_TESTC(!ss::is_signed<a>::value)
    SS_TESTC(!ss::is_signed<b>::value)
    SS_TESTC(!ss::is_signed<e>::value)
    SS_TESTC(!ss::is_signed<f>::value)
  }

  { // is_unsigned

# if SS_CXX_VER >= 20
    SS_TESTC(ss::is_unsigned<char8_t>::value)
# endif
    SS_TESTC(ss::is_unsigned<char16_t>::value)
    SS_TESTC(ss::is_unsigned<char32_t>::value)
    SS_TESTC(ss::is_unsigned<unsigned char>::value)
    SS_TESTC(ss::is_unsigned<unsigned short>::value)
    SS_TESTC(ss::is_unsigned<unsigned int>::value)
    SS_TESTC(ss::is_unsigned<unsigned long>::value)
    SS_TESTC(ss::is_unsigned<unsigned long long>::value)
    SS_TESTC(ss::is_unsigned<std::uint_fast8_t>::value)
    SS_TESTC(ss::is_unsigned<std::uint_fast16_t>::value)
    SS_TESTC(ss::is_unsigned<std::uint_fast32_t>::value)
    SS_TESTC(ss::is_unsigned<std::uint_fast64_t>::value)
    SS_TESTC(ss::is_unsigned<std::uint_least8_t>::value)
    SS_TESTC(ss::is_unsigned<std::uint_least16_t>::value)
    SS_TESTC(ss::is_unsigned<std::uint_least32_t>::value)
    SS_TESTC(ss::is_unsigned<std::uint_least64_t>::value)
    SS_TESTC(ss::is_unsigned<std::uintmax_t>::value)

    SS_TESTC(!ss::is_unsigned<char>::value)
    SS_TESTC(!ss::is_unsigned<signed char>::value)
    SS_TESTC(!ss::is_unsigned<short>::value)
    SS_TESTC(!ss::is_unsigned<int>::value)
    SS_TESTC(!ss::is_unsigned<long>::value)
    SS_TESTC(!ss::is_unsigned<long long>::value)
    SS_TESTC(!ss::is_unsigned<float>::value)
    SS_TESTC(!ss::is_unsigned<double>::value)
    SS_TESTC(!ss::is_unsigned<long double>::value)

    SS_TESTC(!ss::is_unsigned<std::int_fast8_t>::value)
    SS_TESTC(!ss::is_unsigned<std::int_fast16_t>::value)
    SS_TESTC(!ss::is_unsigned<std::int_fast32_t>::value)
    SS_TESTC(!ss::is_unsigned<std::int_fast64_t>::value)
    SS_TESTC(!ss::is_unsigned<std::int_least8_t>::value)
    SS_TESTC(!ss::is_unsigned<std::int_least16_t>::value)
    SS_TESTC(!ss::is_unsigned<std::int_least32_t>::value)
    SS_TESTC(!ss::is_unsigned<std::int_least64_t>::value)
    SS_TESTC(!ss::is_unsigned<std::intmax_t>::value)


    SS_TESTC(!ss::is_unsigned<void>::value)
    SS_TESTC(!ss::is_unsigned<void*>::value)
    SS_TESTC(!ss::is_unsigned<int*>::value)
    SS_TESTC(!ss::is_unsigned<int[]>::value)
    SS_TESTC(!ss::is_unsigned<int[3]>::value)
    SS_TESTC(!ss::is_unsigned<void()>::value)
    SS_TESTC(!ss::is_unsigned<void()&&>::value)
    SS_TESTC(!ss::is_unsigned<void(*)()>::value)
    SS_TESTC(!ss::is_unsigned<ss::nullptr_t>::value)

    struct a {};
    struct b { operator int() { return 0; }};
    enum e {};
    enum class f {};

    SS_TESTC(!ss::is_unsigned<a>::value)
    SS_TESTC(!ss::is_unsigned<b>::value)
    SS_TESTC(!ss::is_unsigned<e>::value)
    SS_TESTC(!ss::is_unsigned<f>::value)
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

    SS_TESTC(!ss::is_scoped_enum<a>::value)
    SS_TESTC(!ss::is_scoped_enum<b>::value)
    SS_TESTC(!ss::is_scoped_enum<c>::value)
    SS_TESTC(!ss::is_scoped_enum<d>::value)
    SS_TESTC(!ss::is_scoped_enum<e>::value)
    SS_TESTC(ss::is_scoped_enum<f>::value)
    SS_TESTC(ss::is_scoped_enum<g>::value)
    SS_TESTC(ss::is_scoped_enum<h>::value)
    SS_TESTC(ss::is_scoped_enum<i>::value)
    SS_TESTC(ss::is_scoped_enum<j>::value)

    SS_TESTC(!ss::is_scoped_enum<void>::value)
    SS_TESTC(!ss::is_scoped_enum<ss::nullptr_t>::value)
    SS_TESTC(!ss::is_scoped_enum<void()>::value)
    SS_TESTC(!ss::is_scoped_enum<void()&&>::value)
    SS_TESTC(!ss::is_scoped_enum<void(*)()>::value)
    SS_TESTC(!ss::is_scoped_enum<int[]>::value)
    SS_TESTC(!ss::is_scoped_enum<int[3]>::value)
  }

  { // alignment_of

  }

  { // rank
    struct s {};
    auto lambda = [](){};

    SS_TESTC(ss::rank<int>::value == 0)
    SS_TESTC(ss::rank<void>::value == 0)
    SS_TESTC(ss::rank<ss::nullptr_t>::value == 0)
    SS_TESTC(ss::rank<s>::value == 0)
    SS_TESTC(ss::rank<decltype(lambda)>::value == 0)
    SS_TESTC(ss::rank<void()>::value == 0)
    SS_TESTC(ss::rank<void()&&>::value == 0)

    SS_TESTC(ss::rank<int(*)[1]>::value == 0)
    SS_TESTC(ss::rank<int(&)[1]>::value == 0)
    SS_TESTC(ss::rank<int[]>::value == 1)
    SS_TESTC(ss::rank<int[][1]>::value == 2)
    SS_TESTC(ss::rank<int[][1][2][3][4]>::value == 5)
    SS_TESTC(ss::rank<int[][1][2][3][4]>::value == 5)
  }

  { // extent

  }

  { // is_base_of
    struct A {};
    struct B1 : public A {};
    struct B2 : protected A {};
    struct B3 : private A {};
    struct C {};

    SS_TESTC(ss::is_base_of<A, A>::value)
    SS_TESTC(ss::is_base_of<A, B1>::value)
    SS_TESTC(ss::is_base_of<A, B2>::value)
    SS_TESTC(ss::is_base_of<A, B3>::value)
    SS_TESTC(!ss::is_base_of<A, C>::value)

    SS_TESTC(!ss::is_base_of<B1, A>::value)
    SS_TESTC(!ss::is_base_of<B2, A>::value)
    SS_TESTC(!ss::is_base_of<B3, A>::value)

    SS_TESTC(!ss::is_base_of<A, void>::value)
    SS_TESTC(!ss::is_base_of<void, void>::value)
    SS_TESTC(!ss::is_base_of<void, void*>::value)
    SS_TESTC(!ss::is_base_of<void*, void*>::value)
    SS_TESTC(!ss::is_base_of<void()&&, int*>::value)

    SS_TESTC(ss::is_public_base_of<A, A>::value)
    SS_TESTC(ss::is_public_base_of<A, B1>::value)
    SS_TESTC(!ss::is_public_base_of<A, B2>::value)
    SS_TESTC(!ss::is_public_base_of<A, B3>::value)
    SS_TESTC(!ss::is_public_base_of<A, C>::value)

    SS_TESTC(!ss::is_public_base_of<B1, A>::value)
    SS_TESTC(!ss::is_public_base_of<B2, A>::value)
    SS_TESTC(!ss::is_public_base_of<B3, A>::value)

    SS_TESTC(!ss::is_public_base_of<A, void>::value)
    SS_TESTC(!ss::is_public_base_of<void, void>::value)
    SS_TESTC(!ss::is_public_base_of<void, void*>::value)
    SS_TESTC(!ss::is_public_base_of<void*, void*>::value)
    SS_TESTC(!ss::is_public_base_of<void()&&, int*>::value)
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
    using x = ss::invoke_result<int>;
    using y = ss::invoke_result<void()&&, ss::nullptr_t, void()>;

    struct foo {};
    struct incomplete;

    SS_TESTC(ss::is_void<ss::invoke_result_t<void()>>::value)
    SS_TESTC(ss::is_void<ss::invoke_result_t<void(*)()>>::value)
    SS_TESTC(ss::is_void<ss::invoke_result_t<void(foo::*)(), foo&>>::value)
    SS_TESTC(ss::is_void<ss::invoke_result_t<void(foo::*)(), foo*>>::value)
# if SS_CXX_VER >= 17
    SS_TESTC(ss::is_same<ss::invoke_result_t<void(foo::*)(), foo>, std::invoke_result_t<void(foo::*)(), foo>>::value)
# endif


    SS_TESTC(ss::is_same<ss::invoke_result_t<int()>, int>::value)
    SS_TESTC(ss::is_same<ss::invoke_result_t<foo()>, foo>::value)
    SS_TESTC(ss::is_same<ss::invoke_result_t<void(incomplete[]), incomplete[3]>, void>::value)

# if SS_CXX_VER >= 14
    auto lambda = [](auto x) -> ss::conditional_t<ss::is_integral<decltype(x)>::value, int, float> { return 0; };
    SS_TESTC(ss::is_same<ss::invoke_result_t<decltype(lambda), int>, int>::value)
    SS_TESTC(ss::is_same<ss::invoke_result_t<decltype(lambda), float>, float>::value)
# endif

    struct c {
      int operator()();
      void operator()(int);
    };
    SS_TESTC(ss::is_same<ss::invoke_result_t<c>, int>::value)
    SS_TESTC(ss::is_same<ss::invoke_result_t<c, float>, void>::value)

    SS_TESTC(std::is_same<void, ss::invoke_result_t<c, int>>::value);
  }

  { // invocable
    SS_TESTC(ss::is_invocable<void()>::value)
    SS_TESTC(ss::is_invocable<void(*)()>::value)
    SS_TESTC(ss::is_invocable<void(&)()>::value)
    SS_TESTC(ss::is_invocable<void(int), float>::value)
    SS_TESTC(ss::is_invocable<void(bool), int>::value)
    SS_TESTC(ss::is_invocable<void(int), bool>::value)
    SS_TESTC(ss::is_invocable<void(int), ss::bool_constant<true>>::value)

    struct a {};
    struct b : a {};

    SS_TESTC(ss::is_invocable<void(a&), b&>::value)
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
    SS_TESTC(ss::is_same<int, ss::make_signed_t<int>>::value)
    SS_TESTC(ss::is_same<signed int, ss::make_signed_t<int>>::value)
    SS_TESTC(ss::is_same<int, ss::make_signed_t<unsigned int>>::value)
    SS_TESTC(ss::is_same<signed char, ss::make_signed_t<e1>>::value)
    SS_TESTC(sizeof(ss::make_signed_t<wchar_t>) == sizeof(wchar_t) &&
             ss::is_not_same<ss::make_signed_t<wchar_t>, wchar_t>::value)
    SS_TESTC(sizeof(ss::make_signed_t<unsigned long long>) == sizeof(unsigned long long) &&
             ss::is_not_same<ss::make_signed_t<unsigned long long>, unsigned long long>::value)
  }

  { // make_unsigned

  }

  { // conjunction
    SS_TESTC(ss::conjunction<>::value == true)
    SS_TESTC(is_true_t<typename ss::conjunction<>::type>::value == true)
    SS_TESTC(ss::conjunction<true_t, true_t, true_t>::value == true)
    SS_TESTC(ss::conjunction<false_t, false_t, false_t>::value == false)
    SS_TESTC(ss::conjunction<false_t, false_t, false_t, true_t>::value == false)
    SS_TESTC(ss::conjunction<false_t, void, void()&&>::value == false)
  }

  { // disjunction
    SS_TESTC(ss::disjunction<>::value == false)
    SS_TESTC(is_false_t<typename ss::disjunction<>::type>::value == true)
    SS_TESTC(ss::disjunction<false_t>::value == false)
    SS_TESTC(ss::disjunction<false_t, false_t>::value == false)
    SS_TESTC(ss::disjunction<false_t, false_t, false_t, true_t>::value == true)
    SS_TESTC(ss::disjunction<true_t>::value == true)
    SS_TESTC(ss::disjunction<i0, i0, i1, i2>::value == 1)
# if SS_CXX_VER >= 14
    SS_TESTC(ss::disjunction_v<> == false)
    SS_TESTC(ss::disjunction_v<false_t> == false)
    SS_TESTC(ss::disjunction_v<false_t, false_t> == false)
    SS_TESTC(ss::disjunction_v<false_t, false_t, true_t> == true)
    SS_TESTC(ss::disjunction_v<i0, i0, i1, i2> == 1)
# endif
  }

  { // negation
    SS_TESTC(ss::negation<false_t>::value == true)
    SS_TESTC(ss::negation<true_t>::value == false)
# if SS_CXX_VER >= 14
    SS_TESTC(ss::negation<false_t>::value == ss::negation_v<false_t>)
    SS_TESTC(ss::negation<true_t>::value == ss::negation_v<true_t>)
# endif
  }

  { // is_constant_evaluated (std)
# if SS_CXX_VER >= 20

# endif
  }

  { // test 'test helpers'
    struct foo { using type = void; };
    struct bar {};

    SS_TESTC(has_typename_type_t<foo>::value == true)
    SS_TESTC(has_typename_type_t<bar>::value == false)
    SS_TESTC(is_true_t<ss::true_type>::value == true)
    SS_TESTC(is_true_t<ss::false_type>::value == false)
    SS_TESTC(is_false_t<ss::true_type>::value == false)
    SS_TESTC(is_false_t<ss::false_type>::value == true)
  }

  SS_TEST_RETURN
}
