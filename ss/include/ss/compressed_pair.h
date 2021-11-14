# /*
#  * Created by YongGyu Lee on 2021/11/14.
#  */
#
# ifndef SS_COMPRESSED_PAIR_H_
# define SS_COMPRESSED_PAIR_H_
#
# include "ss/detail/macro.h"
#
# include "ss/type_traits.h"
# include "ss/utility.h"

namespace ss {


namespace detail {

template<typename T, size_t index, bool v = is_empty<T>::value>
struct compressed_slot {
  constexpr compressed_slot() = default;

  template<typename U, enable_if_t<is_not_same<decay_t<U>, compressed_slot>::value, int> = 0>
  constexpr compressed_slot(U&& u) : value(ss::forward<U>(u)) {}

 protected:
  SS_CONSTEXPR_AFTER_14 T&       get()       noexcept { return value; }
  SS_CONSTEXPR_AFTER_14 const T& get() const noexcept { return value; }

 private:
  T value;
};

template<typename T, size_t index>
struct compressed_slot<T, index, true> : public T {
  constexpr compressed_slot() = default;

  template<typename U, enable_if_t<is_not_same<decay_t<U>, compressed_slot>::value, int> = 0>
  constexpr compressed_slot(U&& u) : T(ss::forward<U>(u)) {}

 protected:
  SS_CONSTEXPR_AFTER_14 T&       get()       noexcept { return static_cast<T&>(*this); }
  SS_CONSTEXPR_AFTER_14 const T& get() const noexcept { return static_cast<const T&>(*this); }
};

} // namespace detail



template<typename T, typename U, bool v = is_empty<T>::value>
class compressed_pair : private detail::compressed_slot<T, 0>, private detail::compressed_slot<U, 1> {
 private:
  using first_base = detail::compressed_slot<T, 0>;
  using second_base = detail::compressed_slot<U, 1>;

  using first_base::first_base;
  using second_base::second_base;

 public:
  constexpr compressed_pair() = default;

  template<typename T2>
  constexpr compressed_pair(T2&& t2) : first_base(ss::forward<T2>(t2)) {}

  template<typename T2, typename U2>
  constexpr compressed_pair(T2&& t2, U2&& u2) : first_base(ss::forward<T2>(t2)), second_base(ss::forward<U2>(u2)) {}

  SS_CONSTEXPR_AFTER_14 T&       first()       noexcept { return first_base::get(); }
  SS_CONSTEXPR_AFTER_14 const T& first() const noexcept { return first_base::get(); }

  SS_CONSTEXPR_AFTER_14 U&       second()       noexcept { return second_base::get(); }
  SS_CONSTEXPR_AFTER_14 const U& second() const noexcept { return second_base::get(); }

  SS_CONSTEXPR_AFTER_14 void swap(compressed_pair& other)
  noexcept(is_nothrow_swappable<T>::value && is_nothrow_swappable<U>::value)
  {
    using ss::swap;
    swap(first(), other.first());
    swap(second(), other.second());
  }
};



template<typename T>
class compressed_pair<T, T, true> : private detail::compressed_slot<T, 0> {
 private:
  using first_base = detail::compressed_slot<T, 0>;
  using second_base = first_base;

 public:
  constexpr compressed_pair() = default;

  template<typename T2>
  constexpr compressed_pair(T2&& t2) : first_base(ss::forward<T2>(t2)) {}

  template<typename T2, typename U2>
  constexpr compressed_pair(T2&& t2, U2&& u2) : first_base(ss::forward<T2>(t2)) {}

  SS_CONSTEXPR_AFTER_14 T&       first()       noexcept { return first_base::get(); }
  SS_CONSTEXPR_AFTER_14 const T& first() const noexcept { return first_base::get(); }

  SS_CONSTEXPR_AFTER_14 T&       second()       noexcept { return second_base::get(); }
  SS_CONSTEXPR_AFTER_14 const T& second() const noexcept { return second_base::get(); }

  SS_CONSTEXPR_AFTER_14 void swap(compressed_pair& other) noexcept(is_nothrow_swappable<T>::value) {
    using ss::swap;
    swap(first(), other.first());
  }
};



template<typename T>
class compressed_pair<T, T, false> : private detail::compressed_slot<T, 0>,
                                     private detail::compressed_slot<T, 1> {
 private:
  using first_base = detail::compressed_slot<T, 0>;
  using second_base = detail::compressed_slot<T, 1>;

 public:
  constexpr compressed_pair() = default;

  template<typename T2>
  constexpr compressed_pair(T2&& t2) : first_base(ss::forward<T2>(t2)) {}

  template<typename T2, typename U2>
  constexpr compressed_pair(T2&& t2, U2&& u2) : first_base(ss::forward<T2>(t2)), second_base(ss::forward<U2>(u2)) {}

  SS_CONSTEXPR_AFTER_14 T&       first()       noexcept { return first_base::get(); }
  SS_CONSTEXPR_AFTER_14 const T& first() const noexcept { return first_base::get(); }

  SS_CONSTEXPR_AFTER_14 T&       second()       noexcept { return second_base::get(); }
  SS_CONSTEXPR_AFTER_14 const T& second() const noexcept { return second_base::get(); }

  SS_CONSTEXPR_AFTER_14 void swap(compressed_pair& other) noexcept(is_nothrow_swappable<T>::value) {
    using ss::swap;
    swap(first(), other.first());
    swap(second(), other.second());
  }
};

template<typename T, typename U>
SS_CONSTEXPR_AFTER_14 void swap(compressed_pair<T, U>& lhs, compressed_pair<T, U>& rhs)
noexcept(conjunction<is_nothrow_swappable<T>, is_nothrow_swappable<U>>::value)
{
  lhs.swap(rhs);
}

}

#endif // SS_COMPRESSED_PAIR_H_
