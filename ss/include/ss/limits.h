# /*
#  * Created by YongGyu Lee on 2021/11/11.
#  */
#
# ifndef SS_LIMITS_H_
# define SS_LIMITS_H_
#
# include <cfloat>
# include <climits>
# include <cmath>
# include <cstdint>
# include <limits>
#
# include "ss/__config.h"
# include "ss/__deprecated.h"
# include "ss/type_traits.h"

#define SS_DEPRECATED_DENORM_CXX23 SS_DEPRECATED_AFTER_CXX_23("")
#define SS_DEPRECATED_DENORM_LOSS_CXX23 SS_DEPRECATED_AFTER_CXX_23("")

#if defined(INFINITY)
#define SS_DEFINED_INFINITY 1
#else
#define SS_DEFINED_INFINITY 0
#endif

namespace ss {

namespace detail {

template<typename T, typename R = int>
constexpr inline R rough_ceil(T x) {
  return static_cast<R>(x) + ((static_cast<R>(x) == x) ? 0 : 1);
}

} // namespace detail

enum float_round_style {
  round_indeterminate       = -1,
  round_toward_zero         = 0,
  round_to_nearest          = 1,
  round_toward_infinity     = 2,
  round_toward_neg_infinity = 3
};

enum float_denorm_style {
  denorm_indeterminate = -1,
  denorm_absent        = 0,
  denorm_present       = 1
};

template<typename T>
class numeric_limits {
 public:
  static constexpr bool is_specialized = false;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = false;
  static constexpr bool is_modulo = false;
  static constexpr int digits = 0;
  static constexpr int digits10 = 0;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 0;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr T min() noexcept { return T(); }
  static constexpr T lowest() noexcept { return T(); }
  static constexpr T max() noexcept { return T(); }
  static constexpr T epsilon() noexcept { return T(); }
  static constexpr T round_error() noexcept { return T(); }
  static constexpr T infinity() noexcept { return T(); }
  static constexpr T quiet_NaN() noexcept { return T(); }
  static constexpr T signaling_NaN() noexcept { return T(); }
  static constexpr T denorm_min() noexcept { return T(); }
};

#if SS_HAS_TYPE_BOOL
template<>
class numeric_limits<bool> {
 public:
  using type = bool;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = 1;
  static constexpr int digits10 = 0;
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return false; }
  static constexpr type lowest() noexcept { return false; }
  static constexpr type max() noexcept { return true; }
  static constexpr type epsilon() noexcept { return false; }
  static constexpr type round_error() noexcept { return false; }
  static constexpr type infinity() noexcept { return false; }
  static constexpr type quiet_NaN() noexcept { return false; }
  static constexpr type signaling_NaN() noexcept { return false; }
  static constexpr type denorm_min() noexcept { return false; }
};
#endif

#if SS_HAS_TYPE_CHAR
template<>
class numeric_limits<char> {
 public:
  using type = char;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = (type(-1) < type(0));
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT - is_signed;
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return CHAR_MIN; }
  static constexpr type lowest() noexcept { return CHAR_MIN; }
  static constexpr type max() noexcept { return CHAR_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_SIGNED_CHAR
template<>
class numeric_limits<signed char> {
 public:
  using type = signed char;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT - 1;
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return SCHAR_MIN; }
  static constexpr type lowest() noexcept { return SCHAR_MIN; }
  static constexpr type max() noexcept { return SCHAR_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_UNSIGNED_CHAR
template<>
class numeric_limits<unsigned char> {
 public:
  using type = unsigned char;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT;
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return 0; }
  static constexpr type lowest() noexcept { return 0; }
  static constexpr type max() noexcept { return UCHAR_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_WCHAR_T
template<>
class numeric_limits<wchar_t> {
 public:
  using type = wchar_t;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = (type(-1) < type(0));
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(type) - is_signed;
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return WCHAR_MIN; }
  static constexpr type lowest() noexcept { return WCHAR_MIN; }
  static constexpr type max() noexcept { return WCHAR_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_CHAR8_T
template<>
class numeric_limits<char8_t> {
 public:
  using type = char8_t;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT;
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return 0; }
  static constexpr type lowest() noexcept { return 0; }
  static constexpr type max() noexcept { return UCHAR_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_CHAR16_T
template<>
class numeric_limits<char16_t> {
 public:
  using type = char16_t;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(type);
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return 0; }
  static constexpr type lowest() noexcept { return 0; }
  static constexpr type max() noexcept { return UINT_LEAST16_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_CHAR32_T
template<>
class numeric_limits<char32_t> {
 public:
  using type = char32_t;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(type);
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return 0; }
  static constexpr type lowest() noexcept { return 0; }
  static constexpr type max() noexcept { return UINT_LEAST32_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_SHORT
template<>
class numeric_limits<short> {
 public:
  using type = short;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(type) - 1;
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return SHRT_MIN; }
  static constexpr type lowest() noexcept { return SHRT_MIN; }
  static constexpr type max() noexcept { return SHRT_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_UNSIGNED_SHORT
template<>
class numeric_limits<unsigned short> {
 public:
  using type = unsigned short;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits =  CHAR_BIT * sizeof(type);
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return 0; }
  static constexpr type lowest() noexcept { return 0; }
  static constexpr type max() noexcept { return USHRT_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_INT
template<>
class numeric_limits<int> {
 public:
  using type = int;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(type) - 1;
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return INT_MIN; }
  static constexpr type lowest() noexcept { return INT_MIN; }
  static constexpr type max() noexcept { return INT_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_UNSIGNED_INT
template<>
class numeric_limits<unsigned int> {
 public:
  using type = unsigned int;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(type);
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return 0; }
  static constexpr type lowest() noexcept { return 0; }
  static constexpr type max() noexcept { return UINT_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_LONG
template<>
class numeric_limits<long> {
 public:
  using type = long;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(type) - 1;
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return LONG_MIN; }
  static constexpr type lowest() noexcept { return LONG_MIN; }
  static constexpr type max() noexcept { return LONG_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_UNSIGNED_LONG
template<>
class numeric_limits<unsigned long> {
 public:
  using type = unsigned long;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(type);
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return 0; }
  static constexpr type lowest() noexcept { return 0; }
  static constexpr type max() noexcept { return ULONG_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_LONG_LONG
template<>
class numeric_limits<long long> {
 public:
  using type = long long;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = CHAR_BIT * sizeof(type) - 1;
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return LLONG_MIN; }
  static constexpr type lowest() noexcept { return LLONG_MIN; }
  static constexpr type max() noexcept { return LLONG_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_UNSIGNED_LONG_LONG
template<>
class numeric_limits<unsigned long long> {
 public:
  using type = unsigned long long;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = false;
  static constexpr bool is_integer = true;
  static constexpr bool is_exact = true;
  static constexpr bool has_infinity = false;
  static constexpr bool has_quiet_NaN = false;
  static constexpr bool has_signaling_NaN = false;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_absent;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = false;
  static constexpr float_round_style round_style = float_round_style::round_toward_zero;
  static constexpr bool is_iec559 = false;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = true;
  static constexpr int digits = CHAR_BIT * sizeof(type);
  static constexpr int digits10 = static_cast<int>(digits * 0.3010);
  static constexpr int max_digits10 = 0;
  static constexpr int radix = 2;
  static constexpr int min_exponent = 0;
  static constexpr int min_exponent10 = 0;
  static constexpr int max_exponent = 0;
  static constexpr int max_exponent10 = 0;
  static constexpr bool traps = true;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return 0; }
  static constexpr type lowest() noexcept { return 0; }
  static constexpr type max() noexcept { return ULLONG_MAX; }
  static constexpr type epsilon() noexcept { return 0; }
  static constexpr type round_error() noexcept { return 0; }
  static constexpr type infinity() noexcept { return 0; }
  static constexpr type quiet_NaN() noexcept { return 0; }
  static constexpr type signaling_NaN() noexcept { return 0; }
  static constexpr type denorm_min() noexcept { return 0; }
};
#endif

#if SS_HAS_TYPE_FLOAT
template<>
class numeric_limits<float> {
 public:
  using type = float;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool has_infinity = SS_DEFINED_INFINITY;
  static constexpr bool has_quiet_NaN = std::numeric_limits<type>::has_quiet_NaN;
  static constexpr bool has_signaling_NaN = std::numeric_limits<type>::has_signaling_NaN;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_present;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = true;
  static constexpr float_round_style round_style = float_round_style::round_to_nearest;
  static constexpr bool is_iec559 = std::numeric_limits<type>::is_iec559;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = FLT_MANT_DIG;
  static constexpr int digits10 = FLT_DIG;
  static constexpr int max_digits10 =
#if defined(FLT_DECIMAL_DIG)
  FLT_DECIMAL_DIG;
#else
  detail::rough_ceil<type>(digits * 0.30103000 + 1);
#endif
  static constexpr int radix = FLT_RADIX;
  static constexpr int min_exponent = FLT_MIN_EXP;
  static constexpr int min_exponent10 = FLT_MIN_10_EXP;
  static constexpr int max_exponent = FLT_MAX_EXP;
  static constexpr int max_exponent10 = FLT_MAX_10_EXP;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return FLT_MIN; }
  static constexpr type lowest() noexcept { return -FLT_MIN; }
  static constexpr type max() noexcept { return FLT_MAX; }
  static constexpr type epsilon() noexcept { return FLT_EPSILON; }
  static constexpr type round_error() noexcept { return 0.5F; }
  static constexpr type infinity() noexcept { return HUGE_VALF; }
  static constexpr type quiet_NaN() noexcept { return std::numeric_limits<type>::quiet_NaN(); }
  static constexpr type signaling_NaN() noexcept { return std::numeric_limits<type>::signaling_NaN(); }
  static constexpr type denorm_min() noexcept { return std::numeric_limits<type>::denorm_min(); }
};
#endif

#if SS_HAS_TYPE_DOUBLE
template<>
class numeric_limits<double> {
 public:
  using type = double;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool has_infinity = SS_DEFINED_INFINITY;
  static constexpr bool has_quiet_NaN = std::numeric_limits<type>::has_quiet_NaN;
  static constexpr bool has_signaling_NaN = std::numeric_limits<type>::has_signaling_NaN;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_present;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = true;
  static constexpr float_round_style round_style = float_round_style::round_to_nearest;
  static constexpr bool is_iec559 = std::numeric_limits<type>::is_iec559;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = DBL_MANT_DIG;
  static constexpr int digits10 = DBL_DIG;
  static constexpr int max_digits10 =
#if defined(DBL_DECIMAL_DIG)
      DBL_DECIMAL_DIG;
#else
      detail::rough_ceil<type>(digits * 0.30103000 + 1);
#endif
  static constexpr int radix = FLT_RADIX;
  static constexpr int min_exponent = DBL_MIN_EXP;
  static constexpr int min_exponent10 = DBL_MIN_10_EXP;
  static constexpr int max_exponent = DBL_MAX_EXP;
  static constexpr int max_exponent10 = DBL_MAX_10_EXP;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return DBL_MIN; }
  static constexpr type lowest() noexcept { return -DBL_MIN; }
  static constexpr type max() noexcept { return DBL_MAX; }
  static constexpr type epsilon() noexcept { return DBL_EPSILON; }
  static constexpr type round_error() noexcept { return 0.5; }
  static constexpr type infinity() noexcept { return HUGE_VAL; }
  static constexpr type quiet_NaN() noexcept { return std::numeric_limits<type>::quiet_NaN(); }
  static constexpr type signaling_NaN() noexcept { return std::numeric_limits<type>::signaling_NaN(); }
  static constexpr type denorm_min() noexcept { return std::numeric_limits<type>::denorm_min(); }
};
#endif

#if SS_HAS_TYPE_LONG_DOUBLE
template<>
class numeric_limits<long double> {
 public:
  using type = long double;

  static constexpr bool is_specialized = true;
  static constexpr bool is_signed = true;
  static constexpr bool is_integer = false;
  static constexpr bool is_exact = false;
  static constexpr bool has_infinity = SS_DEFINED_INFINITY;
  static constexpr bool has_quiet_NaN = std::numeric_limits<type>::has_quiet_NaN;
  static constexpr bool has_signaling_NaN = std::numeric_limits<type>::has_signaling_NaN;
  SS_DEPRECATED_DENORM_CXX23 static constexpr float_denorm_style has_denorm = float_denorm_style::denorm_present;
  SS_DEPRECATED_DENORM_LOSS_CXX23 static constexpr bool has_denorm_loss = true;
  static constexpr float_round_style round_style = float_round_style::round_to_nearest;
  static constexpr bool is_iec559 = std::numeric_limits<type>::is_iec559;
  static constexpr bool is_bounded = true;
  static constexpr bool is_modulo = false;
  static constexpr int digits = LDBL_MANT_DIG;
  static constexpr int digits10 = LDBL_DIG;
  static constexpr int max_digits10 =
#if defined(LDBL_DECIMAL_DIG)
      LDBL_DECIMAL_DIG;
#elif defined(DECIMAL_DIG)
      DECIMAL_DIG;
#else
      detail::rough_ceil<type>(digits * 0.30103000 + 1);
#endif
  static constexpr int radix = FLT_RADIX;
  static constexpr int min_exponent = LDBL_MIN_EXP;
  static constexpr int min_exponent10 = LDBL_MIN_10_EXP;
  static constexpr int max_exponent = LDBL_MAX_EXP;
  static constexpr int max_exponent10 = LDBL_MAX_10_EXP;
  static constexpr bool traps = false;
  static constexpr bool tinyness_before = false;

  static constexpr type min() noexcept { return LDBL_MIN; }
  static constexpr type lowest() noexcept { return -LDBL_MAX; }
  static constexpr type max() noexcept { return LDBL_MAX; }
  static constexpr type epsilon() noexcept { return LDBL_EPSILON; }
  static constexpr type round_error() noexcept { return 0.5L; }
  static constexpr type infinity() noexcept { return HUGE_VALL; }
  static constexpr type quiet_NaN() noexcept { return std::numeric_limits<type>::quiet_NaN(); }
  static constexpr type signaling_NaN() noexcept { return std::numeric_limits<type>::signaling_NaN(); }
  static constexpr type denorm_min() noexcept { return std::numeric_limits<type>::denorm_min(); }
};
#endif

} // namespace ss

#endif // SS_LIMITS_H_
