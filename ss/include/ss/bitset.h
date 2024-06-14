# /*
#  * Created by YongGyu Lee on 2022/01/25.
#  */
#
# ifndef SS_BITSET_H_
# define SS_BITSET_H_
# 
# include <cstddef>
#
# include "ss/detail/macro.h"
# include "ss/algorithm.h"
# include "ss/istream.h"
# include "ss/locale.h"
# include "ss/__functional/hash.h"
# include "ss/ostream.h"
# include "ss/__string/char_traits.h"
# include "ss/__stdexcept/invalid_argument.h"
# include "ss/__stdexcept/out_of_range.h"
# include "ss/__stdexcept/overflow_error.h"
# include "ss/string.h"
# include "ss/type_traits.h"

namespace ss {

namespace detail {

template<size_t d>
struct static_op;

template<> struct static_op<0x0> {
  static constexpr bool is_pow2 = true;
  template<typename T> static constexpr T mul(T x) noexcept { return x; } };

template<> struct static_op<0x1> {
  static constexpr bool is_pow2 = true;
  static constexpr size_t log2 = 0;
  template<typename T> static constexpr T div(T x) noexcept { return x; }
  template<typename T> static constexpr T mul(T x) noexcept { return x; }
  template<typename T> static constexpr T mod(T x) noexcept { return 0; } };
template<> struct static_op<0x2> {
  static constexpr bool is_pow2 = true;
  static constexpr size_t log2 = 1;
  template<typename T> static constexpr T div(T x) noexcept { return x >> 1; }
  template<typename T> static constexpr T mul(T x) noexcept { return x << 1; }
  template<typename T> static constexpr T mod(T x) noexcept { return x & 0x1; } };
template<> struct static_op<0x4> {
  static constexpr bool is_pow2 = true;
  static constexpr size_t log2 = 2;
  template<typename T> static constexpr T div(T x) noexcept { return x >> 2; }
  template<typename T> static constexpr T mul(T x) noexcept { return x << 2; }
  template<typename T> static constexpr T mod(T x) noexcept { return x & 0x3; } };
template<> struct static_op<0x8> {
  static constexpr bool is_pow2 = true;
  static constexpr size_t log2 = 3;
  template<typename T> static constexpr T div(T x) noexcept { return x >> 3; }
  template<typename T> static constexpr T mul(T x) noexcept { return x << 3; }
  template<typename T> static constexpr T mod(T x) noexcept { return x & 0x7; } };
template<> struct static_op<0x10> {
  static constexpr bool is_pow2 = true;
  static constexpr size_t log2 = 4;
  template<typename T> static constexpr T div(T x) noexcept { return x >> 4; }
  template<typename T> static constexpr T mul(T x) noexcept { return x << 4; }
  template<typename T> static constexpr T mod(T x) noexcept { return x & 0xF; } };
template<> struct static_op<0x20> {
  static constexpr bool is_pow2 = true;
  static constexpr size_t log2 = 5;
  template<typename T> static constexpr T div(T x) noexcept { return x >> 5; }
  template<typename T> static constexpr T mul(T x) noexcept { return x << 5; }
  template<typename T> static constexpr T mod(T x) noexcept { return x & 0x1F; } };
template<> struct static_op<0x40> {
  static constexpr bool is_pow2 = true;
  static constexpr size_t log2 = 6;
  template<typename T> static constexpr T div(T x) noexcept { return x >> 6; }
  template<typename T> static constexpr T mul(T x) noexcept { return x << 6; }
  template<typename T> static constexpr T mod(T x) noexcept { return x & 0x3F; } };
template<> struct static_op<0x80> {
  static constexpr bool is_pow2 = true;
  static constexpr size_t log2 = 7;
  template<typename T> static constexpr T div(T x) noexcept { return x >> 7; }
  template<typename T> static constexpr T mul(T x) noexcept { return x << 7; }
  template<typename T> static constexpr T mod(T x) noexcept { return x & 0x7F; } };

template<size_t d>
struct static_op {
  template<typename T> static constexpr T div(T x) noexcept { return x / d; }
  template<typename T> static constexpr T mul(T x) noexcept { return x * d; }
  template<typename T> static constexpr T mod(T x) noexcept { return x % d; }
};

// TODO: Move to elsewhere & generalize
void bitset_throw_range() {
  throw out_of_range("ss::bitset::bitset : pos out of range from str");
}

void throw_overflow(const char* msg) {
  throw overflow_error(msg);
}

void bitset_throw_invalid_argument(const char* msg) {
  throw invalid_argument("ss::bitset::bitset : invalid character detected");
}

} // namespace detail

template<typename Key>
struct hash;


template<size_t N>
class bitset {
  // TODO: Optimize storage size
  using element_type = size_t;
 public:
  class reference {
   public:
    reference& operator=(const reference& x) noexcept {
      src_.set_bit(x.index_, x);
      return *this;
    }
    reference& operator=(bool x) noexcept {
      src_.set_bit(index_, x);
      return *this;
    }

    operator bool() const noexcept {
      return src_.get_bit(index_);
    }

    bool operator~() const noexcept {
      return !src_.get_bit(index_);
    }

    reference& flip() noexcept {
      src_.flip_bit(index_);
      return *this;
    }

   private:
    constexpr reference(bitset& b, size_t i) noexcept : src_(b), index_(i) {}

    size_t index_;
    bitset& src_;
    friend class bitset;
  };

  // bitset member functions

  constexpr bitset() noexcept : bits_{} {}

  constexpr bitset(unsigned long long val) noexcept : bits_{val} {}

  template<typename CharT, typename Traits, typename Alloc>
  SS_CONSTEXPR_AFTER_14 explicit bitset(
      const basic_string<CharT, Traits, Alloc>& str,
      typename basic_string<CharT, Traits, Alloc>::size_type pos = 0,
      typename basic_string<CharT, Traits, Alloc>::size_type n = basic_string<CharT, Traits, Alloc>::npos,
      CharT zero = CharT('0'),
      CharT one = CharT('1'))
  {
    if (pos > str.size())
      ss::detail::bitset_throw_range();

    const auto str_len = ss::min(n, str.size() - pos);
    const auto len = ss::min(str_len, N);
    size_t i = 0;

    // TODO: Optimize
    for (; i < len; ++i) {
      const auto c = str[pos + len - 1 - i];
      if (Traits::eq(c, zero)) {
        set_bit(i, 0);
      } else if (Traits::eq(c, one)) {
        set_bit(i, 1);
      } else {
        throw invalid_argument("ss::bitset::bitset : invalid character detected");
      }
    }

    for(; i < N; ++i) {
      set_bit(i, 0);
    }
  }

  template<typename CharT>
  explicit bitset(const CharT* str,
                  typename basic_string<CharT>::size_type n = basic_string<CharT>::npos,
                  CharT zero = CharT('0'),
                  CharT one = CharT('1'))
      : bitset(n == basic_string<CharT>::npos ? basic_string<CharT>(str) :
               basic_string<CharT>(str, n),
               0, n, zero, one) {}

  bool operator==(const bitset& rhs) const noexcept {
    // TODO: Optimize
    for (size_t i = 0; i < storage_size - 1; ++i) {
      if (bits_[i] != rhs.bits_[i])
        return false;
    }

    size_t i = element_bit * (storage_size - 1);
    for (; i < N; ++i) {
      if (get_bit(i) != rhs.get_bit(i))
        return false;
    }

    return true;
  }

# if SS_CXX_VER < 20
  bool operator!=(const bitset& rhs) const noexcept {
    return !(*this == rhs);
  }
# endif

  constexpr bool operator[](size_t pos) const { return get_bit(pos); }
  reference operator[](size_t pos) { return reference(*this, pos); }

  bool test(size_t pos) const {
    if (pos >= N)
      ss::detail::bitset_throw_range();

    return get_bit(pos);
  }

  bool all() const noexcept {
    // TODO: Optimize
    for (size_t i = 0; i < N; ++i) {
      if (get_bit(i) == 0)
        return false;
    }

    return true;
  }

  bool any() const noexcept {
    return !none();
  }

  bool none() const noexcept {
    // TODO: Optimize
    for (size_t i = 0; i < storage_size - 1; ++i) {
      if (bits_[i])
        return false;
    }

    size_t i = element_bit * (storage_size - 1);
    for (; i < N; ++i) {
      if (get_bit(i))
        return false;
    }

    return true;
  }


  size_t count() const noexcept {
    // TODO: Optimize
    size_t sum = 0;
    for (size_t i = 0; i < N; ++i) {
      sum += get_bit(i);
    }
    return sum;
  }

  constexpr size_t size() const noexcept {
    return N;
  }

  bitset& operator&=(const bitset& other) noexcept {
    for (size_t i = 0; i < storage_size; ++i) {
      bits_[i] &= other.bits_[i];
    }
    return *this;
  }

  bitset& operator|=(const bitset& other) noexcept {
    for (size_t i = 0; i < storage_size; ++i) {
      bits_[i] |= other.bits_[i];
    }
    return *this;
  }

  bitset& operator^=(const bitset& other) noexcept {
    for (size_t i = 0; i < storage_size; ++i) {
      bits_[i] ^= other.bits_[i];
    }
    return *this;
  }

  bitset operator~() noexcept {
    return bitset(*this).flip();
  }

  bitset operator<<(size_t pos) const noexcept {
    bitset ret(*this);
    ret <<= pos;
    return ret;
  }

  bitset& operator<<=(size_t pos) noexcept {
    for (size_t i = 0; i < storage_size; ++i)
      bits_[i] <<= pos;
    return *this;
  }

  bitset operator>>(size_t pos) const noexcept {
    bitset ret(*this);
    ret >>= pos;
    return ret;
  }

  bitset& operator>>=(size_t pos) noexcept {
    for (size_t i = 0; i < storage_size; ++i)
      bits_[i] >>= pos;
    return *this;
  }

  bitset& set() noexcept {
    // TODO: Optimize
    for (size_t i = 0; i < N; ++i) {
      set_bit(i, true);
    }

    return *this;
  }

  bitset& set(size_t pos, bool value = true) {
    if (pos >= N)
      ss::detail::bitset_throw_range();

    set_bit(pos, value);
    return *this;
  }

  bitset& reset() noexcept {
    // TODO: Optimize
    for (size_t i = 0; i < storage_size - 1; ++i) {
      bits_[i] = 0;
    }

    size_t i = element_bit * (storage_size - 1);
    for (; i < N; ++i) {
      set_bit(i, 0);
    }

    return *this;
  }

  bitset& reset(size_t pos) {
    if (pos >= N)
      ss::detail::bitset_throw_range();

    set_bit(pos, 0);
    return *this;
  }

  bitset& flip() noexcept {
    // TODO: Optimize
    for (size_t i = 0; i < storage_size - 1; ++i) {
      bits_[i] = ~bits_[i];
    }

    size_t i = element_bit * (storage_size - 1);
    for (; i < N; ++i) {
      flip_bit(i);
    }

    return *this;
  }

  bitset& flip(size_t pos) {
    if (pos >= N)
      ss::detail::bitset_throw_range();

    flip_bit(pos);
    return *this;
  }

  template<typename CharT = char,
      typename Traits = char_traits<CharT>,
      typename Allocator = allocator<CharT>>
  basic_string<CharT,Traits,Allocator>
  to_string(CharT zero = CharT('0'), CharT one = CharT('1')) const {
    // TODO: Optimize?
    basic_string<CharT,Traits,Allocator> result(N, '\0');
    for (size_t i = 0; i < N; ++i) {
      result[i] = get_bit(N - 1 - i) ? one : zero;
    }
    return result;
  }

  constexpr unsigned long to_ulong() const {
    return to_type<unsigned long>("ss::bitset::to_ulong : overflow error");
  }

  constexpr unsigned long long to_ullong() const {
    return to_type<unsigned long long>("ss::bitset::to_ullong : overflow error");
  }

 private:
  template<typename T>
  constexpr T to_type(const char* overflow_msg) const {
    return to_type_impl<T>(overflow_msg, bool_constant<(N <= sizeof(T) * CHAR_BIT)>{});
  }

  template<typename T>
  constexpr T to_type_impl(const char*, true_type/* N <= bit */) const {
    return static_cast<T>(bits_[0]);
  }

  template<typename T>
  SS_CONSTEXPR_AFTER_14 T to_type_impl(const char* overflow_msg, false_type /* N > bit */) const {
    constexpr size_t type_bit = sizeof(T) * CHAR_BIT;

    for (size_t i = type_bit; i < element_bit; ++i) {
      if (get_bit(i) != 0)
        ss::detail::throw_overflow(overflow_msg);
    }

    for (size_t i = 1; i < storage_size; ++i) {
      if (bits_[i] > 0)
        ss::detail::throw_overflow(overflow_msg);
    }

    return static_cast<T>(bits_[0]);
  }

  static constexpr size_t element_bit = sizeof(element_type) * CHAR_BIT;
  static constexpr size_t storage_size = (detail::static_max<size_t, N, 1>::value + (element_bit - 1)) / element_bit;

  constexpr bool get_bit(size_t i) const noexcept {
    return bits_[detail::static_op<element_bit>::div(i)] & (((element_type)0x1) << detail::static_op<element_bit>::mod(i));
  }

  SS_CONSTEXPR_AFTER_14 void set_bit(size_t i, bool x) noexcept {
    if (x) { // x == 1
      bits_[detail::static_op<element_bit>::div(i)] |= (((element_type)0x1) << detail::static_op<element_bit>::mod(i));
    } else { // x == 0
      bits_[detail::static_op<element_bit>::div(i)] &= ~(((element_type)0x1) << detail::static_op<element_bit>::mod(i));
    }
  }

  SS_CONSTEXPR_AFTER_14 void flip_bit(size_t i) noexcept {
    bits_[detail::static_op<element_bit>::div(i)] ^= (((element_type)0x1) << detail::static_op<element_bit>::mod(i));
  }

  friend class hash<bitset>;

  element_type bits_[storage_size];
};

template<size_t N>
bitset<N> operator&(const bitset<N>& lhs, const bitset<N>& rhs) noexcept {
return bitset<N>(lhs) &= rhs;
}

template<size_t N>
bitset<N> operator|(const bitset<N>& lhs, const bitset<N>& rhs) noexcept {
return bitset<N>(lhs) |= rhs;
}

template<size_t N>
bitset<N> operator^(const bitset<N>& lhs, const bitset<N>& rhs) noexcept {
return bitset<N>(lhs) ^= rhs;
}

template<class CharT, class Traits, size_t N>
basic_ostream<CharT, Traits>&
operator<<(basic_ostream<CharT, Traits>& os, const bitset<N>& x) {
  os << x.to_string(ss::use_facet<ctype<CharT> >(os.getloc()).widen('0'),
                    ss::use_facet<ctype<CharT> >(os.getloc()).widen('1'));
  return os;
}

template<class CharT, class Traits, size_t N>
basic_istream<CharT, Traits>&
operator>>(basic_istream<CharT, Traits>& is, bitset<N>& x) {
  // TODO
  return is;
}

template<size_t N>
struct hash<bitset<N>> {
  size_t operator()(const bitset<N>& key) const noexcept {
    return detail::hash_array(key.bits_);
  }
};

} // namespace ss

# endif // SS_BITSET_H_
