# /*
#  * Created by YongGyu Lee on 2022/01/17.
#  */
#
# ifndef SS_ARRAY_H_
# define SS_ARRAY_H_
#
# include <cstddef> // size_t, ptrdiff_t
#
# include <exception>
#
# include "ss/detail/assert.h"
# include "ss/algorithm.h"
# include "ss/iterator.h"
# include "ss/utility.h"

namespace ss {

template<typename T, size_t N>
struct array {
  using value_type      = T;
  using size_type       = size_t;
  using difference_type = ptrdiff_t;
  using reference       = value_type&;
  using const_reference = const value_type&;
  using pointer         = value_type*;
  using const_pointer   = const value_type*;
  using iterator        = pointer;
  using const_iterator  = const_pointer;
  // TODO: Complete ss::reverse_iterator
  using reverse_iterator        = ss::reverse_iterator<iterator>;
  using const_reverse_iterator  = ss::reverse_iterator<const_iterator>;

 private:
  void throw_range() const {
    throw std::out_of_range("ss::array::at : Out of range");
  }


 public:

  SS_NODISCARD SS_CONSTEXPR_AFTER_14 reference at(size_type pos) {
    if (pos >= size()) {
      throw_range();
    }
    return elements[pos];
  }

  SS_NODISCARD SS_CONSTEXPR_AFTER_14 reference at(size_type pos) const {
    if (pos >= size()) {
      throw_range();
    }
    return elements[pos];
  }

  SS_CONSTEXPR_AFTER_14 reference operator[](size_type pos) {
    SS_DEBUG_ASSERT(pos < size(), "ss::array : Index out of bounds");
    return elements[pos];
  }
  SS_CONSTEXPR_AFTER_14 const_reference operator[](size_type pos) const {
    SS_DEBUG_ASSERT(pos < size(), "ss::array : Index out of bounds");
    return elements[pos];
  }

  SS_CONSTEXPR_AFTER_14 reference front()       { return (*this)[0]; }
  constexpr       const_reference front() const { return (*this)[0]; }
  SS_CONSTEXPR_AFTER_14 reference back()        { return (*this)[size() - 1]; }
  constexpr       const_reference back()  const { return (*this)[size() - 1]; }

  SS_CONSTEXPR_AFTER_14 T* data()       noexcept { return elements; }
  constexpr       const T* data() const noexcept { return elements; }

  SS_CONSTEXPR_AFTER_14 iterator begin()  noexcept { return iterator      (data()); }
  constexpr const_iterator begin()  const noexcept { return const_iterator(data()); }
  constexpr const_iterator cbegin() const noexcept { return const_iterator(data()); }
  SS_CONSTEXPR_AFTER_14 iterator end()    noexcept { return iterator      (data() + size()); }
  constexpr const_iterator end()    const noexcept { return const_iterator(data() + size()); }
  constexpr const_iterator cend()   const noexcept { return const_iterator(data() + size()); }

  SS_CONSTEXPR_AFTER_14 reverse_iterator rbegin()  noexcept { return reverse_iterator      (end()); }
  constexpr const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator(end()); }
  constexpr const_reverse_iterator rcbegin() const noexcept { return const_reverse_iterator(end()); }
  SS_CONSTEXPR_AFTER_14 reverse_iterator rend()    noexcept { return reverse_iterator      (begin()); }
  constexpr const_reverse_iterator rend()    const noexcept { return const_reverse_iterator(begin()); }
  constexpr const_reverse_iterator rcend()   const noexcept { return const_reverse_iterator(begin()); }

  SS_NODISCARD constexpr bool empty() const noexcept {
    return size() == 0;
  }

  SS_NODISCARD constexpr size_type size() const noexcept {
    return N;
  }

  SS_NODISCARD constexpr size_type max_size() const noexcept {
    return N;
  }

  SS_CONSTEXPR_AFTER_14 void fill(const T& value) {
    ss::fill_n(data(), size(), value);
  }

  SS_CONSTEXPR_AFTER_14 void swap(array& other) noexcept(is_nothrow_swappable<T>::value) {
    ss::swap_ranges(begin(), end(), other.begin());
  }

  T elements[N];
};

template<typename T, size_t N>
constexpr bool operator==(const array<T, N>& lhs, const array<T, N>& rhs) {
  return ss::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template<typename T, size_t N>
constexpr bool operator!=(const array<T, N>& lhs, const array<T, N>& rhs) {
  return !(lhs == rhs);
}

template<typename T, size_t N>
constexpr bool operator<(const array<T, N>& lhs, const array<T, N>& rhs) {
  return ss::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template<typename T, size_t N>
constexpr bool operator<=(const array<T, N>& lhs, const array<T, N>& rhs) {
  return !(rhs < lhs);
}

template<typename T, size_t N>
constexpr bool operator>(const array<T, N>& lhs, const array<T, N>& rhs) {
  return rhs < lhs;
}

template<typename T, size_t N>
constexpr bool operator>=(const array<T, N>& lhs, const array<T, N>& rhs) {
  return !(lhs < rhs);
}

// TODO: operator<=>




/**
 * swap(ss::array)
 * @tparam T
 * @tparam N
 * @param lhs
 * @param rhs
 * @return
 */
template<typename T, size_t N>
SS_CONSTEXPR_AFTER_14
enable_if_t<disjunction<bool_constant<N == 0>,
                        is_swappable<T>>::value,
            void>
swap(ss::array<T, N>& lhs, ss::array<T, N>& rhs)
noexcept(noexcept(lhs.swap(rhs)))
{
  lhs.swap(rhs);
}


namespace detail {

template<typename T, size_t N, size_t... I>
constexpr array<remove_cv_t<T>, N> to_array_impl(T (&a)[N], index_sequence<I...>) {
  return array<remove_cv_t<T>, N>{a[I]...};
}

template<typename T, size_t N, size_t... I>
constexpr array<remove_cv_t<T>, N> to_array_impl(T (&&a)[N], index_sequence<I...>) {
  return array<remove_cv_t<T>, N>{ss::move(a[I])...};
}

} // namespace detail


/**
 * to_array
 * @tparam T
 * @tparam N
 * @param a
 * @return
 */
template<typename T, size_t N,
  enable_if_t<
    detail::CopyConstructible<T>::value,
    int> = 0>
constexpr array<remove_cv_t<T>, N> to_array(T (&a)[N]) {
  static_assert(!is_array<T>::value, "ss::to_array : Array must be one-dimensional");
  static_assert(is_constructible<T, T&>::value, "ss::to_array(T (&a)[N]) : T must be copy constructible");
  return detail::to_array_impl(a, make_index_sequence<N>{});
}

template<typename T, size_t N,
  enable_if_t<
    detail::MoveConstructible<T>::value,
    int> = 0>
constexpr array<remove_cv_t<T>, N> to_array(T (&&a)[N]) {
  static_assert(!is_array<T>::value, "ss::to_array : Array must be one-dimensional");
  return detail::to_array_impl(ss::move(a), make_index_sequence<N>{});
}


/**
 * tuple_size<ss::array>
 * @tparam T
 * @tparam N
 */
template<typename T, size_t N>
struct tuple_size<array<T, N>> : integral_constant<size_t, N> {};



/**
 * tuple_element<ss::array>
 * @tparam I
 * @tparam T
 * @tparam N
 */
template<size_t I, typename T, size_t N>
struct tuple_element<I, array<T, N>> {
  static_assert(I < N, "ss::tuple_element<I, array<T, N>> : Index out of bounds");
  using type = T;
};


/**
 * get(ss::array)
 * @tparam I
 * @param a
 * @return
 */
template<size_t I, typename T, size_t N>
constexpr T& get(array<T, N>& a) noexcept {
  static_assert(I < N, "ss::get(ss::array) : Index out of bounds");
  return a.elements[I];
}

template<size_t I, typename T, size_t N>
constexpr T&& get(array<T, N>&& a) noexcept {
  static_assert(I < N, "ss::get(ss::array) : Index out of bounds");
  return ss::move(a.elements[I]);
}

template<size_t I, typename T, size_t N>
constexpr const T& get(const array<T, N>& a) noexcept {
  static_assert(I < N, "ss::get(ss::array) : Index out of bounds");
  return a.elements[I];
}

template<size_t I, typename T, size_t N>
constexpr const T&& get(const array<T, N>&& a) noexcept {
  static_assert(I < N, "ss::get(ss::array) : Index out of bounds");
  return ss::move(a.elements[I]);
}

} // namespace ss

# endif // SS_ARRAY_H_
