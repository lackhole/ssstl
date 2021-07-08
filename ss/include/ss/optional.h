# /*
#  * Created by YongGyu Lee on 2021/05/30.
#  */
#
# ifndef SS_OPTIONAL_H_
# define SS_OPTIONAL_H_
#
# include <cstddef>
#
# include <algorithm>
# include <exception>
# include <functional>
# include <new>
# include <type_traits>
# include <utility>

namespace ss {

template<typename T>
class optional;

struct in_place_t {
  constexpr explicit in_place_t() = default;
};

struct nullopt_t {
  constexpr explicit nullopt_t(int) {}
};

constexpr nullopt_t nullopt{0};

constexpr in_place_t in_place{};

class bad_optional_access : public std::exception {
 public:
  bad_optional_access() noexcept = default;
  bad_optional_access(const bad_optional_access&) noexcept = default;
  bad_optional_access& operator=(const bad_optional_access&) noexcept = default;

  const char *what() const noexcept override {
    return "bad optional access";
  }
};

namespace internal {
namespace optional {

template<typename T>
using void_t = void;

namespace detail {
using std::swap;

template<typename T, typename U, typename = void>
struct is_swappable_with_impl : std::false_type {};

template<typename T, typename U>
struct is_swappable_with_impl<T, U, void_t<
  decltype((swap(std::declval<T>(), std::declval<U>()),
    swap(std::declval<U>(), std::declval<T>())))
>> : std::true_type {};
} // namespace detail

template<typename T, typename = void>
struct is_referencable : std::false_type {};

template<typename T>
struct is_referencable<T, void_t<T&>> : std::true_type {};

template<typename T, typename U>
using is_swappable_with = detail::is_swappable_with_impl<T, U>;

template<typename T>
struct is_swappable :
  std::conditional_t<
    !is_referencable<T>::value,
    std::false_type,
    is_swappable_with<
      std::add_lvalue_reference_t<T>,
      std::add_lvalue_reference_t<T>>
  >{};

struct not_constructible {
  not_constructible() = delete;
};

struct constructible {};

template<typename T>
using hash_constructible =
std::conditional_t<
  std::is_default_constructible<std::hash<T>>::value,
  constructible,
  not_constructible>;

} // namespace optional
} // namespace internal

// declare swap first
template<typename T,
  ::std::enable_if_t<
    ::std::is_move_constructible<T>::value && ::ss::internal::optional::is_swappable<T>::value,
    int> = 0>
void swap(::ss::optional<T>& lhs, ::ss::optional<T>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}

//template<typename T>
//struct hash<::ss::optional<T>> : ::ss::internal::optional::hash_constructible<std::remove_const_t<T>> {
//  using argument_type = ::ss::optional<T>;
//  using result_type = ::std::size_t;
//
//  result_type operator()(const argument_type& key) const {
//    return key.has_value() ? ::std::hash<::std::remove_const_t<T>>()(*key) : 0;
//  }
//};

namespace internal {
namespace optional {

template<bool v>
struct conditional_tf : std::conditional_t<v, std::true_type, std::false_type> {};

template<bool v>
using conditional_tf_t = typename conditional_tf<v>::type;

template<typename Original, typename Other>
struct check_constructible :
  conditional_tf_t<
    !std::is_constructible<Original, Other & >::value && !std::is_constructible<Original, Other const& >::value &&
    !std::is_constructible<Original, Other &&>::value && !std::is_constructible<Original, Other const&&>::value> {};

template<typename Original, typename Other>
struct check_convertible :
  conditional_tf_t<
    !std::is_convertible<Other & , Original>::value && !std::is_convertible<Other const& , Original>::value &&
    !std::is_convertible<Other &&, Original>::value && !std::is_convertible<Other const&&, Original>::value> {};

template<typename Original, typename Other>
struct check_assignable :
  conditional_tf_t<
    !std::is_assignable<Original&, Other & >::value && !std::is_assignable<Original&, Other const& >::value &&
    !std::is_assignable<Original&, Other &&>::value && !std::is_assignable<Original&, Other const&&>::value> {};

template<typename T>
struct strip {
#if __cplusplus <= 201703
  using type = std::decay_t<T>;
#else
  using type = std::remove_cvref_t<T>;
# endif
};

template<typename T>
using strip_t = typename strip<T>::type;

template<typename T, bool v = std::is_copy_constructible<T>::value>
struct check_copy_constructible {};
template<typename T>
struct check_copy_constructible<T, false> {
  check_copy_constructible() = default;
  check_copy_constructible(check_copy_constructible const&) = delete;
  check_copy_constructible(check_copy_constructible &&) = default;
  check_copy_constructible& operator=(check_copy_constructible const&) = default;
  check_copy_constructible& operator=(check_copy_constructible &&) = default;
};

template<typename T, bool v = std::is_move_constructible<T>::value>
struct check_move_constructible {};
template<typename T>
struct check_move_constructible<T, false> {
  check_move_constructible() = default;
  check_move_constructible(check_move_constructible const&) = default;
  check_move_constructible(check_move_constructible &&) = delete;
  check_move_constructible& operator=(check_move_constructible const&) = default;
  check_move_constructible& operator=(check_move_constructible &&) = default;
};

template<typename T, bool v = std::is_copy_assignable<T>::value>
struct check_copy_assignable {};
template<typename T>
struct check_copy_assignable<T, false> {
  check_copy_assignable() = default;
  check_copy_assignable(check_copy_assignable const&) = default;
  check_copy_assignable(check_copy_assignable &&) = default;
  check_copy_assignable& operator=(check_copy_assignable const&) = delete;
  check_copy_assignable& operator=(check_copy_assignable &&) = default;
};

template<typename T, bool v = std::is_move_assignable<T>::value>
struct check_move_assignable {};
template<typename T>
struct check_move_assignable<T, false> {
  check_move_assignable() = default;
  check_move_assignable(check_move_assignable const&) = default;
  check_move_assignable(check_move_assignable &&) = default;
  check_move_assignable& operator=(check_move_assignable const&) = delete;
  check_move_assignable& operator=(check_move_assignable &&) = default;
};

template<typename T, bool v = std::is_trivially_destructible<T>::value>
struct dtor {
  using value_type = T;

  constexpr dtor() noexcept
    : null{} {}

  template<typename ...Args>
  constexpr explicit dtor(in_place_t, Args&&... args)
    : val(std::forward<Args>(args)...),
      valid(true) {}

  void reset() {
    if (valid) {
      val.value_type::~value_type();
      valid = false;
    }
  }

  constexpr inline const value_type* pointer() const { return &val; }
  constexpr inline       value_type* pointer()       { return &val; }

  constexpr inline const value_type& ref() const&  { return val;             }
  constexpr inline       value_type& ref()      &  { return val;             }
  constexpr inline const value_type& ref() const&& { return std::move(val);  }
  constexpr inline       value_type& ref()      && { return std::move(val);  }

  template<typename ...U>
  void construct(U&&... args) {
    ::new((void*)&val) value_type(std::forward<U>(args)...);
    valid = true;
  }

  template<typename U>
  void construct_if(U&& arg) {
    if (valid)
      construct(std::forward<U>(arg));
  }

  ~dtor() = default;

  union {
    char null;
    value_type val;
  };
  bool valid = false;
};

template<typename T>
struct dtor<T, false> {
  using value_type = T;

  constexpr dtor() noexcept
    : null{} {}

  template<typename ...Args>
  constexpr explicit dtor(in_place_t, Args&&... args)
    : val(std::forward<Args>(args)...),
      valid(true) {}

  inline void reset() {
    if (valid) {
      val.T::~T();
      valid = false;
    }
  }

  constexpr inline const value_type* pointer() const { return &val; }
  constexpr inline       value_type* pointer()       { return &val; }

  constexpr inline const value_type& ref() const&  { return val;             }
  constexpr inline       value_type& ref()      &  { return val;             }
  constexpr inline const value_type& ref() const&& { return std::move(val);  }
  constexpr inline       value_type& ref()      && { return std::move(val);  }

  template<typename U>
  void construct(U&& arg) {
    ::new((void*)&val) value_type(std::forward<U>(arg));
    valid = true;
  }

  ~dtor() {
    if (valid)
      val.T::~T();
  };

  union {
    char null;
    T val;
  };
  bool valid = false;
};

template<typename T, bool v = std::is_trivially_copy_constructible<T>::value>
struct copy_ctor : dtor<T> {
  using base = dtor<T>;
  using base::base;
};

template<typename T>
struct copy_ctor<T, false> : dtor<T> {
  using base = dtor<T>;
  using base::base;

  copy_ctor() = default;
  copy_ctor(copy_ctor const& other) {
    if (other.valid) {
      this->construct(other.val);
    }
  }
  copy_ctor(copy_ctor &&) = default;
  copy_ctor& operator=(copy_ctor const&) = default;
  copy_ctor& operator=(copy_ctor &&) = default;
};

template<typename T, bool v = std::is_trivially_move_constructible<T>::value>
struct move_ctor : copy_ctor<T> {
  using base = copy_ctor<T>;
  using base::base;
};

template<typename T>
struct move_ctor<T, false> : copy_ctor<T> {
  using base = copy_ctor<T>;
  using base::base;

  move_ctor() = default;
  move_ctor(move_ctor const&) = default;
  move_ctor(move_ctor && other) noexcept(std::is_nothrow_move_constructible<T>::value) {
    if (other.valid) {
      this->construct(std::move(other.val));
    }
  }
  move_ctor& operator=(move_ctor const&) = default;
  move_ctor& operator=(move_ctor &&) = default;
};

template<typename T, bool v =
std::is_trivially_copy_constructible<T>::value &&
std::is_trivially_copy_assignable<T>::value &&
std::is_trivially_destructible<T>::value>
struct copy_assign : move_ctor<T> {
  using base = move_ctor<T>;
  using base::base;
};

template<typename T>
struct copy_assign<T, false> : move_ctor<T> {
  using base = move_ctor<T>;
  using base::base;

  copy_assign() = default;
  copy_assign(copy_assign const&) = default;
  copy_assign(copy_assign &&) = default;
  copy_assign& operator=(copy_assign const& other) {
    if (!other.valid) {
      this->reset();
    } else {
      if (this->valid)
        this->val = other.val;
      else
        this->construct(other.val);
    }
    return *this;
  }
  copy_assign& operator=(copy_assign &&) = default;
};

template<typename T, bool v =
std::is_trivially_move_constructible<T>::value &&
std::is_trivially_move_assignable<T>::value &&
std::is_trivially_destructible<T>::value>
struct move_assign : copy_assign<T> {
  using base = copy_assign<T>;
  using base::base;
};

template<typename T>
struct move_assign<T, false> : copy_assign<T> {
  using base = copy_assign<T>;
  using base::base;

  move_assign() = default;
  move_assign(move_assign const&) = default;
  move_assign(move_assign &&) = default;
  move_assign& operator=(move_assign const&) = default;
  move_assign& operator=(move_assign && other)
  noexcept(std::is_nothrow_move_assignable<T>::value && std::is_nothrow_move_constructible<T>::value)
  {
    if (!other.valid) {
      this->reset();
    } else {
      if (this->valid)
        this->val = other.val;
      else
        this->construct(other.val);
    }
    return *this;
  }
};

} // namespace optional
} // namespace internal

template<typename T>
class optional :
  private internal::optional::move_assign<T>,
  private internal::optional::check_copy_constructible<T>,
  private internal::optional::check_move_constructible<T>,
  private internal::optional::check_copy_assignable<T>,
  private internal::optional::check_move_assignable<T> {
  using base = internal::optional::move_assign<T>;
  using base::base;

 public:
  using value_type = T;

  static_assert(!std::is_reference<T>::value,
                "ss::optional : T must not be a reference type");
  static_assert(!std::is_same<std::remove_reference_t<std::decay_t<T>>, nullopt_t>::value,
                "ss::optional : T must not be ss::nullopt_t");
  static_assert(!std::is_same<std::remove_reference_t<std::decay_t<T>>, in_place_t>::value,
                "ss::optional : T must not be ss::in_place_t");
  static_assert(std::is_destructible<T>::value,
                "ss::optional : T must be destructible");
  static_assert(!std::is_array<T>::value,
                "ss::optional : T must be an array type");

  // constructors

  constexpr optional() noexcept = default;
  constexpr optional(nullopt_t) noexcept {};
  constexpr optional(const optional& other) = default;
  constexpr optional(optional&& other) = default;

  template<typename U,
    std::enable_if_t<
      std::is_constructible<value_type, const U&>::value &&
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value,
      int> = 0>
  constexpr optional(const optional<U>& other) {
    this->construct_if(*other);
  }

  template<typename U,
    std::enable_if_t<
      std::is_constructible<value_type, const U&>::value &&
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value &&
      !std::is_convertible<const U&, value_type>::value,
      int> = 0>
  explicit constexpr optional(const optional<U>& other) {
    this->construct_if(*other);
  }

  template<typename U,
    std::enable_if_t<
      std::is_constructible<value_type, U&&>::value &&
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value,
      int> = 0>
  constexpr optional(optional<U>&& other) {
    this->construct_if(std::move(*other));
  }

  template<typename U,
    std::enable_if_t<
      std::is_constructible<value_type, U&&>::value &&
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value &&
      !std::is_convertible<U&&, value_type>::value,
      int> = 0>
  explicit constexpr optional(optional<U>&& other) {
    this->construct_if(std::move(*other));
  }

  // Separated into 2 overloads to prevent MSVC from making an ambiguous call in C++14
  template<typename InPlaceT,
    std::enable_if_t<
      std::is_same<InPlaceT, in_place_t>::value &&
      std::is_constructible<value_type>::value,
    int> = 0>
  constexpr explicit optional(InPlaceT)

  template<typename Arg, typename ...Args,
    std::enable_if_t<
      std::is_constructible<value_type, Arg, Args...>::value,
      int> = 0>
  constexpr explicit optional(in_place_t, Arg&& arg, Args&&... args)
    : base(in_place, std::forward<Arg>(arg), std::forward<Args>(args)...) {}

  template<typename U, typename ...Args,
    std::enable_if_t<
      std::is_constructible<value_type, std::initializer_list<U>&, Args&&...>::value,
      int> = 0>
  constexpr explicit optional(in_place_t, std::initializer_list<U> ilist, Args&&... args)
    : base(in_place, ilist, std::forward<Args>(args)...) {}

  template<typename U = value_type,
    std::enable_if_t<
      std::is_constructible<value_type,U&&>::value &&
      !std::is_same<internal::optional::strip_t<U>, in_place_t>::value &&
      !std::is_same<internal::optional::strip_t<U>, optional<value_type>>::value,
      int> = 0>
  constexpr optional(U&& value)
    : base(in_place, std::forward<U>(value)) {}

  // assignment operators

  optional& operator=(nullopt_t) noexcept {
    this->reset();
    return *this;
  }

  constexpr optional& operator=(optional const&) = default;
  constexpr optional& operator=(optional &&) = default;

  template<typename U,
    std::enable_if_t<
      (std::is_constructible<value_type, U>::value &&
       std::is_assignable<value_type&, U>::value &&
       !std::is_same<internal::optional::strip_t<U>, optional>::value) &&
      (!std::is_scalar<value_type>::value ||
       !std::is_same<std::decay_t<U>, value_type>::value),
      int> = 0>
  optional& operator=(U&& value) {
    if (has_value()) {
      this->val = std::forward<U>(value);
    } else {
      this->construct(std::forward<U>(value));
    }
    return *this;
  }

  template<typename U,
    std::enable_if_t<
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value &&
      internal::optional::check_assignable   <value_type, optional<U>>::value &&
      std::is_constructible<value_type , const U&>::value &&
      std::is_assignable   <value_type&, const U&>::value,
      int> = 0>
  optional& operator=(const optional<U>& other) {
    if (other.has_value()) {
      if (this->has_value())
        this->val = *other;
      else
        this->construct(*other);
    } else { // !other.has_value()
      if (this->has_value())
        this->reset();
    }
    return *this;
  }

  template<typename U,
    std::enable_if_t<
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value &&
      internal::optional::check_assignable   <value_type, optional<U>>::value &&
      std::is_constructible<value_type , U>::value &&
      std::is_assignable   <value_type&, U>::value,
      int> = 0>
  optional& operator=(optional<U>&& other) {
    if (other.has_value()) {
      if (this->has_value())
        this->val = std::move(*other);
      else
        this->construct(std::move(*other));
    } else { // !other.has_value()
      if (this->has_value())
        this->reset();
    }
    return *this;
  }


  constexpr inline const value_type*  operator->() const { return this->pointer(); }
  constexpr inline       value_type*  operator->()       { return this->pointer(); }

  constexpr inline const value_type&  operator*() const&  { return this->ref(); }
  constexpr inline       value_type&  operator*()      &  { return this->ref(); }
  constexpr inline const value_type&& operator*() const&& { return std::move(this->ref()); }
  constexpr inline       value_type&& operator*()      && { return std::move(this->ref()); }

  constexpr inline explicit operator bool() const noexcept {
    return this->valid;
  }
  constexpr inline bool has_value() const noexcept {
    return this->valid;
  }

  constexpr inline value_type& value() & {
    if (!this->has_value())
      throw bad_optional_access{};
    return this->ref();
  }
  constexpr inline const value_type& value() const& {
    if (!this->has_value())
      throw bad_optional_access{};
    return this->ref();
  }
  constexpr inline value_type&& value() && {
    if (!this->has_value())
      throw bad_optional_access{};
    return std::move(this->ref());
  }
  constexpr inline const value_type&& value() const && {
    if (!this->has_value())
      throw bad_optional_access{};
    return std::move(this->ref());
  }

  template<typename U>
  constexpr value_type value_or(U&& default_value) const & {
    static_assert(std::is_copy_constructible<value_type>::value,
                  "ss::optional<T>::value_or : T must be copy constructible");
    static_assert(std::is_convertible<U&&, value_type>::value,
                  "ss::optional<T>::value_or : U&& must be convertible to T");

    return this->has_value() ? **this : static_cast<value_type>(std::forward<U>(default_value));
  }

  template<typename U>
  constexpr value_type value_or(U&& default_value) && {
    static_assert(std::is_move_constructible<value_type>::value,
                  "ss::optional<T>::value_or : T must be move constructible");
    static_assert(std::is_convertible<U&&, value_type>::value,
                  "ss::optional<T>::value_or : U&& must be convertible to T");

    return this->has_value() ? std::move(**this) : static_cast<value_type>(std::forward<U>(default_value));
  }

  void swap(optional& other)
#if __cplusplus >= 201703
  noexcept(std::is_nothrow_move_constructible<value_type>::value && std::is_nothrow_swappable<value_type>::value)
#else
  noexcept(std::is_nothrow_move_constructible<value_type>::value)
#endif
  {
    static_assert(std::is_move_constructible<value_type>::value,
                  "ss::optional<T>::swap : T must be move constructible");

    if (other.has_value()) {
      if (this->has_value()) {
        std::swap(**this, *other);
      } else { // !this->has_value()
        this->construct(std::move(*other));
        other.reset();
      }
    } else {
      if (this->has_value()) {
        other.construct(**this);
        this->reset();
      }
    }
  }

  using base::reset;

  template<typename Dummy = void,
    std::enable_if_t<
      std::is_same<Dummy, void>::value &&
      std::is_constructible<value_type>::value,
    int> = 0>
  value_type& emplace(Args&&... args) {
    this->reset();
    this->construct(std::forward<Args>(args)...);
    return **this;
  }

  template<typename U, typename ...Args,
    std::enable_if_t<
      std::is_constructible<value_type, std::initializer_list<U>&, Args&&...>::value,
      int> = 0>
  value_type& emplace(std::initializer_list<U> ilist, Args&&... args) {
    this->reset();
    this->construct(ilist, std::forward<Args>(args)...);
    return **this;
  }

};

# if __cplusplus >= 201703
template<class T> optional(T) -> optional<T>;
# endif

template<typename T>
constexpr inline optional<std::decay_t<T>> make_optional(T&& value) {
  return optional<std::decay_t<T>>(std::forward<T>(value));
}

template<typename T, typename ...Args>
constexpr inline optional<T> make_optional(Args&&... args) {
  return optional<T>(in_place, std::forward<Args>(args)...);
}

template<typename T, typename U, typename ...Args>
constexpr inline optional<T> make_optional(std::initializer_list<U> ilist, Args&&... args) {
  return optional<T>(in_place, ilist, std::forward<Args>(args)...);
}

// compare two optional objects

template<typename T, typename U >
constexpr bool operator==(const optional<T>& lhs, const optional<U>& rhs) {
  if (bool(lhs) != bool(rhs))
    return false;
  if (!lhs)
    return true;
  return *lhs == *rhs;
}

template<typename T, typename U >
constexpr bool operator!=(const optional<T>& lhs, const optional<U>& rhs) {
  if (bool(lhs) != bool(rhs))
    return true;
  if (!lhs)
    return false;
  return lhs != rhs;
}

template<typename T, typename U >
constexpr bool operator<(const optional<T>& lhs, const optional<U>& rhs) {
  if (!rhs.has_value())
    return false;
  if (!lhs.has_value())
    return true;
  return *lhs < *rhs;
}

template<typename T, typename U >
constexpr bool operator<=(const optional<T>& lhs, const optional<U>& rhs) {
  if (!lhs.has_value())
    return true;
  if (!rhs.has_value())
    return false;
  return *lhs <= *rhs;
}

template<typename T, typename U >
constexpr bool operator>(const optional<T>& lhs, const optional<U>& rhs) {
  if (!lhs.has_value())
    return false;
  if (!rhs.has_value())
    return true;
  return *lhs > *rhs;
}

template<typename T, typename U >
constexpr bool operator>=(const optional<T>& lhs, const optional<U>& rhs) {
  if (!rhs.has_value())
    return true;
  if (!lhs.has_value())
    return false;
  return *lhs >= *rhs;
}


// compare an optional object with a nullopt

template<typename T>
constexpr inline bool operator==(const optional<T>& opt, nullopt_t) noexcept {
  return !opt;
}

template<typename T>
constexpr inline bool operator==(nullopt_t, const optional<T>& opt) noexcept {
  return !opt;
}

template<typename T>
constexpr inline bool operator!=(const optional<T>& opt, nullopt_t) noexcept {
  return bool(opt);
}

template<typename T>
constexpr inline bool operator!=(nullopt_t, const optional<T>& opt) noexcept {
  return bool(opt);
}

template<typename T>
constexpr inline bool operator<(const optional<T>& opt, nullopt_t) noexcept {
  return false;
}

template<typename T>
constexpr inline bool operator<(nullopt_t, const optional<T>& opt) noexcept {
  return bool(opt);
}

template<typename T>
constexpr inline bool operator<=(const optional<T>& opt, nullopt_t) noexcept {
  return !opt;
}

template<typename T>
constexpr inline bool operator<=(nullopt_t, const optional<T>& opt) noexcept {
  return true;
}

template<typename T>
constexpr inline bool operator>(const optional<T>& opt, nullopt_t) noexcept {
  return bool(opt);
}

template<typename T>
constexpr inline bool operator>(nullopt_t, const optional<T>& opt) noexcept {
  return false;
}

template<typename T>
constexpr inline bool operator>=(const optional<T>& opt, nullopt_t) noexcept {
  return true;
}

template<typename T>
constexpr inline bool operator>=(nullopt_t, const optional<T>& opt) noexcept {
  return !opt;
}


// compare an optional object with a value

template<typename T, typename U>
constexpr inline bool operator==(const optional<T>& opt, const U& value) {
  return bool(opt) ? *opt == value : false;
}

template<typename T, typename U>
constexpr inline bool operator==(const T& value, const optional<U>& opt) {
  return bool(opt) ? value == *opt : false;
}

template<typename T, typename U>
constexpr inline bool operator!=(const optional<T>& opt, const U& value) {
  return bool(opt) ? opt != value : true;
}

template<typename T, typename U>
constexpr inline bool operator!=(const T& value, const optional<U>& opt) {
  return bool(opt) ? value != opt : true;
}

template<typename T, typename U>
constexpr inline bool operator<(const optional<T>& opt, const U& value) {
  return bool(opt) ? opt < value : true;
}

template<typename T, typename U>
constexpr inline bool operator<(const T& value, const optional<U>& opt) {
  return bool(opt) ? value < opt : false;
}

template<typename T, typename U>
constexpr inline bool operator<=(const optional<T>& opt, const U& value) {
  return bool(opt) ? opt <= value : true;
}

template<typename T, typename U>
constexpr inline bool operator<=(const T& value, const optional<U>& opt) {
  return bool(opt) ? value <= opt : false;
}

template<typename T, typename U>
constexpr inline bool operator>(const optional<T>& opt, const U& value) {
  return bool(opt) ? opt > value : false;
}

template<typename T, typename U>
constexpr inline bool operator>(const T& value, const optional<U>& opt) {
  return bool(opt) ? value > opt : true;
}

template<typename T, typename U>
constexpr inline bool operator>=(const optional<T>& opt, const U& value) {
  return bool(opt) ? opt >= value : false;
}

template<typename T, typename U>
constexpr inline bool operator>=(const T& value, const optional<U>& opt) {
  return bool(opt) ? value >= opt : true;
}

} // namespace ss

# endif // SS_OPTIONAL_H_