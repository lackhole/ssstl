# /*
#  * Created by YongGyu Lee on 2021/07/09.
#  */
#
# ifndef SS_MEMORY_H_
# define SS_MEMORY_H_
#
# include <cstddef>
#
# include <limits>
# include <new>
# include <ostream>
#
# include "ss/detail/addressof.h"
# include "ss/detail/allocator_arg.h"
# include "ss/detail/uses_allocator.h"
# include "ss/detail/macro.h"
# include "ss/compressed_pair.h"
# include "ss/functional.h"
# include "ss/iterator.h"
# include "ss/type_traits.h"
# include "ss/utility.h"

# include "ss/experimental/utility.h"

namespace ss {

namespace detail {

template<typename T, typename ...Args>
auto in_place_new_test(int) -> decltype(::new(::ss::declval<void *>()) T(ss::declval<Args>()...));

template<typename...>
auto in_place_new_test(...) -> unused;

template<typename T, typename ...Args>
struct in_place_new_allocatable : is_not_same<unused, decltype(in_place_new_test<T, Args...>(0))> {};

} // namespace detail

/**
 * construct_at
 * @param p
 * @param args
 * @return
 */
template<typename T, typename ...Args>
constexpr enable_if_t<detail::in_place_new_allocatable<T, Args...>::value, T *>
construct_at(T *p, Args&& ... args) {
  return ::new(const_cast<void *>(static_cast<const volatile void *>(p))) T(ss::forward<Args>(args)...);
}

template<typename ForwardIt>
SS_CONSTEXPR_AFTER_14 void destroy(ForwardIt first, ForwardIt last);

/**
 * destroy_at
 * @tparam T
 * @param p
 */
template<typename T, enable_if_t<!is_array<T>::value, int> = 0>
SS_CONSTEXPR_AFTER_14 void destroy_at(T *p) {
  p->~T();
}

template<typename T, enable_if_t<is_array<T>::value, int> = 0>
SS_CONSTEXPR_AFTER_14 void destroy_at(T *p) {
  ss::destroy(ss::begin(p), ss::end(p));
}

/**
 * destroy
 * @param first
 * @param last
 */
template<typename ForwardIt>
SS_CONSTEXPR_AFTER_14 void destroy(ForwardIt first, ForwardIt last) {
  for (; first != last; ++first)
    ss::destroy_at(ss::addressof(*first));
}

template<typename ForwardIt, typename Size>
SS_CONSTEXPR_AFTER_14 ForwardIt destroy_n(ForwardIt first, Size n) {
  for (; n > 0; (void) ++first, --n)
    ss::destroy_at(ss::addressof(first));
  return first;
}

namespace detail {

template<typename T, typename = void>
struct has_const_pointer : false_type {};
template<typename T>
struct has_const_pointer<T, void_t<typename T::const_pointer>> : true_type {};

template<typename T, typename = void>
struct has_void_pointer : false_type {};
template<typename T>
struct has_void_pointer<T, void_t<typename T::void_pointer>> : true_type {};

template<typename T, typename = void>
struct has_const_void_pointer : false_type {};
template<typename T>
struct has_const_void_pointer<T, void_t<typename T::const_void_pointer>> : true_type {};

template<typename T, typename = void>
struct has_size_type : false_type {};
template<typename T>
struct has_size_type<T, void_t<typename T::size_type>> : true_type {};

template<typename T, typename = void>
struct has_propagate_on_container_copy_assignment : false_type {};
template<typename T>
struct has_propagate_on_container_copy_assignment<T, void_t<typename T::propagate_on_container_copy_assignment>>
  : true_type {
};

template<typename T, typename = void>
struct has_propagate_on_container_move_assignment : false_type {};
template<typename T>
struct has_propagate_on_container_move_assignment<T, void_t<typename T::propagate_on_container_move_assignment>>
  : true_type {
};

template<typename T, typename = void>
struct has_propagate_on_container_swap : false_type {};
template<typename T>
struct has_propagate_on_container_swap<T, void_t<typename T::propagate_on_container_swap>> : true_type {};

template<typename T, typename = void>
struct has_is_always_equal : false_type {};
template<typename T>
struct has_is_always_equal<T, void_t<typename T::is_always_equal>> : true_type {};

template<typename T, typename U, typename = void>
struct has_rebind : false_type {};
template<typename T, typename U>
struct has_rebind<T, U, void_t<typename T::template rebind<U>>> : true_type {};

//template<typename T, typename = void> struct has_element_type : false_type {};
//template<typename T> struct has_element_type<T, void_t<typename T::element_type>> : true_type {};

template<typename T>
struct template_type;

template<template<typename, typename...> class Template, typename T, typename ...Args>
struct template_type<Template<T, Args...>> {
  using first_type = T;
  template<typename U>
  using rebind_first = Template<U, Args...>;
};

template<typename Ptr, typename = void>
struct pointer_traits_element_type {
  using type = typename template_type<Ptr>::first_type;
};

template<typename Ptr>
struct pointer_traits_element_type<Ptr, void_t<typename Ptr::element_type>> {
  using type = typename Ptr::element_type;
};

template<typename Ptr, bool v = has_difference_type<Ptr>::value>
struct pointer_traits_difference_type {
  using type = typename Ptr::difference_type;
};
template<typename Ptr>
struct pointer_traits_difference_type<Ptr, false> {
  using type = ptrdiff_t;
};

template<typename Ptr, typename U, bool v = /* true */ has_rebind<Ptr, U>::value>
struct pointer_traits_rebind {
  using type = typename Ptr::template rebind<U>;
};

template<typename Ptr, typename U>
struct pointer_traits_rebind<Ptr, U, false> {
  using type = typename template_type<Ptr>::template rebind_first<U>;
};

} // namespace detail

/**
 * pointer_traits
 * @tparam Ptr
 */
template<typename Ptr>
struct pointer_traits {
  using pointer = Ptr;
  using element_type = typename detail::pointer_traits_element_type<Ptr>::type;
  using difference_type = typename detail::pointer_traits_difference_type<Ptr>::type;

  template<typename U>
  using rebind = typename detail::pointer_traits_rebind<Ptr, U>::type;

  static pointer pointer_to(conditional_t<is_void<element_type>::value, void, element_type>& r) {
    return Ptr::pointer_to(r);
  }
};

template<typename T>
struct pointer_traits<T *> {
  using pointer = T *;
  using element_type = T;
  using difference_type = ptrdiff_t;

  template<typename U> using rebind = U *;

  static constexpr pointer pointer_to(conditional_t<is_void<element_type>::value, void, element_type>& r) noexcept {
    return ss::addressof(r);
  }
};

namespace detail {

template<typename Alloc, typename value_type, bool v = has_pointer<Alloc>::value>
struct alloc_traits_pointer {
  using type = typename Alloc::pointer;
};
template<typename Alloc, typename value_type>
struct alloc_traits_pointer<Alloc, value_type, false> {
  using type = value_type *;
};

template<typename Alloc, typename pointer, typename value_type, bool v = has_const_pointer<Alloc>::value>
struct alloc_traits_const_pointer {
  using type = typename Alloc::const_pointer;
};
template<typename Alloc, typename pointer, typename value_type>
struct alloc_traits_const_pointer<Alloc, pointer, value_type, false> {
  using type = typename pointer_traits<pointer>::template rebind<const value_type>;
};

template<typename Alloc, typename pointer, bool v = has_void_pointer<Alloc>::value>
struct alloc_traits_void_pointer {
  using type = typename Alloc::void_pointer;
};
template<typename Alloc, typename pointer>
struct alloc_traits_void_pointer<Alloc, pointer, false> {
  using type = typename pointer_traits<pointer>::template rebind<void>;
};

template<typename Alloc, typename pointer, bool v = has_const_void_pointer<Alloc>::value>
struct alloc_traits_const_void_pointer {
  using type = typename Alloc::const_void_pointer;
};
template<typename Alloc, typename pointer>
struct alloc_traits_const_void_pointer<Alloc, pointer, false> {
  using type = typename pointer_traits<pointer>::template rebind<const void>;
};

template<typename Alloc, typename pointer, bool v = has_difference_type<Alloc>::value>
struct alloc_traits_difference_type {
  using type = typename Alloc::difference_type;
};
template<typename Alloc, typename pointer>
struct alloc_traits_difference_type<Alloc, pointer, false> {
  using type = typename pointer_traits<pointer>::difference_type;
};

template<typename Alloc, typename difference_type, bool v = has_size_type<Alloc>::value>
struct alloc_traits_size_type {
  using type = typename Alloc::size_type;
};
template<typename Alloc, typename difference_type>
struct alloc_traits_size_type<Alloc, difference_type, false> {
  using type = typename make_unsigned<difference_type>::type;
};

template<typename Alloc, bool v = has_propagate_on_container_copy_assignment<Alloc>::value>
struct alloc_traits_propagate_on_container_copy_assignment {
  using type = typename Alloc::propagate_on_container_copy_assignment;
};
template<typename Alloc>
struct alloc_traits_propagate_on_container_copy_assignment<Alloc, false> {
  using type = false_type;
};

template<typename Alloc, bool v = has_propagate_on_container_move_assignment<Alloc>::value>
struct alloc_traits_propagate_on_container_move_assignment {
  using type = typename Alloc::propagate_on_container_move_assignment;
};
template<typename Alloc>
struct alloc_traits_propagate_on_container_move_assignment<Alloc, false> {
  using type = false_type;
};

template<typename Alloc, bool v = has_propagate_on_container_swap<Alloc>::value>
struct alloc_traits_propagate_on_container_swap {
  using type = typename Alloc::propagate_on_container_swap;
};
template<typename Alloc>
struct alloc_traits_propagate_on_container_swap<Alloc, false> {
  using type = false_type;
};

template<typename Alloc, bool v = has_is_always_equal<Alloc>::value>
struct alloc_traits_is_always_equal {
  using type = typename Alloc::is_always_equal;
};
template<typename Alloc>
struct alloc_traits_is_always_equal<Alloc, false> {
  using type = typename is_empty<Alloc>::type;
};

template<typename T, typename = void>
struct has_other : false_type {};
template<typename T>
struct has_other<T, void_t<typename T::other>> : true_type {};

template<typename T, typename U, bool v = has_rebind<T, U>::value>
struct has_rebind_other : has_other<typename T::template rebind<U>> {};
template<typename T, typename U>
struct has_rebind_other<T, U, false> : false_type {};

template<typename Alloc, typename T, bool v = /* true */ has_rebind_other<Alloc, T>::value>
struct alloc_traits_rebind_alloc {
  using type = typename Alloc::template rebind<T>::other;
};

template<typename Alloc, typename T>
struct alloc_traits_rebind_alloc<Alloc, T, false> {
  using type = typename template_type<Alloc>::template rebind_first<T>;
};

template<typename Alloc, typename size_type, typename pointer, typename = void>
struct has_allocate_hint : false_type {};
template<typename A, typename size_type, typename pointer>
struct has_allocate_hint<A, size_type, pointer,
                         void_t<decltype(ss::declval<A>().allocate(ss::declval<size_type>(), ss::declval<pointer>()))>>
  : true_type {
};

template<typename Alloc, typename T, typename ...Args>
auto test_construct(int) -> decltype(ss::declval<Alloc>().construct(ss::declval<T *>(), ss::declval<Args>()...));
template<typename Alloc, typename T, typename ...Args>
auto test_construct(...) -> unused;
template<typename Alloc, typename T, typename ...Args>
struct has_construct : is_not_same<unused, decltype(test_construct<Alloc, T, Args...>(0))> {};

template<typename Alloc, typename T>
auto test_destroy(int) -> decltype(ss::declval<Alloc>().destroy(ss::declval<T *>()));
template<typename...>
auto test_destroy(...) -> unused;
template<typename Alloc, typename T>
struct has_destroy : is_not_same<unused, decltype(test_construct<Alloc, T>(0))> {};

template<typename Alloc>
auto test_max_size(int) -> decltype(ss::declval<Alloc>().max_size());
template<typename Alloc>
auto test_max_size(...) -> unused;
template<typename Alloc>
struct has_max_size : is_not_same<unused, decltype(test_max_size<Alloc>(0))> {};

template<typename Alloc>
auto test_select_on_container_copy_construction(int) -> decltype(ss::declval<Alloc>().select_on_container_copy_construction());
template<typename Alloc>
auto test_select_on_container_copy_construction(...) -> unused;
template<typename Alloc>
struct has_select_on_container_copy_construction : is_not_same<unused,
                                                               decltype(test_select_on_container_copy_construction<Alloc>(
                                                                 0))> {
};

} // namespace detail

/**
 * allocator_traits
 * @tparam Alloc
 */
template<typename Alloc>
struct allocator_traits {
  using allocator_type = Alloc;
  using value_type = typename Alloc::value_type;
  using pointer = typename detail::alloc_traits_pointer<Alloc, value_type>::type;
  using const_pointer = typename detail::alloc_traits_const_pointer<Alloc, pointer, value_type>::type;
  using void_pointer = typename detail::alloc_traits_void_pointer<Alloc, pointer>::type;
  using const_void_pointer = typename detail::alloc_traits_const_void_pointer<Alloc, pointer>::type;
  using difference_type = typename detail::alloc_traits_difference_type<Alloc, pointer>::type;
  using size_type = typename detail::alloc_traits_size_type<Alloc, difference_type>::type;
  using propagate_on_container_copy_assignment = typename detail::alloc_traits_propagate_on_container_copy_assignment<
    Alloc>::type;
  using propagate_on_container_move_assignment = typename detail::alloc_traits_propagate_on_container_move_assignment<
    Alloc>::type;
  using propagate_on_container_swap = typename detail::alloc_traits_propagate_on_container_swap<Alloc>::type;
  using is_always_equal = typename detail::alloc_traits_is_always_equal<Alloc>::type;

  template<typename T>
  using rebind_alloc = typename detail::alloc_traits_rebind_alloc<Alloc, T>::type;
  template<typename T>
  using rebind_traits = allocator_traits<rebind_alloc<T>>;

  SS_NODISCARD static constexpr pointer allocate(Alloc& a, size_type n) { return a.allocate(n); }
  SS_NODISCARD static constexpr pointer allocate(Alloc& a, size_type n, const_void_pointer hint) {
    return allocate_hint_impl(a, n, hint, detail::has_allocate_hint<Alloc, size_type, const_void_pointer>{});
  }

  static SS_CONSTEXPR_AFTER_14 void deallocate(Alloc& a, pointer p, size_type n) {
    a.deallocate(p, n);
  }

  template<typename T, typename ...Args>
  static SS_CONSTEXPR_AFTER_14 void construct(Alloc& a, T *p, Args&& ... args) {
    construct_impl(detail::has_construct<Alloc, T, Args...>{}, a, p, ss::forward<Args>(args)...);
  }

  template<typename T>
  static SS_CONSTEXPR_AFTER_14 void destroy(Alloc& a, T *p) {
    destroy_impl(a, p);
  }

  static constexpr size_type max_size(const Alloc& a) noexcept {
    return max_size_impl(a, detail::has_max_size<Alloc>{});
  }

  static constexpr Alloc select_on_container_copy_construction(const Alloc& a) {
    return select_on_container_copy_construction_impl(a, detail::has_select_on_container_copy_construction<Alloc>{});
  }

 private:
  static constexpr pointer allocate_hint_impl(Alloc& a, size_type n, const_void_pointer hint, true_type) {
    return a.allocate(n, hint);
  }
  static constexpr pointer allocate_hint_impl(Alloc& a, size_type n, const_void_pointer, false_type) {
    return a.allocate(n);
  }

  template<typename T, typename ...Args>
  static SS_CONSTEXPR_AFTER_14 void construct_impl(true_type, Alloc& a, T *p, Args&& ... args) {
    a.construct(p, ss::forward<Args>(args)...);
  }
  template<typename T, typename ...Args>
  static SS_CONSTEXPR_AFTER_14 void construct_impl(false_type, Alloc& a, T *p, Args&& ... args) {
    ss::construct_at(p, ss::forward<Args>(args)...);
  }

  template<typename T>
  static SS_CONSTEXPR_AFTER_14 void destroy_impl(Alloc& a, T *p, true_type) {
    a.destroy(p);
  }
  template<typename T>
  static SS_CONSTEXPR_AFTER_14 void destroy_impl(Alloc& a, T *p, false_type) {
    ss::destroy_at(p);
  }

  static constexpr size_type max_size_impl(const Alloc& a, true_type) noexcept {
    return a.max_size();
  }
  static constexpr size_type max_size_impl(const Alloc& a, false_type) noexcept {
    // TODO
    return std::numeric_limits<size_type>::max() / sizeof(value_type);
  }

  static constexpr Alloc select_on_container_copy_construction_impl(const Alloc& a, true_type) {
    return a.select_on_container_copy_construction();
  }
  static constexpr Alloc select_on_container_copy_construction_impl(const Alloc& a, false_type) {
    return a;
  }
};

template<typename Pointer>
class allocation_result {
  Pointer ptr;
  size_t count;
};

template<typename T>
struct allocator {
  using value_type = T;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using propagate_on_container_move_assignment = true_type;

  constexpr allocator() noexcept = default;
  constexpr allocator(const allocator&) noexcept = default;

  template<typename U>
  constexpr allocator(const allocator<U>&) noexcept {}

  SS_AFTER_CXX20(constexpr)
  ~allocator() = default;

  // TODO: Check operator new(size_t, align_val_t), operator delete(void*, align_val_t) is available

  SS_NODISCARD SS_CONSTEXPR_AFTER_14 T *allocate(size_t n) {
    if (std::numeric_limits<size_t>::max() / sizeof(T) < n)
      throw std::bad_array_new_length();
# if SS_CXX_VER < 17
    return ::operator new(n * sizeof(T));
# else
    return ::operator new(n * sizeof(T), static_cast<std::align_val_t>(alignof(T)));
# endif
  }

  SS_NODISCARD SS_CONSTEXPR_AFTER_14 allocation_result<T *> allocate_at_least(size_t n) {
    // http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2021/p0401r6.html#motivation
    if ((std::numeric_limits<size_t>::max() / sizeof(T)) < n)
      throw std::bad_array_new_length();
    return {
# if SS_CXX_VER < 17
      ::operator new(n * sizeof(T)),
# else
      ::operator new(n * sizeof(T), static_cast<std::align_val_t>(sizeof(T))),
# endif
      n};
  }

  SS_CONSTEXPR_AFTER_14 void deallocate(T *p, size_t n) {
# if SS_CXX_VER < 17
    ::operator delete(p);
# else
    ::operator delete(p, static_cast<std::align_val_t>(alignof(T)));
# endif
  }
};

template<typename T1, typename T2>
constexpr bool operator==(const allocator<T1>& lhs, const allocator<T2>& rhs) noexcept {
  return true;
}
# if SS_CXX_VER < 20
template<typename T1, typename T2>
constexpr bool operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs) noexcept {
  return false;
}
# endif

namespace detail {

template<typename Alloc, typename = void>
struct has_allocate_at_least : false_type {};

template<typename Alloc>
struct has_allocate_at_least<Alloc,
                             void_t<decltype(ss::declval<Alloc>().allocate_at_least(size_t{}))>> : true_type {
};

template<typename Alloc>
constexpr allocation_result<typename allocator_traits<Alloc>::pointer>
allocate_at_least_impl(Alloc& a, size_t n, true_type) {
  return a.allocate_at_least(n);
}

template<typename Alloc>
constexpr allocation_result<typename allocator_traits<Alloc>::pointer>
allocate_at_least_impl(Alloc& a, size_t n, false_type) {
  return {a.allocate(n), n};
}

} // namespace detail

/**
 * allocate_at_least
 */
template<typename Alloc>
SS_NODISCARD constexpr allocation_result<typename allocator_traits<Alloc>::pointer>
allocate_at_least(Alloc& a, size_t n) {
  return detail::allocate_at_least_impl(detail::has_allocate_at_least<Alloc>{});
}

/**
 * default_delete<T>
 * @tparam T
 */
template<typename T>
struct default_delete {
  constexpr default_delete() = default;

  template<typename U, enable_if_t<is_convertible<U *, T *>::value, int> = 0>
  default_delete(const default_delete<U>&) noexcept {}

  void operator()(T *ptr) const {
    static_assert(detail::is_complete<T>::value, "ss::default_delete<T>: T must be complete type");
    delete ptr;
  }
};

/**
 * default_delete<T[]>
 * @tparam T
 */
template<typename T>
struct default_delete<T[]> {
  constexpr default_delete() = default;

  template<typename U, enable_if_t<is_convertible<U(*)[], T(*)[]>::value, int> = 0>
  default_delete(const default_delete<U[]>&) noexcept {}

  template<typename U, enable_if_t<is_convertible<U(*)[], T(*)[]>::value, int> = 0>
  void operator()(U *ptr) const {
    static_assert(detail::is_complete<U>::value, "ss::default_delete<T[]>: U must be complete type");
    delete[] ptr;
  }
};

namespace detail {

template<typename T, typename Deleter, bool v = has_pointer<remove_reference_t<Deleter>>::value /* true */>
struct unique_ptr_pointer {
  using type = typename remove_reference_t<Deleter>::pointer;
};

template<typename T, typename Deleter>
struct unique_ptr_pointer<T, Deleter, false> {
  using type = T *;
};

template<typename Deleter>
struct unique_ptr_deleter_default_constructible
  : conjunction<is_default_constructible<Deleter>, negation<is_pointer<Deleter>>> {
};

template<typename A>
struct unique_ptr_deleter_ctor {
  using lvalue_reference = const A&;
  using rvalue_reference = A&&;
# ifdef SS_STRICT_NOEXCEPT
  using enable_lvalue = conjunction<is_constructible<A, lvalue_reference>, is_nothrow_move_constructible<A>, is_nothrow_copy_constructible<A>>;
  using enable_rvalue = conjunction<is_constructible<A, rvalue_reference>, is_nothrow_move_constructible<A>>;
# else
  using enable_lvalue = is_constructible<A, lvalue_reference>;
  using enable_rvalue = is_constructible<A, rvalue_reference>;
# endif
};

template<typename A>
struct unique_ptr_deleter_ctor<A&> {
  using lvalue_reference = A&;
  using rvalue_reference = A&&;
  using enable_lvalue = is_constructible<A, lvalue_reference>;
  using enable_rvalue = is_constructible<A, rvalue_reference>;
};

template<typename A>
struct unique_ptr_deleter_ctor<const A&> {
  using lvalue_reference = const A&;
  using rvalue_reference = const A&&;
  using enable_lvalue = is_constructible<A, lvalue_reference>;
  using enable_rvalue = is_constructible<A, rvalue_reference>;
};

template<typename A>
struct unique_ptr_deleter_ctor<A&&> {
  using enable_lvalue = false_type;
  using enable_rvalue = false_type;
};

template<typename Deleter>
struct unique_ptr_move_constructible :
# ifdef SS_STRICT_NOEXCEPT
  disjunction<
    is_reference<Deleter>,
    conjunction<negation<is_reference<Deleter>>, is_nothrow_move_constructible<Deleter>>
  >
# else
  is_move_constructible<Deleter>
# endif
{
};

template<typename Deleter>
struct unique_ptr_deleter_move_assignable :
# ifdef SS_STRICT_NOEXCEPT
  disjunction<
    conjunction <
      is_reference<deleter_type>,
      is_nothrow_move_assignable<remove_reference_t<deleter_type>>,
      is_nothrow_copy_assignable<remove_reference_t<deleter_type>>
    >,
    conjunction <
      negation<is_reference<deleter_type>>,
      is_nothrow_move_assignable<deleter_type>
    >
  >
# else
  is_move_assignable<Deleter>
# endif
{
};

template<typename U, typename ElementType>
struct unique_ptr_array_ptr_convertible : false_type {};

template<typename U, typename ElementType>
struct unique_ptr_array_ptr_convertible<U *, ElementType> : is_convertible<U(*)[], ElementType(*)[]> {};

template<typename U, typename Pointer, typename ElementType>
struct unique_ptr_array_pointer_ctor_valid :
  disjunction<
    is_same<U, Pointer>,
    conjunction<
      is_same<Pointer, ElementType *>,
      unique_ptr_array_ptr_convertible<U, ElementType>
    >
  > {
};

template<typename From, typename To>
struct unique_ptr_array_alien_check :
  conjunction<
    is_same<typename To::pointer, typename To::element_type *>,
    is_same<typename From::pointer, typename From::element_type *>,
    is_convertible<typename From::element_type(*)[], typename To::element_type(*)[]>
  > {
};

template<typename Deleter, typename E>
using unique_ptr_deleter_convertible =
disjunction<
  conjunction<
    is_reference<Deleter>,
    is_same<Deleter, E>
# ifdef SS_STRICT_NOEXCEPT
    , is_nothrow_copy_constructible<deleter_type>
# endif
  >,
  conjunction<
    negation<is_reference<Deleter>>,
    is_convertible<E, Deleter>
# ifdef SS_STRICT_NOEXCEPT
    , is_nothrow_constructible<deleter_type, E&&>
# endif
  >
>;

}

// Require not throw -> interpret as implementation-defined(noexcept block) behavior. Not changing overload resolution.
// Define SS_STRICT_NOEXCEPT to change its overload resolution

/**
 * unique_ptr<T>
 * @tparam T
 * @tparam Deleter
 */
template<typename T, typename Deleter = default_delete<T>>
class unique_ptr {
 public:
  using pointer = typename detail::unique_ptr_pointer<T, Deleter>::type;
  using element_type = T;
  using deleter_type = Deleter;

  static_assert(detail::NullablePointer<pointer>::value,
                "ss::unique_ptr<T>: pointer type must satisfy NullablePointer");

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        detail::unique_ptr_deleter_default_constructible<deleter_type>
      >::value,
      int> = 0>
  constexpr unique_ptr() noexcept : ptr_(pointer(), compressed_pair_empty) {}

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        detail::unique_ptr_deleter_default_constructible<deleter_type>
      >::value,
      int> = 0>
  constexpr unique_ptr(nullptr_t) noexcept
    : ptr_(nullptr_t{}, compressed_pair_empty) {}

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        detail::unique_ptr_deleter_default_constructible<deleter_type>
      >::value,
      int> = 0>
  explicit unique_ptr(pointer p) noexcept : ptr_(p, compressed_pair_empty) {}

  // D is A / A& / const A&, signature: (pointer, const A& / A& / const A&)
  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        typename detail::unique_ptr_deleter_ctor<deleter_type>::enable_lvalue
      >::value,
      int> = 0>
  unique_ptr(pointer p, typename detail::unique_ptr_deleter_ctor<deleter_type>::lvalue_reference d) noexcept
    : ptr_(p, ss::forward<decltype(d)>(d)) {}

  // D is non reference type A, signature: (pointer, A&&)
  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        negation<is_reference<deleter_type>>,
        typename detail::unique_ptr_deleter_ctor<deleter_type>::enable_rvalue
      >::value,
      int> = 0>
  unique_ptr(pointer p, deleter_type&& d) noexcept : ptr_(p, ss::forward<decltype(d)>(d)) {}

  // D is lvalue-reference type A& / const A&, signature: (pointer, A&& / const A&&)
  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        is_reference<deleter_type>,
        typename detail::unique_ptr_deleter_ctor<deleter_type>::enable_rvalue
      >::value,
      int> = 0>
  unique_ptr(pointer p, typename detail::unique_ptr_deleter_ctor<deleter_type>::rvalue_reference d) = delete;

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        detail::unique_ptr_move_constructible<deleter_type>
      >::value,
      int> = 0>
  unique_ptr(unique_ptr&& other) noexcept : ptr_(other.release(), other.get_deleter()) {}

  template<typename U, typename E,
    enable_if_t<
      conjunction<
        negation<is_array<U>>,
        is_convertible<typename unique_ptr<U, E>::pointer, pointer>,
        detail::unique_ptr_deleter_convertible<deleter_type, E>
      >::value,
      int> = 0>
  unique_ptr(unique_ptr<U, E>&& u) noexcept : ptr_(u.release(), ss::forward<E>(u.get_deleter())) {}

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        detail::unique_ptr_deleter_move_assignable<deleter_type>
      >::value,
      int> = 0>
  unique_ptr& operator=(unique_ptr&& r) noexcept {
    reset(r.release());
    get_deleter() = ss::forward<deleter_type>(r.get_deleter());
  }

  template<typename U, typename E,
    enable_if_t<
      conjunction<
        negation<is_array<U>>,
        is_convertible<typename unique_ptr<U, E>::pointer, pointer>,
        is_assignable<deleter_type&, E&&>
      >::value,
      int> = 0>
  unique_ptr& operator=(unique_ptr<U, E>&& r) noexcept {
    reset(r.release());
    get_deleter() = ss::forward<deleter_type>(r.get_deleter());
  }

  unique_ptr& operator=(nullptr_t) noexcept {
    reset();
  }

  ~unique_ptr() noexcept {
    if (get() != nullptr) {
      get_deleter()(get());
      ptr_.first() = pointer();
    }
  }

  pointer release() noexcept {
    pointer p = ptr_.first();
    ptr_.first() = pointer();
    return p;
  }

  void reset(pointer ptr = pointer()) noexcept {
    // TODO: assert self-reset for debugging
    pointer old_ptr = ptr_.first();
    ptr_.first() = ptr;
    if (old_ptr)
      get_deleter()(old_ptr);
  }

  void swap(unique_ptr& other) noexcept {
    ptr_.swap(other.ptr_);
  }

  pointer get() const noexcept { return ptr_.first(); }

  deleter_type& get_deleter() noexcept { return ptr_.second(); }
  const deleter_type& get_deleter() const noexcept { return ptr_.second(); }

  explicit operator bool() const noexcept { return get() != nullptr; }

  add_lvalue_reference_t<element_type> operator*() const noexcept(noexcept(*ss::declval<pointer>())) { return *get(); }
  pointer operator->() const noexcept { return get(); }

 private:
  compressed_pair<pointer, deleter_type> ptr_;
};

/**
 * unique_ptr<T[]>
 * @tparam T
 * @tparam Deleter
 */
template<typename T, typename Deleter>
class unique_ptr<T[], Deleter> {
 public:
  using pointer = typename detail::unique_ptr_pointer<T, Deleter>::type;
  using element_type = T;
  using deleter_type = Deleter;

  static_assert(detail::NullablePointer<pointer>::value,
                "ss::unique_ptr<T>: pointer type must satisfy NullablePointer");

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        detail::unique_ptr_deleter_default_constructible<deleter_type>
      >::value,
      int> = 0>
  constexpr unique_ptr() noexcept : ptr_(pointer(), compressed_pair_empty) {}

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        detail::unique_ptr_deleter_default_constructible<deleter_type>
      >::value,
      int> = 0>
  constexpr unique_ptr(nullptr_t) noexcept
    : ptr_(nullptr_t{}, compressed_pair_empty) {}

  template<typename U,
    enable_if_t<
      conjunction<
        detail::unique_ptr_deleter_default_constructible<deleter_type>,
        disjunction<
          is_null_pointer<U>,
          detail::unique_ptr_array_pointer_ctor_valid<U, pointer, element_type>
        >
      >::value,
      int> = 0>
  explicit unique_ptr(U p) noexcept : ptr_(p, compressed_pair_empty) {}

  // D is A / A& / const A&, signature: (U, const A& / A& / const A&)
  template<typename U,
    enable_if_t<
      conjunction<
        typename detail::unique_ptr_deleter_ctor<deleter_type>::enable_lvalue,
        disjunction<
          is_null_pointer<U>,
          detail::unique_ptr_array_pointer_ctor_valid<U, pointer, element_type>
        >
      >::value,
      int> = 0>
  unique_ptr(U p, typename detail::unique_ptr_deleter_ctor<deleter_type>::lvalue_reference d) noexcept
    : ptr_(p, ss::forward<decltype(d)>(d)) {}

  // D is non reference type A, signature: (U, A&&)
  template<typename U,
    enable_if_t<
      conjunction<
        negation<is_reference<deleter_type>>,
        typename detail::unique_ptr_deleter_ctor<deleter_type>::enable_rvalue,
        disjunction<
          is_null_pointer<U>,
          detail::unique_ptr_array_pointer_ctor_valid<U, pointer, element_type>
        >
      >::value,
      int> = 0>
  unique_ptr(U p, deleter_type&& d) noexcept : ptr_(p, ss::forward<decltype(d)>(d)) {}

  // D is lvalue-reference type A& / const A&, signature: (U p, A&& / const A&& d)
  template<typename U,
    enable_if_t<
      conjunction<
        is_reference<deleter_type>,
        typename detail::unique_ptr_deleter_ctor<deleter_type>::enable_rvalue,
        disjunction<
          is_null_pointer<U>,
          detail::unique_ptr_array_pointer_ctor_valid<U, pointer, element_type>
        >
      >::value,
      int> = 0>
  unique_ptr(U p, typename detail::unique_ptr_deleter_ctor<deleter_type>::rvalue_reference d) = delete;

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        detail::unique_ptr_move_constructible<deleter_type>
      >::value,
      int> = 0>
  unique_ptr(unique_ptr&& other) noexcept : ptr_(other.release(), other.get_deleter()) {}

  template<typename U, typename E,
    enable_if_t<
      conjunction<
        is_array<U>,
        detail::unique_ptr_array_alien_check<unique_ptr<T[], Deleter>, unique_ptr<U, E>>,
        detail::unique_ptr_deleter_convertible<deleter_type, E>
      >::value,
      int> = 0>
  unique_ptr(unique_ptr<U, E>&& u) noexcept : ptr_(u.release(), ss::forward<E>(u.get_deleter())) {}

  template<typename Dummy = void,
    enable_if_t<
      conjunction<
        is_void<Dummy>,
        detail::unique_ptr_deleter_move_assignable<deleter_type>
      >::value,
      int> = 0>
  unique_ptr& operator=(unique_ptr&& r) noexcept {
    reset(r.release());
    get_deleter() = ss::forward<deleter_type>(r.get_deleter());
  }

  template<typename U, typename E,
    enable_if_t<
      conjunction<
        is_array<U>,
        detail::unique_ptr_array_alien_check<unique_ptr<T[], Deleter>, unique_ptr<U, E>>,
        is_assignable<deleter_type&, E&&>
      >::value,
      int> = 0>
  unique_ptr& operator=(unique_ptr<U, E>&& r) noexcept {
    reset(r.release());
    get_deleter() = ss::forward<deleter_type>(r.get_deleter());
  }

  pointer release() noexcept {
    pointer p = ptr_.first();
    ptr_.first() = pointer();
    return p;
  }

  template<typename U,
    enable_if_t<
      detail::unique_ptr_array_pointer_ctor_valid<U, pointer, element_type>::value,
      int> = 0>
  void reset(U ptr) noexcept {
    // TODO: assert self-reset for debugging
    pointer old_ptr = ptr_.first();
    ptr_.first() = ptr;
    if (old_ptr)
      get_deleter()(old_ptr);
  }

  void reset(nullptr_t p = nullptr) noexcept {
    reset(pointer());
  }

  void swap(unique_ptr& other) noexcept {
    ptr_.swap(other.ptr_);
  }

  pointer get() const noexcept { return ptr_.first(); }

  deleter_type& get_deleter() noexcept { return ptr_.second(); }
  const deleter_type& get_deleter() const noexcept { return ptr_.second(); }

  explicit operator bool() const noexcept { return get() != nullptr; }

  T& operator[](size_t i) const {
    return get()[i];
  }

 private:
  compressed_pair<pointer, deleter_type> ptr_;
};

template<typename T1, typename D1, typename T2, typename D2>
bool operator==(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
  return lhs.get() == rhs.get();
}

# if SS_CXX_VER < 20
template<typename T1, typename D1, typename T2, typename D2>
bool operator!=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
  return lhs.get() != rhs.get();
}
# endif

template<typename T1, typename D1, typename T2, typename D2>
bool operator<(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
  using ct = common_type_t<typename unique_ptr<T1, D1>::pointer, typename unique_ptr<T2, D2>::pointer>;
  return less<ct>(lhs.get(), rhs.get());
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator<=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
  return !(rhs < lhs);
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator>(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
  return rhs < lhs;
}

template<typename T1, typename D1, typename T2, typename D2>
bool operator>=(const unique_ptr<T1, D1>& lhs, const unique_ptr<T2, D2>& rhs) {
  return !(lhs < rhs);
}

// TODO
//template<class T1, class D1, class T2, class D2>
//requires std::three_way_comparable_with<
//  typename unique_ptr<T1, D1>::pointer,
//  typename unique_ptr<T2, D2>::pointer>
//std::compare_three_way_result_t<typename unique_ptr<T1, D1>::pointer,
//                                typename unique_ptr<T2, D2>::pointer>
//operator<=>(const unique_ptr<T1, D1>& x, const unique_ptr<T2, D2>& y) {
//  return std::compare_three_way{}(x.get(), y.get());
//}

template<typename T, typename D>
bool operator==(const unique_ptr<T, D>& x, nullptr_t) noexcept {
  return !x;
}

# if SS_CXX_VER < 20
template<typename T, typename D>
bool operator==(nullptr_t, const unique_ptr<T, D>& x) noexcept {
  return !x;
}

template<typename T, typename D>
bool operator!=(const unique_ptr<T, D>& x, nullptr_t) noexcept {
  return (bool) x;
}

template<typename T, typename D>
bool operator!=(nullptr_t, const unique_ptr<T, D>& x) noexcept {
  return (bool) x;
}
# endif

template<typename T, typename D>
bool operator<(const unique_ptr<T, D>& x, nullptr_t) {
  return less<typename unique_ptr<T, D>::pointer>()(x.get(), nullptr);
}

template<typename T, typename D>
bool operator<(nullptr_t, const unique_ptr<T, D>& y) {
  return less<typename unique_ptr<T, D>::pointer>()(nullptr, y.get());
}

template<typename T, typename D>
bool operator<=(const unique_ptr<T, D>& x, nullptr_t) {
  return !(nullptr < x);
}

template<typename T, typename D>
bool operator<=(nullptr_t, const unique_ptr<T, D>& y) {
  return !(y < nullptr);
}

template<typename T, typename D>
bool operator>(const unique_ptr<T, D>& x, nullptr_t) {
  return nullptr < x;
}

template<typename T, typename D>
bool operator>(nullptr_t, const unique_ptr<T, D>& y) {
  return y < nullptr;
}

template<typename T, typename D>
bool operator>=(const unique_ptr<T, D>& x, nullptr_t) {
  return !(x < nullptr);
}

template<typename T, typename D>
bool operator>=(nullptr_t, const unique_ptr<T, D>& y) {
  return !(nullptr < y);
}

// TODO
//template<class T, class D>
//requires std::three_way_comparable<typename unique_ptr<T, D>::pointer>
//std::compare_three_way_result_t<typename unique_ptr<T, D>::pointer>
//operator<=>(const unique_ptr<T, D>& x, std::nullptr_t) {
//  return std::compare_three_way{}(x.get(), static_cast<typename unique_ptr<T, D>::pointer>(nullptr));
//}


/**
 * make_unique <T>
 * @tparam T
 * @tparam Args
 * @param args
 * @return
 */
template<typename T, typename ...Args, enable_if_t<!is_array<T>::value, int> = 0>
unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T>(new T(ss::forward<Args>(args)...));
}



/**
 * make_unique <T[]>
 * @tparam T
 * @tparam Args
 * @param args
 * @return
 */
template<typename T, enable_if_t<is_unbounded_array<T>::value, int> = 0>
unique_ptr<T> make_unique(size_t size) {
  return unique_ptr<T>(new remove_extent_t<T>[size]());
}



template<typename T, typename ...Args, enable_if_t<is_bounded_array<T>::value, int> = 0>
void make_unique(Args&&...) = delete;



/**
 * make_unique_for_overwrite <T>
 * @tparam T
 * @tparam Args
 * @param args
 * @return
 */
template<typename T, enable_if_t<!is_array<T>::value, int> = 0>
unique_ptr<T> make_unique_for_overwrite() {
  return unique_ptr<T>(new T);
}



/**
 * make_unique_for_overwrite <T[]>
 * @tparam T
 * @tparam Args
 * @param args
 * @return
 */
template<typename T, enable_if_t<is_unbounded_array<T>::value, int> = 0>
unique_ptr<T> make_unique_for_overwrite(size_t size) {
  return unique_ptr<T>(new remove_extent_t<T>[size]);
}



template<typename T, typename ...Args, enable_if_t<is_bounded_array<T>::value, int> = 0>
void make_unique_for_overwrite(Args&&...) = delete;


template<typename CharT, typename Traits, typename Y, typename D,
  enable_if_t<
    is_same<std::basic_ostream<CharT, Traits>&, decltype(ss::declval<std::basic_ostream<CharT, Traits>&>() << ss::declval<const unique_ptr<Y, D>&>().get())>::value,
  int> = 0>
std::basic_ostream<CharT, Traits>& operator<<(std::basic_ostream<CharT, Traits>& os, const unique_ptr<Y, D>& p) {
  os << p.get();
  return os;
}



/**
 * swap(unique_ptr)
 * @param lhs
 * @param rhs
 * @return
 */
template<typename T, typename D>
enable_if<is_swappable<D>::value> swap(unique_ptr<T, D>& lhs, unique_ptr<T, D>& rhs) noexcept {
  lhs.swap(rhs);
}


} // namespace ss

# endif // SS_MEMORY_H_
