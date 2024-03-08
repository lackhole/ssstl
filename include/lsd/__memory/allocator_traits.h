//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___MEMORY_ALLOCATOR_TRAITS_H_
#define LSD___MEMORY_ALLOCATOR_TRAITS_H_

#include "lsd/__memory/construct.h"
#include "lsd/__memory/destroy.h"
#include "lsd/__memory/pointer_traits.h"
#include "lsd/type_traits.h"
#include "lsd/utility.h"

namespace lsd {

namespace detail {

template<typename Alloc, typename value_type, bool v = has_pointer<Alloc>::value>
struct alloc_traits_pointer {
  using type = typename Alloc::pointer;
};
template<typename Alloc, typename value_type>
struct alloc_traits_pointer<Alloc, value_type, false> {
  using type = value_type*;
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
                         void_t<decltype(lsd::declval<A>().allocate(lsd::declval<size_type>(), lsd::declval<pointer>()))>> : true_type {};

template<typename Alloc, typename T, typename ...Args>
auto test_construct(int) -> decltype(lsd::declval<Alloc>().construct(lsd::declval<T *>(), lsd::declval<Args>()...));
template<typename Alloc, typename T, typename ...Args>
auto test_construct(...) -> unused;
template<typename Alloc, typename T, typename ...Args>
struct has_construct : is_not_same<unused, decltype(test_construct<Alloc, T, Args...>(0))> {};

template<typename Alloc, typename T>
auto test_destroy(int) -> decltype(lsd::declval<Alloc>().destroy(lsd::declval<T *>()));
template<typename...>
auto test_destroy(...) -> unused;
template<typename Alloc, typename T>
struct has_destroy : is_not_same<unused, decltype(test_construct<Alloc, T>(0))> {};

template<typename Alloc>
auto test_max_size(int) -> decltype(lsd::declval<Alloc>().max_size());
template<typename Alloc>
auto test_max_size(...) -> unused;
template<typename Alloc>
struct has_max_size : is_not_same<unused, decltype(test_max_size<Alloc>(0))> {};

template<typename Alloc>
auto test_select_on_container_copy_construction(int) -> decltype(lsd::declval<Alloc>().select_on_container_copy_construction());
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
  using propagate_on_container_copy_assignment = typename detail::alloc_traits_propagate_on_container_copy_assignment<Alloc>::type;
  using propagate_on_container_move_assignment = typename detail::alloc_traits_propagate_on_container_move_assignment<Alloc>::type;
  using propagate_on_container_swap = typename detail::alloc_traits_propagate_on_container_swap<Alloc>::type;
  using is_always_equal = typename detail::alloc_traits_is_always_equal<Alloc>::type;

  template<typename T>
  using rebind_alloc = typename detail::alloc_traits_rebind_alloc<Alloc, T>::type;
  template<typename T>
  using rebind_traits = allocator_traits<rebind_alloc<T>>;

  LSD_NODISCARD static constexpr pointer allocate(Alloc& a, size_type n) { return a.allocate(n); }
  LSD_NODISCARD static constexpr pointer allocate(Alloc& a, size_type n, const_void_pointer hint) {
    return allocate_hint_impl(a, n, hint, detail::has_allocate_hint<Alloc, size_type, const_void_pointer>{});
  }

  static LSD_CONSTEXPR_AFTER_14 void deallocate(Alloc& a, pointer p, size_type n) {
    a.deallocate(p, n);
  }

  template<typename T, typename ...Args>
  static LSD_CONSTEXPR_AFTER_14 void construct(Alloc& a, T *p, Args&& ... args) {
    construct_impl(detail::has_construct<Alloc, T, Args...>{}, a, p, lsd::forward<Args>(args)...);
  }

  template<typename T>
  static LSD_CONSTEXPR_AFTER_14 void destroy(Alloc& a, T *p) {
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
  static LSD_CONSTEXPR_AFTER_14 void construct_impl(true_type, Alloc& a, T *p, Args&& ... args) {
    a.construct(p, lsd::forward<Args>(args)...);
  }
  template<typename T, typename ...Args>
  static LSD_CONSTEXPR_AFTER_14 void construct_impl(false_type, Alloc& a, T *p, Args&& ... args) {
    lsd::construct_at(p, lsd::forward<Args>(args)...);
  }

  template<typename T>
  static LSD_CONSTEXPR_AFTER_14 void destroy_impl(Alloc& a, T *p, true_type) {
    a.destroy(p);
  }
  template<typename T>
  static LSD_CONSTEXPR_AFTER_14 void destroy_impl(Alloc& a, T *p, false_type) {
    lsd::destroy_at(p);
  }

  static constexpr size_type max_size_impl(const Alloc& a, true_type) noexcept {
    return a.max_size();
  }
  static constexpr size_type max_size_impl(const Alloc& a, false_type) noexcept {
    // TODO
    return numeric_limits<size_type>::max() / sizeof(value_type);
  }

  static constexpr Alloc select_on_container_copy_construction_impl(const Alloc& a, true_type) {
    return a.select_on_container_copy_construction();
  }
  static constexpr Alloc select_on_container_copy_construction_impl(const Alloc& a, false_type) {
    return a;
  }
};

} // namespace lsd

#endif // LSD___MEMORY_ALLOCATOR_TRAITS_H_
