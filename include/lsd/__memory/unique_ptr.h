//
// Created by cosge on 2023-10-29.
//

#ifndef LSD___MEMORY_UNIQUE_PTR_H_
#define LSD___MEMORY_UNIQUE_PTR_H_

#include "lsd/compressed_pair.h"
#include "lsd/functional.h"
#include "lsd/__memory/default_delete.h"
#include "lsd/ostream.h"
#include "lsd/type_traits.h"
#include "lsd/utility.h"

namespace lsd {

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
# ifdef LSD_STRICT_NOEXCEPT
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
# ifdef LSD_STRICT_NOEXCEPT
    disjunction<
    is_reference<Deleter>,
    conjunction<negation<is_reference<Deleter>>, is_nothrow_move_constructible<Deleter>>
  >
# else
    is_move_constructible<Deleter>
# endif
{};

template<typename Deleter>
struct unique_ptr_deleter_move_assignable :
# ifdef LSD_STRICT_NOEXCEPT
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
  {};

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
    > {};

template<typename From, typename To>
struct unique_ptr_array_alien_check :
    conjunction<
      is_same<typename To::pointer, typename To::element_type *>,
      is_same<typename From::pointer, typename From::element_type *>,
      is_convertible<typename From::element_type(*)[], typename To::element_type(*)[]>
    > {};

template<typename Deleter, typename E>
using unique_ptr_deleter_convertible =
    disjunction<
      conjunction<
        is_reference<Deleter>,
        is_same<Deleter, E>
# ifdef LSD_STRICT_NOEXCEPT
        , is_nothrow_copy_constructible<deleter_type>
# endif
      >,
    conjunction<
      negation<is_reference<Deleter>>,
      is_convertible<E, Deleter>
# ifdef LSD_STRICT_NOEXCEPT
      , is_nothrow_constructible<deleter_type, E&&>
# endif
    >
  >;

}

// Require not throw -> interpret as implementation-defined(noexcept block) behavior. Not changing overload resolution.
// Define LSD_STRICT_NOEXCEPT to change its overload resolution

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
  "lsd::unique_ptr<T>: pointer type must satisfy NullablePointer");

  template<typename Dummy = void,
      enable_if_t<
        conjunction<
          is_void<Dummy>,
          detail::unique_ptr_deleter_default_constructible<deleter_type>
        >::value, int> = 0>
  constexpr unique_ptr() noexcept : ptr_(pointer(), compressed_pair_empty) {}

  template<typename Dummy = void,
      enable_if_t<
        conjunction<
          is_void<Dummy>,
          detail::unique_ptr_deleter_default_constructible<deleter_type>
        >::value, int> = 0>
  constexpr unique_ptr(nullptr_t) noexcept
      : ptr_(nullptr_t{}, compressed_pair_empty) {}

  template<typename Dummy = void,
      enable_if_t<
        conjunction<
          is_void<Dummy>,
          detail::unique_ptr_deleter_default_constructible<deleter_type>
        >::value, int> = 0>
  explicit unique_ptr(pointer p) noexcept : ptr_(p, compressed_pair_empty) {}

  // D is A / A& / const A&, signature: (pointer, const A& / A& / const A&)
  template<typename Dummy = void,
      enable_if_t<
        conjunction<
          is_void<Dummy>,
          typename detail::unique_ptr_deleter_ctor<deleter_type>::enable_lvalue
        >::value, int> = 0>
  unique_ptr(pointer p, typename detail::unique_ptr_deleter_ctor<deleter_type>::lvalue_reference d) noexcept
      : ptr_(p, lsd::forward<decltype(d)>(d)) {}

  // D is non reference type A, signature: (pointer, A&&)
  template<typename Dummy = void,
      enable_if_t<
        conjunction<
          is_void<Dummy>,
          negation<is_reference<deleter_type>>,
          typename detail::unique_ptr_deleter_ctor<deleter_type>::enable_rvalue
        >::value, int> = 0>
  unique_ptr(pointer p, deleter_type&& d) noexcept : ptr_(p, lsd::forward<decltype(d)>(d)) {}

  // D is lvalue-reference type A& / const A&, signature: (pointer, A&& / const A&&)
  template<typename Dummy = void,
      enable_if_t<
        conjunction<
          is_void<Dummy>,
          is_reference<deleter_type>,
          typename detail::unique_ptr_deleter_ctor<deleter_type>::enable_rvalue
        >::value, int> = 0>
  unique_ptr(pointer p, typename detail::unique_ptr_deleter_ctor<deleter_type>::rvalue_reference d) = delete;

  template<typename Dummy = void,
      enable_if_t<
        conjunction<
          is_void<Dummy>,
          detail::unique_ptr_move_constructible<deleter_type>
        >::value, int> = 0>
  unique_ptr(unique_ptr&& other) noexcept : ptr_(other.release(), other.get_deleter()) {}

  template<typename U, typename E,
      enable_if_t<
        conjunction<
          negation<is_array<U>>,
          is_convertible<typename unique_ptr<U, E>::pointer, pointer>,
          detail::unique_ptr_deleter_convertible<deleter_type, E>
        >::value, int> = 0>
  unique_ptr(unique_ptr<U, E>&& u) noexcept : ptr_(u.release(), lsd::forward<E>(u.get_deleter())) {}

  template<typename Dummy = void,
      enable_if_t<
        conjunction<
          is_void<Dummy>,
          detail::unique_ptr_deleter_move_assignable<deleter_type>
        >::value, int> = 0>
  unique_ptr& operator=(unique_ptr&& r) noexcept {
    reset(r.release());
    get_deleter() = lsd::forward<deleter_type>(r.get_deleter());
  }

  template<typename U, typename E,
      enable_if_t<
        conjunction<
          negation<is_array<U>>,
          is_convertible<typename unique_ptr<U, E>::pointer, pointer>,
          is_assignable<deleter_type&, E&&>
        >::value, int> = 0>
  unique_ptr& operator=(unique_ptr<U, E>&& r) noexcept {
    reset(r.release());
    get_deleter() = lsd::forward<deleter_type>(r.get_deleter());
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

  add_lvalue_reference_t<element_type> operator*() const noexcept(noexcept(*lsd::declval<pointer>())) { return *get(); }
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
      "lsd::unique_ptr<T>: pointer type must satisfy NullablePointer");

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
      : ptr_(p, lsd::forward<decltype(d)>(d)) {}

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
  unique_ptr(U p, deleter_type&& d) noexcept : ptr_(p, lsd::forward<decltype(d)>(d)) {}

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
  unique_ptr(unique_ptr<U, E>&& u) noexcept : ptr_(u.release(), lsd::forward<E>(u.get_deleter())) {}

  template<typename Dummy = void,
      enable_if_t<
        conjunction<
          is_void<Dummy>,
          detail::unique_ptr_deleter_move_assignable<deleter_type>
        >::value,
      int> = 0>
  unique_ptr& operator=(unique_ptr&& r) noexcept {
    reset(r.release());
    get_deleter() = lsd::forward<deleter_type>(r.get_deleter());
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
    get_deleter() = lsd::forward<deleter_type>(r.get_deleter());
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

# if LSD_CXX_VER < 20
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

# if LSD_CXX_VER < 20
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
  return unique_ptr<T>(new T(lsd::forward<Args>(args)...));
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
      is_same<
        basic_ostream<CharT, Traits>&,
        decltype(lsd::declval<basic_ostream<CharT, Traits>&>() << lsd::declval<const unique_ptr<Y, D>&>().get())
      >::value,
    int> = 0>
basic_ostream<CharT, Traits>& operator<<(basic_ostream<CharT, Traits>& os, const unique_ptr<Y, D>& p) {
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

} // namespace lsd

#endif // LSD___MEMORY_UNIQUE_PTR_H_
