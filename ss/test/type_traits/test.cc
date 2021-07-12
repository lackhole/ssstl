#include <iostream>

#include "ss/type_traits.h"
#include "ss_test.h"

#ifdef NDEBUG
#define NDEBUG_DEFINED 1
#else
#define NDEBUG_DEFINED 0
#endif

// helpers for testing


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
    SS_TESTC(ss::is_function<void()>::value)
    SS_TESTC(!ss::is_function<void(&)()>::value)
    SS_TESTC(!ss::is_function<void(*)()>::value)
    SS_TESTC(!ss::is_function<std::function<void()>>::value)
    SS_TESTC(!ss::is_function<decltype(lambda)>::value)
  }

  { // is_swappable
    struct e { e(const e &) = delete; };
    struct e2 { e2(const e2 &) noexcept(false); };

//    SS_TESTC(std::is_swappable<std::unique_ptr<int>>::value)
    SS_TESTC(ss::is_swappable<std::unique_ptr<int>>::value)
//    SS_TESTC(std::is_swappable<int>::value)
    SS_TESTC(ss::is_move_constructible<int>::value)
    SS_TESTC(ss::is_assignable<int&, int&&>::value)
    SS_TESTC(ss::is_move_assignable<int>::value)
    SS_TESTC(ss::is_swappable_with<int&, int&>::value)
    SS_TESTC(ss::is_swappable<int>::value)
//    SS_TESTC(!std::is_swappable<e>::value)
    SS_TESTC(!ss::is_swappable<e>::value)
//    SS_TESTC(!std::is_swappable<void() &&>::value)
    SS_TESTC(!ss::is_swappable<void() &&>::value)

//    SS_TESTC(std::is_nothrow_swappable_v<int>)
    SS_TESTC(ss::is_nothrow_swappable<int>::value)
//    SS_TESTC(!std::is_nothrow_swappable_v<e2>)
    SS_TESTC(!ss::is_nothrow_swappable<e2>::value)
  }

  {
    struct s1 {};
    struct s2 : s1 {};
    struct s3 { virtual ~s3() {} };
    struct s4 { virtual void foo() {}};
    struct s5 { int x : 3; };

    SS_TESTC(std::is_empty<s1>::value)
    SS_TESTC(std::is_empty<s2>::value)
    SS_TESTC(!std::is_empty<s3>::value)
    SS_TESTC(!std::is_empty<s4>::value)

    SS_TESTC(ss::is_empty<s1>::value)
    SS_TESTC(ss::is_empty<s2>::value)
    SS_TESTC(!ss::is_empty<s3>::value)
    SS_TESTC(!ss::is_empty<s4>::value)

    SS_TESTC(!std::is_polymorphic<s1>::value)
    SS_TESTC(!std::is_polymorphic<s2>::value)
    SS_TESTC(!std::is_polymorphic<s5>::value)
    SS_TESTC(std::is_polymorphic<s3>::value)
    SS_TESTC(std::is_polymorphic<s4>::value)

    SS_TESTC(!ss::is_polymorphic<s1>::value)
    SS_TESTC(!ss::is_polymorphic<s2>::value)
    SS_TESTC(!ss::is_polymorphic<s5>::value)
    SS_TESTC(ss::is_polymorphic<s3>::value)
    SS_TESTC(ss::is_polymorphic<s4>::value)
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


  // conjunction
  SS_TESTC(ss::conjunction<>::value == true)
  SS_TESTC(is_true_t<typename ss::conjunction<>::type>::value == true)
  SS_TESTC(ss::conjunction<true_t, true_t, true_t>::value == true)
  SS_TESTC(ss::conjunction<false_t, false_t, false_t>::value == false)
  SS_TESTC(ss::conjunction<false_t, false_t, false_t, true_t>::value == false)
  SS_TESTC(ss::conjunction<false_t, void, void()&&>::value == false)

  // disjunction
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

  // negation
  SS_TESTC(ss::negation<false_t>::value == true)
  SS_TESTC(ss::negation<true_t>::value == false)
# if SS_CXX_VER >= 14
  SS_TESTC(ss::negation<false_t>::value == ss::negation_v<false_t>)
  SS_TESTC(ss::negation<true_t>::value == ss::negation_v<true_t>)
# endif

  SS_TEST_RETURN
}
