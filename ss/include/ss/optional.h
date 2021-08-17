# /*
#  * Created by YongGyu Lee on 2021/05/30.
#  */
#
# ifndef SS_OPTIONAL_H_
# define SS_OPTIONAL_H_
#
# include <exception>
# include <functional>
# include <new>
#
# include "ss/type_traits.h"
# include "ss/functional.h"
# include "ss/utility.h"
# include "ss/memory.h"

namespace ss {

template<typename T>
class optional;

struct nullopt_t {
  constexpr explicit nullopt_t(int) {}
};

constexpr nullopt_t nullopt{0};

class bad_optional_access : public std::exception {
 public:
  bad_optional_access() noexcept = default;
  bad_optional_access(const bad_optional_access&) noexcept = default;
  bad_optional_access& operator=(const bad_optional_access&) noexcept = default;

  const char *what() const noexcept override {
    return "bad optional access";
  }
};

namespace detail {
struct not_constructible { not_constructible() = delete; };

struct constructible {};

template<typename T>
using hash_constructible =
conditional_t<
  is_default_constructible<std::hash<T>>::value,
  constructible,
  not_constructible>;

} // namespace detail

// declare swap first
template<typename T,
  enable_if_t<
    is_move_constructible<T>::value && is_swappable<T>::value,
  int> = 0>
void swap(optional<T>& lhs, optional<T>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
  lhs.swap(rhs);
}

template<typename T>
struct hash<optional<T>> : detail::hash_constructible<remove_const_t<T>> {
  using argument_type = optional<T>;
  using result_type = size_t;

  result_type operator()(const argument_type& key) const {
    return key.has_value() ? std::hash<remove_const_t<T>>()(*key) : 0;
  }
};

namespace internal {
namespace optional {

template<bool v>
struct conditional_tf : conditional_t<v, true_type, false_type> {};

template<bool v>
using conditional_tf_t = typename conditional_tf<v>::type;

template<typename Original, typename Other>
struct check_constructible :
  conditional_tf_t<
    !is_constructible<Original, Other & >::value && !is_constructible<Original, Other const& >::value &&
    !is_constructible<Original, Other &&>::value && !is_constructible<Original, Other const&&>::value> {};

template<typename Original, typename Other>
struct check_convertible :
  conditional_tf_t<
    !is_convertible<Other & , Original>::value && !is_convertible<Other const& , Original>::value &&
    !is_convertible<Other &&, Original>::value && !is_convertible<Other const&&, Original>::value> {};

template<typename Original, typename Other>
struct check_assignable :
  conditional_tf_t<
    !is_assignable<Original&, Other & >::value && !is_assignable<Original&, Other const& >::value &&
    !is_assignable<Original&, Other &&>::value && !is_assignable<Original&, Other const&&>::value> {};

template<typename T, bool v = is_copy_constructible<T>::value>
struct check_copy_constructible {};
template<typename T>
struct check_copy_constructible<T, false> {
  check_copy_constructible() = default;
  check_copy_constructible(check_copy_constructible const&) = delete;
  check_copy_constructible(check_copy_constructible &&) = default;
  check_copy_constructible& operator=(check_copy_constructible const&) = default;
  check_copy_constructible& operator=(check_copy_constructible &&) = default;
};

template<typename T, bool v = is_move_constructible<T>::value>
struct check_move_constructible {};
template<typename T>
struct check_move_constructible<T, false> {
  check_move_constructible() = default;
  check_move_constructible(check_move_constructible const&) = default;
  check_move_constructible(check_move_constructible &&) = delete;
  check_move_constructible& operator=(check_move_constructible const&) = default;
  check_move_constructible& operator=(check_move_constructible &&) = default;
};

template<typename T, bool v = is_copy_constructible<T>::value && is_copy_assignable<T>::value>
struct check_copy_assignable {};
template<typename T>
struct check_copy_assignable<T, false> {
  check_copy_assignable() = default;
  check_copy_assignable(check_copy_assignable const&) = default;
  check_copy_assignable(check_copy_assignable &&) = default;
  check_copy_assignable& operator=(check_copy_assignable const&) = delete;
  check_copy_assignable& operator=(check_copy_assignable &&) = default;
};

template<typename T, bool v = is_move_constructible<T>::value && is_move_assignable<T>::value>
struct check_move_assignable {};
template<typename T>
struct check_move_assignable<T, false> {
  check_move_assignable() = default;
  check_move_assignable(check_move_assignable const&) = default;
  check_move_assignable(check_move_assignable &&) = default;
  check_move_assignable& operator=(check_move_assignable const&) = default;
  check_move_assignable& operator=(check_move_assignable &&) = delete;
};

template<typename T, bool v = is_trivially_destructible<T>::value>
struct dtor {
  using value_type = T;

  constexpr dtor() noexcept
    : null{} {}

  template<typename ...Args>
  constexpr explicit dtor(in_place_t, Args&&... args)
    : val(ss::forward<Args>(args)...),
      valid(true) {}

  void reset() {
    if (valid) {
      val.value_type::~value_type();
      valid = false;
    }
  }

  constexpr const        value_type* pointer() const noexcept { return addressof(val); }
  SS_CONSTEXPR_AFTER_14  value_type* pointer()       noexcept { return addressof(val); }

  constexpr const        value_type& ref() const&  noexcept { return val;       }
  SS_CONSTEXPR_AFTER_14  value_type& ref()      &  noexcept { return val;       }
  constexpr const        value_type& ref() const&& noexcept { return ss::move(val); }
  SS_CONSTEXPR_AFTER_14  value_type& ref()      && noexcept { return ss::move(val); }

  template<typename ...Args>
  void construct(Args&&... args) {
    ::new((void*)addressof(val)) value_type(ss::forward<Args>(args)...);
    valid = true;
  }

  template<typename Other>
  void construct_if(Other&& other) {
    if (other)
      construct(*ss::forward<Other>(other));
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
    : val(ss::forward<Args>(args)...),
      valid(true) {}

  void reset() {
    if (valid) {
      val.T::~T();
      valid = false;
    }
  }

  constexpr             const value_type* pointer() const { return addressof(val); }
  SS_CONSTEXPR_AFTER_14       value_type* pointer()       { return addressof(val); }

  constexpr             const value_type& ref() const&  { return val;        }
  SS_CONSTEXPR_AFTER_14       value_type& ref()      &  { return val;        }
  constexpr             const value_type& ref() const&& { return ss::move(val);  }
  SS_CONSTEXPR_AFTER_14       value_type& ref()      && { return ss::move(val);  }

  template<typename ...Args>
  void construct(Args&&... args) {
    ::new((void*)addressof(val)) value_type(ss::forward<Args>(args)...);
    valid = true;
  }

  template<typename Other>
  void construct_if(Other&& other) {
    if (other)
      construct(*ss::forward<Other>(other));
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

template<typename T, bool v = is_trivially_copy_constructible<T>::value>
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

template<typename T, bool v = is_trivially_move_constructible<T>::value>
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
  move_ctor(move_ctor && other) noexcept(is_nothrow_move_constructible<T>::value) {
    if (other.valid) {
      this->construct(ss::move(other.val));
    }
  }
  move_ctor& operator=(move_ctor const&) = default;
  move_ctor& operator=(move_ctor &&) = default;
};

template<typename T, bool v =
  is_trivially_copy_constructible<T>::value &&
  is_trivially_copy_assignable<T>::value &&
  is_trivially_destructible<T>::value>
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
  is_trivially_move_constructible<T>::value &&
  is_trivially_move_assignable<T>::value &&
  is_trivially_destructible<T>::value>
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
  noexcept(is_nothrow_move_assignable<T>::value && is_nothrow_move_constructible<T>::value)
  {
    if (!other.valid) {
      this->reset();
    } else {
      if (this->valid)
        this->val = ss::move(other.val);
      else
        this->construct(ss::move(other.val));
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

  static_assert(!is_reference<T>::value,
                "ss::optional : T must not be a reference type");
  static_assert(!is_same<remove_reference_t<decay_t<T>>, nullopt_t>::value,
                "ss::optional : T must not be ss::nullopt_t");
  static_assert(!is_same<remove_reference_t<decay_t<T>>, in_place_t>::value,
                "ss::optional : T must not be ss::in_place_t");
  static_assert(is_destructible<T>::value,
                "ss::optional : T must be destructible");
  static_assert(!is_array<T>::value,
                "ss::optional : T must be an array type");

  // constructors

  constexpr optional() noexcept = default;
  constexpr optional(nullopt_t) noexcept {};
  constexpr optional(const optional& other) = default;
  constexpr optional(optional&& other) = default;

  template<typename U,
    enable_if_t<
      is_constructible<value_type, const U&>::value &&
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value,
    int> = 0>
  SS_CONSTEXPR_AFTER_14 optional(const optional<U>& other) {
    this->construct_if(other);
  }

  template<typename U,
    enable_if_t<
      is_constructible<value_type, const U&>::value &&
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value &&
      !is_convertible<const U&, value_type>::value,
    int> = 0>
  SS_CONSTEXPR_AFTER_14 explicit optional(const optional<U>& other) {
    this->construct_if(other);
  }

  template<typename U,
    enable_if_t<
      is_constructible<value_type, U&&>::value &&
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value,
    int> = 0>
  SS_CONSTEXPR_AFTER_14 optional(optional<U>&& other) {
    this->construct_if(ss::move(other));
  }

  template<typename U,
    enable_if_t<
      is_constructible<value_type, U&&>::value &&
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value &&
      !is_convertible<U&&, value_type>::value,
    int> = 0>
  SS_CONSTEXPR_AFTER_14 explicit optional(optional<U>&& other) {
    this->construct_if(ss::move(other));
  }

  // Separated into 2 overloads to prevent MSVC from making an ambiguous call in C++14
  template<typename InPlaceT,
    enable_if_t<
      is_same<InPlaceT, in_place_t>::value &&
      is_constructible<value_type>::value,
    int> = 0>
  constexpr explicit optional(InPlaceT) : base(in_place) {}

  template<typename Arg, typename ...Args,
    enable_if_t<
      is_constructible<value_type, Arg, Args...>::value,
    int> = 0>
  constexpr explicit optional(in_place_t, Arg&& arg, Args&&... args)
    : base(in_place, ss::forward<Arg>(arg), ss::forward<Args>(args)...) {}

  template<typename U, typename ...Args,
    enable_if_t<
      is_constructible<value_type, std::initializer_list<U>&, Args&&...>::value,
    int> = 0>
  constexpr explicit optional(in_place_t, std::initializer_list<U> ilist, Args&&... args)
    : base(in_place, ilist, ss::forward<Args>(args)...) {}

  template<typename U = value_type,
    enable_if_t<
      is_constructible<value_type, U&&>::value &&
      is_convertible<U&&, value_type>::value &&
      !is_same<remove_cvref_t<U>, in_place_t>::value &&
      !is_same<remove_cvref_t<U>, optional<value_type>>::value,
    int> = 0>
  constexpr optional(U&& value)
    : base(in_place, ss::forward<U>(value)) {}

  template<typename U = value_type,
    enable_if_t<
      is_constructible<value_type, U&&>::value &&
      !is_convertible<U&&, value_type>::value &&
      !is_same<remove_cvref_t<U>, in_place_t>::value &&
      !is_same<remove_cvref_t<U>, optional<value_type>>::value,
    int> = 0>
  constexpr explicit optional(U&& value)
    : base(in_place, ss::forward<U>(value)) {}

  // assignment operators

  optional& operator=(nullopt_t) noexcept {
    this->reset();
    return *this;
  }

  SS_CONSTEXPR_AFTER_14 optional& operator=(optional const&) = default;
  SS_CONSTEXPR_AFTER_14 optional& operator=(optional &&) = default;

  template<typename U,
    enable_if_t<
      (is_constructible<value_type, U>::value &&
       is_assignable<value_type&, U>::value &&
       !is_same<remove_cvref_t<U>, optional>::value) &&
      (!is_scalar<value_type>::value ||
       !is_same<decay_t<U>, value_type>::value),
    int> = 0>
  optional& operator=(U&& value) {
    if (has_value()) {
      this->val = ss::forward<U>(value);
    } else {
      this->construct(ss::forward<U>(value));
    }
    return *this;
  }

  template<typename U,
    enable_if_t<
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value &&
      internal::optional::check_assignable   <value_type, optional<U>>::value &&
      is_constructible<value_type , const U&>::value &&
      is_assignable   <value_type&, const U&>::value,
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
    enable_if_t<
      internal::optional::check_constructible<value_type, optional<U>>::value &&
      internal::optional::check_convertible  <value_type, optional<U>>::value &&
      internal::optional::check_assignable   <value_type, optional<U>>::value &&
      is_constructible<value_type , U>::value &&
      is_assignable   <value_type&, U>::value,
    int> = 0>
  optional& operator=(optional<U>&& other) {
    if (other.has_value()) {
      if (this->has_value())
        this->val = ss::move(*other);
      else
        this->construct(ss::move(*other));
    } else { // !other.has_value()
      if (this->has_value())
        this->reset();
    }
    return *this;
  }


  constexpr             const value_type*  operator->() const { return this->pointer();    }
  SS_CONSTEXPR_AFTER_14       value_type*  operator->()       { return this->pointer();    }

  constexpr             const value_type&  operator*() const&  { return this->ref();       }
  SS_CONSTEXPR_AFTER_14       value_type&  operator*()      &  { return this->ref();       }
  constexpr             const value_type&& operator*() const&& { return ss::move(this->ref()); }
  SS_CONSTEXPR_AFTER_14       value_type&& operator*()      && { return ss::move(this->ref()); }

  constexpr inline explicit operator bool() const noexcept {
    return this->valid;
  }
  constexpr inline bool has_value() const noexcept {
    return this->valid;
  }

  SS_CONSTEXPR_AFTER_14 inline value_type& value() & {
    if (!this->has_value())
      throw bad_optional_access{};
    return this->ref();
  }
  SS_CONSTEXPR_AFTER_14 inline const value_type& value() const& {
    if (!this->has_value())
      throw bad_optional_access{};
    return this->ref();
  }
  SS_CONSTEXPR_AFTER_14 inline value_type&& value() && {
    if (!this->has_value())
      throw bad_optional_access{};
    return ss::move(this->ref());
  }
  SS_CONSTEXPR_AFTER_14 inline const value_type&& value() const && {
    if (!this->has_value())
      throw bad_optional_access{};
    return ss::move(this->ref());
  }

  template<typename U>
  constexpr value_type value_or(U&& default_value) const & {
    static_assert(is_copy_constructible<value_type>::value,
                  "ss::optional<T>::value_or : T must be copy constructible");
    static_assert(is_convertible<U&&, value_type>::value,
                  "ss::optional<T>::value_or : U&& must be convertible to T");

    return this->has_value() ? **this : static_cast<value_type>(ss::forward<U>(default_value));
  }

  template<typename U>
  SS_CONSTEXPR_AFTER_14 value_type value_or(U&& default_value) && {
    static_assert(is_move_constructible<value_type>::value,
                  "ss::optional<T>::value_or : T must be move constructible");
    static_assert(is_convertible<U&&, value_type>::value,
                  "ss::optional<T>::value_or : U&& must be convertible to T");

    return this->has_value() ? ss::move(**this) : static_cast<value_type>(ss::forward<U>(default_value));
  }

  void swap(optional& other)
    noexcept(is_nothrow_move_constructible<value_type>::value && is_nothrow_swappable<value_type>::value)
  {
    static_assert(is_move_constructible<value_type>::value,
                  "ss::optional<T>::swap : T must be move constructible");

    if (other.has_value()) {
      if (this->has_value()) {
        swap(**this, *other);
      } else { // !this->has_value()
        this->construct(ss::move(*other));
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
    enable_if_t<
      is_same<Dummy, void>::value &&
      is_constructible<value_type>::value,
    int> = 0>
  value_type& emplace() {
    this->reset();
    this->construct();
    return **this;
  }

  template<typename Arg, typename ...Args,
    enable_if_t<
      is_constructible<value_type, Arg, Args...>::value,
    int> = 0>
  value_type& emplace(Arg&& arg, Args&&... args) {
    this->reset();
    this->construct(ss::forward<Arg>(arg), ss::forward<Args>(args)...);
    return **this;
  }

  template<typename U, typename ...Args,
    enable_if_t<
      is_constructible<value_type, std::initializer_list<U>&, Args&&...>::value,
    int> = 0>
  value_type& emplace(std::initializer_list<U> ilist, Args&&... args) {
    this->reset();
    this->construct(ilist, ss::forward<Args>(args)...);
    return **this;
  }

};

# if SS_CXX_VER >= 17
template<class T> optional(T) -> optional<T>;
# endif

template<typename T>
constexpr inline optional<decay_t<T>> make_optional(T&& value) {
  return optional<decay_t<T>>(ss::forward<T>(value));
}

template<typename T, typename ...Args>
constexpr inline optional<T> make_optional(Args&&... args) {
  return optional<T>(in_place, ss::forward<Args>(args)...);
}

template<typename T, typename U, typename ...Args>
constexpr inline optional<T> make_optional(std::initializer_list<U> ilist, Args&&... args) {
  return optional<T>(in_place, ilist, ss::forward<Args>(args)...);
}

// compare two optional objects

template<typename T, typename U >
constexpr bool operator==(const optional<T>& lhs, const optional<U>& rhs) {
  return
    bool(lhs) != bool(rhs) ? false :
    !lhs ? true :
    *lhs == *rhs;
}

template<typename T, typename U >
constexpr bool operator!=(const optional<T>& lhs, const optional<U>& rhs) {
  return
    bool(lhs) != bool(rhs) ? true :
    !lhs ? false :
    lhs != rhs;
}

template<typename T, typename U >
constexpr bool operator<(const optional<T>& lhs, const optional<U>& rhs) {
  return
    !rhs.has_value() ? false :
    !lhs.has_value() ? true :
    *lhs < *rhs;
}

template<typename T, typename U >
constexpr bool operator<=(const optional<T>& lhs, const optional<U>& rhs) {
  return
    !lhs.has_value() ? true :
    !rhs.has_value() ? false :
    *lhs <= *rhs;
}

template<typename T, typename U >
constexpr bool operator>(const optional<T>& lhs, const optional<U>& rhs) {
  return
    !lhs.has_value() ? false :
    !rhs.has_value() ? true :
    *lhs > *rhs;
}

template<typename T, typename U >
constexpr bool operator>=(const optional<T>& lhs, const optional<U>& rhs) {
  return
    !rhs.has_value() ? true :
    !lhs.has_value() ? false :
    *lhs >= *rhs;
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
